/*
 * TcpSocketCompat.h: cross-platform compatibility superclass for sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

// Windows
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#undef TEXT
#include <winsock2.h>
#include <ws2tcpip.h>

// Linux
#else
#define sprintf_s sprintf
typedef int SOCKET;
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR   = -1;
#endif

#include <stdio.h>

class TcpSocketCompat {

    private:

        bool initWinsock(void);

    protected:

        char _host[200];
        char _port[10];

        SOCKET _sock;
        SOCKET _conn;

        struct addrinfo * _addressInfo;

        char _message[200];

        bool _connected;

        TcpSocketCompat(const char * host, const short port);

    public:

        void closeConnection(void);

        bool sendData(void *buf, size_t len);

        bool receiveData(void *buf, size_t len);

        bool isConnected();

        char * getMessage(void);
};