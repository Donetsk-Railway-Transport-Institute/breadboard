//
// Created by User on 27.03.2018.
//

#include <QtScript/QScriptClassPropertyIterator>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>
#include <QDebug>
#include <QFile>
#include <QtDebug>
#include "rw_stantion.h"
#include "before_started.h"

void rw_poligon::parse(const QString &name_xml)
{
    B_S::xml_valid(name_xml);
    QFile xml_file(name_xml);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s (rw_poligon::parse())",name_xml.toUtf8().constData());
    auto xml = new QXmlStreamReader(&xml_file);
    while (!xml->atEnd() && !xml->hasError()){
        xml->readNext();
        QString name = xml->name().toString();
        if((xml->isStartElement())&&(name==QString("objects"))) {
            while (!(xml->isEndElement() && name == QString("objects"))) {
                xml->readNext();
                name = xml->name().toString();
                if (xml->isStartElement() && name == QString("obj")) {
                    QXmlStreamAttributes attr = xml->attributes();
                    if (attr.value(QString("name")).length() == 0)
                        qFatal(QString("error: not found attrbute 'name' for parsing stantion %1").arg(
                                objectName()).toUtf8());
                    QString name_object = objectName() + ":" + attr.value(QString("name")).toString();
                    auto obj = new rw_object(name_object, s_config->objects_view_script, rw_view_obj::parent());
                    if (attr.value(QString("depends_name")).size() > 0) {
                        QString depends_name = objectName() + ":" + attr.value(QString("depends_name")).toString();
                        obj->set_depends_name(depends_name);
                    }
                    obj->init(attr, p_obj_name_state);
                    if(!objects.contains(name_object)) objects.insert(name_object, obj);
                }
            }
        }
    }
}

void rw_stantion::init(int x, int y, int index_type)
{
    type=p_obj_name_state->get_type_obj(index_type);
    comment_type=p_obj_name_state->get_comment_type(index_type);
    for(int j=0;j<p_obj_name_state->get_count_sost(index_type);j++)
        comment_sost<<p_obj_name_state->get_sost_comment(index_type,j);

    auto sc = new script_canvas(s_config->objects_view_script, this);
    QString color = p_obj_name_state->get_color(index_type,0);
    QString color_background = p_obj_name_state->get_color_background(index_type,0);
    QPixmap* pic1 = sc->get_draw_text(objectName(),color,color_background);
    color = p_obj_name_state->get_color(index_type,1);
    color_background = p_obj_name_state->get_color_background(index_type,1);
    QPixmap* pic2 = sc->get_draw_text(objectName(),color,color_background);
    if(!(pic1&&pic2))
        qWarning(QString("Error create pixmaps for stantion %1").arg(objectName()).toUtf8());
    int w = pic1->size().width();
    int h = pic1->size().height();

    for(int i=0;i<w/h;i++)
    {
        QPixmap tmp_pic1 = QPixmap(QSize(h,h));
        tmp_pic1=pic1->copy(QRect(i*h,0,h,h));
        QPixmap tmp_pic2 = QPixmap(QSize(h,h));
        tmp_pic2=pic2->copy(QRect(i*h,0,h,h));
        auto data = new one_cell_base;
        data->push_back_pix(tmp_pic1);
        data->push_back_pix(tmp_pic2);
        CELLS c = {
                y,      //row
                x+i,    //column
                data    //data
        };
        //генерация сигнала для вставки данных в клетку отображения
        emit set_views_data(c.data,c.row,c.column);
#ifdef _DEBUG
        qDebug()<<"insert data object name="<<objectName()<<"to cell (row="<<c.row<<" column="<<c.column<<")";
#endif
        self_cells.push_back(c);
    }

    //соединяет сигналы из Environment со слотом объекта (функция базового класса)
    connected_signals();
}
