#if !defined (START_PIX_HEADER)
#define START_PIX_HEADER

#include <QFile>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QMap>
#include <QAbstractMessageHandler>

class QXmlSchemaValidatorMessageHandler : public QAbstractMessageHandler
{
public:
    explicit QXmlSchemaValidatorMessageHandler() :
            QAbstractMessageHandler(nullptr),m_messageType(),
            m_description(),m_sourceLocation(){}

    QString statusMessage() const { return m_description; }
    qint64 line() const { return m_sourceLocation.line(); }
    qint64 column() const { return m_sourceLocation.column(); }

protected:
    virtual void handleMessage(
            QtMsgType type,const QString &description,const QUrl &identifier,
            const QSourceLocation &sourceLocation) final {
        Q_UNUSED(type);
        Q_UNUSED(identifier);
        m_messageType = type;
        m_description = description;
        m_sourceLocation = sourceLocation;
    }

private:
    QtMsgType m_messageType;
    QString m_description;
    QSourceLocation m_sourceLocation;
};

class B_S : public QObject
{
Q_OBJECT

public:
    explicit B_S(QObject *parent = nullptr){ Q_UNUSED(parent); }

    //возвращает стартовый рисунок с надписью, возвращаемую функцией copyright_string()
    static QPixmap get_start_pix();

    //проверяет корректность xml файла
    static void xml_valid(const QString &xml_file_name);

    static QString copyright_string(){
        return QString("<p style='text-align: center;'><strong>Система диспетчерского "
                       "управления движением поездов макета участка железной дороги.</strong></p>"
                       "<p style='text-align: center;'>breadboard v1.1.0</p>"
                       "<p style='text-align: center;'>Copyright &copy; Cheptsov, 2017&ndash;2018. All rights reserved.</p>"
                       "<p style='text-align: center;'>&nbsp;</p>");
    }
};
#endif //START_PIX_HEADER
