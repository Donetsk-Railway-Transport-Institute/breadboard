#include <QtGui/QMouseEvent>
#include "environment.h"

void Environment::obj_def_at_cursor_pos(QMouseEvent *me){
	int calc_x = me->pos().x()/e_config->CURRENT_SECTION_SIZE+horizontal_value;
	int calc_y = me->pos().y()/e_config->CURRENT_SECTION_SIZE+vertical_value;
	emit obj_name_to_status_bar(calc_x,calc_y);
}

void Environment::msg_info_text_obj(const QString &msg,int pos_x,int pos_y){
    qDebug()<<QString("Environment::msg_info_text_obj(QString msg=%1,int pos_x=%2,int pos_y=%3)").arg(msg).arg(pos_x).arg(pos_y);
    delete info_text_obj;
	info_text_obj = new QTextEdit(centralWidget);
	int x = (pos_x-horizontal_value+1)*e_config->CURRENT_SECTION_SIZE;
	int y = (pos_y-vertical_value+1)*e_config->CURRENT_SECTION_SIZE;
	info_text_obj->setGeometry(x,y,160,120);
	QPalette pt = info_text_obj->palette();
	pt.setColor(QPalette::Base, QColor(255, 240, 220, 170));
	info_text_obj->setPalette(pt);
	info_text_obj->setText(msg);
	info_text_obj->show();
}

bool Environment::event_environment(QObject *obj, QEvent *e)
{	
	if(obj->objectName()=="qt_scrollarea_viewport")
	{
		if (e->type()==QEvent::MouseMove)
		{
			auto me = dynamic_cast<QMouseEvent *>(e);
			obj_def_at_cursor_pos(me);
			if(mouse_press_left)
			{
				int delta_x=me->pos().x()/e_config->CURRENT_SECTION_SIZE-press_pos_x;
				int delta_y=me->pos().y()/e_config->CURRENT_SECTION_SIZE-press_pos_y;
				if(horizontal_value>=delta_x) horizontal_value-=delta_x;
				else horizontal_value=0;
				if(vertical_value>=delta_y) vertical_value-=delta_y;
				else vertical_value=0;
				press_pos_x+=delta_x;
				press_pos_y+=delta_y;
                emit horizontal_value_changed(horizontal_value);
                emit vertical_value_changed(vertical_value);
				emit set_cursor(QCursor(Qt::ClosedHandCursor));
				return true;
			}
		}
		if (e->type()==QEvent::MouseButtonPress)
		{
			auto me = dynamic_cast<QMouseEvent *>(e);
			if(me->button()==Qt::LeftButton)
			{
				press_pos_x=me->pos().x()/e_config->CURRENT_SECTION_SIZE;
				press_pos_y=me->pos().y()/e_config->CURRENT_SECTION_SIZE;
                if(press_timer != nullptr) delete press_timer;
                press_timer = new QTimer(this);
                connect(press_timer, &QTimer::timeout, this, &Environment::left_press_timeout);
                press_timer->start(e_config->press_time_limit);
				return true;
			}
			if(me->button()==Qt::RightButton) 
			{
				obj_def_at_cursor_pos(me);
                int pos_x = me->pos().x()/e_config->CURRENT_SECTION_SIZE+horizontal_value;
                int pos_y = me->pos().y()/e_config->CURRENT_SECTION_SIZE+vertical_value;
				emit obj_info_to_scr(pos_x,pos_y);
				qDebug()<<QString("SEND SIGNAL Environment::obj_info_text_obj(pos_x=%1, pos_y=%2)").arg(pos_x).arg(pos_y);
                emit set_cursor(QCursor(Qt::PointingHandCursor));
                mouse_press_right = true;
				return true;
			}
		}
		if (e->type()==QEvent::MouseButtonRelease)
		{    
			emit set_cursor(QCursor(Qt::ArrowCursor));
            delete press_timer;
            press_timer = nullptr;
            //Если отпускание кнопки быстрее, чем сработал таймер, то генерируем
            //сигнал с командой управления для объекта, над которым находится курсор
            if((!mouse_press_right)&&(!mouse_press_left))
                emit mouse_press_sost(msg_on_status_bar);
            mouse_press_left = mouse_press_right = false;

            if(info_text_obj != nullptr){
            	delete info_text_obj;
				info_text_obj = nullptr;
            }
			return true;
		}		
		if (e->type()==QEvent::Wheel)
		{
			auto we = dynamic_cast<QWheelEvent *>(e);
            e_config->CURRENT_SECTION_SIZE+=we->delta()/120;
			if(e_config->CURRENT_SECTION_SIZE>max_section_size) e_config->CURRENT_SECTION_SIZE = max_section_size;
			if(e_config->CURRENT_SECTION_SIZE<min_section_size) e_config->CURRENT_SECTION_SIZE = min_section_size;
			emit change_section_size(e_config->CURRENT_SECTION_SIZE);
			return true;
		}
	}
	if ((obj->objectName()=="tableView")&&(e->type()==QEvent::KeyRelease))
	{
		auto ke = dynamic_cast<QKeyEvent *>(e);
		//увеличение размера ячеек области отображения, если нажата кнопка "+"
		if ((ke->key()==Qt::Key_Plus)&&(e_config->CURRENT_SECTION_SIZE<max_section_size))
		{
			e_config->CURRENT_SECTION_SIZE+=1;
			emit change_section_size(e_config->CURRENT_SECTION_SIZE);
		}
		//уменьшение размера ячеек области отображения, если нажата кнопка "-"
		if ((ke->key()==Qt::Key_Minus)&&(e_config->CURRENT_SECTION_SIZE>min_section_size))
		{
			e_config->CURRENT_SECTION_SIZE-=1;
			emit change_section_size(e_config->CURRENT_SECTION_SIZE);
		}
		return true;
	}
	return false;
}
