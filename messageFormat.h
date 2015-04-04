#pragma once
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
using namespace std;
/*=======================Message Types========================*/
#define REQUEST_FINAL 0
#define REQUEST_PARTIAL 1
#define HAVE_TOKEN 2
#define RELEASE 3
#define SEND_TOKEN 4
#define RREQUEST 5
#define SETTLE 6
#define UPDATE_HOLD_TOKEN 7
#define UPDATE_LOSE_TOKEN 8


/*=======================Communication Information=============*/
#define SYSTEM_CONTROLLER_ID 66
#define SYSTEM_CONTROLLER_IP "192.168.254.130"
#define MAX_IP_LENGTH 16
#define MAXPENDING 5

#define PORT1 3666
#define PORT2 3766
#define PORT3 3866
/*=====================Message Packet========================*/

struct Packet
{
    int TYPE; //Message Type
    int senderID; //This message`s senderID
};
