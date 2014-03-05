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
#ifndef _CONSOLE_Network_NetworkHTTPStreamIO_H
#define _CONSOLE_Network_NetworkHTTPStreamIO_H

#include <QBuffer>
#include <QIODevice>
#include <QList>

#include "NetworkHTTPStreamHeader.h"

namespace HTTP {
    static const char* SC = ";";
    static const char* EQ = "=";
    static const char* SP = " ";
    static const char* CRLF = "\r\n";
    /*!
     * Argument to NetworkHTTPStreamIO read and write.
     */
    struct Device {

        virtual bool isOpen() = 0;

        virtual bool waitForReadyRead() = 0;

        virtual QByteArray readLine() = 0;

        virtual QByteArray read(qint64) = 0;

        virtual QString peerName() const = 0;

        virtual quint16 peerPort() const = 0;

        virtual void write(const QByteArray&) = 0;

        virtual void write(const char*) = 0;
    };
}

/*!
 * 
 */
struct NetworkHTTPStreamIO : public QList<NetworkHTTPStreamHeader>, public QBuffer {
    NetworkHTTPStreamIO();

    void clear();
    void setHeader(const QVariant& name, const QVariant& value);
    const QVariant& getHeader(const QVariant& name) const;
    void setContentLength(uint len);
    uint getContentLength() const;
    void setContentType(const QVariant& string);
    QString getContentType() const;
    /*!
     * Whether content of this data structure forms a valid HTTP
     * entity
     */
    virtual bool isValid() = 0;
    /*!
     * Read the content of this data structure
     */
    virtual void read(HTTP::Device* io) = 0;
    /*!
     * Write the content of this data structure
     */
    virtual void write(HTTP::Device* io) = 0;
};
#endif
