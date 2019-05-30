#include "tcp_server.h"

int main()
{
    int newSd;
    tcp_server *server;
    server = new tcp_server();
    server->serversocket_setup(1111, newSd);

    string respond = "Server received\n";

    while(1)
    {
        string data;
        //create Jsonobject
        json_object *jobj;

        //receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        data = server->receive(512);
        if(data == "exit")
        {
            cout << "Client has quit the session" << endl;
            break;
        }
        else
        {
            cout << "Client: " << data << endl;
            server->send_data(respond);
        }


        /* //Input data and send
        {
        cout << ">";
        getline(cin, data);
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            server->send_data(data);
            break;
        }
        //send the message to client
        server->send_data(data);
        }
        */


    }
    return 0;
}
