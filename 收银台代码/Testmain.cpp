
#include "Common.h"
#include "login.h"
#include "MYSQL.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	//打开数据库

	Mysql mysql;
	mysql.Connection("127.0.0.1", "root", "1", "Cashier", 3306);

	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	LoginWnd duiFrame;
	duiFrame.p_mysql = &mysql;
	duiFrame.Create(NULL, _T("DUIMainFrame"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();		//模态对话框
	return 0;
}