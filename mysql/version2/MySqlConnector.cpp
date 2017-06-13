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
	std::string queryinhalt = "(Id int ( 4 ) primary key not  null  auto_increment,moduleType varchar(20),timestampId INT,flitId INT,  packetId INT,isTail varchar(10),pacektIdMinus1 INT,flowId INT)";
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


//写入数据
bool MySqlConnector::producerWriteToMysql(const std::string& tableName,const std::string moduleName,int timeStap,int packetIdMinus1,int flowId){
	stringstream queryInhalt;
		std::string queryStr = "insert into ";
		queryStr += tableName;
		queryInhalt<<" values(null,"<<"'"<<moduleName<<"'"<<","<<timeStap<<","<<"null"<<","<<"null"<<","<<"'"<<"null"<<"'"<<","<<packetIdMinus1<<","<<flowId<<")";
		queryStr+=queryInhalt.str();
		cout<<queryStr<<endl;
	    if(0==mysql_query(&conn,queryStr.c_str()))
	        return true;
	    else
	        errorIntoMySQL();
	    return false;
}

//写入数据
bool MySqlConnector::consumerWriteToMysql(const std::string& tableName,const std::string moduleName,int timeStap,int flitId,int packetId,const std::string isTail)
{
	stringstream queryInhalt;
		std::string queryStr = "insert into ";
		queryStr += tableName;
		queryInhalt<<" values(null,"<<"'"<<moduleName<<"'"<<","<<timeStap<<","<<flitId<<","<<packetId<<","<<"'"<<isTail<<"'"<<","<<"null"<<","<<"null"<<")";
		queryStr+=queryInhalt.str();
		cout<<queryStr<<endl;
	    if(0==mysql_query(&conn,queryStr.c_str()))
	        return true;
	    else
	        errorIntoMySQL();
	    return false;
}

void MySqlConnector::startTransaction(){
	mysql_query(&conn,"START TRANSACTION"); // 开启事务， 如果没有开启事务，那么效率会变得非常低下！
}
void MySqlConnector::commitTransaction(){
	mysql_query(&conn,"COMMIT"); // 开启事务， 如果没有开启事务，那么效率会变得非常低下！
	 ///mysql_free_result(res);
	 mysql_close(&conn);
	 mysql_library_end;
}


void MySqlConnector::errorIntoMySQL()
{
    errorNum=mysql_errno(&conn);
    errorInfo=mysql_error(&conn);
}

