#include "StdAfx.h"
#include "InetRaster.h"

#include "afxwin.h "
#include "3DEditor.h"

�InetRaster::�InetRaster()
{
	
	ServerUrl="http://kh.google.com/kh?v=3&t=";
	FolderCache=RES_PATH+"cache\\";
}

�InetRaster::~�InetRaster(void)
{

}
//==========================================================================================================================
void �InetRaster::Connect()
{


}
//==========================================================================================================================
BOOL �InetRaster::InitInstance()
{
	SetThreadPriority(THREAD_PRIORITY_LOWEST); 

    return true;
}
//==========================================================================================================================
int �InetRaster::Run()
{
	  srand(static_cast<unsigned int>(time(0)));
	unsigned int i=0;
	while(1)
	{
		
      if(*Terminated==true)
		  break;
/*	  int count=*LoadedCount;
      
	  if(*LoadedCount>4000)
	  {
            int s;
			s=33;
	  }
	  for(i=0;i<count;i++)
	  {
          if(*Terminated==true)
		  break;
            if(*LoadedCount==0)
				break;
			Sleep(400+rand()*1400/RAND_MAX);
			//Sleep(1000);
		  if(LoadedContainer->size()>0)
		  if(LoadFileFromInet(LoadedContainer->at(count-i-1).FName)==0)
		  { 
            // ���� �������� ����� ������ �������, ������� �� �����
			  if((count-i-1>=0)&&(count-i-1<5000)&&(LoadedContainer->size()>0))
        	      Draw(LoadedContainer->at(count-i-1));
			  
			  if((count-i-1>=0)&&(count-i-1<5000)&&(LoadedContainer->size()>0))
			  {
				  if(*LoadedCount==0)
					  break;
			      LoadedContainer->erase(LoadedContainer->begin()+count-i-1);
				  LoadedContainer->resize(5000);
			  }
			  else
			     break;
			 if(*LoadedCount==0)
				 break;
		     (*LoadedCount)--;//!!!
		     count--;
		  }
		 
	  }*/
	}
	return WM_QUIT;
}
void �InetRaster::Create(CBlockRaster *BlockRaster,bool *TerminatedThread,vector<TLoadedFiles>* LoadedContainer,
						 int *LoadedCount,CWnd *pFrame,int UnicWindIndex,CMutex *Mutex)
{
	this->BlockRaster=BlockRaster;
	this->Terminated=TerminatedThread;
	this->LoadedContainer=LoadedContainer;
	this->LoadedCount=LoadedCount;
	this->pFrame=pFrame;
	this->UnicWindIndex=UnicWindIndex;
	this->InetMutex=Mutex;
	LoadedContainer->resize(5000);
}
//==========================================================================================================================
int �InetRaster::LoadFileFromInet(CString FNameWithoutExp)
{
CString m_mes; // ���������� � ������� ����� �������� ���������
char temp[100]; // ������������� ���������� ��� �������� 
// ������ �� Int � char
CString m_path=FolderCache+FNameWithoutExp+".jpg"; // ��� ����� ��� ������
char strBody[1024]; // ����� �� 1024 ���� 
CString m_url=ServerUrl+FNameWithoutExp;


// ������ ���������� session � ��������� ������ ANDY
CInternetSession *session=new CInternetSession(_T( "ANDY" ), PRE_CONFIG_INTERNET_ACCESS );

// ������ ���������� pServer ������ CHttpConnection
CHttpConnection* pServer = NULL;

// ������ ���������� pFile ������ CHttpFile
CHttpFile* pFile = NULL;

try
{
CString strServerName; // ��� �������
CString strObject; // ��� ������� 
INTERNET_PORT nPort; // ����� ����� ��� �����
DWORD dwServiceType; // ��� �������

// ������� AfxParseURL �������� ������ � ���������� URL ( � ��� m_url ) �� �������,
// �������, ���� ������� � ����� 

if ( AfxParseURL( m_url, dwServiceType, strServerName, strObject, nPort ) == 0 )
{
return -1; // ����� �� ������� OnButtonConnect() 
}
// ����� ������ � �������
/*
m_mes = "";
m_mes += "Server Name = "; 
m_mes += (CString)strServerName; m_mes += "rn";
m_mes += "Object Name = ";
m_mes += (CString)strObject; m_mes += "rn";
m_mes += "Port = ";
itoa( nPort, temp, 10 );
m_mes += (CString)&temp[0]; m_mes += "rn";
*/

// ������������� ����������� �� HTTP ����������. 
pServer = session->GetHttpConnection( strServerName, nPort );

// �������� ������ �� ������� ( strObject )
pFile = pServer->OpenRequest(
CHttpConnection::HTTP_VERB_GET, strObject, NULL, 1, NULL, NULL,
INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT
);

// ��������� ��������� � HTTP ������� 
pFile->AddRequestHeaders( _T( "Accept: */*rnUser-Agent: ANDYrn" ) );

// �������� ������
pFile->SendRequest( );

DWORD dwRet; // ���������� ��� �������� ���� ��������� 
pFile->QueryInfoStatusCode( dwRet ); // ���������� ��� ��������� � dwRet

// ����� ������
m_mes += "The HTTP GET returned a status code of ";
itoa( dwRet, temp, 10 ); 
m_mes += (CString)&temp[0]; m_mes += "rn"; 

CString strHeader; // ���������� ��� �������� ����������� ���������� �������
pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, strHeader); // ���������� ��������� � strHeader

// ����� ������
m_mes += "Header = ";
m_mes += strHeader; 
//UpdateData( FALSE );

// ���� ��� ��������� �� ����� 200, �� ������� �� �������
if( dwRet != 200 ) { m_mes += "Program terminate!";return -1; }
// ----------------------------------------------------------

// �������� ������ ����� ��� ������ 
/*
m_mes += "Starting download the file."; m_mes += "rn";

if( m_path == "" ) 
{ 
m_mes += "Error! No file to save. Choese the file.";
m_mes += "rn"; UpdateData( FALSE ); return 1; }
else 
{
m_mes += "File name to save : ";
m_mes += m_path; m_mes += "rn"; UpdateData( FALSE ); 
}
*/
CFile file2; // ��������� ���������� file2 ������ CFile

// ��������� ���� ��� ������ � �������� ������� ( CFile::typeBinary ) !!!
file2.Open((LPCTSTR)m_path,
CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);

int allRead = 0; // ���������� ��� �������� ������ ����� ��������� ����
int nRead = pFile->Read( strBody, 1024 ); // ��������� ������ 1024 ����� � �����.
// ���������� nRead ������ ����������
// ��������� ���� 

allRead += nRead; // ��������� ����� ����� ��������� ����

// ����� ������
m_mes += "Loading ";
itoa( nRead, temp, 10 );
m_mes += (CString)&temp[0]; m_mes += " bytes"; m_mes += "rn";
//UpdateData( FALSE );

// ���������� ����� �� nRead ���� � ����
file2.Write( strBody, nRead ); 

// ���� ����������, ���� nRead �� ����� ��������� ����
while ( nRead > 0 )
{
nRead = pFile->Read( strBody, 1024 );

if( nRead != 0 ) 
{
m_mes += "Loading ";
itoa( nRead, temp, 10 );
m_mes += (CString)&temp[0]; m_mes += " bytes"; m_mes += "rn";

file2.Write( strBody, nRead );
allRead += nRead;

}

}
// ����� ������
m_mes += "rn";
m_mes += "Total bytes = ";
itoa( allRead, temp, 10 );
m_mes += &temp[0]; m_mes += "rn";
//UpdateData( FALSE );
file2.Close(); // ��������� ����
pFile->Close(); // ��������� Internet ����
pServer->Close(); // ��������� ������
m_mes += "Download is complete !!!"; m_mes += "rn";
//UpdateData( FALSE );
}
catch ( CInternetException* pEx )
{
// ���� ��������� ������ � WinInet

// ����� ������
char szErr[1024];
pEx->GetErrorMessage( szErr, 1024 );
m_mes += "Error: ( ";
itoa( int(pEx->m_dwError), temp ,10 );
m_mes += (CString)&temp[0];
m_mes += " ) ";
m_mes += (CString)&szErr[0]; m_mes += "rn";

pEx->Delete( ); // �������� ���������� ������ CInternetException 
DeleteFile(m_path);//!!!!!!!!!!!!!!
if ( pFile != NULL )
delete pFile; // ��������� Internet ����
if ( pServer != NULL )
delete pServer; // ��������� ������
session->Close( ); // ��������� ������
return -1;
}

if ( pFile != NULL )
delete pFile; // ��������� Internet ����
if ( pServer != NULL )
delete pServer; // ��������� ������
session->Close( ); // ��������� ������

return 0;
}
//==========================================================================================================================
void �InetRaster::Draw(TLoadedFiles LoadedFile)
{
   
 /*  CPoint LeftTop=BlockRaster->GetLeftTopBlock();
   CPoint DrawRect=BlockRaster->GetColOfBlocks();*/
 //  BlockRaster->AddImage(LoadedFile);
 /*  BlockRaster->PushMatrix();
	if(pFrame->m_hWnd!=NULL)
		FrameContainer->GetFramePtr(UnicWindIndex)->Repaint();*/
}
//==========================================================================================================================