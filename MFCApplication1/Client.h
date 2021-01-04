#pragma once
#include "pch.h"
#include "MFCApplication1.h"
#include "framework.h"
#include "MFCApplication1Dlg.h"

//class MFCApplication1Dlg;
class CMFCApplication1Dlg;



class CClientItem {
public:
	CString CIP;
	CString CName;
	CString CID;
	INT CPort;
	SOCKET Soket;
	HANDLE hThread;
	HANDLE hThread1;
	CMFCApplication1Dlg* pMainWnd;
	CClientItem()
	{
		pMainWnd = NULL;
		Soket = INVALID_SOCKET;
		hThread = NULL;
		CIP = "172.20.10.5";
		CID="001";
		CName = "zzz";

	}
};


DWORD WINAPI ConnectThreadFunc(LPVOID pParam);
static DWORD   WINAPI ListThreadFunc(CMFCApplication1Dlg* pChatRoom);

static DWORD   WINAPI ListThreadFuncAll(CMFCApplication1Dlg* pChatRoom);


BOOL Socket_Select(SOCKET hSocket, int nTimeOut = 100, BOOL bRead = FALSE);