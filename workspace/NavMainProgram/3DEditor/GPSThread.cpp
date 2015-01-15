#include "StdAfx.h"
#include "GPSThread.h"
#include "3DEditor.h"
CGPSThread::CGPSThread(SOCKET *WinSocket)
{
	this->WinSocket=WinSocket;
	Terminated=false;
}

CGPSThread::~CGPSThread(void)
{

}
BOOL  CGPSThread::InitInstance()
{
	m_bAutoDelete=true;
   return TRUE;   
}
//***********************************************************************************************************************
void CGPSThread::GetMessage(CString Msg)
{
	///////////////////////////////////////////////////
	//������ �-��� - ��������� ��������� �� �������  //
	//� ������������ ���!                            //
	///////////////////////////////////////////////////

   // Msg: @#<ID>#<Lo>#<De>#<Height>#<Time>;
   unsigned int i;
   CString buf;
   THardware *Hard;
   TGPSPoint AddPosition;
    //��������� ������ � ���������
   while(Msg.GetLength()!=0)
   {
     Msg.Delete(0,2);           //<ID>#<Lo>#<De>#<Height>#<Time>;
     //��������� IMEI(ID) ����������:
     buf=Msg.SpanExcluding("#");
     //���� ����� ���������� � ������ HardwareList
	 if((Hard=GPS->GetHrdwareElem(buf))==NULL) return;
     Msg.Delete(0,buf.GetLength()+1);

     //��������� Lo:
     buf=Msg.SpanExcluding("#");
     //���� ����� ���������� � ������ HardwareList
     AddPosition.Longitude=atof(buf);
     Msg.Delete(0,buf.GetLength()+1);

     //��������� De:
     buf=Msg.SpanExcluding("#");
     //���� ����� ���������� � ������ HardwareList
     AddPosition.Description=atof(buf);
     Msg.Delete(0,buf.GetLength()+1);

     //��������� De:
     buf=Msg.SpanExcluding("#");
     //���� ����� ���������� � ������ HardwareList
     AddPosition.Height=atof(buf);
     Msg.Delete(0,buf.GetLength()+1);

     //��������� time:
	 buf=Msg.SpanExcluding(";");
     //���� ����� ���������� � ������ HardwareList
     AddPosition.DateTime=buf;
     Msg.Delete(0,buf.GetLength()+1);

      if(Hard->runtime==false)
		 Hard->PositionFromBD.push_back(AddPosition);
  
   }
   if(Hard->runtime==true)
   {
	     Hard->PositionFromBD.clear();
		 Hard->PositionFromBD.push_back(AddPosition);
      for(i=0;i<Hard->WindowsList.size();i++)
      {
	    if(FrameContainer->GetFramePtr(Hard->WindowsList[i])!=NULL)
	       FrameContainer->GetFramePtr(Hard->WindowsList[i])->DrawHards();
      }
   }
   //������� �� ��� �����
    HardToolFrame->UpdateCanvas();
}

//************************************************************************************************************************
int CGPSThread::Run()
{
  // ��������� ����������� ���� ������ ���������
   // ������ ���, ����� �� ���� ������ �� �������� ������

while(1)
{
  if(Terminated==true) 
		return WM_QUIT;

    for (int i=0; i<SIZE; i++)
      Buffer[i] = '\0';
    if(WinSocket==NULL)
	{
		return WM_QUIT;
	}
    // �������� ������

    Recv = recv(*WinSocket, Buffer, SIZE, 0);
	// ���� ����� ��������
    if (Recv == SOCKET_ERROR)
    {
		if(GPS->IsConnected()==true)
	     MessageBox(MainForm->m_hWnd,"������ ����������!","",0);
	  MainForm->Menu.GPSConnect=false;
	  GPS->StopGPS();
	  return WM_QUIT;
    }
	else
	if(Buffer[0]=='@')//������ ��������� ���������
	{
		GetMessage(Buffer);
	}
}
	return WM_QUIT;
}
//==========================================================================================================================
void CGPSThread::Terminate()
{
  Terminated=true;

}
//==========================================================================================================================
int CGPSThread::ExitInstance()
{
  return CWinThread::ExitInstance();
}
