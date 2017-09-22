// TargetDisplay.cpp : 实现文件
//

#include "stdafx.h"
#include "DistortionSimulate.h"
#include "TargetDisplay.h"


// CTargetDisplay 对话框

IMPLEMENT_DYNAMIC(CTargetDisplay, CDialog)

CTargetDisplay::CTargetDisplay(CWnd* pParent /*=NULL*/)
	: CDialog(CTargetDisplay::IDD, pParent)
{
	m_pImgDataVec.clear();
	m_nPage = 0;
}

CTargetDisplay::~CTargetDisplay()
{
	m_pImgDataVec.clear();
}

void CTargetDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTargetDisplay, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTargetDisplay 消息处理程序

BOOL CTargetDisplay::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
// 	CRect rect;
// 	GetClientRect(rect);
// 	m_nHcount = int(rect.Width() / (WidthShow + 10));
// 	m_nVcount = int(rect.Height()  / (HeightShow + 10));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTargetDisplay::SetData(ImgDataVec& DataVec)
{
	m_pImgDataVec = DataVec;
}

void CTargetDisplay::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	if(m_pImgDataVec.empty())
		return;
	int Num = m_pImgDataVec.size();

	int K = m_nPage * m_nHcount * m_nVcount;
	int n;
	LPBITMAPINFO pInfo = cv_CreatImgInfo(m_pImgDataVec[0]);
	int lHeight = m_pImgDataVec[0]->height;
	int lWidth = m_pImgDataVec[0]->width;

	for (int i = 0; i < m_nVcount; i++)
	{
		for (int j = 0; j < m_nHcount; j++)
		{
			n = K + i * m_nHcount + j;
			if (n < Num)
			{
				LPBYTE pDibBites = (LPBYTE)m_pImgDataVec[n]->imageData;

				::SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);// 设置显示模式		
				::StretchDIBits(dc.GetSafeHdc(),					// 设备环境句柄
					j * (WidthShow + 10),                 //目标X坐标
					i * (HeightShow + 10),                  // 目标Y坐标
					WidthShow,            // 目标宽度
					HeightShow,           // 目标高度
					0,                // 源X坐标
					0,                 // 源Y坐标
					lWidth,           // 源宽度
					lHeight,          // 源高度
					pDibBites,                      // 指向dib像素的指针
					pInfo,           // 指向位图信息结构的指针
					DIB_RGB_COLORS,                 // 使用的颜色数目
					SRCCOPY);     // 光栅操作类型
			}
		}
	}
}

LPBITMAPINFO CTargetDisplay::cv_CreatImgInfo(IplImage* pImg)
{
	if(pImg == NULL)
		return NULL;

	BITMAPINFOHEADER BIH = {40,1,1,1,8,0,0,0,0,0,0};
	LPBITMAPINFO lpBmInfo;
	int          wid, hei, bits, colors, i;
	RGBQUAD  ColorTab[256];
	wid =pImg->width;
	hei =pImg->height;
	bits = pImg->depth * pImg->nChannels;
	if (bits > 8) colors=0;
	else colors = 1<<bits;
	lpBmInfo = (LPBITMAPINFO) malloc(40 + 4*colors);
	BIH.biWidth = wid;
	BIH.biHeight = hei;
	BIH.biBitCount = (BYTE) bits;
	memcpy(lpBmInfo, &BIH, 40);                   //  复制位图信息头

	if (bits == 8)
	{                           //  256 色位图
		for (i = 0; i < 256; i++)
		{                                    //  设置灰阶调色板
			ColorTab[i].rgbRed = ColorTab[i].rgbGreen = ColorTab[i].rgbBlue = (BYTE) i;
			ColorTab[i].rgbReserved = 0;
		}
		memcpy(lpBmInfo->bmiColors, ColorTab, 1024);
	}
	return lpBmInfo;
}
