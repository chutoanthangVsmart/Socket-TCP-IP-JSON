#include "tcp_client.h"

tcp_client::tcp_client()
{
    clientSd = -1;
    port = 0;
    address = "";
}

/*
 * Connect to a server on a certain port number
 */
bool tcp_client::conn(string address , int port){
    //create socket if it is not already created
    if(clientSd == -1)
    {
        //setup a client socket and connection tools-------------------------------
        struct hostent* host = gethostbyname(address.c_str());
        sockaddr_in sendSockAddr;
        bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
        sendSockAddr.sin_family = AF_INET;
        sendSockAddr.sin_addr.s_addr =
            inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        sendSockAddr.sin_port = htons(port);
        clientSd = socket(AF_INET, SOCK_STREAM, 0);
        if(clientSd < 0)
        {
            cerr << "Error establishing the server socket" << endl;
            exit(0);
        }
        cout << "Client socket created with ID " << clientSd << "\n";
        //try to connect...
        int status = connect(clientSd,
                             (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
        if(status < 0)
        {
            cout<<"Error connecting to socket!"<<endl; return 0;
        }
        cout << "Connected to the server!" << endl;
        return true;
    }
}


/*
 * Send string data to the conencted host
 */
bool tcp_client::send_data(string data) {
    if( send(clientSd , data.c_str() , strlen( data.c_str() ) , 0) < 0) {
            perror("Send failed : ");
            return false;
    }
    return true;
}

bool tcp_client::send_data(json_object *jobj) {
    char temp_buff[1000];
    //convert and send json arrays.
    if (strcpy(temp_buff, json_object_to_json_string(jobj)) == NULL)
    {
        perror("strcpy");
        return EXIT_FAILURE;
    }
    if (write(clientSd, temp_buff, strlen(temp_buff)) == -1)
    {
        perror("write");
        return EXIT_FAILURE;
    }
    return true;
}

/*
 * Receive data from the connected sever
 */
string tcp_client::receive(int size=512)  {

    char buffer[size];
    string reply;

    //Receive a reply from the server
    if( recv(clientSd , buffer , sizeof(buffer) , 0) < 0) {
        puts("recv failed");
    }

    reply = buffer;
    return reply;
}

