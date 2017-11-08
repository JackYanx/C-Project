
// AfloatWindowDlg.h : header file
//

#pragma once


// CAfloatWindowDlg dialog
class CAfloatWindowDlg : public CDialogEx
{
// Construction
public:
	CAfloatWindowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AFLOATWINDOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg LRESULT OnNcHitTest(CPoint pt);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
private:
    BLENDFUNCTION m_Blend;//important struct
	HDC m_hdcMemory;
	HINSTANCE hFuncInst ;
	typedef BOOL (WINAPI *MYFUNC)(HWND,HDC,POINT*,SIZE*,HDC,POINT*,COLORREF,BLENDFUNCTION*,DWORD);          
	MYFUNC UpdateLayeredWindow;
	Image *m_pPrime;
	Image *m_pPrime1;
	Image *m_pPrime2;
	Image *m_pPrime3;
	Image *m_pPrime4;
    int mAnimationStep;
private:
    void ShowPicture();
	BOOL ImageFromIDResource(UINT nID,LPCTSTR sTR,Image * &pImg);
	BOOL UpdateDisplay(Image *image, int Transparent=255);//param is transparent, you known it.
};
