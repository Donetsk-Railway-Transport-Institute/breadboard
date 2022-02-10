#ifndef OBJECTS_NAMED_STATES_H
#define OBJECTS_NAMED_STATES_H

#include <QObject>
#include <QVector>
#include <QXmlStreamReader>
#include "startup_config.h"

//предназначен для хранения состояний объектов, считанных из XML
class OBJECTS_NAMED_STATES : public QObject
{	
	Q_OBJECT

public:
	explicit OBJECTS_NAMED_STATES(QObject *parent = nullptr):QObject(parent){}

private:
	struct OBJ_SOST
	{
		int num;
		QString color;
		QString color_background;
		QString comment;
	};
	typedef QVector<OBJ_SOST> ARRAYOFOBJ_SOST;

	struct NAME_OBJ_SOST
	{
		QString type_obj;
		QString depends_type;
		QString comment;
		ARRAYOFOBJ_SOST obj_sost;
	};
	typedef QVector<NAME_OBJ_SOST> ARRAYOFNAME_OBJ_SOST;

	//массив состояний объекта
	ARRAYOFNAME_OBJ_SOST arr_obj_sost;

	//пустая строка
	QString zero_str;

public:
	//возвращают значения полей объекта по его индексу
	QString& get_type_obj(int index){return arr_obj_sost[index].type_obj;}
	QString& get_depends_type(int index){return arr_obj_sost[index].depends_type;}
	QString& get_comment_type(int index){return arr_obj_sost[index].comment;}
	
	//возвращает индекс в массиве arr_obj_sost, если объект с именем name_type
	//представлен, -1 если нет
	int get_index_for_type(QString name_type);

	//возвращает значение цвета по его номеру num для типа с индексом index
	QString& get_color(int index, int num);

	//возвращает значение цвета фона по его номеру num для типа с индексом index
	QString& get_color_background(int index, int num);

	//возвращает комментарий состояния с номером num для типа с индексом index
	QString& get_sost_comment(int index, int num);

	//возврашает количество состояний для типа с индексом index
	int get_count_sost(int index){return arr_obj_sost[index].obj_sost.size();}

	//добавляет в массив запись для нового типа name_type, если его еще нет
	void set_new_name_type(QString name_type, QXmlStreamAttributes attr);

	//добавляет в массив запись для состояния для типа с индексом index
	void set_sost(int index,QXmlStreamAttributes attr);

	//именяет по всем аттрибутам color_background "all" на цвет фона области отображения
	void prepare_color_background(QString color_background);

	//модификация состояний и отображаемых цветов по зависимостям
	void prepare_color_depends();

	void parse_state_objects(startup_config* config);
};

#endif