/*
 * MySqlCOnnector.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: orange
 */

#include "MySqlConnector.h"
#include <iostream>


MySqlConnector::MySqlConnector(): errorNum(0),errorInfo("ok")
{
//conn=mysql_init(NULL);.
	mysql_library_init(0,NULL,NULL);
    mysql_init(&conn);
}

bool MySqlConnector::connectMySQL(){
	cout<<"connecting mysql"<<endl;
	if(mysql_real_connect(&conn, server,user, password, NULL, 0, NULL, 0)){
		cout<<"connect mysql success!"<<endl;
		return true;
	};
	cout<<"connect mysql failed!"<<endl;
	return false;
}



//判断数据库是否存在，不存在则创建数据库，并打开
bool MySqlConnector::createDatabase(std::string& dbname)
{
    std::string queryStr = "create database if not exists ";
    queryStr += dbname;
    if (0 == mysql_query(&conn,queryStr.c_str()))
    {
    	cout<<"create database success"<<endl;
        queryStr = "use ";
        queryStr += dbname;
        if (0 == mysql_query(&conn,queryStr.c_str()))
        {
        	cout<<"use database success"<<endl;
            return true;
        }

    }
    cout<<"mysql error!"<<endl;
    errorIntoMySQL();
    return false;
}

bool MySqlConnector::createTable(const std::string& create_table){
	//CREATE TABLE simulation(id int(10),name varchar(10));
	std::string queryStr = "CREATE TABLE ";
	std::string queryinhalt = "(id int(10),name varchar(10))";
	queryStr += create_table;
	queryStr += queryinhalt;
	  if (0 == mysql_query(&conn,queryStr.c_str()))
	    {
		  cout<<"create table success"<<endl;
	        return true;
	    }
	  cout<<"create table failed"<<endl;
	    errorIntoMySQL();
	    return false;
}
void MySqlConnector::errorIntoMySQL()
{
    errorNum=mysql_errno(&conn);
    errorInfo=mysql_error(&conn);
}

