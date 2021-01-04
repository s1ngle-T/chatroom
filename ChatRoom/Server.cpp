//#include "stdafx.h"
#include "pch.h"
#include "ChatRoomDlg.h"
#include "framework.h"
#include "ChatRoom.h"
#include<WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")
#include <vector>

using namespace std;
#define MAX_BUF_SIZE 1024
int static rowId = 0;
int  num = 0;
int static flag = 0;
int static t;
vector<pair<CString, CString>>vec_user;
//LPVOID pParam;

CStringArray str;

//typedef struct pra {
//	CString strMsg;
//	CString strMsg1;
//	CClientItem* pNotSend;
//}param;
//param p;


//DWORD WINAPI ClientList( LPVOID pParam)
//{
//	PClientItem.pMainWnd->SendClientList(PClientItem.CName, PClientItem.CID);
//
//
//	return true;
//}

DWORD WINAPI ClientPro(LPVOID pParam)
{
	int i = 0;
	CString strMsg;
	CClientItem PClientItem = *(CClientItem*)pParam;


	char recvBuffer[256] = { 0 };
	char recvBuffer1[256] = { 0 };
	int re = recv(PClientItem.Soket, recvBuffer, sizeof(recvBuffer), 0);
	strMsg.Format(_T("%S"), recvBuffer);
	PClientItem.CName = recvBuffer;
	int re1 = recv(PClientItem.Soket, recvBuffer1, sizeof(recvBuffer1), 0);
	strMsg.Format(_T("%S"), recvBuffer1);
	PClientItem.CID = recvBuffer1;
	vec_user.push_back(make_pair(PClientItem.CName, PClientItem.CID));

	

	strMsg = _T("客户端：") + PClientItem.CName + _T("加入了聊天室");
	PClientItem.pMainWnd->SendClientMsg(strMsg + _T("\n"));
	/*sprintf_s(user[num], "%s", PClientItem.CName.GetBuffer(PClientItem.CName.GetLength()));
	sprintf_s(user[num+1], "%s", PClientItem.CName.GetBuffer(PClientItem.CName.GetLength()));*/
	num++;
	//PClientItem.pMainWnd->SendClientList(PClientItem.CName, PClientItem.CID);


	flag = 0;
	char s[10];
	sprintf_s(s, "%d", num);
	send(PClientItem.Soket, (char*)&s, sizeof(s), 0);


	for (auto i = vec_user.begin(); i != vec_user.end(); i++)
	{
		char  usr[MAX_BUF_SIZE];
		char  usr1[MAX_BUF_SIZE];/*
		(*i).first.GetBuffer((*i).first.GetLength());*/
		//sprintf_s(usr, "%s", (*i).first.GetBuffer(2*(*i).first.GetLength()));
		sprintf_s(usr, "%S", i->first.GetBuffer(i->first.GetLength()));
		sprintf_s(usr1, "%S", i->second.GetBuffer(i->second.GetLength()));
		PClientItem.pMainWnd->SendAll(PClientItem.Soket, usr, 1024);
		PClientItem.pMainWnd->SendAll(PClientItem.Soket, usr1, 1024);

	}

	PClientItem.pMainWnd->User_List.InsertItem(PClientItem.pMainWnd->User_List.GetItemCount(), _T("xxx"));
	PClientItem.pMainWnd->User_List.SetItemText(rowId, 0, PClientItem.CName);
	PClientItem.pMainWnd->User_List.SetItemText(rowId, 1, PClientItem.CID);
	PClientItem.pMainWnd->User_List.SetItemText(rowId, 2, PClientItem.CIP);
	PClientItem.pMainWnd->ServerIF.InsertItem(rowId, strMsg);
	rowId++;
	t++;


	while ( !(PClientItem.pMainWnd->ShutDown))
	{

		if (Socket_Select(PClientItem.Soket, 100, TRUE))
		{
			TCHAR szBuf[MAX_BUF_SIZE] = { 0 };
			int iRet = recv(PClientItem.Soket, (char*)szBuf, MAX_BUF_SIZE, 0);
			if (iRet > 0)
			{
				strMsg.Format(_T("%s"), szBuf);
				strMsg = _T("客户端：") + PClientItem.CName + _T(">") + strMsg;

				PClientItem.pMainWnd->SendClientMsg(strMsg);
				
				//PClientItem.pMainWnd->ShowMsg(strMsg);
			}
			else
			{
				strMsg = _T("客户端：") + PClientItem.CName + _T("离开了聊天室");
				//PClientItem.pMainWnd->ShowMsg(strMsg);
				PClientItem.pMainWnd->SendClientMsg(strMsg);
				PClientItem.pMainWnd->RemoveClient(PClientItem);
				PClientItem.pMainWnd->ServerIF.InsertItem(rowId, strMsg);
				rowId++;
				PClientItem.pMainWnd->showList(PClientItem.CName, PClientItem.CID);



				break;

			}
		}
		Sleep(500);
	}
	rowId++;
	flag = 1;
	return true;
}

BOOL Socket_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	tv.tv_sec = 0;
	tv.tv_usec = nTimeOut;

	int iRec = 0;
	if (bRead)
	{
		iRec = select(0, &fdset, NULL, NULL, &tv);
	}
	else
		iRec = select(0, NULL, &fdset, NULL, &tv);

	if (iRec <= 0)
	{
		return false;
	}
	else if (FD_ISSET(hSocket, &fdset))
	{
		return true;
	}
	return false;
}


DWORD WINAPI ListenThreadFunc(LPVOID pParam)
{
	CChatRoomDlg* pChatRoom = (CChatRoomDlg*)pParam;
	ASSERT(pChatRoom != NULL);

	pChatRoom->SlistenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (pChatRoom->SlistenSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("新建socket失败"));
		return FALSE;
	}
	//绑定
	int uPort = pChatRoom->GetDlgItemInt(Port_Text);
	if (uPort < 1 || uPort>65535)
	{
		AfxMessageBox(_T("请输入正确的端口号：1-65535"));
		goto _Error_End;

	}
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = INADDR_ANY;
	service.sin_port = htons(uPort);
	if (bind(pChatRoom->SlistenSocket, (sockaddr*)&service, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("绑定失败"));
		goto _Error_End;
	}
	else
		AfxMessageBox(_T("服务器链接中"));
	if (listen(pChatRoom->SlistenSocket, 10) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("监听失败"));
		goto _Error_End;
	}
	//pChatRoom->bls_Server = TRUE;
	while (TRUE && !(pChatRoom->ShutDown))
	{
		if (Socket_Select(pChatRoom->SlistenSocket, 100, TRUE))
		{
			sockaddr_in clientAddr;
			int len = sizeof(sockaddr_in);
			SOCKET accSock = accept(pChatRoom->SlistenSocket, (struct sockaddr*) & clientAddr, &len);
			/*if (accSock == SOCKET_ERROR)
			{
				AfxMessageBox(_T("接受失败"));
				goto _Error_End;
			}*/
			if (accSock == INVALID_SOCKET)
			{
				continue;
			}
			CClientItem CItem;
			CItem.Soket = accSock;

			char sendBuf[20] = { '\0' };
			CItem.CIP = inet_ntop(AF_INET, (void*)&clientAddr.sin_addr, sendBuf, 16);

			//CItem.CIP = inet_ntoa(clientAddr.sin_addr);
			CItem.CPort = (clientAddr.sin_port);
			CItem.pMainWnd = pChatRoom;
			INT_PTR index = pChatRoom->ClientArry.Add(CItem);



			CItem.hThread = CreateThread(NULL, 0, ClientPro, &(pChatRoom->ClientArry.GetAt(index)), CREATE_SUSPENDED, NULL);
			pChatRoom->ClientArry.GetAt(index).hThread = CItem.hThread;
			ResumeThread(CItem.hThread);

			/*CItem.hThread1 = CreateThread(NULL, 0, ClientProList, &(pChatRoom->ClientArry.GetAt(index)), CREATE_SUSPENDED, NULL);
			pChatRoom->ClientArry.GetAt(index).hThread1 = CItem.hThread1;
			ResumeThread(CItem.hThread1);*/


			/*Sleep(100);*/
			/*if (accSock != INVALID_SOCKET)
			{
				AfxMessageBox(_T("连接成功"));
				return TRUE;
			}*/
			Sleep(100);

		}

	}



_Error_End:
	closesocket(pChatRoom->SlistenSocket);

	return true;
}







