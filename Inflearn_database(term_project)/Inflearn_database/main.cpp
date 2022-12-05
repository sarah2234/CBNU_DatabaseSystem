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
			cout << "안녕하세요, " << nickname << "님!" << endl;
			cout << "메뉴를 선택하세요." << endl;
			cout << "================================================" << endl;
			cout << "1. 보유 쿠폰 확인" << endl;
			cout << "2. 보유 강의 확인" << endl;
			cout << "3. 장바구니" << endl;
			cout << "4. 인프런 강사들" << endl;
			cout << "5. 인프런 강의들" << endl;
			cout << "================================================" << endl;
			cout << "입력: ";
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
	std::cout << "1. 회원가입" << endl;
	std::cout << "2. 로그인" << endl;
	std::cout << "================================================" << endl;
	cout << "입력: ";
	cin >> main_command;
	if (main_command == 1)
	{
		cout << "아이디(10자 제한): ";
		cin >> id;
		cout << "닉네임(10자 제한): ";
		cin >> nickname;
		cout << "비밀번호(20자 제한): ";
		cin >> password;
		user.SignUp(connection, id, nickname, password);
	}
	else if (main_command == 2)
	{
		cout << "아이디: ";
		cin >> id;
		cout << "비밀번호: ";
		cin >> password;
		if (user.SignIn(connection, id, password))
		{
			strcat(nickname, user.getNickname(connection, id));
			login_status = LoggedIn;
		}
	}
	cout << endl;
}