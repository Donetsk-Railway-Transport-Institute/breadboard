//
// Created by User on 27.03.2018.
//

#ifndef BREADBOARD_RW_STANTION_H
#define BREADBOARD_RW_STANTION_H

#include "rw_view_obj.h"
#include "at_script_canvas.h"

class rw_poligon : public rw_view_obj
{
    Q_OBJECT
public:
    explicit rw_poligon(const QXmlStreamAttributes &attr, OBJECTS_NAMED_STATES* p_ons,
                        startup_config* config, QObject *parent = nullptr):
            rw_view_obj(attr.value(QString("name")).toString(),parent),
            color_background(config->W_COLOR_BACKGROUND), p_obj_name_state(p_ons),
            Valid(false),s_config(config){}

    void parse(const QString &name_xml);
    QString color_background;
    bool isValid(){return Valid;}

    //Возвращает имя объекта по координатам одной
    // из клеток, которые занимает объект
    QString get_objects_name_by_xy(int x,int y){
        for(auto obj : objects)
            if(obj->it_my_cell(x,y))
                return obj->objectName();
        return QString("");
    }

protected:
    MAPOFRAILWAYOBJECTS objects;
    OBJECTS_NAMED_STATES* p_obj_name_state;
    bool Valid;
    startup_config* s_config;
};

//объект типа "Станция"
class rw_stantion : public rw_poligon
{
Q_OBJECT
public:
    explicit rw_stantion(const QXmlStreamAttributes &attr, const QString &name_xml,
                         OBJECTS_NAMED_STATES* p_ons, startup_config* config, QObject *parent = nullptr):
            rw_poligon(attr, p_ons, config, parent),
            st_mpc(new at_script_canvas(config, parent)),
            control_panel(nullptr)
    {
        st_mpc->setObjectName(attr.value(QString("name")).toString());
        int x = attr.value(QString("x")).toString().toInt();
        int y = attr.value(QString("y")).toString().toInt();
        init(x,y,p_ons->get_index_for_type(QString("stantion")));
        rw_poligon::parse(name_xml);
        //После того, как все объекты для станции созданы,
        //создаем структуру быстрого доступа к состоянию, типу и физ.длине объектов
        for(auto obj : objects)
            st_mpc->insert_obj(obj->objectName(), obj->ptr_sost(), obj->r_type(), obj->get_ph_len());
        Valid = true;
    }

    //микропроцессорная централизация данной станции
    at_script_canvas *st_mpc;
    control_window *control_panel;

    void set_control_panel(control_window *cw){ control_panel=cw; }

    void show_control_panel(){
        if(control_panel) control_panel->show();
    }

public slots:
    //начальная инициализация (соединен с general_window::windowShown())
    void first_init(){
        st_mpc->run_init_script(objectName());
    }

    //Слот для приема команд, пришедших по TCP сокету
    void set_sost_from_tcp(const QString &code){ st_mpc->set_control_panel_sost(control_panel->code_command[code]);}

private:
    //инициализация. Параметры - клетка начала, конца и код станции
    void init(int x, int y, int index_type);
};

typedef QVector<rw_stantion*> ARRAYOFSTANTION;

//объект типа "Перегон"
class rw_peregon : public rw_poligon
{
Q_OBJECT
public:
    explicit rw_peregon(const QXmlStreamAttributes &attr, const QString &name_xml,
                        OBJECTS_NAMED_STATES* p_ons,startup_config* config, QObject *parent = nullptr):
            rw_poligon(attr, p_ons, config, parent), at(new at_script_canvas(config, parent)){
        at->setObjectName(attr.value(QString("name")).toString());
        rw_poligon::parse(name_xml);
        //После того, как все объекты для станции созданы,
        //создаем структуру быстрого доступа к состоянию, типу и физ.длине объектов
        for(auto obj : objects)
            at->insert_obj(obj->objectName(), obj->ptr_sost(), obj->r_type(), obj->get_ph_len());
        Valid = true;
    }

    at_script_canvas *at;

public slots:
    //начальная инициализация (соединен с general_window::windowShown())
    void first_init(){
        at->run_init_script(objectName());
    }
};

typedef QVector<rw_peregon*> ARRAYOFPEREGON;

#endif //BREADBOARD_RW_STANTION_H
