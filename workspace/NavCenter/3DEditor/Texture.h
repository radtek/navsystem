#pragma once
#include "afx.h"
#include "3dLib.h"
class CTexture
{
	 AUX_RGBImageRec *texture;                                             // �������� ��������
	 CString FileName;
	 GLuint	texPtr;
	 GLvoid LoadGLTextures();
	 bool createdFlag;          //���� �� ��������� ��������
public:
	void    Create(AUX_RGBImageRec *texture); //������� ������ �� ��� ���������� texture 
	void    InitTexture(CString FileName);
	GLuint  GetTexPt();
	bool    IsCreated();
	CString GetTexFileName();
	int     PictWigth();
	int     PictHeight();
	void    Free();
	CTexture(void);
	~CTexture(void);
};
