// �OpenResDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3DEditor.h"
#include "OpenResDlg.h"


// �OpenResDlg dialog

IMPLEMENT_DYNAMIC(�OpenResDlg, CDialog)

�OpenResDlg::�OpenResDlg(CWnd* pParent /*=NULL*/)
	: CDialog(�OpenResDlg::IDD, pParent)
	, m_RadioBlock(false)
{

}

�OpenResDlg::~�OpenResDlg()
{
}

void �OpenResDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(�OpenResDlg, CDialog)
END_MESSAGE_MAP()


// �OpenResDlg message handlers
