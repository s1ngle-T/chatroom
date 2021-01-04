#include "pch.h"
#include "MFCApplication1.h"
#include "framework.h"
#include "MFCApplication1Dlg.h"
#include "Client.h"
#include<WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")
#define MAX_BUF_SIZE 1024

HANDLE ListThread1;
int static flag = 0;
CString strnew, strnew1;

HANDLE ListThread;
HANDLE List;



static DWORD  WINAPI ListThreadFuncAll(CMFCApplication1Dlg* pChatRoom)
{

	/*CMFCApplication1Dlg* pChatRoom = (CMFCApplication1Dlg*)pParam;
	ASSERT(pChatRoom != NULL);

	CClientItem item;
	pChatRoom->ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (pChatRoom->ConnectSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("新建socket失败"));
		return FALSE;
	}

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(5000);
	inet_pton(AF_INET, "172.20.10.5", (void*)&server.sin_addr.S_un.S_addr);
	if (connect(pChatRoom->ConnectSocket, (struct sockaddr*) & server, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("连接失败，请重试"));
		goto _Error_End;
	}*/
	//pChatRoom->bls_Server = false;
	//pChatRoom->ShowMsg(_T("连接服务器成功\n"));





	char sendBuffer[2][256] = { "s1ngle","002" };
	/*send(sock, (char*)a, sizeof(a), 0);*/
	int re = send(pChatRoom->ConnectSocket, sendBuffer[0], sizeof(sendBuffer[0]), 0);
	int re1 = send(pChatRoom->ConnectSocket, sendBuffer[1], sizeof(sendBuffer[0]), 0);
	//			if (strcmp(sendBuffer, "quit") == 0)



	TCHAR Bufshow[MAX_BUF_SIZE] = { 0 };
	int iRetshow = recv(pChatRoom->ConnectSocket, (char*)Bufshow, MAX_BUF_SIZE, 0);
	pChatRoom->ShowMsg(Bufshow);



	char s[10];
	recv(pChatRoom->ConnectSocket, s, sizeof(s), 0);
	int n = atoi(s);


	for (int i = 0; i < n; i++)
	{
		CHAR user[2][MAX_BUF_SIZE];
		CString str, str1;
		pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)user[0], 1024);
		pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)user[1], 1024);
		/*str = (WCHAR*)usr;
		str1 = (WCHAR*)usr1;*/
		/*strncpy(user[0], szText.GetBuffer());*/
		str.Format(_T("%s"), CStringW(user[0]));
		str1.Format(_T("%s"), CStringW(user[1]));
		//str1.Format(_T("%s"), CStringW(usr1));

		pChatRoom->showList(str, str1);
		return true;
	}





	/*CHAR user[MAX_BUF_SIZE];
	CString str, str1;
	pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)user, 1024);*/





	/*CHAR usernew[2][MAX_BUF_SIZE ];
	pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)usernew[0], 1024);
	pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)usernew[1], 1024);
	strnew.Format(_T("%s"), CStringW(usernew[0]));
	strnew1.Format(_T("%s"), CStringW(usernew[1]));
	pChatRoom->showList(strnew, strnew1);*/



	int i = 0;
	while (TRUE && !(pChatRoom->ShutDown))
	{

		if (Socket_Select(pChatRoom->ConnectSocket, 100, NULL))
		{

			TCHAR Bufshow[MAX_BUF_SIZE] = { 0 };
			int iRetshow = recv(pChatRoom->ConnectSocket, (char*)Bufshow, MAX_BUF_SIZE, 0);


			if (iRetshow > 0)
			{
				pChatRoom->ShowMsg(Bufshow);

			}



			else
			{
				pChatRoom->ShowMsg(_T("聊天室已断开，请重新连接"));
				break;
			}

		}
		Sleep(500);

	}



//_Error_End:
//	closesocket(pChatRoom->SlistenSocket);
	return true;


	return true;
}

static DWORD  WINAPI ListThreadFunc(CMFCApplication1Dlg* pChatRoom)
{
	char sendBuffer[2][256] = { "s1ngle","002" };
	/*send(sock, (char*)a, sizeof(a), 0);*/
	int re = send(pChatRoom->ConnectSocket, sendBuffer[0], sizeof(sendBuffer[0]), 0);
	int re1 = send(pChatRoom->ConnectSocket, sendBuffer[1], sizeof(sendBuffer[1]), 0);
	//			if (strcmp(sendBuffer, "quit") == 0)


	CHAR Bufshow0[MAX_BUF_SIZE] = { 0 };
	CHAR Bufshow1[MAX_BUF_SIZE] = { 0 };
	int iRetshow0 = recv(pChatRoom->ConnectSocket, (char*)Bufshow0, MAX_BUF_SIZE, 0);
	int iRetshow1 = recv(pChatRoom->ConnectSocket, (char*)Bufshow1, MAX_BUF_SIZE, 0);
	strnew.Format(_T("%s"), CStringW(Bufshow0));
	strnew1.Format(_T("%s"), CStringW(Bufshow1));
	pChatRoom->showList(strnew, strnew1);
	return true;
}






DWORD WINAPI ConnectThreadFunc(LPVOID pParam)
{
	/*CClientItem PClientItem = *(CClientItem*)pParam;
	PClientItem.CName = "zzzz";*/
	CMFCApplication1Dlg* pChatRoom = (CMFCApplication1Dlg*)pParam;
	ASSERT(pChatRoom != NULL);
	CClientItem item;
	pChatRoom->ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (pChatRoom->ConnectSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("新建socket失败"));
		return FALSE;
	}

	//pChatRoom->bls_Server = false;
	/*CString strServIP;
	pChatRoom->GetDlgItemText(SIP_Text, strServIP);
	int uPort = pChatRoom->GetDlgItemInt(SPort_Text);
	if (uPort < 1 || uPort>65535)
	{
		AfxMessageBox(_T("请输入正确的端口号：1-65535"));
		goto _Error_End;

	}*/
	/*char IPAddr[16] = { 0 };
	USES_CONVERSION;
	strcpy_s(IPAddr, 16, T2A(strServIP));*/
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(21);
	inet_pton(AF_INET, "172.20.10.5", (void*)&server.sin_addr.S_un.S_addr);
	if (connect(pChatRoom->ConnectSocket, (struct sockaddr*) & server, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("连接失败，请重试"));
		/*goto _Error_End;*/
	}
	pChatRoom->bls_Server = false;
	pChatRoom->ShowMsg(_T("连接服务器成功\n"));

	char read_buf1[20];
	CString str;
	recv(pChatRoom->ConnectSocket, read_buf1, sizeof(read_buf1), 0);
	
	str.Format(_T("%s"), CStringW(read_buf1));
	pChatRoom->ShowMsg(str);

	//pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)read_buf1, 1024);
	///*str = (WCHAR*)usr;
	//str1 = (WCHAR*)usr1;*/
	///*strncpy(user[0], szText.GetBuffer());*/
	//str.Format(_T("%s"), CStringW(read_buf1));




	//char username[10] = { "toldo" };
	//char send_buf[20];
	//sprintf_s(send_buf, "USER %s\r\n", username);
	//send(pChatRoom->ConnectSocket, username, sizeof(username),0);
	///* 客户端接收服务器的响应码和信息，正常为 ”331 User name okay, need password.” */
	//char read_buf[20];
	//recv(pChatRoom->ConnectSocket, (char*)read_buf, sizeof(read_buf),0);

	///* 命令 ”PASS password\r\n” */
	//char password[10] = { "toldo" };
	//sprintf_s(send_buf, "PASS %s\r\n", password);
	///* 客户端发送密码到服务器端 */
	//send(pChatRoom->ConnectSocket, password, sizeof(password),0);
	///* 客户端接收服务器的响应码和信息，正常为 ”230 User logged in, proceed.” */
	//recv(pChatRoom->ConnectSocket, read_buf, sizeof(read_buf), 0);


	////////////////////////////////////////////////////////////////////

	char sendBuffer[2][256] = { "toldo","toldo"};
	/*send(sock, (char*)a, sizeof(a), 0);*/
	int re = send(pChatRoom->ConnectSocket, sendBuffer[0], sizeof(sendBuffer[0]), 0);

	char read_buf2[20];
	recv(pChatRoom->ConnectSocket, read_buf2, sizeof(read_buf2), 0);

	str.Format(_T("%s"), CStringW(read_buf2));
	pChatRoom->ShowMsg(str);

	int re1 = send(pChatRoom->ConnectSocket, sendBuffer[1], sizeof(sendBuffer[1]), 0);
	//			if (strcmp(sendBuffer, "quit") == 0)


	char read_buf3[20];
	recv(pChatRoom->ConnectSocket, read_buf3, sizeof(read_buf3), 0);

	str.Format(_T("%s"), CStringW(read_buf3));
	pChatRoom->ShowMsg(str);

	TCHAR Bufshow1[MAX_BUF_SIZE] = { 0 };
	int iRetshow1 = recv(pChatRoom->ConnectSocket, (char*)Bufshow1, MAX_BUF_SIZE, 0);
	pChatRoom->ShowMsg(Bufshow1);


	char s[10];
	recv(pChatRoom->ConnectSocket, s, sizeof(s), 0);
	int n = atoi(s);

	for (int i = 0; i < n; i++)
	{
		CHAR user[2][MAX_BUF_SIZE];
		CString str, str1;
		pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)user[0], 1024);
		pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)user[1], 1024);
		/*str = (WCHAR*)usr;
		str1 = (WCHAR*)usr1;*/
		/*strncpy(user[0], szText.GetBuffer());*/
		str.Format(_T("%s"), CStringW(user[0]));
		str1.Format(_T("%s"), CStringW(user[1]));
		//str1.Format(_T("%s"), CStringW(usr1));

		pChatRoom->showList(str, str1);
	}
	

	/*CHAR usernew[2][MAX_BUF_SIZE ];
	pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)usernew[0], 1024);
	pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)usernew[1], 1024);
	strnew.Format(_T("%s"), CStringW(usernew[0]));
	strnew1.Format(_T("%s"), CStringW(usernew[1]));
	pChatRoom->showList(strnew, strnew1);*/



	int i = 0;
	while (TRUE && !(pChatRoom->ShutDown))
	{
		/*CHAR usernew[2][MAX_BUF_SIZE ];
	pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)usernew[0], 1024);
	pChatRoom->RecvAll(pChatRoom->ConnectSocket, (char*)usernew[1], 1024);
	strnew.Format(_T("%s"), CStringW(usernew[0]));
	strnew1.Format(_T("%s"), CStringW(usernew[1]));
	pChatRoom->showList(strnew, strnew1);*/


		if (Socket_Select(pChatRoom->ConnectSocket, 100, NULL))
		{
		
					TCHAR Bufshow[MAX_BUF_SIZE] = { 0 };
					int iRetshow = recv(pChatRoom->ConnectSocket, (char*)Bufshow, MAX_BUF_SIZE, 0);


					if (iRetshow > 0)
					{
						pChatRoom->ShowMsg(Bufshow);

					}



					else
					{
						pChatRoom->ShowMsg(_T("聊天室已断开，请重新连接"));
						break;
					}
				//}
				
				
		}
			Sleep(500);

		}



//_Error_End:
//	closesocket(pChatRoom->SlistenSocket);
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


//
//DWORD WINAPI ListThreadFunc(LPVOID pParam)
//{
//	/*CClientItem PClientItem = *(CClientItem*)pParam;
//	PClientItem.CName = "zzzz";*/
//	CMFCApplication1Dlg* pChatRoom = (CMFCApplication1Dlg*)pParam;
//	ASSERT(pChatRoom != NULL);
//	pChatRoom->ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	TCHAR Buf[MAX_BUF_SIZE] = { 0 };
//	int iRet = recv(pChatRoom->ConnectSocket, (char*)Buf, MAX_BUF_SIZE, 0);
//
//	TCHAR Buf1[MAX_BUF_SIZE] = { 0 };
//	int iRet1 = recv(pChatRoom->ConnectSocket, (char*)Buf1, MAX_BUF_SIZE, 0);
//	pChatRoom->showList(Buf, Buf1);
//	return true;
//
//}




//DWORD WINAPI ClientPro(LPVOID pParam)
//{
//
//	CString strMsg;
//	CClientItem PClientItem = *(CClientItem*)pParam;
//	PClientItem.CName = "zzzz";
//	PClientItem.pMainWnd->SendClientList(PClientItem.CName + _T("\n"));
//	//strMsg = _T("客户端：") + PClientItem.CName + _T("加入了聊天室");
//	//PClientItem.pMainWnd->ShowList(PClientItem.CID, PClientItem.CIP);
//	/*PClientItem.pMainWnd->ShowMsg(strMsg);
//	PClientItem.pMainWnd->ShowMsg(strMsg);*/
//	while (TRUE && !(PClientItem.pMainWnd->ShutDown))
//	{
//		if (Socket_Select(PClientItem.Soket, 100, TRUE))
//		{
//			TCHAR szBuf[MAX_BUF_SIZE] = { 0 };
//			int iRet = recv(PClientItem.Soket, (char*)szBuf, MAX_BUF_SIZE, 0);
//			if (iRet > 0)
//			{
//				strMsg.Format(_T("%s"), szBuf);
//				strMsg = _T("客户端：") + PClientItem.CName + _T(">") + strMsg;
//				PClientItem.pMainWnd->ShowMsg(strMsg);
//			}
//			else
//			{
//				strMsg = _T("客户端：") + PClientItem.CName + _T("离开了聊天室");
//				PClientItem.pMainWnd->ShowMsg(strMsg);
//				PClientItem.pMainWnd->RemoveClient(PClientItem);
//				break;
//
//			}
//		}
//		Sleep(500);
//	}
//	return true;
//}



