#pragma once
#include "afx.h"
#include "3DLib.h"
#include <vector>
#include "3ds.h"
#include "GlLandshaft.h"

using std::vector;

//��������� 3ds ��������, ��������� ������ �������(�����, ��������������...) 
class CGlContainer
{
struct TModelCord
{
	
  CVector3 ScaleKoef;          //��������������� ������
  CVector3 pRotate;            //���-�� �������� 
  CVector3 pPos;               //������� ������
  double   pAlphaValue;        //���� �������� ������
};

struct TStaticModel
{
 GLuint ModelMemory;
 CString caption;
 int type;            //��� ������ (���� ��� �� ���������)  
 vector< TModelCord> MassCoord; // ������ ��������� �������(������ � ������ ����, � ������������ �� ������ ��������, �������� ���� ��������, � ������ ������ ����)
};

struct TGridModel
{
 GLuint ModelMemory;
 CString caption;
 int type;            //��� ������ (���� ��� �� ���������)  
 CVector3 Pos;
 CVector3 ScaleKoef;          //��������������� ������

};
private:
vector<int>             FreeUnicObjInd;      //���������� ������ ������� �������  � ������ opengl 
vector<TStaticModel>	ModelsList;         //������ ��� 3ds ������ � ������
TGridModel              GridModel;          // ����� � ������
CLoad3DS                g_Load3ds;		    //��� 3DS �����.
CPoint                  selected_ind;       //������ ���������� �������
public:

void       AnimateModel(t3DModel *pModel, t3DObject *pObject);
void       InitStaticObj();                                   //
void       ShowGrid(bool show,int Width,int Height,int Step); //���������/������� �� ������ ������ �����
void       ShowLand(bool show);                               //���������/������� �� ������ ������ ��������
void       RenderObjects();
int        GetGridInd();
void       DeleteObj(int index);
void       SetPosition(CVector3 position);                       //������� ��������� �� �����(��� �����) 
CPoint     LoadModel(CString FileName,CString Caption,CVector3 pos);       //��������� ����� ������
void       FixMovingModel(CVector3 position);                     //��������� ����������� ������(�.�. ���������� � ������ � �  ModelsList)
void       MovingNewModel(CVector3 position);                   //������� ����� ������������ ������
void       GetObjString(vector<CString> *StrList);            //��������� ������ �����(caption) �������� ��������
void       ChangeObjPos(CPoint ind,CVector3 position);             //������ ������� ������
void       ChangeScale(CPoint ind,CVector3 scale);//������������ ������
void       Destroy();
void       SelectObj(CPoint ind);
bool       GetSaveProtocol(vector<CString> *ProtocolStr,bool rewrite);//�������� ���� � ProtocolStr: ������ �����, �����. � ���� ����������
//������� �������� ������ �� ������� �����
CVector3     GetPosition(CPoint index);
CVector3     GetScale(CPoint index);


CGlContainer(void);
~CGlContainer(void);
};
