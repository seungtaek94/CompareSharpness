
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

	UINT m_radioShrapenMethod; // 0 = Canny, 1 = Sobel, else = Laplacian

	CString m_strImgPath;

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

	CPoint m_rectStart;
	CPoint m_rectEnd;

	Mat m_originImg1;
	Mat m_originImg2;
	Mat m_CropImg1;
	Mat m_CropImg2;

	CRect m_rectPc1;
	CRect m_rectPc2;

	double m_SharpenImg1;
	double m_SharpenImg2;
	double m_SharpenCropedImg1;
	double m_SharpenCropedImg2;
	
	int m_nCropX;
	int m_nCropY;
	int m_nCropW;
	int m_nCropH;
	int m_nImgW;
	int m_nImgH;

	double m_nPointCalibrationPc2ImgX;
	double m_nPointCalibrationPc2ImgY;

	void GetImagePath();	
	void CreateBitmapInfo(int nWith, int nWeight, int bpp);
	void DrawBuff(Mat frame, int IDC_PC);
	void DrawImage(CDC* pDC, Mat frame, int IDC_PC);
	void DrawCropRect(CDC* pDC, Mat frame, int IDC_PC);	
	void GetEditControlValue();
	double GetSharpness(Mat frame);
	Mat LoadImage(CString imagePath);

	afx_msg void OnBnClickedBtnOpenImage1();
	afx_msg void OnBnClickedBtnOpenImage2();	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void RadioButtonClick(UINT ID);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
