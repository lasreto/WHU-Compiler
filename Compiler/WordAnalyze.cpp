#include <ctype.h>
#include <map>
#include <string>
#include <set>
#include <iomanip>
#include <stack>
#include "WordAnalyzer.h"
using namespace std;

char ch;       //��ǰδ������ַ�
bool read = false;
int temp;
string string_get; //�������ַ���
string sym;
pair<int, int> position(1,1);             //������ǰ��ȡ����λ�� <�У���>
WordAnalyze::WordAnalyze(ifstream& file) : sourceFile(file) {
    keep.insert({ "int","INT" });
    keep.insert({ "while", "WHILE" });
    keep.insert({ "do","DO" });
    keep.insert({ "else","ELSE" });
    keep.insert({ "if","IF" });
    keep.insert({ "then","THEN" });
    keep.insert({ "scanf","SCANF" });
    keep.insert({ "printf","PRINTF" });
    keep.insert({ "include","INCLUDE" });
    keep.insert({ "iostream","IOSTREAM" });
    keep.insert({ "for","FOR" });
    keep.insert({ "char","CHAR" });
    keep.insert({ "string","STRING" });
    keep.insert({ "main","MAIN" });
    //���뱣����
}

#define GET     ch = sourceFile.get()   // ����꣬�򻯴��ļ��ж�ȡһ���ַ��Ĳ���
#define PEEK    ch = sourceFile.peek()  // ����꣬�򻯲鿴�ļ�����һ���ַ��Ĳ���
#define ADD(c)  string_get.append(1, c)     // ����꣬�����ַ�����β����ַ��Ĳ���

void WordAnalyze::wordsdivide()
{
    pair <string, string> newitem;
    pair < pair <string, string>, pair<int, int> > wordcheck;
#define PUSH(s1,s2) newitem =  make_pair(s1,s2);\
wordcheck = make_pair(newitem,position);\
Words.push_back(wordcheck);
	GET;
    while (ch != EOF) //
    {
        while (isspace(ch)) //ȥ���ո�
        {
            if (ch == ' ')
            {
                position.second++;
            }
            else if (ch == '\n')
            {
                position.first++;
                position.second = 1;
            }
            GET;
        }
        if (isdigit(ch))
        {                   
            temp = ch - '0';            
            for (GET; isdigit(ch); GET)
            {
                temp = temp * 10 + ch - '0';
                position.second++;
            }
            PUSH(to_string(temp), "NUM");
        }
        else if (isalpha(ch))
        {
            string_get.clear();
            ADD(ch);
            for (GET; isalnum(ch); GET)
            {
                ADD(ch);//��ȡ�������ַ���
                position.second++;
            }

            map<string, string>::iterator it = keep.find(string_get);
            if (it == keep.end())
            {// ���ڱ����ֱ��У�˵���Ǳ�ʶ��
                PUSH(string_get, "ID");
                IDs.insert(string_get);//����õ���ID����ID����
            }
            else
            {// �ڱ����ֱ���
                PUSH(it->first, it->second);
            }
        }
        else
        {
            switch (ch)
            {
                // ���£������ switch ���У�ÿһ�����ִ����֮�󣬶�ʹ�� ch �Ǵ�������ַ�
                // ����� switch �����棬ͳһ�ٶ�һ�����ַ�����
            case '&':
                string_get.clear();
                ADD(ch);
                PEEK;
                if (ch == '&')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "&&");
                    Signs.insert("&&");
                    position.second++;
                    break;
                }
                else
                {
                    PUSH(string_get, "&");
                    Signs.insert("&");
                    break;
                }
            case '|':
                string_get.clear();
                ADD(ch);
                PEEK;
                if (ch == '|')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "||");
                    Signs.insert("||");
                    position.second++;
                    break;
                }
                else
                {
                    PUSH(string_get, "|");
                    Signs.insert("|");
                    break;
                }
            case '(':
                PUSH("(", "(");
                Signs.insert("(");
                break;
            case ')':
                PUSH(")", ")");
                Signs.insert(")");
                break;
            case ';':
                PUSH(";", ";");
                Signs.insert(";");
                break;
            case '+':
                string_get.clear();
                ADD(ch);
                PEEK;
                if (ch == '=')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "+=");
                    Signs.insert("+=");
                    position.second++;
                    break;
                }
                else
                {
                    PUSH(string_get, "+");
                    Signs.insert("+");
                    break;
                }
            case '-':
                string_get.clear();
                ADD(ch);
                PEEK;
                if (ch == '=')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "-=");
                    Signs.insert("-=");
                    position.second++;
                    break;
                }
                else if (isdigit(ch))
                {
                    GET;
                    temp = ch - '0';            // �������ַ�ת��Ϊ����
                    for (GET; isdigit(ch); GET)
                    {
                        temp = temp * 10 + ch - '0';
                        position.second++;
                    }
                    PUSH( "-" + to_string(temp), "NUM");
                    read = true;
                    break;
                }
                else
                {
                    PUSH(string_get, "-");
                    Signs.insert("-");
                    break;
                }
            case '*':
                string_get.clear();
                ADD(ch);
                PEEK;
                if (ch == '=')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "*=");
                    Signs.insert("*=");
                    position.second++;
                    break;
                }
                else
                {
                    PUSH(string_get, "*");
                    Signs.insert("*");
                    break;
                }
            case '/':
                string_get.clear();
                ADD(ch);
                PEEK;
                if (ch == '=')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "/=");
                    Signs.insert("/=");
                    position.second++;
                    break;
                }
                else
                {
                    PUSH(string_get, "/");
                    Signs.insert("/");
                    break;
                }
            case '=':
                string_get.clear();
                ADD(ch);
                PEEK;
                if (ch == '=')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "==");
                    Signs.insert("==");
                    position.second++;
                    break;
                }
                else
                {
                    PUSH(string_get, "=");
                    Signs.insert("=");
                    break;
                }
            case '<':
                string_get.clear();
                ADD(ch);
                PEEK;                           
                switch (ch)
                {
                case '=':
                    ADD(ch);
                    GET;
                    PUSH(string_get, "<=");
                    Signs.insert("<=");
                    position.second++;
                    break;
                case '<':
                    ADD(ch);
                    GET;
                    PUSH(string_get, "<<");
                    Signs.insert("<<");
                    position.second++;
                    break;
                default:
                    PUSH(string_get, "<");
                    Signs.insert("<");
                    break;
                }
                break;
            case '#':
                string_get.clear();
                ADD(ch);
                PUSH(string_get, "BEGIN");
                Signs.insert("#");
                break;
            case '>':
                string_get.clear();
                ADD(ch);
                PEEK;                           // ͬ�ϣ����ﲻ���� get!
                if (ch == '=')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, ">=");
                    Signs.insert(">=");
                    position.second++;
                    break;
                }
                else if (ch == '>')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, ">>");
                    Signs.insert(">>");
                    position.second++;
                    break;
                }
                else
                {
                    PUSH(string_get, ">");
                    Signs.insert(">");
                    break;
                }
            case '{':
            {
                PUSH("{", "{");
                Signs.insert("{");
                break;
            }
            case '}':
            {
                PUSH("}", "}");
                Signs.insert("}");
                break;
            }
            case '!':
                string_get.clear();
                ADD(ch);
                PEEK;                           
                if (ch == '=')
                {
                    ADD(ch);
                    GET;
                    PUSH(string_get, "!=");
                    Signs.insert("!=");
                    position.second++;
                    break;
                }
                else
                {
                    newitem = make_pair(string_get, "���Ϸ��ַ�");
                    ERRORLIST.insert({ newitem,position });
                    break;
                }
            default:                            
                string_get.clear();                        //  ����������������ַ���һ���ǷǷ��ַ�
                ADD(ch);
                newitem = make_pair(string_get, "���Ϸ��ַ�");
                ERRORLIST.insert({ newitem,position });
                break;
            }
            position.second++;
            if (read == false)
            {
                GET;  // �˴���Ҫ�� get һ���µ��ַ�����
            }
            else
            {
                read = false;
            }
        }
    }
    PUSH("#", "FINISH");
#undef PUSH
}

void WordAnalyze::output(ofstream & file)
{
    if (!ERRORLIST.empty())//������գ������﷨����
    {
        for (auto it = ERRORLIST.begin(); it != ERRORLIST.end(); it++)
        {
            cout << it->first.second  << setw(6) << it->first.first << "    ";
            cout << "λ�ã�" << it->second.first << "��" << it->second.second <<"��" << endl;
        }
        return;
    }
    cout << "�ʷ��������" << endl  << endl;
    for (auto it = Words.begin(); it != Words.end(); it++)
    {
        file << "�ַ�ֵ:" << setiosflags(ios::left) 
            << setw(6) << it->first.first<<"�������:" << setw(6) << it->first.second << endl;
        cout << "�ַ�ֵ:" << setiosflags(ios::left)
            << setw(6) << it->first.first << "�������:" << setw(6) << it->first.second 
            << "  λ��:" << it->second.first<< ","<< it->second.second << endl;
    }
}

void WordAnalyze::outeach(ofstream& file)
{
    cout << endl << "ID��;" << endl;
    file << endl << "ID��;" << endl;
    for (auto it = IDs.begin(); it != IDs.end(); it++)
    {
        file << "�ַ�ֵ:" << setiosflags(ios::left)
            << setw(6) << *it << "�������:ID"  <<endl;
        cout << "�ַ�ֵ:" << setiosflags(ios::left)
            << setw(6) << *it << "�������:ID" << endl;
    }

    cout << endl << "���ű�;" << endl;
    file << endl << "���ű�;" << endl;
    for (auto it = Signs.begin(); it != Signs.end(); it++)
    {
        file << "����ֵ:" << setiosflags(ios::left)
            << setw(6) << *it << "�������:Sign" << endl;
        cout << "����ֵ:" << setiosflags(ios::left)
            << setw(6) << *it << "�������:Sign" << endl;
    }

    cout << endl << "�����ֱ�;" << endl;
    file << endl << "�����ֱ�;" << endl;
    for (auto it = keep.begin(); it != keep.end(); it++)
    {
        file << "����ֵ:" << setiosflags(ios::left)
            << setw(6) << it->first << "�������:������" << endl;
        cout << "����ֵ:" << setiosflags(ios::left)
            << setw(6) << it->first << "�������:������" << endl;
    }
}