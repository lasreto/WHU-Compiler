
#include "Explain.h"
#include <iomanip>
using namespace std;

Explain::Explain(GrammerAnalyze& result) :grammerresult(result)
{

}
#define  GF grammerresult.FourLine
map<string, int> IntNums;
map<string, string> StringNums;
set<string> CharNums;
map<string, string>::iterator sit;
map<string, int>::iterator iit;
int line[100];//����������Щ�����tempֵ
int tempnow = 0;
bool teststart = false;
int Valueget(string str)
{//����ǲ����м�ֵ���ʽ
	bool check_in_temp = false;
	int tempValue = 0;
	if (str[0] == 't')
	{
		for (int i = 1; i < str.size(); i++)
		{
			if (isdigit(str[i]))
			{
				tempValue = tempValue * 10 + str[i] - '0';
			}
			else
			{
				check_in_temp = true;
			}
		}
	}
	else
	{
		check_in_temp = true;
	}
	if (check_in_temp == true)
	{
		if (isdigit(str[0]))
		{
			tempValue = 0;
			for (int i = 0; i < str.size(); i++)
			{
				if (isdigit(str[i]))
				{
					tempValue = tempValue * 10 + str[i] - '0';
				}
			}
			return tempValue;
		}
		else if (str[0] == '-')
		{
			tempValue = 0;
			for (int i = 1; i < str.size(); i++)
			{
				if (isdigit(str[i]))
				{
					tempValue = tempValue * 10 + str[i] - '0';
				}
			}
			return -tempValue;
		}
		iit = IntNums.find(str);
		if (iit != IntNums.end())
			return iit->second;
		else
			return 1;
	}
	else
	{
		return line[tempValue];
	}
}
int Posiget(string str)
{
	int tempPosi = 0;
	for (int i = 1; i < str.size(); i++)
	{
		if (isdigit(str[i]))
		{
			tempPosi = tempPosi * 10 + str[i] - '0';
		}
	}
	tempnow = max(tempPosi, tempnow);
	return tempPosi;
}
void Explain::Valueout(int nawo,int posi )
{
	if (teststart == false)
		return;
	else
	{
		cout << "��ǰִ����䣺";
		cout << GF[nawo].Posi << " ";
		cout << "(" << setiosflags(ios::left) << setw(4) << GF[nawo].Type << " ," << setw(4) << GF[nawo].Number_1;
		cout << "," << setw(4) << GF[nawo].Number_2 << "," << setw(4) << GF[nawo].Name << ")" ;
		//��Ԫʽ����
		cout << "    ����Ԫʽ��ָ��C���Ϊ:";
		if (GF[nawo].Type == "INT")
		{
			cout << "int " << GF[nawo].Number_1 << ";" << endl;
		}
		if (GF[nawo].Type == "IN")
		{
			cout << "scanf(" << GF[nawo].Number_1 << ")" << endl;
		}
		if (GF[nawo].Type == "OUT")
		{
			cout << "printf(" << GF[nawo].Number_1 << ")" << endl;
		}
		if (GF[nawo].Type == "J")
		{//��������ת
			cout << "goto" << GF[nawo].Name  << endl;
		}
		if (GF[nawo].Type == "<")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " < " << GF[nawo].Number_2 << "? true : false" << endl;
		}
		if (GF[nawo].Type == "<=")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 <<  " <= " <<  GF[nawo].Number_2 << "? true : false" << endl;
		}
		if (GF[nawo].Type == ">=")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " >= " << GF[nawo].Number_2 << "? true : false" << endl;
		}
		if (GF[nawo].Type == ">")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " > " << GF[nawo].Number_2 << "? true : false" << endl;
		}
		if (GF[nawo].Type == ">>")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " / 2 ^  " << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "<<")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " * 2 ^ " << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "==")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " == " << GF[nawo].Number_2 << "? true : false" << endl;
		}
		if (GF[nawo].Type == "!=")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " != " << GF[nawo].Number_2 << "? true : false" << endl;
		}
		if (GF[nawo].Type == "=")
		{
			cout << GF[nawo].Number_1 << " = " << GF[nawo].Number_2  << endl;
		}
		if (GF[nawo].Type == "+")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " +" << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "-")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " -" << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "*")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " *" << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "/")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " /" << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "JNZ")
		{
			cout << " if(" << GF[nawo].Number_1 << " ==true) goto" << GF[nawo].Name << endl;
		}
		if (GF[nawo].Type == "JEZ")
		{
			cout << " if(" << GF[nawo].Number_1 << " ==false) goto" << GF[nawo].Name << endl;
		}
		if (GF[nawo].Type == "&")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " &" << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "|")
		{
			cout << GF[nawo].Name << " = " << GF[nawo].Number_1 << " |" << GF[nawo].Number_2 << endl;
		}
		if (GF[nawo].Type == "CHAR")
		{
			cout << "char " << GF[nawo].Number_1 << ";" << endl;
		}
		if (GF[nawo].Type == "STR")
		{
			cout << "string " << GF[nawo].Number_1 << ";" << endl;
		}

		cout << "�����ʽִ�к���Ϊ" << endl;
		auto it = IntNums.begin();
		for (; it != IntNums.end(); it++)
			cout << it->first << "   " << it->second << endl;
		for (auto its = StringNums.begin(); its != StringNums.end(); its++)
			cout << its->first << "   " << its->second << endl;
		for (int i = 0; i <= tempnow; i++)
			cout << "t" << i << "   " << line[i] << endl;

		system("pause");
		cout << endl;
		return;
	}

	return;
}
void Explain::outing(int posi)
{//ʹ��ͼ����ķ��� ��ͷ��β �������ͺ���
	for (int i = 0; i < GF.size(); i++)
	{
		if (i >= posi && teststart == false)
			teststart = true;
		if (GF[i].Type == "INT")
		{
			IntNums.insert({ GF[i].Number_1 ,0 });
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "IN")
		{
			cout << "���������" << GF[i].Number_1 << ":";
			string str;
			cin >> str;
			if (IntNums.find(GF[i].Number_1) == IntNums.end())
			{//���ֲ���int����
				sit = StringNums.find(GF[i].Number_1);
				if (CharNums.find(GF[i].Number_1) != CharNums.end()) //�Ǹ�char ����
					sit->second = str[0];
				else
				sit->second = str;
			}
			else
			{
				int tempValue = 0;
				int temp = 0;
				iit = IntNums.find(GF[i].Number_1);
				if (str[0] == '-')
					temp = 1;
				for (temp; temp < str.size(); temp++)
				{
					tempValue = tempValue *10 + str[temp] - '0';
				}
				if (str[0] == '-')
					tempValue = -tempValue;
				iit->second = tempValue;
			}
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "OUT")
		{
			if (IntNums.find(GF[i].Number_1)== IntNums.end())
			{//���ֲ���int����
				sit = StringNums.find(GF[i].Number_1);
				cout << GF[i].Number_1 << "��ֵΪ" << sit->second << endl;
			}
			else
			{
				iit = IntNums.find( GF[i].Number_1);
				cout << GF[i].Number_1 << "��ֵΪ" << iit->second << endl;
			}
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "J")
		{//��������ת
			i = stoi(GF[i].Name) -101;
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "<")
		{
			line[ Posiget(GF[i].Name) ] = Valueget(GF[i].Number_1) < Valueget(GF[i].Number_2) ? 1 : 0;
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "<=")
		{
			line[ Posiget(GF[i].Name) ] = Valueget(GF[i].Number_1) <= Valueget(GF[i].Number_2) ? 1 : 0;
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == ">=")
		{
			line[ Posiget(GF[i].Name) ] = Valueget(GF[i].Number_1) >= Valueget(GF[i].Number_2) ? 1 : 0;
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == ">>")
		{
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) /  pow(2, Valueget(GF[i].Number_2) );
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "<<")
		{
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) * pow(2, Valueget(GF[i].Number_2));
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == ">")
		{
			line[ Posiget(GF[i].Name) ] = Valueget(GF[i].Number_1) > Valueget(GF[i].Number_2) ? 1 : 0;
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "==")
		{
			line[ Posiget(GF[i].Name) ] = ( Valueget(GF[i].Number_1) == Valueget(GF[i].Number_2)) ? 1 : 0;
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "!=")
		{
			line[ Posiget ( GF[i].Name ) ] =  Valueget(GF[i].Number_1) != Valueget(GF[i].Number_2)   ? 1 : 0;
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "=")
		{
			if (IntNums.find(GF[i].Number_1) == IntNums.end())
			{//���ֲ���int����
				cout << "���ͳ������д����ƣ��޷�ִ����������Ŷ��";
				exit(0);
			}
			else
			{
				iit = IntNums.find(GF[i].Number_1);
				iit->second = Valueget(GF[i].Number_2);
			}
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "+")
		{
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) + Valueget(GF[i].Number_2);
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "-")
		{
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) - Valueget(GF[i].Number_2);
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "*")
		{
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) * Valueget(GF[i].Number_2);
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "/")
		{
			if (Valueget(GF[i].Number_2) == 0)
			{
				cout << "�벻Ҫʹ��0��Ϊ������";
				exit(0);
			}
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) / Valueget(GF[i].Number_2);
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "JNZ")
		{
			if (Valueget(GF[i].Number_1) != 0)
				i = stoi(GF[i].Name)-101;

			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "JEZ")
		{
			if (Valueget(GF[i].Number_1) == 0)
				i = stoi(GF[i].Name) -101;

			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "&")
		{
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) & Valueget(GF[i].Number_2);
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "|")
		{
			line[Posiget(GF[i].Name)] = Valueget(GF[i].Number_1) | Valueget(GF[i].Number_2);
			Valueout(i, posi);
			continue;
		}
		if (GF[i].Type == "CHAR" || GF[i].Type == "STR")
		{
			StringNums.insert({ GF[i].Number_1 ,"" });
			Valueout(i, posi);
			if (GF[i].Type == "CHAR")
				CharNums.insert(GF[i].Number_1);
			continue;
		}
		if (GF[i].Type == "FINISH")
		{
			cout << "ִ�н���";
			exit(0);
		}
		else
		{
			cout << "δ֪����";
		}
	}
}