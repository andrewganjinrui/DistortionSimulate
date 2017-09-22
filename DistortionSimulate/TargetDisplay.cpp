// TargetDisplay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DistortionSimulate.h"
#include "TargetDisplay.h"


// CTargetDisplay �Ի���

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


// CTargetDisplay ��Ϣ�������

BOOL CTargetDisplay::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
// 	CRect rect;
// 	GetClientRect(rect);
// 	m_nHcount = int(rect.Width() / (WidthShow + 10));
// 	m_nVcount = int(rect.Height()  / (HeightShow + 10));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTargetDisplay::SetData(ImgDataVec& DataVec)
{
	m_pImgDataVec = DataVec;
}

void CTargetDisplay::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
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

				::SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);// ������ʾģʽ		
				::StretchDIBits(dc.GetSafeHdc(),					// �豸�������
					j * (WidthShow + 10),                 //Ŀ��X����
					i * (HeightShow + 10),                  // Ŀ��Y����
					WidthShow,            // Ŀ����
					HeightShow,           // Ŀ��߶�
					0,                // ԴX����
					0,                 // ԴY����
					lWidth,           // Դ���
					lHeight,          // Դ�߶�
					pDibBites,                      // ָ��dib���ص�ָ��
					pInfo,           // ָ��λͼ��Ϣ�ṹ��ָ��
					DIB_RGB_COLORS,                 // ʹ�õ���ɫ��Ŀ
					SRCCOPY);     // ��դ��������
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
	memcpy(lpBmInfo, &BIH, 40);                   //  ����λͼ��Ϣͷ

	if (bits == 8)
	{                           //  256 ɫλͼ
		for (i = 0; i < 256; i++)
		{                                    //  ���ûҽ׵�ɫ��
			ColorTab[i].rgbRed = ColorTab[i].rgbGreen = ColorTab[i].rgbBlue = (BYTE) i;
			ColorTab[i].rgbReserved = 0;
		}
		memcpy(lpBmInfo->bmiColors, ColorTab, 1024);
	}
	return lpBmInfo;
}
