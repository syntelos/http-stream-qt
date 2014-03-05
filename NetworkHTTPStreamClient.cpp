/*
 * ISS Live Qt
 * Copyright (C) 2014, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QDebug>

#include "NetworkHTTPStreamClient.h"

NetworkHTTPStreamClient::NetworkHTTPStreamClient(QObject* p)
    : QTcpSocket(p)
{
}
NetworkHTTPStreamClient::~NetworkHTTPStreamClient()
{
}
bool NetworkHTTPStreamClient::isOpen(){

    return QTcpSocket::isOpen();
}
bool NetworkHTTPStreamClient::waitForReadyRead(){

    return (QTcpSocket::isOpen() && QTcpSocket::waitForReadyRead());
}
QByteArray NetworkHTTPStreamClient::readLine(){

    return QTcpSocket::readLine();
}
QByteArray NetworkHTTPStreamClient::read(qint64 len){

    return QTcpSocket::read(len);
}
QString NetworkHTTPStreamClient::peerName() const {

    return QTcpSocket::peerName();
}
quint16 NetworkHTTPStreamClient::peerPort() const {

    return QTcpSocket::peerPort();
}
void NetworkHTTPStreamClient::write(const QByteArray& buf){

    QTcpSocket::write(buf);
}
void NetworkHTTPStreamClient::write(const char* string){

    QTcpSocket::write(string);
}
NetworkHTTPStreamResponse* NetworkHTTPStreamClient::send(NetworkHTTPStreamRequest& q){
    if (isOpen() && q.isValid()){

        q.write(this);

        NetworkHTTPStreamResponse* p = new NetworkHTTPStreamResponse();

        p->read(this);

        return p;
    }
    else {
        return 0;
    }
}
NetworkHTTPStreamResponse* NetworkHTTPStreamClient::send(NetworkHTTPStreamRequest* q){
    if (isOpen() && 0 != q && q->isValid()){

        qDebug() << "NetworkHTTPStreamClient.send [write]";

        q->write(this);

        qDebug() << "NetworkHTTPStreamClient.send [p]";

        NetworkHTTPStreamResponse* p = new NetworkHTTPStreamResponse();

        // qDebug() << "NetworkHTTPStreamClient.send [read]";

        p->read(this);

        return p;
    }
    else {
        return 0;
    }
}
void NetworkHTTPStreamClient::printSocketError(QAbstractSocket::SocketError error){
    switch(error){
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "NetworkHTTPStreamClient.error [ConnectionRefusedError]";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "NetworkHTTPStreamClient.error [RemoteHostClosedError]";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "NetworkHTTPStreamClient.error [HostNotFoundError]";
        break;
    case QAbstractSocket::SocketAccessError:
        qDebug() << "NetworkHTTPStreamClient.error [SocketAccessError]";
        break;
    case QAbstractSocket::SocketResourceError:
        qDebug() << "NetworkHTTPStreamClient.error [SocketResourceError]";
        break;
    case QAbstractSocket::SocketTimeoutError:
        qDebug() << "NetworkHTTPStreamClient.error [SocketTimeoutError]";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        qDebug() << "NetworkHTTPStreamClient.error [DatagramTooLargeError]";
        break;
    case QAbstractSocket::NetworkError:
        qDebug() << "NetworkHTTPStreamClient.error [NetworkError]";
        break;
    case QAbstractSocket::AddressInUseError:
        qDebug() << "NetworkHTTPStreamClient.error [AddressInUseError]";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        qDebug() << "NetworkHTTPStreamClient.error [SocketAddressNotAvailableError]";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        qDebug() << "NetworkHTTPStreamClient.error [UnsupportedSocketOperationError]";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        qDebug() << "NetworkHTTPStreamClient.error [ProxyAuthenticationRequiredError]";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        qDebug() << "NetworkHTTPStreamClient.error [SslHandshakeFailedError]";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        qDebug() << "NetworkHTTPStreamClient.error [UnfinishedSocketOperationError]";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        qDebug() << "NetworkHTTPStreamClient.error [ProxyConnectionRefusedError]";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        qDebug() << "NetworkHTTPStreamClient.error [ProxyConnectionClosedError]";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        qDebug() << "NetworkHTTPStreamClient.error [ProxyConnectionTimeoutError]";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        qDebug() << "NetworkHTTPStreamClient.error [ProxyNotFoundError]";
        break;
    case QAbstractSocket::ProxyProtocolError:
        qDebug() << "NetworkHTTPStreamClient.error [ProxyProtocolError]";
        break;
    case QAbstractSocket::UnknownSocketError:
        qDebug() << "NetworkHTTPStreamClient.error [UnknownSocketError]";
        break;
    default:
        qDebug() << "NetworkHTTPStreamClient.error [*]";
        break;
    }
}
