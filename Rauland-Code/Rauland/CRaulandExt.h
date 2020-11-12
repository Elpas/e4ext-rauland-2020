#pragma once
#include <esdkVc.h>
#include <esdkVcExt.h>
extern CEiris g_eiris;
class CSetup;



class CRaulandExt :
    public CEirisExt
{
	virtual CString GetName() const { return "Rauland2020"; }
	virtual CString GetLicName() const { return "Elpas"; }
	virtual BOOL Init();


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
