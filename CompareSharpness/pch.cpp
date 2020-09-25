// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

std::string CString2string(CString str)
{
	CT2CA pszConvertedAnsiString(str);
	return std::string(pszConvertedAnsiString);
}

#if defined(_DEBUG)
#pragma comment(lib,"../lib/opencv_core420d.lib")
#pragma comment(lib,"../lib/opencv_highgui420d.lib")
#pragma comment(lib,"../lib/opencv_imgcodecs420d.lib")
#pragma comment(lib,"../lib/opencv_imgproc420d.lib")
#pragma comment(lib,"../lib/opencv_video420d.lib")
#pragma comment(lib,"../lib/opencv_videoio420d.lib")

#else
#pragma comment(lib,"../lib/opencv_core420.lib")
#pragma comment(lib,"../lib/opencv_highgui420.lib")
#pragma comment(lib,"../lib/opencv_imgcodecs420.lib")
#pragma comment(lib,"../lib/opencv_imgproc420.lib")
#pragma comment(lib,"../lib/opencv_video420.lib")
#pragma comment(lib,"../lib/opencv_videoio420.lib")
#endif

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.
