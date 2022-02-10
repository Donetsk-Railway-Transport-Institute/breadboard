#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QObject>
#include <QtGui/QCursor>
#include <QKeyEvent>
#include <QtWidgets/QTextEdit>
#include <QtCore/QTimer>
#include "startup_config.h"

class Environment : public QObject
{
	Q_OBJECT

public:
	explicit Environment(startup_config* config, QObject *parent = nullptr)
            : QObject(parent), press_pos_x(0), press_pos_y(0), mouse_press_left(false),
              mouse_press_right(false), horizontal_value(0),vertical_value(0),
              info_text_obj(nullptr),press_timer(nullptr),msg_on_status_bar(QString("")){
		e_config = config;
		min_section_size = e_config->MIN_SECTION_SIZE;
		max_section_size = e_config->MAX_SECTION_SIZE;
		centralWidget = dynamic_cast<QWidget*>(parent);
        setObjectName(QString("Environment"));
	}

    bool event_environment(QObject *obj, QEvent *e);

public slots:
	void set_sost(const QString &name, int new_sost){
//        qInfo("Environment::set_sost(%s,%d)",name.toUtf8().constData(),new_sost);
		emit change_data(name,new_sost);
	}

    void to_status_bar(const QString &msg){
		msg_on_status_bar = msg;
        emit msg_to_statusbar(msg);
    }
	//вывод на экран информации об объекте по текущей
	// позиции курсора при нажатии правой кнопки мыши
	void msg_info_text_obj(const QString &msg,int pos_x,int pos_y);

	//При нажатии левой кнопки запускается таймер длительностью e_config->press_time_limit (мс).
	//Если таймер не будет удален из при отпускании кнопки (событие MouseButtonRelease),
	//то будет вызван этот слот и курсор изменится на ClosedHandCursor и реализуется
	//возможность "перетаскивания" изображения на экране.
	void left_press_timeout(){
		mouse_press_left=true;
		emit set_cursor(QCursor(Qt::ClosedHandCursor));
	}
	void set_horizontal_value(int value){horizontal_value = value;}
	void set_vertical_value(int value){vertical_value = value;}

signals:
	void horizontal_value_changed(int newValue);
	void vertical_value_changed(int newValue);
	void change_section_size(int sz);
	void set_cursor(QCursor newValue);
	void change_data(const QString &name, int new_sost);
	void tableView_key_press(QKeyEvent *ke);
    void obj_name_to_status_bar(int x,int y);
    void msg_to_statusbar(QString msg,int timeout = 1000);
	void obj_info_to_scr(int x,int y);
    void dlg_control_panel(int x,int y);
    void mouse_press_sost(const QString &signal);

private:
    //посылка объекту сигнала is_your_cell с текущей позицией курсора
    void obj_def_at_cursor_pos(QMouseEvent *me);

	int press_pos_x,press_pos_y;
	bool mouse_press_left;
    bool mouse_press_right;
	int horizontal_value,vertical_value;
	int min_section_size,max_section_size;
	startup_config* e_config;
    QTextEdit *info_text_obj;
    QWidget *centralWidget;
    QTimer* press_timer;
    QString msg_on_status_bar;
};

#endif // ENVIRONMENT_H
