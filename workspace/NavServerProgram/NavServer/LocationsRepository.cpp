#include "stdafx.h"
#include "NavServerApp.h"
#include "LocationsRepository.h"

CLocationsRepository::CLocationsRepository(CAbstractDbConnectionFactory& _connectionFactory)
:connectionFactory(_connectionFactory)
{
}

CLocationsRepository::~CLocationsRepository(void)
{
}

void CLocationsRepository::insert(TGPSPoint &Add)
{
	TRY_ADO()//������ ��������� ����������
	CADORecordset rs;
	
	rs.SetConnection(connectionFactory.getConnection());//�������� ��������� ������� CADOConnection
	//sql-������, ������ ������� ������ ������ � ������������� �� �� ���� Hardware(���������� ����� ����������)       
	rs.SetSQL("select num_rec,[Hardware],[HardCaption], [Longitude], [Description],[Height],[Date] from DATA order by [Hardware]");
	rs.SetOpenMode(true);// ������ ������������ ������
	rs.Open();           // ��������� ������ � ������
	if (!rs.IsEmpty())   // ���� �� ������ � ��?
		rs.Last();        // ���� ��, ��������� � �����
	rs.AddNew();         // �������� ������, � ���, ��� �� ����� �������� ������
	try
	{
		//�������� ������
		rs.SetField("Hardware", _variant_t(CT2CA((LPCTSTR)Add.IMEI)));
		rs.SetField("HardCaption", _variant_t(CT2CA((LPCTSTR)Add.IMEI)));
		rs.SetField("Longitude", _variant_t(CT2CA((LPCTSTR)Add.Longitude)));
		rs.SetField("Description", _variant_t(CT2CA((LPCTSTR)Add.Description)));
		rs.SetField("Height", _variant_t(CT2CA((LPCTSTR)Add.Height)));
		rs.SetField("Date", _variant_t(CT2CA((LPCSTR)Add.DateTime)));
		rs.Update();    //��������� ���������
	}
	catch (CADOException&)
	{
		//� ������ ������ �������� ���������
		try
		{
			rs.Cancel();
		}
		catch (...)
		{
		}
		throw;
	}
	rs.Close();//��������� ������� ����������
	CATCH_ADO()
}

void CLocationsRepository::clear()
{
	TRY_ADO()
		CADORecordset rs;
	rs.SetConnection(connectionFactory.getConnection());
	rs.SetSQL("DELETE FROM DATA ");
	rs.Open();
	CATCH_ADO()
}

/*
void ClientThread::writeDB(TGPSPoint &Add)
{
	if (Add.DateTime == "" || Add.Description == "" || Add.Height == "" || Add.IMEI == "" || Add.Longitude == "")
		return;

	TRY_ADO()//������ ��������� ����������
	if (!rs.IsEmpty())   // ���� �� ������ � ��?
		rs.Last();        // ���� ��, ��������� � �����
	rs.AddNew();         // �������� ������, � ���, ��� �� ����� �������� ������
	try
	{
		//�������� ������
		rs.SetField("Hardware", _variant_t(CT2CA((LPCTSTR)Add.IMEI)));
		rs.SetField("HardCaption", _variant_t(CT2CA((LPCTSTR)Add.IMEI)));
		rs.SetField("Longitude", _variant_t(CT2CA((LPCTSTR)Add.Longitude)));
		rs.SetField("Description", _variant_t(CT2CA((LPCTSTR)Add.Description)));
		rs.SetField("Height", _variant_t(CT2CA((LPCTSTR)Add.Height)));
		rs.SetField("Date", _variant_t(CT2CA((LPCSTR)Add.DateTime)));
		rs.Update();    //��������� ���������
	}
	catch (CADOException&)
	{
		//� ������ ������ �������� ���������
		try
		{
			rs.Cancel();
		}
		catch (...)
		{
		}
		throw;
	}

	CATCH_ADO()
}*/