// DistortionSimulateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DistortionSimulate.h"
#include "DistortionSimulateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()


// CDistortionSimulateDlg 对话框




CDistortionSimulateDlg::CDistortionSimulateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDistortionSimulateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pButton = NULL;
	m_nPage = 0;

	m_VecTargetData.clear();
	m_VecBeamData.clear();
}

void CDistortionSimulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDistortionSimulateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDS_OPENTARGET, OnOPENTARGET)
	ON_BN_CLICKED(IDS_OPENBAEM, OnOPENBAEM)
	ON_BN_CLICKED(IDS_NEXT, OnNEXT)
	ON_BN_CLICKED(IDS_PRIOR, OnPRIOR)
	ON_BN_CLICKED(IDS_START, OnSTART)
	ON_BN_CLICKED(IDS_FUSSIONPLAY, OnFUSSIONPLAY)
	ON_BN_CLICKED(IDS_SAVEDATA, OnSAVEDATA)
END_MESSAGE_MAP()


// CDistortionSimulateDlg 消息处理程序

BOOL CDistortionSimulateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	MoveWindow(0, 0, width, height);

	if (m_pButton)
	{
		delete m_pButton;
		m_pButton = NULL;
	}
	CRect rect;
	for (int i = 0; i < 7; i++)
	{
		 rect = CRect(i * 100 + (i + 1) * 5, 5, (i + 1) * 100 + (i + 1) * 5, 45);
		m_pButton = CreatButton(102 + i, rect);
	}
	
	m_ShowTarget.Create(IDD_DIALOG1);
	m_ShowBeam.Create(IDD_DIALOG2);

	GetClientRect(rect);
	m_ShowTarget.MoveWindow(5, 50, rect.Width() / 2 - 10, rect.Height() - 55);
	m_ShowBeam.MoveWindow(rect.Width() / 2 + 5, 50, rect.Width() / 2 - 10, rect.Height() - 55);

	m_ShowTarget.GetClientRect(rect);
	m_ShowTarget.m_nHcount = int(rect.Width() / (WidthShow + 10));
	m_ShowTarget.m_nVcount = int(rect.Height()  / (HeightShow + 10));

	m_ShowBeam.GetClientRect(rect);
	m_ShowBeam.m_nHcount = int(rect.Width() / (WidthShow + 10));
	m_ShowBeam.m_nVcount = int(rect.Height()  / (HeightShow + 10));

	m_ShowTarget.ShowWindow(SW_SHOW);
	m_ShowBeam.ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDistortionSimulateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDistortionSimulateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDistortionSimulateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CButton* CDistortionSimulateDlg::CreatButton(int nID, CRect rect)
{
	CButton* pButton = new CButton;
	ASSERT_VALID(pButton);

	CString str;
	str.LoadString(nID);

	pButton->Create(str, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect, this, nID);
	return pButton;
}

void CDistortionSimulateDlg::OnOPENTARGET()
{
	m_VecTargetData.clear();

	BeginWaitCursor();
	
	IplImage* SrcImg = cvLoadImage("D://靶板2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* DstImgaa = cvCloneImage(SrcImg);
	cvFlip(DstImgaa, DstImgaa);
	m_VecTargetData.push_back(DstImgaa);

	double Sita = 0.0;
	for (; Sita <= 33; Sita += 1)
	{
		IplImage* DstImg = cvCloneImage(SrcImg);
		DistortImg(SrcImg, DstImg, CV_PI / 12, Sita * CV_PI / 180, 0, 1/*cos(Sita * CV_PI / 180)*/);
		cvFlip(DstImg, DstImg);
		m_VecTargetData.push_back(DstImg);
	}
	cvReleaseImage(&SrcImg);
	EndWaitCursor();

	if(!m_VecTargetData.empty())
		m_ShowTarget.SetData(m_VecTargetData);

	m_ShowTarget.m_nPage = m_nPage;
	m_ShowTarget.Invalidate(TRUE);

// 	cvNamedWindow("src");
// 	cvShowImage("src", m_VecTargetData[0]);
// 	cvNamedWindow("dst");
// 	cvShowImage("dst", m_VecTargetData[50]);
// 	cvNamedWindow("dstInvert");
// 	cvShowImage("dstInvert", m_VecTargetData[100]);
}

void CDistortionSimulateDlg::OnOPENBAEM()
{
	m_VecBeamData.clear();

	BeginWaitCursor();
	
	IplImage* SrcImg = cvLoadImage("D://光斑.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* DstImgaa = cvCloneImage(SrcImg);
	cvFlip(DstImgaa, DstImgaa);
	m_VecBeamData.push_back(DstImgaa);

	double Sita = 0.0;
	for (; Sita <= 33; Sita += 1)
	{
		IplImage* DstImg = cvCloneImage(SrcImg);
		DistortImg(SrcImg, DstImg, CV_PI / 12, Sita * CV_PI / 180, 0, 1/*cos(Sita * CV_PI / 180)*/);
		cvFlip(DstImg, DstImg);
		m_VecBeamData.push_back(DstImg);
	}
	cvReleaseImage(&SrcImg);
	EndWaitCursor();

	if(!m_VecBeamData.empty())
		m_ShowBeam.SetData(m_VecBeamData);

	m_ShowBeam.m_nPage = m_nPage;
	m_ShowBeam.Invalidate(TRUE);
}

void CDistortionSimulateDlg::DistortImg(IplImage* SrcImg, IplImage* DstImg, double Xsita, double Ysita, double Zsita, double sBeta)
{
	CvMat* Matr = cvCreateMat(1, 3, CV_32FC1);
	CvMat* MatR = cvCreateMat(3, 3, CV_32FC1);

	cvmSet(Matr, 0, 0, Xsita);
	cvmSet(Matr, 0, 1, Ysita);
	cvmSet(Matr, 0, 2, Zsita);

	cvRodrigues2(Matr, MatR);

	cvConvertScale(MatR, MatR, sBeta);

	float a1, a2, a3, a4;
	a1 = cvmGet(MatR, 0, 0);
	a2 = cvmGet(MatR, 0, 1);
	a3 = cvmGet(MatR, 1, 0);
	a4 = cvmGet(MatR, 1, 1);

	CvPoint2D32f* SrcOpt = new CvPoint2D32f[4];
	CvPoint2D32f* DstOpt = new CvPoint2D32f[4];
	SrcOpt[0].x = 10;   SrcOpt[1].x = 50;   SrcOpt[2].x = 10;   SrcOpt[3].x = 50;
	SrcOpt[0].y = 10;   SrcOpt[1].y = 10;   SrcOpt[2].y = 50;   SrcOpt[3].y = 50;

	DstOpt[0].x = a1*SrcOpt[0].x + a2*SrcOpt[0].y; 
	DstOpt[0].y = a3*SrcOpt[0].x + a4*SrcOpt[0].y;

	DstOpt[1].x = a1*SrcOpt[1].x + a2*SrcOpt[1].y; 
	DstOpt[1].y = a3*SrcOpt[1].x + a4*SrcOpt[1].y;

	DstOpt[2].x = a1*SrcOpt[2].x + a2*SrcOpt[2].y; 
	DstOpt[2].y = a3*SrcOpt[2].x + a4*SrcOpt[2].y;

	DstOpt[3].x = a1*SrcOpt[3].x + a2*SrcOpt[3].y; 
	DstOpt[3].y = a3*SrcOpt[3].x + a4*SrcOpt[3].y;

	cvGetPerspectiveTransform(SrcOpt, DstOpt, MatR);
	cvWarpPerspective(SrcImg, DstImg, MatR);

	cvReleaseMat(&Matr);
	cvReleaseMat(&MatR);
	delete[] SrcOpt;
	delete[] DstOpt;
}

void CDistortionSimulateDlg::OnNEXT()
{
	int N = m_VecTargetData.size();
	m_nPage++;
	int k = N / (m_ShowBeam.m_nVcount * m_ShowBeam.m_nHcount);
	if(m_nPage > k)
		m_nPage = k;

	m_ShowTarget.m_nPage = m_nPage;
	m_ShowTarget.Invalidate(TRUE);

	m_ShowBeam.m_nPage = m_nPage;
	m_ShowBeam.Invalidate(TRUE);
}

void CDistortionSimulateDlg::OnPRIOR()
{
	m_nPage--;
	if(m_nPage < 0)
		m_nPage = 0;

	m_ShowTarget.m_nPage = m_nPage;
	m_ShowTarget.Invalidate(TRUE);

	m_ShowBeam.m_nPage = m_nPage;
	m_ShowBeam.Invalidate(TRUE);
}

void CDistortionSimulateDlg::OnSTART()
{
	BeginWaitCursor();
	ProcessImg();
	EndWaitCursor();
}

void CDistortionSimulateDlg::ProcessImg()
{
	int nSum = m_VecTargetData.size();
	CvPoint2D32f TargetOpt, BeamOpt;
	double Xdistance, Ydistance, distance;
	double XSita = CV_PI / 12;
	double YSita = 0; double Sita = 33 * CV_PI / 180.0 / nSum;

	IplImage* pImg = NULL;

	for (int i = 0; i < nSum; i++)
	{
		pImg = cvCloneImage(m_VecTargetData[i]);
		Deal_ImageAnalysis((LPBYTE)pImg->imageData, (LPBYTE)m_VecBeamData[i]->imageData, 
							pImg->width, pImg->height, pImg->widthStep, TargetOpt, BeamOpt);


// 		if(i == 20)
// 			cvSaveImage("D:\\rh.png", pImg);
		
		m_Parameter.CenterOpt = TargetOpt;
		m_Parameter.WeightOpt = BeamOpt;
		
		Xdistance = fabs(TargetOpt.x - BeamOpt.x);
		Ydistance = fabs(TargetOpt.y - BeamOpt.y);
		
		YSita = i * Sita;
		Ydistance = Ydistance / cos(XSita)/* / cos(YSita)*/;
		Xdistance = Xdistance / cos(YSita)/* / cos(YSita)*/;

		distance = sqrtf(Xdistance * Xdistance + Ydistance * Ydistance);
		distance = distance * 645.0 / 545.0 / cos(YSita);
		m_Parameter.Distance = distance;

		m_VecParameter.push_back(m_Parameter);
	}
}

BOOL CDistortionSimulateDlg::Deal_ImageAnalysis(LPBYTE lpImgData, LPBYTE lpLaserSpot, int ImgWidth , int ImgHeight, int LineWidth, CvPoint2D32f& TargetCentre, CvPoint2D32f& LaserSpotCentre)
{
// 	//计算图像每一行存储宽度
	int SavImgWidth = LineWidth;

	LPBYTE lpCopyData = (LPBYTE)new char[SavImgWidth * ImgHeight];
	memcpy(lpCopyData, lpImgData, SavImgWidth * ImgHeight);

	float XSum, YSum, Sum, XSum1, YSum1, Sum1;
	XSum = 0.0f;
	YSum = 0.0f;
	Sum  = 0.0f;
	XSum1 = 0.0f;
	YSum1 = 0.0f;
	Sum1  = 0.0f;
	for (int j = 0; j < ImgHeight; j++)
	{
		for (int i = 0; i < ImgWidth; i++)
		{
			if(lpCopyData[j * SavImgWidth + i] > 200)
			{
				Sum +=  lpCopyData[j * SavImgWidth + i];
				XSum +=  i * lpCopyData[j * SavImgWidth + i];
				YSum +=  j * lpCopyData[j * SavImgWidth + i];
			}
			if (lpLaserSpot[j * SavImgWidth + i] > 5)
			{
				Sum1 +=  lpLaserSpot[j * SavImgWidth + i];
				XSum1 +=  i * lpLaserSpot[j * SavImgWidth + i];
				YSum1 +=  j * lpLaserSpot[j * SavImgWidth + i];
				lpImgData[j * SavImgWidth + i] = lpLaserSpot[j * SavImgWidth + i];
			}

		}
	}
	TargetCentre.x = XSum / Sum + 0.5;
	TargetCentre.y = YSum / Sum + 0.5;
	LaserSpotCentre.x = XSum1 / Sum1 + 0.5;
	LaserSpotCentre.y = YSum1 / Sum1 + 0.5;

	if (lpCopyData != NULL)
	{
		delete[] lpCopyData;
		lpCopyData = NULL;
	}

	return TRUE;

}

void CDistortionSimulateDlg::OnFUSSIONPLAY()
{
//	m_ShowBeam.DestroyWindow();
}

void CDistortionSimulateDlg::OnSAVEDATA()
{
	SaveRequiredData();
}

void CDistortionSimulateDlg::SaveRequiredData()
{
	if(m_VecParameter.empty())
		return;	

	CStdioFile file;
	CFileException ex;
	if (!file.Open(_T("D:\\Data.txt"), CFile::modeWrite|CFile::modeCreate, &ex))
	{
		file.Close();
	}

	CString str;
 	double x1, y1, x2, y2, L;
	
	for (int i = 0; i < m_VecParameter.size(); i++)
	{
		x1 = m_VecParameter[i].CenterOpt.x;
		y1 = m_VecParameter[i].CenterOpt.y;
		x2 = m_VecParameter[i].WeightOpt.x;
		y2 = m_VecParameter[i].WeightOpt.y;
		L = fabs(m_VecParameter[i].Distance - m_VecParameter[0].Distance);
		
		str.Format(_T("第%d组X15Y%d:靶板中心(%.2f, %.2f)光斑质心(%.2f, %.2f)偏差: %.2fcm"), i, i-1, x1, y1, x2, y2, L);
		str += "\r\n";
		file.WriteString(str);
	}

	file.Close();
}