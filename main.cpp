//#include <QtWidgets/QSplashScreen>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>
#include "general_window.h"
#include "before_started.h"

int main(int argc, char *argv[])
{
	qInstallMessageHandler(myMessageOutput);
	int result = -1;
	do {
		QApplication app(argc, argv);
		//set translator for default widget's text (for example: QMessageBox's buttons)
		QTranslator qtTranslator;
		qtTranslator.load("qt_ru", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
		app.installTranslator(&qtTranslator);

		QSplashScreen splash(B_S::get_start_pix());
		splash.show();
		app.processEvents();
		general_window w;
		w.show();
		splash.finish(&w);
		result = app.exec();
		if(result==general_window::EXIT_CODE_REBOOT)
            qInfo("Application rebooted after reset controllers.");
        else
            qInfo("Application exit. Return code = %d.",result);
	}while( result==general_window::EXIT_CODE_REBOOT );
	return result;
}
