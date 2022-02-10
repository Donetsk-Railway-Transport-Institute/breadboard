#include "rw_view_obj.h"

//соединяет сигналы из Environment со слотом объекта
void rw_view_obj::connected_signals()
{
    auto env = parent()->findChild<Environment*>(QString("Environment"));
    if(!env) qFatal("error find Environment");

    connect(env, SIGNAL(change_data(const QString &, int)), this, SLOT(set_sost(const QString &, int)));
    connect(env, SIGNAL(change_data(QString, int)), this, SLOT(set_sost(QString, int)));

    connect(this, SIGNAL(to_status_bar(QString)), env, SLOT(to_status_bar(QString)));
    connect(env, SIGNAL(obj_name_to_status_bar(int,int)), this, SLOT(obj_name_to_status_bar(int,int)));

    connect(this, SIGNAL(msg_info_text_obj(QString,int,int)), env, SLOT(msg_info_text_obj(QString,int,int)));
    connect(env, SIGNAL(obj_info_to_scr(int,int)), this, SLOT(obj_info_to_scr(int,int)));

    qDebug()<<"connected SIGNALs and SLOTs "<<env->objectName()<<" with "<<objectName();
}

void rw_view_obj::set_sost(const QString &name, int new_sost){
    //если это изменение отностится ко мне и новое состояние отличается от предыдущего
    if((name==objectName())&&(sost!=new_sost))
    {
        qDebug()<<"rw_view_obj func:set_sost name="<<name<<" sost="<<new_sost;
        sost=new_sost;
        if(!depends_type.isEmpty()) change_sost_depends();
        else
        {
            //изменяем собственное состояние
            change_sost();
            //и посылаем сигнал всем зависимым объектам
            depends_sost(name);
        }
    }
}

void rw_view_obj::obj_info_to_scr(int x,int y){
    if(it_my_cell(x,y)) {
        QString o_str(comment_type);
        o_str += QString(" <");
        o_str += objectName();
        o_str += QString(">");
        int tmp_sost=sost;
        if (!depends_type.isEmpty()) {
            o_str += QString(" зависит от ");
            o_str += depends_name;
            auto p_depends = parent()->findChild<rw_view_obj*>(depends_name);
            tmp_sost=sost*count_sost_in_depends_type+p_depends->sost;
        }
        o_str += QString(". Текущее состояние - ");
        o_str += comment_sost[tmp_sost];
        msg_info_text_obj(o_str, x, y);
        qDebug() << QString("SEND SIGNAL rw_view_obj::msg_info_text_obj(o_str=%1, x=%2, y=%3)").arg(o_str).arg(x).arg(y);
    }
}

void rw_view_obj::change_sost(){
    //по всем ячейкам объекта изменяем их состояние
    for(auto sc:self_cells) {
        if (sost != sc.data->get_view_state()) {
            sc.data->set_view_state(sost);
            set_views_data(sc.data, sc.row, sc.column);
        }
    }
}

void rw_view_obj::change_sost_depends(){
    auto p_depends = parent()->findChild<rw_view_obj*>(depends_name);
    if(!p_depends){
        qWarning("Error find depends_name %s for object %s",
                 depends_name.toUtf8().constData(),
                 objectName().toUtf8().constData());
    } else {
        for(auto sc:self_cells) {
            int new_sost=sost*count_sost_in_depends_type+p_depends->sost;
            qDebug()<<"rw_view_obj func:change_sost_depends name="<<objectName()<<" sost="<<new_sost;
            sc.data->set_view_state(new_sost);
            set_views_data(sc.data,sc.row,sc.column);
        }
    }
}

void rw_object::init(QXmlStreamAttributes attr, OBJECTS_NAMED_STATES* p_ons){
    int index_type = p_ons->get_index_for_type(attr.value(QString("type")).toString());
    type=p_ons->get_type_obj(index_type);
    if(attr.hasAttribute(QString("ph_len"))) ph_len = attr.value(QString("ph_len")).toInt();
    depends_type=p_ons->get_depends_type(index_type);
    if(depends_type != nullptr) {
        count_sost_in_depends_type=p_ons->get_count_sost(p_ons->get_index_for_type(depends_type));
        //ищем объект, от которого зависит данный
        auto p_depends = parent()->findChild<rw_view_obj*>(depends_name);
        if(p_depends){
            connect(p_depends, SIGNAL(depends_sost(QString)), this, SLOT(set_depends_sost(QString)));
            qDebug()<<"connected SIGNAL (depends_sost(QString)) "<<p_depends->objectName()<<" SLOT (set_depends_sost(QString)) "<<objectName();
        } else {
            qFatal("Error: depends object %s must be created before %s",
                   depends_name.toUtf8().constData(),
                   objectName().toUtf8().constData());
        }
    }
    else count_sost_in_depends_type=0;
    comment_type=p_ons->get_comment_type(index_type);
    for(int j=0;j<p_ons->get_count_sost(index_type);j++)
        comment_sost << p_ons->get_sost_comment(index_type, j);

    auto sc = new script_canvas(js_script_name,this);
    if(!sc->draw_obj(attr, p_ons))
        qFatal("rw_object::init : function sc->draw_obj(attr, p_ons) return false");
    int size_result = sc->script_result.size();
    if(size_result==0)
        qFatal("Error create cells array for object %s",
               objectName().toUtf8().constData());
    for(int i=0;i<size_result;i++){
        auto data = new one_cell_base;
        for(auto sc_pix:sc->script_result[i]->pixmaps) data->push_back_pix(sc_pix->copy());
        set_views_data(data,sc->script_result[i]->row,sc->script_result[i]->column);
        self_cells.push_back({sc->script_result[i]->row,sc->script_result[i]->column,data});
        qDebug()<<"insert data object name= "<<objectName()<<
                  " to cell (row="<<sc->script_result[i]->row<<
                  " column="<<sc->script_result[i]->column<<")";
    }

    //соединяет сигналы из Environment со слотом объекта (функция базового класса)
    connected_signals();
}
