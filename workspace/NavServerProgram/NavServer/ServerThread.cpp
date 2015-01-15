#include "StdAfx.h"
#include "ServerThread.h"


CServerThread::CServerThread(int Port,CListBox *OutPut, CADOConnection *DbConnect)
{
	this->Port=Port;
	this->ListBox=OutPut;
	this->m_connection=DbConnect;

	Q=1000;
	users.resize(Q+2);
	hRecv.resize(Q+2);
	Terminated=false;
}

CServerThread::~CServerThread(void)
{
   unsigned int i;
	for(i=0;i<users.size();i++)
	{
		if(users[i].active==true )
		{
			closesocket(users[i].Accept);
			users[i].Accept=NULL;
           if(hRecv[i]!=NULL)
			hRecv[i]->Terminate();
			WaitForSingleObject(*hRecv[i],500);
		}
	}
}
BOOL  CServerThread::InitInstance()
{
	return true;
}
int CServerThread::Run()
{

 CString Message;
 unsigned int i;
 ListBox->AddString("");
 ListBox->AddString(">> ������ ������ ���������...");
 if (WSAStartup(MAKEWORD(2,1), &WSAData) != 0)
 {
	ListBox->AddString(">> ������! ���������� ���������������� ���������� �������! ������� MainThread()");
    return WM_QUIT;
 }
 // ������� �����
 WinSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 if (WinSocket == SOCKET_ERROR)
 {
    ListBox->AddString(">> ������!  ���������� ������� �����! ������� MainThread()");
	return WM_QUIT;
 }
 // ��������� ���� ��������� ��� ������
 SockStruct.sin_family = AF_INET;
 SockStruct.sin_port = Port;
 SockStruct.sin_addr.s_addr = INADDR_ANY; 
// ��������� ��������� ������� ����� � �������
 Bind = bind(WinSocket, (sockaddr*)&SockStruct, sizeof(SockStruct));
 if (Bind == SOCKET_ERROR)
 {
    ListBox->AddString(">> ������! ���������� ������� ��������� ������� ����� � �������! ������� MainThread()");
	return WM_QUIT;
 }
// ������ ������������ ������� � �������
 Listen = listen(WinSocket, 5);
 if (Listen == SOCKET_ERROR)
 {
    ListBox->AddString(">> ������! ���������� ������� ��������� ������� ����� � �������! ������� MainThread()");
	return WM_QUIT;
 }
 Message.Format(">> ��������� ���������� ��������. ����������� ������������� ����� %d ...",Port);
 ListBox->AddString((LPCSTR)Message);
// ��������� ������� ��� ���� ��������
  for (i=0; i<Q; i++)
  {
        users[i].active = false;
        users[i].size = sizeof(users[i].AcpStruct);
        users[i].IP = "";
  }
  // ������ ������������ ������� � �������
  List = "";
  int num=0;
   while (true)
   {
	   if(Terminated==true) break;
              for (int i=Q; i>0; i--)
                if (users[i].active == false)
                  num = i;
 	   users[num].Accept = accept(WinSocket, (sockaddr*)&users[num].AcpStruct, (int*)&users[num].size);
             if (users[num].Accept != SOCKET_ERROR)
              {
				   CString str,ipStr;
				   ipStr=inet_ntoa(users[num].AcpStruct.sin_addr);
				   str.Format("����������� ������.  IP: %s ����: %d",ipStr,users[num].AcpStruct.sin_port	);
				   ListBox->AddString((LPCSTR) str);
				  // ������������� ���� ����, ��� ������ ���������
                   users[num].active = true;
			    //������� ����� ���������/�������� ��������� �� ������� ������� 
				   hRecv[num]=new CServerUsersThread(ListBox,&users[num],num);
				   hRecv[num]->CreateThread();

			  }
			  
     }
  
	return WM_QUIT;
}
void CServerThread::Terminate()
{
  Terminated=true;
  closesocket(WinSocket);
}