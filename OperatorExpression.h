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
enum priority { Fifth_level,Fourth_level, Third_level, Second_level,First_level, Higtest };	//�洢�������ȼ�
set<string>set_operator{ "+","-","*","/","%","^","(",")","!","|",",","A","C",":"};			//�洢�����ַ����ȵ������
static double answer=0;														//�洢ÿ������ʱ�Ĵ��������´μ���
const static	string error = { "-*-*-*-*-*-*-�������-*-*-*-*--*-*-����������-*-*-*-*-*-*-\t\t :( \n" };	//������Ϣ
bool static input_error = false;												//��������־λ
long static GCD = 0;															//��¼���Լ��
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/*
*�����������Ҫ������������ȼ�
*/
map<string, priority>map_priority{												//�洢�������ȼ�map
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

void read_infix(istream &in, DequeStack<string>&dequeStack_operator_operand) {		//��ȡ��׺���ʽ
	string str_expression;
	while (in >> str_expression) {
		while (!str_expression.empty()) {				//�ַ������ʽΪ��ʱ�˳�ѭ��
			try {
				for (const auto &i : str_expression)
					if (i < -1 || i>255) {
						input_error = true;
						throw str_expression;
					}
			}
			catch (string err) {
				cerr <<'"'<< err<<'"'
					<< "�ǲ������ַ�����ʹ��Ӣ�����뷨!\t\t:>\n";
				break;
			}
			if (isdigit(str_expression.front())) {		//���ʽ���ַ�Ϊ����ʱ
				size_t index = 0;
				double operand = stod(str_expression, &index);	//�������ַ���ת��Ϊdouble��index �����һ���������ֵ��±�
				dequeStack_operator_operand.push_back(to_string(operand));	//ѹ�������DequeStack<string>
				str_expression = str_expression.substr(index);	//�����ʽ�س�ת��Ϊdouble�������ַ���
			}
			else {											//���ַ���������
				string key = "";						//set.find()���ܲ���char
				key = str_expression.front() + key;
				if (set_operator.find(key) == set_operator.end()) {		//���ʽ���ַ����ڲ�����set��
					string temp = "";
					size_t index = 0;
					while (
						index!=str_expression.size()					//ȷ�������ڷ�Χ��
						&& !isdigit(str_expression[index])				//�������Ĳ�������
						&& set_operator.find(key) == set_operator.end()	//�������Ĳ��ڲ�����set��
						) {
						temp += str_expression[index++];				//����������ȡ�ַ�
						key = "";
						key = str_expression[index] + key;
					}
		
					if(temp=="pi")dequeStack_operator_operand.push_back(to_string(3.1416));	//֧�ֵ����������				
					else if (temp == "e")dequeStack_operator_operand.push_back(to_string(2.7183));
					else if(temp=="anw")dequeStack_operator_operand.push_back(to_string(answer));
					else
						dequeStack_operator_operand.push_back(temp);	//ѹ�������DequeStack<string>						
					str_expression = str_expression.substr(index);		//��ȡ���ʽ
				}
				else {												//���ַ��ڲ�����set_operator��
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

void trans_posfix(DequeStack<string>&infix, DequeStack<string>&postfix) {	//����׺���ʽת��Ϊ��׺���ʽ
	DequeStack<string>priority_operator;							//�洢��ʱ���������ڱȽ����ȼ�
	while (!infix.empty()) {		
		string first_element = infix.pop_front();	
		if (map_priority.find(first_element) == map_priority.end()) 	//��Ԫ�ز���֧�ֵĲ��������ǲ�����
			postfix.push_back(first_element);
		else {														//��Ԫ����֧�ֵĲ�����			
			if (first_element == "(") {								//��Ԫ����"("
				if (infix.front() == "-") {							//�������ļ�����һԪ����������
					infix.pop_front();								//"("���ź��Ǹ��ŵ�Ϊ����
					infix.front() = "-" + infix.front();
					}
					priority_operator.push_back(first_element);		//��"("ʱѹ��ջ��
				}
				else if(first_element==")")				//��Ԫ����")"ʱֱ������"("��ֹͣ������()��ѹ���׺���ʽ
					while (!priority_operator.empty()){						 
						string temp_operator = priority_operator.pop_back();
						if (temp_operator != "(") 
							postfix.push_back(temp_operator);						
						else
							break;
					}

				else {									//��Ԫ�ز���"("��")"
					if (first_element == ",") {								//��Ԫ����","
						if (infix.front() == "-") {							//�������ļ�����һԪ����������
							infix.pop_front();								//","���ź��Ǹ��ŵ�Ϊ����
							infix.front() = "-" + infix.front();		
						}
					}
					else {
						while (!priority_operator.empty()	//����ʱ������ջ�������ȼ����ڵ�����Ԫ�ز������Ĳ�����������ѹ���׺���ʽ
							&& map_priority[first_element] <= map_priority[priority_operator.back()]
							&& priority_operator.back() != "(") {	//"("ֻ������")"�ŵ���
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

pair<bool,double> calculat_postfix(DequeStack<string>&postfix,				//�����׺���ʽ
	map < string, function<double(double, double)>>&map_binary_operator,		//��Ԫ�����map
	map<string, function<double(double)>>&map_unary_operator) {				//һԪ�����map
	DequeStack<double>temp_stack;
	while (!postfix.empty()) {
		string temp_operator_operand = postfix.pop_front();
		if (map_unary_operator.find(temp_operator_operand) != map_unary_operator.end()) {	//����������ΪһԪ������
			try {
				if (temp_stack.empty()) 			//��ʱջ���˻��в�����û����
					throw temp_operator_operand;
				else {
					double operand = temp_stack.pop_back();
					double answer_operand = map_unary_operator[temp_operator_operand](operand);
					temp_stack.push_back(answer_operand);
				}
			}
			catch (string err) {
				cerr << '"' << err << '"'
					<< "�����Ƿ�ȱ������!\t\t:>\n"
					<<"����:������̫��!!!\t\t:<"
					<< endl;
				input_error = true;										//��������־λ��λ
				break;
			}
		}
		else if (map_binary_operator.find(temp_operator_operand) != map_binary_operator.end()) { //����������Ϊ��Ԫ������
			double answer_operand = 0;
			double second_operand = 0;
			try {
				if (temp_stack.empty()) 
					throw temp_operator_operand;
				else 
					second_operand = temp_stack.pop_back();			//������Ԫ�������ĵڶ���������	
			}
			catch (string err) {
				cerr << '"' << err << '"'
					<< "�����Ƿ�ȱ������!\t\t:>\n"
					<< "����:������̫��!!!\t\t:<"
					<< endl;
				input_error = true;
				break;
			}
			if (temp_stack.empty()) {
				try {
					if (temp_operator_operand == "-")			//������ʽ��һ��Ϊ�����ļ��ţ���ʱ����ΪһԪ�����
						answer_operand = -second_operand;
					else
						throw temp_operator_operand;
				}
				catch (string err) {
					cerr << '"' << err << '"'
						<< "�����Ƿ�ȱ������!\t\t:>\n"
						<< "����:������̫��!!!\t\t:<"
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
		else {																	//����Ϊ�������ַ���
			try {
				double operand = 0;												//��Ų�����
				if (temp_operator_operand.find_first_of("+-.0123456789") == string::npos)//��������Ϊ���ֱ����������
					throw  temp_operator_operand;
				operand = stod(temp_operator_operand);							//ת��Ϊ����
				temp_stack.push_back(operand);									//ѹ����ʱ����ջ
			}
			catch (string err) {
				cerr << '"' << err << '"'
					<< "�ǲ�֧�ֲ����������������ƥ��!!!\t\t:<"
					<< endl;  
				input_error = true;
				break;
			}			
		}
	}
	if (input_error || temp_stack.empty()
		|| temp_stack.front() != temp_stack.back()) {//ȷ����ʱ����ջ��ֻʣ��Ψһ���֣������������
		if(!input_error)
			cerr << "������̫��!!!\t\t:<" << endl;
		input_error = true;
		return make_pair(!input_error, 0.0);
	}
		
	return make_pair(!input_error, temp_stack.pop_back());					//������������־λ�ͽ��
}

void output_answer(pair<bool, double>&pair_answer,							//������������
	DequeStack<string>&infix, DequeStack<string>&postfix) {	
	if (pair_answer.first) {												//������ȷ
		answer = pair_answer.second;
		cout << "\t\tanw= \t"
			<< answer<< "\t\t :)"<<endl;
	}
	else {
		input_error = false;										//�������
		while (!postfix.empty())									//�ͷŴ洢�ĺ�׺���ʽ�������������´μ���
			postfix.pop_back();									
		while (!infix.empty())									//�ͷŴ洢����׺���ʽ�������������´μ���
			infix.pop_back();
		cerr << error << endl;
	}
}
#endif	//_OPERATOREXPRESSION_H_

