#ifndef TEST_DCPP_VIEWER_H
#define TEST_DCPP_VIEWER_H

#include <QObject>
#include <QThread>
#include "at_script_canvas.h"

class Worker : public QObject {

    Q_OBJECT

public slots:
    void doWork(const QStringList &commands) {
        for(const QString &comm : commands){
            if(comm.indexOf(QString("sleep"))!=-1){
                unsigned long msecs = comm.split("=")[1].toUInt();
                QThread::msleep(msecs);
            } else emit(resultReady(comm));
        }
        emit(end_of_script());
    }

signals:
    void resultReady(const QString &result);
    void end_of_script();
};

class test_DCPP_viewer : public QObject {

    Q_OBJECT
    QThread workerThread;

public:
    explicit test_DCPP_viewer(QObject *parent) : QObject(parent){
        auto *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &test_DCPP_viewer::operate, worker, &Worker::doWork);
        connect(worker, &Worker::resultReady, this, &test_DCPP_viewer::set_new_sost);
        connect(worker, &Worker::end_of_script, this, &test_DCPP_viewer::end_of_script);
        workerThread.start();
	};

    ~test_DCPP_viewer() override {
        workerThread.quit();
        workerThread.wait();
    }

public slots:
    void run_script(const QString &file_name) {
        at_script_canvas::run_script(this, file_name, QString("typing_group"), QString("T"), QString(""));
        emit(operate(commands));
    };
	void add(const QString &command){ commands.append(command);}
    void end_of_script(){ commands.clear();}
    //Запись команд напольным устройствам
    void set_sost_to_board(const QString &msg){
        qInfo(QString("set_sost_to_log(%1)").arg(msg).toUtf8());
    }

signals:
	//Сигнал для перерисовки объекта в новом состоянии
	//Сигнал соединен со слотом set_sost(QString) в MPC
    void set_new_sost(const QString &name);
    void operate(const QStringList &);

private:
    QStringList commands;
    QString menu;
    QString dir;
};

#endif // TEST_DCPP_VIEWER_H
