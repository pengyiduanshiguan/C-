

#include "Cashier.h"
#include <vector>

CDuiString Cashier::GetSkinFolder()
{
	return _T("skin//");
}
CDuiString Cashier::GetSkinFile()
{
	return _T("Cashier.xml");
}
LPCTSTR Cashier::GetWindowClassName() const
{
	return _T("DUIMainFrame");
}

void Cashier:: Notify(TNotifyUI& msg)
{
	//psender 在哪一个控件上所做的单机,获取一下他的名字
	CDuiString strName = msg.pSender->GetName();
	//msg.pSender->GetText()			获取到的是文本
	//sType 消息的类型
	//自己所封装的string类,自己已经重载过了比较的方式

	if (msg.sType ==_T("click")) 
	{
		if (strName == _T("BTN_CLOSE")) 
		{
			PostQuitMessage(0);
		}
		else if (strName == _T("BTN_MIN"))
		{
			//win32 系统命令的消息
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (strName == _T("Button_ADD")) 
		{
			MessageBox(m_hWnd, _T("ADD"), _T("cashier"), IDOK);
		}
		else if (strName == _T("Button_SUB")) {
			MessageBox(m_hWnd, _T("ADD"), _T("cashier"), IDOK);
		}
		else if (strName == _T("Button_ENQUIRY")) {
			Button_SELECT();
		}
		else if (strName == _T("Button_CANCEL")) {
			MessageBox(m_hWnd, _T("ADD"), _T("cashier"), IDOK);
		}
		else if (strName == _T("Button_SELL")) {
			MessageBox(m_hWnd, _T("ADD"), _T("cashier"), IDOK);
		}
		else if (strName == _T("Button_ADDGOODS")) {
			Button_ADDGOODS();
		}
	}
}
void Cashier::Button_SELECT() 
{
	//1.获取商品名称	//强制的转换,基类转换成子类的方式
	CDuiString str_GoodsName = ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GoodsName")))->GetText();
	//select* from Goods where GoodsName='啤酒';
	//2.构造sql语句,到数据库中查询
	string strSql("select *from Goods where GoodsName='");
	strSql += UnicodeToANSI(str_GoodsName);
	strSql += "';";
	
	//将商品的信息显示到界面编辑框中
	vector<vector<string>> vret = p_mysql->SelectDB(strSql);
	if (vret.empty()) 
	{
		MessageBox(m_hWnd, _T("无查询结果!"), _T("用户查询"), IDOK);
		CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Goods"));
		pList->RemoveAll();
		return;
	}

	////3.将商品剩余的个数显示到界面编辑框中
	////创建一个列这个列现在指向的
	//CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Goods"));
	////循环输出每一列的数据


	//vector<string>& strItem = vret[0];
	//CListTextElementUI* pData = new CListTextElementUI;
	//pData->SetAttribute(_T("align"), _T("center"));

	//pList->Add(pData);
	// 0		1			2				3			4				5    6		7			8
	//ID	    姓名		类型		生产日期		过期日期	价格    单位	存库量		报警值
	// GoodsID | GoodsName | GoodsType | ProductDate | DeadDate   | Price | Unit | Inventory | AlarmValye
	//pData->SetText(0, ANSIToUnicode(strItem[0]));		//编号
	//pData->SetText(1, ANSIToUnicode(strItem[1]));		//名称
	//pData->SetText(2, ANSIToUnicode(strItem[5]));		//价格
	//pData->SetText(3, ANSIToUnicode(strItem[7]));		//数量
	//pData->SetText(4, ANSIToUnicode(strItem[6]));		//单位
	//pData->SetText(5, ANSIToUnicode(strItem[6]));		//总价
	m_PaintManager.FindControl(_T("EDIT_Inventory"))->SetText(ANSIToUnicode(vret[0][7]));

	//库存剩余更新到
}
void Cashier::Button_ADDGOODS() 
{
	//1.获取商品名称	//强制的转换,基类转换成子类的方式
	CDuiString str_GoodsName = ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GoodsName")))->GetText();
	//select* from Goods where GoodsName='啤酒';
	//2.构造sql语句
	string strSql("select *from Goods where GoodsName='");
	strSql += UnicodeToANSI(str_GoodsName);
	strSql += "';";

	//将商品的信息显示到界面编辑框中
	vector<vector<string>> vret = p_mysql->SelectDB(strSql);
	if (vret.empty()) 
	{
		MessageBox(m_hWnd, _T("无查询结果!"), _T("用户查询"), IDOK);
		CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Goods"));
		pList->RemoveAll();
		return;
	}

	//3.将商品剩余的个数显示到界面编辑框中
	//创建一个列这个列现在指向的
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Goods"));
	//如果列表中有数据就清除
	//循环输出每一列的数据

	for (size_t i = 0; i < vret.size(); ++i) 
	{
		vector<string>& strItem = vret[i];
		CListTextElementUI* pData = new CListTextElementUI;
		pData->SetAttribute(_T("align"), _T("center"));

		pList->Add(pData);
		// 0		1			2				3			4				5    6		7			8
		//ID	    姓名		类型		生产日期		过期日期	价格    单位	存库量		报警值
		// GoodsID | GoodsName | GoodsType | ProductDate | DeadDate   | Price | Unit | Inventory | AlarmValye
		pData->SetText(0, ANSIToUnicode(strItem[0]));		//编号
		pData->SetText(1, ANSIToUnicode(strItem[1]));		//名称
		pData->SetText(2, ANSIToUnicode(strItem[5]));		//价格
		pData->SetText(3, ANSIToUnicode(strItem[7]));		//数量
		pData->SetText(4, ANSIToUnicode(strItem[6]));		//单位
		//pData->SetText(5, ANSIToUnicode(strItem[6]));		//总价
		m_PaintManager.FindControl(_T("EDIT_Inventory"))->SetText(ANSIToUnicode(strItem[7]));
	}
	//库存剩余更新到;
}