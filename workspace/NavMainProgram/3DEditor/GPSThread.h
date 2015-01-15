#pragma once
#include "afxwin.h"
/*#include "afx.h"
#include "stdafx.h"*/
#define SIZE 2048         // ������ ������������ ���������



class CGPSThread :	public CWinThread
{
	/*
HANDLE hMainThread;        // ���������� ��������� ������
HANDLE hGetMes;             // ���������� �������, ������������ ��� ���������
*/
WSADATA WSAData;           // ��������� ������������ DLL

SOCKET *WinSocket;          // ��� �����
sockaddr_in SockStruct;    // ��������� �������� ���������� � ������

int Bind;                  // ������ ��������� ���������� ���������� �������� ������ � �������
int Listen;                // ������ ��������� ������������� ������
int Connect;               // ���������� ������ ��������� ����������� ������� � �������
int Send;                  // ���������� ������ ��������� �������� ���������
int Recv;                  // ���������� ������ ��������� ������ ���������
bool Terminated;
CString List ;
CString ServIP;
int Port;
char Buffer[SIZE]; 
virtual BOOL InitInstance();
void GetMessage(CString Msg);//������������ ��������� � ������� ���������
public:
    virtual	int Run();
	CGPSThread(SOCKET *WinSocket);
	
	void Terminate();
	~CGPSThread(void);
	virtual int ExitInstance();
};
