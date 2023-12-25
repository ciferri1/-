#include <iostream>
using namespace std;
#include "workerManager.h"
#include "Employee.h"
#include "manager.h"
#include "Boss.h"

int main()
{
	workerManager wm;

	
	while (true)
	{
		wm.show_view();

		cout << "请输入您的选择：" << endl;
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 0: wm.ExitSystem();                //退出系统
			break;
		case 1: wm.Add_Emp();					//添加职工
			break;
		case 2: wm.Show_Emp();					//显示职工
			break;
		case 3:	wm.Del_Emp();					//删除职工
			break;
		case 4: wm.Mod_Emp();					//修改职工
			break;
		case 5: wm.Find_Emp();                  //查找职工
			break;
		case 6: wm.sort_Emp();                  //编号排序
			break;
		case 7: wm.Clean_File();                //清空文档
			break;
		default:
			system("cls");
		}
	}
	system("pause");

	return 0;
}