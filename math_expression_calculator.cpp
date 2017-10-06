#include<iostream>
#include<map>
#include<string>
#include"CalculationFunction.h"
#include"OperatorExpression.h"

using namespace std;

int main() {
	map < string, function<double(double, double)>>map_binary_operator;		//存储二元运算符map
	map < string, function<double(double)>>map_unary_operator;				//储存一元运算符map
	map_insert_fun(map_binary_operator, map_unary_operator);					//将函数插入map
	DequeStack<string>infix;												//中值表达式
	DequeStack<string>postfix;												//后缀表达式
	print_help();															//打印帮助
	while (true) {		
		read_infix(cin, infix);										//将输入表达式转变为中值表达式
		trans_posfix(infix, postfix);									//将中值表达式转变为后缀表达式
		output_answer(calculat_postfix(postfix, map_binary_operator,		//计算后缀表达式
			map_unary_operator), infix, postfix);						//输出结果			
	}
	return 0;
}
