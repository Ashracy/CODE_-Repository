#include"SimpleIni.h"
#include<iostream>
using namespace std;
void test();
int main()
{
	test();
	system("pause");
}

void test()
{
	CSimpleIni ini;
	ini.SetUnicode();
	ini.LoadFile("F:/a.ini");
	
	const char * a=ini.GetValue("asd", "#as",NULL);//��ȡvalue
	
	ini.SetValue("new section", "new key", "value");//���Ļ�����Ӽ�ֵ
	ini.SetValue("new section", NULL, NULL);//����µ�ѡ����
	
	ini.Delete("asd", NULL);//ɾ��ѡ����
	ini.Delete("asd", "a",true);//ɾ����

	string str;
	ini.Save(str);//���浽�ַ���
	ini.SaveFile("F:/a.ini");//���浽�ļ�


}