

#pragma once


#include "Common.h"

class Cashier : public WindowImplBase{

public:
	Mysql* p_mysql;
	void Button_SELECT();						//获取商品名称到数据库中查询
	void Button_ADDGOODS();						//添加商品到售货列表中
	virtual void Notify(TNotifyUI& msg);

protected:
	virtual CDuiString GetSkinFolder();			//xml文件对应的目录
	virtual CDuiString GetSkinFile();           //xml文件的名字 
	virtual LPCTSTR GetWindowClassName(void) const; //窗口类的名字

};
