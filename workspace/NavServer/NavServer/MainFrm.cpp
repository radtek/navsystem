// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "NavServerApp.h"
#include "MainFrm.h"
#include "ListBoxOutputStream.h"
//#include "ServerWork.h"
#include <atlimage.h>

#include "afxwin.h "
#include "afx.h "
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_32774, &CMainFrame::OnMenuBaseView)
	ON_COMMAND(ID_APP_ABOUT, &CMainFrame::OnAppAbout)
	ON_COMMAND(ID_VIEW_STATUS_BAR, &CMainFrame::OnViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, &CMainFrame::OnUpdateViewList)
	ON_COMMAND(ID_32775, &CMainFrame::OnBDClear)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_COMMAND(ID_32772, &CMainFrame::OnMenuExit)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, &CMainFrame::OnUpdateAppExit)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};



CMainFrame::CMainFrame()
{
	DBaseDlg=new CDBaseDlg();
	Menu.ListView=true;
	IsTray=false;
	
	Menu.Started=false;
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
//	delete Server;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nItem=0;
	CRect r;
	
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetWindowRect(r);
	
	r.right=r.Width();
	r.bottom=r.Height();
	r.left=0;
	r.top=0;
	ListBox=new CListBox();
	ListBox->Create(WS_CHILD|WS_BORDER|WS_VISIBLE|WS_HSCROLL,r,this,55);
	theApp.Stream(new CListBoxOutputStream(ListBox));

	//**//
	//связываемся с БД
/*
   TRY_ADO()
      if (theApp.m_connection.IsCreated () && theApp.m_connection.IsOpen ())
         theApp.m_connection.Close ();
      CFileDialog dlg (TRUE, _T("mdb"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
            _T("Files (*.mdb)|*.mdb|All Files (*.*)|*.*||"), this);
	  
  // SetCurrentDirectoryA("C:\\");
   char ch[255];
   GetCurrentDirectoryA(sizeof(ch),ch);
   CString s="";
   //s=ch;
   s+="History.mdb";
   theApp.m_connection.SetMSAccessConnectionParam (4, 0,s,"","");
      theApp.m_connection.Open ();
	  
	  
     // DBaseDlg->ReloadList();
   CATCH_ADO()
*/
	//**//

	OnAppExit();
 	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.style=WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU|WS_MAXIMIZEBOX;
	//cs.dwExStyle=WS_EX_TOOLWINDOW ;
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
   return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
#endif //_DEBUG


// CMainFrame message handlers
void CMainFrame::OnClose()
{
	DBaseDlg->DestroyWindow();
	theApp.stopServerThread();
	
	/*TRY_ADO()
      if (theApp.m_connection.IsOpen ())
         theApp.m_connection.Close ();
   CATCH_ADO()
   TRY_ADO()
      if (theApp.m_connection.IsCreated ())
         theApp.m_connection.Destroy ();
   CATCH_ADO()	  

   if(pThread!=NULL)
   {
       pThread->Terminate();
	   WaitForSingleObject(*pThread,3000);
   }*/

	CFrameWnd::OnClose();

}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); 
}



void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
  
	// TODO: Add your message handler code here
}

void CMainFrame::OnMenuBaseView()
{
	DBaseDlg->DoModal();
}

void CMainFrame::OnAppAbout()
{
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
}

void CMainFrame::OnViewList()
{
	Menu.ListView=!Menu.ListView;
	if(Menu.ListView==true)
	{
		ListBox->ShowWindow(SW_SHOW);
	}
	else
	{
		ListBox->ShowWindow(SW_HIDE);
	}
}

void CMainFrame::OnUpdateViewList(CCmdUI *pCmdUI)
{
	
	if(Menu.ListView==true)
      pCmdUI->SetCheck(1);
	else
	  pCmdUI->SetCheck(0);
}

void CMainFrame::OnBDClear()
{
	
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
/*
	NOTIFYICONDATA nid;
	memset(&nid, 0, sizeof(nid)); nid.cbSize = sizeof(nid); 
	HICON icon;
	CImage g;
	
	icon=LoadIcon(NULL,(LPCSTR)IDI_ICON1);
	nid.hWnd = m_hWnd;
	nid.uID = 1234; 
	nid.uCallbackMessage = WM_APP+1234;
	nid.hIcon =icon;  
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;

	if(IsIconic()==true)
	{
    Shell_NotifyIcon(NIM_ADD, &nid);
    ShowWindow(SW_HIDE);
	IsTray=true;
	}
	if(IsZoomed()==true)
	{
	 NOTIFYICONDATA nid; memset(&nid, 0, sizeof(nid));
	 nid.cbSize = sizeof(nid);  
	 nid.hWnd = this->m_hWnd; 
	 nid.uID = 1234;    // удаляемс    BOOL ok = Shell_NotifyIcon(NIM_DELETE, &nid);
	 ShowWindow(SW_SHOW);
	 IsTray=false;
	}*/
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);

	if(nStatus==SW_MINIMIZE)
	{
		int r;
		r=44;
	}
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*if(IsTray==true)
	{
	 NOTIFYICONDATA nid; memset(&nid, 0, sizeof(nid));
	 nid.cbSize = sizeof(nid);  
	 nid.hWnd = this->m_hWnd; 
	 nid.uID = 1234;    // удаляемс    BOOL ok = Shell_NotifyIcon(NIM_DELETE, &nid);
	ShowWindow(SW_SHOW);
	IsTray=false;
	}
	else
	{

	}*/
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CFrameWnd::OnMButtonDown(nFlags, point);
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return CFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	

	CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void CMainFrame::OnAppExit()
{
 if(Menu.Started==false)
 {
	 theApp.startServerThread();

   Menu.Started=true;
 }
 else
 {
   if(theApp.isStartedServerThread())
   {
	   theApp.stopServerThread();      
	   ListBox->AddString("Сервер был остановлен.");
   }
   Menu.Started=false;
 }
}

void CMainFrame::OnMenuExit()
{
	OnClose();
}

void CMainFrame::OnUpdateAppExit(CCmdUI *pCmdUI)
{
  if(Menu.Started==false)
	  pCmdUI->SetText("Запустить сервер");
  else
	   pCmdUI->SetText("Остановка сервера");
}
