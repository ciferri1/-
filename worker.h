#pragma once
#include<iostream>
#include<string>
using namespace std;

class worker
{
public:

	//显示个人信息
	virtual void showInfo() = 0;

	//获取岗位名称
	virtual string getDeptName() = 0;


	int m_id;
	string m_name;
	int m_DeptId;
};
