#include <iostream>
#include <mysql.h>
#include <string>
#pragma comment(lib, "libmysql.lib")

using namespace std;

int main()
{
	MYSQL* connection;
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_stat;

	connection = mysql_init(NULL);
	connection = mysql_real_connect(connection, "192.168.56.6", "seunghyunlee", "1234", "madang", 4567, NULL, 0);
	if (!connection) // MySQL ���� ����
	{
		cout << "MySQL connection error : " << mysql_error(connection) << endl;
		return 1;
	}

	if (!mysql_set_character_set(connection, "euckr")) // ���ڵ� euc-kr�� ����
		cout << "New client character set: " << mysql_character_set_name(connection) << endl << endl;

	// MySQL ���� �Է� (ex: mysql> SELECT * FROM Book;)
	string query;
	while (true)
	{
		cout << "mysql> ";
		getline(cin, query); // ���� �Է�

		if (!strcmp(query.c_str(), "quit") || !strcmp(query.c_str(), "exit")) break; // quit �Ǵ� exit�� �Է¹����� ���� �Է� ����

		int query_stat = mysql_query(connection, query.c_str());
		if (query_stat != 0) // ���� ����
		{
			cout << mysql_error(connection) << endl << endl; // ���� ���
			continue;
		}

		// ���� ����
		string query_type = query.substr(0, query.find(" ")); // ù ��° �ܾ� �Ľ� �� � �������� �ľ�
		if (strcmp(query_type.c_str(), "DESC") == 0) // DESC ������ ��
		{
			result = mysql_store_result(connection); // ���� ��� ����
			cout << "==========================================================================================" << endl;
			cout.width(15);
			cout << "Field";
			cout.width(15);
			cout << "Type";
			cout.width(15);
			cout << "NULL";
			cout.width(15);
			cout << "Key";
			cout.width(15);
			cout << "Default";
			cout.width(15);
			cout << "Extra" << endl;
			cout << "==========================================================================================" << endl;

			unsigned int num_fields = mysql_num_fields(result);
			while ((row = mysql_fetch_row(result)) != NULL) // ����� �� �پ� row�� ����
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (row[i]) // �� �࿡ ��ȿ�� �ʵ尪 ������ŭ ���
					{
						cout.width(15);
						cout << row[i];
					}
				}
				cout << endl;
			}
			cout << "==========================================================================================" << endl << endl;
			mysql_free_result(result); // mysql_store_result�� ���� �޸𸮸� ����
		}

		else if (strcmp(query_type.c_str(), "SELECT") == 0) // SELECT ������ ��
		{
			result = mysql_store_result(connection);
			cout << "================================================================================" << endl;
			unsigned int num_fields = mysql_num_fields(result);
			unsigned int num_tuples = 0; // �߰��� �� Ʃ���� ����
			while ((row = mysql_fetch_row(result)) != NULL)
			{
				for (int i = 0; i < num_fields; i++)
				{
					cout.width(20);
					cout << row[i];
				}
				cout << endl;
				num_tuples++;
			}
			cout << "================================================================================" << endl;
			cout.width(20 * num_fields);
			cout << "Total: " << num_tuples << endl << endl;
			mysql_free_result(result);
		}

		else
		{
			cout << "Query OK" << endl << endl; // ������ ���� ����
		}
	}

	mysql_close(connection); // MySQL���� ���� ����

	return 0;
}