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

	//��ʾ�˵�
	void show_view();

	//���ְ��
	void Add_Emp();
	// �����ļ�
	void save();

	//ͳ��ְ������
	int get_EmpNum();

	//��ʼ��Ա��
	void Emp_init();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//����ְ�����
	int IsExist(int id);

	//�޸�ְ����Ϣ
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����
	void sort_Emp();

	//�ļ����
	void Clean_File();

	//�˳�ϵͳ
	void ExitSystem();

	~workerManager();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	worker** m_EmpArray;

	//�ļ��򿪱�־
	bool m_FileIsEmpty;
};