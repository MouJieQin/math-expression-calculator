#pragma once
#ifndef _FUN_H_
#define _FUN_H_
#include<iostream>
#include<map>
#include<string>

#include"CalculationFunction.h"

using namespace std;

void map_insert_fun(map < string, function<double(double, double)>>&map_clacu) {
	map_clacu.insert({ "+",f_plus });
	map_clacu.insert({ "-",f_minus });
	map_clacu.insert({ "*",f_multi });
	map_clacu.insert({ "/",f_divi });
	map_clacu.insert({ "%",f_modu });
	map_clacu.insert({ "sin",f_sin });
	map_clacu.insert({ "cos",f_cos });
	map_clacu.insert({ "tan",f_tan });
	map_clacu.insert({ "sin()",f_sin_ });
	map_clacu.insert({ "cos()",f_cos_ });
	map_clacu.insert({ "tan()",f_tan_ });
	map_clacu.insert({ "asin",f_asin });
	map_clacu.insert({ "acos",f_acos });
	map_clacu.insert({ "atan",f_atan });
	map_clacu.insert({ "asin()",f_asin_ });
	map_clacu.insert({ "acos()",f_acos_ });
	map_clacu.insert({ "atan()",f_atan_ });
	map_clacu.insert({ "pow",f_pow });
	map_clacu.insert({ "root",f_root });
}

bool input_expr(istream &is, double &lhs, string &operate, double &rhs) {
	is >> lhs >> operate >> rhs;
	if (!is) {
		is.clear();
		is.ignore(100, '\n');
		cerr << "-*-*-*-*-输入错误-*-*-*-*-注意空格-*-*-*-*-可能不支持该运算符-*-*-*-*-请使用英文输入法-*-*-*-*-请重新输入-*-*-*-*-" << endl;
		return  false;
	}
	return true;
}

void output_anw(ostream &os,map<string,function<double(double,double)>>&map_clacu, double &lhs, string &operate, double &rhs,double &result) {
	if(map_clacu.find(operate)==map_clacu.end())
		cerr << "-*-*-*-*-输入错误-*-*-*-*-注意空格-*-*-*-*-可能不支持该运算符-*-*-*-*-请使用英文输入法-*-*-*-*-请重新输入-*-*-*-*-" << endl;
	else {
		result = map_clacu[operate](lhs, rhs);
		os << "\t" << "r=" << "\t" << result << endl;
	}
}

#endif _FUN_H_
