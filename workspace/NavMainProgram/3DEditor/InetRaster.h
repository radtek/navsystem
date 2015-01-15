#pragma once
#include "afxwin.h"
#include "BlockRaster.h"
#include "afxmt.h "
#include <vector>
#include "afxinet.h"
using std::vector;

class �InetRaster :	public CWinThread
{

bool *Terminated;
CString FolderCache;
CString ServerUrl;
CBlockRaster *BlockRaster;
int LoadFileFromInet(CString FNameWithoutExp);
vector<TLoadedFiles> *LoadedContainer;
int *LoadedCount;
CWnd *pFrame;
int UnicWindIndex;
void Draw(TLoadedFiles LoadedFile);
   CMutex *InetMutex;
public:
void Connect();
	void Create(CBlockRaster *BlockRaster,bool *TerminatedThread,vector<TLoadedFiles>* LoadedContainer,
		int *LoadedCount,CWnd *pDC,int UnicWindIndex,CMutex *Mutex);
	
	�InetRaster();
	~�InetRaster(void);
	virtual BOOL InitInstance();
	virtual int Run();





	
};
