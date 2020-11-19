// CDlgSetup.cpp : implementation file
//

#include "pch.h"
#include "Rauland.h"
#include "CDlgSetup.h"
#include "afxdialogex.h"


// CDlgSetup dialog

IMPLEMENT_DYNAMIC(CDlgSetup, CDialogEx)

CDlgSetup::CDlgSetup(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETUP, pParent)
{

}

CDlgSetup::~CDlgSetup()
{
}

void CDlgSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_EditUrl);
}


BEGIN_MESSAGE_MAP(CDlgSetup, CDialogEx)
END_MESSAGE_MAP()


// CDlgSetup message handlers
