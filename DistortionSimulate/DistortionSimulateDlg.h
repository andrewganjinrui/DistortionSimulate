// DistortionSimulateDlg.h : ͷ�ļ�
//

#pragma once
#include "BeamDisplay.h"
#include "TargetDisplay.h"



// CDistortionSimulateDlg �Ի���
class CDistortionSimulateDlg : public CDialog
{
// ����
public:
	CDistortionSimulateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DISTORTIONSIMULATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

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

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
