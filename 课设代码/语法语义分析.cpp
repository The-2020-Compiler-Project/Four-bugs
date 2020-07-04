#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include "符号表结构.h"
#include "函数名.h"

using namespace std;


TOKEN now_Token;	//当前的读取token
int flag=1;			//检查语法分析是否正确的标志，默认为1，分析错误则变为0
int i;				//now_token读写头


/************************************    测试部分   ************************************************/

vector<TOKEN> tok;	//测试用的token序列

//测试函数
void int_it()
{
	/*
	int max(int a,int b);

	int max(int a,int b)
	{
		if(a<b)
		{
			return b;
		}
		else
		{
			return a;
		}
	}

	int main()
	{
		int a;
		a = 3 * 5;
		int b, c;
		b = 5 * (1 + 1);
		c = a + b;
		if (a < b)
		{
			a = a + 1;
		}
		while (a <= b)
		{
			c = a + b;
		}
		a = max(b, c);
		return 1;
	}
	*/

	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,3 });//max
	tok.push_back({ 2,13 });//(
	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,12 });//,
	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,11 });//;
	
	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,3 });//max
	tok.push_back({ 2,13 });//(
	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,12 });//,
	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,17 });//{
	tok.push_back({ 0,4 });//if
	tok.push_back({ 2,13 });//(
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,4 });//<
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,17 });//{
	tok.push_back({ 0,8 });//return
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,11 });//;
	tok.push_back({ 2,18 });//}
	tok.push_back({ 0,5 });//else
	tok.push_back({ 2,17 });//{
	tok.push_back({ 0,8 });//return
	tok.push_back({ 1,0 });//0
	tok.push_back({ 2,11 });//;
	tok.push_back({ 2,18 });//}
	tok.push_back({ 2,18 });//}
	
	tok.push_back({ 0,1 });//int
	tok.push_back({ 0,0 });//main
	tok.push_back({ 2,13 });//(
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,17 });//{
	
	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,11 });//;
	
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,8 });//=
	tok.push_back({ 3,0 });//3
	tok.push_back({ 2,2 }); //*
	tok.push_back({ 3,1 });//5
	tok.push_back({ 2,11 }); //;
	
	tok.push_back({ 0,1 });//int
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,12 });//,
	tok.push_back({ 1,2 });//c
	tok.push_back({ 2,11 });//;
	
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,8 });//=
	tok.push_back({ 3,1 });//5
	tok.push_back({ 2,2 });//*
	tok.push_back({ 2,13 });//(
	tok.push_back({ 3,2 });//1
	tok.push_back({ 2,0 });//+
	tok.push_back({ 3,2 });//1
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,11 });//;
	
	tok.push_back({ 1,2 });//c
	tok.push_back({ 2,8 });//=
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,0 });//+
	tok.push_back({ 1,2 });//c
	tok.push_back({ 2,11 });//;
	
	tok.push_back({ 0,4 });//if
	tok.push_back({ 2,13 });//(
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,4 });//<
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,17 });//{
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,8 });//=
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,0 });//+
	tok.push_back({ 3,2 });//1
	tok.push_back({ 2,11 });//;
	tok.push_back({ 2,18 });//}
	
	tok.push_back({ 0,6 });//while
	tok.push_back({ 2,13 });//(
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,6 });//<=
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,0 });//+
	tok.push_back({ 1,2 });//c
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,17 });//{
	tok.push_back({ 1,2 });//c
	tok.push_back({ 2,8 });//=
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,0 });//+
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,11 });//;
	tok.push_back({ 2,18 });//}
	
	tok.push_back({ 1,0 });//a
	tok.push_back({ 2,8 });//=
	tok.push_back({ 1,3 });//max
	tok.push_back({ 2,13 });//(
	tok.push_back({ 1,1 });//b
	tok.push_back({ 2,12 });//,
	tok.push_back({ 1,2 });//c
	tok.push_back({ 2,14 });//)
	tok.push_back({ 2,11 });//;

	tok.push_back({ 0,8 });//return
	tok.push_back({ 3,2 });//1
	tok.push_back({ 2,11 });//;
	tok.push_back({ 2,18 });//}


	/*
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	tok.push_back({  });//
	*/

}



/************************************    测试部分   ************************************************/









//初始化now_Token，使now_Token指向第一个token
int int_token()
{
	i = 0;
	now_Token = tok.at(i);
	return 1;
}

//now_Token指向下一个token
void readToken()
{
	i++;
	now_Token = tok.at(i);
}


//程序开始
void run() 
{   
	int_it();
	int_token();
	Source();
	if (flag == 1) 
	{  
		cout << "语法分析完成，没有错误！" << endl;	
	}
	else if (flag == 0)
	{
		cout << "语法分析过程中存在错误！" << endl;
	}
	else
	{
		cout << "错误标志flag结果错误！" << endl;
	}

}

//<源程序>→<开始>
int Source()
{
	begin();
	return 1;
}

//<开始>→<数据类型><主函数>|<数据类型><外部定义>
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
			cout << "函数名缺少或函数名定义错误！" << endl;
			flag = 0;
		}
	}
	else
	{
		cout << "函数缺少类型符！" << endl;
		flag = 0;
	}
	return 1;
}

//<主函数>→main ( ) {<复合语句>}
int main_function()
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "main")
	{
		readToken();
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
						cout << "主函数定义缺少 } 右花括号！" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "主函数定义缺少 } 右花括号！" << endl;
					flag = 0;
				}

			}
			else
			{
				cout << "主函数定义中缺少 ） 右括号！" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "主函数定义中缺少 ( 左括号！" << endl;
			flag = 0;
		}
	}
	return 1;
}

//<外部定义>→<函数头>;<开始>|<函数头>{<复合语句>}<开始>
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
			cout << "函数定义缺少 } 右花括号！" << endl;
			flag = 0;
		}
	}
	else
	{
		cout << "外部定义存在错误！" << endl;
		flag = 0;
	}
	return 1;
}

//<函数头>→<标识符>(<形参>)
int function_header()
{
	if (now_Token.type_id == 1)
	{
		readToken();
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
				cout << "函数定义中缺少 ） 右括号！" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "函数定义中缺少 ( 左括号！" << endl;
			flag = 0;
		}
	}
	
	return 1;
}


//<形参>→<数据类型><标识符>|<数据类型><标识符>,<形参>
int Formal()
{
	if (now_Token.type_id == 0 && (KT[now_Token.num] == "int" || KT[now_Token.num] == "char" || KT[now_Token.num] == "float"))
	{
		readToken();
		if (now_Token.type_id == 1)
		{
			readToken();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ",")
			{
				readToken();
				Formal();
			}
		}
		else
		{
			cout << "定义的形参为非标识符！" << endl;
			flag = 0;
		}
	}
	else
	{
		cout << "数据类型定义错误！" << endl;
		flag = 0;
	}
	return 1;
}


//<复合语句>→<变量声明><复合语句> | <赋值、函数调用语句><复合语句> | <选择语句><复合语句> | <循环语句><复合语句> | <返回语句><复合语句> | ε
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
		Back();
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



//<变量声明>→<数据类型><标识符>；|<数据类型><标识符>，<标识符列表>；|<数据类型><标识符><数组列表>;
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
				readToken();
				dentifier();
				if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
				{
					readToken();
					return 1;
				}
				else
				{
					cout << "变量声明缺少 ; 分号！" << endl;
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
					cout << "变量声明缺少 ; 分号！" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "变量声明缺少 ; 分号！" << endl;
				flag = 0;
			}
			
		}
		
	}
	else
	{
		cout << "变量声明错误！" << endl;
		flag = 0;
	}
	return 1;
}

//<标识符列表>→<标识符> | <标识符>,<标识符列表>
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
		cout << "标识符定义失败！" << endl;
		flag = 0;
	}
	return 1;
}

//<数组列表>→[<算术表达式>] | ，<标识符>[<算术表达式>]<数组列表1>
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
			cout << "数组定义缺少 ] 右方括号！" << endl;
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
					cout << "数组定义缺少 ] 右方括号！" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "数组定义缺少 [ 左方括号！" << endl;
				flag = 0;
			}
		}
	}
	return 1;
}



//<选择语句>→if(<表达式>){<复合语句>}【else(<表达式>){<复合语句>}】
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
									cout << "选择语句缺少 } 右花括号！" << endl;
									flag = 0;
								}
							}
							else
							{
								cout << "选择语句缺少 { 左花括号！" << endl;
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
						cout << "选择语句缺少 } 右花括号！" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "选择语句缺少 { 左花括号！" << endl;
					flag = 0;
				}
			}
		}
		else
		{
			cout << "选择语句缺少 （ 左括号！" << endl;
			flag = 0;
		}
	}
	else
		return 1;
}

//<循环语句>→while(<表达式>){<复合语句>}
int Cycle()
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "while")
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
						cout << "循环语句缺少 } 右花括号！" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "循环语句缺少 { 左花括号！" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "循环语句缺少） 右括号！" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "循环语句缺少（ 左括号！" << endl;
			flag = 0;
		}
	}
	return 1;
}

//<返回语句>→return<标识符>;|return<整型常量>;
int Back()
{
	if (now_Token.type_id == 0 && KT[now_Token.num] == "return")
	{
		readToken();
		if (now_Token.type_id == 1 || now_Token.type_id == 3)
		{
			readToken();
			if (now_Token.type_id == 2 && PT[now_Token.num] == ";")
			{
				readToken();
				return 1;
			}
			else
			{
				cout << "缺少 ; 分号！" << endl;
				flag = 0;
			}
		}
		else
		{
			cout << "返回值非标识符或整数常量！" << endl;
			flag = 0;
		}
	}
	return 1;
}

//<赋值、函数调用语句>→ < 标识符 >= <表达式>； | < 标识符 >= <标识符>(<实参>); | <标识符>(<实参>);
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
						cout << "缺少 ; 分号！" << endl;
						flag = 0;
					}
				}
				else
				{
					cout << "缺少 ） 反括号！" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "赋值或函数调用错误！" << endl;
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
					cout << "缺少 ; 分号！" << endl;
					flag = 0;
				}
			}
			else
			{
				cout << "缺少 ） 反括号！" << endl;
				flag = 0;
			}
		}
	}
	else
	{
		cout << "赋值或函数调用错误！" << endl;
		flag = 0;
	}
	return 1;
}

//<实参>→<标识符>|<标识符>,<实参>
int Actual()
{
	if (now_Token.type_id == 1)
	{
		readToken();
		if (now_Token.type_id == 2 && PT[now_Token.num] == ",")
		{
			readToken();
			Actual();
		}
	}
	else
	{
		cout << "函数实参定义错误！" << endl;
		flag = 0;
	}
	return 1;
}


//<表达式>→<算术表达式>|<逻辑表达式>|<字符常量>|<字符串常量>
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

//<算数表达式>→ <T> 【W1 <T>】
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

//<T>→<F> 【W2 <F>】
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


//<F>→(<算术表达式>)|<标识符> |<整数>|<实数>
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
	else if (now_Token.type_id == 3 || now_Token.type_id == 4 || now_Token.type_id == 1)
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

//逻辑表达式
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
