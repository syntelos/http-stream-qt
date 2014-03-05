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

#include "NetworkHTTPStreamIO.h"

NetworkHTTPStreamIO::NetworkHTTPStreamIO()
    : QList(), QBuffer()
{
}
void NetworkHTTPStreamIO::clear(){
    QList::clear();
    QByteArray empty;
    QBuffer::setData(empty);
}
/*!
 */
void NetworkHTTPStreamIO::setHeader(const QVariant& name, const QVariant& value){
    const int count = QList::size();
    int cc;
    for (cc = 0; cc < count; cc++){
        const NetworkHTTPStreamHeader& h = QList<NetworkHTTPStreamHeader>::at(cc);
        if (h == name){
            NetworkHTTPStreamHeader& hs = const_cast<NetworkHTTPStreamHeader&>(h);
            hs.setValue(value);
            return;
        }
    }
    NetworkHTTPStreamHeader h;
    h.setName(name);
    h.setValue(value);
    QList<NetworkHTTPStreamHeader>::append(h);
}
/*!
 */
const QVariant& NetworkHTTPStreamIO::getHeader(const QVariant& name) const {
    const int count = QList::size();
    int cc;
    for (cc = 0; cc < count; cc++){
        const NetworkHTTPStreamHeader& h = QList<NetworkHTTPStreamHeader>::at(cc);
        if (h == name){

            return h.value;
        }
    }
    QVariant nil;
    return nil;
}
void NetworkHTTPStreamIO::setContentLength(uint len){
    setHeader("Content-Length",len);
}
uint NetworkHTTPStreamIO::getContentLength() const {
    const QVariant& contentLength = getHeader("Content-Length");
    if (contentLength.isValid()){
        bool ok;
        int len = contentLength.toInt(&ok);
        if (ok && 0 < len){
            return len;
        }
    }
    return 0;
}
void NetworkHTTPStreamIO::setContentType(const QVariant& string){
    setHeader("Content-Type",string);
}
QString NetworkHTTPStreamIO::getContentType() const {
    const QVariant& contentType = getHeader("Content-Type");
    if (contentType.isValid()){

        return contentType.toString();
    }
    else {
        QString nil;
        return nil;
    }
}
