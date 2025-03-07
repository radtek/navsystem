//adoclasses.h
#ifndef __ADO__CLASSES__H__
#define __ADO__CLASSES__H__

#include "stdafx.h"

//#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll" rename("EOF", "EndOfFile")


//----CADOException--------------------------------------------------
class CADOException
{
public:
	virtual ~CADOException() {
	}
	virtual const char* What() const {
		return "";
	}
	virtual int GetCode() const {
		return 0;
	}
};
//-------------------------------------------------------------------


//----CADOConnectionException----------------------------------------
class CADOConnectionException : public CADOException
{
public:
	enum _errConnection {
		ceUnknown, ceCantCreateConnection, ceConnectionNotExists, ceConnectionNotOpen,
		ceErrCloseConnection, ceConnectionAlreadyOpen, ceErrOpenConnection, ceErrExecuteCmd
	};
	explicit CADOConnectionException(_errConnection ec)
		: m_errCode(ec), m_strMsg(""), m_bHasDescription(false) {
	}
	explicit CADOConnectionException(const char *pStrMsg)
		: m_errCode(ceUnknown), m_strMsg(pStrMsg), m_bHasDescription(false) {
	}
	CADOConnectionException(_errConnection ec, const char *pStrMsg, bool bHasDescription = false)
		: m_errCode(ec), m_strMsg(pStrMsg), m_bHasDescription(bHasDescription) {
	}
	virtual int GetCode() const {
		return static_cast<int>(m_errCode);
	}
	const char* GetDescription() const {
		return m_strMsg.c_str();
	}
	bool HasDescription() const {
		return m_bHasDescription;
	}

	virtual const char* What() const {
		if (!m_bHasDescription && m_strMsg.length())
			return m_strMsg.c_str();
		switch (m_errCode)
		{
		case ceUnknown: return "������ �� ����� ��������";
		case ceCantCreateConnection: return "������ ��� �������� ������� \"����������\"";
		case ceConnectionNotExists: return "������ \"����������\" �� ������";
		case ceConnectionNotOpen: return "���������� �� �������";
		case ceErrCloseConnection: return "������ ��� �������� ����������";
		case ceConnectionAlreadyOpen: return "���������� ��� �������";
		case ceErrOpenConnection: return "������ ��� �������� ����������";
		case ceErrExecuteCmd: return "������ ��� ���������� �������";
		default: break;
		}
		return "����������� ������";
	}
private:
	_errConnection m_errCode;
	string m_strMsg;
	bool m_bHasDescription;
};

class CADORecordsetException : public CADOException
{
public:
	enum _errRecordset {
		reUnknown, reRecordsetNotCreated, reRecordsetNotClosed, reCannotCreateCmd,
		reCannotCreateRecordset, reRecordsetAlreadyExists, reErrOpenRecordset,
		reRecordsetNotOpen, reErrMoveFirst, reErrMoveLast, reErrMoveNext, reErrMovePrev,
		reErrGetEoF, reErrGetBoF, reErrGetField, reErrCloseRecordset, reErrAddNewRecord,
		reErrUpdateRecordset, reErrSetField, reErrCancel, reErrGetFieldsCount,
		reErrSafeBookmark, reErrSafeGoToBookmark
	};
	explicit CADORecordsetException(_errRecordset re)
		: m_errCode(re), m_strMsg(""), m_bHasDescription(false) {
	}
	explicit CADORecordsetException(const char *pStrMsg)
		: m_errCode(reUnknown), m_strMsg(pStrMsg), m_bHasDescription(false) {
	}
	CADORecordsetException(_errRecordset re, const char *pStrMsg, bool bHasDescription = false)
		: m_errCode(re), m_strMsg(pStrMsg), m_bHasDescription(bHasDescription) {
	}
	virtual int GetCode() const {
		return static_cast<int>(m_errCode);
	}
	const char* GetDescription() const {
		return m_strMsg.c_str();
	}
	bool HasDescription() const {
		return m_bHasDescription;
	}
	virtual const char* What() const {
		if (!m_bHasDescription && m_strMsg.length())
			return m_strMsg.c_str();
		switch (m_errCode)
		{
		case reUnknown: return "������ �� ����� ��������";
		case reRecordsetNotCreated: return "������ \"����� �������\" �� ������";
		case reRecordsetNotClosed: return "\"����� �������\" �� ������";
		case reCannotCreateCmd: return "������ ��� �������� ������� \"��������\"";
		case reCannotCreateRecordset: return "������ ��� �������� ������� \"����� �������\"";
		case reRecordsetAlreadyExists: return "����� ������� ��� ����������";
		case reErrOpenRecordset: return "������ ��� �������� ������ ������";
		case reRecordsetNotOpen: return "����� ������� �� ������";
		case reErrMoveFirst: return "������ ��� �������� �� ������ ������";
		case reErrMoveLast: return "������ ��� �������� �� ��������� ������";
		case reErrMoveNext: return "������ ��� �������� �� ��������� ������";
		case reErrMovePrev: return "������ ��� �������� �� ���������� ������";
		case reErrGetEoF: return "������ ��� ����������� ������ ������ �������";
		case reErrGetBoF: return "������ ��� ����������� ����� ������ �������";
		case reErrGetField: return "������ ��� ��������� �������� ����";
		case reErrCloseRecordset: return "������ ��� �������� ������ ������";
		case reErrAddNewRecord: return "������ ��� ���������� ����� ������";
		case reErrUpdateRecordset: return "������ ��� ���������� ������ �������";
		case reErrSetField: return "������ ��� ��������� �������� ����";
		case reErrCancel: return "������ ��� ������";
		case reErrGetFieldsCount: return "������ ��� ��������� ���������� ����� ������ �������";
		case reErrSafeBookmark: return "������ ��� ���������� ��������";
		case reErrSafeGoToBookmark: return "������ ��� �������� �� ��������";
		default: break;
		}
		return "����������� ������";
	}
private:
	_errRecordset m_errCode;
	string m_strMsg;
	bool m_bHasDescription;
};

class CADOConnection;
//-------------------------------------------------------------------

class CADORecordset
{
public:
	CADORecordset();
	virtual ~CADORecordset();
	bool IsCreated() const;//������ �� ������?
	bool IsOpen() const;   //������� �� ��?
	void SetConnection(CADOConnection *pConnection); //��������� � ������� pConnection
	void SetSQL(const char *pStrSQL);//��������� SQL- ������
	void AddParam(DataTypeEnum prmType, const _variant_t &vtPrm);
	void SetOpenMode(bool bDynamicOpen);
	void Open();//������� ��
	void Close();//������� ��
	void First();//��������� ������ �� ������ ������
	void Last(); //��������� ������ �� ��������� ������
	void Next(); //��������� ������ �� ��������� ������
	void Prev();
	bool IsEoF();//��������� �� ���������� �������?
	bool IsBoF();//��������� �� ���������� �������?
	bool IsEmpty();
	//�������� ������:
	_variant_t GetField(short nNumField);
	_variant_t GetField(const char *pFieldName);
	//�������� ������/������:
	void SetField(short nNumField, const _variant_t &vtValue);
	void SetField(const char *pFieldName, const _variant_t &vtValue);
	void SetArrayField(const char *pFieldName, const void *pBuf, int nBytes);
	void SetArrayField(short nNumField, const void *pBuf, int nBytes);
	void AddNew();//����������
	void Update();//���������� ��������� � ���� ������
	void Cancel();//������ ������������� ���������

	int GetFieldsCount() const; //�������� ���������� �������
	void SafeBookmark();
	void GoToBookmark();
	long GetCountRecs();
	bool IsNewRecord() const;
	bool IsEditing() const;
private:
	CADOConnection *m_pConnection;//��������� �� ������ �����. ��
	//���������� �������� ADO �� ��������� msado15.dll
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	_bstr_t m_strSQL;
	bool m_bDynamicOpen;//��� �������
	_ConnectionPtr GetAdoConnection();
	struct SQL_PARAMS {
		DataTypeEnum prmType;
		_variant_t vtParam;
	};
	list<SQL_PARAMS> m_lstParam;
	_variant_t m_vtBookmark;
	bool m_bNewRecond;
	bool m_bEditing;
	void CheckOpen();
};
//-------------------------------------------------------------------

class CADOConnection
{
public:
	CADOConnection();
	//������������ � ����������� ����������� � ��
	CADOConnection(const char *pStrConnection, const char *pStrUserID = "", const char *pStrPassword = "", bool bOpen = false);
	CADOConnection(int nJetVer, int nJetVerEx, const char *pStrFileName,
		const char *pStrUserID = "", const char *pStrPassword = "", bool bOpen = false);
	//���� �� ������� �����������?
	bool IsCreated() const;
	//���� �� ������� ��?
	bool IsOpen() const;
	//������ ����. ��������� �����������: ������ �����., ��� ������������, ������
	void SetConnectionParam(const char *pStrConnection, const char *pStrUserID = "", const char *pStrPassword = "");
	//������ ����. ��������� �����������: ��� ��������,������ ��������, ��� ��, ��� ������������,������
	void SetMSAccessConnectionParam(int nJetVer, int nJetVerEx, const char *pStrFileName,
		const char *pStrUserID = "", const char *pStrPassword = "");

	void Open();         	         //������� ��
	void Close();                    //������� ��
	void Destroy();                  //���������� ������
	void Execute(const char *pStrCmd);
	virtual ~CADOConnection();
private:

	CADOConnection(const CADOConnection &) {}
	void operator = (const CADOConnection &) {}
	//���������� �������� ADO �� ��������� msado15.dll
	_ConnectionPtr m_pConnection;
	_bstr_t m_strConnection;
	_bstr_t m_strUserID;
	_bstr_t m_strPassword;
	friend class CADORecordset;
};
//-------------------------------------------------------------------


#endif

