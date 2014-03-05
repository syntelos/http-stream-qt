/*
 * Copyright 2013 John Pritchard, Syntelos.  All rights reserved.
 */
#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QTcpSocket>

#include "SystemDeviceIdentifier.h"
#include "NetworkDeviceConnectionTCP.h"

NetworkDeviceConnectionTCP::NetworkDeviceConnectionTCP(const SystemDeviceIdentifier& sid, QObject* parent)
    : SystemDeviceConnection(sid,parent)
{
}
NetworkDeviceConnectionTCP::~NetworkDeviceConnectionTCP(){
}
void NetworkDeviceConnectionTCP::run(){

    QTcpSocket socket;

    const QString& prefix = deviceIdentifier.getPrefix();
    const quint16 suffix = deviceIdentifier.getSuffix();

    socket.connectToHost(prefix,suffix);

    qDebug().nospace() << "NetworkDeviceConnectionTCP connecting to " << prefix.toAscii().data() << ":" << suffix;

    if (socket.waitForConnected()){

        qDebug().nospace() << "NetworkDeviceConnectionTCP connection succeeded ";

        emit connectionSucceeded();

        QByteArray linen;

        while (socket.isValid() && (!this->shutdown_flag)){
            /*
             * Output process
             */
            if (this->sendFlag){

                this->sendMutex.lock();

                SystemMessage* m = this->sendQ.takeFirst();

                QByteArray* output = m->createOutput();

                output->append('\r');
                output->append('\n');

                socket.write(*output);

                socket.flush();

                delete output;

                delete m;

                this->sendFlag = (!this->sendQ.isEmpty());

                this->sendMutex.unlock();
            }
            /*
             * Input process
             *
             * Thread polling rate throttle
             */
            if (socket.waitForReadyRead(200L)){

                while (socket.canReadLine()){
                    linen = socket.readLine();

                    QByteArray linet = linen.trimmed();

                    if ( ! linet.isEmpty()){

                        SystemMessage* msg = new SystemMessage(deviceIdentifier,linet);

                        if ( ! msg->isEmpty()){

                            emit received(msg);
                        }

                        msg->deleteLater();
                    }
                }
            }
        }

        socket.close();

        qDebug() << "NetworkDeviceConnectionTCP connection terminated";

        emit connectionTerminated();
    }
    else {

        qDebug() << "NetworkDeviceConnectionTCP connection failed";

        emit connectionFailed();
    }
}
SystemDevice* NetworkDeviceConnectionTCP::getSystemDevice() const {
    return dynamic_cast<SystemDevice*>(this->parent());
}
