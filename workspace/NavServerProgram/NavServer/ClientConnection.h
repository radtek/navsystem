#pragma once

enum ClientType;
class CAbstractClientHandler;

class ClientConnection
{
private:
	int id;
	bool active;                   // ������� ����, ��� ������ ��������� (true - ���������, false - ��������)

	SOCKET accept;                    // ����� ������������� �������
	sockaddr_in socketInfo;        // �������� �������� ���������� � ������������ �������
	int socketInfoSize;            // ������ ��������� socketInfo
	CString clientIP;              // IP-����� �������
	CAbstractClientHandler* clientHandler;
public:
	ClientConnection();
	~ClientConnection();

	int Accept() const{ return accept; }


	void Accept(SOCKET accept)
	{
		this->accept = accept;
	}

	sockaddr_in& SocketInfo(){ return this->socketInfo; }
	void SocketInfo(sockaddr_in socketInfo){ this->socketInfo = socketInfo; }

	CString IP()
	{
		clientIP = inet_ntoa(socketInfo.sin_addr);
		return clientIP;
	}

	int& SocketInfoSize(){ return socketInfoSize; }

	int Port()
	{
		return socketInfo.sin_port;
	}

	bool isActive() const{ return active; }
	void Active(bool active) { this->active = active; }

	int ID() const { return id; }
	void ID(int id){ this->id = id; }

	void setupClientHandler(ClientType type);

	CAbstractClientHandler* ClientHandler()
	{
		return this->clientHandler;
	}
	
	void close();
	
};

