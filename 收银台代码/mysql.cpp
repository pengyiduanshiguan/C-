#include "MYSQL.h"


//初始化连接并且返回一个句柄,接收这个句柄

Mysql::Mysql(){
	_mysql = mysql_init(nullptr);
	if (_mysql == NULL)
		cout << "mysql_init()faile" << endl;
	else
		cout << "mysql_init()success" << endl;
}
Mysql::~Mysql(){
	mysql_close(_mysql);
}
//使用mysql_real_connect()建立一个到mysql数据库的连接
bool Mysql::Connection(const char* host,const char*user,const char*passwd,
					   const char*db_name,unsigned int port = 3306 )
{
	if (!mysql_real_connect(_mysql, host, user, passwd, db_name, port, NULL, 0))
	{
		cout << "connect mysql error" << endl;
		return false;
	}
	cout << "connect success" << endl;
	//将mysql字符编码设置为  gbk
	mysql_query(_mysql,"set names 'gbk'");
	return true;
}

//查询函数
bool Mysql::Enquiry(const string& str)
{
	if (str.empty())
	{
		cout << "enquiry str is empty" << endl;
		return false;
	}
	//select *form tables(xxxx);
	int ret = mysql_query(_mysql, str.c_str());
	//看起来查询结果成功的返回值是一个 0 ???
	if ( !ret )
	{
		//MYSQL_RES = mysql_store_result(); 将查询的结果拿到, 获取记录集
		MYSQL_RES* result = mysql_store_result(_mysql);
		if (result == NULL)
		{
			mysql_error(_mysql);
			return false;
		}
		//能走下来说明获取到了数据
		//int item = mysql_num_field(MYSQL_RES) 返回记录一行中有多少个字段,也就是有多少个元素属性 (参数是记录集)
		int item = mysql_num_fields(result);
		cout << "Table item is " << item << endl;

		//将item拿到之后再去查询有多少个行,也就是有多少个元素
		//mysql_fetch_row(MYSQL_RES)检索结果集的下一行 拿到满足条件的每一行 最后返回空
		//MYSQL_ROW 是一个二级指针的类型

		/*
			MYSQL_FIFELD 是一个结构体里面有各种的数据
		*/
		cout << endl;
		MYSQL_ROW row = NULL;
		while (row = mysql_fetch_row(result))
		{
			for (int i = 0; i < item; ++i)
			{
				cout << row[i]<<" ";
			}
			cout << endl;
		}
		cout << "Enquiry success" << endl;
	}
	return true;
}

bool Mysql::Add(const string& cmd)
{
	if (cmd.empty())
	{
		cout << "Your input is incorrect " << endl;
		return false;
	}
	if (mysql_query(_mysql, cmd.c_str())){
		cout << "input data success" << endl;
		return true;
	}
	return false;
}
bool Mysql::Delete(const string& cmd)
{
	if (cmd.empty())
	{
		cout << "Your input is incorrect " << endl;
		return false;
	}
	if (mysql_query(_mysql, cmd.c_str()))
	{
		cout << "delete data success" << endl;
		return true;
	}
	return false;
}
bool Mysql::Insert(const string& cmd) {
	// 执行sql语句    
	if (mysql_query(_mysql,cmd.c_str())) { 
		return false;    
	}

	return true;
}

bool Mysql::Update(const string& cmd){
	if (cmd.empty()){
		cout << "Your input is incorrect " << endl;
		return false;
	}
	if (mysql_query(_mysql, cmd.c_str())){
		cout << "Update data success" << endl;
		return true;
	}
	return false;
}


vector<vector<string>> Mysql::SelectDB(const string& db_name){
	vector<vector<string>> vret;

	if (mysql_query(_mysql, db_name.c_str())){
		vret[0][0] = (mysql_error(_mysql));
		cout << "Your input is incorrect" << endl;
		return vret;
	}
	MYSQL_RES* res = mysql_store_result(_mysql);
	if (res == NULL){
		return vret;
	}
	//获取item
	int item = mysql_num_fields(res);
	MYSQL_ROW row = NULL;
	while (row = mysql_fetch_row(res)){
		vector<string> temp;
		temp.resize(item);
		for (int i = 0; i < item; ++i){
			temp[i] = row[i];
		}
		//将数据尾插到二维数组中
		vret.push_back(temp);
	}

	const char*str = mysql_error(_mysql);
	mysql_free_result(res);
	return vret;
	
}
