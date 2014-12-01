// ANS1ParseDlg.cpp : ʵ���ļ�
//

#include  "stdafx.h"
#include  "ANS1Parse.h"
#include  "ANS1ParseDlg.h"
#include  "x509.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define MAX_COLUMN_NUM    12
#define MAX_COLUMN_LENGTH 512+1
#define MAX_SHOW_CHAR     512+1

char ItemName[12][30] =
{
	{"�汾"},
	{"���к�"},
	{"�䷢��"},
	{"ʹ����"},
	{"��Ч�ڴ�"},
	{"��"},
	{"��Կ�㷨"},
	{"��Կģ��E"},
	{"��Կģ��N"},
	{"ǩ��ֵ"},
	{"ǩ���㷨"},
	{"֤�����"}
};
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CANS1ParseDlg �Ի���




CANS1ParseDlg::CANS1ParseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CANS1ParseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CANS1ParseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CANS1ParseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CANS1ParseDlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CANS1ParseDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// CANS1ParseDlg ��Ϣ�������

BOOL CANS1ParseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_listCtrl.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|
		LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
    m_listCtrl.InsertColumn(0, "�ֶ�", LVCFMT_LEFT, 150);
	m_listCtrl.InsertColumn(1, "�ɼ�", LVCFMT_LEFT, 150);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CANS1ParseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CANS1ParseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CANS1ParseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CANS1ParseDlg::ListCtrShow(x509Info* x509_msg)
{

    char pData[MAX_COLUMN_NUM][MAX_COLUMN_LENGTH];
	CString str;


	memset(pData,0, sizeof(pData));

	memcpy(&pData[0][0], x509_msg->version, strlen(x509_msg->version) + 1);
	memcpy(&pData[1][0], x509_msg->serialnumber, strlen(x509_msg->serialnumber) + 1);
	memcpy(&pData[2][0], x509_msg->issuer, strlen(x509_msg->issuer) + 1);
	memcpy(&pData[3][0], x509_msg->subject , strlen(x509_msg->subject ) + 1);
	memcpy(&pData[4][0], x509_msg->notbefore , strlen(x509_msg->notbefore ) + 1);
	memcpy(&pData[5][0], x509_msg->notafter, strlen(x509_msg->notafter) + 1);
	memcpy(&pData[6][0], x509_msg->algFlag, strlen(x509_msg->algFlag) + 1);
	memcpy(&pData[7][0], x509_msg->rs.exponent , strlen(x509_msg->rs.exponent ) + 1);
	memcpy(&pData[8][0], x509_msg->rs.modulus , strlen(x509_msg->rs.modulus ) + 1);
	memcpy(&pData[9][0], x509_msg->rs.signValue, strlen(x509_msg->rs.signValue) + 1);
	memcpy(&pData[10][0], x509_msg->signAlgorithm , strlen(x509_msg->signAlgorithm ) + 1);
	memcpy(&pData[11][0], x509_msg->caflag, strlen(x509_msg->caflag) + 1);


	for(int i = 0; i < sizeof(ItemName) / sizeof(ItemName[0]); i++)
	{
		str = (CString)&ItemName[i][0];
		m_listCtrl.InsertItem(i,str,i);

		str = (CString)&pData[i][0];
		m_listCtrl.SetItemText(i,1, str);
	}


}



void CANS1ParseDlg::GetCertInfo()
{
	CFile fp;	
	if(!(fp.Open((LPCTSTR)m_strFilePath.GetBuffer(m_strFilePath.GetLength()),	//open
		CFile::modeReadWrite | CFile::modeCreate | CFile::modeNoTruncate ))
		)
	{
		MessageBox("Open File Fail");
		return;
	}
	fp.SeekToEnd();					//file pointer to the end
	DWORD fplength = (DWORD)fp.GetLength();	//get file data length
	UCHAR *FileDataBuffer = new UCHAR[fplength * 2 + 1];
	UCHAR *pTempHeader=FileDataBuffer,*pTempTail=FileDataBuffer;
	int i=0;
	memset(FileDataBuffer, 0x00, fplength * 2 + 1);
	fp.SeekToBegin();
	UINT len = fp.Read(FileDataBuffer, fplength);	//read data for data length
	fp.Close();		//close file


	int error_code;
	//CString csMsg;
	signed_x509_certificate certificate;
	SetDlgItemText(IDC_EDIT1, "");
    m_listCtrl.DeleteAllItems(); 
	x509Info x509_msg;

	// now parse it
	init_x509_certificate( &certificate );
	init_x509_msg(&x509_msg);

	if ( !( error_code = parse_x509_certificate( FileDataBuffer, len, &certificate ) ) )
	{
		printf( "X509 Certificate:\n" );
		//display_x509_certificate( &certificate, csMsg);
		display_x509(&certificate, &x509_msg);     


		// Assume it's a self-signed certificate and try to validate it that
		switch ( certificate.algorithm )
		{
		case md5WithRSAEncryption:
		case shaWithRSAEncryption:
			if ( validate_certificate_rsa( &certificate,
				&certificate.tbsCertificate.subjectPublicKeyInfo.rsa_public_key ) )
			{
				printf( "Certificate is a valid self-signed certificate.\n" );
			}
			else
			{
				printf( "Certificate is corrupt or not self-signed.\n" );
			}
			break;
		case shaWithDSA:
			if ( validate_certificate_dsa( &certificate ) )
			{
				printf( "Certificate is a valid self-signed certificate.\n" );
			}
			else
			{
				printf( "Certificate is corrupt or not self-signed.\n" );
			}
		}
	}


	ListCtrShow(&x509_msg);  //��������֤����ʾ���б�ؼ��ϡ�

	free_x509_certificate(&certificate);
	free_x509_msg(&x509_msg);	
}

void CANS1ParseDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	CString lpstrName;
	CString	strFilePath;
	char cLocalDir[1000];
	GetModuleFileName(NULL,   cLocalDir,   sizeof(cLocalDir));	//get local folder path
	CFileDialog	dlgFile(TRUE, NULL, NULL,  OFN_HIDEREADONLY, "Cer Files(*.cer)|*.cer|All Files(*.*)|*.*|| ", NULL);

	dlgFile.m_ofn.lpstrInitialDir = cLocalDir ;
	dlgFile.m_ofn.lpstrTitle =_T("��ѡ���ļ�");

	if (dlgFile.DoModal() == IDOK)
	{
		lpstrName =  dlgFile.GetPathName( ); 
		char PathName[1024  + 1]={0};
		memcpy(PathName,lpstrName,strlen(lpstrName));	//store file path 

		strFilePath.Format((char *)PathName);	//change format
		SetDlgItemText(IDC_EDIT2,strFilePath.GetBuffer(strFilePath.GetLength()));	//show the path
		m_strFilePath=strFilePath;
        
		GetCertInfo();   //����֤������

	}else   
	{  //���������ʾ
	   SetDlgItemText(IDC_EDIT1,"");
       SetDlgItemText(IDC_EDIT2, "");
	   m_listCtrl.DeleteAllItems(); 
	}
}

void CANS1ParseDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString str; 
	char tmp[MAX_SHOW_CHAR];

    for(int i = 0; i < m_listCtrl.GetItemCount(); i++)
	{
      if(m_listCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
	  {
          m_listCtrl.GetItemText(i,1,tmp, MAX_SHOW_CHAR);
		  str = (CString)tmp;
          SetDlgItemText(IDC_EDIT1, str);
	  }
	}

	*pResult = 0;
}
