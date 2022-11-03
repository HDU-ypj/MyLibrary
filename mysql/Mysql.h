#ifndef MYSQL_H
#define MYSQL_H

#include <mysql/mysql.h>
#include <string>
using namespace std;

class Mysql
{
public:
	//初始化mysql结构体
	Mysql();
	//删除释放mysql资源
	~Mysql();
	//连接mysql服务器
	bool connect(string ip,string user,string pass,string db,unsigned int port=3306);
	//更新信息
	bool update(string cmd);
	//查询信息
	bool query(string cmd);
	//遍历下一行信息
	bool next(void);
	//获取一行中第N个数据的值
	string value(int index);
	//设置不可自动提交
	bool setAutoCommit(bool flag);
	//提交事物
	bool commit(void);
	//回滚
	bool rollback(void);
	//列数目
	int field_count(void);
	
	
private:
	//释放存储的二维数组内存
	void free_result(void);
	MYSQL* m_sql;		//mysql句柄
	MYSQL_RES* m_res;	//存放result
	MYSQL_ROW m_row;	//存放一行的数据
};
#endif//MYSQL_H
