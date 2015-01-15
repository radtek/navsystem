//#include "3DLib.h"
#pragma once
#include "stdafx.h"
#include "afx.h"
#include <gl\glew.h>
#include <gl\gl.h>
#include <gl\glaux.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\glut.h>
#include <gl\wglext.h>

#include "stdafx.h"
using namespace std;

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glut32.lib")

#pragma comment (lib,"OpenGL32.Lib")
#pragma comment (lib,"GLu32.Lib")
#pragma comment (lib,"WinMm.Lib")
#pragma comment (lib,"GLaux.Lib")

struct TLandProperties
{//��������  ���������
  CString LandFile;                         //���� � ����� �����
  CString TexFile;                          //���� � ����� ��������
  int ElemSize;                             //� ����� ������� �������� ������ 
  int StepSize;                             //���, � ������� �������� ���� �����
  int width,height;                         //������� ����� ����� 
  int MaxHeight,MinHeight;                  //������������ � ����������� ������ �� �����
  bool AutoCalcMaxMinHeight;                //����/��� ������ ��������� ���������� ��� �� ����� ������������?
  double ScaleX,ScaleY;                     // ��������������� �� X,Y(���������� ��� ������)
  int DW,DH;                                //������ � ������ StepSize(w/StepSize;h/StepSize)
  
  bool FilterTaling;                        //��������
  bool FilterFractal;                       //����������� ���������� ���
  bool FilterAverage;                       //����������
  bool FilterSmooth;                        //�����������
};

struct CVector3{
	float x,y,z;
};

struct CVector2{
	float x,y;
};

// ��� ��������� ��������. ��� ������������ ��� �������������� �������� ���������
// ������ � �������. ��� ���������� �������� ��� � ���, ����� ������ ������ � �������
// ������ �������� �����������. �� �� ����� �������� ���������� ���������.
struct tFace
{
	int vertIndex[3];			// indicies for the verts that make up this triangle
	int coordIndex[3];			// indicies for the tex coords to texture this face
};
 
 
// ��� ��������� ������ ���������� � ���������. ��� ����� ���� ���������� ����� �����.
// ��������� �������� �� ������������, �� � ������� ��, ����� ����� ������� �� ���
// �������.
struct tMaterialInfo
{
	char  strName[255];			// ��� ��������
	char  strFile[255];			// ��� ����� ��������
	BYTE  color[3];				// ���� ������� (R, G, B)
	int   texureId;				// ID ��������
	float uTile;				// u-tiling �������� (������ �� ������������)
	float vTile;				// v-tiling �������� (������ �� ������������)
	float uOffset;				// u-offset �������� (������ �� ������������)
	float vOffset;				// v-offset �������� (������ �� ������������)
};
 
// �������� ��� ���������� � ������/�����.
struct t3DObject
{
	int  numOfVerts;			// ����� ������ � ������
	int  numOfFaces;			// ����� ��������� � ������
	int  numTexVertex;			// ����� ���������� ���������
	int  materialID;			// ID �������� ��� �������������, ������ ������� �������
	bool bHasTexture;			// TRUE ���� ���� ���������� ����� ��� ����� �������
	char strName[255];			// ��� �������
	CVector3  *pVerts;			// ������ ������ �������
	CVector3  *pNormals;			// ������� �������
	CVector2  *pTexVerts;			// ���������� ����������
	tFace *pFaces;				// �������� �������

	int  positionFrames;		// ����� ���������� �����������
	int  rotationFrames;		// ����� ���������� ��������
	int  scaleFrames;		// ����� ���������� ���������������
 
	CVector3 vPivot;		// ����� ����� �������
 
	vector<CVector3> vPosition;	// ������ ������� �������
	vector<CVector3> vRotation;	// ������ �������� �������
	vector<CVector3> vScale;	// ������ �������� �������
 
	vector<float> vRotDegree;	// ���� �������� �������
};
 
 
 
// �������� ���������� � ������. ���� ������� �� �������� � �����. 
struct t3DModel
{
	int numOfObjects;			// ����� �������� � ������
	int numOfMaterials;			// ����� ���������� ������
	vector<tMaterialInfo> pMaterials;	// ����� �������� ���������� (�������� � �����)
	vector<t3DObject> pObject;		// ������ �������� � ������

	int numberOfFrames;	// ����� ������ �������� ��� ������ ������ (��� ������� 1)
	int currentFrame;	// ������� ���� �������� ������
};
 
