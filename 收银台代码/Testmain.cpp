
#include "Common.h"
#include "login.h"
#include "MYSQL.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	//�����ݿ�

	Mysql mysql;
	mysql.Connection("127.0.0.1", "root", "1", "Cashier", 3306);

	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	LoginWnd duiFrame;
	duiFrame.p_mysql = &mysql;
	duiFrame.Create(NULL, _T("DUIMainFrame"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();		//ģ̬�Ի���
	return 0;
}