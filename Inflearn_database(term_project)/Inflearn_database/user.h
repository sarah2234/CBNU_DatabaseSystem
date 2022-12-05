#include <iostream>
#include <mysql.h>
#include <limits>
#pragma comment(lib, "libmysql.lib")
using namespace std;

class User
{
public:
	User();
	bool SignUp(MYSQL* connection, char user_id[11], char nickname[11], char password[21]);
	bool SignIn(MYSQL* connection, char* user_id, char* password);
	char* getNickname(MYSQL* connection, char* user_id);
	~User();

protected:

private:
	MYSQL_RES* result;
	MYSQL_ROW row;
};