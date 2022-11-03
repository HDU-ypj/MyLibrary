/**************************************************
>	作	  者：杭电羊皮卷
>	邮	  箱：2997675141@qq.com
>   文件名称: Mysql.cpp
>   创建日期：2022年10月26日
>   描    述：
**************************************************/

#include "Mysql.h"

	
//初始化mysql结构体
Mysql::Mysql()
{
	m_sql = mysql_init(m_sql);
	mysql_set_character_set(m_sql,"utf8");
	mysql_autocommit(m_sql,false);
}

//删除释放mysql资源
Mysql::~Mysql()
{
	free_result();
	if(NULL != m_sql)
	{
		mysql_close(m_sql);
	}
}

//连接mysql服务器
bool Mysql::connect(string ip,string user,string pass,string db,unsigned int port)
{
	MYSQL *ptr = mysql_real_connect(m_sql,ip.c_str(),user.c_str(),pass.c_str(),db.c_str(),port,NULL,0);
	return ptr!=nullptr;
}

//更新信息
bool Mysql::update(string cmd)
{
	return 0 == mysql_real_query(m_sql,cmd.c_str(),cmd.size());
}

//查询信息
bool Mysql::query(string cmd)
{
	free_result();
	if(mysql_real_query(m_sql,cmd.c_str(),cmd.size()))
	{
		return false;
	}
	m_res = mysql_store_result(m_sql);
	return true;
}

//遍历下一行信息
bool Mysql::next(void)
{
	if(nullptr != m_res)
	{
		m_row = mysql_fetch_row(m_res);
	}
	return m_row!=nullptr;
}

//获取一行中第N个数据的值
string Mysql::value(int index)
{
	int rowcnt = mysql_field_count(m_sql);
	if(index<0 || index>=rowcnt)
	{
		return string();
	}
	char* val = m_row[index];
	unsigned long length = mysql_fetch_lengths(m_res)[index];
	return string(val,length);
}

//设置不可自动提交
bool Mysql::setAutoCommit(bool flag)
{
	return mysql_autocommit(m_sql,flag);
}

//提交事物
bool Mysql::commit(void)
{
	return mysql_commit(m_sql);
}

//回滚
bool Mysql::rollback(void)
{
	return mysql_rollback(m_sql);
}

//字段数
int Mysql::field_count(void)
{
	return mysql_field_count(m_sql);
}

//释放存储数据
void Mysql::free_result(void)
{
	if(nullptr != m_res)
	{
		mysql_free_result(m_res);
		m_res = nullptr;
	}
}

