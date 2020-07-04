#pragma once
#include <string>
#include <stdio.h>
#include <vector>
#include "函数名.h"

using namespace std;

struct TOKEN
{
	int type_id;
	int num;
	/*
	type_id
	0：关键字表
	1：标识符表
	2：界符表
	3：整型常量表
	4：实型常量表
	5：字符表
	6：字符串表
	
	7：SYNBL表
	8：类型表
	9：数组表
	10：种类表
	11：函数表
	
	num为该类型的标号（偏移地址）
	*/
};	//token序列用于表示表的类型

//SYNBL主表结构
struct SYNBL
{
	string name;	//名字
	TOKEN type;		//类型
	string CAT;		//种类
	TOKEN ADDR;		//地址
};

//类型表结构
struct TYPEL
{
	char TVAL;		//类型代码
	TOKEN TPOINT;	//信息内容指向
};

//数组表结构
struct AINFL
{
	int LOW;		//数组起始标号
	int UP;			//数组末尾标号
	char CTP;		//数组类型
	int CLEN;		//数组长度
};

//函数表结构
struct PFINFL
{
	int nowLEVEL;	//当前层次
	int farLEVEL;	//调用此函数的层次
	int FN;			//参数个数
	TOKEN funAddr;	//在主表中的位置
};

//四元式结构
struct QT 
{
	string operate;  //操作符
	string res1;     //第一个操作数
	string res2;     //第二个操作数
	string result;   //操作结果
};

//token序列
extern vector<TOKEN> TOKEN_List;

//关键字表
static const char* KT[10] = { "main","int","char","float","if","else","while","for","return" };
//			        0      1      2      3     4     5       6      7      8

//标识符表
extern vector<string> IT;

//界符表
static const char* PT[19] = { "+" ,"-","*","/","<",">","<=",">=","=","!=","==",";",",","(",")","[","]","{" ,"}" };
//                             0    1   2   3   4   5    6    7   8    9   10   11  12  13  14  15  16  17  18

//字符表
extern vector<char> CT;

//字符串常量表
extern vector<string> ST;

//整型常量表
extern vector<int> IC;

//实型常量表
extern vector<float> FC;

//SYNBL主表
extern vector<SYNBL> SYNBL_List;

//类型表
extern vector<TYPEL> TYPEL_List;

//数组表
extern vector<AINFL> AINFL_List;

//函数表
extern vector<PFINFL> PFINFL_List;

//长度表
extern vector<int> Len_List;

//四元式序列
extern vector<QT> QT_List;



