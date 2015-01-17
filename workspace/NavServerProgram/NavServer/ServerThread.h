#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "GPSPointRepository.h"
#include "AbstractOutputStream.h"
#include "ClientThread.h"
#include "Server.h"
/*
& - ������ ��������� �� ��������� 3dEditor
@ - ������ ��������� �� ��������� PCMobileGPS
*/
class CServerThread : public CWinThread
{
private:
	WSADATA WSAData;           // ��������� ������������ DLL
	CString List;
	HANDLE hMainThread;        // ���������� ��������� ������
	HANDLE hGetMes;            // ���������� �������, ������������ ��� ���������
	vector<ClientThread * > hRecv;
	bool terminated;
	CServer &server;
	CAbstractOutputStream &stream;
public:
	virtual BOOL InitInstance();
	CServerThread(CServer &serv, CAbstractOutputStream &stream);
	~CServerThread(void);
	virtual int Run();
	void Terminate();
};