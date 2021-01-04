
// MFCApplication1Dlg.h: 头文件
//

#pragma once
#include"Client.h"
#include"resource.h"
#include"afxwin.h"



// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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
	afx_msg void OnBnClickedShowmore();
	void Extend(BOOL Allshow);
	BOOL  flagshow;
	SOCKET SlistenSocket;
	void Init();
	HANDLE ConnectThread;
	SOCKET ConnectSocket;
	void ShowMsg(CString Msg);
	CEdit Msg_Edit;
	BOOL ShutDown;
	CArray <CClientItem, CClientItem>ClientArry;
	void CheckSend();
	int bls_Server;
	void StopClient();
	void RemoveClient(CClientItem citem);
	BOOL EnableWindows(UINT uID, BOOL able);
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedClose();
	afx_msg void OnEnChangeText();
	CListCtrl showlist;

	//////////////////////////////////////
	bool RecvAll(SOCKET& sock, char* buffer, int size);
	


	void showList(CString str, CString str1);

	CString CharArrayToCString(char CharArray[]);

	//static DWORD   WINAPI ListThreadFunc(LPVOID pParam);

	//static DWORD   WINAPI ListThreadFuncAll(LPVOID pParam);

};


