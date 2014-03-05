/*
 * Copyright 2013 John Pritchard, Syntelos.  All rights reserved.
 */
#ifndef _CONSOLE_Network_NetworkDeviceConnectionTCP_H
#define _CONSOLE_Network_NetworkDeviceConnectionTCP_H

#include <QObject>
#include <QList>
#include <QMutex>

#include "SystemDeviceConnection.h"
#include "SystemDeviceIdentifier.h"
#include "SystemDevice.h"
#include "SystemMessage.h"

/*!
 * A system device connection for TM/TC over TCP/IP.
 */
class NetworkDeviceConnectionTCP : public SystemDeviceConnection {
    Q_OBJECT;

 protected:
    /*!
     * Cast parent to required \class SystemDevice
     */
    SystemDevice* getSystemDevice() const;

 public:
    /*!
     * The argument \a parent is a member of \class QObject and \class
     * SystemDevice
     */
    NetworkDeviceConnectionTCP(const SystemDeviceIdentifier&,QObject*);
    /*!
     */
    ~NetworkDeviceConnectionTCP();
    /*!
     */
    virtual void run();

 private:
    Q_DISABLE_COPY(NetworkDeviceConnectionTCP)
};
#endif
