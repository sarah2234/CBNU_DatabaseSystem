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
			std::cout << "1. 테이블 목록 보기               2. 테이블 설명 보기					 	                " << endl;
			std::cout << "3. 테이블 선택                    4. 프로그램 종료										" << endl;
			std::cout << "==========================================================================================" << endl;
			std::cout << "(cls: 화면 지우기)" << endl << endl;
			cout << "명령 입력>> ";
			cin >> sub_command;
			cout << endl;

			switch (Hash(sub_command.c_str()))
			{
			case Hash("1"):
				printQueryResult("SHOW TABLES");
				cout << "-End of Results-" << endl;
				break;
			case Hash("2"):
				cout << "어떤 테이블의 설명을 보시겠습니까?" << endl;
				printQueryResult("SHOW TABLES");
				cout << "테이블 번호 입력>> ";
				
				break;
			case Hash("3"):
				cout << "어떤 테이블을 선택하시겠습니까?>> " << endl;
				printQueryResult("SHOW TABLES");
				cout << "테이블 번호 입력>> ";
				cin >> selected_table;
				main_command = 2;
				break;
			case 3:
				main_command = 0;
				std::cout << "프로그램이 종료되었습니다." << endl;
				break;
			case Hash("cls"):
				system("cls");
				break;
			default:
				std::cout << "잘못된 입력값입니다." << endl;
				break;
			}
		}
		else if (main_command == 2)
		{
			cout << tables[stoi(selected_table) - 1] << endl;
			std::cout << "==========================================================================================" << endl;
			std::cout << "1. 테이블 구조 보기							    2. 데이터 조회							" << endl;
			std::cout << "3. 데이터 찾기									4. 데이터 입력하기						" << endl;
			std::cout << "5. 데이터 수정하기								6. 데이터 전체 수정하기					" << endl;
			std::cout << "7. 데이터 삭제하기								8. 데이터 전체 삭제하기					" << endl;
			std::cout << "9. 뒤로 가기																				" << endl;
			std::cout << "==========================================================================================" << endl;
			std::cout << "(cls: 화면 지우기)" << endl << endl;
			cout << "명령 입력>> ";
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
		cout << "잘못된 접근입니다. (" << mysql_error(connection) << ")" << endl << endl;
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
		while ((row = mysql_fetch_row(result)) != NULL) // 결과를 한 줄씩 row에 저장
		{
			for (int i = 0; i < num_of_fields; i++)
			{
				if (row[i]) // 각 행에 유효한 필드값 개수만큼 출력
				{
					std::cout.width(15);
					std::cout << row[i];
				}
			}
			std::cout << endl;
		}
		std::cout << "==========================================================================================" << endl << endl;
		
		mysql_free_result(result); // mysql_store_result에 사용된 메모리를 해제
		break;

	case Hash("SELECT"):
		result = mysql_store_result(connection);

		std::cout << "================================================================================" << endl;
		num_of_fields = mysql_num_fields(result);
		num_of_tuples = 0; // 발견한 총 튜플의 개수
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
		cout << "명시되지 않은 쿼리문입니다." << endl << endl;
		break;
	}
}