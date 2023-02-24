#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <stack>
#include "WordAnalyzer.h"
#include "GrammerAnalyzer.h"
using namespace std;

/*��������
* 1.���Դ򿪴�����ļ�
* 2.ʹ���˲��Ϸ��ķ���
* 3.ͷ�ļ�δ��������������
* 4.δ���б�������
* 5.���������
* 6.���������Ϊִ��
* 7.��ֵ���ʹ�ô���        
* 8.While���û�����׵�do
* 9.While���֮�䶨���˱���
* 10.While���֮��ȱ���ж����
* 11.While�����ɲ�����
* 12.for���ȱ����ɳɷ�
* 13.��for���֮�ж������
* 14.�ض�����ͬ�ı���
* 15.��While���֮�ж����˱���
* 16.if�����ɲ�����
* 17.if���û�����׵�then
* 18.thenû�к������
* 19.{û�����׵�}��Ϊ��β
* 20.��ֵ���ʽû��;��Ϊ��β
* 21.�����������û��;��Ϊ��β
* 22.�������û����ȷ��д
* 23.������û����ȷ��д
* 24.������������˶����������ʽ
* 25.����������˶����������ʽ
* 26.��û�У���Ϊƥ��
* 27.�ķ�û��ִ�����
* 28.�ķ�û�ж������
* 29.ʹ����δ����ı���
* 30.�������ʽʹ��0��Ϊ��ĸ   
*/


/*�﷨��
<����> ::= <ͷ�ļ�����>{<�ֳ���>}
<ͷ�ļ�����>::= #include<iostream> int main()
<�ֳ���> ::= <��������><ִ�����>
 <��������>::= <��������><��ʶ��>;{<�������� >}
<��ʶ��> ::= <��ĸ>{<��ĸ>|<����>}
<ִ�����>::=<�������>|<������>|<��ֵ���>|<�������>|<While���>|<For���>|{<ִ�����>}
<��ֵ���>::=<��ʶ��> <��ֵ�����> <���ʽ > ;
<While���>::= while(<�������>)do<ִ�����>
<For���>::= for([<��ֵ���>] <�������> ; <��ֵ���> ) <ִ�����>
<�������>::= if( <����> ) then <ִ�����> [ else <ִ�����> ]
<�������>::= <�߼�����ʽ> { || <�߼�����ʽ> }
<�߼�����ʽ>::= <�߼�����ʽ> { && <�߼�����ʽ> }
<�߼�����ʽ>::= <���ʽ><��ϵ�����><���ʽ>
<���ʽ>::= <��λ����ʽ> { |  < ��λ����ʽ>}
<��λ����ʽ>::= <��λ����ʽ> { &  < ��λ����ʽ>}
<��λ����ʽ>::= <λ�Ʊ��ʽ> { <λ�������> <λ�Ʊ��ʽ>}
<λ�Ʊ��ʽ>::= <�˳����ʽ>{<�Ӽ������> <�˳����ʽ>}
<�˳����ʽ>::= <����ʽ>{<�˳������> <����ʽ>}
<����ʽ>::=(<����ʽ>) |<��ʶ��>|<����>
<�˳������>::= * | /
<�Ӽ������>::= + | -
<λ�������>::= >> | <<
<��ϵ�����> ::= == | != | < | <= | > | >=
<��ֵ�����>::= = | += | -= | *= | /=
<�������> ::= scanf(<��ʶ��>)
<������> ::= printf(<��ʶ��>)
<��������>::= int | char | string
<��ĸ> ::= a|b|...|X|Y|Z
<����> ::= 0|1|2|...|8|9
<����> ::= [-] <����> 
*/
pair<string, string> Errorname; //��������
pair<int, int> Errorposi; //����λ��
pair<string, string> IDNEED;
stack <string> outposi;//���ڱ�����ѭ��ʱ������
int tempValue = 0; //�ܾ���Ҫ��ջ
int Line = 100; //��תʱʹ�õ�λ�ñ��

bool hasLEF = false; //����Ƿ�ӵ��������
int forstart = 0;
int Sdeep = 0;
int times = 0;
#define VEC vector < pair< pair< string, string >, pair<int, int> > >::iterator
#define Wresult wordanalyze.Words
#define Elist wordanalyze.ERRORLIST
#define KEEP wordanalyze.keep
#define ERRORSET(s)  Errorname = make_pair(it->first.first, s);\
wordanalyze.ERRORLIST.insert({ Errorname,it->second });

#define Four(s1,s2,s3,s4) Foursentence line;\
line.Type = s1;\
line.Number_1 = s2;\
line.Number_2 = s3;\
line.Name =s4;\
line.Posi = Line++;\
FourLine.push_back(line);

#define FoueTemp(s1,s2,s3,s4) Foursentence line_temp;\
line_temp.Type = s1; \
line_temp.Number_1 = s2; \
line_temp.Number_2 = s3; \
line_temp.Name = s4; \
line_temp.Posi = Line++; \
FourLine.push_back(line_temp);

GrammerAnalyze::GrammerAnalyze(WordAnalyze& word) :wordanalyze(word) {

    Relop.insert("="); Relop.insert("=="); Relop.insert("<="); Relop.insert("<"); Relop.insert(">=");
    Relop.insert(">");  Relop.insert("!="); Relop.insert(">");
    DEQU.insert("=");
    DEQU.insert("*=");
    DEQU.insert("/=");
    DEQU.insert("+=");
    DEQU.insert("-=");
    it = Wresult.begin();

}
void GrammerAnalyze::Define() 
{
    if (it->first.second == "INT")
    {
        it++;
        if (it->first.second == "ID")
        {

            if (IDList.find(it->first.first) != IDList.end())//����ض���
            {
                cout << "�ض���Ԫ�أ�"  <<"     ����λ��" << it->second.first << "��" << it->second.second << "��";
                exit(0);
            }
            IDNEED = make_pair(it->first.first,"_");
            IDList.insert(IDNEED);
            string TempID = it->first.first;
            it++;
            if (it->first.first == ";")
            {
                it++;
                //����D����Ԫʽ
                Four("INT", TempID, "_", "_");
            }
            else
            {
                cout << "ȱ��;��β" << "     ����λ��" 
                    << it->second.first << "��" << it->second.second << "��";
                exit(0);
            }
        }
        else
        {
            Errorname = make_pair(it->first.second, "D()fail");
            cout << "ȱ�������ı����� " << "     ����λ��" 
                << it->second.first << "��" << it->second.second << "��";
            wordanalyze.ERRORLIST.insert({ Errorname,it->second });
            exit(0);
        }
        if (it->first.second == "INT" || it->first.second == "CHAR" || it->first.second == "STRING")
            Define();
    }
    else if (it->first.second == "CHAR")
    {
        it++;
        if (it->first.second == "ID")
        {

            if (IDList.find(it->first.first) != IDList.end())//����ض���
            {
                cout << "�ض���Ԫ�أ�" << "     ����λ��" << it->second.first << "��" << it->second.second << "��";
                exit(0);
            }
            IDNEED = make_pair(it->first.first, "_");
            IDList.insert(IDNEED);
            string TempID = it->first.first;
            it++;
            if (it->first.first == ";")
            {
                it++;
                //����D����Ԫʽ
                Four("CHAR", TempID, "_", "_");
            }
            else
            {
                cout << "ȱ��;��β" << "     ����λ��"
                    << it->second.first << "��" << it->second.second << "��";
                exit(0);
            }

        }
        else
        {
            Errorname = make_pair(it->first.second, "D()fail");
            cout << "ȱ�������ı����� " << "     ����λ��"
                << it->second.first << "��" << it->second.second << "��";
            wordanalyze.ERRORLIST.insert({ Errorname,it->second });
            exit(0);
        }
        if (it->first.second == "INT" || it->first.second == "CHAR" || it->first.second == "STRING")
            Define();
    }
    else if (it->first.second == "STRING")
    {
        it++;
        if (it->first.second == "ID")
        {

            if (IDList.find(it->first.first) != IDList.end())//����ض���
            {
                cout << "�ض���Ԫ�أ�" << "     ����λ��" << it->second.first << "��" << it->second.second << "��";
                exit(0);
            }
            IDNEED = make_pair(it->first.first, "_");
            IDList.insert(IDNEED);
            string TempID = it->first.first;
            it++;
            if (it->first.first == ";")
            {
                it++;
                //����D����Ԫʽ
                Four("STR", TempID, "_", "_");
            }
            else
            {
                cout << "ȱ��;��β" << "     ����λ��"
                    << it->second.first << "��" << it->second.second << "��";
                exit(0);
            }
        }
        else
        {
            Errorname = make_pair(it->first.second, "D()fail");
            cout << "ȱ�������ı����� " << "     ����λ��"
                << it->second.first << "��" << it->second.second << "��";
            wordanalyze.ERRORLIST.insert({ Errorname,it->second });
            exit(0);
        }
        if (it->first.second == "INT" || it->first.second == "CHAR" || it->first.second == "STRING")
            Define();
    }
    else
    {
        Errorname = make_pair(it->first.second, "�����������");
        cout << "Please Check where ID was define" << "     ����λ��"
            << it->second.first << "��" << it->second.second << "��";
        wordanalyze.ERRORLIST.insert({ Errorname,it->second });
        exit(0);
    }

}
void GrammerAnalyze::Numgiven()
{
    if (IDList.find(it->first.first) == IDList.end())//����Ƿ񱻶���
    {
        cout << "δ������ı���" << it->first.first << "    ����λ��:" << it->second.first << "��"
            << it->second.second << "��";
        exit(0);
    }
    else
    {
        string tempID = it->first.first;//��¼��ǰID��
        it++;
        if (it->first.first == "*=")
        {
            it++;
            string stringpoint = "t" + to_string(++tempValue);
            Four("*", tempID, OR(), stringpoint);
            FoueTemp ("=", tempID, stringpoint, "_")
        }
        else if (it->first.first == "+=")
        {
            it++;
            string stringpoint = "t" + to_string(++tempValue);
            Four("+", tempID, OR(), stringpoint);
            FoueTemp("=", tempID, stringpoint, "_")
        }
        else if (it->first.first == "-=")
        {
            it++;
            string stringpoint = "t" + to_string(++tempValue);
            Four("-", tempID, OR(), stringpoint);
            FoueTemp("=", tempID, stringpoint, "_")
        }
        else if (it->first.first == "/=")
        {
            it++;
            string stringpoint = "t" + to_string(++tempValue);
            Four("/", tempID, OR(), stringpoint);
            FoueTemp("=", tempID, stringpoint, "_")
        }
        else if (it->first.first == "=")
        {
            it++;
            Four("=", tempID, OR(), "_");
        }
        else
        {
            it++;
            cout << "��֪���ĸ�ֵ����" << it->first.first << "    ����λ��:" << it->second.first << "��"
                << it->second.second << "��";
            exit(0);
        }
    }
    if (it->first.first == ")" && forstart > 0 )
    {
        return;
    }
    if (it->first.first != ";")
    {
        cout << "ȱ�� ';' " << "    ����λ��:" << it->second.first << "��"
            << it->second.second << "��";;
        exit(0);
    }
    else
    {
        it++;
    }
}
void GrammerAnalyze::IFCHECK()
{
    if (it->first.second == "IF")
    {
        it++;
        if (it->first.second == "(")
        {
            it++;
            string temp_if = Bool();
            int trueout, falseout;
            Four("JNZ", temp_if, "_", "");//�����
            trueout = Line;
            FoueTemp("JEZ", temp_if, "_", "");//�ٳ���
            falseout = Line;
            if (it->first.second == ")")
            {
                it++;
                if (it->first.second == "THEN")
                {
                    it++;
                    FourLine[trueout - 101].Name = to_string(Line);
                    jumpsymbol = true;
                    Sdeep++;
                    Start();
                    Sdeep--;
                    //��������ת���
                    Foursentence Jtemp;
                    Jtemp.Type = "J";
                    Jtemp.Number_1 = Jtemp.Number_2 = "_";
                    Jtemp.Name = "";
                    Jtemp.Posi = Line++;
                    int jump_posi = Line;
                    FourLine.push_back(Jtemp);
                    if (it->first.second == "ELSE")
                    {
                        it++;
                        FourLine[falseout - 101].Name = to_string(Line);
                        jumpsymbol = true;
                        Sdeep++;
                        Start();
                        Sdeep--;
                    }
                    FourLine[jump_posi - 101].Name = to_string(Line);
                }
                else
                {
                    cout << "ȱ��Then" <<  "    ����λ��:" << it->second.first << "��"
                        << it->second.second << "��";
                    exit(0);
                }
            }
            else
            {
                cout << "ȱ�٣�" << "    ����λ��:" << it->second.first << "��"
                    << it->second.second << "��";
                exit(0);
            }

        }
        else
        {
            cout << "ȱ��IF" << "    ����λ��:" << it->second.first << "��"
                << it->second.second << "��";
            wordanalyze.ERRORLIST.insert({ Errorname,it->second });
            exit(0);
        }
    }
}
void GrammerAnalyze::WhileCheck()
{
    if (it->first.second == "WHILE")
    {
    it++;
    if (it->first.second == "(")
    {
        it++;
        int jumpback = Line;
        outposi.push(to_string(jumpback) );//����ջ�� ������ѭ��ʹ��
        string temp_while = Bool();
        int trueout, falseout;
        Four("JNZ", temp_while, "_", "");//�����
        trueout = Line;
        FoueTemp("JEZ", temp_while, "_", "");//�ٳ���
        falseout = Line;
        if (it->first.second == ")")
        {
            it++;
            if (it->first.second == "DO")
            {
                it++;
                FourLine[trueout - 101].Name = to_string(Line); //�����ʽΪ���ʱ�� ����Ҫ����ִ��Do�����
                jumpsymbol = true;
                Sdeep++;
                Start();
                Sdeep--;
                //��һ��ѭ���������֮�� ����Ҫ�����ص�while��ͷ�����ٴν����ж�
                Foursentence Jtemp;
                Jtemp.Type = "J";
                Jtemp.Number_1 = Jtemp.Number_2 = "_";
                Jtemp.Name = outposi.top();
                outposi.pop();//��ѭ��ִ�����֮�� ����Ҫ���������ǰ��
                Jtemp.Posi = Line++;
                FourLine.push_back(Jtemp);
                //������ ���Ǿ���֪�� �ٳ�����������
                FourLine[falseout - 101].Name = to_string(Line);
            }
            else
            {
                cout << "ȱ��Do" << "    ����λ��:" << it->second.first << "��"
                    << it->second.second << "��";;
                exit(0);
            }
        }
        else {
            cout << "ȱ�٣�"  << "    ����λ��:" << it->second.first << "��"
                << it->second.second << "��";
            exit(0);
        }
    }
    else
    {
        cout << "ȱ��(" << "    ����λ��:" << it->second.first << "��"
            << it->second.second << "��";;
        exit(0);
    }
    }
}
void GrammerAnalyze::FORCHECK()
{
    it++;
    if (it->first.second == "(")
    {
        it++;
        if (it->first.second == "INT")
        {
            cout << "�����ʼ���������� "<<"     ����λ��" 
                << it->second.first <<"��" << it->second.second << "��";
            exit(0);
        }
        else if (it->first.second == "ID")
        {//��ʼ������
            jumpsymbol = true;
            Numgiven();
        }
        else if (it->first.second == ";")
            it++;
        else
        {
            cout << "��֧����˶���for���" << "     ����λ��" 
                << it->second.first << "��" << it->second.second << "��";
            exit(0);
        }
    }
    else
    {
        cout << "for���ȱ��(" << "     ����λ��" 
            << it->second.first << "��" << it->second.second << "��";
        exit(0);
    }
    //for���˳����
    string jumpback = to_string(Line);
        outposi.push(jumpback);//����ջ�� ������ѭ��ʹ��
    string temp_if = Bool(); //������ɵ����˳����
    int trueout, falseout;
    Four("JNZ", temp_if, "_", "");//�����
    trueout = Line;
    FoueTemp("JEZ", temp_if, "_", "");//�ٳ���
    falseout = Line;

    if (it->first.second == ";")
    {
        it++;
        //FourLine[trueout - 101].Name = to_string(Line);
        jumpsymbol = true;
        string numback = to_string(Line);
        Numgiven();
        //outposi.push(to_string(Line - 1 ));//���뵱ǰ����λ��

        Foursentence Jtemp;
        Jtemp.Type = "J";
        Jtemp.Number_1 = Jtemp.Number_2 = "_";
        Jtemp.Name = outposi.top();
        outposi.pop();//��ѭ��ִ�����֮�� ����Ҫ����While�����ǰ��
        Jtemp.Posi = Line++;
        FourLine.push_back(Jtemp);
        outposi.push(numback);

        FourLine[trueout - 101].Name = to_string(Line);

        if (it->first.second == ")")
        {
            it++;
            if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID" ||
                it->first.second == "CHAR" || it->first.second == "FOR" || it->first.second == "PRINTF"
                || it->first.second == "{" || it->first.second == "SCANF") 
                )
            {
                Sdeep++;
                Start();
                Sdeep--;
            }
            //��һ��ѭ���������֮�� ����Ҫ�����ص�for��ͷ�����ٴν����ж�
            Foursentence Jtemp;
            Jtemp.Type = "J";
            Jtemp.Number_1 = Jtemp.Number_2 = "_";
            Jtemp.Name = outposi.top();
            outposi.pop();//��ѭ��ִ�����֮�� ����Ҫ����While�����ǰ��
            Jtemp.Posi = Line++;
            FourLine.push_back(Jtemp);
            //������ ���Ǿ���֪�� �ٳ�����������
            FourLine[falseout - 101].Name = to_string(Line);
        }
        else
        {
            cout << "for���ȱ�٣�" << "    ����λ��:" << it->second.first << "��"
                << it->second.second << "��";
            exit(0);
        }
    }
    else
    {
        cout << "for���ȱ�� ; " << "     ����λ��" 
            << it->second.first << "��" << it->second.second << "��";
        exit(0);
    }
}
void GrammerAnalyze::Printout()
{
    if (it->first.second == "PRINTF")
    {
        it++;
        if (it->first.second == "(")
        {
            it++;
            if ((it->first.second == "ID") && ((it + 1)->first.second == ")"))
            {
                string outtemp = OR();
                Four("OUT", outtemp, "_", "_");
                if (it->first.second == ")")
                {
                    it++;
                    /*
                    if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID"
                        || it->first.second == "FOR" || it->first.second == "PRINTF" ||it->first.second == "{"
                        || it->first.second == "SCANF")
                        && ((Sdeep - forstart) != 1 || forstart == 0))
                    {
                        Start();
                    }*/
                }
                else
                {
                    cout << "Print���ȱ�� )" << "    λ��:" << it->second.first << "��"
                        << it->second.second << "��";
                    exit(0);
                }
            }
            else
            {
                cout << "printf���ÿ��ֻ�����һ��������" << "    ����λ��:" << it->second.first << "��"
                    << it->second.second << "��";
                exit(0);
            }
        }
        else
        {
            cout << "Print���ȱ�� (" << "    λ��:" << it->second.first << "��"
                << it->second.second << "��";
            exit(0);
        }
    }
}
void GrammerAnalyze::Scanfin()
{
    if (it->first.second == "SCANF")
    {
        it++;
        if (it->first.second == "(")
        {
            it++;
            if ( ( it->first.second == "ID"  )
                &&( (it + 1)->first.second == ")" ) )
            {
                string outtemp = OR();
                Four("IN", outtemp, "_", "_");
                if (it->first.second == ")")
                {
                    it++;
                    /*if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID"
                        || it->first.second == "FOR" || it->first.second == "PRINTF" ||it->first.second == "{")
                        && ((Sdeep - forstart) != 1 || forstart == 0))
                    {
                        Start();
                    }*/
                }
                else
                {
                    cout << "sacnf���ȱ�� )" << "    ����λ��:" << it->second.first << "��"
                        << it->second.second << "��";
                    exit(0);
                }
            }
            else
            {
                cout << "scanf���ÿ��ֻ�ܸ�ֵһ��������" << "    ����λ��:" << it->second.first << "��"
                    << it->second.second << "��";
                exit(0);
            }
        }
        else
        {
            cout << "scanf���ȱ�� (" << "    ����λ��:" << it->second.first << "��"
                << it->second.second << "��";
            exit(0);
        }
    }
}
void GrammerAnalyze::Start()
{
    if (it->first.second == "IF")
    {
        forstart++;
        IFCHECK();
        forstart--;
        if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID" || 
            it->first.second == "CHAR"|| it->first.second == "FOR" || it->first.second == "PRINTF" 
            || it->first.second == "{"|| it->first.second == "SCANF"))
        {
            Start();
        }
    }
    else if (it->first.second == "WHILE")
    {
        forstart++;
        WhileCheck();
        forstart--;
        if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID" ||
            it->first.second == "CHAR" || it->first.second == "FOR" || it->first.second == "PRINTF"
            || it->first.second == "{" || it->first.second == "SCANF"))
        {
            Start();
        }
    }
    else if (it->first.first == "{")
    {
        it++;
        jumpsymbol = false;
        Start();
        if (it->first.first == "}")
        {
            it++;
            if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID" ||
                it->first.second == "CHAR" || it->first.second == "FOR" || it->first.second == "PRINTF"
                || it->first.second == "{" || it->first.second == "SCANF"))
            {
                if (forstart == Sdeep && (forstart != 0) && (Sdeep!=0))
                    return;
                Start();
            }
        }
        else
        {
            cout << "���Ų�ƥ��" << it->second.first << "," << it->second.second;
            exit(0);
        }

    }
    else if (it->first.second == "ID" ||
        it->first.second == "CHAR" || 
        it->first.second == "STRING")
    {
        while (it->first.second == "ID" || it->first.second == "CHAR" || it->first.second == "STRING")
        {
            Numgiven();
            if (jumpsymbol == true)
            {
                jumpsymbol = false;
                break;
            }
        }
        if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID" ||
            it->first.second == "CHAR" || it->first.second == "FOR" || it->first.second == "PRINTF"
            || it->first.second == "{" || it->first.second == "SCANF"))
        {
            Start();
        }
    }
    else if (it->first.second == "FOR")
    {
        forstart++; 
        FORCHECK();
        forstart--;
        if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID" ||
            it->first.second == "CHAR" || it->first.second == "FOR" || it->first.second == "PRINTF"
            || it->first.second == "{" || it->first.second == "SCANF"))
        {
           // if (forstart == Sdeep && (forstart != 0) && (Sdeep != 0))
                //return;
            Start();
        }
    }
    else if (it->first.second == "PRINTF")
    {
        Printout();
        if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID"
            || it->first.second == "FOR" || it->first.second == "PRINTF" ||it->first.second == "{"
            || it->first.second == "SCANF"))
        {
            Start();
        }
    }
    else if (it->first.second == "SCANF")
    {
        Scanfin();
        if ((it->first.second == "IF" || it->first.second == "WHILE" || it->first.second == "ID" ||
            it->first.second == "CHAR" || it->first.second == "FOR" || it->first.second == "PRINTF"
            || it->first.second == "{" || it->first.second == "SCANF"))
        {
            Start();
        }
    }
    else
    {
        cout << "ȱ��ִ����䣡"  << "    ����λ��:" << it->second.first << "��"
            << it->second.second << "��";;
        exit(0);
    }
}
string GrammerAnalyze::Bool()// ||
{
    string tempstring_pos1 = DoubleAnd();
    string tempstring_pos2;
    while (it->first.second == "||")
    {
        it++;
        tempstring_pos2 = DoubleAnd();
        string stringpoint = "t" + to_string(++tempValue);
        Four("|", tempstring_pos1, tempstring_pos2, stringpoint);
        string stringpoint_2 = "t" + to_string(++tempValue);
        FoueTemp("!=", stringpoint, "0", stringpoint_2);
        tempstring_pos1 = stringpoint_2;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::DoubleAnd() // &&
{
    string tempstring_pos1 = Relopcheck();
    string tempstring_pos2;
    while (it->first.second == "&&")
    {
        it++;
        tempstring_pos2  = Relopcheck();
        string stringpoint = "t" + to_string(++tempValue);
        Four("&", tempstring_pos1, tempstring_pos2, stringpoint);
        string stringpoint_2 = "t" + to_string(++tempValue);
        FoueTemp("!=", stringpoint, "0", stringpoint_2);
        tempstring_pos1 = stringpoint_2;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::Relopcheck()
{
    string tempstring_pos1 = OR();
    string tempstring_pos2;
    while (Relop.find(it->first.second) != Relop.end()) //�ж�>= > <= < != == 
    {
        string temp_type = it->first.first;
        it++;
        tempstring_pos2 =  OR();
        string stringpoint = "t" + to_string(++tempValue);
        Four(temp_type, tempstring_pos1, tempstring_pos2, stringpoint);
        tempstring_pos1 = stringpoint;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::OR()
{
    string tempstring_pos1 = AND();
    string tempstring_pos2;
    while (it->first.second == "|")
    {
        string temp_type = it->first.first;
        it++;
        tempstring_pos2 = AND();
        string stringpoint = "t" + to_string(++tempValue);
        Four(temp_type, tempstring_pos1, tempstring_pos2, stringpoint);
        tempstring_pos1 = stringpoint;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::AND()
{
    string tempstring_pos1 = Drift();
    string tempstring_pos2;
    while (it->first.second == "&")
    {
        string temp_type = it->first.first;
        it++;
        tempstring_pos2 = Drift();
        string stringpoint = "t" + to_string(++tempValue);
        Four(temp_type, tempstring_pos1, tempstring_pos2, stringpoint);
        tempstring_pos1 = stringpoint;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::Drift()
{
    string tempstring_pos1 = ADDCheck();
    string tempstring_pos2;
    while ( it->first.second == ">>" || it->first.second == "<<" )
    {
        string temp_type = it->first.first;
        it++;
        tempstring_pos2 = ADDCheck();
        string stringpoint = "t" + to_string(++tempValue);
        Four(temp_type, tempstring_pos1, tempstring_pos2, stringpoint);
        tempstring_pos1 = stringpoint;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::ADDCheck()//E��T { +T | -T }
{
    string tempstring_pos1 = MulCheck();
    string tempstring_pos2;
    while (it->first.second == "+" || it->first.second == "-")
    {
        string temp_type = it->first.first;
        it++;
        tempstring_pos2 = MulCheck();
        string stringpoint = "t" + to_string(++tempValue);
        Four(temp_type, tempstring_pos1, tempstring_pos2, stringpoint);
        tempstring_pos1 = stringpoint;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::MulCheck()
{
    string tempstring_pos1 = Equal();
    string tempstring_pos2;
    while (it->first.second == "*" || it->first.second == "/")
    {
        string temp_type = it->first.first;
        it++;
        tempstring_pos2 = Equal();
        string stringpoint = "t" + to_string(++tempValue);
        Four(temp_type, tempstring_pos1, tempstring_pos2, stringpoint);
        tempstring_pos1 = stringpoint;
    }
    return tempstring_pos1;
}
string GrammerAnalyze::Equal()
{
    if (it->first.second == "(")
    {
        it++;
       string tempstring = OR();
       if (it->first.second == ")")
       {
           it++;
           return tempstring;
       }
        else
        {
            cout << "���Ϲ���������"  << it->second.first << "��" << it->second.second  << "��";
            exit(0);
        }
    }
    else if (it->first.second == "NUM")
    {
        it++;
        return (it - 1)->first.first;//���س���ֵ
    }
    else if (it->first.second == "ID")
    {
        if (IDList.find(it->first.first) == IDList.end())//����Ƿ񱻶���
        {
            cout << "δ������ı���" << it->first.first << " λ��   " <<it->second.first 
                << "��" << it->second.second << "��";
            exit(0);
        }
        it++;
        return (it - 1)->first.first; //���ر�����
    }
    else
    {
        cout << "���Ϲ�����" << it->first.first << " λ��   " << it->second.first
            << "��" << it->second.second << "��";
        exit(0);
    }
}
void GrammerAnalyze::Program() 
{//ͷ�ļ����
    int i = 0;
    //���P��first����
    for (it = Wresult.begin(); it != Wresult.begin() + 10; it++, i++)
    {
        switch (i)
        {
        case 0:
            if (it->first.second != "BEGIN")
            {
                Errorname = make_pair(it->first.second, "Should start with a '#'");
                cout << "Should start with a '#'";
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                exit(0);
            }
            break;
        case 1:
            if (it->first.second != "INCLUDE")
            {
                Errorname = make_pair(it->first.first, "Expect for 'include'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "Expect for 'include'";
                exit(0);
            }
            break;
        case 2:
            if (it->first.first != "<")
            {
                Errorname = make_pair(it->first.first, "please ues '<'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "please ues '<'";
                exit(0);
            }
            break;
        case 3:
            if (it->first.second != "IOSTREAM")
            {
                Errorname = make_pair(it->first.first, "Expect for 'iostream' to start");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "Expect for 'iostream' to start";
                exit(0);
            }
            break;
        case 4:
            if (it->first.first != ">")
            {
                Errorname = make_pair(it->first.first, "please use '>'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "please use '>'";
                exit(0);
            }
            break;
        case 5:
            if (it->first.first != "int")
            {
                Errorname = make_pair(it->first.first, "need 'int'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "need '{'";
                exit(0);
            }
            break;
        case 6:
            if (it->first.first != "main")
            {
                Errorname = make_pair(it->first.first, "need '{'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "need '{'";
                exit(0);
            }
            break;
        case 7:
            if (it->first.first != "(")
            {
                Errorname = make_pair(it->first.first, "need '{'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "need '{'";
                exit(0);
            }
            break;
        case 8:
            if (it->first.first != ")")
            {
                Errorname = make_pair(it->first.first, "need '{'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "need '{'";
                exit(0);
            }
            break;
        case 9:
            if (it->first.first != "{")
            {
                Errorname = make_pair(it->first.first, "need '{'");
                wordanalyze.ERRORLIST.insert({ Errorname,it->second });
                cout << "need '{'";
                exit(0);
            }
            break;
        }
    }
    Define();
    Start();
    if (it->first.first != "}")
    {
        cout << "ȱ��}��Ϊ��β"  << "λ�� "<< it->second .first << "��" << it->second.second <<"��";
        exit(0);
    }
    else
    {
        it++;
    }
}
void GrammerAnalyze::outputfour(ofstream &file)
{
    vector <Foursentence>::iterator itout = FourLine.begin();
    cout <<endl <<  "������Ԫʽ�����" << endl << endl;
    for (; itout != FourLine.end(); itout++)
    {
        file  << itout->Posi << " ";
        file << "(" << setiosflags(ios::left) << setw(4) << itout->Type << " ," << setw(4) << itout->Number_1;
        file << ","<< setw(4) << itout->Number_2 << "," << setw(4) << itout->Name << ")" << endl;

        cout << itout->Posi << " ";
        cout << "(" << setiosflags(ios::left) << setw(4) << itout->Type << " ," << setw(4) << itout->Number_1;
        cout << "," << setw(4) << itout->Number_2 << ","<< setw(4) << itout->Name << ")" << endl;
    }
}
bool GrammerAnalyze::grammeranalyze()
{

    Program();
    if (it->first.second != "FINISH")
    {
        cout << "�﷨����ʧ��";
        return false;
    }
    Four("FINISH", "_", "_", "_");
    return true;
}