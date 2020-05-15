///////////////////////////////////////////////////////////////////
//
//	ModPlayer: Win32 Mod Player using ModPlugin DLL
//
//	Copyright © Samuel Gomes (Blade), 2002-2020
//	mailto: v_2samg@hotmail.com || gomes.samuel@gmail.com
//
//////////////////////////////////////////////////////////////////

// MODPlayer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMODPlayerApp:
// See MODPlayer.cpp for the implementation of this class
//

class CMODPlayerApp : public CWinApp
{
public:
	CMODPlayerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMODPlayerApp theApp;