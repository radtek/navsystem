#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "AbstractOutputStream.h"
#include "ClientThread.h"
/*
& - ������ ��������� �� ��������� 3dEditor
@ - ������ ��������� �� ��������� PCMobileGPS
*/
class CServerThread : public CWinThread
{
private:
	WSADATA WSAData;           // ��������� ������������ DLL
	HANDLE hMainThread;        // ���������� ��������� ������
	HANDLE hGetMes;            // ���������� �������, ������������ ��� ���������
	vector<ClientThread * > hRecv;
	bool terminated;
	CAbstractOutputStream &stream;

public:
	virtual BOOL InitInstance();
	CServerThread(CAbstractOutputStream &stream);
	~CServerThread(void);
	virtual int Run();
	void Terminate();
};