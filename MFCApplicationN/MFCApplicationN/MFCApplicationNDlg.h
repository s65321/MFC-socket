
// MFCApplicationNDlg.h: 標頭檔
//

#pragma once


// CMFCApplicationNDlg 對話方塊
class CMFCApplicationNDlg : public CDialogEx
{
// 建構
public:
	CMFCApplicationNDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONN_DIALOG };
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
	afx_msg void OnBnClickedCancel();//clear chat box
	afx_msg void OnBnClickedCancel2();//connect 
	afx_msg void OnBnClickedOk();//send message
	afx_msg void OnBnClickedCancel3();//close all
	afx_msg void OnEnChangeEdit2();//輸入暱稱
	afx_msg void OnEnChangeEdit1();//port number must be digital
	afx_msg void OnBnClickedCancel4();//設定暱稱與port
	afx_msg void OnEnChangeEdit3();//limit message size
	afx_msg void OnClose();//右上角的叉叉
	CListBox ChatBox;
	CEdit EnterMessenge;
	CEdit PortNum;
	CEdit NickName;
	CButton bSetNickName;
	CButton BtnConnect;
	CButton BtnStopConnect;
	CButton BtnSend;

	//connect功能開發用properties
	static DWORD WINAPI ConnectNetworkThread(LPVOID lpParameter); // 呼叫connect函數
	BOOL ConnectSocket(CMFCApplicationNDlg* pClient); //連線，while loop rcv
	BOOL socket_Select(SOCKET hSocket, DWORD nTimeOut, BOOL bRead);//polling socket
	SOCKET m_ClientSock;//client socket locate in object
	BOOL isServerOn;//State of connection, for next stage development
};
