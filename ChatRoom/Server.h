#pragma once
#include "pch.h"
#include "ChatRoomDlg.h"
#include "framework.h"
#include "ChatRoom.h"

class CChatRoomDlg;

class CClientItem {
public:
	CString CIP;
	CString CID;
	CString CName;
	INT CPort;
	SOCKET Soket;
	HANDLE hThread;
	HANDLE hThread1;
	CChatRoomDlg* pMainWnd;
	CClientItem()
	{
		pMainWnd = NULL;
		Soket = INVALID_SOCKET;
		hThread = NULL;
	}
};
//class CChatRoomDlg;
DWORD WINAPI ListenThreadFunc(LPVOID pParam);
DWORD WINAPI ClientPro(LPVOID pParam);
//DWORD WINAPI ClientList(LPVOID pParam);

DWORD WINAPI ListThreadFunc(LPVOID pParam);
BOOL Socket_Select(SOCKET hSocket, int nTimeOut = 100, BOOL bRead = FALSE);
