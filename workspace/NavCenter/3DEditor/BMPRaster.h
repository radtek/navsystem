#include "Raster.h"
#include "Memory.h"
#include <atlimage.h>

#ifndef _RASTER_INCLUDED
#define _RASTER_INCLUDED
// ������ ��� ����������� ���������� ���� � ����������� �� DWORD ������ �������� � DIB 
// Width - ����� ������ � ��������; BPP - ��� �� ������
#define BYTESPERLINE(Width, BPP) ((WORD)((((DWORD)(Width) * \
(DWORD)(BPP) + 31) >> 5)) << 2) 

//****const


class CBMPRaster : public CRaster
{
   LPBITMAPINFO   m_pBmpBMI;   //��������� �� �������� �����������
   LPBITMAPINFO   m_pBmpMiniBMI;
   PBYTE          m_pData;     //��������� �� ������ �����. �����
   PBYTE          m_BmpData; //��������� �� ������ �������, ������� ��������� �� ����� 

   CMemoryMappedFile MemoryF;  //������ ������������� �����
   CRect WindowRect;           //������� ���� ������

   
   bool LoadFlag;   // �������� ������ �������
   bool project_type; //��� ������������ �����, ������(�� ���� ��������� ����-�����)
   int Rop;
   CString FileName;  // ��� � �����
   struct TColor 
   {
     unsigned int  R;
	 unsigned int  G;
	 unsigned int  B;
   }**Color;
private:
	PBYTE MiniMapMass;
    CRect MiniMapSize;
	CImage *MixedMiniMap;
	
	void RefreshMemory();
public:
  //   virtual �Rect SetMiniMap(CRect MapSize);///*������� ������� ������ ��� ������������������ ����� �� ������� MapSize   ���������� ������� ��-�(���� ����� ���� ������. �����)*/
   virtual CRect SetMiniMap(CRect MapSize);
   virtual void DrawMiniMap(CDC *dc,CPoint pos);//������ ��������� ��  dc � ��������(�� �������) pos
   void DrawMiniMap(HDC hDC,CPoint pos);//������ ��������� ��  dc � ��������(�� �������) pos

   virtual void Resize(CRect WindRect);
   virtual bool Load(CString FileName,CRect WindRect);
   virtual void Free();
   void Draw(CRect Output,CDC *dc,CPoint pos);
   CRect SizeNormalize(CRect pict,CRect Output);
   void Clear();
   
   /*void DrawBitmap(CDC *pDC, LONG x=0, LONG y=0, LONG cx=0, LONG cy=0,
                   LONG x0=0, LONG y0=0, LONG cx0=0, LONG cy0=0,
                   int str_mode=COLORONCOLOR, DWORD rop=SRCCOPY);*/
   void PushMass(CRect oldRect,CRect newRect);
   CBMPRaster();
   ~CBMPRaster();
};
#endif
