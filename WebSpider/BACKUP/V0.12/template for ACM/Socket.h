#pragma once

#ifndef _SOCKET_WEB_SPIDER_
#define _SOCKET_WEB_SPIDER_

#include<string>
#include<iostream>

#pragma warning(disable:4996)

#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

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
	SOCKET sockid = socket(AF_INET, SOCK_STREAM, 0);
	if (sockid == INVALID_SOCKET)return INVALID_SOCKET;

	sockaddr_in host;
	host.sin_port = 0;
	host.sin_family = AF_INET;
	host.sin_addr.S_un.S_addr = htons(INADDR_ANY);
	if (bind(sockid, (sockaddr *)&host, sizeof(host)) == SOCKET_ERROR)return INVALID_SOCKET;

	return sockid;
}

sockaddr_in Server(string &URL){
	char host[1024], path[1024];
	http_parse(URL.c_str(), host, path);

	hostent *hostent;
	hostent = gethostbyname(host);

	sockaddr_in svr;
	svr.sin_port = htons(80);
	svr.sin_family = AF_INET;
	svr.sin_addr.S_un.S_addr = hostent->h_addr_list;
}

string Download(string &URL){
	SOCKET sockid = Socket();
	if (sockid == INVALID_SOCKET)return "";

}

#endif;