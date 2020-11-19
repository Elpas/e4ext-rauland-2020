#include "pch.h"
#include "CRaulandExt.h"
extern CRaulandExt* g_ext;

enum
{

	// custom setup screens are in the range of 1..100
	SETUP_SETTINGS = 1
	
};

static EirisMsgRtn(OnDbChange)
{

	if (subtype != 0)
		return;


	EIRIS_MSGDATA_DB_CHANGE* pMsg = (EIRIS_MSGDATA_DB_CHANGE*)data;
	int nType = g_eiris.GetObjType(pMsg->id);

	try
	{
		if (!g_eiris.IsController())
			return;


		EIRIS_MSGDATA_DB_CHANGE* pMsg = (EIRIS_MSGDATA_DB_CHANGE*)data;
		CString stPID = g_eiris.GetProgramId(pMsg->id);
		int nType = g_eiris.GetObjType(pMsg->id);

		if (nType == EIRIS_TYPE_BADGE )
		{
			g_ext->UpdateBadges();
		}
		if (stPID == PID_RAULAND)
		{
			g_ext->UpdateRaulandObj();
		}

		if (nType == EIRIS_TYPE_READER)
		{
			g_ext->UpdateRdrs();
		}

		


	}
	catch (...)
	{
		return;
	}




}
#include <direct.h>
#include <fstream>
#include <string> 
int CRaulandExt::WriteFile(CString fileName,CString &stData)
{

		static CString  dataPath = "";
		std::ofstream writeFile;
		writeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		if (dataPath == "")
		{
			CEirisLock lock;
			while (!lock.Lock(1000))
				Sleep(10);
			dataPath = g_eiris.GetDataPath();
			lock.Unlock();
			dataPath += "\\Rauland";
			if (!(CreateDirectory(dataPath, NULL) ||
				ERROR_ALREADY_EXISTS == GetLastError()))
			{
				g_eiris.WriteEngineLog("rauland error creating directory unable to save pulse data");
				dataPath = "";
				return 0;
			}

		}
		try
		{
			static int nFileNum = 0;
			if (nFileNum > 10000000)
				nFileNum = 0;
			CString filename = dataPath +"\\"+ fileName;
			writeFile.open(filename, std::fstream::out);
		
		
			writeFile << stData;
			

			writeFile.close();
		
			return 1;

		}
		catch (std::ofstream::failure& writeErr) {
			CString err = writeErr.what();
			err += "rauland error creating  file for upload ";
			g_eiris.WriteEngineLog(err);

		}
		dataPath = "";
		//WriteDebugLog("Data was uploaded successfully");
		return 0;
	
}
void CRaulandExt::UpdateRaulandObj()
{
	CEirisLock lock;
	while (!lock.Lock())
		Sleep(100);

	CEirisIds ids;
	g_eiris.GetObjsByProgramId(PID_RAULAND, ids);
	if (ids.GetSize() >= 1)
	{
		CString s; 
		g_eiris.GetValue(ids.GetAt(0), PROP_URL, s);
		if(!s.IsEmpty()) 
			m_nAppRauland = ids.GetAt(0);

	}
	m_nAppRauland = 0; 

}
void CRaulandExt::UpdateBadges()
{


	if (!m_nAppRauland)
		return;

	CEirisLock lock;
	while (!lock.Lock())
		Sleep(100);

	CString stFinal = ""; 
	int n=g_eiris.GetBadgeCount();
	for (int i = 0; i < n; i++)
	{
		long id = g_eiris.GetBadgeAt(i); 
		CString  stName; 
		g_eiris.GetValue(id, "Name", stName);
		
		CString json = "{";
		json += '"';
		json += "Name";
		json += '"';
		json += ":";
		json += '"';
		json += stName;
		json += '"';
		json += "}";
				
		
		stFinal += json;
		stFinal += "\n"; 
	}
	lock.Unlock(); 
	WriteFile("rauland_badges.txt" , stFinal); 


}
void CRaulandExt::UpdateRdrs()
{
	if (!m_nAppRauland)
		return;

	CEirisLock lock;
	while (!lock.Lock())
		Sleep(100);

	CString stFinal = "";
	int n = g_eiris.GetReaderCount();
	for (int i = 0; i < n; i++)
	{
		long id = g_eiris.GetReaderAt(i);
		CString  stName;
		g_eiris.GetValue(id, "Name", stName);
		CString json = "{";
		json += '"';
		json += "Name";
		json += '"';
		json += ":";
		json += '"';
		json += stName;
		json += '"';
		json += "}";


		stFinal += json;
		stFinal += "\n";
	}
	lock.Unlock();
	WriteFile("rauland_readers.txt", stFinal);
}
CRaulandExt::CRaulandExt()
{
	g_ext = this;
	m_pDlgSetup = NULL; 
	m_nAppRauland = 0;
}


BOOL CRaulandExt::Init()
{


	EIRIS_PIDINFO info;
	lstrcpy(info.szCategory, "Modules");
	lstrcpy( info.szDisplayName, "Rauland Server" ); 
	lstrcpy(info.szProgramId, PID_RAULAND);


	// specify its capabilities.
	info.nMaxItems = 1;
	info.nMaxTextOuts = 0;
	//info.nIconResourceId = IDI_ICON2;
	info.bLonDevice = FALSE;
	info.bIsMapable = TRUE;
	info.bCanUserAdd = TRUE;
	info.bCanReportTrouble = TRUE;
	info.eType = EIRIS_TYPE_MISC;

	// pass this info to the engine.
	g_eiris.AddPidInfo(&info);

	if (!g_eiris.IsController())
		return TRUE;


	g_eiris.AddMsgHandler(EIRIS_MSG_DB_CHANGE, OnDbChange, (long)this);

	return TRUE;
}


void CRaulandExt::Startup()
{
	if (!g_eiris.IsController())
		return;
	
	UpdateRaulandObj();
	UpdateBadges();
	UpdateRdrs();
}



void CRaulandExt::OnEndSetup(long lSetup)
{

	try
	{
		if (lSetup)
		{

			CSetup* pSetup = (CSetup*)lSetup;
			g_eiris.Release(pSetup->m_idCopy);
			delete pSetup;
		}



	}
	catch (...) {}
}
long CRaulandExt::OnStartSetup(EIRISOBJ id)
{


	CSetup* pSetup = new CSetup;
	pSetup->m_id = id;
	return (long)pSetup;

}

// build UI for setup tab
BOOL CRaulandExt::OnConstructSetupScreen(long lSetup, int nScreen, HWND hWnd, COLORREF crFill)
{
	if (nScreen == SETUP_SETTINGS)
	{
		CSetup* pSetup = (CSetup*)lSetup;
		pSetup->m_hWnd = hWnd;

		// create setup window
		CWnd* pWndParent = CWnd::FromHandle(hWnd);
		m_pDlgSetup = new CDlgSetup();
		//m_pDlgSetup->m_nAppID = pSetup->m_id;
		m_pDlgSetup->Create(m_pDlgSetup->IDD, pWndParent);
		CRect rcParentClient;
		pWndParent->GetClientRect(&rcParentClient);
		m_pDlgSetup->MoveWindow(rcParentClient);

		return TRUE;
	}
	

	return FALSE;
}
BOOL CRaulandExt::OnGetSetupScreenName(EIRISOBJ id, int nScreen, CString& strShortName, CString& strLongName)
{

	CString stPID;
	g_eiris.GetValue(id, "Program", stPID);

	if (stPID == PID_RAULAND)
		if (nScreen == SETUP_SETTINGS)
		{
			strShortName = "Settings ";  
						return TRUE;
		}

	
	return FALSE;


	return CEirisExt::OnGetSetupScreenName(id, nScreen, strShortName, strLongName);

}

void CRaulandExt::OnLoadSetupScreen(long lSetup, int nScreen)
{
	CSetup* pSetup = (CSetup*)lSetup;

	if (nScreen == SETUP_SETTINGS)
	{
		m_pDlgSetup->ShowWindow(SW_SHOW);

		CString s;
		g_eiris.GetValue(pSetup->m_id, PROP_URL, s);

		m_pDlgSetup->m_EditUrl.SetWindowTextA(s);
		

		return;
	}
	


	CEirisExt::OnLoadSetupScreen(lSetup, nScreen);
}

// before moving to next setup tab unload this tab
int CRaulandExt::OnUnloadSetupScreen(long lSetup, int nScreen)
{
	CSetup* pSetup = (CSetup*)lSetup;

	if (nScreen == SETUP_SETTINGS)
	{
		CString s; 
		m_pDlgSetup->m_EditUrl.GetWindowTextA(s);
		g_eiris.SetValue(pSetup->m_id, PROP_URL, s);



	}

	




	return IDYES;
}


