#pragma once
#include<iostream>
#include<string>
#include "worker.h"
using namespace std;

class Employee : public worker
{
public:
	Employee(int id, string name,int Deptid);

	void showInfo();

	string getDeptName();
};
