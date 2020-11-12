// Rauland.h : main header file for the Rauland DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif


#include "resource.h"		// main symbols
#include "CRaulandExt.h"

// CRaulandApp
// See Rauland.cpp for the implementation of this class
//

class CRaulandApp : public CWinApp
{
public:
	CRaulandApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


