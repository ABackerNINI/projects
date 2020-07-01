#pragma once

#ifndef _SOCKET_WEB_SPIDER_
#define _SOCKET_WEB_SPIDER_

#include<string>
#include<iostream>

#pragma warning(disable:4996)

#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define MAXSIZEOFEACHRECV 30000
#define MAXSIZEOFWEB 300000

void http_parse(const char *buf, char *host, char *path){
	int idx = 0, len = strlen(buf) - 1; *path = '\0';
	for (int i = 0; i < len; ++i){
		if (buf[i] == '/'&&buf[i + 1] == '/'){ idx = i + 2; break; }
	}

	for (; idx <= len; ++idx){
		if (buf[idx] == '/'){
			strcpy(path, buf + 1 + idx);
			break;
		}
		else if (buf[idx] == '?'){
			strcpy(path, buf + idx);
			break;
		}
		*(host++) = buf[idx];
	}
	*host = '\0';
}

SOCKET Socket(){
	//初始化winsock
	WSADATA wsaData;
	WORD wVersionRequested;//表示该应用程序上的winsock库版本
	wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)return INVALID_SOCKET;

	//创建套接字
	SOCKET sockid = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (sockid == INVALID_SOCKET)return INVALID_SOCKET;

	sockaddr_in hostaddr;
	hostaddr.sin_port = 0;
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_addr.S_un.S_addr = htons(INADDR_ANY);

	try{
		bind(sockid, (sockaddr *)&hostaddr, sizeof(hostaddr));

		int nNetTimeout = 2000;//超时时长
		setsockopt(sockid, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
	}
	catch (...){
		return INVALID_SOCKET;
	}

	return sockid;
}

sockaddr_in Serveraddr(char *host,char *path){
	hostent *hostent;
	hostent = gethostbyname(host);

	sockaddr_in svraddr;
	svraddr.sin_port = htons(80);
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.S_un.S_addr = *(unsigned long *)hostent->h_addr_list[0];

	return svraddr;
}

class Download{
public:
	Download(){
		if (sockid == INVALID_SOCKET)throw exception("INVALLID_SOCKET");
		data = new char[MAXSIZEOFWEB + MAXSIZEOFEACHRECV];
	}

	char *DLoad(const char *URL){
		sockid = Socket();
		//地址解析
		char host[1024], path[1024]; http_parse(URL, host, path);
		sockaddr_in svraddr = Serveraddr(host, path);

		//连接服务器
		if (connect(sockid, (sockaddr *)&svraddr, sizeof(svraddr)) == SOCKET_ERROR){ throw exception("Connect Fail!"); };

		//发送请求
		static char questfmt[] = "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: Close\r\n\r\n\r\n";
		char quest[1024]; int len = sprintf(quest, questfmt, path, host);
		int res = send(sockid, quest, len, 0);

		//接收数据
		int recvd = 0;
		while (res > 0){
			res = recv(sockid, data + recvd, MAXSIZEOFEACHRECV, 0);
			if (res > 0)recvd += res;
		}
		data[recvd] = '\0';
		
		return data;
	}
	~Download(){
		shutdown(sockid, 2);
		closesocket(sockid);
		WSACleanup();
		if (data)delete[]data;
	}
private:
	SOCKET sockid; char *data;
};
#endif;