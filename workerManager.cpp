#include "workerManager.h"

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FileName, ios::in);

	//1、文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在!" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//3、文件存在并记录数据
	int num = get_EmpNum();
	cout << "职工人数为: " << num << endl;
	this->m_EmpNum = num;

	//初始化员工
	this->m_EmpArray = new worker * [this->m_EmpNum];
	this->Emp_init();

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号: " << this->m_EmpArray[i]->m_id << " "
			<< "姓名: " << this->m_EmpArray[i]->m_name << " "
			<< "部门编号: " << this->m_EmpArray[i]->m_DeptId << endl;
	}
}

workerManager::~workerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}
//菜单
void workerManager::show_view()
{
	cout << "*************************************" << endl;
	cout << "*********欢迎使用职工管理系统！********" << endl;
	cout << "********** 0.退出管理程序 ************" << endl;
	cout << "********** 1.增加职工信息 ************" << endl;
	cout << "********** 2.显示职工信息 ************" << endl;
	cout << "********** 3.删除离职职工 ************" << endl;
	cout << "********** 4.修改职工信息 ************" << endl;
	cout << "********** 5.查找职工信息 ************" << endl;
	cout << "********** 6.按照编号排序 ************" << endl;
	cout << "********** 7.清空所有文档 ************" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}
//退出系统
void workerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);  //退出程序
}

//添加职工
void workerManager::Add_Emp()
{
	cout << "请输入添加职工的数量: " << endl;

	int add_Num;    //保存输入的职工数量
	cin >> add_Num;

	if (add_Num > 0)
	{
		//计算新空间的大小
		int newSize = this->m_EmpNum + add_Num;
		//开辟新空间
		worker** newSpace = new worker * [newSize];
		//把旧数组数据迁移到新数组
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = m_EmpArray[i];
			}
		}

		for (int i = 0; i < add_Num; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			worker* w = NULL;

			switch (dSelect)
			{
			case 1: w = new Employee(id, name, 1);
				break;
			case 2: w = new manager(id, name, 2);
				break;
			case 3: w = new Boss(id, name, 3);
				break;

			default:
				break;
			}

			//将新职工添加到数组中
			newSpace[this->m_EmpNum + i] = w;
		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//更新数组指向
		this->m_EmpArray = newSpace;
		//更新职工人数
		this->m_EmpNum = newSize;

		this->save();
		cout << "成功添加" << add_Num << "名新职工!" << endl;
	}
	else
	{
		cout << "输入的数据有误" << endl;
	}

	system("pause");
	system("cls");
}


void workerManager::save()
{
	ofstream ofs;
	ofs.open(FileName, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//统计职工人数
int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FileName, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	return num;
}

//初始化员工
void workerManager::Emp_init()
{
	ifstream ifs;
	ifs.open(FileName, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* w = NULL;
		if (did == 1)
		{
			w = new Employee(id, name, did);
		}
		else if (did == 2)
		{
			w = new manager(id, name, did);
		}
		else
		{
			w = new Boss(id, name, did);
		}

		this->m_EmpArray[index++] = w;
	}
	
	ifs.close();
}


//显示所有职工
void workerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int workerManager::IsExist(int id)
{
	int idx = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			idx = i;
			break;
		}
	}
	return idx;
}

void workerManager::Del_Emp()
{
	

	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工编号: " << endl;
	
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//说明职工存在
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];//数据前移覆盖
			}
			this->m_EmpNum--;
			// 同步更新文件
			this->save();
			cout << "删除成功!" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工!" << endl;
		}
	}

	system("pause");
	system("cls");
}

//修改职工信息
void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号: " << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];

			int newId;
			string newName;
			int dSelect;

			cout << "查到: " << id << "号员工,请输入新职工号: " << endl;
			cin >> newId;
			cout << "请输入新姓名: " << endl;
			cin >> newName;
			cout << "请选择该职工的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			worker* w = NULL;

			switch (dSelect)
			{
			case 1: w = new Employee(newId, newName, 1);
				break;
			case 2: w = new manager(newId, newName, 2);
				break;
			case 3: w = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}
			//更新到数组
			this->m_EmpArray[ret] = w;
			cout << "修改成功! ";
			//保存到文件
			this->save();
		}
		else
		{
			cout << "修改失败,查无此人! " << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空! " << endl;
	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "请输入要查找的职工编号: " << endl;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功，该职工信息如下: " << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人! " << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入查找的姓名: " << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功, " << this->m_EmpArray[i]->m_name << "的信息如下" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}

				if (!flag)
				{
					cout << "查找失败，查无此人！" << endl;
				}
			}
		}
		else
		{
			cout << "输入有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序
void workerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空! " << endl;
	}
	else
	{
		cout << "请选择排序方式: " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrmax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minOrmax = j;
					}
				}
				else  //降序
				{
					if (this->m_EmpArray[minOrmax]->m_id < this->m_EmpArray[j]->m_id)
					{
						minOrmax = j;
					}
				}
			}
			if (minOrmax != i)
			{
				worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrmax];
				m_EmpArray[minOrmax] = temp;
			}
		}
	}
	cout << "排序成功，排序后结果为: " << endl;
	this->save();
	this->Show_Emp();

	system("pause");
	system("cls");
}

//文件清空
void workerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FileName, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)//删除堆区每个职工对象
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
			
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}