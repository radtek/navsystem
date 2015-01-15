#pragma once
#include "afxwin.h"
#include "DBWork.h"
/*
*/


class CServerUsersThread :
	public CWinThread
{
	 static const int SIZE; 
     int UserIndex;
     CListBox *ListBox;
	 User *user;
	 int Send;                  // ���������� ������ ��������� �������� ���������
     int Recv;                  // ���������� ������ ��������� ������ ���������
     bool Terminated;
	 CString IP;
	 int port;
	     CADORecordset rs;
public:
  void DelteFromMass(CString ID,int indexUser);//����� ����� indexUser  � ������� � ��������� ������ �� ���-�� ID 
  void AddToMass(CString ID,int indexUser);//�������� ����� indexUser � ������� �� ��������� ������ �� ���-�� ID
  void LoadDataFromDB(int *Accept,TEditorProtocol EditorProtocol);/*������ ���� ������ � ���������� ��������� ��������  
																	EditorProtocol, ������� ������� - ��������� ������ ��������� 3deditor  */
  bool SendGPSPoint(int *SOCKET,TGPSPoint GPSPoint);
	 virtual BOOL InitInstance();
 	 
   //  CDBWork DBWork;
	 void EditorMessage(CString protocol);
	 void MobileMessage(CString protocol);

 void Stop();
	CServerUsersThread(CListBox *ListBox,User *user,int UserIndex);
	~CServerUsersThread(void);

void writeDB(TGPSPoint &Add);
	virtual int Run();
	virtual void Delete();
	void Terminate();
	virtual int ExitInstance();
};
