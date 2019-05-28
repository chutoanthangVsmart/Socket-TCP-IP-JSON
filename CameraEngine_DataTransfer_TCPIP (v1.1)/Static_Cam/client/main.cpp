#include "tcp_client.h"

int main()
{
   tcp_client *client;
   client = new tcp_client();
   //for the client,we need Ip address and port number
   string serverIp; int port;
   serverIp = "127.0.0.1";
   port = 1111;
   //connect to server
   client->conn(serverIp, port);

   while(true) {
       cout << ">";
       string data;
       getline(cin, data);
       if(data == "exit")
       {
           client->send_data(data);
           break;
       }

       //create Jsonobject
       json_object *jobj;
       /*allocate memory for json_object*/
       jobj = json_object_new_object();
       json_object_object_add(jobj, "u", json_object_new_int(100));
       json_object_object_add(jobj, "v", json_object_new_int(99));
       client->send_data(jobj);

       data=client->receive(255);
       if(data == "exit")
       {
           cout << "Server has quit the session" << endl;
           break;
       }
       cout << "Server: " << data << endl;
   }
   return 0;
}



























