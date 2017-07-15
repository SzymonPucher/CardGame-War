/*
#include <iostream>
#include <mysql.h>

using namespace std;

MYSQL mysql, *connection;
MYSQL_RES result;
MYSQL_ROW row;

char * ip = (char*)"192.168.49.131";
char * usr = (char*)"root";
char * pass = (char*)"admin";
char * db = (char*)"vcs";

int query_state;

int main(int argc, char **argv)
{
	mysql_init(&mysql);

	connection = mysql_real_connect(&mysql, ip, usr, pass, db, 0, NULL, 0);

	if (connection == NULL)
	{
		cout << mysql_error(&mysql) << endl;
	}

	else
	{
		(mysql_query(&mysql, "INSERT into 'vcs'.'users' ('id', 'fname', 'sname') VALUES ('3', 'rana', 'sameer')"));
		if (query_state != 0) {
			cout << mysql_error(connection) << endl;
			return 1;
		}
	}
	mysql_close(&mysql);

}
*/