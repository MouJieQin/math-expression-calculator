#pragma once
#ifndef _CALCULATIONFUNCTION_H
#define _CALCULATIONFUNCTION_H
#include<iostream>
#include<functional>
#include<cmath>

using namespace std;

void print_help() {															//打印帮助
	cout <<"*|-*-*-*-*-*-请使用英文输入法-*-*-*-*-*-*-*-不能有空格-*-*-*-*-*-*-*-*-*-*-*-*-*|\n"
		<<"*|1.请使用英文输入法输入表达式                                                 *|\n"
		<<"*|2.一个完整的表达式不能有空格和等号                                           *|\n"
		<<"*|3.请看第一条                                                                 *|\n"
		<<"*|支持的运算符有:                                                              *|\n"
		<<"*|+ - * / %(取余)  : (可用于求最大公因子化简分数)                              *|\n"
		<<"*|!(阶乘)  |()(取括号中绝对值)  ^(指数运算，可使用该符号开根号)                *|\n"
		<<"*|sin cos tan asin(反三角函数) acos atan pi(3.1416) e(2.7183)  ln(对数)        *|\n"
		<<"*|sin_ cos_ tan_ asin_ acos_ atan_ 带下划线正反三角函数使用角度,不带使用弧度   *|\n"
		<<"*|A(n,m) (n>=m,排列操作符)  C(n,m)(n>=m，组合操作符)                           *|\n"
		<<"*|示例如下:                                                                    *|\n"
		<<"*|输入:                                                                        *|\n"
		<<"*|8*(3-3)+sin(|(-pi/2))*sin_(30)+0.5*2^3                                       *|\n"
		<<"*|输出:                                                                        *|\n"
		<<"*|anw=     4.5                                                                 *|\n"
		<<"*|anw 可用于表达式,示例:                                                       *|\n"
		<<"*|2*anw                                                                        *|\n"
		<<"*|anw=   9                                                                     *|\n"
		<<"*|-*-*-*-*-*-不能有空格-*-*-*-*-*-*-*-请使用英文输入法-*-*-*-*-*-*-*-*--*-*-*-**|\n"
		<<endl;
}
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/*
*单元运算符原函数
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
function<double(double)>f_fact = [](double hs) {return fact(static_cast<long>(hs)); };   //阶乘运算
function<double(double)>f_ln = [](double hs) {return log(hs); };
function<double(double)>f_abs = [](double hs) {return hs > 0 ? hs : -hs; };
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/*
*双元运算符原函数
*/
function<double(double, double)>f_plus = [](double lhs, double rhs) {return lhs + rhs; };
function<double(double, double)>f_minus = [](double lhs, double rhs) {return lhs - rhs; };
function<double(double, double)>f_multi = [](double lhs, double rhs) {return lhs*rhs; };
function<double(double, double)>f_divi = [](double lhs, double rhs) {if (!rhs) { cerr << "警告:除数不能为零!\t\t:>" << endl; input_error =true; return 0.0; } return  lhs / rhs; };
function<double(double, double)>f_modu = [](double lhs, double rhs){return static_cast<int>(lhs) % static_cast<int>(rhs); };
function<double(double, double)>f_pow = [](double lhs, double rhs) {return pow(lhs, rhs); };
long fact_A(long lhs, long rhs) { if (lhs < rhs||lhs<=0||rhs<=0) { cerr << "警告:排列组合左操作数不能小于右操作数且必须大于0!\t\t:<" << endl; input_error = true; return 1; }return lhs == rhs ? lhs : lhs*fact_A(lhs - 1, rhs); };
function<double(double, double)>f_arrange = [](double lhs, double rhs) {return fact_A(static_cast<long>(lhs), static_cast<long>(lhs) - static_cast<long>(rhs) +1); };//排列函数
function<double(double, double)>f_comb = [](double lhs, double rhs) ->double{return f_arrange(lhs, rhs) / f_fact(rhs); };//组合函数
long common(long lhs, long rhs) { if (!rhs){cerr << "警告:除数不能为零!\t\t:>" << endl; input_error = true; return 0; }auto mod = lhs%rhs; return !mod ? rhs : common(rhs, mod); };
function<double(double, double)>f_comp = [](double lhs, double rhs) {if(rhs!=0)cout << "\t\tGCD=\t" << (lhs > rhs ? common(static_cast<long>(lhs), static_cast<long>(rhs)) : common(static_cast<long>(rhs), static_cast<long>(lhs))) << "\t\t:>"<<endl; return f_divi(lhs, rhs); };//求比函数
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
