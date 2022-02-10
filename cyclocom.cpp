//
// Created by User on 16.02.2018.
//

#include <QTextCodec>
#include <QXmlStreamReader>
#include <QFile>
#include <QDialog>
#include <QPushButton>
#include <QCryptographicHash>

#include "cyclocom.h"
#include "before_started.h"

inline bool operator==(const cyclocom::StrCommand &a,const cyclocom::StrCommand &b){
    return ((a.msg==b.msg)&&(a.code==b.code)&&(a.comment==b.comment));
}

cyclocom::cyclocom(const QString &xml_file_name, QObject *parent):QObject(parent),
        CODE_SIZE(-1),m_serial(new ESerialPort(this)),time_limit_control(0),
        time_next_control_object(0),index_next_control_object(0),
        ansver_com_timer(false),tcp_sok(nullptr),
        menu_connect_disconnect(nullptr),sb(nullptr){
    connect(m_serial, &QSerialPort::readyRead, this, &cyclocom::readData);    
    xml_read(xml_file_name);
    if(filename_or_full!="FULL") logger_xml_read();
    for(auto sc:s_cycle){
        QStringList tmp = sc.msg.split(":");
        QString obj = QString("%1:%2").arg(tmp[0]).arg(tmp[1]);
        data_curr_sost.insert(obj,QString("%1:%2").arg(obj).arg("0"));
    }
    m_serial->openSerialPort(p);
    m_serial->set_time_limit(static_cast<uint>(time_next_control_object));
    //Циклический опрос состояния объектов контроля
    auto *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(next_control_object()));
    timer->start(time_next_control_object);
}

void cyclocom::work_with_errors(const QByteArray &err){
    int pos_error_code = read_buffer.indexOf(err);
    if(pos_error_code==-1) return;
    if (ansver_com_timer) ansver_com_timer = false;
    QString str_err = err.toHex(' ').toUpper();
    QString str_data = read_buffer.toHex(' ').toUpper();
    QString t = QTime::currentTime().toString("hh:mm:ss");
    QString msg = QString("[%1] Error reading data from %2. Read %3 (error code in position %4)").arg(t).arg(p.name).arg(str_data).arg(pos_error_code);
    qWarning("%s",msg.toUtf8().constData());
    if(sb) emit msg_to_statusbar(msg,500);
    while(pos_error_code!=-1){
        read_buffer.remove(pos_error_code,err.size());
        pos_error_code = read_buffer.indexOf(err);
    }
}

/*
Алгоритм ведущего устройства в процессе обмена данными.
1. Формирует запрос и посылает его в линию.
2. Ожидает ответ.
3. Принимает ответ и записывает восемь байт в ОЗУ
4. Считывает 1 байт. Если он не содержит адрес одного из подключенных МПК и равен 0, записанные в ОЗУ данные стираются, и производится повторный запрос.
5. Рассчитывает CRC и сравнивает его с принятым CRC (7 и 8 байт). Если CRC совпал, код считается верным. Если не совпал, производится повторный запрос.
6. Считывает 2 байт. Если он не совпадает со вторым байтом запроса и имеет код 0x8F, то фиксирует ошибку, причина которой указана в 6 байте.
7. Считывает 3,4,5,6 байт и обрабатывает их (данные 3,4,5 байтов всегда равны нулю).
*/
void cyclocom::readData() {
    const QByteArray data = m_serial->read_from();
    read_buffer.append(data);
    if(filename_or_full=="FULL"){
        QString tmp = data.toHex(' ').toUpper();
        qInfo("read: %s",tmp.toUtf8().constData());
    }
    //Проверка на принятие байта ошибки
//    work_with_errors(error_code);
//    work_with_errors(error_connection);
    //Разбор содержимого буффера приема по трехбайтовым посылкам
    while(read_buffer.size()>=CODE_SIZE) {
        QByteArray buffer = read_buffer.left(CODE_SIZE);
        read_buffer.remove(0,CODE_SIZE);        
        //проверим на ошибку
        for (auto s_e:s_errors)
            if(s_e.code == buffer)
                qWarning("%s",s_e.comment.toUtf8().constData());
        if(buffer==curr_code_write) {
            //сбрасываем флаг таймера контроля ответа и отсылаем сигнал кода ответа
            if (ansver_com_timer) ansver_com_timer = false;
            QString tmp = buffer.toHex(' ').toUpper();
            emit ansver_module(tmp);
        } else {
            //Если прочитали код - ранее записанную в СОМ порт команду (в цикле)
            for (auto s_c:s_control) {
                if (s_c.code == buffer) {
                    emit read_cycle_code(s_c.msg);
                    //если эта информация является новой, посылаем сигнал изменения состояния
                    if (new_info(s_c.msg)){
                        emit set_new_sost(s_c.msg);
                        if(log_s_control.contains(s_c))
                            qInfo("Принято: %s (%s)",s_c.comment.toUtf8().constData(),s_c.msg.toUtf8().constData());
                    }
                }
            }
        }
    }
};

bool cyclocom::new_info(const QString &msg){
    QStringList tmp = msg.split(":");
    QString obj = QString("%1:%2").arg(tmp[0]).arg(tmp[1]);
    if(!data_curr_sost.contains(obj)) return false;
    if(data_curr_sost[obj]!=msg){
        data_curr_sost[obj]=msg;
        return true;
    }
    return false;
}

void cyclocom::set_sost_log(QString str_sost){
    for(auto s_c:fin_command)
        if((s_c.msg == str_sost)&&(log_fin_command.contains(s_c)))
            qInfo("Передано: %s (%s)",s_c.comment.toUtf8().constData(),s_c.msg.toUtf8().constData());

    for(auto s_c:s_command)
        if((s_c.msg == str_sost)&&(log_s_command.contains(s_c)))
            qInfo("Передано: %s (%s)",s_c.comment.toUtf8().constData(),s_c.msg.toUtf8().constData());

    for(auto s_c:s_errors)
        if((s_c.msg == str_sost)&&(log_s_errors.contains(s_c)))
            qInfo("Передано: %s (%s)",s_c.comment.toUtf8().constData(),s_c.msg.toUtf8().constData());
}

void cyclocom::set_sost(QString str_sost){
    set_sost_log(str_sost);
    if((tcp_sok)&&(tcp_sok->state()==QAbstractSocket::ConnectedState)) send_to(str_sost);
    for(auto f_c:fin_command) //Если команды на перезагрузку контроллеров
        if(f_c.msg==str_sost)
            if (m_serial->write_to(f_c.code) != f_c.code.size())
                qWarning("cyclocom: error write resets command - %s",f_c.msg.toUtf8().constData());

    if(ansver_com_timer){
        //Если не пришел ответ на предыдущую запись команды - сохраняем
        queue_commands.enqueue(str_sost);
    } else {
        //Ели пришедшая комманда str_sost содержится в списке s_command, то отсылаем
        //в COM порт соответствующий ей код (список в файле board_objects.xml)
        for(auto s_c:s_command){
            if(s_c.msg==str_sost) {
                QString tmp = s_c.code.toHex(' ').toUpper();
//                qInfo("cyclocom: set_sost(%s) ansver_com_timer = %d time_limit_control=%d",tmp.toUtf8().constData(),ansver_com_timer,time_limit_control);
                //Для контроля ответа запускаем таймер
                QTimer::singleShot(time_limit_control, this, SLOT(ansver_timer_control()));
                qint64 res_write = m_serial->write_to(s_c.code);
                if(filename_or_full=="FULL"){
                    QString tmp = s_c.code.toHex(' ').toUpper();
                    qInfo("write: %s",tmp.toUtf8().constData());
                }
                if(res_write!=s_c.code.size())
                    qWarning("cyclocom: error write command m_serial->write_to(%s)",tmp.toUtf8().constData());
                //Сохраняем записанную в СОМ порт последовательность
                curr_code_write = s_c.code;
                ansver_com_timer = true;
            }
        }
    }    
};

//Циклический опрос состояния объектов контроля.
//Вызывается с периодичностью time_next_control_object
//для посылки в сом порт кода следующего объекта контроля
void cyclocom::next_control_object(){
    //Если пришел ответ на предыдущую запись команды (канал свободен)
    if(!ansver_com_timer) {
        //сохраняем переданный сигнал
        cycle_code_write = s_cycle[index_next_control_object].code;
        QString tmp = cycle_code_write.toHex(' ').toUpper();
        emit write_cycle_code(tmp);
        qint64 res_write = m_serial->write_to(cycle_code_write);
        if(filename_or_full=="FULL"){
            QString tmp = cycle_code_write.toHex(' ').toUpper();
            qInfo("write: %s",tmp.toUtf8().constData());
        }
        if(res_write!=cycle_code_write.size())
            qWarning("cyclocom: error write cycle code m_serial->write_to(%s)",tmp.toUtf8().constData());
        if(index_next_control_object == s_cycle.size()-1) index_next_control_object = 0;
        else index_next_control_object++;
//           QString tmp = s_cycle[index_next_control_object].code.toHex(' ').toUpper();
//            qInfo(QString("cyclocom: Write to %1 command = %2 code = %3").arg(p.name).arg(s_cycle[index_next_control_object].msg).arg(tmp).toUtf8());
    }
}

//Контроль ответа модуля по порту
void cyclocom::ansver_timer_control(){
    //Если к моменту срабатывания таймера ответа от модуля еще небыло,
    //то это превышение времени ожидания ответа(p.time_limit_control)
    if(ansver_com_timer) {
        ansver_com_timer=false;
        QString tmp = curr_code_write.toHex(' ').toUpper();
        qWarning("Time limit error. No answer module after write code %s. Reinit %s.",
                 tmp.toUtf8().constData(),get_port_name().toUtf8().constData());
        emit time_limit_error(tmp);
//        closeSerialPort();
//        m_serial->openSerialPort(p);
        //Повторная запись текущего кода после переинициализации порта
//        set_sost(curr_code_write);
    }
    //выполняем накопленные (ранее сохраненные в функции set_sost) команды
    if(!queue_commands.isEmpty()) set_sost(queue_commands.dequeue());
}

void cyclocom::connect_to_tcp_host(){
    //создаем сокет
    tcp_sok = new QTcpSocket(this);
    //подключаем сигналы
    connect(tcp_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(tcp_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
    tcp_sok->connectToHost(host, port);
    if(menu_connect_disconnect->text()==CONNECT_TCP_HOST){
        if(tcp_sok->waitForConnected()){
            menu_connect_disconnect->setText(DISCONNECT_TCP_HOST);
            qInfo("SOCKET: connect to host %s port=%lld",host.toUtf8().constData(), static_cast<long long>(port));
        }
    } else {
        tcp_sok->disconnectFromHost();
        menu_connect_disconnect->setText(CONNECT_TCP_HOST);
        qInfo("SOCKET: disconnect (host %s port=%lld)",host.toUtf8().constData(), static_cast<long long>(port));
    }
}

void cyclocom::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qWarning("SOCKET error: The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qWarning("SOCKET error: The connection was refused by the peer");
        break;
    default:
        qWarning("SOCKET error: The following error occurred: %s",tcp_sok->errorString().toUtf8().constData());
    }
}

void cyclocom::onSokReadyRead() {   
    const int SIZE_BUFFER_READ = 256;
    char buffer[SIZE_BUFFER_READ];
    tcp_sok->read(buffer,SIZE_BUFFER_READ);
    QByteArray data = QByteArray::fromHex(QString(buffer).toUtf8());
    if(TCP_CODE_SIZE==data.size()){
        emit set_sost_from_tcp(data.toHex().toUpper());
    } else qWarning("SOCKET error: size read data %d, but must be %d",data.size(),TCP_CODE_SIZE);
}

void cyclocom::send_to(const QString &data){
    QByteArray code;
    for(auto s_c:fin_command)
        if(s_c.msg == data)
            code = s_c.code;
    for(auto s_c:s_command)
        if(s_c.msg == data)
            code = s_c.code;
    for(auto s_c:s_errors)
        if(s_c.msg == data)
            code = s_c.code;
    for(auto s_c:s_control)
        if(s_c.msg == data)
            code = s_c.code;
    QString tmp = code.toHex(' ').toUpper()+"\n";
    tcp_sok->write(QByteArray::fromStdString(tmp.toStdString()));
    tcp_sok->waitForBytesWritten(3000);
    tcp_sok->flush();
}

void cyclocom::xml_read(const QString &xml_name)
{
    B_S::xml_valid(xml_name);
    QFile xml_file(xml_name);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s",xml_name.toUtf8().constData());
    auto xml = new QXmlStreamReader(&xml_file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    while (!xml->atEnd() && !xml->hasError()){
        xml->readNext();
        QString name = xml->name().toString();
        if((xml->isStartElement())&&(name==QString("board_objects")))
        {
            while (!(xml->isEndElement() && name==QString("board_objects"))){
                xml->readNext();
                name = xml->name().toString();
                if(xml->isStartElement() && name==QString("init_serial")){
                    p.name = xml->attributes().value("name").toString();
                    p.stringBaudRate = xml->attributes().value("baudRate").toUtf8();
                    p.baudRate=QSerialPort::UnknownBaud;
                    if(p.stringBaudRate==QString("9600")) p.baudRate = QSerialPort::Baud9600;
                    else if(p.stringBaudRate==QString("19200")) p.baudRate = QSerialPort::Baud19200;
                    else if(p.stringBaudRate==QString("38400")) p.baudRate = QSerialPort::Baud38400;
                    else if(p.stringBaudRate==QString("115200")) p.baudRate = QSerialPort::Baud115200;
                    else qWarning("ERROR read baudRate from xml");
                    p.stringDataBits = xml->attributes().value("dataBits").toUtf8();
                    p.dataBits = QSerialPort::UnknownDataBits;
                    if(p.stringDataBits==QString("5")) p.dataBits = QSerialPort::Data5;
                    else if(p.stringDataBits==QString("6")) p.dataBits = QSerialPort::Data6;
                    else if(p.stringDataBits==QString("7")) p.dataBits = QSerialPort::Data7;
                    else if(p.stringDataBits==QString("8")) p.dataBits = QSerialPort::Data8;
                    else qWarning("ERROR read dataBits from xml");
                    p.stringParity = xml->attributes().value("parity").toUtf8();
                    p.parity = QSerialPort::UnknownParity;
                    if(p.stringParity==QString("No")) p.parity = QSerialPort::NoParity;
                    else if(p.stringParity==QString("Even")) p.parity = QSerialPort::EvenParity;
                    else if(p.stringParity==QString("Odd")) p.parity = QSerialPort::OddParity;
                    else if(p.stringParity==QString("Space")) p.parity = QSerialPort::SpaceParity;
                    else if(p.stringParity==QString("Mark")) p.parity = QSerialPort::MarkParity;
                    else qWarning("ERROR read parity from xml");
                    p.stringStopBits = xml->attributes().value("stopBits").toUtf8();
                    p.stopBits = QSerialPort::UnknownStopBits;
                    if(p.stringStopBits==QString("One")) p.stopBits = QSerialPort::OneStop;
                    else if(p.stringStopBits==QString("OneAndHalf")) p.stopBits = QSerialPort::OneAndHalfStop;
                    else if(p.stringStopBits==QString("Two")) p.stopBits = QSerialPort::TwoStop;
                    else qWarning("ERROR read stopBits from xml");
                    p.stringFlowControl = xml->attributes().value("flowControl").toUtf8();
                    p.flowControl = QSerialPort::UnknownFlowControl;
                    if(p.stringFlowControl==QString("NoFlow")) p.flowControl = QSerialPort::NoFlowControl;
                    else if(p.stringFlowControl==QString("Hardware")) p.flowControl = QSerialPort::HardwareControl;
                    else if(p.stringFlowControl==QString("Software")) p.flowControl = QSerialPort::SoftwareControl;
                    else qWarning("ERROR read flowControl from xml");
                    qDebug()<<QString(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                              .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                              .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
                }
                if(xml->isStartElement() && name==QString("time_limits")){
                    time_limit_control = xml->attributes().value("time_limit_control").toUtf8().toInt();
//                    qDebug()<<"xml file "<<xml_name<<" time_limit_control = "<<time_limit_control;
                    time_next_control_object = xml->attributes().value("time_next_control_object").toUtf8().toInt();
//                    qDebug()<<"xml file "<<xml_name<<" time_next_control_object = "<<time_next_control_object;
                }
                if(xml->isStartElement() && name==QString("logging"))
                    filename_or_full = xml->attributes().value("filename_or_full").toUtf8();

                if(xml->isStartElement() && name==QString("socket")){
                    host = xml->attributes().value("host").toUtf8();
                    port = static_cast<quint16>(xml->attributes().value("port").toInt());
                }

                if(xml->isStartElement()&&name.contains(QString("fin_command"))) insert_data(fin_command,xml->attributes());
                if(xml->isStartElement()&&name.contains(QString("obj_command"))) insert_data(s_command,xml->attributes());
                if(xml->isStartElement()&&name.contains(QString("cycle"))) insert_data(s_cycle,xml->attributes());
                if(xml->isStartElement()&&name.contains(QString("obj_control"))) insert_data(s_control,xml->attributes());
                if(xml->isStartElement()&&name.contains(QString("error_code"))) insert_data(s_errors,xml->attributes());
            }
        }
    }
}

void cyclocom::logger_xml_read(){
    B_S::xml_valid(filename_or_full);
    QFile xml_file(filename_or_full);
    if (!xml_file.open(QIODevice::ReadOnly))
        qFatal("Failed to open file %s",filename_or_full.toUtf8().constData());
    auto xml = new QXmlStreamReader(&xml_file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    while (!xml->atEnd() && !xml->hasError()){
        xml->readNext();
        QString name = xml->name().toString();
        if((xml->isStartElement())&&(name==QString("logging"))) {
            while (!(xml->isEndElement() && name==QString("logging"))){
                xml->readNext();
                name = xml->name().toString();
                if(xml->isStartElement()&&name.contains(QString("fin_command"))) insert_data(log_fin_command,xml->attributes());
                if(xml->isStartElement()&&name.contains(QString("obj_command"))) insert_data(log_s_command,xml->attributes());
                if(xml->isStartElement()&&name.contains(QString("obj_control"))) insert_data(log_s_control,xml->attributes());
                if(xml->isStartElement()&&name.contains(QString("error_code"))) insert_data(log_s_errors,xml->attributes());
            }
        }
    }
}


void cyclocom::insert_data(QVector <StrCommand> &to,QXmlStreamAttributes attr){
    StrCommand sc = {attr.value("msg").toString(),
                     QByteArray::fromHex(attr.value("code").toUtf8()),
                     attr.value("comment").toString()};
    if(CODE_SIZE==-1) CODE_SIZE=sc.code.size();
    else if(CODE_SIZE!=sc.code.size())
        qWarning("ERROR commands code from xml. "
                 "Size can be %d but loaded size = %d",
                 CODE_SIZE,sc.code.size());
    to.append(sc);
//    qDebug()<<"xml file msg = "<<sc.msg<<" code = "<<QString(sc.code.toHex(' ').toUpper())<<" comment = "<<sc.comment;
}
