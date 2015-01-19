#pragma once
#include "afxwin.h"
#include <vector>
#include "afx.h"
#include "include.h"
#include "Linkage.h"
#include "3DLib.h"
using std::vector;
const unsigned short MAXCOL_WIND=2000;// ������������ ���-�� ������������ �������� ����
//Index      - ������ ���� � �������  
//FrameIndex - ���������� ������ ����(��������� � ����� ������� "����" � � ��������� TContainer)
class CFrameContainer :	public CMDIChildWnd
{
	struct TContainer
	{
       CFrameContainer* FramePtr;
	   int FrameIndex;
	};
protected:
	unsigned int activeIndex;// ���������� ������ ��������� ����
    void DrawPoint(CDC *pDC,CPoint position,int ColorType);
	int UnicIndex;  //���������� ������ ����(��� ��������)
    THardware SelectedAbonent;//��������� �������(������� ��������)
	unsigned int WindowType;
	bool FlagMiniMap;
private:
	bool DestroyFlag;
    vector<TContainer> Container;
	vector<unsigned short> FreeIndex;
	CFrameContainer *FramesMass[MAXCOL_WIND+1];/* i-�	 ������� �������( i-�������� ���������� �������� ����)  ��������
											   ��������� ��  ���� �� ��� ����. �������   FramesMass[i] -  �������� ���������
   											   �� ���� � ����. �������� i*/ 
public:
CFrameContainer(void);


void             InitContainer();
void             AddToContainer(CFrameContainer* AddFrame);
void             DelFromContainer(int FrameIndex);
void             SetActive(int FrameIndex){activeIndex=FrameIndex;}          //������� � ��������� ����������, ��� ���� FrameIndex ����� �������� 
void             SetSelectAbonent(THardware Hardware){this->SelectedAbonent=Hardware;}
int              InsertToListBox(CListBox* ListBox);                         //��������� � ListBox ������ ����,���������� ����� ������ �������� ��������� 
void             DestroyContainer();

int              GetActiveIndexFrame();
int              GetWindowCount();
int              GetFrameIndex(int Index);                                   //�������� ���������� ������ ���� �� ������� ������� Container
int              GetIndexFromFrameIndex(int FrameIndex);                     //�������� ������ ������� �� ����������� ������� ����
CFrameContainer* GetActiveFrame();
TContainer       GetContainerElement(int index);                             //�������� ������� ������� Container 
CFrameContainer* GetFramePtr(int FrameIndex){return FramesMass[FrameIndex];}
CString          GetWindText(int FrameIndex);                                //�������� ����� ��������� ���� �� ���������� ������� ����
THardware        GetSelectAbonent(){return SelectedAbonent;}                 //���������� �������� ��������, ������� ����������� �������������(������� ��������)
bool             isDestroy();
CFrameContainer* Find3DWindow();                                             //���� � ���������� ���� "3�-�����"(��� ����� ���� ������� ������ ����)
int              GetWindowType();                                            //���������� ��� ����: 0,1,2
bool             IsMiniMapVisiable(){return FlagMiniMap;}                    //����� �� ����-����� � �������� ����?

virtual void     Repaint(){}
virtual CLinkage* GetLinkageObj(){return NULL;}                               //����������� ����-�� �����(�.�. ����������� �� � ������� ������� �����)
virtual void      DrawHards(){}                                               //���������� �� ����� ���� ���������
virtual void      FindAbonent(TGPSPoint *Position){}                          //����� �������� �� ����� � ��������� �� �������� ��������� ��������
virtual void      Save(CString FName=""){}                                    //��������� ������
virtual           ~CFrameContainer(void);
virtual void      ShowMiniMap(bool visiable){}                                 //��������/������ ����-�����
//����������� ������� ������������� ��� ���� CGlFrame

virtual void     ShowGrid(bool show){}                                         //�����/������ �����
virtual bool     IsGridShow(){return false;}	                               //���� �� ����� � gl ����?
virtual void     AddObj(CString FileName,CString Caption){}                    //�������� ������ � ����
virtual void     StartMoveObj(CPoint ind){}                                       //������ �������� �������
virtual void     StopMoveObj(){}                                               //���������� �������� �������
virtual void     ChangeObjScale(CPoint ind,double &scaleX,double &scaleY,double &scaleZ){}                        //�������� �������(������) �������
virtual void     RenderScene(){}                                               //�������� opengl �����
virtual double   GetScale(CPoint ind){return 0.0;}                                //������� �������
virtual void     GetObjPos(CPoint ind,double &x,double &y,double &z){}      //������� �������
virtual void     SelectObj(CPoint ind){}                                          //�������� ind ������(3ds), ����� ���� �� ���������� �����
virtual void     InitLand(TLandProperties LandProperties){}//������������� ���������


virtual void     LandMixing(CString Tex1File,CString Tex2File,CString Tex3File,CString WaterFile,CString TexVecFile){} //�������� ������� ��� ���������� ��������
virtual void     AddMapToLand(CString FileName){}                    

};
