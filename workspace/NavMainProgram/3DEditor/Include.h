#pragma once



/*#include <Stdio.H>
#include <Stdlib.H>*/
#include <Math.H>
#include <vector>
using std::vector;
struct TGPSPoint
{
  double Longitude;                        // �������
  double Description;                      // ������
  double Height;                           // ������ ��� ������� ����
  CString DateTime;                        // ����� ������� ��������� �� ������
};
struct THardware                            //������ ��� � ����� �������
{
   CString Name;                            //�����<caption> ����������
   CString ID;                              //IMEI ����������
   bool runtime;                            //��������� � �������� �������
   CString DateTime1,DateTime2;             //���� runtime=false: ������ ���������� ������� 
   vector<int> WindowsList;                 //������ FrameIndex ����, � ������� ��������� THardware
   vector<TGPSPoint> PositionFromBD;        /*���������� � ������ ������� �/� DateTime1 � DateTime2
									          �������� ������ ���� runtime=false*/
 };