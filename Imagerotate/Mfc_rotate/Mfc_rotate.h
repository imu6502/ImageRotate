
// Mfc_rotate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMfc_rotateApp:
// �йش����ʵ�֣������ Mfc_rotate.cpp
//

class CMfc_rotateApp : public CWinApp
{
public:
	CMfc_rotateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMfc_rotateApp theApp;