
// ImageLink.h : ImageLink Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CImageLinkApp:
// �йش����ʵ�֣������ ImageLink.cpp
//

class CImageLinkApp : public CWinApp
{
public:
	CImageLinkApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageLinkApp theApp;
