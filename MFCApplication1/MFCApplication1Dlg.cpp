
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include"Client.h"
#define MAX_BUF_SIZE 1024
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	flagshow = 0;
	bls_Server = -1;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Show_Text, Msg_Edit);
	DDX_Control(pDX, list, showlist);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ShowMore, &CMFCApplication1Dlg::OnBnClickedShowmore)
	ON_BN_CLICKED(Send, &CMFCApplication1Dlg::OnBnClickedSend)
	ON_BN_CLICKED(Close, &CMFCApplication1Dlg::OnBnClickedClose)
	ON_EN_CHANGE(Send_Text, &CMFCApplication1Dlg::OnEnChangeText)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Extend(FALSE);
	Init();
	EnableWindows(Send, FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////
void CMFCApplication1Dlg::Extend(BOOL Allshow)
{
	static CRect Dlg_Large(0, 0, 0, 0);
	static CRect Dlg_Small(0, 0, 0, 0);

	if (Dlg_Large.IsRectNull())
	{
		GetWindowRect(&Dlg_Large);
		Dlg_Small = Dlg_Large;
		Dlg_Small.right -= 235;
	}

	if (Allshow)
	{
		flagshow = 1;
		SetWindowPos(NULL, Dlg_Large.left, Dlg_Large.top, Dlg_Large.Width(), Dlg_Large.Height(), SWP_NOZORDER | SWP_NOMOVE);
	}
	else
	{
		flagshow = 0;
		SetWindowPos(NULL, Dlg_Large.left, Dlg_Large.top, Dlg_Small.Width(), Dlg_Small.Height(), SWP_NOZORDER | SWP_NOMOVE);
	}
}


void  CMFCApplication1Dlg::Init()
{
	ConnectThread = CreateThread(NULL, 0, ConnectThreadFunc, this, 0, NULL);
	ResumeThread(ConnectThread);
	


	DWORD dwstyle = showlist.GetExtendedStyle();

	dwstyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;

	showlist.SetExtendedStyle(dwstyle);
	showlist.InsertColumn(0, _T("用户名"), LVCFMT_CENTER, 110);
	showlist.InsertColumn(1, _T("用户ID"), LVCFMT_LEFT, 100);
}


void CMFCApplication1Dlg::ShowMsg(CString Msg)
{
	Msg_Edit.SetSel(-1, -1);  //光标定位在最后一个位置

	Msg_Edit.ReplaceSel(Msg); //光标替换成传进来的字符串
	Msg_Edit.ReplaceSel(_T("\r\n")); //光标替换成传进来的字符串

}


void CMFCApplication1Dlg::CheckSend()
{
	CString strmsg;
	GetDlgItemText(Send_Text, strmsg);
	/*if (bls_Server == TRUE)
	{
		strmsg = _T("服务器：>") + strmsg;
		ShowMsg(strmsg);
		SendClientMsg(strmsg);
	}*/
	//else if (bls_Server == FALSE)
	if(bls_Server == FALSE)
	{
		/*CString strTmp = _T("客户端：>") + strmsg;
		ShowMsg(strTmp);*/
		int isend = send(ConnectSocket, (char*)strmsg.GetBuffer(), strmsg.GetLength() * sizeof(TCHAR), 0);
		strmsg.ReleaseBuffer();
	}
	else {
		AfxMessageBox(_T("请先进入聊天室"));
	}
	SetDlgItemText(Send_Text, _T(""));

}

void  CMFCApplication1Dlg::RemoveClient(CClientItem citem)
{
	for (int index = 0; index < ClientArry.GetCount(); index++)
	{
		CClientItem item = ClientArry.GetAt(index);
		if (item.Soket == citem.Soket && item.hThread == citem.hThread && item.CIP == citem.CIP && item.CPort == citem.CPort)
		{
			ClientArry.RemoveAt(index);
		}
	}
}


void CMFCApplication1Dlg::StopClient()
{
	ShutDown = TRUE;
	DWORD dwRet = WaitForSingleObject(ConnectThread, 1000);
	if (dwRet != WAIT_OBJECT_0)
	{
		TerminateThread(ConnectThread, -1);
		closesocket(ConnectSocket);
	}
	ConnectThread = NULL;
	ConnectSocket = INVALID_SOCKET;
	bls_Server = -1;
	ShutDown = FALSE;
}



BOOL CMFCApplication1Dlg::EnableWindows(UINT uID, BOOL able)
{
	return GetDlgItem(uID)->EnableWindow(able);
}


/////////////////////////////////
void CMFCApplication1Dlg::OnBnClickedShowmore()
{
	// TODO: 在此添加控件通知处理程序代码
	if (flagshow)
	{
		Extend(FALSE);

	}
	else
	{
		Extend(TRUE);
	}
}


void CMFCApplication1Dlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CheckSend();
}



void CMFCApplication1Dlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	StopClient();
	ShowMsg(_T("停止客户端成功"));
}




void CMFCApplication1Dlg::OnEnChangeText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	CString str;
	GetDlgItemText(Send_Text, str);
	if (str.IsEmpty())
	{
		EnableWindows(Send, FALSE);
	}
	else
	{
		EnableWindows(Send, TRUE);
	}

}



void CMFCApplication1Dlg::showList(CString str, CString str1)
{
	int static flag = 1;

	int count = showlist.GetItemCount();
	for (int index = 0; index < count; index++)
	{
		if (str == showlist.GetItemText(index, 0) && str1 == showlist.GetItemText(index, 1))
			flag = 0;
			break;
		
	}
	if (flag == 1)
	{
		int static rowId = 0;
		showlist.InsertItem(showlist.GetItemCount(), _T("xxx"));
		showlist.SetItemText(rowId, 0, str);
		showlist.SetItemText(rowId, 1, str1);
		rowId++;
	}
	
}






bool CMFCApplication1Dlg::RecvAll(SOCKET& sock, char* buffer, int size)
{
	
	while (size > 0)//剩余部分大于0
	{
		CString strMsg;
		int RecvSize = recv(sock, buffer, 1024, 0);
		strMsg.Format(_T("%s"), buffer);
		if (SOCKET_ERROR == RecvSize)
			return false;
		size = size - RecvSize;
		buffer += RecvSize;
	
	}

	return true;
}


//bool CMFCApplication1Dlg::RecvNew(SOCKET& sock, char* buffer, int size)
//{
//	while (size > 0)//剩余部分大于0
//	{
//		CString strMsg;
//		int RecvSize = recv(sock, buffer, 1024, 0);
//		strMsg.Format(_T("%s"), buffer);
//		showList(strMsg, _T("xxx"));
//		if (SOCKET_ERROR == RecvSize)
//			return false;
//		size = size - RecvSize;
//		buffer += RecvSize;
//
//	}
//	return true;
//}





//Char[]转CString返回CString
CString CMFCApplication1Dlg::CharArrayToCString(char CharArray[])
{
	CString str;
	int Char_len = strlen(CharArray);
	int len = MultiByteToWideChar(CP_ACP, 0, CharArray, Char_len, NULL, 0);//计算字符数
	TCHAR* buf = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, CharArray, Char_len, buf, len);
	buf[len] = '\0';
	str.Append(buf);
	delete[]buf;
	return str;
}