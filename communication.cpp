#include "communication.h"

int communication::serverListen(int portNum,messageQueue<Packet*> *queue){
    int servSock;
    int clntSock;
    Packet msg;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned short echoServPort;
    socklen_t clntLen;

    echoServPort = portNum;

    if((servSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
        errorAndTerminate("Socket() failed\n");

    memset(&echoServAddr,0,sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    if(bind(servSock,(struct sockaddr*)&echoServAddr,sizeof(echoServAddr)) < 0)
        errorAndTerminate("bind() failed\n");

    if(listen(servSock,MAXPENDING) < 0 )
        errorAndTerminate("listen() failed\n");

        clntLen = sizeof(echoClntAddr);
        if((clntSock = accept(servSock,(struct sockaddr*)&echoClntAddr,&clntLen)) < 0)
            errorAndTerminate("accept() failed\n");
        char *client_ip = inet_ntoa(echoClntAddr.sin_addr);
        readFromSocket(clntSock,&msg,sizeof(msg));
        cout<<"Received msg from IP:"<<client_ip<<endl;
        queue->add(&msg);
        close(servSock); //@@
}

int communication::readFromSocket(int sockfd, Packet *msg, int size)
{
    ssize_t n_recv = recv(sockfd,(Packet*)msg,size,0);
    if(n_recv < 0)
        errorAndTerminate("Error in receiving\n");
    cout<<"===Message Type:"<<msg->TYPE<<endl;
    cout<<"Time:"<<msg->timestamp<<endl;
    close(sockfd);
}

int communication::writeToSocket(int sockfd, Packet *msg, int size)
{
    ssize_t n_send = send(sockfd,(Packet*)msg,size,0);
    if(n_send < 0)
        errorAndTerminate("send() failed\n");
    cout<<"===Message Type: "<<msg->TYPE<<" sent"<<endl;
    cout<<"Time: "<<msg->timestamp<<endl;
    return n_send;
}

int communication::connectToServer(char dest_IP_address[15], int dest_port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        errorAndTerminate("error in socket()\n");

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(dest_port);

    if(inet_pton(AF_INET,dest_IP_address,&servaddr.sin_addr) <= 0)//convert ID address from num to binary form
        errorAndTerminate("error in inet_pton\n");

    if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
        errorAndTerminate("connect() failed");
    return sockfd;
}


void communication::errorAndTerminate(string erroMessage)
{
    perror(erroMessage.c_str());
    exit(1);
}
