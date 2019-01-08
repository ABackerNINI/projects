#pragma once

#ifndef _ABACKER_IPSTAT_
#define _ABACKER_IPSTAT_

#include "stdio.h"
#include "stdlib.h"
#include "string"

using namespace std;

struct node
{
	node *l;//l����0
	node *r;//r����1
	node(){l = NULL;r = NULL;}
};

/*������Ҫ��֤��������:
	1.ÿһ��ip��������һ��������û���ظ�ip
	2.��������111...11000...0000�ĸ�ʽ
	3.��������������(��:202.112.6.1	255.255.255.0 ����ip&�����벻���ܵ��ڸ�����)

  ���ݽṹ:
	��һ��������������,����������ǰkλ(������)����һ�Ŷ�����,kΪ����Ķ�����1�ĸ���,�����һ���ڵ��lָ����ΪEND��,��Ӧ��rָ�������������ڸ������ڵ�ip��

  ƥ���㷨:
	��ÿһ��ip,����������Ƶ�λ�ķ��������ϴ���������,�������END��,��END���Ӧ��rָ�뱣���ֵ��1(��memcpy����)

  �㷨����:
	1.��calc(char*,char*,char*)������ΪΨһ�ӿ�,�����������ļ�·��
	2.����buildTree(char*)������ȡsubnet.txt,�����ʵ���
	3.����match(char*)������ȡip.txt,�����Ͻ���ƥ��
	4.����find(char*)������result.txt�ļ�
		a.����dfs_output(node*,int*,int)������������ѰEND��,���õ��Ӧ��������ip�������result.txt�ļ�
	5.����,����dfs_unconstruction(node*)����ɾ�����ϵ�ÿһ���ڵ�
	6.����

  �������:
	����֤��ԭ�е�˳�����
*/
class IPStat
{
public:
	IPStat();
	~IPStat();//������dfs_output�������ͷ�new�����ڴ�,��Ϊ����ļ�û��ȷ�򿪻���ǰ����,��ô�ڴ�͵ò����ͷ�,������Ҫ����dfsһ��
	bool calc(string sourceIpPath, string sourceSubnetPath, string resultPath);//����
	bool calc(char *sourceIpPath, char *sourceSubnetPath, char *resultPath);//��Ҫ�ӿ�

private:
	bool buildTree(char *sourceSubnetPath);//�����ʵ���
	bool match(char *sourceIpPath);//��ÿһ��ip�����Ͻ���ƥ��,ֱ������END��
	bool find(char *resultPath);//Ѱ��ip��
	void dfs_output(node *where,int sec[4],int depth);//dfs�������ϵ�END��,����õ��Ӧ������ֵ��ip��
	void dfs_unconstruction(node *where);//�ͷ�new�����ڴ�

	node Tree;//ͷ�ڵ�
	node *END;//�ж����������ı�־
	FILE *resultTxt;//result.txt�ļ�ָ��,����dfs_output��������
};

inline IPStat::IPStat(){ memset(&END, -1, sizeof(&END)); }

inline IPStat::~IPStat(){ dfs_unconstruction(&Tree); }

inline bool IPStat::calc(string sourceIpPath, string sourceSubnetPath, string resultPath){return calc((char *)sourceIpPath.data(), (char *)sourceSubnetPath.data(), (char *)resultPath.data());}

inline bool IPStat::calc(char *sourceIpPath, char *sourceSubnetPath, char *resultPath)
{
	if (!buildTree(sourceSubnetPath) || !match(sourceIpPath) || !find(resultPath))//���ļ���ʧ��������������false
		return false;

	return true;
}

bool IPStat::buildTree(char *sourceSubnetPath)
{
	int sec[8];

	//////��ȡsubnet.txt
	FILE *subnetTxt;
	if (subnetTxt = fopen(sourceSubnetPath, "r"), !subnetTxt)
		return false;//���ļ�ʧ��

	int i, j;
	node *tail; 
	while (fscanf(subnetTxt, "%d.", &sec[0]) != EOF)
	{
		fscanf(subnetTxt, "%d.%d.%d\t", &sec[1], &sec[2], &sec[3]);
		fscanf(subnetTxt, "%d.%d.%d.%d", &sec[4], &sec[5], &sec[6], &sec[7]);

		/*//��������������Ƿ�����,�����������,����Ҫ���
		for (i = 3; i >= 0; i--)
		{
			for (j = 0; j < 8; j++)
			{
				if ((sec[i + 4] & (1 << j)) == 0 && sec[i] & (1 << j))
					goto next;
			}
		}*/

		//�����ʵ���
		tail = &Tree;
		for (i = 0; i < 4; i++)
		{
			for (j = 7; j >= 0; j--)//�Ӹߵ�������ö�������������ÿһλֱ�������λΪ0
			{
				if (sec[i + 4] & (1 << j))//�������ĸ�λΪ1,����������λ������
				{
					if (sec[i] & (1 << j))//1 -> r
					{
						if (tail->r == NULL)
							tail->r = new node;
						tail = tail->r;
					}
					else//0 -> l
					{
						if (tail->l == NULL)
							tail->l = new node;
						tail = tail->l;
					}
				}
				else//�����λΪ0,�������´���,��֮��ĵ��l��ΪEND��ʶ,�˳�ö��
				{
					tail->l = END;
					//memcpy(&tail->l, &END, sizeof(&tail->l));
					goto next;
				}
			}
		}

	next:
		continue;
	}

	fclose(subnetTxt);

	return true;
}

bool IPStat::match(char *sourceIpPath)
{
	int sec[4];
	
	//////��ȡip.txt
	FILE *ipTxt;
	if (ipTxt = fopen(sourceIpPath, "r"), !ipTxt)
		return false;//���ļ�ʧ��

	node *tail;
	while (fscanf(ipTxt, "%d.", &sec[0]) != EOF)
	{
		fscanf(ipTxt, "%d.%d.%d\t", &sec[1], &sec[2], &sec[3]);

		tail = &Tree;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 7; j >= 0; j--)
			{
				if (tail->l == END)//tail-l==-1
				{
					unsigned int tmp_val;//�������û��ip��Ϊ2 ^ 32�ļ������
					memcpy(&tmp_val, &tail->r, sizeof(&tmp_val));
					tmp_val++;
					memcpy(&tail->r, &tmp_val, sizeof(&tail->r));
					goto next;
				}

				if (sec[i] & (1 << j))//1 -> r
					tail = tail->r;
				else//0 -> l
					tail = tail->l;
			}
		}

	next:
		continue;
	}

	fclose(ipTxt);

	return true;
}

bool IPStat::find(char *resultPath)
{
	/////дresult.txt�ļ�
	if (resultTxt = fopen(resultPath, "w"), !resultTxt)
		return false;//���ļ�ʧ��

	int sec[4];
	memset(sec, 0, sizeof(sec));
	dfs_output(&Tree, sec, 0);

	fclose(resultTxt);

	return true;
}

void IPStat::dfs_output(node *where, int *sec, int depth)
{
	if (where->l!=END)//where->l!=-1
	{//˵����û��ƥ��ɹ�,����������
		int tmp_depth = depth >> 3;//depth/8
		int tmp_sec[4];
		if (where->l)//l -> 0
		{
			memcpy(tmp_sec, sec, sizeof(tmp_sec));
			tmp_sec[tmp_depth] <<= 1;

			dfs_output(where->l, tmp_sec, depth + 1);
		}

		if (where->r)//r -> 1
		{
			sec[tmp_depth] <<= 1;
			sec[tmp_depth] |= 1;

			dfs_output(where->r, sec, depth + 1);
		}
	}
	else//ƥ��ɹ�,�����where->r�����ip��
		fprintf(resultTxt, "%d.%d.%d.%d\t%u\n", sec[0], sec[1], sec[2], sec[3], (unsigned int)where->r);
}

void IPStat::dfs_unconstruction(node *where)
{
	if (where->l != END)
	{
		if (where->l)
			dfs_unconstruction(where->l),delete where->l;

		if (where->r)
			dfs_unconstruction(where->r),delete where->r;
	}
}

#endif