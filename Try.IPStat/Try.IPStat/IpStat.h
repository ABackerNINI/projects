#pragma once

#ifndef _ABACKER_IPSTAT_
#define _ABACKER_IPSTAT_

#include "stdio.h"
#include "stdlib.h"
#include "string"

using namespace std;

struct node
{
	node *l;//l代表0
	node *r;//r代表1
	node(){l = NULL;r = NULL;}
};

/*输入需要保证以下条件:
	1.每一个ip都仅属于一个子网且没有重复ip
	2.掩码满足111...11000...0000的格式
	3.子网与掩码相配(如:202.112.6.1	255.255.255.0 所有ip&该掩码不可能等于该子网)

  数据结构:
	对一个子网及其掩码,依据子网的前k位(二进制)创建一颗二叉树,k为掩码的二进制1的个数,将最后一个节点的l指针设为END点,对应的r指针用来保存落在该子网内的ip数

  匹配算法:
	对每一个ip,按照其二进制的位的方向在树上从上往下跳,如果遇到END点,则将END点对应的r指针保存的值加1(用memcpy函数)

  算法流程:
	1.以calc(char*,char*,char*)函数作为唯一接口,接收入三个文件路径
	2.调用buildTree(char*)函数读取subnet.txt,创建质点树
	3.调用match(char*)函数读取ip.txt,在树上进行匹配
	4.调用find(char*)函数打开result.txt文件
		a.调用dfs_output(node*,int*,int)函数在树上搜寻END点,将该点对应的子网和ip数输出到result.txt文件
	5.析构,调用dfs_unconstruction(node*)函数删除树上的每一个节点
	6.结束

  输出声明:
	不保证按原有的顺序输出
*/
class IPStat
{
public:
	IPStat();
	~IPStat();//不能在dfs_output过程中释放new出的内存,因为如果文件没正确打开会提前返回,那么内存就得不到释放,所以需要重新dfs一次
	bool calc(string sourceIpPath, string sourceSubnetPath, string resultPath);//重载
	bool calc(char *sourceIpPath, char *sourceSubnetPath, char *resultPath);//主要接口

private:
	bool buildTree(char *sourceSubnetPath);//创建质点树
	bool match(char *sourceIpPath);//将每一条ip在树上进行匹配,直到发现END点
	bool find(char *resultPath);//寻找ip数
	void dfs_output(node *where,int sec[4],int depth);//dfs搜索树上的END点,输出该点对应的子网值和ip数
	void dfs_unconstruction(node *where);//释放new出的内存

	node Tree;//头节点
	node *END;//判断子网结束的标志
	FILE *resultTxt;//result.txt文件指针,方便dfs_output函数调用
};

inline IPStat::IPStat(){ memset(&END, -1, sizeof(&END)); }

inline IPStat::~IPStat(){ dfs_unconstruction(&Tree); }

inline bool IPStat::calc(string sourceIpPath, string sourceSubnetPath, string resultPath){return calc((char *)sourceIpPath.data(), (char *)sourceSubnetPath.data(), (char *)resultPath.data());}

inline bool IPStat::calc(char *sourceIpPath, char *sourceSubnetPath, char *resultPath)
{
	if (!buildTree(sourceSubnetPath) || !match(sourceIpPath) || !find(resultPath))//当文件打开失败三个函数返回false
		return false;

	return true;
}

bool IPStat::buildTree(char *sourceSubnetPath)
{
	int sec[8];

	//////读取subnet.txt
	FILE *subnetTxt;
	if (subnetTxt = fopen(sourceSubnetPath, "r"), !subnetTxt)
		return false;//打开文件失败

	int i, j;
	node *tail; 
	while (fscanf(subnetTxt, "%d.", &sec[0]) != EOF)
	{
		fscanf(subnetTxt, "%d.%d.%d\t", &sec[1], &sec[2], &sec[3]);
		fscanf(subnetTxt, "%d.%d.%d.%d", &sec[4], &sec[5], &sec[6], &sec[7]);

		/*//检查子网与掩码是否相配,如果抱着输入,则不需要检查
		for (i = 3; i >= 0; i--)
		{
			for (j = 0; j < 8; j++)
			{
				if ((sec[i + 4] & (1 << j)) == 0 && sec[i] & (1 << j))
					goto next;
			}
		}*/

		//创建质点树
		tail = &Tree;
		for (i = 0; i < 4; i++)
		{
			for (j = 7; j >= 0; j--)//从高到低依次枚举子网和掩码的每一位直到掩码的位为0
			{
				if (sec[i + 4] & (1 << j))//如果掩码的该位为1,依据子网的位创建树
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
				else//掩码的位为0,结束向下创建,将之后的点的l赋为END标识,退出枚举
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
	
	//////读取ip.txt
	FILE *ipTxt;
	if (ipTxt = fopen(sourceIpPath, "r"), !ipTxt)
		return false;//打开文件失败

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
					unsigned int tmp_val;//这里假设没有ip数为2 ^ 32的极端情况
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
	/////写result.txt文件
	if (resultTxt = fopen(resultPath, "w"), !resultTxt)
		return false;//打开文件失败

	int sec[4];
	memset(sec, 0, sizeof(sec));
	dfs_output(&Tree, sec, 0);

	fclose(resultTxt);

	return true;
}

void IPStat::dfs_output(node *where, int *sec, int depth)
{
	if (where->l!=END)//where->l!=-1
	{//说明还没有匹配成功,继续往下搜
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
	else//匹配成功,输出的where->r保存的ip数
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