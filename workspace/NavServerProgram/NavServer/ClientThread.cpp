#include "StdAfx.h"
#include "ClientThread.h"
#include <vector>
#include <winsock2.h>
#include "NavServer.h"

using std::vector;
const int CServerUsersThread::SIZE=2048;
const int MAXELEM=2000;
struct TRunTimeUsers
{
   CString IMEI;        
   vector<int> users; //������ ������, ������� ���� ��������� ���. ������ �� ID
};


vector<TRunTimeUsers> RunTimeUsers;//RTU


CServerUsersThread::CServerUsersThread(CListBox *ListBox,User *user,int UserIndex)
{
	this->ListBox=ListBox;
	this->user=user;
	m_bAutoDelete=true;
	this->UserIndex=UserIndex;
	Terminated=false;

	IP=inet_ntoa(user->AcpStruct.sin_addr);
	port=user->AcpStruct.sin_port;
}

CServerUsersThread::~CServerUsersThread(void)
{
	int d;
	d=33;
}
//==========================================================================================================
void CServerUsersThread::Terminate()
{
   Terminated=true;
}
//==========================================================================================================
bool CServerUsersThread::SendGPSPoint(int *SOCKET,TGPSPoint GPSPoint)
{

 if(SOCKET!=NULL&&*SOCKET!=NULL)
 {
	 CString SendStr;//@#<ID>#<Lo>#<De>#<Height>#<Time>;
	 SendStr="@#"+GPSPoint.IMEI+"#"+GPSPoint.Longitude+"#"+GPSPoint.Description+"#"+
		     GPSPoint.Height+"#"+GPSPoint.DateTime+";";
	 if(send(*SOCKET,(LPCSTR)SendStr,SendStr.GetLength(),0)==S_OK){ return false;}
	 return true;

 }
// terminate();
 return false;
}
//==========================================================================================================
void CServerUsersThread::LoadDataFromDB(int *Accept,TEditorProtocol EditorProtocol)
{
   	  CString sqlStr;
      int nItem = 0;     
	  TGPSPoint SendInfo;
	  
	TRY_ADO()
       
      CADORecordset rs;
      rs.SetConnection (& theApp.m_connection);

	  sqlStr="select num_rec,[Hardware],[HardCaption], [Longitude], [Description],[Height],[Date] from DATA";
	  sqlStr+=" WHERE Hardware = '"+EditorProtocol.IMEI+"' ";
	 
	  rs.SetSQL((LPCSTR)sqlStr);
      rs.SetOpenMode (true);
      rs.Open ();
	  rs.First();
      
      try
         {

            if (!rs.IsEmpty ())
            for (rs.First () ; !rs.IsEoF () ; rs.Next ())
            {
				
			  SendInfo.IMEI       =(const char*)_bstr_t(rs.GetField("Hardware"));
			  SendInfo.Description=(const char*)_bstr_t(rs.GetField("Description"));
			  SendInfo.Longitude  =(const char*)_bstr_t(rs.GetField("Longitude"));
			  SendInfo.Height     =(const char*)_bstr_t(rs.GetField("Height"));
			  SendInfo.DateTime   =(const char*)_bstr_t(rs.GetField("Date"));
              
              
			  if(SendGPSPoint(Accept,SendInfo)==false) break;
			  nItem++;
			  if(Terminated==true) break;
            }   
         }
      catch (CADOException&)
         {
         try
            {
            rs.Cancel ();
            }
         catch (...)
            {
            }
         throw;
         }
	  rs.Close();
     CATCH_ADO()
	

 /////////
}
//============================================================================================================================
void CServerUsersThread::AddToMass(CString ID,int indexUser)
{
   unsigned int i,j;
  

   for(i=0;i<RunTimeUsers.size();i++)
   {
	   if(RunTimeUsers[i].IMEI==ID)
	   {
		   for(j=0;j<RunTimeUsers[i].users.size();j++)
			   if(RunTimeUsers[i].users[j]==indexUser)// ���������, ����� ����� ������ ��� �������� �� ����� �������
				   return;
		   RunTimeUsers[i].users.push_back(indexUser);
		   return;
	   }
   }
  TRunTimeUsers add;
   add.IMEI=ID;
   add.users.push_back(indexUser);
   RunTimeUsers.push_back(add);

}
//============================================================================================================================
void CServerUsersThread::DelteFromMass(CString ID,int indexUser)
{
   unsigned int i,j;

   for(i=0;i<RunTimeUsers.size();i++)
   {
	   if(RunTimeUsers[i].IMEI==ID)
	   {
		   for(j=0;j<RunTimeUsers[i].users.size();j++)
		   {
			   if(RunTimeUsers[i].users[j]==indexUser)
			   {
				   RunTimeUsers[i].users.erase(RunTimeUsers[i].users.begin()+j);
				   return;
			   }
		   }
	   }
   }
}
//============================================================================================================================
void CServerUsersThread::EditorMessage(CString protocol)
{
   TEditorProtocol Prl;
   CString buf;
   
   while(protocol.GetLength()!=0) //� ����� ��������� ����� ���� ��������� ��������(�������� ";")
   {
    buf=protocol.SpanExcluding(";");
	  	//��������� ID
	protocol.Delete(0,2);                    //<ID>#<t1>#<t2>#0;
	buf=protocol.SpanExcluding("#");
	Prl.IMEI=buf;
	protocol.Delete(0,buf.GetLength()+1);      //<t1>#<t2>#0;
	//��������� time1
	buf=protocol.SpanExcluding("#");
	Prl.DTime1=buf;
	protocol.Delete(0,buf.GetLength()+1);      //#<t2>#0;
	//��������� time2
	buf=protocol.SpanExcluding("#");
	Prl.DTime2=buf;
	protocol.Delete(0,buf.GetLength()+1);      //#0;
    //��������� ����. �����-�������������
	buf=protocol.SpanExcluding(";");
	Prl.type=atoi(buf);
	if(Prl.DTime1=="."||Prl.DTime2==".")
		Prl.RunTime=true;
	else
		Prl.RunTime=false;

	if(Prl.type==1)  //���� ������ �� ��������� �������� �� ������� ����������
	{
		DelteFromMass(Prl.IMEI,UserIndex);
	}
	else
	{
		if(Prl.RunTime==1)         // ���� � �������� �������
		{
			AddToMass(Prl.IMEI,UserIndex);
		}
		else                           // �������� ������ � ��
		{
			//LoadDataFromDB(&(user->Accept),Prl);
		}
	}
	protocol.Delete(0,protocol.SpanExcluding(";").GetLength()+1);
   }
}
//============================================================================================================================
void CServerUsersThread::MobileMessage(CString protocol)
{
	//@#<ID>#<Lo>#<De>#<Height>#;
   int i;
   CTime time;
   TGPSPoint Info;
   CString buf;
   CString TimeNow;
   time=CTime::GetCurrentTime();
   TimeNow.Format("%d.%d.%d %d:%d:%d",time.GetDay(),time.GetMonth(),time.GetYear(),
	                                  time.GetHour(),time.GetMinute(),time.GetSecond());
   i=0;
   while(protocol.GetLength()!=0&&i<protocol.GetLength()) //� ����� ��������� ����� ���� ��������� ��������(�������� ";")
   {
	   i++;
//��������� ������ � ���������
	  
    buf=protocol.SpanExcluding(";");
	protocol.Delete(0,2);                   //<ID>#<Lo>#<De>#<Height>#;

	//��������� ID
	buf=protocol.SpanExcluding("#");
	Info.IMEI=buf;
	protocol.Delete(0,buf.GetLength()+1);  //<Lo>#<De>#<Height>#;

	//��������� Lo
	buf=protocol.SpanExcluding("#");
	Info.Longitude=buf;
	protocol.Delete(0,buf.GetLength()+1);  //<De>#<Height>#;

	//��������� De
	buf=protocol.SpanExcluding("#");
	Info.Description=buf;
	protocol.Delete(0,buf.GetLength()+1);  //<Height>#;

	//��������� Height
	buf=protocol.SpanExcluding(";");
	Info.Height=buf;
	protocol.Delete(0,buf.GetLength()+1);  //<Height>#;
    
	Info.DateTime=TimeNow;
  protocol.Delete(0,protocol.SpanExcluding(";").GetLength()+1);


//���������� ���������� ���� �������������, ������� � ������� � ����� ����������
  CString Message;
  int ind;
  unsigned int i,j;

  Message.Format("@#%s#%s#%s#%s#%s;",Info.IMEI,Info.Longitude,Info.Description,Info.Height,Info.DateTime);
  for(i=0;i<RunTimeUsers.size();i++)
  {
	 if(RunTimeUsers[i].IMEI==Info.IMEI)//���� ���� ����������
	 {
		 for(j=0;j<RunTimeUsers[i].users.size();j++)
		 {
           ind=RunTimeUsers[i].users[j];
		   send(users[ind].Accept,(LPCSTR)Message,Message.GetLength(),0);
		 }
	 }
  }
  //������� ������ � ��
  //writeDB(Info);
  // CDBWork::writeDB(Info);
  
}	
}
//============================================================================================================================
int CServerUsersThread::Run()
{
  char Buffer[20000]; // ����� �������� ������
  CString f;
 while (true)                                  // ��������� ����������� ���� ������ ���������
 {
	 for (int i=0; i<SIZE; i++)                // ������ ���, ����� �� ���� ������ �� �������� ������
      Buffer[i] = '\0';
    Recv = recv(user->Accept,Buffer, SIZE, 0);  // �������� ������
    f=CString(Buffer);
	if(Terminated==true){Stop(); break;}
 	if (Recv == SOCKET_ERROR||Recv == 0)
	  {
		  CString str;
	         str.Format("������ ����������.  IP: %s ����: %d",IP,port);
				   ListBox->AddString((LPCSTR) str);
		  Stop();
		  PostQuitMessage(WM_QUIT);
		  break;
	  }
 	else
	if(f!="")
	{
	  if(f[0]=='$')                              //������ Navagation GIS
         EditorMessage(f);
	  else
	  if(f[0]=='@')                              //������ GPS(�������)
		  MobileMessage(f);
 	  //f.Insert(0,">>  ");
	  //ListBox->AddString(f);
   	}
}
return WM_QUIT;
}
//============================================================================================================================
BOOL  CServerUsersThread::InitInstance()
{
	SetThreadPriority(THREAD_PRIORITY_LOWEST);
	m_bAutoDelete=true;

	/*
      rs.SetConnection (&theApp.m_connection);//�������� ��������� ������� CADOConnection
      //sql-������, ������ ������� ������ ������ � ������������� �� �� ���� Hardware(���������� ����� ����������)       
	  rs.SetSQL ("select num_rec,[Hardware],[HardCaption], [Longitude], [Description],[Height],[Date] from DATA order by [Hardware]");
      rs.SetOpenMode (true);// ������ ������������ ������
      rs.Open ();           // ��������� ������ � ������
  
*/


   return true;   
}
//============================================================================================================================
void CServerUsersThread::Delete()
{
	unsigned int i,j;
	for(i=0;i<RunTimeUsers.size();i++)
		  {
			  for(j=0;j<RunTimeUsers[i].users.size();j++) 
				  if(RunTimeUsers[i].users[j]==UserIndex)
					  RunTimeUsers[i].users.erase(RunTimeUsers[i].users.begin()+j);
		  }
}
//============================================================================================================================
void CServerUsersThread::Stop()
{
		  
	      user->active = false;
		  Delete();
		  closesocket(user->Accept);
		  user->Accept=NULL;
		  Terminated=true;

		  
}
//======================================================================================================================
void CServerUsersThread::writeDB(TGPSPoint &Add)
{
	if(Add.DateTime==""||Add.Description==""||Add.Height==""||Add.IMEI==""||Add.Longitude=="")
      return;

   TRY_ADO()//������ ��������� ����������
      if (!rs.IsEmpty ())   // ���� �� ������ � ��?
         rs.Last ();        // ���� ��, ��������� � �����
      rs.AddNew ();         // �������� ������, � ���, ��� �� ����� �������� ������
      try
         {
			 //�������� ������
			 rs.SetField ("Hardware", _variant_t(CT2CA((LPCTSTR)Add.IMEI)));
			 rs.SetField ("HardCaption", _variant_t(CT2CA((LPCTSTR)Add.IMEI)));
			 rs.SetField ("Longitude", _variant_t(CT2CA((LPCTSTR)Add.Longitude)));
			 rs.SetField ("Description", _variant_t(CT2CA((LPCTSTR)Add.Description)));
			 rs.SetField ("Height", _variant_t(CT2CA((LPCTSTR)Add.Height)));
			 rs.SetField ("Date", _variant_t(CT2CA((LPCSTR)Add.DateTime)));
           rs.Update ();    //��������� ���������
         }
      catch (CADOException&)
         {
		 //� ������ ������ �������� ���������
         try
            {
            rs.Cancel ();
            }
         catch (...)
            {
            }
         throw;
         }

  CATCH_ADO()
}
//======================================================================================================================
int CServerUsersThread::ExitInstance()
{
	  //rs.Close();//��������� ������� ����������

	return CWinThread::ExitInstance();
}
