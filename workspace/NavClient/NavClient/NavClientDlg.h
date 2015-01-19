// NavClientDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ClientThread.h"


// CNavClientDlg dialog
class CNavClientDlg : public CDialog
{
// Construction
public:
	CNavClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NAVCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnConnect();


//**********************
HANDLE hMainThread;         // ���������� ��������� ������
HANDLE hGetMes;             // ���������� �������, ������������ ��� ���������
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

	bool ConnectByServer();
CClientThread *ClientThread;
//**********************
	CIPAddressCtrl m_Adress;
	CButton m_Disconnect;
	CButton m_Connect;
	CEdit m_Port;
	CString m_TextPort;
	afx_msg void OnBnDisconnected();
	afx_msg void OnBnClickedCheckThread();
	CButton m_ThreadCheck;
	afx_msg void OnClose();
	CEdit m_idCtrl;
};
