
// MFCApplicationSDlg.h: 標頭檔
//

#pragma once
// CMFCApplicationSDlg 對話方塊
class CClientItem;
class CMFCApplicationSDlg : public CDialogEx
{
// 建構
public:
	CMFCApplicationSDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//sending mssage to client
	afx_msg void OnBnClickedButton3();//clear chat box
	afx_msg void OnBnClickedButton1();//start to accept socket
	afx_msg void OnBnClickedButton4();//delete selected client socket
	afx_msg void OnEnChangeEdit1();//enter port number, limit port number 1024~49152, only digital
	afx_msg void OnBnClickedCancel();//stop connect and close
	afx_msg void OnEnChangeEdit2();//limit message size
	afx_msg void OnClose();//右上角的叉叉
	afx_msg void OnDestroy();
	CEdit PortNum;
	CEdit EnterMessenge;
	CListBox ChatBox;
	CButton BtnConnect;
	CButton BtnStopConnect;
	CListCtrl LinkMember;

	//server socket
	bool m_isServerOpen;
	BOOL StartServer(void);
	SOCKET SockListen;

	CArray<CClientItem> m_ClientArray;//連線後會建立 個client物件，裡面包著client的資訊
	void SendClientMsg(CString strMsg, CClientItem* pWhoseItem);//傳訊息給Client
	void RemoveClientFromArray(CClientItem in_item);
	BOOL equal(const CClientItem* p1, const CClientItem* p2);//for sending chaeck, make sure for sending client socket

	//thread parameter and function
	HANDLE ThreadListen;//thread information of socket thread
	static DWORD WINAPI ListenThreadFunc(LPVOID Lparam);//wgile loop socket accept
	static BOOL socket_Select(SOCKET hSocket, DWORD nTimeOut, BOOL bRead);
	static DWORD WINAPI ClientThreadProc(LPVOID Lparam);//while loop recieve client socket
	CCriticalSection csRemoveArray;
	afx_msg void OnBnClickedButton2();

	void setIniFilePathToBuffer(wchar_t* Buffer, const wchar_t* IniName);
	CString getIP();

	char IP[20];
};

class CClientItem
{
public:
	CString m_strIp;//client socket ip
	SOCKET m_ClientSocket;//client socket
	HANDLE m_hThread;//client socket thread id
	CMFCApplicationSDlg* m_pMainWnd;//內部變數，連接外部傳進來的main object，方便在thread內對外做操作
	CClientItem() {
		m_ClientSocket = INVALID_SOCKET;
		m_hThread = NULL;
		m_pMainWnd = NULL;
	}
};
