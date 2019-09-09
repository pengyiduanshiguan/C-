#include"login.h"
#include "Mainwindow.h"
#include "Common.h"
#include "Cashier.h"

CDuiString LoginWnd::GetSkinFolder(){
	return _T("skin\\");
}
CDuiString LoginWnd::GetSkinFile(){
	return _T("login.xml");
}
LPCTSTR LoginWnd::GetWindowClassName() const{
	return _T("LogInWnd");
}

void LoginWnd::Notify(TNotifyUI& msg){

		
	if (msg.sType == _T("click")){
		if (msg.pSender->GetName() == _T("Button_CLOSE")){					//关闭按键
			PostQuitMessage(0);												//结束进程
		}																
		else if (msg.pSender->GetName() == _T("Button_MIN")){				//最小化
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
			}
		else if (msg.pSender->GetName() == _T("Button_LOGIN")){
			Login();														//登录
		}
	}
}
void LoginWnd::Login()
{
	CEditUI* pEdituserName = (CEditUI*)m_PaintManager.FindControl(_T("Edit_Uer"));
	CDuiString strUserName = pEdituserName->GetText();

	CEditUI* pEdituserPassword = (CEditUI*)m_PaintManager.FindControl(_T("Edit_MI"));
	CDuiString strUserPassword = pEdituserPassword->GetText();


	if (strUserName.IsEmpty()){
		MessageBox(m_hWnd, _T("请输入用户名"), _T("Cashier"), IDOK);
		return;
	}
	if (strUserPassword.IsEmpty()){
		MessageBox(m_hWnd, _T("请输入密码"), _T("Cashier"), IDOK);
		return;
	}

	//查询数据库,检测用户是否存在
	string strSQL("select *from Employee where name='");
	strSQL += UnicodeToANSI(strUserName);
	strSQL += "';";

	vector <vector<string >> vRet = p_mysql->SelectDB(strSQL);

	if (vRet.empty()) {
		MessageBox(m_hWnd, _T("用户名错误"), _T("Cashier"), IDOK);
		return;
	}
	string userpassword = UnicodeToANSI(strUserPassword);
	if (userpassword != vRet[0][4]) {
		MessageBox(m_hWnd, _T("用户名密码错误"), _T("Cashier"), IDOK);
		return;
	}
	if (vRet[0][5] == "售货员") {					//售货员界面
		DestroyWindow(m_hWnd);//进入之后就关闭界面
		Cashier cashier;
		cashier.p_mysql = p_mysql;
		cashier.Create(NULL, _T("Cashier"), UI_WNDSTYLE_EX_FRAME, WS_EX_WINDOWEDGE);
		cashier.CenterWindow();
		cashier.ShowModal();
		
	}
	else{											//管理员界面
		DestroyWindow(m_hWnd);
		MainWnd mainwnd;
		mainwnd.p_mysql = p_mysql;
		mainwnd.Create(NULL, _T("MainWnd"), UI_WNDSTYLE_EX_FRAME, WS_EX_WINDOWEDGE);
		mainwnd.CenterWindow();
		mainwnd.ShowModal();
	}
}




