#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<iostream>
#include"http_conn.h"
#include"process_pool.h"
using namespace std;

int main(int argc,char* argv[])
{
	if(argc<=4)
	{
		cout<<"usage: "<< argv[0] <<" ip port process_number connect_number_per_process"<<endl;
		return 1;
	}
	
	const char*ip = argv[1];
	int port = atoi(argv[2]);
	int process_number = atoi(argv[3]);
	int connect_number_per_process = atoi(argv[4]);

	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd>=0);

	int ret = 0;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret==0);
	ret = listen(listenfd,5);
	assert(ret==0);

	cout<<"==== wait request ===="<<endl;
	//todo:use process_poll class creat process
	ProcessPool<HttpConn>&pool = ProcessPool<HttpConn>::instance(listenfd,process_number,connect_number_per_process);
	pool.Run();

	close(listenfd);
	return 0;
}


