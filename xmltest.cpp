// xmlTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "PrjXml.h"



int main() {
	
	ProjXml::Instance().parseXml("settingdata.xml");
	
	ProjXml::Instance().search("ID");
	return 0;
}


