
// CompareSharpnessDlg.h: 헤더 파일
//

#pragma once

#include "pch.h"

// CCompareSharpnessDlg 대화 상자
class CCompareSharpnessDlg : public CDialogEx
{
// 생성입니다.
public:
	CCompareSharpnessDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPARESHARPNESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BITMAPINFO* m_pBitmapInfo;

	CStatic m_PcImg1;
	CStatic m_PcImg2;
	CStatic m_staticSharpenImg1;
	CStatic m_staticSharpenImg2;
	CStatic m_staticSharpenCropedImg1;
	CStatic m_staticSharpenCropedImg2;

	CEdit m_editPathImg1;
	CEdit m_editPathImg2;
	CEdit m_editCropX;
	CEdit m_editCropY;
	CEdit m_editCropW;
	CEdit m_editCropH;
	CString strPath;

	CPoint m_rectStart;
	CPoint m_rectEnd;

	Mat m_dislplayImg1;
	Mat m_dislplayImg2;
	Mat m_cropRect1;
	Mat m_cropRect2;
	Mat m_originImg1;
	Mat m_originImg2;
	
	int m_distancePc2Pc;
	double m_Sharpeness;
	
	int m_nCropX;
	int m_nCropY;
	int m_nCropW;
	int m_nCropH;

	double m_nCalibrationMousePointX;
	double m_nCalibrationMousePointY;

	void CreateBitmapInfo(int nWith, int nWeight, int bpp);
	void DisplayImage(Mat frame, int IDC_PC);
	void GetEditControlValue();
	void DisplayCropRect();

	Mat OpenImage();
	double GetSharpness(Mat frame);

	afx_msg void OnBnClickedBtnOpenImage1();
	afx_msg void OnBnClickedBtnOpenImage2();	
	afx_msg void OnBnClickedBtnGetCropSharpen();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
