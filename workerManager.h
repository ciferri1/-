#pragma once
#include <iostream>
using namespace std;
#include "workerManager.h";
#include "Boss.h"
#include "manager.h"
#include "Employee.h"

#include <fstream>
#define FileName "empFile.txt"

class workerManager
{
public:

	workerManager();

	//显示菜单
	void show_view();

	//添加职工
	void Add_Emp();
	// 保存文件
	void save();

	//统计职工人数
	int get_EmpNum();

	//初始化员工
	void Emp_init();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//查找职工编号
	int IsExist(int id);

	//修改职工信息
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序
	void sort_Emp();

	//文件清空
	void Clean_File();

	//退出系统
	void ExitSystem();

	~workerManager();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	worker** m_EmpArray;

	//文件打开标志
	bool m_FileIsEmpty;
};