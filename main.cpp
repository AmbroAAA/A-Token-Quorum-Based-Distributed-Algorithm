/*==================================================================================
                Token-Quorum Based Distributed Algorithm
                Author:     Hongyi Guo
                Basic Communication + Timestamped
                Create Process Thread & Listen Thread
                Version:1.3
====================================================================================*/


#include "communication.h"
#include "localProcessInfo.h"
#include "messageFormat.h"

int askRequest = 0;
void *forRequest(void* threadAttribute)
{
    char *temp1 = (char*)threadAttribute;//meaningless


    cout<<"Enter 1 for Requesting\n";
   // pthread_mutex_t typing;
  //  pthread_mutex_lock(&typing);
    cin.sync();
    sleep(3);
    cin>>askRequest;                         //@@@@@can not get any input
  //  pthread_mutex_unlock(&typing);


}

void *threadProcess(void* threadAtrribute)
{
    communication com;
    messageQueue<Packet*> *queue = ((messageQueue<Packet*>*)threadAtrribute);
    cout<<"Start Processing"<<endl;
    cout<<"Input \"1\" to Request Critical Section"<<endl;
    sleep(3);
    if(askRequest == 1)
    {
        cout<<"Enter critical section\n";
    }
    cout<<"Processing\n";

}

void *threadListen(void* threadAttribute)
{
    communication com;
    messageQueue<Packet*>* queue = ((messageQueue<Packet*>*)threadAttribute);
    cout<<"Start Listening"<<endl;
    cout<<"Listening\n";
    //com.serverListen(PORT_LISTEN,queue);

}

int main()
{
    communication com;
    algorithmDataStruct algo;
    messageQueue<Packet*> queue;

    cout<<"Controller(0) or New node(1) or New node(2)"<<endl;
    int roleSelector;
    cin>>roleSelector;
    if(roleSelector == 0)
    {
        cout<<"Controller Set Up"<<endl;
        com.serverListen(PORT1,&queue);
    }
    else if(roleSelector == 1)
    {

        cout<<"New Node Set Up"<<endl;
        Packet msg;
        cin>>msg.TYPE;
        //Timestamp
        time_t currentTime = time(NULL);
        snprintf(msg.timestamp,sizeof(msg.timestamp),"%.24s\r\n",ctime(&currentTime));

        int sockfd = com.connectToServer(SYSTEM_CONTROLLER_IP,PORT1);

        com.writeToSocket(sockfd,&msg,sizeof(msg));



        int *request;

        pthread_t listenThread;                       //two thread share same resources AKA the msgQueue
        pthread_t processThread;
        pthread_t callRequest;

while(1)
       { pthread_create(&callRequest,NULL,forRequest,(void*)request);
        pthread_create(&processThread,NULL,threadListen,&queue);
        pthread_create(&listenThread,NULL,threadProcess,&queue);


        pthread_join(callRequest,NULL);
        pthread_join(listenThread,NULL);
        pthread_join(processThread,NULL);

        }

        //close(sockfd);

    }
}
