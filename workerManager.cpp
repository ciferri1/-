#include "workerManager.h"

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FileName, ios::in);

	//1���ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������!" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��!" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//3���ļ����ڲ���¼����
	int num = get_EmpNum();
	cout << "ְ������Ϊ: " << num << endl;
	this->m_EmpNum = num;

	//��ʼ��Ա��
	this->m_EmpArray = new worker * [this->m_EmpNum];
	this->Emp_init();

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ�����: " << this->m_EmpArray[i]->m_id << " "
			<< "����: " << this->m_EmpArray[i]->m_name << " "
			<< "���ű��: " << this->m_EmpArray[i]->m_DeptId << endl;
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
//�˵�
void workerManager::show_view()
{
	cout << "*************************************" << endl;
	cout << "*********��ӭʹ��ְ������ϵͳ��********" << endl;
	cout << "********** 0.�˳�������� ************" << endl;
	cout << "********** 1.����ְ����Ϣ ************" << endl;
	cout << "********** 2.��ʾְ����Ϣ ************" << endl;
	cout << "********** 3.ɾ����ְְ�� ************" << endl;
	cout << "********** 4.�޸�ְ����Ϣ ************" << endl;
	cout << "********** 5.����ְ����Ϣ ************" << endl;
	cout << "********** 6.���ձ������ ************" << endl;
	cout << "********** 7.��������ĵ� ************" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}
//�˳�ϵͳ
void workerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);  //�˳�����
}

//���ְ��
void workerManager::Add_Emp()
{
	cout << "���������ְ��������: " << endl;

	int add_Num;    //���������ְ������
	cin >> add_Num;

	if (add_Num > 0)
	{
		//�����¿ռ�Ĵ�С
		int newSize = this->m_EmpNum + add_Num;
		//�����¿ռ�
		worker** newSpace = new worker * [newSize];
		//�Ѿ���������Ǩ�Ƶ�������
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

			cout << "�������" << i + 1 << "����ְ�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			//����ְ����ӵ�������
			newSpace[this->m_EmpNum + i] = w;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//��������ָ��
		this->m_EmpArray = newSpace;
		//����ְ������
		this->m_EmpNum = newSize;

		this->save();
		cout << "�ɹ����" << add_Num << "����ְ��!" << endl;
	}
	else
	{
		cout << "�������������" << endl;
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

//ͳ��ְ������
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

//��ʼ��Ա��
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


//��ʾ����ְ��
void workerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ�����: " << endl;
	
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//˵��ְ������
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];//����ǰ�Ƹ���
			}
			this->m_EmpNum--;
			// ͬ�������ļ�
			this->save();
			cout << "ɾ���ɹ�!" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��!" << endl;
		}
	}

	system("pause");
	system("cls");
}

//�޸�ְ����Ϣ
void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ�����: " << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];

			int newId;
			string newName;
			int dSelect;

			cout << "�鵽: " << id << "��Ա��,��������ְ����: " << endl;
			cin >> newId;
			cout << "������������: " << endl;
			cin >> newName;
			cout << "��ѡ���ְ���ĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//���µ�����
			this->m_EmpArray[ret] = w;
			cout << "�޸ĳɹ�! ";
			//���浽�ļ�
			this->save();
		}
		else
		{
			cout << "�޸�ʧ��,���޴���! " << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��! " << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "������Ҫ���ҵ�ְ�����: " << endl;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ����: " << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���! " << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "��������ҵ�����: " << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ�, " << this->m_EmpArray[i]->m_name << "����Ϣ����" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}

				if (!flag)
				{
					cout << "����ʧ�ܣ����޴��ˣ�" << endl;
				}
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����
void workerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��! " << endl;
	}
	else
	{
		cout << "��ѡ������ʽ: " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrmax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minOrmax = j;
					}
				}
				else  //����
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
	cout << "����ɹ����������Ϊ: " << endl;
	this->save();
	this->Show_Emp();

	system("pause");
	system("cls");
}

//�ļ����
void workerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FileName, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)//ɾ������ÿ��ְ������
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
		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}