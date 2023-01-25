#include <QPixmap>
#include <QString>
#include <QPainter>
#include <QtGui/QStaticText>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QTextCodec>
#include "first_pix.h"
#include "before_started.h"

QPixmap B_S::get_start_pix(){
    auto pix = QPixmap(s_pix);
    QPainter painter(&pix);
    auto st = QStaticText(copyright_string());
    painter.setFont(QFont("Arial", 16));
    painter.setPen(QPen(Qt::black, 1));
    QPoint pos(pix.width()/2-210,pix.height()/2-90);
    painter.drawStaticText(pos,st);
    return pix;
}

void B_S::xml_valid(const QString &xml_file_name){
    if (!QFile::exists(xml_file_name))
        qFatal("File %s does not exist (B_S::xml_valid())",xml_file_name.toUtf8().constData());
//    qInfo("Validation file %s (B_S::xml_valid())",xml_file_name.toUtf8().constData());
    QString xsd_file_name = xml_file_name;
    xsd_file_name.replace(xsd_file_name.size()-3,3,QString("xsd"));
    if (!QFile::exists(xsd_file_name)) return;

    QFile file(xsd_file_name);
    if (!file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s (B_S::xml_valid())",xml_file_name.toUtf8().constData());
    QXmlSchema schema;
    schema.load(&file, QUrl::fromLocalFile(file.fileName()));
    if (!schema.isValid())
        qFatal("Schema for %s file does not valid",xml_file_name.toUtf8().constData());
    QFile xml_file(xml_file_name);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s",xml_file_name.toUtf8().constData());
    QXmlSchemaValidator validator(schema);
    QXmlSchemaValidatorMessageHandler handler;
    validator.setMessageHandler(&handler);
    if (!validator.validate(&xml_file, QUrl::fromLocalFile(xml_file.fileName()))) {
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        QString errorMsg = handler.statusMessage().remove(QRegExp("<[^>]*>"));
        qFatal("File %s is invalid at line: %lld, column: %lld - %s",
               xml_file_name.toUtf8().constData(),
               handler.line(),handler.column(),
               errorMsg.toUtf8().constData());
    }
    xml_file.close();
}
