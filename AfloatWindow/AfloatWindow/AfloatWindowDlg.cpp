
// AfloatWindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AfloatWindow.h"
#include "AfloatWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "gdiplus.h"   
using namespace Gdiplus;  

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAfloatWindowDlg dialog



CAfloatWindowDlg::CAfloatWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAfloatWindowDlg::IDD, pParent),
    mAnimationStep(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAfloatWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAfloatWindowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_NCHITTEST()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CAfloatWindowDlg message handlers

BOOL CAfloatWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    /*
    please see my previous blog.
	CRgn rgn;
    rgn. CreateEllipticRgn(0,0,196,196);
    SetWindowRgn(rgn,TRUE);
    */
    UpdateDisplay(m_pPrime);
    //SetTimer(1,500,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

int CAfloatWindowDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    hFuncInst = LoadLibrary(L"User32.DLL"); 
	BOOL bRet=FALSE;
	if(hFuncInst) 
		UpdateLayeredWindow=(MYFUNC)GetProcAddress(hFuncInst, "UpdateLayeredWindow");
	else
	{
		AfxMessageBox(L"User32.dll ERROR!");
		exit(0);
	}

	// Initialize GDI+.
	m_Blend.BlendOp=0; //theonlyBlendOpdefinedinWindows2000
	m_Blend.BlendFlags=0; //nothingelseisspecial...
	m_Blend.AlphaFormat=1; //...
	m_Blend.SourceConstantAlpha=255;//AC_SRC_ALPHA

    ImageFromIDResource(IDB_PRIME,L"PNG",m_pPrime);
    ImageFromIDResource(IDB_PRIME1,L"PNG",m_pPrime1);
    ImageFromIDResource(IDB_PRIME2,L"PNG",m_pPrime2);
    ImageFromIDResource(IDB_PRIME3,L"PNG",m_pPrime3);
    ImageFromIDResource(IDB_PRIME4,L"PNG",m_pPrime4);
	::SetWindowPos(m_hWnd, HWND_TOPMOST,0,0,240,240,SWP_NOSIZE|SWP_NOMOVE);   
	return 0;
}

void CAfloatWindowDlg::OnDestroy()
{
    if(m_pPrime)
    {
	    delete m_pPrime;
        m_pPrime = NULL;
    }
    if(m_pPrime1)
    {
	    delete m_pPrime1;
        m_pPrime1 = NULL;
    }    
    if(m_pPrime2)
    {
	    delete m_pPrime2;
        m_pPrime2 = NULL;
    }   
    if(m_pPrime3)
    {
	    delete m_pPrime3;
        m_pPrime3 = NULL;
    } 
    if(m_pPrime4)
    {
	    delete m_pPrime4;
        m_pPrime4 = NULL;
    } 

	FreeLibrary(hFuncInst); 
	CDialog::OnDestroy();
}

void CAfloatWindowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

LRESULT CAfloatWindowDlg::OnNcHitTest(CPoint pt)
{
    LRESULT nHitTest = CDialog::OnNcHitTest(pt);
    if(nHitTest == HTCLIENT)
    {
        nHitTest = HTCAPTION;
    }
    return nHitTest;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAfloatWindowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        CDialogEx::OnPaint();

        //ShowPicture();

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAfloatWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAfloatWindowDlg::ShowPicture()
{
    CImage img;    
    HRESULT result = img.Load(_T("prime.png")); 
    
    for(int i = 0; i < img.GetWidth(); i++)  
    {  
        for(int j = 0; j < img.GetHeight(); j++)  
        {  
            unsigned char* pucColor = reinterpret_cast<unsigned char *>(img.GetPixelAddress(i , j));  
            pucColor[0] = pucColor[0] * pucColor[3] / 255;  
            pucColor[1] = pucColor[1] * pucColor[3] / 255;  
            pucColor[2] = pucColor[2] * pucColor[3] / 255;  
        }  
    } 
    
    CDC *pDC = GetWindowDC();
    int nX = img.GetWidth();
    int nY = img.GetHeight();

    img.Draw( pDC->m_hDC,0,0); 
    ReleaseDC( pDC );
}
///resurceID: resource ID
///imgType: type of image
///pImg: pointer to image
BOOL CAfloatWindowDlg::ImageFromIDResource(UINT resurceID,LPCTSTR imgType,Image * &pImg)
{
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(resurceID),imgType); // type
	if (hRsrc)
    {
	    // load resource into memory
	    DWORD len = SizeofResource(hInst, hRsrc);
	    BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	    if (lpRsrc)
        {
            // Allocate global memory on which to create stream
	        HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
	        BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
	        memcpy(pmem,lpRsrc,len);
	        IStream* pstm;
	        CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);
	
	        // load from stream
	        pImg=Gdiplus::Image::FromStream(pstm);

	        // free/release stuff
	        GlobalUnlock(m_hMem);
	        pstm->Release();
	        FreeResource(lpRsrc);
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CAfloatWindowDlg::UpdateDisplay(Image *image, int Transparent)
{
    int imageWidth = 240;
    int imageHeight = 240;//magic number of my image width and height
	HDC hdcTemp=GetDC()->m_hDC;
	m_hdcMemory=CreateCompatibleDC(hdcTemp);
	HBITMAP hBitMap=CreateCompatibleBitmap(hdcTemp,imageWidth,imageHeight);
	SelectObject(m_hdcMemory,hBitMap);
	if(Transparent<0||Transparent>100)	Transparent=100;

	m_Blend.SourceConstantAlpha=int(Transparent*2.55);//1~255, if you want to change transparent, modify this.
	HDC hdcScreen=::GetDC (m_hWnd);
	RECT rct;
	GetWindowRect(&rct);
	POINT ptWinPos={rct.left,rct.top};
	Graphics graph(m_hdcMemory);

	Point points[] = { Point(0, 0), 
		               Point(imageWidth, 0), //width
					   Point(0, imageHeight)//height
					};

    graph.DrawImage(image,points,3);//Do it!

	SIZE sizeWindow={imageWidth,imageHeight};
	POINT ptSrc={0,0};
	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	if((dwExStyle&0x80000)!=0x80000)
		SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle^0x80000);

	BOOL bRet=FALSE;
	bRet= UpdateLayeredWindow( m_hWnd,hdcScreen,&ptWinPos,
				&sizeWindow,m_hdcMemory,&ptSrc,0,&m_Blend,2);
	graph.ReleaseHDC(m_hdcMemory);
	::ReleaseDC(m_hWnd,hdcScreen);
	hdcScreen=NULL;
	::ReleaseDC(m_hWnd,hdcTemp);
	hdcTemp=NULL;
	DeleteObject(hBitMap);
	DeleteDC(m_hdcMemory);
	m_hdcMemory=NULL;
	return bRet;
}

void CAfloatWindowDlg::OnTimer(UINT nIDEvent)
{
    switch (mAnimationStep)
        {
        case 1:
            UpdateDisplay(m_pPrime1);
            break;
        case 2:
            UpdateDisplay(m_pPrime2);
            break;
        case 3:
            UpdateDisplay(m_pPrime3);
            break;
        case 4:
            UpdateDisplay(m_pPrime4);
            mAnimationStep = 0;
            break;
        default:
            break;
        }
    mAnimationStep++;
}

