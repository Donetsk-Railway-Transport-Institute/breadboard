#include <QtScript/QScriptClassPropertyIterator>
#include <QtScript/QScriptValueIterator>
#include <QtScript/QScriptValue>
#include <QFile>
#include <QDebug>
#include "script_canvas.h"
#include "at_script_canvas.h"

#define qClamp(val, min, max) qMin(qMax(val, min), max)
static QList<qreal> parseNumbersList(QString::const_iterator &itr)
{
	QList<qreal> points;
	QString temp;
	while ((*itr).isSpace())
		++itr;
	while ((*itr).isNumber() ||
		   (*itr) == '-' || (*itr) == '+' || (*itr) == '.') {
		temp = QString();

		if ((*itr) == '-')
			temp += *itr++;
		else if ((*itr) == '+')
			temp += *itr++;
		while ((*itr).isDigit())
			temp += *itr++;
		if ((*itr) == '.')
			temp += *itr++;
		while ((*itr).isDigit())
			temp += *itr++;
		while ((*itr).isSpace())
			++itr;
		if ((*itr) == ',')
			++itr;
		points.append(temp.toDouble());
		//eat spaces
		while ((*itr).isSpace())
			++itr;
	}

	return points;
}

QColor colorFromString(const QString &name)
{
	QString::const_iterator itr = name.constBegin();
	QList<qreal> compo;
	if (name.startsWith("rgba(")) {
		++itr; ++itr; ++itr; ++itr; ++itr;
		compo = parseNumbersList(itr);
		if (compo.size() != 4) return QColor();

		//alpha seems to be always between 0-1
		compo[3] *= 255;
		return QColor((int)compo[0], (int)compo[1],
					  (int)compo[2], (int)compo[3]);
	} else if (name.startsWith("rgb(")) {
		++itr; ++itr; ++itr; ++itr;
		compo = parseNumbersList(itr);
		if (compo.size() != 3) return QColor();
		return QColor((int)qClamp(compo[0], qreal(0), qreal(255)),
					  (int)qClamp(compo[1], qreal(0), qreal(255)),
					  (int)qClamp(compo[2], qreal(0), qreal(255)));
	} else return QColor(name);
}

bool script_canvas::get_value_by_name_attr(const QString &attr_name, int& value)
{
	QString str_val;
	if(!get_value_by_name_attr(attr_name, str_val)) return false;
	value = str_val.toInt();
	return true;
}

bool script_canvas::get_value_by_name_attr(const QString &attr_name, QString& value)
{
	int pos=str_attributes.indexOf(attr_name+"=",0);
	if(pos==-1) return false;
	pos+=attr_name.size();
	int pos_end=str_attributes.indexOf(" ",pos);
	if(pos_end==-1) return false;
	value=str_attributes.mid(pos+1,pos_end-pos-1);
	return true;
}

bool script_canvas::draw_obj(QXmlStreamAttributes attr, OBJECTS_NAMED_STATES* p_ons)
{
	for(int i=0;i<attr.size();i++)
	{
		str_attributes+=attr[i].name().toString()+"=";
		str_attributes+=attr[i].value().toString()+" ";
	}

	QString name_script;
	if(!get_value_by_name_attr("script",name_script))
	    qFatal(QString("error not found attrbute 'script' for object %1").arg(attr.value(QString("name"))).toUtf8());

	QString name_type;
	if(!get_value_by_name_attr("type",name_type))
        qFatal(QString("error not found attrbute 'type' for object %1").arg(attr.value(QString("name"))).toUtf8());

	//индекс типа в массиве его возможных состояний
	int index_type = p_ons->get_index_for_type(name_type);
	if(index_type<0)
        qFatal(QString("error not found type %1 in stucture OBJECTS_NAMED_STATES").arg(name_type).toUtf8());

	for(int index_sost=0;index_sost<p_ons->get_count_sost(index_type);index_sost++)
	{
		OBJ_COLORS_SOST ocs;
		ocs.color=p_ons->get_color(index_type,index_sost);
		ocs.color_background=p_ons->get_color_background(index_type,index_sost);
		arr_objects_color_sost.push_back(ocs);
	}

	//количество состояний у типа, от которого зависит данный объект
	QString name_depends = p_ons->get_depends_type(index_type);
	if(name_depends!="") count_depends_count_sost=p_ons->get_count_sost(p_ons->get_index_for_type(name_depends));
    at_script_canvas::run_script(this,js_script_name,name_script,QString("SC"),QString());
	//если скрипт некорректно отработал, чистим массив
	if(!check_result(name_script)) script_result.clear();
	return true;
}

bool script_canvas::check_result(const QString &script_name)
{
	//проверка результатов работы скрипта
	if(script_result.isEmpty())
	{
		QString msg = "error create result array from script "+script_name;
		qWarning(msg.toUtf8());
		return false;
	}
	for(int i=0;i<script_result.size();i++)
	{
		SCRIPT_CELL* cell = script_result[i];
		if(!cell)
		{
			QString msg = "error create cell num="+QString(i)+" in result array from script "+script_name;
			qWarning(msg.toUtf8());
			return false;
		}
		if(cell->pixmaps.isEmpty()) return false;
		for(int j=0;j<cell->pixmaps.size();j++)
		{
			QPixmap* pix = cell->pixmaps[j];
			if((!pix)||(pix->height()==0)||(pix->width()==0))
			{
				QString msg = "error create pixmap num="+QString(j)+" on cell num="+QString(i)+" in result array from script "+script_name;
				qWarning(msg.toUtf8());
				return false;
			}
		}
	}
	return true;
}

void script_canvas::set_pen(const QString &color_name, int width)
{
	//инициализация пера
	m_pen.setStyle(Qt::SolidLine);
	m_pen.setCapStyle(Qt::RoundCap);
	m_pen.setJoinStyle(Qt::RoundJoin);
	m_pen.setBrush(colorFromString(color_name));
	m_pen.setWidth(width);
	if (!p) return;
	p->setPen(m_pen);
}

QPixmap* script_canvas::get_draw_text(const QString &text, const QString &color_name, const QString &color_background, int align)
{
	QPixmap* tmp_pic = new QPixmap(QSize(50,50));
	auto p = new QPainter(tmp_pic);
	p->setFont(QFont("Arial",50));
	QRect tmp_rect = p->boundingRect(QRect(0,0,0,0), align, text);
	p->end();
	int correct_width=tmp_rect.height()*(tmp_rect.width()/tmp_rect.height()+1);
	QRect text_rect = QRect(0,0,correct_width,tmp_rect.height());
	QPixmap* pic = new QPixmap(QSize(text_rect.width(),text_rect.height()));
	p = new QPainter(pic);
	p->fillRect(text_rect,colorFromString(color_background));
	p->setPen(colorFromString(color_name));
	p->setFont(QFont("Arial",50));
	p->drawText(text_rect, align, text);
	p->end();
	return pic;
}

QPixmap* script_canvas::get_draw_pix(const QString &name_script, const QString &color_name, const QString &color_background)
{
	for(auto ap:arr_pix_cool) //если данный рисунок уже есть в коллекции
		if((ap.script_name==name_script)&&(ap.color_name==color_name)&&
		   (ap.color_background==color_background))	return ap.pix;

	//рисунока в коллекции нет, то создаем его
	curr_color_name = color_name;
	pix = new QPixmap(QSize(50,50));
	p = new QPainter(pix);
	rect.setRect(0,0,50,50);
	p->fillRect(rect,colorFromString(color_background));

	pixmap_collection=false;
    at_script_canvas::run_script(this,js_script_name,name_script,QString("SC"),QString());
	if(pixmap_collection)
	{
		//если в скрипте установлен флаг, то заносим рисунок в коллекцию
		PIXMAP_COLLECTION pix_coll;
		pix_coll.script_name=name_script;
		pix_coll.color_name=color_name;
		pix_coll.color_background=color_background;
		pix_coll.pix=pix;
		arr_pix_cool.push_back(pix_coll);
	}
	return pix;
}
