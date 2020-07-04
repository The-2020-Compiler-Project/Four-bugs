#pragma once
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

struct TOKEN
{
	int type_id;
	int num;
	/*
	type_id
	0���ؼ��ֱ�
	1����ʶ����
	2�������
	3�����ͳ�����
	4��ʵ�ͳ�����
	5���ַ���
	6���ַ�����
	
	7��SYNBL��
	8�����ͱ�
	9�������
	10�������
	11��������
	
	numΪ�����͵ı�ţ�ƫ�Ƶ�ַ��
	*/
};	//token�������ڱ�ʾ�������

//SYNBL����ṹ
struct SYNBL
{
	string name;	//����
	TOKEN type;		//����
	string CAT;		//����
	TOKEN ADDR;		//��ַ
};

//���ͱ�ṹ
struct TYPEL
{
	char TVAL;		//���ʹ���
	TOKEN TPOINT;	//��Ϣ����ָ��
};

//�����ṹ
struct AINFL
{
	int LOW;		//������ʼ���
	int UP;			//����ĩβ���
	char CTP;		//��������
	int CLEN;		//���鳤��
};

//������ṹ
struct PFINFL
{
	int nowLEVEL;	//��ǰ���
	int farLEVEL;	//���ô˺����Ĳ��
	int FN;			//��������
	TOKEN funAddr;	//�������е�λ��
};

//��Ԫʽ�ṹ
struct QT 
{
	string operate;  //������
	string res1;     //��һ��������
	string res2;     //�ڶ���������
	string result;   //�������
};

//token����
vector<TOKEN> TOKEN_List;

//�ؼ��ֱ�
const char* KT[10] = { "main","int","char","float","if","else","while","for","return" };

//��ʶ����
vector<string> IT;

//�����
const char* PT[19] = { "+" ,"-","*","/","<",">","<=",">=","=","!=","==",";",",","(",")","[","]","{" ,"}" };

//�ַ���
vector<char> CT;

//�ַ���������
vector<string> ST;

//���ͳ�����
vector<int> IC;

//ʵ�ͳ�����
vector<float> FC;

//SYNBL����
vector<SYNBL> SYNBL_List;

//���ͱ�
vector<TYPEL> TYPEL_List;

//�����
vector<AINFL> AINFL_List;

//������
vector<PFINFL> PFINFL_List;

//���ȱ�
vector<int> Len_List;

//��Ԫʽ����
vector<QT> QT_List;



