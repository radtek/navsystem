// �OpenResDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3DEditor.h"
#include "OpenResDlg.h"

#include "MapFrame.h"
#include "WorldMapFrame.h"

#include "Memory.h"
#include "CompLib.h"
// �OpenResDlg dialog

IMPLEMENT_DYNAMIC(�OpenResDlg, CDialog)

�OpenResDlg::�OpenResDlg(CWnd* pParent /*=NULL*/)
	: CDialog(�OpenResDlg::IDD, pParent)
{
WayBlock="";
WayRastr="";
}

�OpenResDlg::~�OpenResDlg()
{
}

void �OpenResDlg::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_radioBlock);
	DDX_Control(pDX, IDC_RADIO2, m_radioRastr);
	DDX_Control(pDX, IDC_EDIT1, m_Way);

	
	if(m_radioBlock.GetCheck()==0&&m_radioRastr.GetCheck()==0)
		m_radioRastr.SetCheck(1);

}


BEGIN_MESSAGE_MAP(�OpenResDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &�OpenResDlg::OnBnSelectPuth)
	ON_BN_CLICKED(1, &�OpenResDlg::OnBnClicked1)
	ON_BN_CLICKED(IDC_RADIO1, &�OpenResDlg::OnBnClickedRadioBlock)
	ON_BN_CLICKED(IDC_RADIO2, &�OpenResDlg::OnBnClickedRadioRastr)
END_MESSAGE_MAP()


// �OpenResDlg message handlers


void �OpenResDlg::OnBnSelectPuth()
{
 if(m_radioRastr.GetCheck()==1)
 {
	 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"�����������|*.bmp||");
	 if(File.DoModal()==IDOK)
     {
		 WayRastr= File.GetPathName();
		 m_Way.SetWindowTextA(WayRastr);
	}
 }
 else
 if(m_radioBlock.GetCheck()==1)
 {
	 CDirDialog DirDialog;
	 if(DirDialog.DoModal(this->m_hWnd)==true)
		 WayBlock=DirDialog.GetPath();
	  m_Way.SetWindowTextA(WayBlock);
 }
 
}

void �OpenResDlg::OnBnClicked1()
{
 if(m_radioRastr.GetCheck()==1)
 {
	 if(WayRastr=="")
	 {
	    MessageBox("����������,�������� ������ ��� ��� �������� ��� ������� '������'","��������������!",0);
		return;
	 }
	 if(IsFileExists(WayRastr)==false)
	 {
	    MessageBox("��������� ���� �� ����������.����������, �������� ������������ ����������� ���� ��� ������� '������'","��������������!",0);
		return;
	 }
	 if(IsUsingFile(WayRastr)==true)
	 {
	    MessageBox("��������� ���� ��� ������� ��� ������������ ������ ����������. ����������, �������� ������ ����������� ����","��������������!",0);
		return;
	 }
	 //TRY_RASTER()
	 CMapFrame *pMapFrame=new CMapFrame(WayRastr);
	   if(pMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN,
					   CRect(0,0,800,700),MainForm,NULL)==TRUE)
	   pMapFrame->ShowWindow(SW_SHOW);

 }
 else
 if(m_radioBlock.GetCheck()==1)
 {
	 WayBlock=GetStrFromEdit(&m_Way);//~~~!!!!

	 if(WayBlock=="")
	 {
		 MessageBox("����������,�������� ������ ��� ��� �������� ��� ������� '������'","��������������!",MB_ICONWARNING);
		return;
	 }
	 CWorldMapFrame *pWorldMapFrame=new CWorldMapFrame(WayBlock+"\\");

	  pWorldMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN ,
		              CRect(0,0,260*3,260*3),MainForm,NULL);
	  pWorldMapFrame->ShowWindow(SW_SHOW);

 }
 OnOK();
}

void �OpenResDlg::OnBnClickedRadioBlock()
{
	 m_Way.SetWindowTextA(WayBlock);
	
}

void �OpenResDlg::OnBnClickedRadioRastr()
{
 m_Way.SetWindowTextA(WayRastr);
}
