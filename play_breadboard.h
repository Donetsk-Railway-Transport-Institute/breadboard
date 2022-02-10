#ifndef BREADBOARD_PLAY_BREADBOARD_H
#define BREADBOARD_PLAY_BREADBOARD_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QButtonGroup>
#include <QtCore/QTime>
#include "at_script_canvas.h"

class moving_train : public QObject
{
Q_OBJECT
public:
    explicit moving_train(const QString &name_rail, QMap<QString, int> *p_lr, int t_s, QObject *parent = nullptr) :
            QObject(parent),train_speed(t_s),lr(p_lr),train_head_rail(name_rail),
            train_tail_rail(name_rail),to_rail(""),t_moving(false){}

    //команда на занятие/освобождение участка (signal) c задержкой (tm)
    void train_movie(const QString &signal, unsigned long tm){
        auto sts = new worker_sleep_signal(signal, tm, this);
        ws_signals.insert(signal,sts);
        connect(sts, &worker_sleep_signal::resultReady, this, &moving_train::sleep_train_signal);
        connect(sts, &worker_sleep_signal::finished, sts, &QObject::deleteLater);
        sts->start();
    }
    void rm_sleep_signal(worker_sleep_signal *ws){
        ws->abort();
        ws->quit();
        ws->wait();
    }

    //местонахождение головы поезда
    QString head_train(){return train_head_rail;}
    QString tail_train(){return train_tail_rail;}

public slots:
    //команда, формируемая в скрипте, содержит название участка в который
    //включается тяга и участок, на который должен переместиться поезд
    void power_on(const QString &rail, const QString &next_rail){
        //если включение тяги для участка, на котором не находится
        //ни голова ни хвост, то это не имеет отношения к данному поезду
        if((rail!=train_head_rail)&&(rail!=train_tail_rail)) return;
        power_rails<<rail;  //в список участков с включенной тягой
        to_rail = next_rail; //на какой участок должен переместиться поезд
        if(lr->contains(rail)) { //если участок есть в списке, содержащем их длины
            unsigned long msec = (unsigned long)100*lr->value(rail)/train_speed;
            if(!t_moving) msec /= 10; //если стояли перед закрытым сигналом то 10% времени проследования участка
            train_movie(QString("%1:1").arg(to_rail),msec); //перемещение головы
            train_movie(QString("%1:2").arg(train_head_rail), msec+1000); //освобождение хвостом поезда считаем, что длина поезда 19 см (время в движении 1 сек).
        } else qWarning(QString("%1 is not found.").arg(rail).toUtf8());
        t_moving = true;
    }
    //команда, формируемая в скрипте при выключении тяги
    void power_off(const QString &rail){
        if((rail!=train_head_rail)&&(rail!=train_tail_rail)) return;
        power_rails.removeAll(rail);  //удаление из списка участков с включенной тягой
        //если поезд полностью находится на участке и выключается тяга - остановка
        if((rail==train_head_rail)&&(train_tail_rail==train_head_rail)) {
            t_moving = false;
            QMap<QString,worker_sleep_signal*>::const_iterator i = ws_signals.constBegin();
            while (i != ws_signals.constEnd()){
                rm_sleep_signal(i.value());
                ++i;
            }
            ws_signals.clear();
        }
    }
    //команда пришедшая после выдержки времени
    void sleep_train_signal(const QString &s){
        //сигнал сформирован, удаляем его из списка сигналов с задержкой форирования
        if(ws_signals.contains(s)){
            rm_sleep_signal(ws_signals[s]);
            ws_signals.remove(s);
        }
        QStringList tmp = s.split(":");
        //если ни с головы ни с хвоста нет тяги - остановка
        if((!power_rails.contains(train_tail_rail))&&
           (!power_rails.contains(train_head_rail))) {
            t_moving = false;
            //если освобождение хвостом и поезд на разных участках
            //и этот участок не является текущим (фильтрация сигналов при остановке поезда)
            if((tmp[2].contains("2"))&&(train_head_rail!=QString("%1:%2").arg(tmp[0]).arg(tmp[1]))) emit train_signal(s);
        } else {
            if (tmp[2].contains("2")) { //если освобождение участка хвостом
                train_tail_rail = train_head_rail;
            } else { //занятие участка головой поезда
                train_head_rail = QString("%1:%2").arg(tmp[0]).arg(tmp[1]);
            }
            emit train_signal(s);
        }
        if(train_tail_rail == train_head_rail) emit train_on_track(train_head_rail);
    }

signals:
    void train_signal(const QString &);
    void train_on_track(const QString &);

private:
    int train_speed; //Скорость движения поезда (см/сек)
    //длинны участков указатель на play_breadboard::len_rail
    QMap<QString, int> *lr;
    //список сигналов с задержкой форирования
    QMap<QString,worker_sleep_signal*> ws_signals;
    QList<QString> power_rails; //список участков с включенной тягой
    QString train_head_rail; //участок пути, на котором находится голова поезда
    QString train_tail_rail; //участок пути, на котором находится хвост поезда
    QString to_rail; //участок пути, на который должен переместится поезд
    bool t_moving; //движется или стоит поезд
};

struct RESULT_GAMES{
    QString name;   //имя игрока
    QTime result;   //результат (время, затраченное на игру)
    bool this_result; //флаг, что этот результат получен в данной игре
};

class play_breadboard : public QObject {
    Q_OBJECT
public:
    explicit play_breadboard(startup_config* config, QWidget *parent)
        :QObject(parent),t_speed(config->train_speed),dlg_choice_game(nullptr),
          dlg_result_games(nullptr),buttongroup(nullptr),init_script(""),
          move_train_script(""),stop_time(QString("00:00:000")),
         at_sc(new at_script_canvas(config, this)){ parse_xml(config->play_name); }
    //вызов окна выборы сценария игры, возвращает true,
    //если сценарий выбран, false, если нажата кнопка отмены
    bool choice_game();

    void insert_len_rail(const QString &obj_name, int len){
        if(!len_rail.contains(obj_name))
            len_rail.insert(obj_name, len);
    }
    void insert_obj_sost(const QString &obj_name, int *o_sost){
        if(!obj_sost.contains(obj_name))
            obj_sost.insert(obj_name, o_sost);
    }

    //создание поезда с номером num, стоящего на участке t_rail
    Q_INVOKABLE void create_train(const QString &num, const QString &t_rail){
        auto train = new moving_train(t_rail, &len_rail, t_speed, this);
        trains.insert(num,train);
        connect(train, &moving_train::train_signal, this, &play_breadboard::set_new_sost);
        connect(train, &moving_train::train_on_track, this, &play_breadboard::train_on_track);
        connect(this, &play_breadboard::power_on, train, &moving_train::power_on);
        connect(this, &play_breadboard::power_off, train, &moving_train::power_off);
        emit set_new_sost(QString("%1:%2").arg(t_rail).arg(1));
    }

    //получение времени (в mc) движения поезда со скоростью 19 см/сек по физической
    //рельсовой линии (параметр pct - процент от полного времени проследования)
    Q_INVOKABLE int m_time(const QString &obj_name, int pct = 100){
        if(len_rail.contains(obj_name)) return pct*len_rail[obj_name]/t_speed;
        else return -1;
    }

    //окно с описанием выбранного сценария
    Q_INVOKABLE void first_help();
    //окно окончания игры
    Q_INVOKABLE void w_game_ower();
    Q_INVOKABLE void set(const QString &command){ emit set_new_sost(command); }
    Q_INVOKABLE void run(const QString &script_name){
        at_script_canvas::run_script(this,script_name,QString("run"),QString("G"),QString(""));
    }
    //возвращает местонахождение головы поезда по его номеру
    Q_INVOKABLE QString head_train(const QString &train_num){
        return trains[train_num]->head_train();
    }
    //возвращает местонахождение хвоста поезда по его номеру
    Q_INVOKABLE QString tail_train(const QString &train_num){
        return trains[train_num]->tail_train();
    }

    Q_INVOKABLE QStringList spl(const QString &signal, const QString &dt = QString(":")){ return signal.split(dt); }
    Q_INVOKABLE int indexOf(const QString &str, const QString &substr){ return str.indexOf(substr); }
    //получение состояния объекта в скрипте по его имени
    Q_INVOKABLE int s(const QString &obj_name){
        if(obj_sost.contains(obj_name)) return *obj_sost[obj_name];
        else return -1;
    }
    Q_INVOKABLE void msg_to_log(const QString &msg){
        qInfo(QString("play_breadboard::msg_to_log(%1)").arg(msg).toUtf8());
    }

public slots:
    //Запись команд напольным устройствам
    //соединен с сигналом set_sost_from_at из МПЦ или АТ
    void set_sost_to_board(const QString &msg){
        QStringList tmp = msg.split(":");
        //если это команда, относящаяся к тяге поездов
        if(tmp[1].indexOf("Т")==0)
            at_script_canvas::run_script(this, move_train_script, QString("move_train"), QString("G"), msg);
    }
    //после посылки sw_stop() вызывается этот слот
    //и возвращает показание секундомера
    void sw_stop_time(const QString &s_time){ stop_time = s_time; }
    //начальная инициализация (соединен с general_window::windowShown())
    void init_game(){
        at_script_canvas::run_script(this, curr_game.script_name,QString("first_init"),QString("G"),init_script);
    }
    //Сигнал для отслеживания манипуляций пользователя с
    //контрольной панелью (ввод команд оператором)
    void change_control_panel_sost(const QString &button_signal){
        at_script_canvas::run_script(this, curr_game.script_name,QString("button_press"),QString("G"),button_signal);
    }
    //Местонахождение поезда (сигнал генерируется по факту освобождения участка хвостом)
    void train_on_track(const QString &name_track){
        at_script_canvas::run_script(this, curr_game.script_name,QString("game_over"),QString("G"),name_track);
    }

    void on_pb_again_pressed(){ //сыграть еще раз
        dlg_result_games->done(0);
        emit init_poligon();
        init_game();
    }
    void on_pb_other_pressed(){ //сыграть другой сценарий
        dlg_result_games->done(1);
        emit init_poligon();
        choice_game();
        init_game();
    }
    void on_pb_exit_pressed(){ //выйти из программы
        qFatal(QString("Выход из игры после окончания сценария: %1").arg(curr_game.name).toUtf8());
    }

signals:
    //Сигнал для отрисовки полигона в первоначальном состоянии
    void init_poligon();
    //Сигнал для перерисовки объекта в новом состоянии
    //соединен со слотом set_sost(QString) в МПЦ или АТ
    void set_new_sost(const QString &name);
    //команда, формируемая в скрипте, содержит название участка в который
    //включается тяга и участок, на который должен переместиться поезд
    void power_on(const QString &this_rail, const QString &next_rail);
    //команда, формируемая в скрипте при выключении тяги
    void power_off(const QString &rail);
    //запуск и остановка секундомера
    void sw_start();
    void sw_stop();

private:
    int t_speed; //Скорость движения поезда (см/сек)
    QDialog *dlg_choice_game; //окно выбора сценария игры
    QDialog *dlg_result_games; //окно просмотра результатов игр (рекорды)
    QButtonGroup *buttongroup;
    QString init_script;    //имя файла скрипта инициализации для всех игр
    QString move_train_script;  //имя файла скрипта движения поезда
    struct PLAY_GAME{
        QString name; //название игры
        QString script_name; //имя файла скрипта
        QString html_name; //имя файла с информацией о сценарии игры
        QString result_name; //имя файла с информацией о рекордах
    };
    QVector<PLAY_GAME> games_name;
    //выбранный сценарий игры
    PLAY_GAME curr_game;
    void parse_xml(const QString &file_name);    
    QString stop_time;
    at_script_canvas *at_sc;
    //данные длин участков
    QMap<QString, int> len_rail;
    //данные состояния объектов автоматики
    QMap<QString, int*> obj_sost;
    //Список поездов
    QMap<QString, moving_train*> trains;
    void load_result_games(const QString &file_name); //чтение файла с результатами игр (рекорды)
    void save_result_games(const QString &file_name); //запись файла с результатами игр (рекорды)
    QList<RESULT_GAMES> lst_results;
};

#endif //BREADBOARD_PLAY_BREADBOARD_H
