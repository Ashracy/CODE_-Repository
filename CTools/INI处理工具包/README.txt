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
	
	const char * a=ini.GetValue("asd", "#as",NULL);//获取value
	
	ini.SetValue("new section", "new key", "value");//更改或者添加键值
	ini.SetValue("new section", NULL, NULL);//添加新的选择器
	
	ini.Delete("asd", NULL);//删除选择器
	ini.Delete("asd", "a",true);//删除键

	string str;
	ini.Save(str);//保存到字符串
	ini.SaveFile("F:/a.ini");//保存到文件


}