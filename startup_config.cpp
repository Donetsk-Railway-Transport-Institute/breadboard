#include <QtCore/QUrl>
#include "before_started.h"
#include "startup_config.h"

void startup_config::xml_read(const QString &xml_file_name)
{
    B_S::xml_valid(xml_file_name);
    QFile xml_file(xml_file_name);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal(QString("Failed to open file %1").arg(xml_file_name).toUtf8());
    auto xml = new QXmlStreamReader(&xml_file);
    while (!xml->atEnd() && !xml->hasError()){
		xml->readNext();
		if (xml->isStartElement()){
			QString name = xml->name().toString();
			while (!(xml->isEndElement() && name == QString("general_window"))){
				xml->readNext();
				name = xml->name().toString();
				if (xml->isStartElement() && name==QString("run")){
					if(xml->attributes().value(QString("as")).length()!=0) {
                        run_as = xml->attributes().value(QString("as")).toString();
						if (run_as.contains("work"))
                            if (xml->attributes().value(QString("stop_watch")).toInt() == 1) b_stop_watch = true;
						if (run_as.contains("test"))
							test_dir = xml->attributes().value(QString("dir")).toString();
                        if (run_as.contains("play"))
							play_name = xml->attributes().value(QString("name")).toString();
						if (run_as.contains("emulate_com_port"))
                            e_script_name = xml->attributes().value(QString("name")).toString();
                    }
				}
				if (xml->isStartElement() && name==QString("size")){
					if(xml->attributes().value(QString("width")).length()!=0)
						SIZE_WINDOW_X = xml->attributes().value(QString("width")).toString().toInt();
					if(xml->attributes().value(QString("height")).length()!=0) 
						SIZE_WINDOW_Y = xml->attributes().value(QString("height")).toString().toInt();
				}
				if (xml->isStartElement() && name==QString("count_cells")){
					if(xml->attributes().value(QString("count_row")).length()!=0) 
						COUNT_ROW = xml->attributes().value(QString("count_row")).toString().toInt();
					if(xml->attributes().value(QString("count_column")).length()!=0) 
						COUNT_COLUMN = xml->attributes().value(QString("count_column")).toString().toInt();
				}
				if (xml->isStartElement() && name==QString("section_size")){
					if(xml->attributes().value(QString("min")).length()!=0) 
						MIN_SECTION_SIZE = xml->attributes().value(QString("min")).toString().toInt();
					if(xml->attributes().value(QString("max")).length()!=0) 
						MAX_SECTION_SIZE = xml->attributes().value(QString("max")).toString().toInt();
					if(xml->attributes().value(QString("current")).length()!=0) 
						CURRENT_SECTION_SIZE = xml->attributes().value(QString("current")).toString().toInt();
				}
				if (xml->isStartElement() && name==QString("colors")){
					if(xml->attributes().value(QString("background_color")).length()!=0) 
						W_COLOR_BACKGROUND = xml->attributes().value(QString("background_color")).toString();
				}				
				if (xml->isStartElement() && name==QString("objects_xml_file")){
					if(xml->attributes().value(QString("name")).length()!=0) 
						objects_xml_file = xml->attributes().value(QString("name")).toString();
				}
				if (xml->isStartElement() && name==QString("objects_state_xml_file")){
					if(xml->attributes().value(QString("name")).length()!=0) 
						objects_state_xml_file = xml->attributes().value(QString("name")).toString();
				}
				if (xml->isStartElement() && name==QString("objects_view_script")){
					if(xml->attributes().value(QString("name")).length()!=0)
						objects_view_script = xml->attributes().value(QString("name")).toString();
				}
				if (xml->isStartElement() && name==QString("show_grid")){
					if(xml->attributes().value(QString("show")).length()!=0)
						if(xml->attributes().value(QString("show")).toInt()==0) SHOW_GRID = false;
						else SHOW_GRID = true;
				}
				if (xml->isStartElement() && name==QString("press_time_limit")){
					if(xml->attributes().value(QString("ms")).length()!=0)
                        press_time_limit = xml->attributes().value(QString("ms")).toInt();
				}
				if (xml->isStartElement() && name==QString("train_speed")){
					if(xml->attributes().value(QString("sm_sec")).length()!=0)
						train_speed = xml->attributes().value(QString("sm_sec")).toInt();
				}
			}
		}
	}
	if (xml->hasError())
		qFatal(QString("XML error: %1").arg(xml->errorString()).toUtf8());
}
