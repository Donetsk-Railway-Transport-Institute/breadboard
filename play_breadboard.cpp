//
// Created by User on 08.09.2018.
//

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
#include <QtWidgets/QScrollArea>
#include "before_started.h"
#include "play_breadboard.h"

//условие сортировки lst_results
static bool by_time(const RESULT_GAMES &r1,const RESULT_GAMES &r2){
    return r1.result < r2.result;
}

//чтение файла с результатами игр (рекорды)
void play_breadboard::save_result_games(const QString &file_name) {
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("results"); // Записываем первый элемент с его именем
    for(int i=0;i<10;++i){
        xmlWriter.writeStartElement("game");
        xmlWriter.writeAttribute("name",lst_results[i].name);
        xmlWriter.writeAttribute("result",lst_results[i].result.toString("mm:ss.zzz"));
        xmlWriter.writeEndElement();        // Закрываем тег
    }
    xmlWriter.writeEndElement(); // Закрываем тег "results"
    xmlWriter.writeEndDocument(); // Завершаем запись в документ
    file.close();   // Закрываем файл
}

//чтение файла с результатами игр (рекорды)
void play_breadboard::load_result_games(const QString &file_name){
    lst_results.clear();
    for(int i=0;i<10;++i)
        lst_results.append({"Вася Пупкин",QTime(23,59,59,999),false});
    if (!QFile::exists(file_name))
        return save_result_games(file_name);
    QFile xml_file(file_name);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal(QString("Failed to open file %1").arg(file_name).toUtf8());
    auto xml = new QXmlStreamReader(&xml_file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    while (!xml->atEnd() && !xml->hasError()){
        xml->readNext();
        QString name = xml->name().toString();
        if (xml->isStartElement()){
            if(name==QString("results")){
                while (!(xml->isEndElement() && name==QString("results"))){
                    xml->readNext();
                    name = xml->name().toString();
                    if(xml->isStartElement() && name==QString("game")){
                        QString n = xml->attributes().value("name").toString();
                        QString r = xml->attributes().value("result").toString();
                        RESULT_GAMES rg = {n,QTime::fromString(r,"mm:ss.zzz"),false};
                        lst_results.append(rg);
                    }
                }
            }
        }
    }
}

void play_breadboard::w_game_ower(){
    emit sw_stop(); //останавливаем секундомер
    trains.clear(); //удаляем все поезда
    auto cw = findChild<QWidget *>("centralWidget");
    auto rec_dlg = new QDialog(cw);
    rec_dlg->resize(343, 131);
    auto buttonBox = new QDialogButtonBox(rec_dlg);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setGeometry(QRect(250, 40, 81, 51));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    auto l_rec1 = new QLabel(rec_dlg);
    l_rec1->setGeometry(QRect(20, 10, 150, 16));
    l_rec1->setText(QString("Ваш результат %1 сек.").arg(stop_time));
    auto l_rec2 = new QLabel(rec_dlg);
    l_rec2->setGeometry(QRect(20, 40, 191, 16));
    l_rec2->setText(QString("Для сохранения в таблице рекордов"));
    auto l_rec3 = new QLabel(rec_dlg);
    l_rec3->setGeometry(QRect(70, 60, 111, 16));
    l_rec3->setText(QString("введите Ваше имя:"));
    auto l_edit = new  QLineEdit(rec_dlg);
    l_edit->setGeometry(QRect(20, 90, 191, 20));
    l_edit->setFocus();
    QObject::connect(buttonBox, SIGNAL(accepted()), rec_dlg, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), rec_dlg, SLOT(reject()));

    //Считываем данные о ранее установленных рекордах
    lst_results.clear();
    load_result_games(curr_game.result_name);
    if(rec_dlg->exec()!=QDialogButtonBox::Cancel) {
        //добавляем рекорд только что сыгранной игре
        RESULT_GAMES this_resut = {l_edit->text(),QTime::fromString(stop_time,"mm:ss.zzz"),true};
        lst_results.append(this_resut);
    }
    qSort(lst_results.begin(), lst_results.end(), by_time);
    //Перезаписываем данные с установленными рекордами
    save_result_games(curr_game.result_name);
    dlg_result_games = new QDialog(cw);
    dlg_result_games->resize(400, 300);
    dlg_result_games->setWindowTitle("Игра окончена");
    auto label = new QLabel(dlg_result_games);
    label->setGeometry(QRect(30, 10, 331, 20));
    label->setText(QString("Затраченное время - %1").arg(stop_time));
    auto pb1 = new QPushButton(dlg_result_games);
    pb1->setGeometry(QRect(20, 250, 111, 23));
    pb1->setText(QString("Еще раз"));
    auto pb2 = new QPushButton(dlg_result_games);
    pb2->setGeometry(QRect(140, 250, 111, 23));
    pb2->setText(QString("Другой сценарий"));
    auto pb3 = new QPushButton(dlg_result_games);
    pb3->setGeometry(QRect(260, 250, 111, 23));
    pb3->setText(QString("Выход из игры"));
    connect(pb1, &QPushButton::pressed,this,&play_breadboard::on_pb_again_pressed);
    connect(pb2, &QPushButton::pressed,this,&play_breadboard::on_pb_other_pressed);
    connect(pb3, &QPushButton::pressed,this,&play_breadboard::on_pb_exit_pressed);

    auto twc = new QTableWidget(dlg_result_games);
    twc->setGeometry(QRect(0, 0, 400, 230));
    twc->setRowCount(10);
    for(int i=0;i<10;++i) twc->setRowHeight(i,20);
    twc->setColumnCount(2);
    twc->setColumnWidth(0,275);
    twc->setColumnWidth(1,100);

    auto item0 = new QTableWidgetItem();
    item0->setText(QString("Имя"));
    twc->setHorizontalHeaderItem(0, item0);
    auto item1 = new QTableWidgetItem();
    item1->setText(QString("Время"));
    twc->setHorizontalHeaderItem(1, item1);
    for(int i=0;i<10;++i){ //выводим 10 лучшх результатов
        twc->setItem(i, 0, new QTableWidgetItem(lst_results[i].name));
        twc->setItem(i, 1, new QTableWidgetItem(lst_results[i].result.toString("mm:ss.zzz")));
        if(lst_results[i].this_result){
            twc->item(i, 0)->setBackground(QBrush(Qt::cyan));
            twc->item(i, 1)->setBackground(QBrush(Qt::cyan));
        }
    }
    dlg_result_games->setFocus();
    dlg_result_games->exec();
}

void play_breadboard::first_help() {
    auto cw = findChild<QWidget *>("centralWidget");
    auto msgBox = new QMessageBox(cw);
    msgBox->setFixedSize(640, 480);
    msgBox->setWindowTitle("Режим игры");
    msgBox->setWindowModality(Qt::NonModal);
    QString message;
    if (!QFile::exists(curr_game.html_name))
        qFatal(QString("File %1 does not exist.").arg(curr_game.html_name).toUtf8());
    QFile inputFile(curr_game.html_name);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd()) message += in.readLine();
       inputFile.close();
    }
    msgBox->setInformativeText(message);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->exec();
    emit sw_start();
}

void play_breadboard::parse_xml(const QString &file_name){
    B_S::xml_valid(file_name);
    QFile File(file_name);
    if (!File.open(QIODevice::ReadOnly))
        qFatal(QString("Failed to open file %1").arg(file_name).toUtf8());
    QXmlStreamReader xml(&File);
    while (!xml.atEnd() && !xml.hasError()){
        xml.readNext();
        QString name = xml.name().toString();
        if (xml.isStartElement()){
            if(name==QString("objects")){
                while (!(xml.isEndElement() && name==QString("objects"))){
                    xml.readNext();
                    name = xml.name().toString();
                    if(xml.isStartElement() && name==QString("all")){
                        init_script = xml.attributes().value("init_script").toString();
                        move_train_script = xml.attributes().value("move_train_script").toString();
                    }
                    if(xml.isStartElement() && name==QString("game")){
                        QString n = xml.attributes().value("name").toString();
                        QString s_n = xml.attributes().value("script_name").toString();
                        QString h_n = xml.attributes().value("html_name").toString();
                        QString r_n = xml.attributes().value("result_name").toString();
                        PLAY_GAME pg = {n,s_n,h_n,r_n};
                        games_name.append(pg);
                    }
                }
            }
        }
    }
}

bool play_breadboard::choice_game(){
    auto cw = findChild<QWidget *>("centralWidget");
    dlg_choice_game = new QDialog(cw);
    int count_games = games_name.size();
    if(count_games>10) count_games=10;
    dlg_choice_game->setWindowTitle("Режим игры");
    dlg_choice_game->setObjectName(QStringLiteral("Dialog"));
    int WIDTH = 380;
    int HEIGHT = 220+25*count_games;
    QDesktopWidget *desktop = QApplication::desktop();
    int x = (desktop->width() - WIDTH) / 2;
    int y = (desktop->height() - HEIGHT) / 2;
    dlg_choice_game->resize(WIDTH, HEIGHT);
    dlg_choice_game->move( x, y );

    auto buttonBox = new QDialogButtonBox(dlg_choice_game);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setGeometry(QRect(20, 170+25*count_games, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    auto label = new QLabel(dlg_choice_game);
    label->setGeometry(QRect(30, 25, 331, 31));
    QFont font;
    font.setFamily(QStringLiteral("Times New Roman"));
    font.setPointSize(14);
    font.setBold(true);
    font.setItalic(true);
    font.setWeight(75);
    font.setKerning(false);
    label->setFont(font);
    label->setText("Система диспетчерского управления");
    auto label_2 = new QLabel(dlg_choice_game);
    label_2->setGeometry(QRect(120, 55, 171, 20));
    label_2->setFont(font);
    label_2->setText("движением поездов");
    auto label_3 = new QLabel(dlg_choice_game);
    label_3->setGeometry(QRect(50, 75, 301, 30));
    label_3->setFont(font);
    label_3->setText(" макета участка железной дороги");
    auto label_4 = new QLabel(dlg_choice_game);
    label_4->setGeometry(QRect(QRect(25, 110, 150, 30)));
    label_4->setText("Выбор сценария игры");

    auto scrollArea = new QScrollArea(dlg_choice_game);
    scrollArea->setGeometry(QRect(15, 140, 348, 10+25*count_games));
    scrollArea->setWidgetResizable(true);

    auto vbox = new QVBoxLayout;
    buttongroup = new QButtonGroup();

    for(int i=0;i<games_name.size();++i){
        auto rb = new QRadioButton(games_name[i].name,dlg_choice_game);
        rb->setChecked(false);
        rb->setGeometry(40,150+30*i,300,20);
        vbox->addWidget(rb);
        buttongroup->addButton(rb,i);
    }
    buttongroup->button(0)->setChecked(true);
    vbox->addStretch(1);
    auto dd = new QWidget(dlg_choice_game);
    dd->setLayout(vbox);
    scrollArea->setWidget(dd);

    QObject::connect(buttonBox, SIGNAL(accepted()), dlg_choice_game, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dlg_choice_game, SLOT(reject()));
    QMetaObject::connectSlotsByName(dlg_choice_game);
    if(dlg_choice_game->exec()==0) return false;
    for(auto pl:games_name)
        if (pl.name.contains(buttongroup->checkedButton()->text())) curr_game = pl;
    delete dlg_choice_game;
    return true;
}

