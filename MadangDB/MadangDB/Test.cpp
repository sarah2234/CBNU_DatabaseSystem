#include <iostream>
#include <mysql.h>
#include <string>
#include <limits.h>
#include <string.h>
#pragma comment(lib, "libmysql.lib")

using namespace std;

void desc_table(MYSQL* connection, string table);
void select_from_table(MYSQL* connection, string table, string attribute, string condition = std::string());
void insert_values(MYSQL* connection, string table, string attribute_list, string values_list);

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
		cout << "MySQL connection succeeded" << endl;
	
	if (!mysql_set_character_set(connection, "euckr"))
		cout << "New client character set: " << mysql_character_set_name(connection) << endl;

	desc_table(connection, "Book");
	insert_values(connection, "Customer", "custid, name, address, phone", "1, '이승현', '용인', 01012345678");
	select_from_table(connection, "Customer", "*");


	
	mysql_close(connection);

	return 0;
}

void desc_table(MYSQL* connection, string table)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	string command = "DESC " + table;

	int query_stat = mysql_query(connection, command.c_str());
	if (query_stat != 0)
	{
		cout << "MySQL query error : " << mysql_error(connection) << endl;
		return;
	}

	result = mysql_store_result(connection);

	cout << "================================================================================" << endl;
	cout.width(20);
	cout << "Field";
	cout.width(20);
	cout << "Type";
	cout.width(20);
	cout << "NULL";
	cout.width(20);
	cout << "Key";
	cout << endl;
	cout << "================================================================================" << endl;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		cout.width(20);
		cout << row[0];
		cout.width(20);
		cout << row[1];
		cout.width(20);
		cout << row[2];
		cout.width(20);
		cout << row[3];
		cout << endl;
	}
	cout << "================================================================================" << endl << endl;

	mysql_free_result(result);
}

void select_from_table(MYSQL* connection, string table, string attribute, string condition)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	string command = "DESC " + table;

	int query_stat = mysql_query(connection, command.c_str());
	if (query_stat != 0)
	{
		cout << "MySQL query error : " << mysql_error(connection) << endl;
		return;
	}

	result = mysql_store_result(connection);
	cout << "================================================================================" << endl;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		cout.width(20);
;		cout << std::right << row[0];
	}
	cout << endl;
	cout << "================================================================================" << endl;
	
	///
	command = "SELECT " + attribute + " FROM " + table;
	if (condition != "")
		command += " WHERE " + condition;
	query_stat = mysql_query(connection, command.c_str());

	result = mysql_store_result(connection);

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		cout.width(20);
		cout << row[0];
		cout.width(20);
		cout << row[1];
		cout.width(20);
		cout << row[2];
		cout.width(20);
		cout << row[3] << endl;
	}
	cout << "================================================================================" << endl << endl;
	mysql_free_result(result);
}

void insert_values(MYSQL* connection, string table, string attribute, string values)
{
	MYSQL_ROW row;
	string command = "INSERT INTO " + table + " (" + attribute + ") VALUES (" + values + ")";
	cout << endl << "command : " << command << endl;

	int query_stat = mysql_query(connection, command.c_str());
	if (query_stat != 0)
	{
		cout << "MySQL query error : " << mysql_error(connection) << endl << endl;
		return;
	}
	cout << "Query OK, 1 row affected" << endl << endl;
}