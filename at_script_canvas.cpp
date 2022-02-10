#include "at_script_canvas.h"

//быстрый доступ для скриптов (загрузка из файла в память один раз, при первом вызове)
static QMap<QString,QScriptEngine*> buf_engine;

void at_script_canvas::run_script(QObject *object,
                                  const QString &js_name,
                                  const QString &function_name,
                                  const QString &property_name,
                                  const QString &obj_name){
//    qInfo(QString("at_script_canvas::run_script %1 %2 %3 %4").arg(js_name).arg(function_name).arg(property_name).arg(obj_name).toUtf8());
    QScriptEngine *engine;
    if(!buf_engine.contains(js_name)) {
        QFile file(js_name);
        if (!file.open(QIODevice::ReadOnly))
            qFatal("Error open script %s",js_name.toUtf8().constData());
        QTextStream stream(&file);
        engine = new QScriptEngine();
        engine->evaluate(stream.readAll());
        file.close();
        buf_engine.insert(js_name,engine);
    } else engine = buf_engine[js_name];
    QScriptValue at = engine->newQObject(object);
    engine->globalObject().setProperty(property_name, at);
    QScriptValue scriptFun = engine->globalObject().property(function_name);
    scriptFun.call(QScriptValue(), QScriptValueList() << obj_name);
}

void at_script_canvas::start_blink(const QString &obj,
                                   const QString &com,
                                   unsigned long msecs,
                                   const QString &s_b){
    QMap<QString, worker_blink_signals*> *bl;
    if(s_b.contains(QString("scr"))) bl = &blink_obj;
    else if(s_b.contains(QString("board"))) bl = &blink_board;
    else {
        qWarning("Error parametrs in call start_blinc s_b = %s."
                 " Can be scr or board.",s_b.toUtf8().constData());
        return;
    }
    if(!bl->contains(obj)) {
        auto workerThread = new worker_blink_signals(obj, com, msecs, this);
        if(s_b.contains(QString("scr")))
            connect(workerThread, &worker_blink_signals::resultReady, this, &at_script_canvas::set_sost);
        if(s_b.contains(QString("board")))
            connect(workerThread, &worker_blink_signals::resultReady, this, &at_script_canvas::set_sost_to_at);
        connect(workerThread, &worker_blink_signals::finished, workerThread, &QObject::deleteLater);
        bl->insert(QString("%1").arg(obj), workerThread);
        workerThread->start();
    } else qWarning("Object %s allready blinking.",obj.toUtf8().constData());
}

void at_script_canvas::stop_blink(const QString &obj,
                                  const QString &end_sost,
                                  const QString &s_b){
    QMap<QString, worker_blink_signals*> *bl;
    if(s_b.contains(QString("scr"))) bl = &blink_obj;
    else if(s_b.contains(QString("board"))) bl = &blink_board;
    else {
        qWarning("Error parametrs in call stop_blinc s_b = %s."
                 " Can be scr or board.",s_b.toUtf8().constData());
        return;
    }
    if(bl->contains(obj)){
        worker_blink_signals *workerThread = bl->value(QString("%1").arg(obj));
        workerThread->stop_blink(end_sost);
        bl->remove(QString("%1").arg(obj));
    }
}

int at_script_canvas::is_blink(const QString &obj, const QString &s_b){
    QMap<QString, worker_blink_signals*> *bl;
    if(s_b.contains(QString("scr"))) bl = &blink_obj;
    else if(s_b.contains(QString("board"))) bl = &blink_board;
    else {
        qWarning("Error parametrs in call is_blink s_b = %s."
                 " Can be scr or board.",s_b.toUtf8().constData());
        return -2;
    }
    if(bl->contains(QString("%1").arg(obj))) return 0;
    else return -1;
}

