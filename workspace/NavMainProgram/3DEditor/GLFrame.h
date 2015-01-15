#pragma once
#include "include.h"
#include "3dlib.h"
#include "FrameContainer.h" 
#include "GlContainer.h"

using std::vector;


struct TObjMoving
{
  bool move;
  CPoint ind;
};
class CGLFrame :public CFrameContainer
{
struct TCursorGuidance // ��������� ������ ����������, ����������� � ���� � �����
{
  CVector3 Pos;
  CVector3 Angle;
  CVector3 Center; //���� ����������, �� ������� ��������� ������
  float R;  //������
};
struct TFlyGuidance // ��������� ������ ����������, ����������� � ���� � �����
{
  CVector3 Pos;
  CVector3 Angle;
//  CVector3 Center; //���� ����������, �� ������� ��������� ������
};
struct TLandGuidance // ��������� ������ ����������, ����������� � ���� � �����
{
  CVector3 Pos;
  CVector3 Angle;
//  CVector3 Center; //���� ����������, �� ������� ��������� ������
//  float R;  //������
};
struct TMouse
{
  int  CameraType;  //0 - ����� �������, 1- ��������� �����, 2-������ �� ���������
  TCursorGuidance CursorCamera; 
  TFlyGuidance FlyCamera;
  TLandGuidance LandCamera;
  bool  PressingLB,PressingRB;//������ �� �����/������ ������
}Camera;

private:
//******************************************************
 int screenBitSize;
 CVector3 CursorPosition;
 HGLRC  hRC;                     // ���������� �������� ����������
 HDC  hDC;                       // ��������� �������� ���������� GDI
 CDC *pDC;
 CGlContainer GlContainer;       //��������� 3ds ��������
 bool  keys[256];                // ������, ������������ ��� �������� � �����������
// float koef;                    
 int MapWidth,MapHeight;        //������� �����(�� ������������)
 float PosLight[4];             //������� ��������� �����
 bool IsCreated;                //���� �� ������� ����
 bool GridFlag;                 //�����/������ ����� 
 CString ProjName;
 TObjMoving MoveObj;            //������ ������ � ��������� ��������� 3ds ������(� �����������)
 CGlLandshaft *Landshaft;       //��������
//******************************************************
 bool		InitGL( GLvoid );
 void		DestroyGL(GLvoid);
 void		DrawScene();
 void		Load(CString FName);  //�������� �� ������������ �����
 CVector2   GetGeoCord(CPoint p); //�������� �����. ���������� ������������ ��������� ������
 CString    GetFNameFromDB(CString caption);
//******************************************************
public:
virtual void     AddMapToLand(CString FileName)
{
	Landshaft->AddMap(FileName);
}  
virtual void     InitLand(TLandProperties LandProperties);
virtual  void LandMixing(CString Tex1File,CString Tex2File,CString Tex3File,CString WaterFile,CString TexVecFile)
{
  Landshaft->AddMapMixing(Tex1File,Tex2File,Tex3File,WaterFile,TexVecFile);
}
virtual bool     IsGridShow(){return GridFlag;}	
virtual void     ShowGrid(bool show)
{
		GridFlag=show;
		GlContainer.ShowGrid(show,MapWidth,MapHeight,20);
}
virtual void  AddObj(CString FileName,CString Caption)
{
	GlContainer.LoadModel(FileName,Caption,Camera.CursorCamera.Center);

}
virtual void   StartMoveObj(CPoint ind)
{
	MoveObj.move=true;
	MoveObj.ind=ind;
}
virtual void StopMoveObj()
{
   MoveObj.move=false;
}
virtual CVector3 GetObjPos(CPoint ind)
{
   return GlContainer.GetPosition(ind);
}
virtual void  ChangeObjScale(CPoint ind,double &scaleX,double &scaleY,double &scaleZ)
{
	CVector3 scale;
	scale.x=scaleX;
	scale.y=scaleY;
	scale.z=scaleZ;

	GlContainer.ChangeScale(ind,scale);
	//GlContainer
}
virtual void     RenderScene()
{
	DrawScene();
}
virtual void GetScale(CPoint ind,double &x,double &y,double &z)
{
	CVector3 Scale;
	Scale=GlContainer.GetScale(ind);
	x=Scale.x;
	y=Scale.y;
	z=Scale.z;
}

virtual void     SelectObj(CPoint ind)
{
   GlContainer.SelectObj(ind);
}
virtual void Save(CString FName="");
//////////////
public:
    CGLFrame(CString FName="");
protected:
	DECLARE_DYNAMIC(CGLFrame)
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
    afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnCaptureChanged(CWnd *pWnd);

	virtual ~CGLFrame(void);



};

