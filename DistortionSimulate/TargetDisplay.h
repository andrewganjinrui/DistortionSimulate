#pragma once


// CTargetDisplay �Ի���

class CTargetDisplay : public CDialog
{
	DECLARE_DYNAMIC(CTargetDisplay)

public:
	CTargetDisplay(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTargetDisplay();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

public:
	int m_nHcount;
	int m_nVcount;
	int m_nPage;

	ImgDataVec m_pImgDataVec;

public:
	void SetData(ImgDataVec& DataVec);
	LPBITMAPINFO cv_CreatImgInfo(IplImage* pImg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};