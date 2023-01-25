#include <QtCore/QDirIterator>
#include <QtCore/QDir>
#include <QDateTime>
#include <QStyleFactory>
#include "general_window.h"
#include "test_dcpp_viewer.h"
#include "play_breadboard.h"
#include "control_window.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QString sCurrDateTime="["+QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss")+"]";
    QString log_name = QDateTime::currentDateTime().toString("dd.MM.yy")+".log";
    QFile fMessFile(qApp->applicationDirPath() + "/log/"+log_name);
    if(!fMessFile.open(QIODevice::Append | QIODevice::Text)) return;
    QTextStream tsTextStream(&fMessFile);
    tsTextStream.setCodec("UTF-8");
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
        case QtDebugMsg:
#ifdef _DEBUG
            tsTextStream << QString("%1 Debug: %2\n").arg(sCurrDateTime).arg(localMsg.constData());
#endif
            break;
        case QtInfoMsg:
            tsTextStream << QString("%1 Info: %2\n").arg(sCurrDateTime).arg(localMsg.constData());
            break;
        case QtWarningMsg:
            tsTextStream << QString("%1 Warning: %2\n").arg(sCurrDateTime).arg(localMsg.constData());
            break;
        case QtCriticalMsg:
            tsTextStream << QString("%1 Critical: %2\n").arg(sCurrDateTime).arg(localMsg.constData());
            break;
        case QtFatalMsg: {
            tsTextStream << QString("%1 Fatal: %2\n").arg(sCurrDateTime).arg(localMsg.constData());
            tsTextStream.flush();
            fMessFile.flush();
            fMessFile.close();
            exit(-1);
        }
    }
    tsTextStream.flush();
    fMessFile.flush();
    fMessFile.close();
}

void general_window::setupUi()
{
//    QMainWindow *DCPP_viewerClass = this;
    //рендеринг экрана
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setStyle(QStyleFactory::create("Fusion")); // these lines before the next

    if (objectName().isEmpty()) setObjectName(QString::fromUtf8("DCPP_viewerClass"));
    resize(config->SIZE_WINDOW_X, config->SIZE_WINDOW_Y);
	setWindowTitle(QString("breadboard"));
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    tableView = new QTableView(centralWidget);
    tableView->setObjectName(QString::fromUtf8("tableView"));    
    tableView->horizontalHeader()->setVisible(false);
    tableView->horizontalHeader()->setMinimumSectionSize(config->MIN_SECTION_SIZE);
    tableView->horizontalHeader()->setMaximumSectionSize(config->MAX_SECTION_SIZE);
    tableView->verticalHeader()->setVisible(false);
    tableView->verticalHeader()->setMinimumSectionSize(config->MIN_SECTION_SIZE);
    tableView->verticalHeader()->setMaximumSectionSize(config->MAX_SECTION_SIZE);

	delegateImage = new ImageDelegate(tableView,config->COUNT_ROW,config->COUNT_COLUMN);
    delegateImage->setObjectName(QString::fromUtf8("delegateImage"));
	tableView->setItemDelegate(delegateImage);
	tableView->setModel(delegateImage->views);
		
	QPalette p = tableView->palette();
	p.setColor(QPalette::Base, colorFromString(config->W_COLOR_BACKGROUND));
	tableView->setPalette(p);
	tableView->setShowGrid(config->SHOW_GRID);

    setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    ctr_panel = new QMenu("Панель управления");
    menuBar->addMenu(ctr_panel);
    setMenuBar(menuBar);

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    setStatusBar(statusBar);

    QMetaObject::connectSlotsByName(this);
	env = new Environment(config,this);		
	connect(env, SIGNAL(horizontal_value_changed(int)), this, SLOT(set_horizontal_value(int)));
	connect(env, SIGNAL(vertical_value_changed(int)), this, SLOT(set_vertical_value(int)));

    connect(tableView->horizontalScrollBar(),SIGNAL(valueChanged(int)), env, SLOT(set_horizontal_value(int)));
    connect(tableView->verticalScrollBar(),SIGNAL(valueChanged(int)), env, SLOT(set_vertical_value(int)));

	connect(env, SIGNAL(change_section_size(int)), this, SLOT(set_section_size(int)));
	connect(env, SIGNAL(set_cursor(QCursor)), this, SLOT(set_cursor(QCursor)));
	connect(env, SIGNAL(msg_to_statusbar(QString, int)), statusBar, SLOT(showMessage(QString, int)));
    connect(env, SIGNAL(dlg_control_panel(int, int)), this, SLOT(dlg_control_panel(int, int)));
	set_section_size(config->CURRENT_SECTION_SIZE);

    qApp->installEventFilter(this);

    //инициализация класса, предназначенного для хранения состояний объектов, считанных из XML
    objects_named_states->parse_state_objects(config);
	parse_objects();

    cc->set_sb(statusBar);  //для вывода на статус бар сообщений об ошибках связи

    // Соединение с сервером TCP из меню
    QAction *act = ctr_panel->addAction(CONNECT_TCP_HOST,cc,&cyclocom::connect_to_tcp_host);
    cc->set_action_connect_disconnect(act);


    //Режим запуска программы. Возможны варианты:
    //	work - основной режим, если отсутствует связь по СОМ-порту, то ожидает подключения
    //	test - тестовый режим, в меню появляется пункт тесты, который состоит из файлов
    //	       в каталоге, описанном в переменной test_DCPP_viewer.
    //  play - режим игры.
    //  emulate_com_port - режим эмуляции СОМ порта. При записи в порт выполняется скрипт name

    if(config->run_as.contains("work")){
        if (!cc->is_connect_to_com_port())
            qFatal("Exit after error open COM port.");
        ctr_panel->addAction(QString("Reset CTRs"),this,&general_window::reset_all);
        pCheckableCameraAction = ctr_panel->addAction(QString("&Камера"),this,&general_window::show_camera);
        pCheckableCameraAction->setCheckable(true);
        pCheckableCameraAction->setChecked(false);
        //включение режима автодиспетчера
        pAutomaticTrainTrafficController = ctr_panel->addAction(QString("&Автодиспетчер"),
                                                                this,
                                                                &general_window::AutomaticTrainTrafficController);
        pAutomaticTrainTrafficController->setCheckable(true);
        pAutomaticTrainTrafficController->setChecked(false);
    }

    if(config->run_as.contains("emulate_com_port")) {
        cc->set_emulate(config->e_script_name);
        ctr_panel->addAction(QString("Reset CTRs"),this,&general_window::reset_all);        
        pCheckableCameraAction = ctr_panel->addAction(QString("&Камера"),this,&general_window::show_camera);
        pCheckableCameraAction->setCheckable(true);
        pCheckableCameraAction->setChecked(false);
    }

    if(config->run_as.contains("test")) {        
        auto test = new test_DCPP_viewer(this);
        //Копируем список команд управления и их расшифровку
        for(auto m_c:cc->s_command) test->msg_comment.append({m_c.msg,m_c.comment});
        for(auto m_c:cc->s_control) test->msg_comment.append({m_c.msg,m_c.comment});
        reconnect_for_test(test);
        delete cc;
        auto panel = new QMenu("Тесты");
        menuBar->addMenu(panel);
        setMenuBar(menuBar);
        if(!QDir(config->test_dir).exists())
            qFatal("%s not exist.",config->test_dir.toUtf8().constData());
        QDirIterator it(config->test_dir,QDir::Files,QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QAction *action = panel->addAction(it.next());
            connect(action, &QAction::triggered, [test, action](){test->run_script(action->text());});
        }
    }

    if(config->run_as.contains("play")) {
        auto play = new play_breadboard(config, this);
        reconnect_for_test(play);
        delete cc;
        //Инициализация данных путевого развития
        for(rw_stantion* st:stantions){
            //Сигнал для отслеживания манипуляций пользователя с
            //контрольной панелью (ввод команд оператором)
            connect(st->st_mpc, SIGNAL(change_control_panel_sost(const QString &)), play, SLOT(change_control_panel_sost(const QString &)));
            connect(play, SIGNAL(init_poligon()),st, SLOT(first_init()));
            QMap<QString, int>* p_map = st->st_mpc->get_map_len();
            QMapIterator<QString, int> i(*p_map);
            while (i.hasNext()) {
                i.next();
                QString name = QString("%1:%2").arg(st->objectName()).arg(i.key());
                if(i.value()>0) play->insert_len_rail(name,i.value());
            }
            QMap<QString, int*>* p_sost = st->st_mpc->get_map_obj_sost();
            QMapIterator<QString, int*> i_s(*p_sost);
            while (i_s.hasNext()) {
                i_s.next();
                QString name = QString("%1:%2").arg(st->objectName()).arg(i_s.key());
                play->insert_obj_sost(name,i_s.value());
            }
        }
        for(rw_peregon* pr:peregons){
            connect(play, SIGNAL(init_poligon()),pr, SLOT(first_init()));
            QMap<QString, int>* p_map = pr->at->get_map_len();
            QMapIterator<QString, int> i(*p_map);
            while (i.hasNext()) {
                i.next();
                QString name = QString("%1:%2").arg(pr->objectName()).arg(i.key());
                if(i.value()>0) play->insert_len_rail(name,i.value());
            }
            QMap<QString, int*>* p_sost = pr->at->get_map_obj_sost();
            QMapIterator<QString, int*> i_s(*p_sost);
            while (i_s.hasNext()) {
                i_s.next();
                QString name = QString("%1:%2").arg(pr->objectName()).arg(i_s.key());
                play->insert_obj_sost(name,i_s.value());
            }
        }
        if(!play->choice_game())
            qFatal("Exit after choice Cancel for started play mode.");
        stopWatch = new StopWatch(play,config,this);
        connect(env, SIGNAL(change_section_size(int)), stopWatch, SLOT(set_size(int)));
        //для инициализации после создания основного окна
        connect(this, SIGNAL(windowShown()), play, SLOT(init_game()));
        //включение режима автодиспетчера
        pAutomaticTrainTrafficController = ctr_panel->addAction(QString("&Автодиспетчер"),
                                                                this,
                                                                &general_window::AutomaticTrainTrafficController);
        pAutomaticTrainTrafficController->setCheckable(true);
        pAutomaticTrainTrafficController->setChecked(false);
    }

    QAction *action = menuBar->addAction("О программе");
    connect(action, &QAction::triggered, this, &general_window::about_box);

    auto action_exit = ctr_panel->addAction(QString("Выход"),this,&general_window::normal_exit);
    action_exit->setShortcut(QString("Ctrl+Q"));

    //если в каком либо сценарии не установлен секундомер, устанавливаем часы
    if(stopWatch == nullptr) {
        dClock = new DClock(config, this);
        connect(env, SIGNAL(change_section_size(int)), dClock, SLOT(set_size(int)));
    }

} // setupUi

void general_window::reconnect_for_test(QObject *newobject){    
    for(auto st:stantions){
        //Перенаправляем вывод команд из СОМ порта в лог для МПЦ
        disconnect(st->st_mpc, SIGNAL(set_sost_from_at(const QString &)), cc, SLOT(set_sost(const QString &)));
        connect(st->st_mpc, SIGNAL(set_sost_from_at(const QString &)), newobject, SLOT(set_sost_to_board(const QString &)));
        //и состояний вместо СОМ порта из тестовых скриптов
        disconnect(cc, SIGNAL(set_new_sost(const QString &)), st->st_mpc, SLOT(set_sost(const QString &)));
        connect(newobject, SIGNAL(set_new_sost(const QString &)), st->st_mpc, SLOT(set_sost(const QString &)));
        connect(newobject, SIGNAL(set_new_sost(const QString &)), st->st_mpc, SLOT(set_control_panel_sost(const QString &)));
    }
    for(auto peregon:peregons){
        //Перенаправляем вывод команд из СОМ порта в лог для перегона
        disconnect(peregon->at, SIGNAL(set_sost_from_at(const QString &)), cc, SLOT(set_sost(const QString &)));
        connect(peregon->at, SIGNAL(set_sost_from_at(const QString &)), newobject, SLOT(set_sost_to_board(const QString &)));
        //и состояний вместо СОМ порта из тестовых скриптов
        disconnect(cc, SIGNAL(set_new_sost(const QString &)), peregon->at, SLOT(set_sost(const QString &)));
        connect(newobject, SIGNAL(set_new_sost(const QString &)), peregon->at, SLOT(set_sost(const QString &)));
    }
    connect(newobject, SIGNAL(set_new_sost(const QString &)), newobject, SLOT(set_sost_to_board(const QString &)));
}

void general_window::bind_signals_peregon_stantion(const QString &from,const QString &to, bool gen_signal){
    auto p_stantion = findChild<rw_stantion*>(to.split(":")[0]);
    if(!p_stantion) qFatal("Error parce binding section. No find stantion %s",to.split(":")[0].toUtf8().constData());
    auto p_rw_obj = findChild<rw_view_obj*>(from);
    if(!p_rw_obj) qFatal("Error parce binding section. No find rw_view_obj %s",from.toUtf8().constData());
    p_stantion->st_mpc->insert_obj(to,p_rw_obj->ptr_sost(),QString(""),0);
    if(gen_signal){
        auto p_peregon = findChild<rw_peregon*>(from.split(":")[0]);
        auto p_rw_obj_to = findChild<rw_view_obj*>(to);
        p_peregon->at->insert_bind_obj(from,p_rw_obj->ptr_sost(),to,p_rw_obj_to->ptr_sost());
        connect(p_peregon->at, SIGNAL(set_new_bind_sost(const QString &)), p_stantion->st_mpc, SLOT(set_sost(const QString &)));
    }
}

void general_window::bind_signals_stantion_peregon(const QString &from,const QString &to, bool gen_signal){
    auto p_peregon = findChild<rw_peregon*>(to.split(":")[0]);
    if(!p_peregon) qFatal("Error parce binding section. No find peregon %s",to.split(":")[0].toUtf8().constData());
    auto p_rw_obj = findChild<rw_view_obj*>(from);
    if(!p_rw_obj) qFatal("Error parce binding section. No find rw_view_obj %s",from.toUtf8().constData());
    p_peregon->at->insert_obj(to,p_rw_obj->ptr_sost(),QString(""),0);
    if(gen_signal){
        auto p_stantion = findChild<rw_stantion*>(from.split(":")[0]);
        auto p_rw_obj_to = findChild<rw_view_obj*>(to);
        p_peregon->at->insert_bind_obj(from,p_rw_obj->ptr_sost(),to,p_rw_obj_to->ptr_sost());
        connect(p_stantion->st_mpc, SIGNAL(set_new_bind_sost(const QString &)), p_peregon->at, SLOT(set_sost(const QString &)));
    }
}

void general_window::parse_objects(){
    B_S::xml_valid(config->objects_xml_file);
    QFile xml_file(config->objects_xml_file);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s (general_window::parse_objects())",config->objects_xml_file.toUtf8().constData());
    auto xml = new QXmlStreamReader(&xml_file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	while (!xml->atEnd() && !xml->hasError()){
		xml->readNext();
		QString name = xml->name().toString();
		if((xml->isStartElement())&&(name==QString("poligon"))){
            while (!(xml->isEndElement() && name==QString("poligon"))){
                xml->readNext();
                name = xml->name().toString();
                if(xml->isStartElement() && name==QString("peregon")){
                    rw_peregon *peregon = nullptr;
                    QString n_xml;
                    QString n_js;
                    QXmlStreamAttributes attr_p = xml->attributes();
                    while (!(xml->isEndElement() && name==QString("peregon"))) {
                        xml->readNext();
                        name = xml->name().toString();
                        if (xml->isStartElement() && name == QString("xml"))
                            n_xml = xml->attributes().value("name").toString();
                        if (xml->isStartElement() && name == QString("at_script"))
                            n_js = xml->attributes().value("name").toString();
                    }
                    peregon = new rw_peregon(attr_p, n_xml, objects_named_states, config, this);
                    if (!peregon->isValid()) qFatal("Error create peregon %s",
                                                    xml->attributes().value(QString("name"))
                                                    .toString().toUtf8().constData());
                    peregon->at->set_js_file_name(n_js);

                    connect(peregon->at, SIGNAL(set_sost_from_at(const QString &)), cc, SLOT(set_sost(const QString &)));
                    connect(peregon->at, SIGNAL(set_new_sost(const QString &, int)), env, SLOT(set_sost(const QString &, int)));
                    connect(cc, SIGNAL(set_new_sost(const QString &)), peregon->at, SLOT(set_sost(const QString &)));
                    //для инициализации после создания основного окна
                    connect(this, SIGNAL(windowShown()), peregon, SLOT(first_init()));
                    qDebug()<<"push_back peregon "<<peregon->objectName();
                    peregons.push_back(peregon);
                }
                if(xml->isStartElement() && name==QString("stantion")){
                    rw_stantion* stantion = nullptr;
                    QString n_xml;
                    QString n_js;
                    QXmlStreamAttributes attr_s = xml->attributes();
                    control_window *cw = nullptr;
                    QString xml_name;
                    QString ui_name;
                    while (!(xml->isEndElement() && name==QString("stantion"))) {
                        xml->readNext();
                        name = xml->name().toString();
                        if (xml->isStartElement() && name == QString("xml"))
                            n_xml = xml->attributes().value("name").toString();
                        if (xml->isStartElement() && name == QString("at_script"))
                            n_js = xml->attributes().value("name").toString();
                        if(xml->isStartElement() && name==QString("control")) {
                            xml_name = xml->attributes().value("name_xml").toString();
                            ui_name = xml->attributes().value("name_ui").toString();
                        }
                    }
                    stantion = new rw_stantion(attr_s,n_xml,objects_named_states,config,this);
                    if (!stantion->isValid())
                        qFatal("Error parse objects for stantion %s from attributes %s",
                               stantion->objectName().toUtf8().constData(),
                               xml->attributes().value(QString("name"))
                               .toString().toUtf8().constData());
                    stantion->st_mpc->set_js_file_name(n_js);
                    cw = new control_window(stantion->objectName(), xml_name, ui_name,this);
                    ctr_panel->addAction(stantion->objectName(), cw,&control_window::show);
                    stantion->set_control_panel(cw);                    
                    connect(stantion->st_mpc, &at_script_canvas::set_sost_from_at, cc, &cyclocom::set_sost);
                    connect(cc, &cyclocom::set_new_sost, stantion->st_mpc, &at_script_canvas::set_sost);
                    connect(cc, &cyclocom::set_sost_from_tcp, stantion, &rw_stantion::set_sost_from_tcp);
                    connect(stantion->st_mpc, &at_script_canvas::set_new_sost, env, &Environment::set_sost);
                    connect(cw, SIGNAL(clicked(QString)),stantion->st_mpc, SLOT(set_control_panel_sost(QString)));
                    connect(env, &Environment::mouse_press_sost, stantion->st_mpc, &at_script_canvas::set_mouse_press_sost);
                    //для инициализации после создания основного окна
                    connect(this, SIGNAL(windowShown()), stantion, SLOT(first_init()));
                    stantions.push_back(stantion);
                }
                if(xml->isStartElement() && name==QString("binding")) {
                    while (!(xml->isEndElement() && name==QString("binding"))) {
                        xml->readNext();
                        name = xml->name().toString();
                        if(xml->isStartElement() && name==QString("signal_peregon_stantion")){
                            QString from = xml->attributes().value("from").toString();
                            QString to = xml->attributes().value("to").toString();
                            bool gen_signal = xml->attributes().value("gen_signal").toInt()==1;
                            bind_signals_peregon_stantion(from,to,gen_signal);
                        }
                        if(xml->isStartElement() && name==QString("signal_stantion_peregon")){
                            QString from = xml->attributes().value("from").toString();
                            QString to = xml->attributes().value("to").toString();
                            bool gen_signal = xml->attributes().value("gen_signal").toInt()==1;
                            bind_signals_stantion_peregon(from,to,gen_signal);
                        }
                    }
                }
			}
		}
	}
}
