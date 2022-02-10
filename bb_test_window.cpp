//
// Created by User on 26.07.2018.
//

#include <QtUiTools>
#include "bb_test_window.h"
#include "startup_config.h"

BB_TEST_WINDOW::BB_TEST_WINDOW(QWidget *parent)
        :QMainWindow(parent),cc(new cyclocom(QString("./xml/board_objects.xml"))),
         signalMapper(new QSignalMapper(this)),tw(nullptr),twc(nullptr),counter(0){
    startup_config* config = new startup_config(QString("./xml/breadboard.xml"));
    bb_window();
    tw = findChild<QTableWidget*>("twCommand");
    if(!tw) qFatal(QString("BB_TEST_WINDOW: error finding twCommand in file bb_test_window.ui").toUtf8());
    l_counter = findChild<QLabel*>("l_counter");
    if(!l_counter) qFatal(QString("BB_TEST_WINDOW: error finding l_counter in file bb_test_window.ui").toUtf8());
    tw->setRowCount(cc->s_command.size()); // указываем количество строк
    tw->setColumnCount(4);
    tw->setColumnWidth(0,160);
    tw->setColumnWidth(1,500);
    tw->setColumnWidth(2,50);
    tw->setColumnWidth(3,50);
    uint i;
    for(i=0;i<cc->s_command.size();++i) {
        QString name_command = QString("%1").arg(cc->s_command[i].msg);
        auto m_button = new QPushButton(name_command, tw);
        connect(m_button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_button, name_command);
        tw->setCellWidget(i, 0, m_button);
    }
    for(i=0;i<cc->s_command.size();++i)
        tw->setItem(i,1, new QTableWidgetItem(QString("%1").arg(cc->s_command[i].comment)));
    for(i=0;i<cc->s_command.size();++i)
        tw->setItem(i,2, new QTableWidgetItem(QString("%1").arg(QString(cc->s_command[i].code.toHex(' ').toUpper()))));
    for(i=0;i<cc->s_command.size();++i)
        tw->setItem(i,3, new QTableWidgetItem(QString("")));

    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SIGNAL(clicked(const QString &)));
    if (!cc->is_connect_to_com_port()) cc->set_emulate(config->e_script_name);
    connect(this, SIGNAL(clicked(const QString &)), cc, SLOT(set_sost(const QString &)));
    connect(cc, SIGNAL(read_cycle_code(const QString &)), this, SLOT(set_data(const QString &)));
    connect(cc, SIGNAL(write_cycle_code(const QString &)), this, SLOT(write_cycle_code(const QString &)));
    connect(cc, SIGNAL(ansver_module(const QString &)), this, SLOT(set_ansver_module(const QString &)));
    connect(cc, SIGNAL(time_limit_error(const QString &)), this, SLOT(time_limit_error(const QString &)));
    connect(cc->m_serial, SIGNAL(change_count_cycles(uint)), this, SLOT(change_count_cycles(uint)));

    twc = findChild<QTableWidget*>("twControl");
    if(!twc) qFatal(QString("BB_TEST_WINDOW: error finding twControl in file bb_test_window.ui").toUtf8());
    twc->setRowCount(cc->s_cycle.size());
    twc->setColumnCount(3);
    twc->setColumnWidth(0,160);
    twc->setColumnWidth(1,500);
    twc->setColumnWidth(2,100);
    for(i=0;i<cc->s_cycle.size();++i){
        QStringList tmp = QString("%1").arg(cc->s_cycle[i].msg).split(":");
        twc->setItem(i,0, new QTableWidgetItem(QString("%1:%2").arg(tmp[0]).arg(tmp[1])));
        twc->setItem(i,1, new QTableWidgetItem(QString("")));
        twc->setItem(i,2, new QTableWidgetItem(QString("")));
    }
}

void BB_TEST_WINDOW::bb_window(){
    setObjectName(QStringLiteral("Dialog"));
    resize(831, 605);
    auto twCommand = new QTableWidget(this);
    if (twCommand->columnCount() < 4)
        twCommand->setColumnCount(4);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    twCommand->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    twCommand->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    twCommand->setHorizontalHeaderItem(2, __qtablewidgetitem2);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    twCommand->setHorizontalHeaderItem(3, __qtablewidgetitem3);
    twCommand->setObjectName(QStringLiteral("twCommand"));
    twCommand->setGeometry(QRect(10, 10, 811, 361));
    auto label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(10, 380, 501, 16));
    auto twControl = new QTableWidget(this);
    if (twControl->columnCount() < 3) twControl->setColumnCount(3);
    QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
    twControl->setHorizontalHeaderItem(0, __qtablewidgetitem4);
    QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
    twControl->setHorizontalHeaderItem(1, __qtablewidgetitem5);
    QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
    twControl->setHorizontalHeaderItem(2, __qtablewidgetitem6);
    twControl->setObjectName(QStringLiteral("twControl"));
    twControl->setGeometry(QRect(10, 400, 811, 192));
    auto label_2 = new QLabel(this);
    label_2->setObjectName(QStringLiteral("label_2"));
    label_2->setGeometry(QRect(620, 379, 71, 21));
    auto l_counter = new QLabel(this);
    l_counter->setObjectName(QStringLiteral("l_counter"));
    l_counter->setGeometry(QRect(710, 380, 111, 21));
    setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
    QTableWidgetItem *___qtablewidgetitem = twCommand->horizontalHeaderItem(0);
    ___qtablewidgetitem->setText(QApplication::translate("Dialog", "\320\262\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
    QTableWidgetItem *___qtablewidgetitem1 = twCommand->horizontalHeaderItem(1);
    ___qtablewidgetitem1->setText(QApplication::translate("Dialog", "\320\272\320\276\320\274\320\260\320\275\320\264\320\260", nullptr));
    QTableWidgetItem *___qtablewidgetitem2 = twCommand->horizontalHeaderItem(2);
    ___qtablewidgetitem2->setText(QApplication::translate("Dialog", "\320\272\320\276\320\264", nullptr));
    QTableWidgetItem *___qtablewidgetitem3 = twCommand->horizontalHeaderItem(3);
    ___qtablewidgetitem3->setText(QApplication::translate("Dialog", "\320\276\321\202\320\262\320\265\321\202", nullptr));
    label->setText(QApplication::translate("Dialog", "\320\232\320\276\320\275\321\202\321\200\320\276\320\273\321\214 \321\201\320\262\320\276\320\261\320\276\320\264\320\275\320\276\321\201\321\202\320\270/\320\267\320\260\320\275\321\217\321\202\320\276\321\201\321\202\320\270 \321\203\321\207\320\260\321\201\321\202\320\272\320\276\320\262 \320\277\321\203\321\202\320\270 \320\262 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\265 \321\206\320\270\320\272\320\273\320\270\321\207\320\265\321\201\320\272\320\276\320\263\320\276 \320\276\320\277\321\200\320\276\321\201\320\260 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\321\217", nullptr));
    QTableWidgetItem *___qtablewidgetitem4 = twControl->horizontalHeaderItem(0);
    ___qtablewidgetitem4->setText(QApplication::translate("Dialog", "\320\236\320\261\321\212\320\265\320\272\321\202", nullptr));
    QTableWidgetItem *___qtablewidgetitem5 = twControl->horizontalHeaderItem(1);
    ___qtablewidgetitem5->setText(QApplication::translate("Dialog", "\320\237\321\200\320\270\320\275\321\217\321\202\320\276\320\265 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
    QTableWidgetItem *___qtablewidgetitem6 = twControl->horizontalHeaderItem(2);
    ___qtablewidgetitem6->setText(QApplication::translate("Dialog", "\320\272\320\276\320\264", nullptr));
    label_2->setText(QApplication::translate("Dialog", "\320\235\320\276\320\274\320\265\321\200 \321\206\320\270\320\272\320\273\320\260", nullptr));
    l_counter->setText(QString());
    QMetaObject::connectSlotsByName(this);
}

