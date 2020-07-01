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
		sockaddr_in sever_addr;//���������׽�����Ϣ
		int result = 0, send_len;//�������ݵĳ���
		unsigned short sever_port = http_def_port;
		char host[1024];//������
		char path[1024];//�ļ�·��
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

			//��ȡ��������ַ
			http_parse(URL.data(), svr.host, svr.path);
			svr.sever_hostent = gethostbyname(svr.host);
			if (svr.sever_hostent == NULL)return "";

			svr.sever_addr.sin_family = AF_INET;
			svr.sever_addr.sin_port = htons(http_def_port);//ѡ��������Ķ˿�
			svr.sever_addr.sin_addr.s_addr = *(unsigned long *)svr.sever_hostent->h_addr;


			//��������
			connect(sockid, (sockaddr*)&svr.sever_addr, sizeof(svr.sever_addr));

			svr.send_len = sprintf(svr.data_buf, svr.send_buf, svr.path, svr.host);

			string ret; int recvd = 0;

			svr.result = send(sockid, svr.data_buf, svr.send_len, 0);
			while (svr.result > 0){
				svr.result = recv(sockid, svr.data_buf, BUF_SIZE, 0);//��������
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
		shutdown(sockid, 2);//�رն�дͨ��
		closesocket(sockid);//�ر��׽ӿ�
		WSACleanup();//��ֹʹ���׽ӿ�
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
		WORD wVersionRequested;//��ʾ��Ӧ�ó����ϵ�winsock��汾
		SOCKET sockid;
		sockaddr_in hostaddr;//���ص��׽��ֵ�ַ��Ϣ

		try{
			wVersionRequested = MAKEWORD(2, 2);
			//��ʼ��winsock
			if (WSAStartup(wVersionRequested, &wsaData) != 0){
				printf(" winsock��ʼ����\n");
				return NULL;
			}
			//�����׽ӿ�
			sockid = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
			//��ʼ�����ص�ַ
			hostaddr.sin_family = AF_INET;
			int host_port = 0;//���ض˿�
			hostaddr.sin_port = htons(host_port);//��ʾ�˿ڲ���
			hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);//��ʾIP��ַ������INADDR_ANY��ʾʹ��ϵͳ�Զ�ָ����IP��ַ
			//�󶨱��ص�ַ
			bind(sockid, (sockaddr *)&hostaddr, sizeof(hostaddr));
			return sockid;
		}
		catch (...){ return NULL; }
	}
};

#endif