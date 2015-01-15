#pragma once
#include <vector>
using std::vector;
#include "GPSThread.h"
#include "include.h"
/*������� ��� ���� ��������� ����������: ������� � ��������:

�������  - &#<ID>#<t1>#<t2>#<bool: 1- �������; 0- �������� >;
�������� - &#<ID>#<t1>#<t2>#<bool: 1- �������; 0- �������� >;^<���(caption) ����������>.

������� FileToLanProtocol() - ��������������� �������� � �������, �.�. ������� <���(caption) ����������> �� ������
 � ���������:
 protocol     = �������
 fileprotocol = ��������
*/
/*
@#<ID>#<Lo>#<De>#<Height>#<Time>;
*/

class CGPS
{
//HANDLE hMainThread;         // ���������� ��������� ������
//HANDLE hGetMes;             // ���������� �������, ������������ ��� ���������
WSADATA WSAData;           // ��������� ������������ DLL
SOCKET WinSocket;          // ��� �����
sockaddr_in SockStruct;    // ��������� �������� ���������� � ������

int Bind;                  // ������ ��������� ���������� ���������� �������� ������ � �������
int Listen;                // ������ ��������� ������������� ������
int Connect;               // ���������� ������ ��������� ����������� ������� � �������
int Send;                  // ���������� ������ ��������� �������� ���������
int Recv;                  // ���������� ������ ��������� ������ ���������

CString List ;
CString ServIP;
bool connected;
int Port;

CGPSThread *GPSThread;

	bool ConnectByServer();
    bool LoadDataOfServ();//��������� ������ � ����� � �����  RES/Settings.lan
    
public:
    vector<THardware> HardwareList; //������ ���������, ���� � ������� ����������� � ������� 
	
	void UpdateHardwareList(int DelIndex);
	bool IsConnected();
    void StartGPS();
	void StopGPS();
	THardware* GetDrive(int index);
    void AddGPSHardware(THardware hard);
	bool LoadHardwareToList(CListBox* ListBox);
	bool LoadHardwareToList(CComboBox* ComboBox);
    bool LoadWindowOfGHardToList(int HardIndex,CListBox *ListBox);/*��������� � ListBox ������ ����, ������. � ����� ����������*/
	int LoadWindowOfGHardToChList(int HardIndex,CCheckListBox *ListBox);/*��������� � ListBox ������ ���� ����,
																 � �������� ��, � ������� ���������
																 ���������� HardwareList[HardIndex] ���������� ����� ����� ������� ������*/
	void LoadFromFile(CString FileName,CListBox *ListBox,bool IsSend);/*��������� � ����� ������ ��������� � HardwareList
																	  � ������� � ListBox`� ���� IsSend=true -
																	  ��������� ������ �� ������*/
	void SaveToFile(CString FileName);/*��������� �� ���� ������ ��������� � ������� ������� */
	CString    HardwareToProtocol(THardware *hard,bool protocol_type,bool del);   //������� ������(��������) ������ �� ���������� hard
    THardware* FileProtocolToHradware(CString FProtocol);  //��������� ��������� THardware �� ������(�.���������) Protokol
	SOCKET* GetSocket();
	CString FileToLanProtocol(CString FileP);//�������� �������� � �������
    void SendHardwareList();//�������� ������ �� ��������� ��������� �� ���� ���������  HardwareList 
	bool TestIdentityHard(THardware *hard);//�������� ������������ ����������(���� �� ��� ����� � HardwareList)
	
	THardware* GetHrdwareElem(CString IMEI);//�������� ����������, �������� ������ IMEI
	void SendAllDelHardware(); //��������� �� ������, ��� ������ �����������
	CGPS(void);
	~CGPS(void);
};
