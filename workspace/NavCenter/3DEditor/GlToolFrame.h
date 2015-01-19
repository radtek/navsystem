#pragma once


// CGlToolFrame frame


//������ 3d �����(��������� ������)
class CGlToolFrame : public CFrameWnd
{

	DECLARE_DYNCREATE(CGlToolFrame)
protected:
	DECLARE_MESSAGE_MAP()
public:
	CGlToolFrame();           // protected constructor used by dynamic creation
	virtual ~CGlToolFrame();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnCategoryBoxChange();
	afx_msg void OnObjComboBoxChange();
	afx_msg void OnObjListChange();
	afx_msg void OnBtnAddClick();
	afx_msg void OnBtnFixClick();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar *pScrollBar);
    afx_msg void OnObjListCLick(NMHDR *pNMHDR, LRESULT *pResult);

	
protected:
	  CPoint       SelectInd;
      CButton     *ButtonAdd;      //������ ���������� �������
      CButton     *ButtonFix;      //�������� �������
	  CComboBox   *ComboCategory;  //����������� ������ ���������	
	  CComboBox   *ComboObj;       //������������ ������ �������� ��������� ��������� � ComboCategory
	  
      CSliderCtrl *Slider;
 	  CRect RectWnd;
      
	  CString     GetFileNameFromBD(CString Category,CString Caption);    //���������� ��� ����� ���������� �� ��������� Category � ��������  Caption
      CString     TreeGetPathName(HTREEITEM parItem); 
	  CPoint      GetItemIndex(HTREEITEM parItem);
public:
	CTreeCtrl   *ListObj;
	CPoint  AddToObjList(CString caption);
    void    ReLoadCategory();
    void    ReLoadObj(CString category);
    void    ReloadObjList(vector<CString> strings);
    int     GetLevelCount(HTREEITEM parItem);
};


