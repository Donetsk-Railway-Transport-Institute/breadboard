#include "objects_named_states.h"
#include "before_started.h"

void OBJECTS_NAMED_STATES::parse_state_objects(startup_config* config)
{
    B_S::xml_valid(config->objects_state_xml_file);
	QFile xml_file(config->objects_state_xml_file);
	if (!xml_file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s (OBJECTS_NAMED_STATES::parse_state_objects())",config->objects_state_xml_file.toUtf8().constData());
	auto xml = new QXmlStreamReader(&xml_file);
	while (!xml->atEnd() && !xml->hasError()){
		xml->readNext();
		QString name = xml->name().toString();
		if((xml->isStartElement())&&(name==QString("objects"))){
			while(!(xml->isEndElement() && name==QString("objects"))){
				xml->readNext();
				name = xml->name().toString();
				set_new_name_type(name,xml->attributes());
				int index_type = get_index_for_type(name);
				if(xml->isStartElement() && index_type>=0){
					while (!(xml->isEndElement() && name==arr_obj_sost[index_type].type_obj)){
						xml->readNext();
						name = xml->name().toString();
						if(xml->isStartElement() && name==QString("sost")) set_sost(index_type,xml->attributes());
					}
				}
			}
		}
	}
	delete xml;
	prepare_color_background(config->W_COLOR_BACKGROUND);
	prepare_color_depends();
}

int OBJECTS_NAMED_STATES::get_index_for_type(QString name_type)
{
	if(name_type.isEmpty()) return -1;
	for(int i=0;i<arr_obj_sost.size();i++)
		if(name_type==arr_obj_sost[i].type_obj) 
			return i;
	return -1;
}

void OBJECTS_NAMED_STATES::set_new_name_type(QString name_type, QXmlStreamAttributes attr)
{
	//если такого типа нет
	if((name_type!=QString(""))&&(get_index_for_type(name_type)<0)){
		NAME_OBJ_SOST nos;
		nos.type_obj=name_type;
		nos.depends_type=attr.value("depends_type").toString();
		nos.comment=attr.value("comment").toString();
		nos.obj_sost.clear();
		arr_obj_sost.push_back(nos);
	}
}

void OBJECTS_NAMED_STATES::set_sost(int index,QXmlStreamAttributes attr)
{
	if(index<arr_obj_sost.size()){
		OBJ_SOST os;
		os.num = attr.value("num").toString().toInt();
		os.color = attr.value("color").toString();
		os.color_background = attr.value("color_background").toString();
		os.comment = attr.value("comment").toString();
		arr_obj_sost[index].obj_sost.push_back(os);		
	}
}

QString& OBJECTS_NAMED_STATES::get_color(int index, int num)
{
	if(index>=0 && index<arr_obj_sost.size())
	    for(auto& as:arr_obj_sost[index].obj_sost)
            if (as.num == num) return as.color;
	return zero_str;
}

QString& OBJECTS_NAMED_STATES::get_color_background(int index, int num)
{
	if(index<arr_obj_sost.size())
        for(auto& as:arr_obj_sost[index].obj_sost)
            if (as.num == num) return as.color_background;
	return zero_str;
}

//возвращает комментарий состояния с номером num для типа с индексом index
QString& OBJECTS_NAMED_STATES::get_sost_comment(int index, int num)
{
	if(index<arr_obj_sost.size())
        for(auto& as:arr_obj_sost[index].obj_sost)
            if (as.num == num) return as.comment;
	return zero_str;
}

//именяет по всем аттрибутам color_background "all" на цвет фона области отображения
void OBJECTS_NAMED_STATES::prepare_color_background(QString color_background)
{
    for(auto& as:arr_obj_sost)
		for(auto& os:as.obj_sost)
			if(os.color_background==QString("all"))
				os.color_background=color_background;
}

//модификация состояний и отображаемых цветов по зависимостям
void OBJECTS_NAMED_STATES::prepare_color_depends()
{
	for(auto& as:arr_obj_sost) {
        if (as.depends_type != "") {
            QString obj_type = as.type_obj;
            QString depends_type = as.depends_type;
            int type_index = get_index_for_type(obj_type);
            int depends_index = get_index_for_type(depends_type);
            ARRAYOFOBJ_SOST tmp_arr_obj_sost;
            for (int t = 0; t < get_count_sost(type_index); t++) {
                for (int d = 0; d < get_count_sost(depends_index); d++) {
                    OBJ_SOST tmp_obj_sost;
                    tmp_obj_sost.color = get_color(depends_index, d);
                    tmp_obj_sost.color_background = get_color_background(depends_index, d);
                    tmp_obj_sost.comment = get_sost_comment(depends_index, d) + " : " + get_sost_comment(type_index, t);
                    tmp_arr_obj_sost.push_back(tmp_obj_sost);
                }
            }
            as.obj_sost.clear();
            for (int k = 0; k < tmp_arr_obj_sost.size(); k++) {
                OBJ_SOST tmp;
                tmp.color = tmp_arr_obj_sost[k].color;
                tmp.color_background = tmp_arr_obj_sost[k].color_background;
                tmp.comment = tmp_arr_obj_sost[k].comment;
                tmp.num = k;
                as.obj_sost.push_back(tmp);
            }
        }
    }
}
