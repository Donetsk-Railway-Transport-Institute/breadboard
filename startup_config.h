#if !defined ( STARTUP_CONFIG_HEADER)
#define STARTUP_CONFIG_HEADER
#include <QColor>
#include <QTextCodec>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

//  Параметры инициализации приложения.
class startup_config : public QObject
{
	Q_OBJECT

public:
    explicit startup_config(const QString &xml_file_name, QObject *parent = nullptr):
            QObject(parent),SIZE_WINDOW_X(0),SIZE_WINDOW_Y(0),COUNT_ROW(0),
            COUNT_COLUMN(0),MIN_SECTION_SIZE(0),MAX_SECTION_SIZE(0),
            CURRENT_SECTION_SIZE(0),SHOW_GRID(false),b_stop_watch(false),press_time_limit(0){
		xml_read(xml_file_name);
	}

	//Режим запуска программы. Возможны варианты:
	//	work - основной режим, если отсутствует связь по СОМ-порту, то ожидает подключения
	//	test - тестовый режим, в меню появляется пункт тесты, который состоит из файлов
	//	в каталоге, описанном в переменной test_DCPP_viewer.
	QString run_as;

	//размер главного окна приложения
	int SIZE_WINDOW_X;
	int SIZE_WINDOW_Y;

	//количество ячеек (COUNT_ROW*COUNT_COLUMN)
	int COUNT_ROW;
	int COUNT_COLUMN;

	//значения размера ячеек
	int MIN_SECTION_SIZE;
	int MAX_SECTION_SIZE;
	int CURRENT_SECTION_SIZE;

	//"Сетка" на экране
	bool SHOW_GRID;

	//цвет фона главного окна
	QString W_COLOR_BACKGROUND;

	//файл описания объектов отображения
	QString objects_xml_file;
	QString objects_state_xml_file;
	QString objects_view_script;

	//при запуске в основном режиме (work)
    //b_stop_watch==true - секундомер; b_stop_watch==false - часы.
    bool b_stop_watch;
	//при запуске в тестовом режиме (отсутствует соединение по последовательному порту)
	//test_dir - каталог скриптов тестов.
	QString test_dir;
	//при запуске в режиме игры play_name - xml файл описания игр.
	QString play_name;
    //при запуске в режиме эмуляции СОМ порта e_script_name - файл скрипта эмулятора.
	QString e_script_name;
	//Длительность времени удержаня левой кнопки мыши, в течении которого
	//клик воспринимается как команда объекту. После окончания выдержки времени
	//курсор изменяется на Qt::ClosedHandCursor и реализуется перетягивание изображения
    int press_time_limit;
    //Скорость движения поезда (см/сек)
    int train_speed;
private:
    //Чтение xml файлов общей конфигурации и объектов
    void xml_read(const QString &xml_file_name);
};

#endif //STARTUP_CONFIG_HEADER

