#pragma once
#include "afxwin.h"
#include "GPSPointRepository.h"
/*
*/


class ClientThread : public CWinThread
{

// gui
private:
	CListBox *ListBox;

private:
	static const int SIZE;
	int userIndex;
	
	User *user;
	int Send;                  // ���������� ������ ��������� �������� ���������
	int Recv;                  // ���������� ������ ��������� ������ ���������
	bool Terminated;
	CString IP;
	int port;
	CADORecordset rs;
public:
	void DelteFromMass(CString ID, int indexUser);//����� ����� indexUser  � ������� � ��������� ������ �� ���-�� ID 
	void AddToMass(CString ID, int indexUser);//�������� ����� indexUser � ������� �� ��������� ������ �� ���-�� ID
	void LoadDataFromDB(int *Accept, TEditorProtocol EditorProtocol);/*������ ���� ������ � ���������� ��������� ��������
																	  EditorProtocol, ������� ������� - ��������� ������ ��������� 3deditor  */
	bool SendGPSPoint(int *SOCKET, TGPSPoint GPSPoint);
	virtual BOOL InitInstance();

	void EditorMessage(CString protocol);
	void MobileMessage(CString protocol);

	void Stop();
	ClientThread(CListBox *ListBox, User *user, int UserIndex);
	~ClientThread(void);

	//void writeDB(TGPSPoint &Add);
	virtual int Run();
	virtual void Delete();
	void Terminate();
	virtual int ExitInstance();
};
