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

#include <json-c/json.h>

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

    json_object* get_JsonKeyValue(json_object* rootObj, const char* key)
    {
        json_object* returnObj;
        if (json_object_object_get_ex(rootObj, key, &returnObj));
        {
            return returnObj;
        }
        return  NULL;
    }
};

#endif // TCP_SERVER_H
