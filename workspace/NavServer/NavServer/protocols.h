#pragma once
#include "stdafx.h"


struct TDispetcherProtocol
{
	CString IMEI;
	CString DTime1, DTime2;
	int type;
	int RunTime;
};

struct TGPSPoint
{
	CString IMEI;
	CString Longitude;     //�������
	CString Description;   //������
	CString Height;        //������
	CString DateTime;     //����� ������� ��������� �� ������
};