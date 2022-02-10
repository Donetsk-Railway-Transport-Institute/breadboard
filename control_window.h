//
// Created by User on 27.01.2018.
//

#ifndef DCPP_VIEWER_CONTROL_WINDOW_H
#define DCPP_VIEWER_CONTROL_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSignalMapper>
#include <vector>
#include <QMap>

class control_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit control_window(const QString &st_name,
                            const QString &xml_name,
                            const QString &ui_name,
                            QWidget *parent = nullptr) :
        QMainWindow(parent,Qt::WindowCloseButtonHint),w(nullptr),signalMapper(new QSignalMapper(this)){
        parse(st_name, xml_name, ui_name);
    }
    //содержит пары code:signal, необходима для быстрого
    //нахождения сигнала по коду, пришедшему по TCP
    QMap<QString,QString> code_command;

signals:
    void clicked(const QString &text);

private:
    void parse(const QString &st_name, const QString &xml_name, const QString &ui_name);
    QWidget *w;
    QSignalMapper *signalMapper;
};


#endif //DCPP_VIEWER_CONTROL_WINDOW_H
