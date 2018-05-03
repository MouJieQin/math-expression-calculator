#pragma once
#ifndef _OPERATOREXPRESSION_H_
#define _OPERATOREXPRESSION_H_
#include<iostream>
#include<string>
#include<cctype>
#include<set>
#include"DequeStack.h"
using namespace std;

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
enum priority { Fifth_level,Fourth_level, Third_level, Second_level,First_level, Higtest };	//存储运算优先级
set<string>set_operator{ "+","-","*","/","%","^","(",")","!","|",",","A","C",":"};			//存储单个字符长度的运算符
static double answer=0;														//存储每次运行时的答案以用于下次计算
const static	string error = { "-*-*-*-*-*-*-输入错误-*-*-*-*--*-*-请重新输入-*-*-*-*-*-*-\t\t :( \n" };	//错误信息
bool input_error = false;												//运算错误标志位
long GCD = 0;															//记录最大公约数
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/*
*增加运算符需要在下面加入优先级
*/
map<string, priority>map_priority{												//存储运算优先级map
	{"+",Fifth_level },{ "-",Fifth_level },{ ",",Fifth_level },
	{"*",Fourth_level } ,{"/",Fourth_level } ,{ "%",Fourth_level },{":",Fourth_level },
	{ "sin",Third_level },{ "cos",Third_level },{ "tan",Third_level },
	{ "asin",Third_level },{ "acos",Third_level },{ "atan",Third_level },
	{ "sin_",Third_level },{ "cos_",Third_level },{ "tan_",Third_level },
	{ "asin_",Third_level },{ "acos_",Third_level },{ "atan_",Third_level },
	{ "|",Second_level },
	{"!",Second_level },{"ln",Second_level},{ "A",Second_level },{ "C",Second_level },
	{ "^",First_level },
	{ "(",Higtest },{ ")",Higtest }
};
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void read_infix(istream &in, DequeStack<string>&dequeStack_operator_operand) {		//读取中缀表达式
	string str_expression;
	while (in >> str_expression) {
		while (!str_expression.empty()) {				//字符串表达式为空时退出循环
			try {
				for (const auto &i : str_expression)
					if (i < -1 || i>255) {
						input_error = true;
						throw str_expression;
					}
			}
			catch (string err) {
				cerr <<'"'<< err<<'"'
					<< "是不兼容字符，请使用英文输入法!\t\t:>\n";
				break;
			}
			if (isdigit(str_expression.front())) {		//表达式首字符为数字时
				size_t index = 0;
				double operand = stod(str_expression, &index);	//将数字字符串转变为double，index 保存第一个不是数字的下标
				dequeStack_operator_operand.push_back(to_string(operand));	//压入操作数DequeStack<string>
				str_expression = str_expression.substr(index);	//将表达式截除转变为double的数字字符串
			}
			else {											//首字符不是数字
				string key = "";						//set.find()不能查找char
				key = str_expression.front() + key;
				if (set_operator.find(key) == set_operator.end()) {		//表达式首字符不在操作符set中
					string temp = "";
					size_t index = 0;
					while (
						index!=str_expression.size()					//确保索引在范围内
						&& !isdigit(str_expression[index])				//索引出的不是数字
						&& set_operator.find(key) == set_operator.end()	//索引出的不在操作符set中
						) {
						temp += str_expression[index++];				//递增索引提取字符
						key = "";
						key = str_expression[index] + key;
					}
		
					if(temp=="pi")dequeStack_operator_operand.push_back(to_string(3.1416));	//支持的特殊操作符				
					else if (temp == "e")dequeStack_operator_operand.push_back(to_string(2.7183));
					else if(temp=="anw")dequeStack_operator_operand.push_back(to_string(answer));
					else
						dequeStack_operator_operand.push_back(temp);	//压入操作符DequeStack<string>						
					str_expression = str_expression.substr(index);		//截取表达式
				}
				else {												//首字符在操作符set_operator中
					string temp = "";
					temp = str_expression.front() + temp;
					dequeStack_operator_operand.push_back(temp);
					str_expression = str_expression.substr(1);
				}
			}
		}
		break;
	}
	in.clear();
}

void trans_posfix(DequeStack<string>&infix, DequeStack<string>&postfix) {	//将中缀表达式转换为后缀表达式
	DequeStack<string>priority_operator;							//存储临时操作符用于比较优先级
	while (!infix.empty()) {		
		string first_element = infix.pop_front();	
		if (map_priority.find(first_element) == map_priority.end()) 	//首元素不是支持的操作符而是操作数
			postfix.push_back(first_element);
		else {														//首元素是支持的操作符			
			if (first_element == "(") {								//首元素是"("
				if (infix.front() == "-") {							//处理负数的减号是一元运算符的情况
					infix.pop_front();								//"("括号后是负号的为负数
					infix.front() = "-" + infix.front();
					}
					priority_operator.push_back(first_element);		//是"("时压入栈中
				}
				else if(first_element==")")				//首元素是")"时直到遇到"("才停止弹出，()不压入后缀表达式
					while (!priority_operator.empty()){						 
						string temp_operator = priority_operator.pop_back();
						if (temp_operator != "(") 
							postfix.push_back(temp_operator);						
						else
							break;
					}

				else {									//首元素不是"("或")"
					if (first_element == ",") {								//首元素是","
						if (infix.front() == "-") {							//处理负数的减号是一元运算符的情况
							infix.pop_front();								//","括号后是负号的为负数
							infix.front() = "-" + infix.front();		
						}
					}
					else {
						while (!priority_operator.empty()	//将临时操作符栈所有优先级大于等于首元素操作符的操作符弹出并压入后缀表达式
							&& map_priority[first_element] <= map_priority[priority_operator.back()]
							&& priority_operator.back() != "(") {	//"("只在遇到")"才弹出
							postfix.push_back(priority_operator.pop_back());
						}
						priority_operator.push_back(first_element);
					}
				}
		}
	}
	while (!priority_operator.empty())
		postfix.push_back(priority_operator.pop_back());
}

pair<bool,double> calculat_postfix(DequeStack<string>&postfix,				//计算后缀表达式
	map < string, function<double(double, double)>>&map_binary_operator,		//二元运算符map
	map<string, function<double(double)>>&map_unary_operator) {				//一元运算符map
	DequeStack<double>temp_stack;
	while (!postfix.empty()) {
		string temp_operator_operand = postfix.pop_front();
		if (map_unary_operator.find(temp_operator_operand) != map_unary_operator.end()) {	//弹出操作符为一元操作符
			try {
				if (temp_stack.empty()) 			//临时栈空了还有操作符没用完
					throw temp_operator_operand;
				else {
					double operand = temp_stack.pop_back();
					double answer_operand = map_unary_operator[temp_operator_operand](operand);
					temp_stack.push_back(answer_operand);
				}
			}
			catch (string err) {
				cerr << '"' << err << '"'
					<< "附近是否缺少括号!\t\t:>\n"
					<<"警告:操作符太多!!!\t\t:<"
					<< endl;
				input_error = true;										//输入错误标志位置位
				break;
			}
		}
		else if (map_binary_operator.find(temp_operator_operand) != map_binary_operator.end()) { //弹出操作符为二元操作符
			double answer_operand = 0;
			double second_operand = 0;
			try {
				if (temp_stack.empty()) 
					throw temp_operator_operand;
				else 
					second_operand = temp_stack.pop_back();			//弹出二元操作符的第二个操作数	
			}
			catch (string err) {
				cerr << '"' << err << '"'
					<< "附近是否缺少括号!\t\t:>\n"
					<< "警告:操作符太多!!!\t\t:<"
					<< endl;
				input_error = true;
				break;
			}
			if (temp_stack.empty()) {
				try {
					if (temp_operator_operand == "-")			//处理表达式第一个为负数的减号，此时减号为一元运算符
						answer_operand = -second_operand;
					else
						throw temp_operator_operand;
				}
				catch (string err) {
					cerr << '"' << err << '"'
						<< "附近是否缺少括号!\t\t:>\n"
						<< "警告:操作符太多!!!\t\t:<"
						<< endl;
					input_error = true;
					break;
				}
			}
			else {
				double first_operand = temp_stack.pop_back();
				answer_operand = map_binary_operator[temp_operator_operand](first_operand, second_operand);
			}
			temp_stack.push_back(answer_operand);
		}
		else {																	//弹出为操作数字符串
			try {
				double operand = 0;												//存放操作数
				if (temp_operator_operand.find_first_of("+-.0123456789") == string::npos)//操作数不为数字表明输入错误
					throw  temp_operator_operand;
				operand = stod(temp_operator_operand);							//转换为数字
				temp_stack.push_back(operand);									//压入临时计算栈
			}
			catch (string err) {
				cerr << '"' << err << '"'
					<< "是不支持操作符或与操作数不匹配!!!\t\t:<"
					<< endl;  
				input_error = true;
				break;
			}			
		}
	}
	if (input_error || temp_stack.empty()
		|| temp_stack.front() != temp_stack.back()) {//确保临时计算栈中只剩下唯一数字，否则运算错误
		if(!input_error)
			cerr << "操作数太多!!!\t\t:<" << endl;
		input_error = true;
		return make_pair(!input_error, 0.0);
	}
		
	return make_pair(!input_error, temp_stack.pop_back());					//返回运算错误标志位和结果
}

void output_answer(const pair<bool, double>&pair_answer,							//处理错误并输出答案
	DequeStack<string>&infix, DequeStack<string>&postfix) {	
	if (pair_answer.first) {												//运算正确
		answer = pair_answer.second;
		cout << "\t\tanw= \t"
			<< answer<< "\t\t :)"<<endl;
	}
	else {
		input_error = false;										//运算错误
		while (!postfix.empty())									//释放存储的后缀表达式才能重新用于下次计算
			postfix.pop_back();									
		while (!infix.empty())									//释放存储的中缀表达式才能重新用于下次计算
			infix.pop_back();
		cerr << error << endl;
	}
}
#endif	//_OPERATOREXPRESSION_H_

