#include "Employee.h"

Employee::Employee(int id, string name, int Deptid)
{
	this->m_id = id;
	this->m_name = name;
	this->m_DeptId = Deptid;
}


void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}


string Employee::getDeptName()
{
	return string("Ա��");
}