//
// Created by User on 27.01.2018.
//

#include "control_window.h"
#include "before_started.h"
#include <QtUiTools/QtUiTools>

void control_window::parse(const QString &st_name, const QString &xml_name, const QString &ui_name)
{
    //Считываем ui файл, содержащий построенную в Qt Designer форму
    QUiLoader loader;
    QFile file(ui_name);
    if(!file.open(QFile::ReadOnly))
        qFatal("Отсутствует файл %s",ui_name.toUtf8().constData());
    w = loader.load(&file, this);
    file.close();

    setCentralWidget(w);
    resize(w->size());
    setWindowTitle(st_name);

    //Парсим xml файл, содержащий описание органов управления панелей
    //(например кнопки) с командами, которые необходимо сгенерировать
    //по факту подачи команды оператором.
    B_S::xml_valid(xml_name);
    QFile xml_file(xml_name);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s",xml_name.toUtf8().constData());
    auto xml = new QXmlStreamReader(&xml_file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    while (!xml->atEnd() && !xml->hasError())
    {
        xml->readNext();
        QString name = xml->name().toString();
        if (xml->isStartElement())
        {
            if(name==QString("widgets"))
            {
                while (!(xml->isEndElement() && name==QString("widgets")))
                {
                    xml->readNext();
                    name = xml->name().toString();
                    qDebug()<<"xml file "<<xml_name<<" tag name = "<<name;
                    if(xml->isStartElement() && name==QString("button"))
                    {
                        QString l_name = xml->attributes().value("name").toString();
                        int x = xml->attributes().value("x").toInt();
                        int y = xml->attributes().value("y").toInt();
                        int w = xml->attributes().value("w").toInt();
                        int h = xml->attributes().value("h").toInt();
                        QString signal = xml->attributes().value("signal").toString();
                        QString code = xml->attributes().value("code").toString();
                        QPushButton *m_button = new QPushButton(l_name, this);
                        m_button->setGeometry(QRect(QPoint(x, y),QSize(w, h)));
                        connect(m_button, SIGNAL(clicked()), signalMapper, SLOT(map()));
                        signalMapper->setMapping(m_button, signal);
                        code_command.insert(code,signal);
                    }
                }
                connect(signalMapper, SIGNAL(mapped(const QString &)), this, SIGNAL(clicked(const QString &)));
            }
        }
    }
}

