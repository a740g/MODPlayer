///////////////////////////////////////////////////////////////////
//
//	ModPlayer: Win32 Mod Player using ModPlugin DLL
//
//	Copyright © Samuel Gomes (Blade), 2002-2020
//	mailto: v_2samg@hotmail.com || gomes.samuel@gmail.com
//
//////////////////////////////////////////////////////////////////

// MODPlayer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MODPlayer.h"
#include "MODPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMODPlayerApp

BEGIN_MESSAGE_MAP(CMODPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMODPlayerApp construction

CMODPlayerApp::CMODPlayerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMODPlayerApp object

CMODPlayerApp theApp;


// CMODPlayerApp initialization

BOOL CMODPlayerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	CMODPlayerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

