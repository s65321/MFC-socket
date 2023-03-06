
// MFCApplicationSDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationS.h"
#include "MFCApplicationSDlg.h"
#include "afxdialogex.h"
#include "afxsock.h"
#include "afxwin.h"
#include "afxmt.h"
#include <atlconv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCApplicationSDlg 對話方塊

CMFCApplicationSDlg::CMFCApplicationSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ThreadListen = NULL;
	SockListen = NULL;
	m_isServerOpen = false;
	m_ClientArray.RemoveAll();
}

void CMFCApplicationSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, EnterMessenge);
	DDX_Control(pDX, IDC_LIST2, ChatBox);
	DDX_Control(pDX, IDC_EDIT1, PortNum);
	DDX_Control(pDX, IDC_BUTTON1, BtnConnect);
	DDX_Control(pDX, IDCANCEL, BtnStopConnect);
	DDX_Control(pDX, IDC_LIST3, LinkMember);
}

BEGIN_MESSAGE_MAP(CMFCApplicationSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplicationSDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplicationSDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplicationSDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplicationSDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplicationSDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplicationSDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplicationSDlg::OnEnChangeEdit2)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplicationSDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplicationSDlg 訊息處理常式
//Initial, Set check box and column
BOOL CMFCApplicationSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	//設置checkbox和多選
	DWORD dwExStyle = LinkMember.GetExtendedStyle();
	LinkMember.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT);
	//設置這行column header才會出來
	LinkMember.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	LinkMember.InsertColumn(0, _T(""), LVCFMT_LEFT, 100);//姓名
	LinkMember.InsertColumn(1, L"IP", LVCFMT_LEFT, 125);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplicationSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCApplicationSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCApplicationSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Send Server messenge
void CMFCApplicationSDlg::OnBnClickedOk()
{
	CString csenterContext,temp;
	EnterMessenge.GetWindowTextW(temp);

	if (temp != L"") {
		csenterContext.Format(L"Server: " + temp);
		SendClientMsg(csenterContext, NULL);
		ChatBox.AddString(csenterContext);
		EnterMessenge.SetWindowTextW(L"");
	}
	else {
		AfxMessageBox(L"發送訊息不得為空");
		EnterMessenge.SetWindowTextW(L"");
	}
	ChatBox.SetTopIndex(ChatBox.GetCount() - 1);
	EnterMessenge.SetFocus();
}

//Clear the messenge box
void CMFCApplicationSDlg::OnBnClickedButton3()
{
	while (ChatBox.GetCount()) {
		ChatBox.DeleteString(0);
	}
}

//Start Socket Accept in another thread
void CMFCApplicationSDlg::OnBnClickedButton1()
{
	//set port num
	CString strPort;
	PortNum.GetWindowTextW(strPort);
	int numPort = _ttoi(strPort);
	if (numPort < 1024 || numPort > 49151)
	{
		AfxMessageBox(_T("Port number only can be choose from 1024 to 49151"));
		PortNum.SetWindowTextW(L"");
		return;
	}
	ChatBox.AddString(L"Server: Set server port is: " + strPort);
	BtnConnect.EnableWindow(false);
	StartServer();
	m_isServerOpen = true;
	BtnStopConnect.EnableWindow(true);
}
BOOL CMFCApplicationSDlg::StartServer() {
	ThreadListen = CreateThread(NULL, 0, ListenThreadFunc, this, 0, 0);
	if (ThreadListen == NULL)
	{
		AfxMessageBox(L"ListenThreadFunc doesn't start!!");
		return FALSE;
	}
	else {
		return TRUE;
	}
	return true;
};

//刪除 
void CMFCApplicationSDlg::OnBnClickedButton4()
{
	int rowSelect = 0;
	for (int rowCount = LinkMember.GetItemCount(); rowCount > 0; rowCount--) {
		if (LinkMember.GetCheck(rowSelect)) {
#if 1
			csRemoveArray.Lock();
			RemoveClientFromArray(m_ClientArray.GetAt(rowSelect));
			csRemoveArray.Unlock();
#endif
#if 0//critical section
			RemoveClientFromArray(m_ClientArray.GetAt(rowSelect));
#endif	
		}
		else {
			rowSelect++;
		}
	}
}


//Server stop all connection
void CMFCApplicationSDlg::OnBnClickedCancel()
{
	int AllClient = m_ClientArray.GetCount();
	for (int idx = 0 ; idx < AllClient ; idx++)
	{
		closesocket(m_ClientArray.GetAt(idx).m_ClientSocket);
	}
	m_ClientArray.RemoveAll();
	//Server inform client disconnect
	SendClientMsg(L"Sever: 中斷所有連線", NULL);

	closesocket(SockListen);

	ChatBox.AddString(_T("Server: 已中斷連線"));
	m_isServerOpen = FALSE;
	BtnConnect.EnableWindow(FALSE);
	BtnStopConnect.EnableWindow(FALSE);
	CDialogEx::OnOK();
}

//while loop accept socket
DWORD WINAPI CMFCApplicationSDlg::ListenThreadFunc(LPVOID pParam) {
	CMFCApplicationSDlg* pDlg = (CMFCApplicationSDlg*)pParam;
	if (INVALID_SOCKET == (pDlg->SockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		AfxMessageBox(_T("socket isn't exit"));
		return 0;
	}
	pDlg->ChatBox.AddString(L"Server: Build the socket");

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("172.20.10.2");
	CString csPortNum;
	pDlg->PortNum.GetWindowTextW(csPortNum);
	service.sin_port = htons(_ttoi(csPortNum));

	if (0 != bind(pDlg->SockListen, (sockaddr*)&service, sizeof(sockaddr_in)))
	{
		AfxMessageBox(_T("binding fail"));
		return 0;
	}
	pDlg->ChatBox.AddString(L"Server: bind the socket");

	if (0 != listen(pDlg->SockListen, 5))
	{
		AfxMessageBox(_T("listening fail"));
		return 0;
	}
	pDlg->ChatBox.AddString(L"Server: listen up to 5 devices");
	pDlg->ChatBox.AddString(L"Server: Start connect other Client...");

	while (TRUE) {
		if (socket_Select(pDlg->SockListen, 100, TRUE))
		{
			sockaddr_in clientAddr;
			int iLen = sizeof(sockaddr_in);
			SOCKET accSock = accept(pDlg->SockListen, (struct sockaddr*)&clientAddr, &iLen);
			if (accSock == INVALID_SOCKET)
			{
				continue;
			}
			pDlg->ChatBox.AddString(L"Accept new Client!!");
			//收到client後，建立Client物件
			CClientItem tItem;
			tItem.m_ClientSocket = accSock;
			tItem.m_strIp = inet_ntoa(clientAddr.sin_addr); //Client IP
			tItem.m_pMainWnd = pDlg;
			int idx = pDlg->m_ClientArray.Add(tItem); //client array 是server紀錄client資訊的地方

			//插入listctrl
			pDlg->LinkMember.InsertItem(pDlg->LinkMember.GetItemCount(), L"");
			pDlg->LinkMember.SetItemText(pDlg->LinkMember.GetItemCount() - 1,1, tItem.m_strIp);

			tItem.m_hThread = CreateThread(NULL, 0, ClientThreadProc, //創建thread給Client使用
				&(pDlg->m_ClientArray.GetAt(idx)), CREATE_SUSPENDED, NULL);//保持thread suspend
			pDlg->m_ClientArray.GetAt(idx).m_hThread = tItem.m_hThread;//把創建完的thread id傳入client item
			//恢復clientThread的執行，理論上這邊要先判斷thread有沒有建成
			ResumeThread(tItem.m_hThread);
			pDlg->ChatBox.AddString(_T("Server: IP ") + tItem.m_strIp + _T(", 已連線"));
			Sleep(100);
		}
	}
	return 0;
}

 

 //物件內定義的函數
 //limit port number only can be typed in number
 void CMFCApplicationSDlg::OnEnChangeEdit1()
 {
	 CString str;
	 PortNum.SetLimitText(5);
	 PortNum.GetWindowTextW(str);
	 int PortNumFlag = 0;
	 int StringLen = str.GetLength();
	 switch (StringLen) {
	 case 0:
		 PortNumFlag = 0;
		 break;
	 case 1:
		 PortNumFlag = iswdigit(str[0]);
		 break;
	 case 2:
		 PortNumFlag = iswdigit(str[0]) & iswdigit(str[1]);
		 break;
	 case 3:
		 PortNumFlag = iswdigit(str[0]) & iswdigit(str[1]) & iswdigit(str[2]);
		 break;
	 case 4:
		 PortNumFlag = iswdigit(str[0]) & iswdigit(str[1]) & iswdigit(str[2]) & iswdigit(str[3]);
		 break;
	 case 5:
		 PortNumFlag = iswdigit(str[0]) & iswdigit(str[1]) & iswdigit(str[2]) & iswdigit(str[3]) & iswdigit(str[4]);
		 break;
	 default:
		 PortNumFlag = 0;
	 }
	 if ((str != L"\0") && (PortNumFlag != 0))
	 {
		 BtnConnect.EnableWindow(true);
	 }
	 else {
		 BtnConnect.EnableWindow(false);
	 }
	 m_isServerOpen = true;
	
 }


 //向socket中看一眼，如果有資訊則返回TRUE，如果沒有資訊則返回FALSE。 有資訊代表有客戶端來連接了
 BOOL CMFCApplicationSDlg::socket_Select(SOCKET hSocket, DWORD nTimeOut, BOOL bRead) {
#if 0
	 FD_SET fdset;
	 timeval tv;
	 FD_ZERO(&fdset);
	 FD_SET(hSocket, &fdset);
	 nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	 tv.tv_sec = 0;
	 tv.tv_usec = nTimeOut;
	 int iRet = 0;
	 if (bRead)
	 {
		 iRet = select(0, &fdset, NULL, NULL, &tv);
	 }
	 else
	 {
		 iRet = select(0, NULL, &fdset, NULL, &tv);
	 }
	 if (iRet <= 0)
	 {
		 return FALSE;
	 }
	 else if (FD_ISSET(hSocket, &fdset))
	 {
		 return TRUE;
	 }
	 return FALSE;
#endif
	 return true;
 };

 DWORD WINAPI CMFCApplicationSDlg::ClientThreadProc(LPVOID Lparam) {
	 USES_CONVERSION;
	 CString strMsg;
	 CClientItem ClientItem = *(CClientItem*)Lparam;
	 while (TRUE)
	 {
		 if (socket_Select(ClientItem.m_ClientSocket, 100, TRUE))
		 {
			 //接收資料，一次接收最多256byte
			 char szRev[256] = { 0 };
			 int iRet = recv(ClientItem.m_ClientSocket, szRev, sizeof(szRev), 0);//保持接收資料狀態
			 if (iRet > 0)
			 {
				 strMsg = A2T(szRev); //取得傳輸過來的字串並轉換成Cstring
 				//strMsg.Format(_T("%s"),szRev); //也可以這樣做轉型

				//將接收訊息顯示在chatbox上
				ClientItem.m_pMainWnd->ChatBox.AddString(strMsg);
				ClientItem.m_pMainWnd->ChatBox.SetTopIndex(ClientItem.m_pMainWnd->ChatBox.GetCount() - 1);
				//將訊息回傳讓訊息可顯示在client端的chatbox上
				ClientItem.m_pMainWnd->SendClientMsg(strMsg, &ClientItem);
			 }
			 else {//接收到斷線資訊 or 0 (會在client端把它弄掉)
				 strMsg = ClientItem.m_strIp + _T(" 已斷線");
#if 1//solution for critical condition
				 ClientItem.m_pMainWnd->csRemoveArray.Lock();
				 ClientItem.m_pMainWnd->RemoveClientFromArray(ClientItem);
				 ClientItem.m_pMainWnd->csRemoveArray.Unlock();
#endif
#if 0//solution for critical condition
				 Sleep(1000);
				 ClientItem.m_pMainWnd->RemoveClientFromArray(ClientItem);
#endif 
				 ClientItem.m_pMainWnd->ChatBox.AddString(strMsg);
				 ClientItem.m_pMainWnd->ChatBox.SetTopIndex(ClientItem.m_pMainWnd->ChatBox.GetCount() -1);
				 break;//這條thread就會跑完
			 }
		 }
	 }
	 return 0;
 }

 void CMFCApplicationSDlg::SendClientMsg(CString strMsg, CClientItem* pWhoseItem) {
	 USES_CONVERSION;
	 char szBuf[256] = { 0 };
	 strcpy_s(szBuf, 256, T2A(strMsg));
	 //發給每個client
	 for (int i = 0; i < m_ClientArray.GetCount(); i++)
	 {
		 if (!pWhoseItem || !equal(pWhoseItem, &(m_ClientArray.GetAt(i))))
		 {
			 send(m_ClientArray.GetAt(i).m_ClientSocket, szBuf, 256, 0);
		 }
	 }
 }

 //斷開Client
 void CMFCApplicationSDlg::RemoveClientFromArray(CClientItem in_item) {
	 for (int idx = 0; idx < m_ClientArray.GetCount(); idx++)
	 {
		 if ((in_item.m_ClientSocket == m_ClientArray[idx].m_ClientSocket) &&
			 (in_item.m_hThread == m_ClientArray[idx].m_hThread) &&
			 (in_item.m_strIp == m_ClientArray[idx].m_strIp) &&
			 (in_item.m_pMainWnd == m_ClientArray[idx].m_pMainWnd))
		 {
			 LinkMember.DeleteItem(idx);
			 ChatBox.AddString(L"已將" + m_ClientArray.GetAt(idx).m_strIp + L"移除");
			 closesocket(m_ClientArray.GetAt(idx).m_ClientSocket);
			 m_ClientArray.RemoveAt(idx);
		 }
	 }
	 return;
 }
 //for sending chaeck, make sure for sending client socket
 BOOL CMFCApplicationSDlg::equal(const CClientItem* p1, const CClientItem* p2)
 {
	 if (p1->m_ClientSocket == p2->m_ClientSocket && p1->m_hThread == p2->m_hThread && p1->m_strIp == p2->m_strIp)
	 {
		 return TRUE;
	 }
	 else
	 {
		 return FALSE;
	 }
 }

 void CMFCApplicationSDlg::OnEnChangeEdit2()
 {
	 EnterMessenge.SetLimitText(100);
 }





 void CMFCApplicationSDlg::OnClose()
 {
	 // TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	 CDialogEx::OnOK();

 }


 void CMFCApplicationSDlg::OnDestroy()
 {
	 CDialogEx::OnDestroy();

	 // TODO: 在此加入您的訊息處理常式程式碼
 }


 void CMFCApplicationSDlg::OnBnClickedButton2()
 {
	 CString a = L"123";
	 CString b = L"123";
	 CString c = L"666";
	 CString d = L"999";
	 if (a.Compare(b)==0) {
		 ChatBox.AddString(a);
	 }
	 else {
		 ChatBox.AddString(b);
	 }
 }
