// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "3DEditor.h"
#include "MainFrm.h"
#include "GLFrame.h"
#include "MapFrame.h"
#include "WorldMapFrame.h"
#include "FrameContainer.h"
#include  <winuser.h>
#include "DlgPrivAdd.h"
#include "DlgPrivList.h"
#include "memory.h"   //temp
#include "DlgGlRegistry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
CMainFrame* MainForm;	

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
    ON_WM_MOVE()
    ON_WM_MOVING()
    ON_WM_MOUSEMOVE()
    ON_WM_KEYUP()
	ON_COMMAND(ID_MenuNew, &CMainFrame::OnMenunew)
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnMenuExit)
	ON_WM_CHILDACTIVATE()
	ON_COMMAND(ID_GPS_CONNECT, &CMainFrame::OnGpsConnect)
	ON_UPDATE_COMMAND_UI(ID_GPS_CONNECT, &CMainFrame::OnUpdateGpsConnect)
	ON_COMMAND(ID_GPS_32782, &CMainFrame::OnGPSAdd)
	ON_UPDATE_COMMAND_UI(ID_GPS_32782, &CMainFrame::OnUpdateGpsAdd)
	ON_COMMAND(ID_GPS_32784, &CMainFrame::OnGpsDelete)
	ON_UPDATE_COMMAND_UI(ID_GPS_32784, &CMainFrame::OnUpdateGpsDel)
	ON_COMMAND(ID_GPS_32780, &CMainFrame::OnGpsSettings)
	ON_COMMAND(ID_32787, &CMainFrame::OnDocView)
	ON_UPDATE_COMMAND_UI(ID_32787, &CMainFrame::OnUpdateDocView)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_32788, &CMainFrame::OnGpsList)
	ON_COMMAND(ID_32789, &CMainFrame::OnHardView)
	ON_UPDATE_COMMAND_UI(ID_32789, &CMainFrame::OnUpdateHardView)
	ON_COMMAND(ID_32793, &CMainFrame::OnMenuOpenRes)
	ON_COMMAND(ID_32791, &CMainFrame::OnMenuOpenProject)
	ON_COMMAND(ID_32796, &CMainFrame::OnMenuRastrCurMove)
	ON_COMMAND(ID_32797, &CMainFrame::OnMenuRastrCurPriv)
	ON_UPDATE_COMMAND_UI(ID_32797, &CMainFrame::OnUpdateMenuRastrCurPriv)
	ON_UPDATE_COMMAND_UI(ID_32796, &CMainFrame::OnUpdateMenuRastrCurMove)
	ON_COMMAND(ID_32778, &CMainFrame::OnMenuLink)
	ON_COMMAND(ID_32794, &CMainFrame::OnMenuSave)
	ON_COMMAND(ID_3D32801, &CMainFrame::OnGlGrid)
	ON_UPDATE_COMMAND_UI(ID_3D32801, &CMainFrame::OnUpdateGlGrid)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_32802, &CMainFrame::OnMenu3DNew)
	ON_COMMAND(ID_3D32810, &CMainFrame::OnMenuGlReg)
	ON_COMMAND(ID_32811, &CMainFrame::OnMenu3DMapTool)
	ON_UPDATE_COMMAND_UI(ID_32811, &CMainFrame::OnMenu3DToolMap)
	ON_WM_CLOSE()
	ON_COMMAND(ID_32813, &CMainFrame::OnMenuLoadLandHgt)
	ON_COMMAND(ID_32814, &CMainFrame::OnMenuGlLoadRaw)
	ON_COMMAND(ID_3D32815, &CMainFrame::OnMenuGlTexLand)
	ON_COMMAND(ID_32816, &CMainFrame::OnMenuMiniMap)
	ON_UPDATE_COMMAND_UI(ID_32816, &CMainFrame::OnUpdateMinMap)
END_MESSAGE_MAP()

static UINT IndicatorIDs [] =
{
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
    ID_SEPARATOR,
};
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	Menu.GPSConnect=false;
	Menu.GPSAddEnable=false;
	Menu.DocumentView=false;
	Menu.HardView=false;
	Menu.RaterCur=0;
	Menu.GlGrid=false;
	Menu.Tool3D=false;
	GPSDlgList=new CGPSDlgList;

	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{


}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//void (*LPSEARCHFUNC)(LPCTSTR lpszFileName);
/*BOOL SearchFiles(
        LPCTSTR lpszFileName,                // Äèðåêòîðèÿ è ìàñêà ôàéëîâ äëÿ ïîèñêà
        LPSEARCHFUNC lpSearchFunc,            // Ôóíêöèÿ, âûçûâàåìàÿ äëÿ âñåõ íàéäåííûõ ôàéëîâ.
        BOOL bInnerFolders /* = TRUE *///)    // TRUE - ïîèñê â ïîäïàïêàõ.
                                            // FALSE - ïîèñê òîëüêî â çàäàííîé ïàïêå
//typedef void (*LPSEARCHFUNC)(LPCTSTR lpszFileName);

BOOL SearchFiles(LPCTSTR lpszFileName, BOOL bInnerFolders = TRUE)
{
    LPTSTR part;
   char tmp[MAX_PATH]; // âðåìåííûé ìàññèâ
    char name[MAX_PATH];

   HANDLE hSearch = NULL;
   WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

    // ñíà÷àëî ïîèñê âíóòðè âëîæåííûõ ïàïêàõ ...
    if(bInnerFolders)
    {
        if(GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
        strcpy(name, part);
        strcpy(part, "*.*");

        // åñëè ïàïêè ñóùåñòâóþò, òî äåëàåì ïîèñê
        wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
        if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
        do
        {
            // â êàæäîé ïàïêå åñòü äâå ïàïêè ñ èìåíàìè "." è ".."
            // è ýòè ïàïêè ìû íå òðîãàåì

            // ïðîïóñêàåì ïàïêè "." è ".."
            if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))            
           continue;
       
            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // åñëè ìû íàøëè ïàïêó
            {
                char next[MAX_PATH];
                if(GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
                strcpy(part, wfd.cFileName);
                strcat(next, "\\");
                strcat(next, name);

                SearchFiles(next, TRUE);
            }
        }
        while (FindNextFile(hSearch, &wfd)); // èùåì ñëåäóþùèé ôàéë

        FindClose (hSearch); // çàêàí÷èâàåì ïîèñê
    }

   if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE) 
       return TRUE; // â ïðîòèâíîì ñëó÷àå âûõîäèì
   do
   if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // åñëè ìû íàøëè ôàéë
   {
        char file[MAX_PATH];
        if(GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
        strcpy(part, wfd.cFileName);
        CString olds,news;
        olds=file;
		news=GetPuth(file)+"\\new\\t"+GetFileName(file);
		CopyFileA(olds,news,1);
		//AfxMessageBox(file);
        
//        lpSearchFunc(file);
   }
   while (FindNextFile(hSearch, &wfd)); // èùåì ñëåäóþùèé ôàéë
   FindClose (hSearch); // çàêàí÷èâàåì ïîèñê

    return TRUE;
/////////////////////////
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//	SearchFiles("D:\\Kyrsov\\ResFiles\\WorldKharkov\\*.jpg",false);
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

//связываемся с БД
	
 TRY_ADO()
	 CString dbFile = RES_PATH + "models\\3dmodels.mdb";
 //SetCurrentDirectoryA("");
 if (theApp.m_GlConnection.IsCreated () && theApp.m_GlConnection.IsOpen ())
         theApp.m_GlConnection.Close ();
 theApp.m_GlConnection.SetMSAccessConnectionParam(4, 0, (LPCSTR)dbFile, "", "");
      theApp.m_GlConnection.Open ();
 CATCH_ADO()
 
	if(!m_StatusBar.Create(this)||!m_StatusBar.SetIndicators(IndicatorIDs,sizeof(IndicatorIDs)/sizeof(UINT)))
		return -1;
	
GlToolFrame=new CGlToolFrame;
GlToolFrame->Create(NULL,NULL,WS_CHILD|WS_BORDER|WS_MAXIMIZE,CRect(0,0,50,100),this);
   
HardToolFrame=new CHardToolFrame;
HardToolFrame->Create(NULL,"Устройства",WS_CAPTION|WS_CHILD|WS_BORDER|WS_MAXIMIZE ,CRect(0,0,250,520),this);
	   
   
  // OnMenu3DNew();
  // OnMenu3DMapTool();

///временный блок!!!
  /*     CMapFrame *pMapFrame=new CMapFrame("D:\\Kyrsov\\ResFiles\\BMPKharkov\\Kharkov.rsmap");
	   if(pMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN,
		              CRect(0,0,800,700),this,NULL)==TRUE)
	     pMapFrame->ShowWindow(SW_SHOW);*/
///*****         !!!
 /*
CWorldMapFrame *pWorldMapFrame=new CWorldMapFrame(LOAD_PATH+"WorldKharkov\\1World.rsmap");

	  if(pWorldMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN ,
		              CRect(0,0,260*3,260*3),NULL,NULL)==TRUE)
	  pWorldMapFrame->ShowWindow(SW_SHOW);
*/
  return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG



#endif //_DEBUG
// CMainFrame message handlers
void CMainFrame::OnMove(int x, int y)
{
	CMDIFrameWnd::OnMove(x, y);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	CMDIFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMDIFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnMenunew()
{
	
/*	CDlgNewMaster DlgNewMaster("Создаем новый проэкт... Шаг 1.");
	DlgNewMaster.DoModal();*/
   /* CGLFrame *pGlFrame=new CGLFrame;
	pGlFrame=NULL;
	if(pGlFrame==NULL)
	{
	  pGlFrame=new CGLFrame;
	  pGlFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE,
		              CRect(0,0,900,800),this,NULL);
	  pGlFrame->ShowWindow(SW_SHOW);
	  pGlFrame->UpdateWindow();
	    theApp.FrameContainer->AddToContainer(pGlFrame);
	}*/



//	CMapFrame *pMapFrame=new CMapFrame(LOAD_PATH+"1.bmp");
/*	CMapFrame *pMapFrame=new CMapFrame(LOAD_PATH+"kharkov.bmp");
	  pMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN,
		              CRect(0,0,800,700),this,NULL);
	  pMapFrame->ShowWindow(SW_SHOW);

	*/
   
    /*  CWorldMapFrame *pWorldMapFrame=new CWorldMapFrame(LOAD_PATH+"WorldKharkov\\");
	  pWorldMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN ,
		              CRect(0,0,260*3,260*3),NULL,NULL);
	  pWorldMapFrame->ShowWindow(SW_SHOW);*/
	 // theApp.FrameContainer->AddToContainer(pWorldMapFrame);
	//  pFrame->UpdateWindow();
  
}

void CMainFrame::OnMenuExit()
{
}

void CMainFrame::OnChildActivate()
{
	CMDIFrameWnd::OnChildActivate();
	
	// TODO: Add your message handler code here
}

void CMainFrame::OnGpsConnect()
{
	if(GPS->IsConnected()==true)
		GPS->StopGPS();
	else
	if(GPS->IsConnected()==false)
		GPS->StartGPS();
	
}

void CMainFrame::OnUpdateGpsConnect(CCmdUI *pCmdUI)
{

	if(Menu.GPSConnect==true)
	pCmdUI->SetText("Отключиться");
	else
	pCmdUI->SetText("Подключиться");
}


void CMainFrame::OnGPSAdd()
{
	GPSDlgAdd->DoModal();

}

void CMainFrame::OnUpdateGpsAdd(CCmdUI *pCmdUI)
{
	if(Menu.GPSConnect==true)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);

}

void CMainFrame::OnGpsDelete()
{
	GPSDlgDel->DoModal();
}

void CMainFrame::OnUpdateGpsDel(CCmdUI *pCmdUI)
{
	if(Menu.GPSConnect==true)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);	
}

void CMainFrame::OnGpsSettings()
{
	
}

void CMainFrame::OnDocView()
{
	
	if(Menu.DocumentView==false)
	{
       ViewDocFrame=new CViewDocFrame;
	   ViewDocFrame->Create(NULL,"Документы",WS_POPUP|WS_CAPTION|WS_THICKFRAME|WS_SYSMENU,CRect(0,0,150,200),this);
       ViewDocFrame->ShowWindow(SW_SHOW);
	}
	else
	{
		ViewDocFrame->DestroyWindow();
	}
}

void CMainFrame::OnUpdateDocView(CCmdUI *pCmdUI)
{
	
	pCmdUI->SetCheck(Menu.DocumentView);
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CMDIFrameWnd::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}

void CMainFrame::OnGpsList()
{
	GPSDlgList->DoModal();
}

void CMainFrame::OnHardView()
{

	if(Menu.HardView==false)
	{
       Menu.HardView=true;
	    HardToolFrame->MoveWindow(CRect(0,0,250,580));  
	    HardToolFrame->ShowWindow(SW_SHOW);
	}
	else
	{
		 Menu.HardView=false;
		 HardToolFrame->ShowWindow(SW_HIDE);
		
	}
}

void CMainFrame::OnUpdateHardView(CCmdUI *pCmdUI)
{
	if(Menu.HardView==false)
		pCmdUI->SetCheck(0);
	else
		pCmdUI->SetCheck(1);

}

void CMainFrame::OnMenuOpenRes()
{
	СOpenResDlg *OpenResDlg;
	OpenResDlg=new СOpenResDlg();
	OpenResDlg->DoModal();
	
}

void CMainFrame::OnMenuOpenProject()
{
 CFileDialog File(true,"rsmap",NULL,OFN_NOLONGNAMES   ,"Список устройства|*.rsmap||");
 if(File.DoModal()==IDOK)
{

	CStdioFile F;
	CString type;
	if(F.Open(File.GetPathName(),CFile::modeRead)==TRUE)
	{
		F.ReadString(type);
		
	}
	F.Close();
	int prob=type.Find(' ');
	if(prob!=-1) type.Delete(prob,type.GetLength()-prob);
	
	if(type=="0")
	{
	  CWorldMapFrame *pWorldMapFrame=new CWorldMapFrame(File.GetPathName());

	  if(pWorldMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN ,
		              CRect(0,0,260*3,260*3),NULL,NULL)==TRUE)
	  pWorldMapFrame->ShowWindow(SW_SHOW);
	}
	else
	if(type=="1")
	{
       CMapFrame *pMapFrame=new CMapFrame(File.GetPathName());
	   if(pMapFrame->Create(NULL,NULL,
		               WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_CLIPCHILDREN,
		              CRect(0,0,800,700),this,NULL)==TRUE)
	     pMapFrame->ShowWindow(SW_SHOW);
	}
	else
	if(type=="2")
	{
	   if(FrameContainer->Find3DWindow()!=NULL)
		 FrameContainer->Find3DWindow()->DestroyWindow();
	  CGLFrame *pGlFrame=new CGLFrame(File.GetPathName());
	  pGlFrame->Create(NULL,NULL,
		                 WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE,
		              CRect(0,0,800,600),this,NULL);
	  pGlFrame->ShowWindow(SW_SHOW);
	}

  }

}
void CMainFrame::OnMenuRastrCurMove()
{
	Menu.RaterCur=0;
}

void CMainFrame::OnMenuRastrCurPriv()
{
	Menu.RaterCur=1;
}

void CMainFrame::OnUpdateMenuRastrCurPriv(CCmdUI *pCmdUI)
{
	if(Menu.RaterCur==1)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);

}

void CMainFrame::OnUpdateMenuRastrCurMove(CCmdUI *pCmdUI)
{
	if(Menu.RaterCur==0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CMainFrame::OnMenuLink()
{
CDlgPrivList DlgPrivList;
DlgPrivList.DoModal();
}

void CMainFrame::OnMenuSave()
{
	FrameContainer->GetActiveFrame()->Save();
}

void CMainFrame::OnGlGrid()
{
   if(FrameContainer->GetActiveFrame()!=NULL)
	FrameContainer->GetActiveFrame()->ShowGrid(! FrameContainer->GetActiveFrame()->IsGridShow());

}

void CMainFrame::OnUpdateGlGrid(CCmdUI *pCmdUI)
{
	if(FrameContainer->GetActiveFrame()!=NULL)
 	 pCmdUI->SetCheck(FrameContainer->GetActiveFrame()->IsGridShow());
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); 

}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIFrameWnd::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect);
	GlToolFrame->MoveWindow(rect.right-232,0,230,rect.bottom- 15,1); 

}

void CMainFrame::OnMenu3DNew()
{
	if(FrameContainer->Find3DWindow()!=NULL)
		FrameContainer->Find3DWindow()->DestroyWindow();
    CGLFrame *pGlFrame=new CGLFrame();
	  pGlFrame->Create(NULL,NULL,
		                 WS_CHILD|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MAXIMIZE,
		              CRect(0,0,800,600),this,NULL);
	  pGlFrame->ShowWindow(SW_SHOW);
}

void CMainFrame::OnMenuGlReg()
{
CDlgGlRegistry DlgGlRegistry;
DlgGlRegistry.DoModal();
}

void CMainFrame::OnMenu3DMapTool()
{
  if(Menu.Tool3D==true)
  {
      Menu.Tool3D=false;
	  GlToolFrame->ShowWindow(SW_HIDE);
  }
  else
  {
      Menu.Tool3D=true;
	  GlToolFrame->ShowWindow(SW_SHOW);

  }
}

void CMainFrame::OnMenu3DToolMap(CCmdUI *pCmdUI)
{
	   pCmdUI->SetCheck(Menu.Tool3D); 

}

void CMainFrame::OnClose()
{
		GPS->StopGPS();
	delete GPSDlgList;
	delete GPS;
	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnMenuLoadLandHgt()
{
	GlLoadHgtDlg.DoModal();
}

void CMainFrame::OnMenuGlLoadRaw()
{
	GlLoadRawDlg.DoModal();
}

void CMainFrame::OnMenuGlTexLand()
{
	GlLandTexDlg.DoModal();
}


void CMainFrame::OnMenuMiniMap()
{
	if(FrameContainer->GetActiveFrame()!=NULL)
	{
         if(FrameContainer->GetActiveFrame()->IsMiniMapVisiable()==true)
			 FrameContainer->GetActiveFrame()->ShowMiniMap(0);
		 else
         if(FrameContainer->GetActiveFrame()->IsMiniMapVisiable()==false)
			 FrameContainer->GetActiveFrame()->ShowMiniMap(1);

	}
      
}

void CMainFrame::OnUpdateMinMap(CCmdUI *pCmdUI)
{
	if(FrameContainer->GetActiveFrame()!=NULL)
	{
         pCmdUI->SetCheck(FrameContainer->GetActiveFrame()->IsMiniMapVisiable());
	}
	else
	{
		pCmdUI->SetCheck(0);
	}

}
