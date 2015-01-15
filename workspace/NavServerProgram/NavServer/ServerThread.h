#pragma once
#include "afxwin.h"
#include "DBWork.h"
#include "stdafx.h"
#include "ClientThread.h"
#define SIZE 4048         // ������ ������������ ���������
/*
& - ������ ��������� �� ��������� 3dEditor
@ - ������ ��������� �� ��������� PCMobileGPS
*/
class CServerThread :	public CWinThread
{
private:
 int Port;
 CListBox *ListBox;
 WSADATA WSAData;           // ��������� ������������ DLL
 SOCKET WinSocket;          // ��� �����
 sockaddr_in SockStruct;    // ��������� �������� ���������� � ������
 int Bind;                  // ������ ��������� ���������� ���������� �������� ������ � �������
 int Listen;                // ������ ��������� ������������� ������
 unsigned int  Q;           // ���������� ���������� ������������ ���������� ��������
 CString List;
 HANDLE hMainThread;        // ���������� ��������� ������
 HANDLE hGetMes;            // ���������� �������, ������������ ��� ���������
 CADOConnection *m_connection; 
 vector<CServerUsersThread * > hRecv;
 bool Terminated;
public:
	 virtual BOOL InitInstance();
	 CServerThread();
 	 CServerThread(int Port,CListBox *OutPut, CADOConnection *DbConnect);
	~CServerThread(void);
	virtual int Run();
	void Terminate();
};
extern  vector<User> users;