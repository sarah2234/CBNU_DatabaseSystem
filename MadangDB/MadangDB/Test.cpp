#include <iostream>
#include <mysql.h>
#include <string>
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
	if (!connection) // MySQL 연결 실패
	{
		cout << "MySQL connection error : " << mysql_error(connection) << endl;
		return 1;
	}
	
	if (!mysql_set_character_set(connection, "euckr")) // 인코딩 euc-kr로 변경
		cout << "New client character set: " << mysql_character_set_name(connection) << endl << endl;

	// MySQL 쿼리 입력 (ex: mysql> SELECT * FROM Book;)
	string query;
	while(true)
	{
		cout << "mysql> ";
		getline(cin, query); // 쿼리 입력

		if (!stricmp(query.c_str(), "quit") || !stricmp(query.c_str(), "exit")) break; // quit 또는 exit을 입력받으면 쿼리 입력 종료

		int query_stat = mysql_query(connection, query.c_str());
		if (query_stat != 0) // 쿼리 에러
		{
			cout << mysql_error(connection) << endl << endl; // 에러 출력
			continue;
		}

		// 쿼리 성공
		string query_type = query.substr(0, query.find(" ")); // 첫 번째 단어 파싱 후 어떤 쿼리인지 파악
		if (stricmp(query_type.c_str(), "DESC") == 0) // DESC 쿼리일 때
		{
			result = mysql_store_result(connection); // 쿼리 결과 저장
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
			while ((row = mysql_fetch_row(result)) != NULL) // 결과를 한 줄씩 row에 저장
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (row[i]) // 각 행에 유효한 필드값 개수만큼 출력
					{
						cout.width(15);
						cout << row[i];
					}
				}
				cout << endl;
			}
			cout << "==========================================================================================" << endl << endl;
			mysql_free_result(result); // mysql_store_result에 사용된 메모리를 해제
		}

		else if(stricmp(query_type.c_str(), "SELECT") == 0) // SELECT 쿼리일 때
		{
			result = mysql_store_result(connection);
			cout << "================================================================================" << endl;
			unsigned int num_fields = mysql_num_fields(result);
			unsigned int num_tuples = 0; // 발견한 총 튜플의 개수
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
			cout << "Query OK" << endl << endl; // 쿼리문 실행 성공
		}
	}
	
	mysql_close(connection); // MySQL과의 연결 종료
	
	return 0;
}