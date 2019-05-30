#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include<iostream>    //cout
#include <sstream>
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent

#include <unistd.h> //write
#include <json-c/json.h>

using namespace std;

class tcp_client
{
private:

    int clientSd;
    std::string address;
    int port;

public:

    tcp_client();
    bool conn(string, int);
    bool send_data(string data);
    bool send_data(json_object *jobj);
    string receive(int);
};

#endif // TCP_CLIENT_H
