#pragma once
#include <esdkVc.h>
#include <esdkVcExt.h>
extern CEiris g_eiris;
class CSetup;

#define PID_RAULAND   "pidRaulandServer"
#include "CDlgSetup.h"

#define PROP_URL  "propUrl" 

class CRaulandExt :
    public CEirisExt
{
public:
	CRaulandExt::CRaulandExt();
	void CRaulandExt::UpdateRaulandObj();
	virtual CString GetName() const { return "Rauland2020"; }
	virtual CString GetLicName() const { return "Elpas"; }
	virtual BOOL Init();
	int  CRaulandExt::WriteFile(CString fileName, CString& stData);
	void UpdateBadges(); 
	void UpdateRdrs();
	void CRaulandExt::Startup();

	virtual BOOL OnConstructSetupScreen(long lSetup, int nScreen, HWND hWnd, COLORREF crFill);
	virtual void OnLoadSetupScreen(long lSetup, int nScreen);
	virtual int  OnUnloadSetupScreen(long lSetup, int nScreen);
	virtual void OnEndSetup(long lSetup);
	virtual BOOL OnGetSetupScreenName(EIRISOBJ id, int nScreen, CString& strShortName, CString& strLongName);
	long CRaulandExt::OnStartSetup(EIRISOBJ id);

	CDlgSetup* m_pDlgSetup;
	long m_nAppRauland;
};

class CSetup
{
public:

	CSetup()
	{
		m_hWnd = NULL;
		m_id = EIRIS_ID_NONE;
		m_idCopy = EIRIS_ID_NONE;
	}

	HWND m_hWnd;

	// the original id
	EIRISOBJ m_id;

	// the dup id
	EIRISOBJ m_idCopy;

};
