#include "tcp_server.h"

tcp_server::tcp_server()
{

}

bool tcp_server::serversocket_setup(int port, int& r_newSd)
{
    //setup a server socket and connection tools-------------------------------
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    cout << "Server socket created\n";
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //accept, create a new socket descriptor to
    //handle the new connection with client
    newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        return false;
    }
    r_newSd = newSd;
    cout << "Connected with client!" << endl;
    return true;
}

bool tcp_server::send_data(string data) {
    if( send(newSd , data.c_str() , strlen( data.c_str() ) , 0) < 0) {
            perror("Send failed : ");
            return false;
    }
    return true;
}

string tcp_server::receive(int size=512)  {

    char buffer[size];
    string reply;

    //Receive a reply from the server
    if( recv(newSd , buffer , sizeof(buffer) , 0) < 0) {
        puts("recv failed");
    }

    reply = buffer;
    return reply;
}
