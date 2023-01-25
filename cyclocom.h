//
// Created by User on 16.02.2018.
//

#ifndef BREADBOARD_CYCLOCOM_H
#define BREADBOARD_CYCLOCOM_H

#include <QObject>
#include <QAction>
#include <QTimer>
#include <QEventLoop>
#include <QMessageBox>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QXmlStreamAttributes>
#include <QtCore/QTime>
#include <QtWidgets/QStatusBar>
#include <QTcpSocket>
#include "at_script_canvas.h"

struct Settings {
    QString name;
    qint32 baudRate;
    QString stringBaudRate;
    QSerialPort::DataBits dataBits;
    QString stringDataBits;
    QSerialPort::Parity parity;
    QString stringParity;
    QSerialPort::StopBits stopBits;
    QString stringStopBits;
    QSerialPort::FlowControl flowControl;
    QString stringFlowControl;
};

const QString CONNECT_TCP_HOST = QString("Connect to TCP host");
const QString DISCONNECT_TCP_HOST = QString("Disonnect TCP host");
const int TCP_CODE_SIZE = 16;

class cyclocom;

class script_thread : public QThread
{
    Q_OBJECT
public:
    //Параметры: code_write - текуший код (иммитация функции QSerialPort::write(byteArray))
    //s_name - имя скрипта, count - счетчик команд (необходим для реализации логики скрипта)
    explicit script_thread(const QByteArray &code_write,const QString &s_name, uint count):
            code(code_write),script_name(s_name),counter(count){}

    void run() override {
        QByteArray str_code = code.toHex(' ').toUpper();
        at_script_canvas::run_script(this, script_name, QString("write"), QString("C"), str_code);
    }

    //скрипт возвращает данные (эмуляция)
    Q_INVOKABLE void set_e_data(const QString &r_data){
        QByteArray e_data = QByteArray::fromHex(r_data.toUtf8());
        emit script_readData(e_data);
    }
    Q_INVOKABLE uint get_count(){ return counter; }
    Q_INVOKABLE void msg_to_log(const QString &msg){
        qWarning("ESerialPort: msg_to_log(%s)",msg.toUtf8().constData());
    }

signals:
    void script_readData(const QByteArray &);

private:
    QByteArray code;
    QString script_name;
    //счетчик команд (необходим для реализации логики скрипта)
    uint counter;
};

//Эмулятор СОМ порта
class ESerialPort : public QSerialPort
{
    Q_OBJECT
public:
    inline void delay(uint millisecondsWait) {
        QEventLoop loop;
        QTimer t;
        t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
        t.start(static_cast<int>(millisecondsWait));
        loop.exec();
    }

    explicit ESerialPort(QObject *parent = nullptr):
            QSerialPort(parent),connect_to_com_port(false),
            script_name(QString("")),e_data(QByteArray::fromHex("000000")),
            time_limit(0),counter(0){}

    void openSerialPort(const Settings &p){
        setPortName(p.name);
        setBaudRate(p.baudRate);
        setDataBits(p.dataBits);
        setParity(p.parity);
        setStopBits(p.stopBits);
        setFlowControl(p.flowControl);
        connect_to_com_port = open(QIODevice::ReadWrite);
    }
    //Если connect_to_com_port==false - работа в режиме эмуляции
    bool connect_to_com_port;

    qint64 write_to(const QByteArray &byteArray){
        emit change_count_cycles(counter++);
        if(connect_to_com_port) return QSerialPort::write(byteArray);
        else {
            if(script_name==QString("")) return -1;
            //в режиме эмуляции запускается скрипт, иммитирующий ответы модулей
            auto sr = new script_thread(byteArray, script_name,counter);
            connect(sr, &script_thread::script_readData, this, &ESerialPort::script_readData);
            sr->start();
            return byteArray.size();
        }
    }
    //чтение данных из порта, в режиме эмуляции возвращает e_data,
    //значение которой устанавливается в скрипте
    QByteArray read_from(){
        if(connect_to_com_port) return QSerialPort::readAll();
        else return e_data;
    }

    void set_script_name(const QString &file_name){script_name = file_name;}
    void set_time_limit(uint t_l){ time_limit=t_l; }

signals:
    //Эмуляция сигнала приема данных в режиме тестирования
    void test_readData();
    void change_count_cycles(uint c);

public slots:
    void script_readData(const QByteArray &data){
        e_data = data;
        emit test_readData();
    }

private:        
    QString script_name;
    QByteArray e_data;
    //Промежуток времени до следующей посылки запроса контроля состояния устройств (Цикл опроса)
    uint time_limit;
    //счетчик команд (необходим для реализации логики скрипта)
    uint counter;
};

//Интерфейс взаимодействия с макетом по порту RS232
class cyclocom : public QObject
{
    Q_OBJECT

public:
    explicit cyclocom(const QString &xml_file_name, QObject *parent = nullptr);
    ~cyclocom() final { closeSerialPort(); }

    //Установка эмуляциии СОМ порта.
    void set_emulate(const QString &name_script){
        qWarning("Serial port %s started in emulation mode",get_port_name().toUtf8().constData());
        closeSerialPort();
        m_serial->set_script_name(name_script);
        disconnect(m_serial, &QSerialPort::readyRead, this, &cyclocom::readData);
        connect(m_serial, &ESerialPort::test_readData, this, &cyclocom::readData);
    }
    void set_sb(QStatusBar *statusBar) {
        sb = statusBar;
        connect(this, SIGNAL(msg_to_statusbar(QString, int)), statusBar, SLOT(showMessage(QString, int)));
    }

    //Пункт меню connect или disconnect TCP socket
    void set_action_connect_disconnect(QAction *con_discon) { menu_connect_disconnect = con_discon;}
    void closeSerialPort(){if (m_serial->isOpen()) m_serial->close();}
    bool is_connect_to_com_port(){return m_serial->connect_to_com_port;}

public slots:
    //Чтение данных из порта
    void readData();

    //Преобразование из строчной команды в байтовую посылку и запись данных в порт
    //Приходит из set_sost_from_at(QString)
    void set_sost(QString str_sost);

    //перед закрытием главного окна передаем команды из fin_command
    void reset_controllers() {
        for (auto f_c:fin_command) {
            set_sost(f_c.msg);
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Information,
                                                  "Перезагрузка",f_c.comment,
                                                  QMessageBox::Ok);
            QTimer *msgBoxCloseTimer = new QTimer(this);
            msgBoxCloseTimer->setInterval(1000);
            msgBoxCloseTimer->setSingleShot(true);
            connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject()));
            msgBoxCloseTimer->start();
            msgBox->exec();
        }
    }

    //Контроль ответа модуля по порту
    void ansver_timer_control();
    QString get_port_name(){return p.name;}

    //Циклический опрос состояния объектов контроля.
    //Вызывается с периодичностью time_next_control_object
    //для посылки в сом порт кода следующего объекта контроля
    void next_control_object();

    // Соединение с сервером TCP
    void connect_to_tcp_host();

private slots:
    //сигнал readyRead вызывается, когда сокет получает пакет (который может быть лишь частью отправленых данных) байтов
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);

signals:
    // Соединен со слотом set_sost(QString) в МПЦ
    void set_new_sost(const QString &);
    //Генерируется после прихода команды по TCP сокету
    // Соединен со слотом set_sost_from_tcp(QString) в МПЦ
    void set_sost_from_tcp(const QString &);
    //Генерируется при записи в порт циклической команды опроса состояния
    void write_cycle_code(const QString &);
    //Генерируется при чтении из порта результата циклической команды опроса состояния
    void read_cycle_code(const QString &);
    //Контроль отвеа модуля (генерируется если пришедший сигнал соответствует переданному)
    void ansver_module(const QString &);
    //Отсутствие контроля ответа модуля по порту дольше чем
    //время ожидания ответа модуля по порту time_limit_control
    void time_limit_error(const QString &);
    //Для вывода информации об ошибках в статус бар
    void msg_to_statusbar(QString, int);

public:
    struct StrCommand{
        QString msg;
        QByteArray code;
        QString comment;
    };
    int CODE_SIZE;
    //Список команд, передаваемых перед закрытием основного окна (перезагрузка контроллеров)
    QVector <StrCommand> fin_command;
    QVector <StrCommand> log_fin_command; //и какие из них необходимо логгировать

    //Список команд управления и соответствующих им кодов
    QVector <StrCommand> s_command;
    QVector <StrCommand> log_s_command; //и какие из них необходимо логгировать

    //Список циклических команд, подаваемых в компорт
    QVector <StrCommand> s_cycle;

    //Список кодов и соответсвующих им состояний объектов контроля
    QVector <StrCommand> s_control;
    QVector <StrCommand> log_s_control; //и какие из них необходимо логгировать

    //Список кодов и соответсвующих им ошибок при обработке данных
    QVector <StrCommand> s_errors;
    QVector <StrCommand> log_s_errors; //и какие из них необходимо логгировать

    //Список команд и текущих состояний объектов контроля,
    //предназначеный для выявления новой информации
    QMap<QString,QString> data_curr_sost;

    ESerialPort *m_serial;

    //Время ожидания ответа модуля по порту
    int time_limit_control;
    //Промежуток времени до следующей посылки запроса контроля состояния устройств (Цикл опроса)
    int time_next_control_object;
    //Индекс команды в s_cycle, которая будет послана в сом-порт следующей из слота next_control_object()
    int index_next_control_object;
    //индикатор запуска таймера контроля ответа модуля после записи в СОМ порт
    bool ansver_com_timer;

private:
    Settings p;
    QString filename_or_full; //имя файла с сигналами для логгирования

    // Обмен данными через TCP сокет
    QString host;
    quint16 port;
    QTcpSocket *tcp_sok;
    void send_to(const QString &data); //запись данных в сокет
    QAction *menu_connect_disconnect;

    void xml_read(const QString &xml_name);
    void logger_xml_read();
    bool new_info(const QString &msg);
    void set_sost_log(QString str_sost); //логгирование новых состояний
    QByteArray curr_code_write;
    QByteArray cycle_code_write;
    QByteArray read_buffer;
    void insert_data(QVector <StrCommand> &to,QXmlStreamAttributes attr);
    QQueue<QString> queue_commands;
    void work_with_errors(const QByteArray &err);
    QStatusBar *sb;
};

#endif //BREADBOARD_CYCLOCOM_H
