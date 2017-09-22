#pragma once


// CBeamDisplay 对话框

class CBeamDisplay : public CDialog
{
	DECLARE_DYNAMIC(CBeamDisplay)

public:
	CBeamDisplay(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBeamDisplay();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

public:
	int m_nHcount;
	int m_nVcount;
	int m_nPage;

	ImgDataVec m_pImgDataVec;

public:
	void SetData(ImgDataVec& DataVec);
	LPBITMAPINFO cv_CreatImgInfo(IplImage* pImg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
