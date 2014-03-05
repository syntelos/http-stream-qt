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
#ifndef _CONSOLE_Network_NetworkHTTPStreamHeader_H
#define _CONSOLE_Network_NetworkHTTPStreamHeader_H

#include <QByteArray>
#include <QVariant>

/*!
 * 
 */
struct NetworkHTTPStreamHeader {

    QVariant name;
    QVariant value;

    NetworkHTTPStreamHeader()
        : name(), value()
    {
    }
    NetworkHTTPStreamHeader(const NetworkHTTPStreamHeader& copy)
        : name(copy.name), value(copy.value)
    {
    }
    NetworkHTTPStreamHeader(const QByteArray& input){
        int parse = input.indexOf(':');
        if (0 < parse){
            QByteArray n0 = input.mid(0,parse);
            QByteArray n1 = n0.trimmed();
            name.setValue(n1);
            QByteArray v0 = input.mid(parse+1);
            QByteArray v1 = v0.trimmed();
            value.setValue(v1);
        }
    }
    bool isValid() const {
        return (name.isValid() && value.isValid());
    }
    void setName(const QVariant& name){

        QString string = name.toString();
        this->name.setValue(string);
    }
    void setValue(const QVariant& value){

        QString string = value.toString();
        this->value.setValue(string);
    }
    QByteArray toByteArray() const {
        QByteArray re;
        if (isValid()){
            re += name.toByteArray();
            re += ": ";
            re += value.toByteArray();
        }
        return re;
    }
    bool operator==(const QVariant& name) const {
        return (this->name == name);
    }

};
#endif
