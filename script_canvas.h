#ifndef SCRIPT_CANVAS_H
#define SCRIPT_CANVAS_H

#include <QObject>
#include <QVector>
#include <QPixmap>
#include <QPainter>
#include <QXmlStreamReader>
#include <QtScript/QScriptEngine>
#include "objects_named_states.h"

//структура и массив предназначены для
//однократного построения рисунков
struct PIXMAP_COLLECTION
{
	QString script_name;
	QString color_name;
	QString color_background;
	QPixmap* pix;
};
typedef QVector<PIXMAP_COLLECTION> ARRAYOFPIXMAP_COLLECTION;
static ARRAYOFPIXMAP_COLLECTION arr_pix_cool;

QColor colorFromString(const QString &name);

//предназначен для рисования одноклеточных объектов из скриптов
class script_canvas : public QObject
{
Q_OBJECT
	Q_PROPERTY(QString curr_color_name WRITE set_curr_color_name READ get_curr_color_name)
	Q_PROPERTY(QPixmap* pix WRITE set_pix READ get_pix)

public:
	explicit script_canvas(const QString &script_name, QObject *parent = nullptr):
            QObject(parent),pix(nullptr),p(nullptr),curr_cell(nullptr),js_script_name(script_name){}

	//создаваемый одноклеточный объект
	typedef QVector<QPixmap*> ARRAYOFPTRPIXMAP;
	struct SCRIPT_CELL		//ячейка отображения
	{
		int row;			//ее координаты в поле отображения
		int column;
		ARRAYOFPTRPIXMAP pixmaps;	//массив картинок, отображаемых в зависимости от состояния
	};
	typedef QVector<SCRIPT_CELL*> ARRAYOFPTRSCRIPTCELL;
	ARRAYOFPTRSCRIPTCELL script_result;

	bool draw_obj(QXmlStreamAttributes attr, OBJECTS_NAMED_STATES* p_ons);

	//возвращает указатель на отрисованный скриптом с именем - script_name
	//одноклеточный объект цветом, соответствующим его отображению в заданном состоянии
	QPixmap* get_draw_pix(const QString &name_script, const QString &color_name, const QString &color_background);

	//отрисовывает текст заданным цветом color_name на фоне color_background
	QPixmap* get_draw_text(const QString &text, const QString &color_name, const QString &color_background,int align=Qt::AlignCenter);

public slots:	//контекст скриптов (функции, которые могут вызываться из скриптов)
	//геттер и сеттер указателя на одноклеточный рисунок
	QPixmap* get_pix(){return pix;}
	void set_pix(QPixmap* p_pix){pix=p_pix;}

	//создание рисунка произвольного размера
	void create_pix(int width, int height){pix = new QPixmap(QSize(width,height));}

	//создает number фрагмент картинки с отрисованным текстом заданным цветом color_name на фоне color_background
	void cell_draw_text(int number, const QString &color_name, const QString &color_background,int align){
		QString name;
		get_value_by_name_attr("name",name);
		QPixmap* pix_text = get_draw_text(name,color_name,color_background,align);
		int h = pix_text->size().height();
		pix = new QPixmap(pix_text->copy(QRect(number*h,0,h,h)));
	}

	void cell_draw_pix(const QString &script_name, const QString &color_name, const QString &color_background){
		pix = get_draw_pix(script_name,color_name,color_background);
	}

	//возвращает количество ячеек по размеру рисунка
	int get_pix_count_cells(int align){
		int aligned;
		if(align==0) aligned=Qt::AlignCenter;
		else aligned=align;
		QString name;
		get_value_by_name_attr("name",name);
		QPixmap* pix_text = get_draw_text(name,QString("black"),QString("black"),aligned);
		return pix_text->size().width()/pix_text->size().height();
	}

	//создание однослеточного объекта
	void create_cell(){curr_cell = new SCRIPT_CELL;}

	//добавление отрисованной в скрипте картинки в одноклеточный объест
	void add_pix_to_cell(){
		if((curr_cell)&&(pix))
			curr_cell->pixmaps.push_back(pix);
	}

	//добавление отрисованной в скрипте "большой" картинки в массива curr_pixmaps
	void push_back_pix_to_array(){curr_pixmaps.push_back(pix);}

	//добавление из отрисованной в скрипте "большой" картинки
	//из массива curr_pixmaps ее части в одноклеточный объест
	void add_part_pix_to_cell(int index_pix, int x, int y, int width, int height){
		if((curr_cell)&&(pix)&&(index_pix<curr_pixmaps.size())&&(curr_pixmaps[index_pix]))
		{
			QPixmap* tmp_pix = new QPixmap(curr_pixmaps[index_pix]->copy(QRect(x,y,width,height)));
			curr_cell->pixmaps.push_back(tmp_pix);
		}
	}
	//добавление отрисованных клеток в массив с результатами работы функции draw_obj
	void add_cell_to_array(int column, int row){
		if(curr_cell)
		{
			curr_cell->column=column;
			curr_cell->row=row;
			script_result.push_back(curr_cell);
		}
	}

	//графичиские примитивы
	void begin_painter(){p = new QPainter(pix);}
    void draw_line(int x, int y,int to_x, int to_y){p->drawLine(x,y,to_x,to_y);}
	void set_pen(const QString &color_name, int width);
	int rect_x(){return rect.x();}
	int rect_y(){return rect.y();}
	int rect_w(){return rect.width();}
	int rect_h(){return rect.height();}
	QString& get_curr_color_name(){ return curr_color_name;}
	void set_curr_color_name(const QString &new_color){curr_color_name=new_color;}
	QRect& boundingRect(){return rect;}
	void beginPath(){ m_path = QPainterPath();}
	void closePath(){ m_path.closeSubpath();}
	void moveTo(qreal x, qreal y){m_path.moveTo(x,y);}
	void lineTo(qreal x, qreal y){m_path.lineTo(x,y);}
	void addEllipse(qreal x, qreal y, qreal w){m_path.addEllipse(QRectF(x,y,w,w));}
	void drawLine(qreal x, qreal y, qreal to_x, qreal to_y){p->drawLine(x,y,to_x,to_y);}
    void drawEllipse(qreal x, qreal y, qreal w){p->drawEllipse(QRectF(x,y,w,w));}
	void fillPath(){p->fillPath(m_path,m_pen.brush());}
	void fill_rect(const QString &color){rect.setRect(0,0,pix->width(),pix->height()); p->fillRect(rect,colorFromString(color));}

	//значения атрибутов считанных из XML
	int get_int_attr(const QString &attr_name){
		int res;
		if(get_value_by_name_attr(attr_name, res)) return res;
		return -65536;
    }
	QString& get_str_attr(const QString &attr_name){
		if(get_value_by_name_attr(attr_name, value_attributes)) return value_attributes;
		value_attributes=QString("");
		return value_attributes;
    }

	//количество состояний и ссответствующих им цветов для объекта
	int get_count_color_sost(){return arr_objects_color_sost.size();}
	//количество состояний типа, от которого зависит данный объект
	int get_count_depends_count_sost(){return count_depends_count_sost;}
	QString get_color_sost(int index){
		if(index<get_count_color_sost())
			return arr_objects_color_sost[index].color;
		return QString();
	}
	QString get_color_background_sost(int index){
		if(index<get_count_color_sost())
			return arr_objects_color_sost[index].color_background;
		return QString();
	}

	void set_pixmap_collection(){ pixmap_collection=true;}

signals:
	void set_sost(QString name, int sost);

private:
	//быстрый доступ для скриптов (загрузка из файла в память один раз, при первом вызове)
	QMap<QString,QScriptEngine*> buf_engine;

	//проверка результатов работы скрипта
	bool check_result(const QString &script_name);

	//переменные для рисования из скриптов
	QPainterPath m_path;
	QPixmap* pix;
	QPainter* p;
	QRect rect;
	QPen m_pen;

	//текущее значение цвета отрисовки объекта
	QString curr_color_name;

	struct OBJ_COLORS_SOST
	{
		//цвета отрисовки объекта в данном состоянии
		QString color;
		//цвета фона отрисовки объекта в данном состоянии
		QString color_background;
	};
	typedef QVector<OBJ_COLORS_SOST> ARRAYOFOBJCOLORSSOST;
	ARRAYOFOBJCOLORSSOST arr_objects_color_sost;
	int count_depends_count_sost;

	//имена и значения атрибутов из XML, в виде имя=значение, разделенных пробелами
	QString str_attributes;
	//значения атрибутов считанных из XML
	bool get_value_by_name_attr(const QString &attr_name, int& value);
	bool get_value_by_name_attr(const QString &attr_name, QString& value);
	QString value_attributes;

	//создаваемая клетка отображения
	SCRIPT_CELL* curr_cell;
	//создаваемый массив картинок
	ARRAYOFPTRPIXMAP curr_pixmaps;

	//флаг возможности занесения отрисованной в скрипте
	//картинки в коллекцию (устанавливается в скрипте
	//вызовом функции set_pixmap_collection())
	bool pixmap_collection;
    QString js_script_name;
};

#endif // SCRIPT_CANVAS_H
