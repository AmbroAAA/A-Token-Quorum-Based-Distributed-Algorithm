#pragma once
#include <vector>
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
#define MAX_IP_LENGTH 16
/*=====================Message Packet========================*/
struct Packet
{
int TYPE; //Message Type
int senderID; //This message`s senderID
}
