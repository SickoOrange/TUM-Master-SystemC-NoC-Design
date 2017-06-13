/*
 * mytest.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: orange
 */
#include <systemc.h>
#include <iostream>
#include "MySqlConnector.h"
int sc_main(int argc, char* argv[]) {
	//MySqlCOnnector::ConnectMysql();
MySqlConnector connector;
std::string dataName="systemc";
connector.connectMySQL();
connector.createDatabase(dataName);
connector.createTable(dataName);
//bool h=connector.createDatabase(dataName);
}

