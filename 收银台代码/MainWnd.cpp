#include "Mainwindow.h"
#include "Cashier.h"
#include "Common.h"

CDuiString MainWnd::GetSkinFolder(){
	return _T("skin\\");
}
CDuiString MainWnd::GetSkinFile(){
	//return _T("Cashier.xml");
	return _T("MainWnd.xml");
}
LPCTSTR MainWnd::GetWindowClassName() const{
	return _T("DUIMainFrame");
}

void MainWnd:: Notify(TNotifyUI& msg) {
	//CDuiString strName = msg.pSender->GetName();
	if (msg.sType == _T("click")){
		if (msg.pSender->GetName() == _T("BTN_CLOSE"))					//关闭按键
			PostQuitMessage(0);
		else if (msg.pSender->GetName() == _T("BTN_MIN")){				//最小化
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (msg.pSender->GetName() == _T("Button_SELECT")) {		//查询
			Button_SELECT();
		}
		else if (msg.pSender->GetName() == _T("Button_INSERT")) {
			Button_INSERT();
		}
		else if (msg.pSender->GetName() == _T("Button_DROP")) {
			Button_Delete();
		}
		else if (msg.pSender->GetName() == _T("Button_UPDATE")) {
			Button_Update();
		}
		
	}
	else if (msg.sType == _T("selectchanged")) {
		//找这个控件,名字是TABLAYOUT
		//返回的指针是,是所有控件的基类CControlUI						   uncode格式
		CTabLayoutUI *pTab = (CTabLayoutUI*)m_PaintManager.FindControl(_T("TABLAYOUT"));
		if (msg.pSender->GetName() == _T("BTN_EMP")) {
			//m_hwnd			按键名字
			//MessageBox(m_hWnd, _T("EMP"), _T("MAINWND"), NULL);
			//加载不同的页面,设置选择项
			//员工的操作是0
			pTab->SelectItem(0);
		}
		else {
			//商品界面操作
			DestroyWindow(m_hWnd);
			Cashier cashier;
			cashier.Create(NULL, _T("Cashier"), UI_WNDSTYLE_EX_FRAME, WS_EX_WINDOWEDGE);
			cashier.CenterWindow();
			cashier.ShowModal();
		}
	}
	else if (msg.sType == _T("itemclick")) {

		//MessageBox(m_hWnd, _T("ADD"), _T("domain"), IDOK);
		//选中列表中的某一项,这个属性打印到上面的选项中去
		//Iltemselect();
		//CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Employee"));
		//int line = pList->GetCurSel();	//获取当前选中,返回的是行号
		//CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(line);			//选中的行号的数据
		//CDuiString* strName = (CDuiString*)m_PaintManager.FindControl(pItem->GetText(0));
		
	}
}
void MainWnd::Iltemselect() {

	
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Employee"));
	int line = pList->GetCurSel();	//获取当前选中,返回的是行号
	CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(line);			//选中的行号的数据
	CDuiString* strName = (CDuiString*)m_PaintManager.FindControl(pItem->GetText(0));

	m_PaintManager.FindControl(_T("username"))->SetText(pItem->GetText(1));				//姓名
	//m_PaintManager.FindControl(_T(""))->SetText(pItem->GetText(2));					//性别	
	m_PaintManager.FindControl(_T("birthday"))->SetText(pItem->GetText(3));				//生日
	//m_PaintManager.FindControl(_T(""))->SetText(pItem->GetText(4));					//置位
	m_PaintManager.FindControl(_T("phone_number"))->SetText(pItem->GetText(5));			//电话
	m_PaintManager.FindControl(_T("slary"))->SetText(pItem->GetText(6));				//薪水
}

//查询功能----实现的是选择的查询
void MainWnd::Button_SELECT() {
	
	string strSql("select *from employee");
	CDuiString combo_name = ((CComboBoxUI*)m_PaintManager.FindControl(_T("Combo_SELECT")))->GetText();
	//姓名的话就是全部查询
	//其他的话就是按照姓名和薪资分别查询
	// select *from employee where name='王八';

	if (combo_name == _T("整体查询"))
		strSql += ";";

	else if (combo_name == _T("姓名")) {
		CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();
		if (strName == _T("")) {
			MessageBox(m_hWnd,_T("请输入员工姓名"), _T("员工查询"), IDOK);
			return;
		}
		strSql += " where name='";
		strSql += UnicodeToANSI(strName);
		strSql += "';";
	}
	else if (combo_name == _T("性别")) {
		CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("Combo_sex")))->GetText();
		strSql += " where Gender='";
		strSql += UnicodeToANSI(strGender);
		strSql += "';";
	}
	else if (combo_name == _T("薪资")) {
		CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("slary")))->GetText();
		strSql += " where Salary='";
		strSql += UnicodeToANSI(strGender);
		strSql += "';";
	}

	vector<vector<string>> vret = p_mysql->SelectDB(strSql);
	if (vret.empty()) {
		MessageBox(m_hWnd, _T("无查询结果!"), _T("用户查询"), IDOK);
		CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Employee"));
		pList->RemoveAll();
		return;
	}
		

	//能走下来说明有数据,需要插入到页面里面
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Employee"));
	if (pList != NULL) {
		pList->RemoveAll();
	}
	for (size_t i = 0; i < vret.size(); ++i) {
		vector<string>& strItem = vret[i];
		CListTextElementUI* pData = new CListTextElementUI;
		pData->SetAttribute(_T("align"), _T("center"));

		pList->Add(pData);

		pData->SetText(0, ANSIToUnicode(strItem[0]));
		pData->SetText(1, ANSIToUnicode(strItem[1]));
		pData->SetText(2, ANSIToUnicode(strItem[2]));
		pData->SetText(3, ANSIToUnicode(strItem[3]));
		pData->SetText(4, ANSIToUnicode(strItem[5]));
		pData->SetText(5, ANSIToUnicode(strItem[6]));
		pData->SetText(6, ANSIToUnicode(strItem[7]));
	}
	//每次查询完毕就清楚掉数据
	vret.clear();
}

//
void MainWnd::Button_INSERT() 
{	
	CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();
	CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("Combo_sex")))->GetText();
	CDuiString strBirthday = ((CEditUI*)m_PaintManager.FindControl(_T("birthday")))->GetText();
	CDuiString strPosition = ((CComboBoxUI*)m_PaintManager.FindControl(_T("Combo_Position")))->GetText();
	CDuiString strNumber = ((CEditUI*)m_PaintManager.FindControl(_T("phone_number")))->GetText();
	CDuiString strSalary = ((CEditUI*)m_PaintManager.FindControl(_T("slary")))->GetText();
	
	if (strName.IsEmpty() || strGender.IsEmpty() || strBirthday.IsEmpty() ||
		strPosition.IsEmpty() || strNumber.IsEmpty() || strSalary.IsEmpty()) {
		MessageBox(m_hWnd, _T("请将要插入员工数据填入完整"), _T("增加员工"), IDOK);
		return;
	}

	//插入的时候查询一下,有多少行然后插入到最后一行
	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("List_Employee"));
	char szcount[32] = { 0 };
	//整形数据变字符串
	//		整形的数据			接收的数据  几进制的数据 
	_itoa(pListUI->GetCount() + 1, szcount, 10);
	string strSql("insert into employee values(");
	//员工的ID加入
	strSql += szcount;
	strSql += ",'";
	strSql += UnicodeToANSI(strName);
	strSql += "','";
	strSql += UnicodeToANSI(strGender);
	strSql += "','";
	strSql += UnicodeToANSI(strBirthday);
	strSql += "','0','";
	strSql += UnicodeToANSI(strPosition);
	strSql += "','";
	strSql += UnicodeToANSI(strNumber);
	strSql += "','";
	strSql += UnicodeToANSI(strSalary);
	strSql += "');";

	//插入数据库中
	p_mysql->Insert(strSql);

	//员工信息插入到List中,新创建一个列表进行修改操作
	CListTextElementUI* pItem = new CListTextElementUI;
	pListUI->Add(pItem);
	pItem->SetText(1, strName);
	pItem->SetText(2, strGender);
	pItem->SetText(3, strBirthday);
	pItem->SetText(4, strPosition);
	pItem->SetText(5, strNumber);
	pItem->SetText(6, strSalary);

	m_PaintManager.FindControl(_T("username"))->SetText(_T(""));
}

void MainWnd::Button_Delete() 
{
	//界面页面删除这一行
	//数据库中去删除
	//获取当前选中
	// delete from employee where name='王八'and id='6';
	
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Employee"));
	int line = pList->GetCurSel();	//获取当前选中,返回的是行号
	//获取到了某一行的这一行信息
	CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(line);
	if (pItem == NULL) {
		MessageBox(m_hWnd, _T("请选中要修改的人员"), _T("用户删除"), IDOK);
		return;
	}
	if (pItem->GetText(0) == NULL) {
		MessageBox(m_hWnd, _T("请选中要修改的人员"), _T("用户删除"), IDOK);
		return;
	}
	if (pItem->GetText(0) != NULL) {
		if (IDCANCEL == MessageBox(m_hWnd,_T("确认删除?"),_T("用户删除"),IDOK))
			return;
	}
	//从数据库中将该员工信息删除掉
	string mySql("delete from employee where name='");
	mySql += UnicodeToANSI(pItem->GetText(1));
	mySql += "'and id='";
	mySql += UnicodeToANSI(pItem->GetText(0));
	mySql += "';";
	p_mysql->Delete(mySql);

	//拿到某一行的名字
	//CDuiString strName = pItem->GetText(0);

	//删除了某一行
	pList->RemoveAt(line);
}
void MainWnd::Button_Update()
{
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("List_Employee"));
	int line = pList->GetCurSel();	//获取当前选中,返回的是行号
	CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(line);			//选中的行号的数据
	if (line == -1	&& pItem != NULL) {
		MessageBox(m_hWnd, _T("请选中要修改的人员"), _T("用户更新"), IDOK);
		return;
	}
	if (pItem->GetText(line) == NULL)  {
		MessageBox(m_hWnd, _T("请选中要修改的人员"), _T("用户更新"), IDOK);
		return;
	}
	//输入要修改的参数,再做出修改,先修改掉页面上的信息,再对数据库中的信息做出修改
	//在List中选中要修改的人,再将edit中变化的参数,传到List控件的参数中,做出修改
		//获取到了某一行的这一行信息

	CDuiString strId = pItem->GetText(0);
	CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();
	CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("Combo_sex")))->GetText();
	CDuiString strBirthday = ((CEditUI*)m_PaintManager.FindControl(_T("birthday")))->GetText();
	CDuiString strPosition = ((CComboBoxUI*)m_PaintManager.FindControl(_T("Combo_Position")))->GetText();
	CDuiString strNumber = ((CEditUI*)m_PaintManager.FindControl(_T("phone_number")))->GetText();
	CDuiString strSalary = ((CEditUI*)m_PaintManager.FindControl(_T("slary")))->GetText();

	if (strName.IsEmpty() || strGender.IsEmpty() || strBirthday.IsEmpty() ||
		strPosition.IsEmpty() || strNumber.IsEmpty() || strSalary.IsEmpty()) {
		MessageBox(m_hWnd, _T("请将要更新的数据填入完整"), _T("用户更新"), IDOK);
		return;
	}
	pItem->SetText(1, strName);
	pItem->SetText(2, strGender);
	pItem->SetText(3, strBirthday);
	pItem->SetText(4, strPosition);
	pItem->SetText(5, strNumber);
	pItem->SetText(6, strSalary);

	//UPDATE exam_result SET shuxue = 60, yuwen = 70 WHERE name = '曹孟德'; 
	//id   | name   | gender | birthday   | password | position     | telphone    | salary  |
	string mySql("update employee set name='");
	mySql += UnicodeToANSI(strName);
	mySql += "',gender='";
	mySql += UnicodeToANSI(strGender);
	mySql += "',birthday='";
	mySql += UnicodeToANSI(strBirthday);
	mySql += "',position='";
	mySql += UnicodeToANSI(strPosition);
	mySql += "',telphone='";
	mySql += UnicodeToANSI(strNumber);
	mySql += "',salary='";
	mySql += UnicodeToANSI(strSalary);
	mySql += "' where id='";
	mySql += UnicodeToANSI(strId);
	mySql += "';";
	p_mysql->Update(mySql);

	m_PaintManager.FindControl(_T("username"))->SetText(_T(""));
}
