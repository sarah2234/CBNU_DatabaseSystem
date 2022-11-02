#include <iostream>
#include <string>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")

using namespace std;

int main()
{
	MYSQL *connection;
	MYSQL_RES* result;
	MYSQL_ROW row;
	
	int query_stat;

	connection = mysql_init(NULL);
	connection = mysql_real_connect(connection, "192.168.56.6", "seunghyunlee", "1234", "madang", 4567, NULL, 0);
	if (!connection)
	{
		cout << "MySQL connection error : " << mysql_error(connection) << endl;
		return 1;
	}
	else
		cout << "success" << endl;
	
	if (!mysql_set_character_set(connection, "euckr"))
		cout << "New client character set: " << mysql_character_set_name(connection) << endl;
	query_stat = mysql_query(connection, "Select * FROM Book");
	if (query_stat != 0)
	{
		cout << "MySQL query error : " << mysql_error(connection) << endl;
		return 1;
	}

	result = mysql_store_result(connection);
	
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		cout << row[0] << " " << row[1] << " " << row[2] << " " << endl;
	}



	mysql_free_result(result);
	mysql_close(connection);

	return 0;
}