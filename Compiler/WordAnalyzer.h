#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;


class WordAnalyze {
public:
    WordAnalyze(ifstream& file);
    void wordsdivide();//�ʷ�����
    void output(ofstream &file); //����ʷ��������
    void outeach(ofstream& file); //��������ֱ� ID ��sign
    map<pair<string, string>, pair<int, int>> ERRORLIST; //����λ�ú����
private:
    ifstream& sourceFile;           // Դ�����ļ�������
    friend class GrammerAnalyze;
    vector < pair< pair< string, string >,pair<int,int> > > Words; //�ʷ��������
    map<string, string> keep;//�����ֱ�
    set< string > IDs; //ID��
    set< string > Signs;//�ַ���
};
