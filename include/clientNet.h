#ifndef CLIENTNET_H
#define CLIENTNET_H
#include <stdio.h>
#include <stdlib.h>  
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

class CClientNet
{
public:
    int Connect(int port,const char* address);
    //success:0      failed:1
    int SendMsg(const char* msg,int len);
    //nothing received: -1     success: 0       overflow: 1
    int ReceiveMsg(char* msg,int len);
    void Close();
private:
    int sock_fd;
};

#endif
