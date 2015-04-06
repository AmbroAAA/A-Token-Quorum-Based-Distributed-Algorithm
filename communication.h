#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "messageFormat.h"


class communication
{
private:
    void errorAndTerminate(string erroMessage);
public:
    int serverListen(int portNum,messageQueue<Packet*>* queue);
    void receiveMessage(Packet msg);
    void sendMessage(Packet msg);
    int readFromSocket(int sockfd,Packet *msg,int size);
    int writeToSocket(int sockfd,Packet *msg,int size);

    int connectToServer(char dest_IP_address[15],int dest_port);
    void msgHandling(messageQueue<Packet*>* queue);
};

#endif // COMMUNICATION_H
