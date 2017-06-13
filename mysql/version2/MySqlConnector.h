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
#include <sstream>
using namespace std;

class MySqlConnector {
public:
	MySqlConnector();
	//~MySqlConnector(); //must be public
	bool connectMySQL();
	bool createDatabase(std::string& dbname);
	bool createTable(const std::string& create_table);
	bool producerWriteToMysql(const std::string& tableName,const std::string moduleName,int timeStap,int packetIdMinus1,int flowId);
	bool consumerWriteToMysql(const std::string& tableName,const std::string moduleName,int timeStap,int flitId,int packetId,const std::string isTail);
	void errorIntoMySQL();

	void startTransaction();
	void commitTransaction();

	

public:
    int errorNum;                    
    const char* errorInfo;             

private:
	MYSQL conn;
	char server[10] = "localhost";
	char user[10] = "root";
	char password[11] = "9145190618";
	char database[10] = "";
};

