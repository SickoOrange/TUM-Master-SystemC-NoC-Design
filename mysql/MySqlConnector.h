/*
 * MySqlConnector.h
 *
 *  Created on: 2017年2月25日
 *      Author: orange
 */
#include "systemc.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
using namespace std;

class MySqlConnector {
public:
	MySqlConnector();
	//~MySqlConnector(); //must be public
	bool connectMySQL();
	bool createDatabase(std::string& dbname);
	bool createTable(const std::string& create_table);
	void errorIntoMySQL();

public:
    int errorNum;                    //错误代号
    const char* errorInfo;             //错误提示

private:
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char server[10] = "localhost";
	char user[10] = "root";
	char password[11] = "9145190618";
	char database[10] = "";
};

