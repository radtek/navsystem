#pragma once
#include "AbstractClient.h"
class ClientTraker : public CAbstractClient
{
private:
	CString IMEI;
	vector<int> users; //������ ������, ������� ���� ��������� ���. ������ �� IMEI
public:
	ClientTraker();
	~ClientTraker();
};

