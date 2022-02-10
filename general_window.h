 #pragma once

#ifndef UI_DCPP_VIEWER_H
#define UI_DCPP_VIEWER_H

#include <QtWidgets/QLCDNumber>
#include <QtCore/QTime>
#include <QtWidgets/QLabel>
#include "startup_config.h"
#include "environment.h"
#include "rw_stantion.h"
#include "views_obj.h"
#include "cyclocom.h"
#include "before_started.h"
#include "camera.h"
#include "attcontroller.h"

QT_BEGIN_NAMESPACE

//#define _DEBUG
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);


class DigitalClock : public QLCDNumber
{
Q_OBJECT

public:
    explicit DigitalClock(startup_config* config, QWidget *parent = nullptr)
            : QLCDNumber(parent),timer(new QTimer(this)) {
        setSegmentStyle(Flat);
        set_size(config->CURRENT_SECTION_SIZE);
        timer->start(10);
    }

public slots:
    void set_size(int sz){
        resize(4*sz, sz);
        move(5,25);
    }

protected:
    QTimer *timer;
};

class DClock : public DigitalClock
{
Q_OBJECT
public:
    explicit DClock(startup_config* config, QWidget *parent = nullptr)
        : DigitalClock(config, parent){
        setDigitCount(8);
        connect(timer, SIGNAL(timeout()), this, SLOT(show_clock()));
    }
private slots:
    void show_clock(){
        QString text = QTime::currentTime().toString("hh:mm:ss");
        display(text);
    }
};

class StopWatch : public DigitalClock
{
Q_OBJECT
public:
    explicit StopWatch(QObject *n_wid, startup_config *config, QWidget *parent = nullptr)
            : DigitalClock(config, parent), time(QTime(0,0,0)),isStarted(false){
        setDigitCount(9);        
        QTime t(0,0,0);
        stop_time = t.addMSecs(0).toString("mm:ss.zzz");
        connect(timer, SIGNAL(timeout()), this, SLOT(show_stopwatch()));
        connect(this, SIGNAL(sw_stop_time(const QString &)), n_wid, SLOT(sw_stop_time(const QString &)));
        connect(n_wid, SIGNAL(sw_start()), this, SLOT(sw_start()));
        connect(n_wid, SIGNAL(sw_stop()), this, SLOT(sw_stop()));
    }

public slots:
    void sw_start(){
        time.start();
        isStarted = true;
    }
    //restart после sw_stop()
    void sw_restart(){
        time = QTime::fromString(stop_time,"mm:ss.zzz");
        time.start();
        isStarted = true;
    }
    void sw_stop(){
        QTime t(0,0,0);
        stop_time = t.addMSecs(time.elapsed()).toString("mm:ss.zzz");
        time = QTime(0,0,0);
        isStarted = false;
        emit sw_stop_time(stop_time);
    }

signals:
    void sw_stop_time(const QString &);

private slots:
    void show_stopwatch(){
        if(isStarted){
            QTime t(0,0,0);
            QString text = t.addMSecs(time.elapsed()).toString("mm:ss.zzz");
            display(text);
        } else display(stop_time);
    }

private:
    QTime time;
    bool isStarted;
    QString stop_time;
};

class general_window : public QMainWindow
{
	Q_OBJECT

public:
    static int const EXIT_CODE_REBOOT = -4444;
    ATTController *attctr;
    Camera *cam;
    QWidget *centralWidget;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *ctr_panel;
    QStatusBar *statusBar;
	ImageDelegate* delegateImage;
	Environment* env;
	OBJECTS_NAMED_STATES* objects_named_states;
	startup_config* config;
    cyclocom* cc;
    DClock* dClock;
    StopWatch* stopWatch;
    ARRAYOFSTANTION stantions;
	ARRAYOFPEREGON peregons;
	
	//создание главного окна отображения
    explicit general_window(QWidget *parent = nullptr, Qt::WindowFlags flags = nullptr):
            QMainWindow(parent,flags),attctr(nullptr),cam(nullptr),centralWidget(nullptr),tableView(nullptr),
            menuBar(nullptr),ctr_panel(nullptr),statusBar(nullptr),
            delegateImage(nullptr),env(nullptr),objects_named_states(new OBJECTS_NAMED_STATES),
            config(new startup_config(QString("./xml/breadboard.xml"))),
            cc(new cyclocom(QString("./xml/board_objects.xml"),this)),dClock(nullptr),
            stopWatch(nullptr),pCheckableCameraAction(nullptr),board_first_control(false){ setupUi(); }

	//парсинг и создание объектов отображения в главном окне
	void parse_objects();

    //Для генерации сигнала после отображения главного окна
    void show()
    {
        QMainWindow::show();
        QApplication::processEvents();
        emit windowShown();
    }

signals:
    //сигнал после отображения главного окна
    void windowShown();
    //сигнала перед закрытием главного окна
    void windowClose();

public slots:
    void show_camera(){ //вывод на экран окна вебкамеры
        if(pCheckableCameraAction->isChecked()){
            cam = new Camera(QSize(config->SIZE_WINDOW_X,config->SIZE_WINDOW_X));
            QPoint pos = mapToGlobal(QPoint(0,0));
            cam->move(pos.x()+50,pos.y());
            cam->show();
        } else {
            cam->close();
            delete cam;
        }
    }

    void AutomaticTrainTrafficController(){//включение режима автодиспетчера
        if(pAutomaticTrainTrafficController->isChecked()){
            attctr = new ATTController(config, this);
            qInfo("connecting set_control_panel_sost");
            connect(attctr,SIGNAL(send_button(const QString &)),this, SLOT(set_control_panel_sost(const QString &)));
            for(auto st:stantions) {
                connect(st->st_mpc, SIGNAL(set_new_sost(const QString &, int)), attctr, SLOT(a_set_new_sost(const QString &, int)));
                connect(st->st_mpc, SIGNAL(set_sost_from_at(const QString &)), attctr, SLOT(a_set_sost_from_at(const QString &)));
                connect(st->st_mpc, SIGNAL(set_new_bind_sost(const QString &)), attctr, SLOT(a_set_new_bind_sost(const QString &)));
                connect(st->st_mpc, SIGNAL(change_control_panel_sost(const QString &)), attctr, SLOT(a_change_control_panel_sost(const QString &)));
                disconnect(st->control_panel, SIGNAL(clicked(QString)),st->st_mpc, SLOT(set_control_panel_sost(QString)));
                disconnect(env, &Environment::mouse_press_sost, st->st_mpc, &at_script_canvas::set_mouse_press_sost);
                connect(attctr,SIGNAL(send_button(const QString &)),st->st_mpc, SLOT(set_control_panel_sost(const QString &)));
            }
            for(auto peregon:peregons)
            {
                connect(peregon->at, SIGNAL(set_new_sost(const QString &, int)), attctr, SLOT(a_set_new_sost(const QString &, int)));
            }
            attctr->first_init();
        } else {
            delete attctr;
            for(auto st:stantions){
                connect(st->control_panel, SIGNAL(clicked(QString)),st->st_mpc, SLOT(set_control_panel_sost(QString)));
                connect(env, &Environment::mouse_press_sost, st->st_mpc, &at_script_canvas::set_mouse_press_sost);
            }
        }
    }

    //сигнал перезагрузки контроллеров и реинициализации станций и перегонов
    void reset_all(){
        if(cc) cc->reset_controllers();
        QApplication::exit(EXIT_CODE_REBOOT);
    }
    void normal_exit(){ QApplication::exit(0); }

	void set_horizontal_value(int newValue) {tableView->horizontalScrollBar()->setValue(newValue);}
	void set_vertical_value(int newValue) {tableView->verticalScrollBar()->setValue(newValue);}
    void set_cursor(QCursor newValue){setCursor(newValue);}
	void set_section_size(int sz){
		//изменение размера ячеек области отображения
        tableView->verticalHeader()->setDefaultSectionSize(sz);
        tableView->horizontalHeader()->setDefaultSectionSize(sz);
	}
	void set_views_data(one_cell_base* data, int row, int column){
		QModelIndex index = delegateImage->views->index(row,column);
		delegateImage->views->setData(index,QVariant::fromValue(data),Qt::EditRole);
	}

    //Вывод контрольной панели станции по двойному нажатию кнопки мыши
    void dlg_control_panel(int x,int y){
        for(auto st:stantions)
            if(st->get_objects_name_by_xy(x,y)!=QString(""))
                st->show_control_panel();
    }

    void about_box(){
        auto msgBox = new QMessageBox(this);
		msgBox->setFixedSize(320,240);
        msgBox->setWindowTitle("О программе");
        msgBox->setWindowModality(Qt::NonModal);
        msgBox->setInformativeText(B_S::copyright_string());
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
	}

protected:
    //Для генерации сигнала перед закрытием главного окна
    void closeEvent(QCloseEvent *event) override {
        emit windowClose();
        event->accept();
    }

     bool eventFilter(QObject *obj, QEvent *e) final {
		 if((env)&&(env->event_environment(obj, e))) return true;
		 return QMainWindow::eventFilter(obj, e);
	 }

	 void resizeEvent(QResizeEvent *event) final {
		 int w = centralWidget->size().width();
		 int h = centralWidget->size().height();
		 tableView->setGeometry(QRect(0, 0, w, h));         
		 QWidget::resizeEvent(event);
	 }

public:
	//создание главного окна отображения
	void setupUi();

private:
    QAction* pCheckableCameraAction; //камера
    QAction* pAutomaticTrainTrafficController; //автодиспетчер
    void reconnect_for_test(QObject *newobject);
	//Увязка перегонных и станционных сигналов
	void bind_signals_peregon_stantion(const QString &from,const QString &to, bool gen_signal = false);
	void bind_signals_stantion_peregon(const QString &from,const QString &to, bool gen_signal = false);
	bool board_first_control;
};

namespace Ui {
    class DCPP_viewerClass: public general_window {};
} // namespace Ui


QT_END_NAMESPACE

#endif // UI_DCPP_VIEWER_H
