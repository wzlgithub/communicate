#include "clientNet.h"

int CClientNet::Connect(int port,const char* address)
{  
    struct sockaddr_in server;  

    if((sock_fd=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {  
        printf("socket()error\n");  
        return -1;
    }  
    printf("create socket success!\n");
    bzero(&server,sizeof(server));  
    server.sin_family= AF_INET;  
    server.sin_port = htons(port);  
    server.sin_addr.s_addr =inet_addr(address);
    if(connect(sock_fd,(struct sockaddr *)&server,sizeof(server))==-1)
    {  
        printf("connect()error\n");  
        return -2;
    }  
    return 0;  
}  


int CClientNet::SendMsg(const char* msg,int len)
{
	int iErrMsg = 0;

	//send message
    iErrMsg = send(sock_fd, msg, len, 0);
	//send message failed
	if (iErrMsg < 0)
	{
        return 1;
	}
    return 0;
}


int CClientNet::ReceiveMsg( char* msg, int len) {

	int recv_size = 0;

	memset(msg,0,512);
    recv_size = recv(sock_fd, msg, len, 0);
	//printf("recv_size is  %d\n", recv_size);
	if (recv_size == -1)
	{
        return -1;
	}
	if (512 > recv_size)
	{
		msg[recv_size] = '\0';
        return 0;
	}
	else
	{
        return 1;
	}
}


void CClientNet::Close()
{
    close(sock_fd);			//terminate Windows Sockets DLL
}
