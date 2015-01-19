#pragma once
#include "ClientConnection.h"
#include "TrackersMap.h"
#include "ServerThread.h"
class CServerManager
{
private:
	// �������
	unsigned int  maxWorkingClientCount;           //Q - ���������� ���������� ������������ ���������� ��������
	unsigned int packageSize;  // ������ ������������ ���������
	int port;

private:
	SOCKET servSocket;          // ��� �����
	sockaddr_in socketInfo;    // ��������� �������� ���������� � ������
	int bindStatus;            // ������ ��������� ���������� ���������� �������� ������ � �������
	int listenStatus;          // ������ ��������� ������������� ������
	CServerThread* pThread;

	std::vector<ClientConnection> clients;
	CTrackersMap trackersMap;
public:
	CServerManager();
	CServerManager(int port);
	CServerManager(unsigned int maxWorkingClientCount, int port);
	~CServerManager();

	SOCKET ServSocket() const { return servSocket; }
	void ServSocket(SOCKET val) { servSocket = val; }

	unsigned int MaxWorkingClientCount() const { return maxWorkingClientCount; }
	std::vector<ClientConnection> Clients() const { return clients; }

	sockaddr_in& SocketInfo() { return this->socketInfo; }

	int BindStatus() const { return bindStatus; }
	void BindStatus(int bindStatus) { this->bindStatus = bindStatus; }

	int ListenStatus() const { return listenStatus; }
	void ListenStatus(int listenStatus) { this->listenStatus = listenStatus; }

	int PackageSize() const { return packageSize; }
	int Port() const { return this->port; }

	ClientConnection* getFreeClientConnection();

	CTrackersMap& TrackersMap()
	{
		return this->trackersMap;
	}

	void Start()
	{
		
	}
	void Stop()
	{
		
	}
};

