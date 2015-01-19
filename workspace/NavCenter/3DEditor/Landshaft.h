#pragma once
#include "GlModels.h" 
#include "include.h"
#include "afx.h"
#include "3dLib.h"


class CLandshaft: public CGlModels
{
private:
bool InitFlag;
bool LoadRawFileToMass(int ***mass,CString FileName,int type);               // ������ raw-���� � ���������� � ������ mass 
bool InitLandshaft(CString LandFile,CString TexFile);				   //��������� ������ �������� ���������
void RenderLand(); //���������� �������� � OpenGl
void GenVNormals();//������� ��������� ������� � ������ MassVNormal ���������
void Tailing();    //�������� ����� �����
TPoint GenTrianglePNormal(TPoint p1,TPoint p2,TPoint p3); // ����������� ������� � ���������(������������ � 3D)
public:
   int **MassHeight,**MassTexture; // �������: ����� ����� � ��������
   TPoint **MassVNormal;            //��������� ������� �������
   TLandProperties LandInfo;       //���������� � ���������   
   GLuint GlModelList;             //������ ��� ������ ���������

   virtual void Draw();
   virtual void ReGenModel();
   virtual ~CLandshaft(void);

   CLandshaft(TLandProperties prop);
   CLandshaft(void);
   bool isInit()
   {
     return InitFlag;
   }
   
};
