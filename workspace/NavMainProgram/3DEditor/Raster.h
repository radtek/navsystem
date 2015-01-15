#pragma once

#include <vector>
using std::vector;
//============================================================================================================================

class CRaster
{
public:
    struct TPictInfo
   {
      unsigned int width;
	  unsigned int height;
      unsigned int bit;

   };
private:
protected:
	bool LoadFlag;                                 //true - ����� ���������, �� ��
	TPictInfo m_pBMI;                              // ���� � ��������(������, ����)
	CRect PictRect;
	CRect Output;                                  //������� ������� ��������, ������� ��������(���������) �� �����  
   
public:

// ������� ������������ �����(�����������)
	TPictInfo GetPictInfo(){return m_pBMI;}       // ���������� ���� � ����. �����������
	void SetOutputRect(CRect rect){Output=rect;}  // ������� � ������ ������� ������� �������� ��� ���������(�������� ������ ������ �� �����)
	CRect GetOutputRect(){ return Output;}        // ���������� ������� ������� ������

// ���� ������ ��� ��������
	virtual void Draw(CRect Output,CDC *dc,CPoint pos){}
	virtual bool Load(CString FileName,CRect WindRect){return true;}
	virtual void Resize(CRect WindRect){}
	virtual void DrawMiniMap(CDC *dc,CPoint pos){}
	virtual CRect SetMiniMap(CRect MapSize){CRect r; return r;}
	virtual void Free(){}
// ���������� �������
	virtual bool     LoadFromFile(){return true;}
	virtual bool     SaveToFile(){return true;}

	CRaster(CString FileName);
	CRaster(void);
	~CRaster(void);
};

//============================================================================================================================
//����� ��������� ������
class CRasterException
{
public:
	enum _errs{ceUnknown,ceLoad,ceFileExists,ceFileUsing};
private:
	_errs Error;
public:    
	CString GetError()
	{
		switch (Error)
        {
        case ceUnknown                  : return "������ �� ����� ��������";
        case ceLoad                     : return "������ ��� �������� �������.";
		case ceFileExists               : return "������ ���� �� ����������";
		case ceFileUsing                : return "������ ���� ��� ������������";

        default : break;
        }
        return "����������� ������";
	}
	CRasterException(_errs Error){this->Error=Error;}
};
//============================================================================================================================

//��������� ��������� ������
#define TRY_RASTER() \
   try \
      { 
#define CATCH_RASTER() \
      } \
   catch (CRasterException& e) \
      { \
	    CString strErr= e.GetError();\
	    AfxMessageBox (strErr, MB_ICONWARNING); \
      } \


//============================================================================================================================
