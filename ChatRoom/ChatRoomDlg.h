
// ChatRoomDlg.h: 头文件
//

#pragma once
#include"Server.h"

// CChatRoomDlg 对话框
class CChatRoomDlg : public CDialogEx
{
// 构造
public:
	CChatRoomDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATROOM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CListCtrl User_List;
	HANDLE ListenThread;
	BOOL DlgAllInit();
	CArray <CClientItem, CClientItem>ClientArry;
	SOCKET SlistenSocket;
	BOOL ShutDown;
	void RemoveClient(CClientItem citem);
	afx_msg void OnBnClickedStartserver();
	/*CListCtrl ServerInfr;*/
	void StopServer();
	afx_msg void OnBnClickedCloseserver();
	CListCtrl ServerIF;
	void SendClientMsg(CString strMsg, CClientItem* pNotSend = NULL);
	void SendClientList(CString strMsg, CString strMsg1,CClientItem* pNotSend=NULL);
	void CheckSend();
	bool SendAll(SOCKET& sock, char* buffer, int size);
	bool Sendnew(SOCKET& sock, char* buffer, int size);
	void SendClient(char* buffer, CClientItem* pNotSend=NULL);
	void showList(CString str, CString str1);


};
