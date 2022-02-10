#ifndef _AT_SCRIPT_CANVAS_H_
#define _AT_SCRIPT_CANVAS_H_

#include <QtScript/QScriptClassPropertyIterator>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>
#include <QStatusBar>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QMap>
#include <QMessageBox>
#include <QtCore/QQueue>
#include <QtCore/QThread>
#include "startup_config.h"

class worker_sleep_signal : public QThread
{
    Q_OBJECT
public:
    // параметры сигнала с задержкой на срабатывание:
    //  const QString &s - полное название сигнала
    //  unsigned long msecs - время до посылки сигнала s (в мсек)
    explicit worker_sleep_signal(const QString &s, unsigned long msecs, QObject *parent = nullptr) :
            QThread(parent),str_command(s),msecs_sleep(msecs),m_abort(false){}
    void run() override {
        QThread::msleep(msecs_sleep);
        if(!m_abort) emit resultReady(str_command);
    }
    void abort(){m_abort=true;} //для отмены несработавшего (задержанного) сигнала
signals:
    void resultReady(const QString &s);
private:
    QString str_command;
    unsigned long msecs_sleep;
    bool m_abort;
};

class worker_blink_signals : public QThread
{
    Q_OBJECT
public:
    // параметры "мигающего объекта":
    //  const QString &obj - имя объекта
    //  const QString &com - состояния, которые периодически изменяются (разделенные двоеточием)
    //  unsigned long msecs - время между посылками сигналов на изменение состояния (в мсек)
    explicit worker_blink_signals(const QString &obj, const QString &com, unsigned long msecs, QObject *parent = nullptr) :
            QThread(parent),blink_obj(obj),commands(com),end_command(""),msecs_sleep(msecs),to_finished(false) {}
    void run() override {
        QStringList str_commands = commands.split(":");
        int index = 0;
        while (!to_finished) {
            QThread::msleep(msecs_sleep);
            emit resultReady(QString("%1:%2").arg(blink_obj).arg(str_commands[index++]));
            if(index==str_commands.size()) index = 0;
        }
        emit resultReady(QString("%1:%2").arg(blink_obj).arg(end_command));
    }
signals:
    void resultReady(const QString &s);

public slots:
    //  const QString &end_sost - конечное состояние, в котором должен остаться обьект после окончания мигания
    void stop_blink(const QString &end_sost){
        end_command = end_sost;
        to_finished = true;
    }
private:
    QString blink_obj;
    QString commands;
    QString end_command;
    unsigned long msecs_sleep;
    bool to_finished;
};

class at_script_canvas : public QObject
{
    Q_OBJECT

public:
    explicit at_script_canvas(startup_config* config, QObject *parent = nullptr) :
            QObject(parent), t_speed(config->train_speed),
            prop_name(QString("AT")){
//        Q_UNUSED(parent);
        sb =  parent->findChild<QStatusBar *>(QString::fromUtf8("statusBar"));
    }

    void set_js_file_name(const QString &js_name){js_file_name=js_name;}

//  Выполнение скрипта. Параметры:
//  object - указатель на объект из которого вызывается функция;
//  js_name - имя файла скрипта; function_name - наименование вызываемой функции;
//  property_name - символическое имя, через которое вызываются Q_INVOKABLE функции основной программы;
//  obj_name - параметр, который передается в вызываемую функцию.
    static void run_script(QObject *object, const QString &js_name, const QString &function_name, const QString &property_name, const QString &obj_name);

    //Запуск скрипта первоначальной инициализации вызывается из rw_peregon
    // или rw_stantion, где соединен с general_window::windowShown()
    void run_init_script(const QString &msg){
        run_script(this, js_file_name,QString("first_init"),prop_name,msg);
    }

    //Инициализация данных быстрого доступа к состояниям, типам и физ.длине объектов по имени
    void insert_obj(const QString &obj_name, int* p_sost, const QString &type, int ph_len){
        QString name = obj_name.split(QString(":"))[1];
        if(!obj_sost.contains(name)){
            obj_sost.insert(name, p_sost);
            obj_type.insert(name, type);
            obj_ph_len.insert(name, ph_len);
        }
    }

    QMap<QString, int>* get_map_len(){return &obj_ph_len;}
    QMap<QString, int*>* get_map_obj_sost(){return &obj_sost;}

    //Автоматическая генерация сигналов повторителю для увязки
    void insert_bind_obj(const QString &from,  int *f_sost, const QString &to, int *t_sost){
        BIND_SIGNAL bs;
        bs.from = from;
        bs.from_sost = f_sost;
        bs.to = to;
        bs.to_sost = t_sost;
        arr_bind_signals.append(bs);
    }

    //выполнение команды obj_sost с задержкой на msecs милисекунд
    Q_INVOKABLE void sleep_signal(const QString &obj_sost, unsigned long msecs)
    {
        auto workerThread = new worker_sleep_signal(obj_sost, msecs, this);
        s_sleep.insert(obj_sost,workerThread);
        connect(workerThread, &worker_sleep_signal::resultReady, this, &at_script_canvas::set_delay_sost);
        connect(workerThread, &worker_sleep_signal::finished, workerThread, &QObject::deleteLater);
        workerThread->start();
//        qInfo(QString("at_script_canvas::sleep_signal(%1, %2)").arg(obj_sost).arg(msecs).toUtf8());
    }

    //параметры "мигающего объекта на макете":
    //  const QString &obj - имя объекта
    //  const QString &com - состояния, которые периодически изменяются (разделенные двоеточием)
    //  unsigned long msecs - время между посылками сигналов на изменение состояния (в мсек)
    Q_INVOKABLE void start_blink_board(const QString &obj, const QString &com, unsigned long msecs){
        start_blink(obj,com,msecs,QString("board"));
    }
    Q_INVOKABLE void stop_blink_board(const QString &obj, const QString &end_sost){
        stop_blink(obj,end_sost,QString("board"));
    }
    Q_INVOKABLE int is_blink_board(const QString &obj){
        return is_blink(obj,QString("board"));
    }

    //параметры "мигающего объекта":
    //  const QString &obj - имя объекта
    //  const QString &com - состояния, которые периодически изменяются (разделенные двоеточием)
    //  unsigned long msecs - время между посылками сигналов на изменение состояния (в мсек)
    Q_INVOKABLE void start_blink_signal(const QString &obj, const QString &com, unsigned long msecs){
        start_blink(obj,com,msecs,QString("scr"));
    }
    Q_INVOKABLE void stop_blink_signal(const QString &obj, const QString &end_sost){
        stop_blink(obj,end_sost,QString("scr"));
    }
    Q_INVOKABLE int is_blink_signal(const QString &obj){
        return is_blink(obj,QString("scr"));
    }

    //сохранение имени нажатой кнопки
    Q_INVOKABLE void s_button(const QString &obj_name) {
        first_button.enqueue(obj_name);
    }
    //возвращает имя нажатой кнопки и удаляет его из очереди
    Q_INVOKABLE QString get_button() {
        if (!first_button.isEmpty())
            return first_button.dequeue();
        return QString("");
    }
    Q_INVOKABLE int sz_button() { return first_button.size(); }

    //получение состояния объекта в скрипте по его имени
    Q_INVOKABLE int s(const QString &obj_name){
        if(obj_sost.contains(obj_name)) return *obj_sost[obj_name];
        else return -1;
    }

    //получение типа объекта в скрипте по его имени
    Q_INVOKABLE QString st(const QString &obj_name){
        if(obj_type.contains(obj_name)) return obj_type[obj_name];
        else return QString("");
    }

    //получение времени (в mc) движения поезда со скоростью t_speed см/сек по физической
    //рельсовой линии (параметр pct - процент от полного времени проследования)
    Q_INVOKABLE int m_time(const QString &obj_name, int pct = 100){
        if(obj_ph_len.contains(obj_name))
            return pct * obj_ph_len[obj_name] / t_speed;
        else return -1;
    }

    //получение состояние основного сигнала по имени повторителя
    Q_INVOKABLE int ss(const QString &to){
        for (BIND_SIGNAL bin:arr_bind_signals)
            if (bin.to == to) return *bin.from_sost;
        return -1;
    }

    Q_INVOKABLE QStringList spl(const QString &signal, const QString &dt = QString(":")){ return signal.split(dt); }
    Q_INVOKABLE int to_int(const QString &signal){ return signal.toInt(); }
    Q_INVOKABLE QString to_str(int int_signal){ return QString("%1").arg(int_signal); }
    Q_INVOKABLE QString to_str(double double_signal){ return QString("%1").arg(double_signal); }
    Q_INVOKABLE int indexOf(const QString &str, const QString &substr){ return str.indexOf(substr); }
    Q_INVOKABLE int dlg_m_press(const QString &msg){
        return QMessageBox::question(nullptr, QString("Подтвердите"), msg, QMessageBox::Yes | QMessageBox::No);
    }
    Q_INVOKABLE void msg_script(const QString &msg){
//        QMessageBox::information(nullptr, QString("Информация"),msg);
        if(sb) sb->showMessage(msg,1000);
    }
    Q_INVOKABLE void msg_to_log(const QString &msg){
        qInfo("at_script_canvas::msg_to_log(%s)",msg.toUtf8().constData());
    }

public slots:
    //Сигнал приходит от напольных устройств (SIGNAL cyclocom::set_new_sost)
    //в виде ИМЯСТАНЦИИ:ИМЯОБЪЕКТА:НОВОЕСОСТОЯНИЕ, обрабатывается в функции скрипта
    //с именем change_sost, где вызывается сигнал set_new_sost, который соединен
    //со слотом SLOT environment::set_sost для отрисовки в новом состоянии
    void set_sost(const QString &str_sost){
        QStringList tmp = str_sost.split(QString(":"));
        //Если сигнал для меня, обрабатываем логику
        if(tmp[0]==objectName()) {
//            msg_to_log(QString("set_sost(%1) objectName() = %2").arg(str_sost).arg(objectName()));
            if(tmp.size()==2) {
                //Если контроль состояния станции (изменение цвета надписи на табло)
                set_new_sost(tmp[0], tmp[1].toInt());
            } else {
                //выполнение необходимой функциональности при изменении состояния объекта
                run_script(this, js_file_name, QString("change_sost"), prop_name, str_sost);
                //обработка сигнала повторителю
                for(BIND_SIGNAL b:arr_bind_signals)
                    if (b.from == QString(tmp[0] + ":" + tmp[1]))
                        if (*b.from_sost != *b.to_sost)
                            emit set_new_bind_sost(b.to + ":" + tmp[2]);
            }
        }
    }

    //Слот для сигналов контрольной панели. Параметр button_signal представляет
    //собой содержание тега signal, как прописано в файле panel.xml для нажатой кнопки
    void set_control_panel_sost(const QString &button_signal){
//        qInfo("at_script_canvas::set_control_panel_sost(%s) for objectName() = %s",
//              button_signal.toUtf8().constData(),objectName().toUtf8().constData());
        QStringList tmp = button_signal.split(QString(":"));
        if(tmp[0]==QString("ПУЛЬТ_%1").arg(objectName())) {
            run_script(this, js_file_name,QString("control_panel"),prop_name,button_signal);
            emit change_control_panel_sost(button_signal);
        }
    }

    //Слот для сигналов из Environment, сгенерированых по нажатию левой кнопки мыши.
    void set_mouse_press_sost(const QString &mouse_press_signal){
        QStringList tmp = mouse_press_signal.split(QString(":"));
        if(tmp[0]==objectName()) {
//            msg_to_log(QString("set_mouse_press_sost(%1) objectName() = %2").arg(mouse_press_signal).arg(objectName()));
            run_script(this, js_file_name, QString("mouse_press_command"), prop_name, mouse_press_signal);
        }
    }

    void set_sost_to_at(const QString &msg){
        emit set_sost_from_at(msg);
    }

    //удаление таймера из списка сигналов с задержкой
    void set_delay_sost(const QString &signal){
        if(s_sleep.contains(signal))
            s_sleep.remove(signal);
        emit set_sost(signal);
    }

signals:
    //Сигнал для перерисовки объекта в новом состоянии
    //Сигнал соединен со слотом set_sost(QString, int) в Environment
    void set_new_sost(QString name, int new_sost);

    //Сигнал для установки нового состояния напольных устройств
    //Сигнал соединен со слотом set_sost в cyclocom при
    //основном режиме или со слотом set_sost_to_log в тестовом.
    void set_sost_from_at(QString str_sost);

    //Сигнал для установки нового состояния повторителя, соединен
    //со слотом set_sost станции или перегона в соответствии
    //с данными секции <binding> файла настроек poligon.xml
    void set_new_bind_sost(QString str_sost);

    //Сигнал для отслеживания манипуляций пользователя с
    //контрольной панелью (ввод команд оператором)
    void change_control_panel_sost(const QString &button_signal);

private:
    //Скорость движения поезда (см/сек)
    int t_speed;

    //Имя файла скрипта
    QString js_file_name;
    //Имя proxi оьъекта для доступа к С++ функциям в скрипте
    QString prop_name;

    //Для быстрого доступа к состоянию объекта, его типу, длине рельсовой линии
    // по его имени, без указания имени станции или перегона
    QMap<QString, int*> obj_sost;
    QMap<QString, QString> obj_type;
    QMap<QString, int> obj_ph_len;

    //Список мигающих объектов экрана и макета
    QMap<QString, worker_blink_signals*> blink_obj;
    QMap<QString, worker_blink_signals*> blink_board;

    //Список команд с задержкой выполнения
    QMap<QString, worker_sleep_signal*> s_sleep;

    //Для сохранения названия первой нажатой маршрутной кнопки
    QQueue<QString> first_button;

    struct BIND_SIGNAL{
        QString from; //основной сигнал
        int *from_sost; //состояние основного сигнала
        QString to; //его повторитель
        int *to_sost; //состояние основного сигнала
    };
    typedef QVector<BIND_SIGNAL> ARRAY_OF_BIND_SIGNALS;
    ARRAY_OF_BIND_SIGNALS arr_bind_signals;
    void start_blink(const QString &obj, const QString &com, unsigned long msecs, const QString &s_b);
    void stop_blink(const QString &obj, const QString &end_sost, const QString &s_b);
    int is_blink(const QString &obj, const QString &s_b);
    QStatusBar *sb;
};

#endif //_AT_SCRIPT_CANVAS_H_
