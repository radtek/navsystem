#pragma once


// CHardToolFrame

class CHardToolFrame : public CFrameWnd
{
   DECLARE_DYNAMIC(CHardToolFrame)
   CComboBox *ComboHardware;
   CListBox  *ListBox;
   int DriveIndex;                     /*������( ���������� ����������) � �������  
									     theApp.MainForm->GPS->HardwareList*/
   THardware *SelectedDrive;
   CButton   *ButtonPrevious;
   CButton   *ButtonNext;
   CButton   *ButtonFind;               //������ ������ ����������(��������) �� �����
   CRect ClientRect;                    //������� ���������� ������� ����
   bool ConnectStatus;                //��������� �����������: true - ����� � �������
   CDC dcMemory;
   void UpdateVirtualCanvas(CDC *pDC);        //��������� �������� � ������ � �������� ��� � pDC
public:
	void UpdateInfo();                //�������� ������ ���������
	void UpdateWindowList(int index); //�������� ������ ���� � ������ ���� � index ����������
	void SetDriveRedraw();            /*���������, ���������� ������ � ������� ����������� ���������� � 
									    ComboHardware  ����������(����������� ������) ��� ���(�����������
										�� ������)*/
	void CloseConnect();              //���������� ���� ���������� ���� ��������(��� ������ ����)
	void OpenConnect();               //���������� ���� ��������� ���������� � ��������
	void AddToDriveList(int index);   //�������� � ComboHardware ������
	void DeleFromDriveList(int index);//������� �� ComboHardware ������
	void UpdateCanvas();
	CHardToolFrame();
	virtual ~CHardToolFrame();
    
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBoxChange();
	afx_msg void OnSessionChange();
	afx_msg void OnBtnFindClick();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
};


