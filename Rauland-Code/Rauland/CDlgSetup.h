#pragma once
#include "resource.h"
#include <afxdialogex.h>


// CDlgSetup dialog

class CDlgSetup : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetup)

public:
	CDlgSetup(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgSetup();

// Dialog Data

	enum { IDD = IDD_DIALOG_SETUP };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditUrl;
};
