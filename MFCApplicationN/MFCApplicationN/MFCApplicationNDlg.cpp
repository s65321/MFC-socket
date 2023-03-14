
// MFCApplicationNDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationN.h"
#include "MFCApplicationNDlg.h"
#include "afxdialogex.h"
#include <afxwin.h>

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


// CMFCApplicationNDlg 對話方塊



CMFCApplicationNDlg::CMFCApplicationNDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ClientSock = NULL;
	isServerOn = FALSE;
}

void CMFCApplicationNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, EnterMessenge);
	DDX_Control(pDX, IDC_LIST1, ChatBox);
	DDX_Control(pDX, IDC_EDIT1, PortNum);
	DDX_Control(pDX, IDC_EDIT2, NickName);
	DDX_Control(pDX, IDCANCEL4, bSetNickName);
	DDX_Control(pDX, IDCANCEL2, BtnConnect);
	DDX_Control(pDX, IDCANCEL3, BtnStopConnect);
	DDX_Control(pDX, IDOK, BtnSend);
}

BEGIN_MESSAGE_MAP(CMFCApplicationNDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMFCApplicationNDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDCANCEL2, &CMFCApplicationNDlg::OnBnClickedCancel2)
	ON_BN_CLICKED(IDOK, &CMFCApplicationNDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL3, &CMFCApplicationNDlg::OnBnClickedCancel3)
	ON_BN_CLICKED(IDCANCEL4, &CMFCApplicationNDlg::OnBnClickedCancel4)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplicationNDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplicationNDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplicationNDlg::OnEnChangeEdit3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMFCApplicationNDlg 訊息處理常式

BOOL CMFCApplicationNDlg::OnInitDialog()
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
	CString b = getIP();
	strcpy_s(IP, CT2A(b));
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplicationNDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplicationNDlg::OnPaint()
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
HCURSOR CMFCApplicationNDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//clear
void CMFCApplicationNDlg::OnBnClickedCancel()
{
	while (ChatBox.GetCount()) {
		ChatBox.DeleteString(0);
	}
}

// build connect
void CMFCApplicationNDlg::OnBnClickedCancel2()
{
	CreateThread(0, 0, ConnectNetworkThread, this, 0, NULL);
	EnterMessenge.EnableWindow(true);
	BtnSend.EnableWindow(true);
	BtnStopConnect.EnableWindow(true);
}
DWORD WINAPI CMFCApplicationNDlg::ConnectNetworkThread(LPVOID lpParameter) {
	CMFCApplicationNDlg *pClient = (CMFCApplicationNDlg*)lpParameter;
	if (pClient->ConnectSocket(pClient))
	{
	}
	else {
		AfxMessageBox(L"執行連線時發生錯誤");
	}
	return 0;
}
BOOL CMFCApplicationNDlg::ConnectSocket(CMFCApplicationNDlg* pClient) {
	CString strIp;
	pClient->PortNum.GetWindowTextW(strIp);
	int dPort = _ttoi(strIp);
	if (dPort > 49151 && dPort < 1024)
	{
		AfxMessageBox(_T("Port number only can be set from 1024 to 49151"));
		return FALSE;
	}
	
	m_ClientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (NULL == m_ClientSock)
	{
		AfxMessageBox(_T("client socket建立失敗"));
		return FALSE;
	}
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(dPort);
	//這邊開始連線
	sa.sin_addr.s_addr = inet_addr(IP);
	/*char szIpAdd[32];
	USES_CONVERSION; 
	sprintf_s(szIpAdd, 32, "%s", T2A(strIp));
	sa.sin_addr.S_un.S_addr = inet_addr(szIpAdd);*/
	if (SOCKET_ERROR == connect(m_ClientSock, (sockaddr*)&sa, sizeof(sa)))
	{
		AfxMessageBox(_T("Client 連線失敗"));
		return FALSE;
	}

	//連線成功
	CString nickname, csenterContext;
	char szBuf[256] = { 0 };
	NickName.GetWindowTextW(nickname);
	USES_CONVERSION;
	int iW;
	//把Csting 變成char包進szBuf內
	strcpy_s(szBuf, T2A(nickname + _T("已加入聊天室")));
	iW = send(m_ClientSock, szBuf, 256, 0);
	if (SOCKET_ERROR == iW) {
		AfxMessageBox(L"訊息未成功發送");
		return 0;
	}
	pClient->ChatBox.AddString(nickname + _T("已加入聊天室"));
	pClient->BtnStopConnect.EnableWindow(TRUE);
	pClient->BtnConnect.EnableWindow(FALSE);

	isServerOn = TRUE;

	CString strMsg;
	while (TRUE)
	{
		if (socket_Select(m_ClientSock, 100, TRUE))
		{
			char szMsg[256] = { 0 };
			int iRead = recv(m_ClientSock, szMsg, 256, 0);
			if (iRead > 0)
			{
				strMsg = szMsg;
				pClient->ChatBox.AddString(strMsg);
				pClient->ChatBox.SetTopIndex(ChatBox.GetCount() - 1);
			}
			else
			{
				pClient->ChatBox.AddString(_T("Server已中斷此處連線"));
				pClient->ChatBox.SetTopIndex(ChatBox.GetCount() - 1);
				isServerOn = FALSE;
				return TRUE;
			}
		}
	}
	return TRUE;
}

BOOL CMFCApplicationNDlg::socket_Select(SOCKET hSocket, DWORD nTimeOut, BOOL bRead)
{
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
	if (iRet <= 0)//0 continue -1 error
	{
		return FALSE;
	}
	else if (FD_ISSET(hSocket, &fdset)) // 1 && socket fd可讀 == socket上有數據
	{
		return TRUE;
	}
	return FALSE;
#endif
	return true;
}
//send
void CMFCApplicationNDlg::OnBnClickedOk()
{
	CString name;
	NickName.GetWindowTextW(name);

	CString csenterContext;
	char szBuf[256] = { 0 };
	USES_CONVERSION;
	int iW;
	EnterMessenge.GetWindowTextW(csenterContext);
	if (csenterContext == L"") {
		AfxMessageBox(L"訊息發送不得為空");
		EnterMessenge.SetWindowTextW(L"");
	}
	else {
		strcpy_s(szBuf, T2A(name + L": " + csenterContext));
		iW = send(m_ClientSock, szBuf, 256, 0);
		if (SOCKET_ERROR == iW) {
			AfxMessageBox(L"訊息未成功發送");
			return;
		}
		else {
			ChatBox.InsertString(ChatBox.GetCount(), name + L": " + csenterContext);
			EnterMessenge.SetWindowTextW(L"");
			EnterMessenge.SetFocus();
		}
	}
	//置底
	ChatBox.SetTopIndex(ChatBox.GetCount() - 1);
}

//斷線 == close
void CMFCApplicationNDlg::OnBnClickedCancel3()
{
	BtnConnect.EnableWindow(TRUE);
	BtnSend.EnableWindow(FALSE);
	BtnStopConnect.EnableWindow(FALSE);
	closesocket(m_ClientSock);
	isServerOn = FALSE;
	CDialogEx::OnOK();
}

//Set the nick name
void CMFCApplicationNDlg::OnBnClickedCancel4()
{
	CString n;
	NickName.GetWindowTextW(n);
	if (n != L"") {
		NickName.EnableWindow(false);
		bSetNickName.EnableWindow(false);
		PortNum.EnableWindow(true);
	}
	else {
		AfxMessageBox(L"暱稱不得為空!");
	}
}

//輸入暱稱，字數上限18個
void CMFCApplicationNDlg::OnEnChangeEdit2()
{
	NickName.SetLimitText(18);
}

//限制輸入port num 為數字且最多五個字
void CMFCApplicationNDlg::OnEnChangeEdit1()
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
}

// type in message 上限100字
void CMFCApplicationNDlg::OnEnChangeEdit3()
{
	EnterMessenge.SetLimitText(100);
}


void CMFCApplicationNDlg::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialogEx::OnOK();
}
void CMFCApplicationNDlg::setIniFilePathToBuffer(wchar_t* Buffer, const wchar_t* IniName) {
	wchar_t strFilePath[MAX_PATH];
	//get the path og exe. Because config,ini is locate  there
	GetModuleFileName(NULL, strFilePath, MAX_PATH);
	PathRemoveFileSpec(strFilePath);
	wcscat_s(strFilePath, L"\\");
	wcscat_s(strFilePath, IniName);
	memcpy(Buffer, strFilePath, MAX_PATH);
}
CString CMFCApplicationNDlg::getIP() {
	wchar_t strFilePath[MAX_PATH];
	setIniFilePathToBuffer(strFilePath, L"Config.ini");
	CString strContentReturn;
	GetPrivateProfileString(L"IP", L"IPv4", L"172.20.10.3", strContentReturn.GetBuffer(256), 256, strFilePath);
	return strContentReturn;
}