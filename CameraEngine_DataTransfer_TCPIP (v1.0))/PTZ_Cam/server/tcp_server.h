#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

class tcp_server
{
private:
    int serverSd;
    int port;
    int newSd;

public:
    tcp_server();
    bool serversocket_setup(int port, int& r_newSd);
    bool send_data(string data);
    string receive(int);
};

#endif // TCP_SERVER_H
