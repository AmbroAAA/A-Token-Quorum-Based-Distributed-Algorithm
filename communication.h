#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "messageFormat.h"


class communication
{
private:
    void errorAndTerminate(string erroMessage);
public:
    int serverListen(int portNum);
    void receiveMessage(Packet msg);
    void sendMessage(Packet msg);
    int readFromSocket(int sockfd,void* buffer,int size);
    int writeToSocket(int sockfd,void* buffer,int size);

    int connectToServer(char dest_IP_address[15],int dest_port);

};

#endif // COMMUNICATION_H
