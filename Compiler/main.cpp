#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "WordAnalyzer.h"
#include "GrammerAnalyzer.h"
#include "Explain.h"
using namespace std;

int main()
{
	string file_name;
	cout << "请输入测试文件名称" << endl;
	cin >> file_name;
	ifstream fin;
	fin.open("../test/" + file_name, ios::in);// 打开源程序文件
	if (!fin.is_open()) {   // 检查文件是否成功打开，如否，报错并退出程序
		cerr << "无法打开文件 " << file_name << endl;
		cerr << "请检查文件名称和位置是否正确" << endl;
		return 0;
	}

	//词法分析
	WordAnalyze word(fin);
	word.wordsdivide();
	ofstream fout;
	fout.open("../result/" + file_name  + "_Wordresule.txt", ios::out);
	word.output(fout);
	if (!word.ERRORLIST.empty())
	{
		cout << "词法分析有错误，请检查代码对应位置";
		return 0;
	}
	ofstream fout_d;
	fout_d.open("../result/" + file_name + "_Worddivid.txt", ios::out);
	word.outeach(fout_d);
	//语法分析
	GrammerAnalyze grammer(word);
	grammer.grammeranalyze();
	ofstream fout_grammer;
	fout_grammer.open("../result/" + file_name + "_Grammerresule.txt", ios::out);
	grammer.outputfour(fout_grammer);

	fin.close();
	fout.close();
	fout_grammer.close();
	fout.close();
	return 0;
}