#include <iostream>
#include <mysql.h>
#include "user.h"
#pragma comment(lib, "libmysql.lib")
#define NotLoggedIn 0;
#define LoggedIn 1;
using namespace std;

MYSQL* connection;
char nickname[12] = "";
bool login_status = false;
string command;

constexpr unsigned int Hash(const char* str)
{
	return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * Hash(str + 1) : 8603;
}

void UserFunction();

int main()
{
	connection = mysql_init(NULL);
	login_status = NotLoggedIn;
	connection = mysql_real_connect(connection, "192.168.56.6", "seunghyunlee", "1234", "inflearn", 4567, NULL, 0);
	if (!connection)
	{
		std::cout << "MySQL connection error : " << mysql_error(connection) << endl;
		return 1;
	}

	if (!mysql_set_character_set(connection, "euckr"))
		mysql_character_set_name(connection);

	while (command != "exit")
	{ 
		if (login_status == false)
		{
			UserFunction();
		}
		else
		{
			cout << "�ȳ��ϼ���, " << nickname << "��!" << endl;
			cout << "�޴��� �����ϼ���." << endl;
			cout << "================================================" << endl;
			cout << "1. ���� ���� Ȯ��" << endl;
			cout << "2. ���� ���� Ȯ��" << endl;
			cout << "3. ��ٱ���" << endl;
			cout << "4. ������ �����" << endl;
			cout << "5. ������ ���ǵ�" << endl;
			cout << "================================================" << endl;
			cout << "�Է�: ";
			cin >> command;
		}
	}

	mysql_close(connection);
	return 0;
}

void UserFunction()
{
	User user;
	char id[11], nickname[11], password[21];
	int main_command;
	string sub_command;
	std::cout << "================================================" << endl;
	std::cout << "1. ȸ������" << endl;
	std::cout << "2. �α���" << endl;
	std::cout << "================================================" << endl;
	cout << "�Է�: ";
	cin >> main_command;
	if (main_command == 1)
	{
		cout << "���̵�(10�� ����): ";
		cin >> id;
		cout << "�г���(10�� ����): ";
		cin >> nickname;
		cout << "��й�ȣ(20�� ����): ";
		cin >> password;
		user.SignUp(connection, id, nickname, password);
	}
	else if (main_command == 2)
	{
		cout << "���̵�: ";
		cin >> id;
		cout << "��й�ȣ: ";
		cin >> password;
		if (user.SignIn(connection, id, password))
		{
			strcat(nickname, user.getNickname(connection, id));
			login_status = LoggedIn;
		}
	}
	cout << endl;
}