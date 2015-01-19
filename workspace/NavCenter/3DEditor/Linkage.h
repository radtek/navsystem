#pragma once
#include "afx.h"
#include <vector>
#include "matrix.h"
using std::vector;
struct TPointPriviazka
{
   double Lon;        //�������
   double Dest;       //������
   int    MapX,MapY;  //����� �� �����

};
/*
F1(x,y)=a1+a2*x+a3*y+a4*x^2+a5*x*y+a6*y^2 - De
F2(x,y)=b1+b2*x+b3*y+b4*x^2+b5*x*y+b6*y^2 - Lo

F1IsolateX1 - �������� x �� F1(x,y) + ����� ������ �������������
F1IsolateX2 - �������� x �� F1(x,y) - ����� ������ �������������

F1xToF2(y)=b1+b2*F1IsolateX1+b3*y+b4*F1IsolateX1^2+b5*F1IsolateX1*y+b6*y^2 - Lo
*/
class CLinkage
{
  bool bindingFlag;                                   //true - �������� ���������  
  bool created;
  double a[7],b[7];                                   //���-�� �������. ��������������
  vector<TPointPriviazka> PointsPriviazka;            // ������ ����� ��������
  CRect MapRect;                                      //������� �����, ������� �����������           

//������� ��� ������� ������� ������� ������� �������
  double F1(double &x,double &y,double &De);                  //���������� �������� 1-�� �������� ��� x,y,De
  double F1IsolateX1(double &y,double &De);                   //�� ��������� F1 �������� ���������� x �� ������ +, �-��� ���������� � �������� ��� ��������� y
  double F1IsolateX2(double &y,double &De);                   //�� ��������� F1 �������� ���������� x �� ������ -, �-��� ���������� � �������� ��� ��������� y,
  double FxToF2(double &y,double &De,double &Lo,int X_Ind);   //�������� �-��� F2 � ������������ ������ x ��������� F1IsolateX1(F1IsolateX2)
  double F2(double &x,double &y,double &Lo);                  //���������� �������� 2-�� �������� ��� x,y,Lo
  CPoint SolveDivHalfMethod(double &De,double &Lo);
 
  CPoint SolveModificNewtonMethod(double &De,double &Lo);
  CPoint SolveNewtonMethod(double &De,double &Lo);
public:
    void     CreateObj(CRect MapRect);                                              //������� ������         	
//������� ��� ��������
    void      AddPoint(int MapX,int MapY,double GeoDest,double GeoLon);             // ��������� ����� ��������
	void      AddPointFromStr(CString S);
	void      GenerateKoefPriv();                                                   // ���������� ����-�� �������
	int       GetPointPrivCount(){return PointsPriviazka.size();}                  // ���������� ���-�� ����� ��������
	CString*  GetListPointPriv(int *count);                                        // ���������� ������ �����(<MapX> <MapY> <GeoDe> <GeoLon>) - ��� ������ � ����
    void      ConvertMapToGeoCord(CPoint Point,double *GeoDest,double *GeoLon);   
    CPoint    ConvertGeoToMapCord(double GeoDest,double GeoLon);     
	bool      IsBinding();                                                         // ���� �� �������� ��������?
    void      RewriteElem(unsigned int ind,int MapX,int MapY,
		                  double GeoDest,double GeoLon);                           //�������� ����� ind ������� PointsPriviazka
	bool      GetPointPriv(TPointPriviazka *PointPriv,unsigned int ind);
    void      DeletePoint(unsigned int ind);                                      //������� ����� � ������� ������� �����
	CLinkage(void);
	~CLinkage(void);
};
