#include<iostream>
#include<map>
#include<string>
#include"CalculationFunction.h"
#include"OperatorExpression.h"

using namespace std;

int main() {
	map < string, function<double(double, double)>>map_binary_operator;		//�洢��Ԫ�����map
	map < string, function<double(double)>>map_unary_operator;				//����һԪ�����map
	map_insert_fun(map_binary_operator, map_unary_operator);					//����������map
	DequeStack<string>infix;												//��ֵ���ʽ
	DequeStack<string>postfix;												//��׺���ʽ
	print_help();															//��ӡ����
	while (true) {		
		read_infix(cin, infix);										//��������ʽת��Ϊ��ֵ���ʽ
		trans_posfix(infix, postfix);									//����ֵ���ʽת��Ϊ��׺���ʽ
		output_answer(calculat_postfix(postfix, map_binary_operator,		//�����׺���ʽ
			map_unary_operator), infix, postfix);						//������			
	}
	return 0;
}
