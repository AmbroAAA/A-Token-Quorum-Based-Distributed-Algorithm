#include "communication.h"
#include "localProcessInfo.h"
#include "messageFormat.h"

int main()
{
    communication com;
    algorithmDataStruct algo;

    cout<<"Server or Client"<<endl;
    int temp;
    cin>>temp;
    if(temp == 1)
    {
        cout<<"server"<<endl;
        com.serverListen(PORT1);
    }
    else
    {
        cout<<"client"<<endl;
        char buffer[20];
        cin>>buffer;

        int sockfd = com.connectToServer(SYSTEM_CONTROLLER_IP,PORT1);

        com.writeToSocket(sockfd,buffer,sizeof(buffer));

    }
}
