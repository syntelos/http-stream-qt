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

#include "NetworkHTTPStreamResponse.h"

NetworkHTTPStreamResponse::NetworkHTTPStreamResponse()
    : NetworkHTTPStreamIO(), protocol(), status(), message()
{
}
bool NetworkHTTPStreamResponse::isValid(){
    return (protocol.isValid() && status.isValid() && message.isValid() && 0 < QList::size());
}
void NetworkHTTPStreamResponse::clear(){
    protocol.clear();
    status.clear();
    message.clear();
    NetworkHTTPStreamIO::clear();
}
bool NetworkHTTPStreamResponse::isOk(){
    if (isValid()){
        bool ok;
        int sc = status.toInt(&ok);
        return (ok && 200 <= sc && 400 > sc);
    }
    else
        return false;
}
void NetworkHTTPStreamResponse::read(HTTP::Device* io){

    NetworkHTTPStreamResponse::clear();

    if (io->waitForReadyRead()){
        /*
         * Request line
         */
        QByteArray line = io->readLine();
        line = line.trimmed();
        if (0 < line.length()){
            QList<QByteArray> linary = line.split(' ');
            int count = linary.count();
            if (3 <= count){
                protocol.setValue(linary.at(0));
                status.setValue(linary.at(1));
                {
                    QByteArray msgbuf;
                    int cc;
                    for (cc = 2; cc < count; cc++){
                        if (2 < cc)
                            msgbuf += ' ';

                        msgbuf += linary.at(cc);
                    }
                    message.setValue(msgbuf);
                }

                /*
                 * Headers
                 */
                while (true){
                    NetworkHTTPStreamHeader h(io->readLine());
                    if (h.isValid())
                        QList<NetworkHTTPStreamHeader>::append(h);
                    else
                        break;
                }
                /*
                 * Body
                 */
                int body = getContentLength();
                if (0 < body){
                    QByteArray input = io->read(body);
                    QBuffer::setData(input);
                }
            }
        }
    }
}
void NetworkHTTPStreamResponse::write(HTTP::Device* io){
    if (isValid() && io->isOpen()){
        io->write(protocol.toByteArray());
        io->write(HTTP::SP);
        io->write(status.toByteArray());
        io->write(HTTP::SP);
        io->write(message.toByteArray());
        io->write(HTTP::CRLF);
        /*
         * Default header "content-length"
         */
        qint64 len = QBuffer::size();
        if (0 < len){
            setHeader("Content-Length", len);
        }

        const QList<NetworkHTTPStreamHeader>& headers = *this;

        foreach (const NetworkHTTPStreamHeader& h, headers){
            io->write(h.toByteArray());
            io->write(HTTP::CRLF);
        }
        io->write(HTTP::CRLF);

        if (0 < len){
            const QByteArray& body = QBuffer::buffer();
            io->write(body);
        }
    }
}
