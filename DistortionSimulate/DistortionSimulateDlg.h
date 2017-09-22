// DistortionSimulateDlg.h : 头文件
//

#pragma once
#include "BeamDisplay.h"
#include "TargetDisplay.h"



// CDistortionSimulateDlg 对话框
class CDistortionSimulateDlg : public CDialog
{
// 构造
public:
	CDistortionSimulateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DISTORTIONSIMULATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CTargetDisplay m_ShowTarget;
	CBeamDisplay m_ShowBeam;
	CButton *m_pButton;

	int m_nPage;

	ImgDataVec m_VecTargetData;
	ImgDataVec m_VecBeamData;
	ParameterVec m_VecParameter;
	Parameter m_Parameter;

public:
	CButton* CreatButton(int nID, CRect rect);
	void DistortImg(IplImage* SrcImg, IplImage* DstImg, double Xsita, double Ysita, double Zsita, double sBeta);
	void ProcessImg();
	BOOL Deal_ImageAnalysis(LPBYTE lpImgData, LPBYTE lpLaserSpot, int ImgWidth , int ImgHeight, int LineWidth, CvPoint2D32f& TargetCentre, CvPoint2D32f& LaserSpotCentre);
	void SaveRequiredData();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnOPENTARGET();
	afx_msg void OnOPENBAEM();
	afx_msg void OnNEXT();
	afx_msg void OnPRIOR();
	afx_msg void OnSTART();
	afx_msg void OnFUSSIONPLAY();
	afx_msg void OnSAVEDATA();

	DECLARE_MESSAGE_MAP()
};
