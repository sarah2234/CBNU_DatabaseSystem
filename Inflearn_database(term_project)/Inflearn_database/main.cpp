#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
#include <windows.h>
#pragma comment(lib, "libmysql.lib")
using namespace std;

MYSQL* connection;
vector<char*> tables;

constexpr unsigned int Hash(const char* str)
{
	return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * Hash(str + 1) : 8603;
}
void printQueryResult(const string query);

int main()
{
	connection = mysql_init(NULL);
	connection = mysql_real_connect(connection, "192.168.56.6", "seunghyunlee", "1234", "inflearn", 4567, NULL, 0);
	if (!connection)
	{
		std::cout << "MySQL connection error : " << mysql_error(connection) << endl;
		return 1;
	}

	if (!mysql_set_character_set(connection, "euckr"))
		mysql_character_set_name(connection);

	int main_command = 1;
	string sub_command = "";
	string selected_table = "";
	while(main_command)
	{
		if (main_command == 1)
		{
			std::cout << "==========================================================================================" << endl;
			std::cout << "1. ���̺� ��� ����               2. ���̺� ���� ����					 	                " << endl;
			std::cout << "3. ���̺� ����                    4. ���α׷� ����										" << endl;
			std::cout << "==========================================================================================" << endl;
			std::cout << "(cls: ȭ�� �����)" << endl << endl;
			cout << "��� �Է�>> ";
			cin >> sub_command;
			cout << endl;

			switch (Hash(sub_command.c_str()))
			{
			case Hash("1"):
				printQueryResult("SHOW TABLES");
				cout << "-End of Results-" << endl;
				break;
			case Hash("2"):
				cout << "� ���̺��� ������ ���ðڽ��ϱ�?" << endl;
				printQueryResult("SHOW TABLES");
				cout << "���̺� ��ȣ �Է�>> ";
				
				break;
			case Hash("3"):
				cout << "� ���̺��� �����Ͻðڽ��ϱ�?>> " << endl;
				printQueryResult("SHOW TABLES");
				cout << "���̺� ��ȣ �Է�>> ";
				cin >> selected_table;
				main_command = 2;
				break;
			case 3:
				main_command = 0;
				std::cout << "���α׷��� ����Ǿ����ϴ�." << endl;
				break;
			case Hash("cls"):
				system("cls");
				break;
			default:
				std::cout << "�߸��� �Է°��Դϴ�." << endl;
				break;
			}
		}
		else if (main_command == 2)
		{
			cout << tables[stoi(selected_table) - 1] << endl;
			std::cout << "==========================================================================================" << endl;
			std::cout << "1. ���̺� ���� ����							    2. ������ ��ȸ							" << endl;
			std::cout << "3. ������ ã��									4. ������ �Է��ϱ�						" << endl;
			std::cout << "5. ������ �����ϱ�								6. ������ ��ü �����ϱ�					" << endl;
			std::cout << "7. ������ �����ϱ�								8. ������ ��ü �����ϱ�					" << endl;
			std::cout << "9. �ڷ� ����																				" << endl;
			std::cout << "==========================================================================================" << endl;
			std::cout << "(cls: ȭ�� �����)" << endl << endl;
			cout << "��� �Է�>> ";
			cin >> main_command;
			cout << endl;


			switch (main_command)
			{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case Hash("cls"):
				system("cls");
				break;
			default:
				break;
			}
		}

		cout << endl << endl;
	}

	mysql_close(connection);
	return 0;
}

void printQueryResult(const string query)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_stat = mysql_query(connection, query.c_str());
	unsigned int num_of_fields, num_of_rows, num_of_tuples;

	if(query_stat !=0)
	{
		cout << "�߸��� �����Դϴ�. (" << mysql_error(connection) << ")" << endl << endl;
		return;
	}

	string query_type = query.substr(0, query.find(" "));
	switch (Hash(query_type.c_str()))
	{
	case Hash("DESC"):
		result = mysql_store_result(connection);
		std::cout << "==========================================================================================" << endl;
		std::cout.width(15);
		std::cout << "Field";
		std::cout.width(15);
		std::cout << "Type";
		std::cout.width(15);
		std::cout << "NULL";
		std::cout.width(15);
		std::cout << "Key";
		std::cout.width(15);
		std::cout << "Default";
		std::cout.width(15);
		std::cout << "Extra" << endl;
		std::cout << "==========================================================================================" << endl;

		num_of_fields = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)) != NULL) // ����� �� �پ� row�� ����
		{
			for (int i = 0; i < num_of_fields; i++)
			{
				if (row[i]) // �� �࿡ ��ȿ�� �ʵ尪 ������ŭ ���
				{
					std::cout.width(15);
					std::cout << row[i];
				}
			}
			std::cout << endl;
		}
		std::cout << "==========================================================================================" << endl << endl;
		
		mysql_free_result(result); // mysql_store_result�� ���� �޸𸮸� ����
		break;

	case Hash("SELECT"):
		result = mysql_store_result(connection);

		std::cout << "================================================================================" << endl;
		num_of_fields = mysql_num_fields(result);
		num_of_tuples = 0; // �߰��� �� Ʃ���� ����
		while ((row = mysql_fetch_row(result)) != NULL)
		{
			for (int i = 0; i < num_of_fields; i++)
			{
				std::cout.width(20);
				std::cout << row[i];
			}
			std::cout << endl;
			num_of_tuples++;
		}
		std::cout << "================================================================================" << endl;
		std::cout.width(20 * num_of_fields);

		std::cout << "Total: " << num_of_tuples << endl << endl;

		mysql_free_result(result);
		break;

	case Hash("SHOW"):
		result = mysql_store_result(connection);
		num_of_rows = mysql_num_rows(result);

		std::cout << "================================================================================" << endl;
		std::cout << "Tables in Inflearn" << endl;
		std::cout << "================================================================================" << endl;
		if (tables.size() == 0)
		{
			while ((row = mysql_fetch_row(result)) != NULL)
			{
				tables.push_back(row[0]);
			}
		}
		for (int i = 0; i < tables.size(); i++)
		{
			cout << i + 1 << ". " << tables[i] << endl;
		}

		std::cout << "================================================================================" << endl;


		mysql_free_result(result);
		break;
	default:
		cout << "��õ��� ���� �������Դϴ�." << endl << endl;
		break;
	}
}