#include <QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <QtWidgets/QSplashScreen>
#include "bb_test_window.h"
//#include "general_window.h"

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


int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    BB_TEST_WINDOW w;
    w.show();
    return a.exec();
}
