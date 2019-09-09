#pragma once

#include<Winsock2.h>
#include<mysql.h>
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
/*
	初始化,连接,增删改查,
	在连接的时候我们已经连接到了这个库也就是说是可以使用了

*/
class Mysql{
public:
	Mysql();
	bool Connection(const char*host,
					const char* user,
					const char*passwd,
					const char*db_name,
					unsigned int port);				//连接函数
	bool Add(const string& cmd);					//增加
	bool Delete(const string& cmd);					//删除
	bool Update(const string& cmd);					//修改
	bool Enquiry(const string& str);				//查询某一个表中的数据,并打印出来
	bool Insert(const string& cmd);
	vector<vector<string>> SelectDB(const string& db_name);			//选择表将表中的数据赋值给_table
	~Mysql();

private:
	MYSQL *_mysql;				//mysql 实体连接所返回的一个对象
	string _dbname;
	vector<string> _tables;		//一个表,表中的信息被存储在这个二维字符串中
};


