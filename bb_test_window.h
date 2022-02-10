//
// Created by User on 26.07.2018.
//

#ifndef BREADBOARD_BB_TEST_WINDOW_H
#define BREADBOARD_BB_TEST_WINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QTableWidget>
#include <QLabel>
#include "cyclocom.h"

class b_timer : public QTimer
{
    Q_OBJECT
public:
    explicit b_timer(QTableWidgetItem *item, int msec, const QColor &f_color, QObject *parent = nullptr):
            p_item(item),QTimer(parent),fin_color(f_color){
        connect(this, SIGNAL(timeout()), this, SLOT(stop_timer()));
        start(msec);
    }

public slots:
    void stop_timer() {
        p_item->setBackground(QBrush(fin_color));
        emit timeout_item(p_item);
    }

signals:
    void timeout_item(QTableWidgetItem *i);

private:
    QTableWidgetItem *p_item;
    QColor fin_color;
};

class BB_TEST_WINDOW : public QMainWindow
{
    Q_OBJECT

public:
    explicit BB_TEST_WINDOW(QWidget *parent = nullptr);

public slots:
    //Слот соединен с сигналом set_new_sost(const QString &) класс cyclocom
    void set_data(const QString &signal){
//        qInfo(QString("BB_TEST_WINDOW: set_data(%1)").arg(signal).toUtf8());
        for(uint i=0;i<cc->s_cycle.size();++i) {
            QStringList tmp1 = QString("%1").arg(cc->s_cycle[i].msg).split(":");
            QStringList tmp2 = QString("%1").arg(signal).split(":");
            //Если сигнал, вне зависимости от состояния, соответствует одному из подаваемых в цикле
            if((tmp1[0]==tmp2[0])&&(tmp1[1]==tmp2[1])) {
                //Изменяем цвет 0-й ячейки на белый (он был красный после посылки сигнала)
                //Это была индикация посылки новго сигнала циклического опроса
                QTableWidgetItem *item_msg = twc->item(i, 0);
                QStringList l_tmp = QString("%1").arg(cc->s_cycle[i].msg).split(":");
                item_msg->setText(QString("%1:%2").arg(l_tmp[0]).arg(l_tmp[1]));
                item_msg->setBackground(QBrush(Qt::white));
                for (auto sc:cc->s_control)
                    if (signal.contains(sc.msg)) {
                        //и изменяем значение цвета 1 и 2-й ячеек на синий,
                        //запускаем таймеры на длительность, равную cc->time_next_control_object
                        //для изменения цвета Background на белый. Это индикация приема нового сигнала
                        QTableWidgetItem *item_comment = twc->item(i, 1);
                        item_comment->setText(QString(sc.comment));
                        item_comment->setBackground(QBrush(Qt::blue));
                        auto *timer_comment = new b_timer(item_comment, cc->time_next_control_object, Qt::white, this);
                        connect(timer_comment,SIGNAL(timeout_item(QTableWidgetItem * )),this,SLOT(del_timer(QTableWidgetItem * )));
                        item_timer.insert(item_comment, timer_comment);
                        QTableWidgetItem *item_code = twc->item(i, 2);
                        item_code->setText(QString(sc.code.toHex(' ').toUpper()));
                        item_code->setBackground(QBrush(Qt::blue));
                        auto *timer = new b_timer(item_code, cc->time_next_control_object, Qt::white, this);
                        connect(timer,SIGNAL(timeout_item(QTableWidgetItem * )),this,SLOT(del_timer(QTableWidgetItem * )));
                        item_timer.insert(item_code, timer);
                    }
            }
        }
    }
    //Слот соединен с сигналом write_cycle_code(const QString &) класс cyclocom
    void write_cycle_code(const QString &signal){
        for(uint i=0;i<cc->s_cycle.size();++i) {
            QString tmp = cc->s_cycle[i].code.toHex(' ').toUpper();
            if (signal.contains(tmp)) {
                //Изменяем цвет 0-й ячейки на красный, 1 и 2 - вставляем пустую запись.
                //Это индикация посылки новго сигнала циклического опроса.
                QTableWidgetItem *item_code = twc->item(i, 0);
                QStringList l_tmp = QString("%1").arg(cc->s_cycle[i].msg).split(":");
                item_code->setText(QString("%1:%2").arg(l_tmp[0]).arg(l_tmp[1]));
                item_code->setBackground(QBrush(Qt::red));
                QTableWidgetItem *item_comment = twc->item(i, 1);
                item_comment->setText(QString(""));
                QTableWidgetItem *i_code = twc->item(i, 2);
                i_code->setText(QString(""));
            }
        }
    }

    void set_ansver_module(const QString &signal){
        for(uint i=0;i<cc->s_command.size();++i){
            QString tmp = cc->s_command[i].code.toHex(' ').toUpper();
            if(signal.contains(tmp)){
                QTableWidgetItem *item_code = tw->item(i,3);
                item_code->setText(QString("%1").arg(tmp));
                item_code->setBackground(QBrush(Qt::blue));
                auto *timer = new b_timer(item_code,5*cc->time_next_control_object,Qt::white,this);
                connect(timer, SIGNAL(timeout_item(QTableWidgetItem*)), this, SLOT(del_timer(QTableWidgetItem*)));
                item_timer.insert(item_code,timer);
            }
        }
    }

    void time_limit_error(const QString &signal){
        for(uint i=0;i<cc->s_command.size();++i) {
            QString tmp = cc->s_command[i].code.toHex(' ').toUpper();
            if (signal.contains(tmp)) {
                QTableWidgetItem *item_code = tw->item(i, 2);
                item_code->setText(QString("%1").arg(tmp));
                item_code->setBackground(QBrush(Qt::red));
                auto *timer = new b_timer(item_code,10*cc->time_limit_control,Qt::white,this);
                qInfo(QString("BB_TEST_WINDOW: time_limit_error(%1) time=%2").arg(signal).arg(10*cc->time_limit_control).toUtf8());
            }
        }
        for(uint i=0;i<cc->s_cycle.size();++i) {
            QString tmp = cc->s_cycle[i].code.toHex(' ').toUpper();
            if (signal.contains(tmp)) {
                QTableWidgetItem *item_code = twc->item(i, 1);
                QStringList l_tmp = QString("%1").arg(cc->s_cycle[i].msg).split(":");
                item_code->setText(QString("%1:%2").arg(l_tmp[0]).arg(l_tmp[1]));
                item_code->setBackground(QBrush(Qt::red));
                auto *timer = new b_timer(item_code,10*cc->time_limit_control,Qt::white,this);
            }
        }
    }

    void del_timer(QTableWidgetItem *item){
        delete item_timer[item];
        item_timer.remove(item);
    };

    void change_count_cycles(uint c){
        if(c % cc->s_cycle.size() == 0) ++counter;
        l_counter->setText(QString("%1").arg(counter));
    }

signals:
    void clicked(const QString &text);

private:
    cyclocom* cc;
    QSignalMapper *signalMapper;
    QTableWidget* tw;
    QTableWidget* twc;
    uint counter;
    QLabel* l_counter;
    QMap<QTableWidgetItem*,b_timer*> item_timer;
    void bb_window();
};

#endif //BREADBOARD_BB_TEST_WINDOW_H
