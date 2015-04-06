#include "messageFormat.h"

class algorithmDataStruct
{
protected:
    int quorumSize;
    int totalNodeNumber;
public:
    bool isServer;
    int nodeID;
    vector<int> quorumMembers;
    bool REQUESTING;
    bool TOKEN;
    bool USING;
    bool KNOWFLAG;
    int TADDR; //save the nodeID of which hold the token
    bool SERVFLAG;
    int SERVEE; //save the nodeID of which the local node is serving
    char **mapIDtoIP; //save the IP Address of correspond nodeID
};
 
