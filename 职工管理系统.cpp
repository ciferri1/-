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

		cout << "����������ѡ��" << endl;
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 0: wm.ExitSystem();                //�˳�ϵͳ
			break;
		case 1: wm.Add_Emp();					//���ְ��
			break;
		case 2: wm.Show_Emp();					//��ʾְ��
			break;
		case 3:	wm.Del_Emp();					//ɾ��ְ��
			break;
		case 4: wm.Mod_Emp();					//�޸�ְ��
			break;
		case 5: wm.Find_Emp();                  //����ְ��
			break;
		case 6: wm.sort_Emp();                  //�������
			break;
		case 7: wm.Clean_File();                //����ĵ�
			break;
		default:
			system("cls");
		}
	}
	system("pause");

	return 0;
}