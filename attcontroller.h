#ifndef BREADBOARD_ATTCONTROLLER_H
#define BREADBOARD_ATTCONTROLLER_H

#include "at_script_canvas.h"

//автодиспетчер
class ATTController : public at_script_canvas {
    Q_OBJECT

public:
    explicit ATTController(startup_config* config, QObject *parent = nullptr) :
            at_script_canvas(config, parent),cycle_num(0){}

    void first_init(){
        at_script_canvas::run_script(this, attctr_script,QString("first_init"),QString("A"),QString(""));
    }

    Q_INVOKABLE void send_ctr_panel(const QString &button){ emit send_button(button); }
    Q_INVOKABLE void set_sycle_num(int num){ cycle_num = num; }
    Q_INVOKABLE int get_sycle_num(){ return cycle_num; }

signals:
    void send_button(const QString &);

public slots:
    //Сигнал для перерисовки объекта в новом состоянии
    //Сигнал соединен со слотом set_sost(QString, int) в Environment
    void a_set_new_sost(QString name, int new_sost){
        at_script_canvas::run_script(this, attctr_script, QString("set_new_sost"), QString("A"), QString("%1:%2").arg(name).arg(new_sost));
    }

    //Сигнал для установки нового состояния напольных устройств
    //Сигнал соединен со слотом set_sost в cyclocom при
    //основном режиме или со слотом set_sost_to_log в тестовом.
    void a_set_sost_from_at(QString str_sost){
        at_script_canvas::run_script(this, attctr_script, QString("set_sost_from_at"), QString("A"), str_sost);
    }

    //Сигнал для установки нового состояния повторителя, соединен
    //со слотом set_sost станции или перегона в соответствии
    //с данными секции <binding> файла настроек poligon.xml
    void a_set_new_bind_sost(QString str_sost){
        at_script_canvas::run_script(this, attctr_script, QString("set_new_bind_sost"), QString("A"), str_sost);
    }
    //Сигнал для отслеживания манипуляций пользователя с
    //контрольной панелью (ввод команд оператором)
    void a_change_control_panel_sost(const QString &button_signal){
        at_script_canvas::run_script(this, attctr_script, QString("change_control_panel_sost"), QString("A"), button_signal);
    }

private:
    const QString attctr_script = QString("./xml/Автодиспетчер/attctr.js");  //имя файла скрипта
    int cycle_num;

};
#endif //BREADBOARD_ATTCONTROLLER_H
