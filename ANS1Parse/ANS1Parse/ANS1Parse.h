// ANS1Parse.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CANS1ParseApp:
// �йش����ʵ�֣������ ANS1Parse.cpp
//

class CANS1ParseApp : public CWinApp
{
public:
	CANS1ParseApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CANS1ParseApp theApp;