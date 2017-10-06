#pragma once
#ifndef _CALCULATIONFUNCTION_H
#define _CALCULATIONFUNCTION_H
#include<iostream>
#include<functional>
#include<cmath>

using namespace std;

void print_help() {															//��ӡ����
	cout <<"*|-*-*-*-*-*-��ʹ��Ӣ�����뷨-*-*-*-*-*-*-*-�����пո�-*-*-*-*-*-*-*-*-*-*-*-*-*|\n"
		<<"*|1.��ʹ��Ӣ�����뷨������ʽ                                                 *|\n"
		<<"*|2.һ�������ı��ʽ�����пո�͵Ⱥ�                                           *|\n"
		<<"*|3.�뿴��һ��                                                                 *|\n"
		<<"*|֧�ֵ��������:                                                              *|\n"
		<<"*|+ - * / %(ȡ��)  : (��������������ӻ������)                              *|\n"
		<<"*|!(�׳�)  |()(ȡ�����о���ֵ)  ^(ָ�����㣬��ʹ�ø÷��ſ�����)                *|\n"
		<<"*|sin cos tan asin(�����Ǻ���) acos atan pi(3.1416) e(2.7183)  ln(����)        *|\n"
		<<"*|sin_ cos_ tan_ asin_ acos_ atan_ ���»����������Ǻ���ʹ�ýǶ�,����ʹ�û���   *|\n"
		<<"*|A(n,m) (n>=m,���в�����)  C(n,m)(n>=m����ϲ�����)                           *|\n"
		<<"*|ʾ������:                                                                    *|\n"
		<<"*|����:                                                                        *|\n"
		<<"*|8*(3-3)+sin(|(-pi/2))*sin_(30)+0.5*2^3                                       *|\n"
		<<"*|���:                                                                        *|\n"
		<<"*|anw=     4.5                                                                 *|\n"
		<<"*|anw �����ڱ��ʽ,ʾ��:                                                       *|\n"
		<<"*|2*anw                                                                        *|\n"
		<<"*|anw=   9                                                                     *|\n"
		<<"*|-*-*-*-*-*-�����пո�-*-*-*-*-*-*-*-��ʹ��Ӣ�����뷨-*-*-*-*-*-*-*-*--*-*-*-**|\n"
		<<endl;
}
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/*
*��Ԫ�����ԭ����
*/
extern bool input_error;
extern long GCD;
const double rad = 3.1416 / 180.0;
const double ang = 180.0 / 3.1416;
function<double(double)>f_sin = [](double hs) {return sin(hs); };
function<double(double)>f_cos= [](double hs) {return cos(hs); };
function<double(double)>f_tan = [](double hs) {return tan(hs); };
function<double(double)>f_sin_ = [](double hs){ return sin(hs*rad); };
function<double(double)>f_cos_ = [](double hs) {return cos(hs*rad); };
function<double(double)>f_tan_ = [](double hs) {return tan(hs*rad); };
function<double(double)>f_asin = [](double hs) {return asin(hs); };
function<double(double)>f_acos = [](double hs) {return acos(hs); };
function<double(double)>f_atan = [](double hs) {return atan(hs); };
function<double(double)>f_asin_ = [](double hs) {return asin(hs)*ang; };
function<double(double)>f_acos_ = [](double hs) {return acos(hs)*ang; };
function<double(double)>f_atan_ = [](double hs) {return atan(hs)*ang; };
long fact(long hs) { return hs <= 1 ? 1 : hs*fact(hs - 1); }							
function<double(double)>f_fact = [](double hs) {return fact(static_cast<long>(hs)); };   //�׳�����
function<double(double)>f_ln = [](double hs) {return log(hs); };
function<double(double)>f_abs = [](double hs) {return hs > 0 ? hs : -hs; };
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/*
*˫Ԫ�����ԭ����
*/
function<double(double, double)>f_plus = [](double lhs, double rhs) {return lhs + rhs; };
function<double(double, double)>f_minus = [](double lhs, double rhs) {return lhs - rhs; };
function<double(double, double)>f_multi = [](double lhs, double rhs) {return lhs*rhs; };
function<double(double, double)>f_divi = [](double lhs, double rhs) {if (!rhs) { cerr << "����:��������Ϊ��!\t\t:>" << endl; input_error =true; return 0.0; } return  lhs / rhs; };
function<double(double, double)>f_modu = [](double lhs, double rhs){return static_cast<int>(lhs) % static_cast<int>(rhs); };
function<double(double, double)>f_pow = [](double lhs, double rhs) {return pow(lhs, rhs); };
long fact_A(long lhs, long rhs) { if (lhs < rhs||lhs<=0||rhs<=0) { cerr << "����:������������������С���Ҳ������ұ������0!\t\t:<" << endl; input_error = true; return 1; }return lhs == rhs ? lhs : lhs*fact_A(lhs - 1, rhs); };
function<double(double, double)>f_arrange = [](double lhs, double rhs) {return fact_A(static_cast<long>(lhs), static_cast<long>(lhs) - static_cast<long>(rhs) +1); };//���к���
function<double(double, double)>f_comb = [](double lhs, double rhs) ->double{return f_arrange(lhs, rhs) / f_fact(rhs); };//��Ϻ���
long common(long lhs, long rhs) { if (!rhs){cerr << "����:��������Ϊ��!\t\t:>" << endl; input_error = true; return 0; }auto mod = lhs%rhs; return !mod ? rhs : common(rhs, mod); };
function<double(double, double)>f_comp = [](double lhs, double rhs) {if(rhs!=0)cout << "\t\tGCD=\t" << (lhs > rhs ? common(static_cast<long>(lhs), static_cast<long>(rhs)) : common(static_cast<long>(rhs), static_cast<long>(lhs))) << "\t\t:>"<<endl; return f_divi(lhs, rhs); };//��Ⱥ���
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void map_insert_fun(map < string, function<double(double, double)>>&map_binary_operator,
	map<string, function<double(double)>>&map_unary_operator) {
	map_binary_operator.insert({ "+",f_plus });
	map_binary_operator.insert({ "-",f_minus });
	map_binary_operator.insert({ "*",f_multi });
	map_binary_operator.insert({ "/",f_divi });
	map_binary_operator.insert({ "%",f_modu });
	map_binary_operator.insert({ "^",f_pow });
	map_binary_operator.insert({ "A",f_arrange });
	map_binary_operator.insert({ "C",f_comb });
	map_binary_operator.insert({ ":",f_comp });
	map_unary_operator.insert({ "sin",f_sin });
	map_unary_operator.insert({ "cos",f_cos });
	map_unary_operator.insert({ "tan",f_tan });
	map_unary_operator.insert({ "sin_",f_sin_ });
	map_unary_operator.insert({ "cos_",f_cos_ });
	map_unary_operator.insert({ "tan_",f_tan_ });
	map_unary_operator.insert({ "asin",f_asin });
	map_unary_operator.insert({ "acos",f_acos });
	map_unary_operator.insert({ "atan",f_atan });
	map_unary_operator.insert({ "asin_",f_asin_ });
	map_unary_operator.insert({ "acos_",f_acos_ });
	map_unary_operator.insert({ "atan_",f_atan_ });
	map_unary_operator.insert({ "!",f_fact });
	map_unary_operator.insert({ "ln",f_ln });
	map_unary_operator.insert({ "|",f_abs });
}
#endif //_CALCULATIONFUNCTION_H
