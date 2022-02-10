#ifndef RW_VIEW_OBJ_H
#define RW_VIEW_OBJ_H

#include <QObject>
#include <QPainter>
#include <QPixmap>
#include "environment.h"
#include "script_canvas.h"
#include "control_window.h"
#include <QDebug>

//одноклеточный объект
//содержит все возможные варианты отображения объекта 
//в зависимости от установленного состояния
class one_cell_base
{
public:
    one_cell_base() : index(0) {}
	~one_cell_base() = default;

	//отображение клетки в зависимости от состояния объекта
	//ф-я вызывается из ImageDelegate
    void paint_object(QPainter *painter,const QRect rect){
		painter->drawPixmap(rect,pix_array[index]);
	}

	//инициализация объекта
	void push_back_pix(const QPixmap &pix){pix_array.push_back(pix);}
	void set_pix(QPixmap pix, int index){if(pix_array.size()<index) pix_array[index]=pix;}

    QPixmap* get_pix(int index){return &pix_array[index];}

	//возвращает состояние объекта для его отображения
	int get_view_state(){return index;}

	//установка состояния объекта для его отображения 
	bool set_view_state(int new_index_view)
	{
		if ((new_index_view<pix_array.size())&&(new_index_view>=0))
		{
			index=new_index_view;
//			qDebug()<<"one_cell_base func:set_view_state index="<<index;
			return true;
		}
        qWarning()<<QString("one_cell_base func:set_view_state - return false: ")<<
				  QString("new_index_view=%1 >= pix_array.size()=%2").arg(new_index_view).arg(pix_array.size());
		return false;
	}

private:
	//массив одноклеточных "картинок"
    QVector<QPixmap> pix_array;
	//индекс в массиве для отображения необходимой "картинки"
	int index;
};
//макрос необходим для обеспечения совместимости указателя на базовый класс с QVariant
Q_DECLARE_METATYPE(one_cell_base*)

//базовый объект для создания и функционирования ж.д. объектов 
class rw_view_obj : public QObject
{
	Q_OBJECT

public:
    explicit rw_view_obj(const QString &name, QObject *parent = nullptr):
            QObject(parent), sost(0), count_sost_in_depends_type(0), ph_len(0){
        setObjectName(name);
		connect(this, SIGNAL(set_views_data(one_cell_base*, int, int)), parent, SLOT(set_views_data(one_cell_base*,int,int)));
//		qDebug()<<"connected SIGNAL (set_views_data(one_cell_base*, int, int)) "<<objectName()<<" SLOT (set_views_data(one_cell_base*,int,int)) "<<parent->objectName();
	}

	//соединяет сигналы из Environment со слотом объекта 
	void connected_signals();

    //установить имя объекта, от которого зависит данный
	void set_depends_name(const QString &d_name){depends_name=d_name;}

    //занимает ли объект ячейку с координатами x,y
    bool it_my_cell(int x,int y){
        for(auto sc:self_cells)
            if ((sc.column == x) && (sc.row == y))
                return true;
        return false;
    }
    int* ptr_sost(){return &sost;}
    QString r_type(){return type;}
    int get_ph_len(){return ph_len;}

public slots:
	//слот изменения состояния объекта
	void set_sost(const QString &name, int new_sost);

	void set_depends_sost(const QString &name){
		if(depends_name==name) change_sost_depends();
	}

    //Если объект занимает ячейку с координатами x,y
    //то посылаем данные в status_bar
    void obj_name_to_status_bar(int x,int y) {
        if (it_my_cell(x, y))
            emit to_status_bar(objectName());
    }

	//Если объект занимает ячейку с координатами x,y
	//то посылаем данные с информацией об объекте
	// для отображения (по нажатию правой кнопки мыши)
	void obj_info_to_scr(int x,int y);

signals:
	//генерация сигнала для вставки данных в клетку отображения
	void set_views_data(one_cell_base* data, int row, int column);
	void depends_sost(QString name);
    //сигнал с именем объекта для отображения в status_bar
    void to_status_bar(QString msg);
    //сигнал с информацией об объекте для отображения как контекстную помощь
	void msg_info_text_obj(QString msg,int x,int y);

protected:
	void change_sost();
	void change_sost_depends();

	struct CELLS				//ячейка отображения
	{
		int row;				//ее координаты в поле отображения
		int column;		
		one_cell_base* data;	//одноклеточный объект
	};
	typedef QVector<CELLS> ARRAYOFCELLS;

	//каждый наследник имеет одну или несколько ячеек для отображения 
	ARRAYOFCELLS self_cells;

    //состояние объекта
    int sost;

	//переменные заполняются при инициализации объекта (берутся из XML)
	QString type;					//тип объекта
	QString depends_type;			//от какого типа зависит объект
    int count_sost_in_depends_type;	//количество состояний типа от которого зависит объект
	QString depends_name;			//имя объекта, от которого зависит данный объект
	QString comment_type;			//комментарий типа объекта
	QStringList comment_sost;		//список комментариев каждого состояния объекта
    int ph_len;                     //физическая длина участка пути (если объект путь или блок-участок или стрелочная секция)
};

typedef QMap<QString,rw_view_obj*> MAPOFRAILWAYOBJECTS;

//объект типа "Станционный объект"
class rw_object : public rw_view_obj
{
public:
    explicit rw_object(const QString &name, const QString &script_name, QObject *parent = nullptr)
			:rw_view_obj(name, parent),js_script_name(script_name){}
    void init(QXmlStreamAttributes attr, OBJECTS_NAMED_STATES* p_ons);
private:
	QString js_script_name;
};

#endif // RW_VIEW_OBJ_H
