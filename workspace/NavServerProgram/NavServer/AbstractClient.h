#pragma once

class CAbstractClient
{
protected:
	bool active;             // ������� ����, ��� ������ ��������� (true - ���������, false - ��������)
	int accept;              // ����� ������������� �������
	sockaddr_in acpStruct;   // �������� �������� ���������� � ������������ �������
	int size;                // ������ ���� ���������
	CString IP;              // IP-����� �������
public:
	CAbstractClient();
	virtual ~CAbstractClient();

};

