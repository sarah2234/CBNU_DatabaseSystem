#include "user.h"

User::User()
{
	result = NULL;
}

bool User::SignUp(MYSQL* connection, char user_id[10], char nickname[10], char password[20])
{
	char query[CHAR_MAX] = "INSERT INTO User (user_id,  nickname, password) VALUE (";
	char refineChar[CHAR_MAX] = "'";
	strcat(refineChar, user_id);
	strcat(refineChar, "'");
	strcpy(user_id, refineChar);
	strcpy(refineChar, "'");

	strcat(refineChar, nickname);
	strcat(refineChar, "'");
	strcpy(nickname, refineChar);
	strcpy(refineChar, "'");

	strcat(refineChar, password);
	strcat(refineChar, "'");
	strcpy(password, refineChar);
	strcpy(refineChar, "'");

	strcat(query, user_id);
	strcat(query, ", ");
	strcat(query, nickname);
	strcat(query, ", ");
	strcat(query, password);
	strcat(query, ")");
	//cout << query << endl;
	int query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		cout << "�߸��� �����Դϴ�. (" << mysql_error(connection) << ")" << endl << endl;
		return false;
	}

	cout << "ȸ�� ���Կ� �����Ͽ����ϴ�!" << endl;
	cout << endl;
	result = mysql_store_result(connection);
	return true;
}

bool User::SignIn(MYSQL* connection, char* user_id, char* password)
{
	char query[CHAR_MAX] = "SELECT * FROM USER WHERE user_id=";
	char refineChar[CHAR_MAX] = "'";

	strcat(refineChar, user_id);
	strcat(refineChar, "'");
	strcpy(user_id, refineChar);
	strcpy(refineChar, "'");

	strcat(query, user_id);

	strcat(query, " AND password=");
	strcat(refineChar, password);
	strcat(refineChar, "'");
	strcpy(password, refineChar);
	strcpy(refineChar, "'");

	strcpy(query, password);
	//cout << query << endl;

	int query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		cout << "�α��� ����!" << endl;
		return true;
	}
	else
	{
		cout << "�α��� ����!" << endl;
		return false;
	}

	cout << endl;
}

char* User::getNickname(MYSQL* connection, char* user_id)
{
	char query[CHAR_MAX] = "SELECT * FROM User WHERE user_id=";
	strcat(query, user_id);
	int query_stat = mysql_query(connection, query);
	//cout << query << endl;

	result = mysql_store_result(connection);
	if (result == NULL)
	{
		cout << "��ġ�ϴ� ������ ã�� �� �����ϴ�." << endl << endl;
		return NULL;
	}

	row = mysql_fetch_row(result);
	return row[1];
}

User::~User()
{
	if (result)
		mysql_free_result(result);
}
