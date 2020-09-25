﻿
// CompareSharpnessDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CompareSharpness.h"
#include "CompareSharpnessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCompareSharpnessDlg 대화 상자



CCompareSharpnessDlg::CCompareSharpnessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMPARESHARPNESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nCropX = 0;
	m_nCropY = 0;
	m_nCropW = 0;
	m_nCropH = 0;

	m_SharpenImg1 = 0.0f;
	m_SharpenImg2 = 0.0f;
	m_SharpenCropedImg1 = 0.0f;
	m_SharpenCropedImg2 = 0.0f;
}

void CCompareSharpnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH_IMG1, m_editPathImg1);
	DDX_Control(pDX, IDC_EDIT_PATH_IMG2, m_editPathImg2);
	DDX_Control(pDX, IDC_STATIC_SHARPEN_IMG1, m_staticSharpenImg1);
	DDX_Control(pDX, IDC_STATIC_SHARPEN_IMG2, m_staticSharpenImg2);
	DDX_Control(pDX, IDC_STATIC_SHARPEN_CROPED_IMG1, m_staticSharpenCropedImg1);
	DDX_Control(pDX, IDC_STATIC_SHARPEN_CROPED_IMG2, m_staticSharpenCropedImg2);
	DDX_Control(pDX, IDC_PC_IMAGE1, m_PcImg1);
	DDX_Control(pDX, IDC_PC_IMAGE2, m_PcImg2);
	DDX_Control(pDX, IDC_EDIT_CROP_X, m_editCropX);
	DDX_Control(pDX, IDC_EDIT_CROP_Y, m_editCropY);
	DDX_Control(pDX, IDC_EDIT_CROP_W, m_editCropW);
	DDX_Control(pDX, IDC_EDIT_CROP_H, m_editCropH);
}

BEGIN_MESSAGE_MAP(CCompareSharpnessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN_IMAGE1, &CCompareSharpnessDlg::OnBnClickedBtnOpenImage1)
	ON_BN_CLICKED(IDC_BTN_OPEN_IMAGE2, &CCompareSharpnessDlg::OnBnClickedBtnOpenImage2)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCompareSharpnessDlg 메시지 처리기

BOOL CCompareSharpnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_PC_IMAGE1)->GetWindowRect(&m_rectPc1);
	ScreenToClient(&m_rectPc1);

	GetDlgItem(IDC_PC_IMAGE2)->GetWindowRect(&m_rectPc2);
	ScreenToClient(&m_rectPc2);

	m_nCalibrationMousePointX = 1280.0 / m_rectPc1.Width();
	m_nCalibrationMousePointY = 720.0 / m_rectPc2.Height();


	CString strTmp;
	strTmp.Format(_T("%d"), m_nCropX);
	m_editCropX.SetWindowText(strTmp);
	strTmp.Format(_T("%d"), m_nCropY);
	m_editCropY.SetWindowText(strTmp);
	strTmp.Format(_T("%d"), m_nCropW);
	m_editCropW.SetWindowText(strTmp);
	strTmp.Format(_T("%d"), m_nCropH);
	m_editCropH.SetWindowText(strTmp);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCompareSharpnessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCompareSharpnessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();		
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCompareSharpnessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCompareSharpnessDlg::GetEditControlValue()
{
	CString strTmp;

	m_editCropX.GetWindowText(strTmp);
	m_nCropX = _ttoi(strTmp);

	m_editCropY.GetWindowText(strTmp);
	m_nCropY = _ttoi(strTmp);

	m_editCropW.GetWindowText(strTmp);
	m_nCropW = _ttoi(strTmp);

	m_editCropH.GetWindowText(strTmp);
	m_nCropH = _ttoi(strTmp);
}

void CCompareSharpnessDlg::OnBnClickedBtnOpenImage1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_originImg1 = LoadImage();	
	m_SharpenImg1 = GetSharpness(m_originImg1);
	
	CString strTmp;
	strTmp.Format(_T("%f"), m_SharpenImg1);

	m_editPathImg1.SetWindowText(strPath);
	m_staticSharpenImg1.SetWindowText(strTmp);
	m_staticSharpenCropedImg1.SetWindowText(_T("000.000"));

	DrawBuff(m_originImg1, IDC_PC_IMAGE1);
}

void CCompareSharpnessDlg::OnBnClickedBtnOpenImage2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_originImg2 = LoadImage();
	m_SharpenImg2 = GetSharpness(m_originImg2);

	CString strTmp;
	strTmp.Format(_T("%f"), m_SharpenImg2);

	m_editPathImg2.SetWindowText(strPath);
	m_staticSharpenImg2.SetWindowText(strTmp);
	m_staticSharpenCropedImg2.SetWindowText(_T("000.000"));

	DrawBuff(m_originImg2, IDC_PC_IMAGE2);
}

Mat CCompareSharpnessDlg::LoadImage()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		strPath = fileDlg.GetPathName();

		Mat image;
		image = imread(CString2string(strPath), IMREAD_UNCHANGED);
		CreateBitmapInfo(image.cols, image.rows, image.channels() * 8);

		return image;
	}
}

void CCompareSharpnessDlg::DrawBuff(Mat frame, int IDC_PC)
{
	if (!frame.empty())
	{
		CClientDC dc(GetDlgItem(IDC_PC));

		CRect rect;
		GetDlgItem(IDC_PC)->GetClientRect(&rect);

		CDC bufDC;
		CBitmap* pOldBitmap, bitmap;

		bufDC.CreateCompatibleDC(&dc);

		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

		pOldBitmap = bufDC.SelectObject(&bitmap);

		bufDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);


		DrawImage(&bufDC, frame, IDC_PC);
		DrawCropRect(&bufDC, frame, IDC_PC);


		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bufDC, 0, 0, SRCCOPY);

		bufDC.SelectObject(pOldBitmap);

		bufDC.DeleteDC();
		bitmap.DeleteObject();
	}
}

void CCompareSharpnessDlg::DrawImage(CDC* pDC, Mat frame, int IDC_PC)
{
	CRect rect;
	GetDlgItem(IDC_PC)->GetClientRect(&rect);

	CreateBitmapInfo(frame.cols, frame.rows, frame.channels() * 8);
	SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
				frame.cols, frame.rows, frame.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CCompareSharpnessDlg::CreateBitmapInfo(int width, int height, int bpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete[]m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = width;
	m_pBitmapInfo->bmiHeader.biHeight = -height;
}


//double CCompareSharpnessDlg::GetSharpness(Mat frame)
//{
//	Mat gray;
//	if (frame.channels() == 4)
//		cvtColor(frame, gray, COLOR_BGRA2GRAY);
//	else if (frame.channels() == 3)
//		cvtColor(frame, gray, COLOR_BGR2GRAY);
//	else
//		gray = frame;
//
//	Mat img_laplacian;	
//
//	Laplacian(gray, img_laplacian, CV_64F);
//	Scalar mean, stddev; // 0:1st channel, 1:2nd channel and 2:3rd channel
//	meanStdDev(img_laplacian, mean, stddev, Mat());
//	double variance = stddev.val[0] * stddev.val[0];
//
//	return variance;
//}

double CCompareSharpnessDlg::GetSharpness(Mat frame)
{
	Mat gray;
	if (frame.channels() == 4)
		cvtColor(frame, gray, COLOR_BGRA2GRAY);
	else if (frame.channels() == 3)
		cvtColor(frame, gray, COLOR_BGR2GRAY);
	else
		gray = frame;

	Mat img_canny;
		
	Canny(gray, img_canny, 255, 175);

	int nCountCanny = countNonZero(img_canny);

	double dSharpness = (double)nCountCanny * 100.0 / ((double)img_canny.cols * (double)img_canny.rows);

	return dSharpness;
}

//double CCompareSharpnessDlg::GetSharpness(Mat frame)
//{
//	Mat gray;
//	if (frame.channels() == 4)
//		cvtColor(frame, gray, COLOR_BGRA2GRAY);
//	else if (frame.channels() == 3)
//		cvtColor(frame, gray, COLOR_BGR2GRAY);
//	else
//		gray = frame;
//
//	Mat img_blur, img_sobel, img_laplacian;
//	blur(gray, img_blur, cv::Size(7, 7));
//	Sobel(img_blur, img_sobel, CV_8U, 1, 1, 3, 1, 0, cv::BORDER_DEFAULT);
//
//	Mat sobel_one = img_sobel.reshape(1);
//	int sum_sobel = sum(sobel_one)[0];
//
//	return (double)(sum_sobel) / (double)(sobel_one.cols);
//}

void CCompareSharpnessDlg::DrawCropRect(CDC* pDC, Mat frame, int IDC_PC)
{
	CRect rect;
	GetDlgItem(IDC_PC)->GetClientRect(&rect);
	
	CPen* pOldPen, pen;
	CBrush* pOldBrush, brush;
	pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	brush.CreateStockObject(NULL_BRUSH);

	pOldPen = pDC->SelectObject(&pen);
	pOldBrush = pDC->SelectObject(&brush);

	pDC->Rectangle(CRect(m_rectStart.x, m_rectStart.y, m_rectEnd.x, m_rectEnd.y));

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	brush.DeleteObject();
	pen.DeleteObject();

	int roiL = (int)(m_rectStart.x * m_nCalibrationMousePointX);
	int roiT = (int)(m_rectStart.y * m_nCalibrationMousePointY);
	int roiR = (int)(m_rectEnd.x * m_nCalibrationMousePointX);
	int roiB = (int)(m_rectEnd.y * m_nCalibrationMousePointY);

	if (roiL > roiR)
	{
		int tmp = roiL;
		roiL = roiR;
		roiR = tmp;
	}
	
	if (roiB < roiT)
	{
		int tmp2 = roiB;
		roiB = roiT;
		roiT = tmp2;
	}

	if (roiL < 0) roiL = 0;
	if (roiL > 1280) roiL = 1280;
	if (roiR > 1280) roiR = 1280;
	if (roiT < 0) roiT = 0;
	if (roiT > 720)roiT = 720;
	if (roiB > 720) roiB = 720;

	/*CString strTmp;

	strTmp.Format(_T("L: %d, T: %d, R: %d, B: %d\n"), roiL, roiT, roiR, roiB);
	OutputDebugString(strTmp);*/
	
	CString strTmp;
	CRect calibratedRect;
	calibratedRect.SetRect(roiL, roiT, roiR, roiB);

	m_nCropX = calibratedRect.left;
	m_nCropY = calibratedRect.top;
	m_nCropW = calibratedRect.Width();
	m_nCropH = calibratedRect.Height();

	strTmp.Format(_T("%d"), m_nCropX);
	m_editCropX.SetWindowText(strTmp);

	strTmp.Format(_T("%d"), m_nCropY);
	m_editCropY.SetWindowText(strTmp);

	strTmp.Format(_T("%d"), m_nCropW);
	m_editCropW.SetWindowText(strTmp);

	strTmp.Format(_T("%d"), m_nCropH);
	m_editCropH.SetWindowText(strTmp);

	
	Mat matCrop;
	matCrop = frame(Rect(m_nCropX, m_nCropY, m_nCropW, m_nCropH)).clone();
	
	if (IDC_PC == IDC_PC_IMAGE1) 
	{
		m_SharpenCropedImg1 = GetSharpness(matCrop);
		strTmp.Format(_T("%f"), m_SharpenCropedImg1);
		m_staticSharpenCropedImg1.SetWindowText(strTmp);
	}
	else
	{
		m_SharpenCropedImg2 = GetSharpness(matCrop);
		strTmp.Format(_T("%f"), m_SharpenCropedImg2);
		m_staticSharpenCropedImg2.SetWindowText(strTmp);
	}
}

void CCompareSharpnessDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_rectPc1.PtInRect(point)) {
		GetCursorPos(&point);
		GetDlgItem(IDC_PC_IMAGE1)->ScreenToClient(&point);
	}

	if (m_rectPc2.PtInRect(point)) {
		GetCursorPos(&point);
		GetDlgItem(IDC_PC_IMAGE2)->ScreenToClient(&point);
	}
	
	/*CString strTmp;
	strTmp.Format(_T("PC1 cord => x: %d, y: %d // Image cord => x: %d, y: %d\n"), point.x, point.y,
		(int) (point.x * m_nCalibrationMousePointX), (int)(point.y * m_nCalibrationMousePointY));
	OutputDebugString(strTmp);*/

	if (nFlags & MK_LBUTTON)
	{
		m_rectEnd = point;
		DrawBuff(m_originImg1, IDC_PC_IMAGE1);
		DrawBuff(m_originImg2, IDC_PC_IMAGE2);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CCompareSharpnessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_rectPc1.PtInRect(point)) {
		GetCursorPos(&point);
		GetDlgItem(IDC_PC_IMAGE1)->ScreenToClient(&point);
	}

	if (m_rectPc2.PtInRect(point)) {
		GetCursorPos(&point);
		GetDlgItem(IDC_PC_IMAGE2)->ScreenToClient(&point);
	}

	m_rectStart = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}