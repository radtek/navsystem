#include "stdafx.h"
#include "GPSPointRepository.h"
#include "NavServer.h"

GPSPointRepository::GPSPointRepository(void)
{
}

GPSPointRepository::~GPSPointRepository(void)
{
}

void GPSPointRepository::insert(TGPSPoint &Add)
{
	TRY_ADO()//������ ��������� ����������
		CADORecordset rs;
	rs.SetConnection(&theApp.m_connection);//�������� ��������� ������� CADOConnection
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

void GPSPointRepository::clearDB()
{
	TRY_ADO()
		CADORecordset rs;
	rs.SetConnection(&theApp.m_connection);
	rs.SetSQL("DELETE FROM DATA WHERE Hardware = '234324235' ");
	rs.Open();
	CATCH_ADO()
}
