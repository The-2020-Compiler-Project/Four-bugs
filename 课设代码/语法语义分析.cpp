#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include "���ű�ṹ.h"

using namespace std;

TOKEN now_Token;	//��ǰ�Ķ�ȡtoken
int flag=1;			//����﷨�����Ƿ���ȷ�ı�־��Ĭ��Ϊ1�������������Ϊ0

//��ʼ��now_Token��ʹnow_Tokenָ���һ��token
int int_token()
{

}

//now_Tokenָ����һ��token
void readToken()
{

}


//����ʼ
void run() 
{   
	int_token();
	Source();
	if (flag == 1) 
	{  
		cout << "�﷨������ɣ�û�д���" << endl;	
	}
	else if (flag == 0)
	{
		cout << "�﷨���������д��ڴ���" << endl;
	}
	else
	{
		cout << "�����־flag�������" << endl;
	}

}

//<Դ����>��<��ʼ>
int Source()
{
	begin();
}

//<��ʼ>��<��������><������>|<��������><�ⲿ����>
int begin()
{
	if (now_Token.type_id == 0 && (KT[now_Token.num] == "int" || KT[now_Token.num] == "char" || KT[now_Token.num] == "float"))
	{
		readToken();
		if (now_Token.type_id == 0 && KT[now_Token.num] == "main")
		{
			main_function();
		}
		else if (now_Token.type_id == 1)
		{
			External();
		}
		else
		{
			cout << "������ȱ�ٻ������������" << endl;
			flag = 0;
		}
	}
	else
	{
		cout << "����ȱ�����ͷ���" << endl;
		flag = 0;
	}
}

//<������>��main ( ) {<�������>}
int main_function()
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "main")
	{
		if (now_Token.type_id == 2 && PT[now_Token.num] == "(")
		{
			readToken();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ")")
			{
				readToken();
				if (now_Token.type_id == 2 && PT[now_Token.num] == "{")
				{
					readToken();
					Compound();
					if (now_Token.type_id == 2 && PT[now_Token.num] == "}")
					{
						return 1;
					}
					else
					{
						cout << "����������ȱ�� } �һ����ţ�" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "����������ȱ�� } �һ����ţ�" << endl;
					flag = 0;
				}

			}
			else
			{
				cout << "������������ȱ�� �� �����ţ�" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "������������ȱ�� ( �����ţ�" << endl;
			flag = 0;
		}
	}
	return 1;
}

//<�ⲿ����>��<����ͷ>;<��ʼ>|<����ͷ>{<�������>}<��ʼ>
int External()
{
	function_header();
	if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
	{
		readToken();
		begin();
	}
	else if (now_Token.type_id == 2 && PT[now_Token.num] == "{")
	{
		readToken();
		Compound();
		if (now_Token.type_id == 2 && PT[now_Token.num] == "}")
		{
			readToken();
			begin();
		}
		else
		{
			cout << "��������ȱ�� } �һ����ţ�" << endl;
			flag = 0;
		}
	}
	else
	{
		cout << "�ⲿ������ڴ���" << endl;
		flag = 0;
	}
	return 1;
}

//<����ͷ>��<��ʶ��>(<�β�>)
int function_header()
{
	if (now_Token.type_id == 1)
	{
		if (now_Token.type_id == 2 && PT[now_Token.num] == "(")
		{
			readToken();
			Formal();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ")")
			{
				readToken();
				return 1;
			}
			else
			{
				cout << "����������ȱ�� �� �����ţ�" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "����������ȱ�� ( �����ţ�" << endl;
			flag = 0;
		}
	}
	
	return 1;
}


//<�β�>��<��������><��ʶ��>|<��������><��ʶ��>,<�β�>
int Formal()
{
	if (now_Token.type_id == 0 && (KT[now_Token.num] == "int" || KT[now_Token.num] == "char" || KT[now_Token.num] == "float"))
	{
		readToken();
		if (now_Token.type_id == 1)
		{
			readToken();
			Formal();
		}
		else
		{
			cout << "������β�Ϊ�Ǳ�ʶ����" << endl;
			flag = 0;
		}
	}
	else
	{
		cout << "�������Ͷ������" << endl;
		flag = 0;
	}
	return 1;
}


//<�������>��<��������><�������> | <��ֵ�������������><�������> | <ѡ�����><�������> | <ѭ�����><�������> | <�������><�������> | ��
int Compound() 
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "if")
	{
		Select();
		Compound();
	}
	else if (now_Token.type_id == 0 && KT[now_Token.num] == "while")
	{
		Cycle();
		Compound();
	}
	else if (now_Token.type_id == 0 && KT[now_Token.num] == "return")
	{
		Cycle();
		Compound();
	}
	else if (now_Token.type_id == 0 && (KT[now_Token.num] == "int" || KT[now_Token.num] == "char" || KT[now_Token.num] == "float"))
	{
		Variable();
		Compound();
	}
	else if (now_Token.type_id == 1)
	{
		Call_and_Assignment();
		Compound();
	}
	return 1;
}



//<��������>��<��������><��ʶ��>��|<��������><��ʶ��>��<��ʶ���б�>��|<��������><��ʶ��><�����б�>;
int Variable()
{
	if (now_Token.type_id == 0 && (KT[now_Token.num] == "int" || KT[now_Token.num] == "char" || KT[now_Token.num] == "float"))
	{
		readToken();
		if (now_Token.type_id == 1)
		{
			readToken();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
			{
				readToken();
				return 1;
			}
			else if (now_Token.type_id == 2 && PT[now_Token.num] == ",")
			{
				dentifier();
				if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
				{
					readToken();
					return 1;
				}
				else
				{
					cout << "��������ȱ�� ; �ֺţ�" << endl;
					flag = 0;
				}
			}
			else if (now_Token.type_id == 2 && PT[now_Token.num] == "[")
			{
				Array();
				if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
				{
					readToken();
					return 1;
				}
				else
				{
					cout << "��������ȱ�� ; �ֺţ�" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "��������ȱ�� ; �ֺţ�" << endl;
				flag = 0;
			}
			
		}
		
	}
	else
	{
		cout << "������������" << endl;
		flag = 0;
	}
	return 1;
}

//<��ʶ���б�>��<��ʶ��> | <��ʶ��>,<��ʶ���б�>
int dentifier()
{
	if (now_Token.type_id == 1)
	{
		readToken();
		if (now_Token.type_id == 2 && PT[now_Token.num] == ",")
		{
			readToken();
			dentifier();
		}
	}
	else
	{
		cout << "��ʶ������ʧ�ܣ�" << endl;
		flag = 0;
	}
	return 1;
}

//<�����б�>��[<�������ʽ>] | ��<��ʶ��>[<�������ʽ>]<�����б�1>
int Array()
{
	if (now_Token.type_id == 2 && PT[now_Token.num] == "[")
	{
		readToken();
		Arithmetic_Expression();
		if (now_Token.type_id == 2 && PT[now_Token.num] == "]")
		{
			readToken();
			return 1;
		}
		else
		{
			cout << "���鶨��ȱ�� ] �ҷ����ţ�" << endl;
			flag = 0;
		}
	}
	else if (now_Token.type_id == 2 && PT[now_Token.num] == ",")
	{
		readToken();
		if (now_Token.type_id == 1)
		{
			if (now_Token.type_id == 2 && PT[now_Token.num] == "[")
			{
				readToken();
				Arithmetic_Expression();
				if (now_Token.type_id == 2 && PT[now_Token.num] == "]")
				{
					readToken();
					if (now_Token.type_id == 2 && PT[now_Token.num] == ",")
					{
						Array();
					}
					else
					{
						return 1;
					}
				}
				else
				{
					cout << "���鶨��ȱ�� ] �ҷ����ţ�" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "���鶨��ȱ�� [ �����ţ�" << endl;
				flag = 0;
			}
		}
	}
	return 1;
}



//<ѡ�����>��if(<���ʽ>){<�������>}��else(<���ʽ>){<�������>}��
int Select()
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "if")
	{
		readToken();
		if (now_Token.type_id == 2 && PT[now_Token.num] == "(")
		{
			readToken();
			Expression();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ")")
			{
				readToken();
				if (now_Token.type_id == 2 && PT[now_Token.num] == "{")
				{
					readToken();
					Compound();
					if (now_Token.type_id == 2 && PT[now_Token.num], "}")
					{
						readToken();
						if (now_Token.type_id == 0 && KT[now_Token.num] == "else")
						{
							readToken();
							if (now_Token.type_id == 2 && PT[now_Token.num] == "(")
							{
								readToken();
								Expression();
								if (now_Token.type_id == 2 && PT[now_Token.num] == ")")
								{
									readToken();
									if (now_Token.type_id == 2 && PT[now_Token.num] == "{")
									{
										readToken();
										Compound();
										if (now_Token.type_id == 2 && PT[now_Token.num] == "}")
										{
											readToken();
											return 1;
										}
										else
										{
											cout << "ѭ�����ȱ�� } �һ����ţ�" << endl;
											flag = 0;
										}
									}
									else
									{
										cout << "ѭ�����ȱ�� { �����ţ�" << endl;
										flag = 0;
									}
								}
								else
								{
									cout << "ѭ�����ȱ�٣� �����ţ�" << endl;
									flag = 0;
								}
							}
							else
							{
								cout << "ѭ�����ȱ�٣� �����ţ�" << endl;
								flag = 0;
							}
						}
						else
						{
							return 1;
						}
					}
					else
					{
						cout << "ѡ�����ȱ�� } �һ����ţ�" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "ѡ�����ȱ�� { �����ţ�" << endl;
					flag = 0;
				}
			}
		}
		else
		{
			cout << "ѡ�����ȱ�� �� �����ţ�" << endl;
			flag = 0;
		}
	}
	else
		return 1;
}

//<ѭ�����>��while(<���ʽ>){<�������>}
int Cycle()
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "while")
	{
		readToken();
		if (now_Token.type_id == 2 && KT[now_Token.num] == "(")
		{
			readToken();
			Expression();
			if (now_Token.type_id == 2 && KT[now_Token.num] == ")")
			{
				readToken();
				if (now_Token.type_id == 2 && KT[now_Token.num] == "{")
				{
					readToken();
					Compound();
					if (now_Token.type_id == 2 && PT[now_Token.num] == "}")
					{
						readToken();
						return 1;
					}
					else
					{
						cout << "ѭ�����ȱ�� } �һ����ţ�" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "ѭ�����ȱ�� { �����ţ�" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "ѭ�����ȱ�٣� �����ţ�" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "ѭ�����ȱ�٣� �����ţ�" << endl;
			flag = 0;
		}
	}
	return 1;
}

//<�������>��return<��ʶ��>;|return<���ͳ���>;
int Back()
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "return")
	{
		readToken();
		if (now_Token.type_id == 1 || now_Token.type_id == 3)
		{
			if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
			{
				readToken();
				return 1;
			}
			else
			{
				cout << "ȱ�� ; �ֺţ�" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "����ֵ�Ǳ�ʶ��������������" << endl;
			flag = 0;
		}
	}
	return 1;
}

//<��ֵ�������������>�� < ��ʶ�� >= <���ʽ>�� | < ��ʶ�� >= <��ʶ��>(<ʵ��>); | <��ʶ��>(<ʵ��>);
int Call_and_Assignment()
{
	if (now_Token.type_id == 1)
	{
		readToken();
		if (now_Token.type_id == 2 && PT[now_Token.num] == "=")
		{
			readToken();
			Expression();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
			{
				readToken();
				return 1;
			}
			else if (now_Token.type_id == 2 && PT[now_Token.num] == "(")
			{
				readToken();
				Actual();
				if (now_Token.type_id == 2 && PT[now_Token.num] == ")")
				{
					readToken();
					if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
					{
						readToken();
						return 1;
					}
					else
					{
						cout << "ȱ�� ; �ֺţ�" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "ȱ�� �� �����ţ�" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "��ֵ�������ô���" << endl;
				flag = 0;
			}
		}
		else if (now_Token.type_id == 2 && PT[now_Token.num] == "(")
		{
			readToken();
			Actual();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ")")
			{
				readToken();
				if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
				{
					readToken();
					return 1;
				}
				else
				{
					cout << "ȱ�� ; �ֺţ�" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "ȱ�� �� �����ţ�" << endl;
				flag = 0;
			}
		}
	}
	else
	{
		cout << "��ֵ�������ô���" << endl;
		flag = 0;
	}
	return 1;
}

//<ʵ��>��<��ʶ��>|<��ʶ��>,<ʵ��>
int Actual()
{
	if (now_Token.type_id == 1)
	{
		readToken;
		if (now_Token.type_id == 2 && PT[now_Token.num] == ",")
		{
			readToken;
			Actual();
		}
	}
	else
	{
		cout << "����ʵ�ζ������" << endl;
		flag = 0;
	}
	return 1;
}


//<���ʽ>��<�������ʽ>|<�߼����ʽ>|<�ַ�����>|<�ַ�������>
int Expression()
{
	Arithmetic_Expression();
	Logic_Expression();
	if (now_Token.type_id == 5 || now_Token.type_id == 6)
	{
		readToken();
	}
	return 1;

}

//<�������ʽ>�� <T> ��W1 <T>��
int Arithmetic_Expression()
{
	T();
	if (now_Token.type_id == 2 && (PT[now_Token.num] == "+" || PT[now_Token.num] == "-"))
	{
		readToken();
		T();
	}
	return 1;
}

//<T>��<F> ��W2 <F>��
int T()
{
	F();
	if (now_Token.type_id == 2 && (PT[now_Token.num] == "*" || PT[now_Token.num] == "/"))
	{
		readToken();
		F();
	}
	return 1;
}


//<F>��(<�������ʽ>)|<��ʶ��> |<����>|<ʵ��>
int F()
{
	if (now_Token.type_id == 2 && PT[now_Token.num] == "(")
	{
		readToken();
		Arithmetic_Expression();
		if (now_Token.type_id == 2 && PT[now_Token.num] == ")")
		{
			readToken();
			return 1;
		}
	}
	else if (now_Token.type_id == 3 || now_Token.type_id == 4)
	{
		readToken();
		return 1;
	}
	else if (now_Token.type_id == 2)	
	{
		readToken();
		return 1;
	}
	return 1;
}

//�߼����ʽ
int Logic_Expression()
{
	if (now_Token.type_id == 2 && (PT[now_Token.num] == "<" || 
		PT[now_Token.num] == "<=" || PT[now_Token.num] == ">" || 
		PT[now_Token.num] == ">=" || PT[now_Token.num] == "==" || 
		PT[now_Token.num] == "!="  ))
	{
		readToken();
		Arithmetic_Expression();
	}
	return 1;
}