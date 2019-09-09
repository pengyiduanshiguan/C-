#pragma  once

#include "Common.h"

class LoginWnd : public WindowImplBase{

public:
	Mysql *p_mysql;
	virtual void Notify(TNotifyUI& msg);
	void Login();						//注册按键按下之后响应的事件

protected:
	virtual CDuiString GetSkinFolder();			//xml文件对应的目录
	virtual CDuiString GetSkinFile();           //xml文件的名字 
	virtual LPCTSTR GetWindowClassName(void) const; //窗口类的名字

};
