#pragma once
#include "include.h"
#include "Shader.h"
#include "Texture.h"
#include "3DLib.h"
class CGlLandshaft
{
struct THgtGeoInfo
{
  CVector2 Block;            //������ hgt �����. ������ �� (-180,-90)
  CVector2 GeoCord;          //������ �� �����  � �������� �� 0
  CVector2 GlobMapSize;      //������ ����� ������� ���� � ������ ��������(1201-���� ������)
}HgtGeoInfo;
private:

static WORD  sh(WORD x);                                                //������ ������� ������� � ������� ����
bool   PointBilongTriangle(CPoint Point,CVector3 *Triangle);             //������������ �� ����� ������������?
int    IsolateYFromEauation(CPoint pp,CVector3 *p);           //������� ������ ��� ����� Point(X,Y-?,Z) 
void	     GenVNormals();                                              //��������� ��������� �������
void 	     LoadLandToMemory();                                         //��������� �������� � ������(opengl list) 
CVector3	 GenTrianglePNormal(CVector3 p1,CVector3 p2,CVector3 p3);    //��������� ������� ������������ 
bool         LoadRawFileToMass(int ***mass,CString FileName,int type);   //��������� � ������ mass ������ �� ����� FileName; type - ���-�� ������ ��� ���� �������

bool InitFlag;
bool MixingFlag;                                 //���� �� ������� ��������� ���������?
TLandProperties LandInfo;                        //���������� � ���������   
GLuint GlMemoryPt;                               // ��������� �� ������ ��� ������ ���������
int **MassHeight,**MassTexture;                  // �������: ����� ����� � ��������
CVector3 **MassVNormal;                          //��������� ������� �������
CVector2  ScaleTexMixing;
CShader MixingShader;                            // ������(���������) ������ ����������
CShader MapShader;                               // ������(���������) ������ ������������ ����� ���������
CShader WaterShader;
CTexture TexMixing[5];                           // 3 ��������, ������� ������������ ��� ����������(���� �� ���� �������� ���������� ������)
int TextureDetalLevel;                           //  ���-� ����������� ��������, ������, ������ ������
vector<CTexture> MapTextures;                    // ������ �������-����, ������������� �� �������� 
int SelectMapInd;                                //  ������ ������� �����
template<class T> void         FilterDiamondSquareFractal(T** &heights,float roughness,int width,int height);
template<class T> void         FilterTailing(T** &heights,int w, int h);
template<class T> void         FilterSmooth(vector<T> &m_heights,int w,int h);
template<class T> void         FilterAverage(T** &heights,int w, int h);
CPoint MapSize;
CVector2 pictCord;
public:

int           Create();                              
int			  Create(TLandProperties Properties,CPoint MapSize);    //������� �������� �� �������� ��������� � ��������� Properties
void		  Render();                                             //���������� ��������
bool          IsInit();                                             //��� �� ��������������� ��������?
void          NextMap();                                            //��������� ��������� �����-�������� (-1 - ������ ����,0-������, 1.. - MapTextures)
void	      BackMap();                                            //��������� ���������� �����-�������� (-1 - ������ ����,0-������)
void          SetTextureDetalization(int DetalizationKoef);
void	      AddMapMixing(CString Tex1File,CString Tex2File,CString Tex3File,CString TexWaterFile, CString TexVec);
bool          IsLandMixing();
void          GetMixingInfo(CString &Tex1File,CString &Tex2File,CString &Tex3File, CString &TexVec,CString &TexWaterFile);
void          AddMap(CString TexFileName);
bool          SaveLand(CString PathName,vector<CString> *ProtocolStr,bool rewrite);
int           GetLandGridType();
CVector2      GetHgtGeoCord(CPoint p);                      // ��� ��������� p ����������  ������ � �������(������ ��� hgt �����)
int           GetHeightForPoint(CPoint p);                  // �������� �������� ������ ��� p
bool          IsPossibleMove(CPoint OldP,CPoint NewP);      // ����� �� ������������� �� �����  OldP � ����� NewP
void          Free();

vector<CString>  PrintTexFiles();

	CGlLandshaft(void);
	~CGlLandshaft(void);
};
