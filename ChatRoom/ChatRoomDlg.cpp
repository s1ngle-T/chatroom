
// ChatRoomDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ChatRoom.h"
#include "ChatRoomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_BUF_SIZE 1024
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


// CChatRoomDlg 对话框



CChatRoomDlg::CChatRoomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATROOM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, UserList, User_List);
	/*DDX_Control(pDX, Server_Infr, ServerInfr);*/
	DDX_Control(pDX, Server_Infr, ServerIF);
}

BEGIN_MESSAGE_MAP(CChatRoomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(UserList, &CChatRoomDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(StartServer, &CChatRoomDlg::OnBnClickedStartserver)
	ON_BN_CLICKED(CloseServer, &CChatRoomDlg::OnBnClickedCloseserver)
END_MESSAGE_MAP()


// CChatRoomDlg 消息处理程序

BOOL CChatRoomDlg::OnInitDialog()
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

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	DlgAllInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatRoomDlg::OnPaint()
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
HCURSOR CChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatRoomDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
/////////////////////////////////////
BOOL  CChatRoomDlg::DlgAllInit()
{
	SetDlgItemText(Port_Text, _T("5000"));
	//扩展风格，网格线
	DWORD dwstyle = User_List.GetExtendedStyle();
	DWORD dwstyle1 = ServerIF.GetExtendedStyle();
	dwstyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
	dwstyle1 |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
	User_List.SetExtendedStyle(dwstyle);
	ServerIF.SetExtendedStyle(dwstyle1);

	/*UserList.*/

	User_List.InsertColumn(0, _T("用户名"), LVCFMT_CENTER, 80);
	User_List.InsertColumn(1, _T("用户ID"), LVCFMT_LEFT, 100);
	User_List.InsertColumn(2, _T("IP地址"), LVCFMT_CENTER, 120);

	ServerIF.InsertColumn(0, _T("服务器信息"), LVCFMT_CENTER,350);

	ShutDown = FALSE;
	//添加
	//int rowId = UserList.GetItemCount();
	//UserList.InsertItem(UserList.GetItemCount(), _T("xxx"));
	//UserList.SetItemText(rowId, 0, _T("aaa"));
	//UserList.SetItemText(rowId, 1, _T("bbb"));
	//UserList.SetItemText(rowId, 2, _T("ccc"));
	//rowId++;
	///*int rowId = UserList.GetItemCount();*/
	//UserList.InsertItem(UserList.GetItemCount(), _T("xxx"));
	//UserList.SetItemText(rowId, 0, _T("aaa"));
	//UserList.SetItemText(rowId, 1, _T("bbb"));
	//UserList.SetItemText(rowId, 2, _T("ccc"));


	//获取某行文本
	//int count = UserList.GetItemCount();
	//for (int index = 0; index < count; index++)
	//{
	//	BOOL bcheck = UserList.GetCheck(index);
	//	if (bcheck)
	//	{
	//		CString strText;
	//		UserList.GetItemText(index, 0);
	//		UserList.GetItemText(index, 1);
	//		UserList.GetItemText(index, 2);
	//		strText= UserList.GetItemText(index, 2);



	//	}
	//}

	return true;
}


void  CChatRoomDlg::RemoveClient(CClientItem citem)
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

void CChatRoomDlg::StopServer()
{
	UINT Count = ClientArry.GetCount();
	HANDLE* phandle = new HANDLE[Count];
	phandle[0] = ListenThread;
	for (int index = 0; index < Count; index++)
	{
		phandle[index + 1] = ClientArry.GetAt(index).hThread;

	}
	ShutDown = true;
	DWORD dwRet = WaitForMultipleObjects(Count + 1, phandle, TRUE, 1000);
	if (dwRet != WAIT_OBJECT_0)
	{
		for (INT_PTR i = 0; i < ClientArry.GetCount(); i++)
		{
			TerminateThread(ClientArry.GetAt(i).hThread, -1);
			closesocket(ClientArry.GetAt(i).Soket);
		}
		delete[]phandle;
		ListenThread = NULL;
		SlistenSocket = INVALID_SOCKET;
		//bls_Server = -1;
		ShutDown = FALSE;
	}

}

////////////////////////////////////

void CChatRoomDlg::OnBnClickedStartserver()
{
	// TODO: 在此添加控件通知处理程序代码
	/*ListenThreadFunc();*/
	ListenThread = CreateThread(NULL, 0, ListenThreadFunc, this, 0, NULL);


}


void CChatRoomDlg::OnBnClickedCloseserver()
{
	// TODO: 在此添加控件通知处理程序代码
	StopServer();
	//ShowMsg(_T("停止服务端成功"));
}


void  CChatRoomDlg::SendClientMsg(CString strMsg, CClientItem* pNotSend)
{
	TCHAR szBuf[MAX_BUF_SIZE] = { 0 };
	_tcscpy_s(szBuf, MAX_BUF_SIZE, strMsg);

	for (int index = 0; index < ClientArry.GetCount(); index++)
	{
		if (!pNotSend || pNotSend->Soket != ClientArry.GetAt(index).Soket || pNotSend->hThread != ClientArry.GetAt(index).hThread || pNotSend->CIP != ClientArry.GetAt(index).CIP || pNotSend->CPort != ClientArry.GetAt(index).CPort)
		{
			send(ClientArry.GetAt(index).Soket, (char*)szBuf, 1024, 0);
		}
	}
}


void  CChatRoomDlg::SendClient(char* buffer, CClientItem* pNotSend)
{
	//CHAR szBuf[MAX_BUF_SIZE] = { 0 };
	for (int index = 0; index < ClientArry.GetCount(); index++)
	{
		if (!pNotSend || pNotSend->Soket != ClientArry.GetAt(index).Soket || pNotSend->hThread != ClientArry.GetAt(index).hThread || pNotSend->CIP != ClientArry.GetAt(index).CIP || pNotSend->CPort != ClientArry.GetAt(index).CPort)
		{
			int SendSize = send(ClientArry.GetAt(index).Soket, buffer, 1024, 0);

		}
	}
}


void  CChatRoomDlg::SendClientList(CString strMsg, CString strMsg1, CClientItem* pNotSend)
{

	TCHAR szBuf[MAX_BUF_SIZE] = { 0 };
	_tcscpy_s(szBuf, MAX_BUF_SIZE, strMsg);
	//sprintf_s(szBuf, "%S", strMsg);


	TCHAR szBuf1[MAX_BUF_SIZE] = { 0 };
	_tcscpy_s(szBuf1, MAX_BUF_SIZE, strMsg1);
	/*sprintf_s(szBuf1, "%S", strMsg1);*/


	for (int index = 0; index < ClientArry.GetCount(); index++)
	{
		/*if (!pNotSend || pNotSend->Soket != ClientArry.GetAt(index).Soket || pNotSend->hThread != ClientArry.GetAt(index).hThread || pNotSend->CIP != ClientArry.GetAt(index).CIP || pNotSend->CPort != ClientArry.GetAt(index).CPort)
		{*/
			send(ClientArry.GetAt(index).Soket, (char*)szBuf, 1024, 0);
		
			send(ClientArry.GetAt(index).Soket, (char*)szBuf1, 1024, 0);
		//}
	}
	return;
}



bool CChatRoomDlg::SendAll(SOCKET& sock, char* buffer, int size)
{
	/*for (int index = 0; index < ClientArry.GetCount(); index++)
	{*/
		while (size > 0)
		{
			int SendSize = send(sock, buffer, 1024, 0);
			if (SOCKET_ERROR == SendSize)
				return false;
			size = size - SendSize;//用于循环发送且退出功能
			buffer += SendSize;//用于计算已发buffer的偏移量
		}
	//}
	return true;
}


bool CChatRoomDlg::Sendnew(SOCKET& sock, char* buffer, int size)
{
	for (int index = 0; index < ClientArry.GetCount(); index++)
	{
	while (size > 0)
	{
		int SendSize = send(ClientArry.GetAt(index).Soket, buffer, 1024, 0);
		if (SOCKET_ERROR == SendSize)
			return false;
		size = size - SendSize;//用于循环发送且退出功能
		buffer += SendSize;//用于计算已发buffer的偏移量
	}
	}
	return true;
}



void CChatRoomDlg::showList(CString str, CString str1)
{
	int count =User_List.GetItemCount();
	for (int index = 0; index < count; index++)
	{
		if (str == User_List.GetItemText(index, 0) && str1 == User_List.GetItemText(index, 1))
		{
			
			User_List.DeleteItem(index);
			UpdateWindow();
			break;
		}
		

	}


}



