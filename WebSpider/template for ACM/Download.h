#pragma once

#ifndef _DOWNLOAD_WEB_SPIDER_
#define _DOWNLOAD_WEB_SPIDER_

#include<string>
#include<iostream>

#pragma warning(disable:4996)

#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define BUF_SIZE 150000
#define http_def_port 80
//#define MAXSIZEOFWEB 300000

struct server{
		sockaddr_in sever_addr;//服务器的套结字信息
		int result = 0, send_len;//发送数据的长度
		unsigned short sever_port = http_def_port;
		char host[1024];//主机名
		char path[1024];//文件路径
		char data_buf[BUF_SIZE];
		char *send_buf = "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: Close\r\n\r\n\r\n";
		hostent *sever_hostent;
};

class Download{
public:
	Download(){}

	string download(const string &URL){
		try{
			sockid = local();
			if (sockid == NULL)return "";

			//获取服务器地址
			http_parse(URL.data(), svr.host, svr.path);
			svr.sever_hostent = gethostbyname(svr.host);
			if (svr.sever_hostent == NULL)return "";

			svr.sever_addr.sin_family = AF_INET;
			svr.sever_addr.sin_port = htons(http_def_port);//选择服务器的端口
			svr.sever_addr.sin_addr.s_addr = *(unsigned long *)svr.sever_hostent->h_addr;


			//建立连接
			connect(sockid, (sockaddr*)&svr.sever_addr, sizeof(svr.sever_addr));

			svr.send_len = sprintf(svr.data_buf, svr.send_buf, svr.path, svr.host);

			string ret; int recvd = 0;

			svr.result = send(sockid, svr.data_buf, svr.send_len, 0);
			while (svr.result > 0){
				svr.result = recv(sockid, svr.data_buf, BUF_SIZE, 0);//接受数据
				if (svr.result > 0){
					svr.data_buf[svr.result] = 0;
					ret += svr.data_buf;
				}
			}
			return ret;
		}
		catch (...){ return ""; }
	}

	~Download(){
		shutdown(sockid, 2);//关闭读写通道
		closesocket(sockid);//关闭套接口
		WSACleanup();//终止使用套接口
	}

private:
	SOCKET sockid;
	server svr;

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

	SOCKET local(){
		WSADATA wsaData;
		WORD wVersionRequested;//表示该应用程序上的winsock库版本
		SOCKET sockid;
		sockaddr_in hostaddr;//本地的套结字地址信息

		try{
			wVersionRequested = MAKEWORD(2, 2);
			//初始化winsock
			if (WSAStartup(wVersionRequested, &wsaData) != 0){
				printf(" winsock初始错误\n");
				return NULL;
			}
			//创建套接口
			sockid = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
			//初始化本地地址
			hostaddr.sin_family = AF_INET;
			int host_port = 0;//本地端口
			hostaddr.sin_port = htons(host_port);//表示端口参数
			hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);//表示IP地址参数，INADDR_ANY表示使用系统自动指定的IP地址
			//绑定本地地址
			bind(sockid, (sockaddr *)&hostaddr, sizeof(hostaddr));
			return sockid;
		}
		catch (...){ return NULL; }
	}
};

#endif