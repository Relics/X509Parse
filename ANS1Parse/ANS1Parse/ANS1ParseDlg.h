// ANS1ParseDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CANS1ParseDlg �Ի���
class CANS1ParseDlg : public CDialog
{
// ����
public:
	CANS1ParseDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CFont m_Font;
// �Ի�������
	enum { IDD = IDD_ANS1PARSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

    CString m_strFilePath;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_edit;
};
