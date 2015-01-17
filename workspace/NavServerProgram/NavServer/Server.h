#pragma once
#include <winsock.h>
#include <hash_map>
#include "ClientTraker.h"

class CServer
{
private:
	unsigned int  maxWorkingClientCount;           //Q - ���������� ���������� ������������ ���������� ��������
	unsigned int packageSize;  // ������ ������������ ���������
	int port;
	SOCKET servSocket;          // ��� �����
	sockaddr_in socketInfo;    // ��������� �������� ���������� � ������
	int bindStatus;            // ������ ��������� ���������� ���������� �������� ������ � �������
	int listenStatus;          // ������ ��������� ������������� ������
	std::hash_map<CString, ClientTraker> trackersMap;
	std::vector<CAbstractClient> clients;

public:
	CServer();
	CServer(unsigned int maxWorkingClientCount);
	~CServer();
	void Port(int val) { port = val; }
	SOCKET ServSocket() const { return servSocket; }
	void ServSocket(SOCKET val) { servSocket = val; }
	unsigned int MaxWorkingClientCount() const { return maxWorkingClientCount; }
	std::vector<CAbstractClient> Clients() const { return clients;}
};

