///////////////////////////////////////////////////////////////////
//
//	ModPlayer: Win32 Mod Player using ModPlugin DLL
//
//	Copyright © Samuel Gomes, 2002-2020
//	mailto: v_2samg@hotmail.com || gomes.samuel@gmail.com
//
//////////////////////////////////////////////////////////////////

// MODPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MODPlayer.h"
#include "MODPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// This links in npmod32.dll
#pragma comment (lib, "npmod32")

// CMODPlayerDlg dialog


CMODPlayerDlg::CMODPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMODPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMODPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMODPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPTIONS, OnBnClickedOptions)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPEN, OnBnClickedOpen)
	ON_BN_CLICKED(IDC_PREVIOUS, OnBnClickedPrevious)
	ON_BN_CLICKED(IDC_NEXT, OnBnClickedNext)
	ON_BN_CLICKED(IDC_SHUFFLE, OnBnClickedShuffle)
END_MESSAGE_MAP()


// Creates the ModPlugin object and sets it up with MFC
BOOL CMODPlayerDlg::ModPluginCreate()
{
	CString sArgs;
	COLORREF clrBack;

	// Initialize ModPlugin
	if (m_pMP != NULL) return TRUE;

	// Sync windows background color with ModPlugin
	clrBack = GetSysColor(COLOR_3DFACE);

	// Create an instance of ModPlugin
	sArgs.Format(TEXT(
		"autoload|true|"
		"autonext|false|"
		"autoplay|true|"
		"autostart|true|"
		"bgcolor|#%.2X%.2X%.2X|"
		"controls|stereo|"
		"hidden|false|"
		"loop|false|"
		"shuffle|false|"
		"spcolor|cyan|"
		"spcolorhi|magenta|"
		"title|Ready!|"
		"volume|100|"
		"vucolor|yellow|"
		"vucolorhi|red"),
		(int)LOBYTE(clrBack), (int)HIBYTE(clrBack), (int)LOBYTE(HIWORD(clrBack))
		);
	m_pMP = ModPlug_CreateEx(sArgs);
 
	if (m_pMP == NULL) return FALSE;

	// Attach the plugin to our windows
	if (!ModPlug_SetWindow(m_pMP, m_hWnd)) return FALSE;

	// We need a timer to keep ticking in the background so
	// that we can monitor all ModPlugin DLL's activities
	// Set the timer interval to 500 ms, i.e. 2 events/sec
	m_pTimer = SetTimer(1, 500, NULL);

	return TRUE;
}

// Destroys the ModPlugin object
VOID CMODPlayerDlg::ModPluginDestroy()
{
	// Stop any playback
	ModPlug_Stop(m_pMP);

	// Destroy our background timer
	if (m_pTimer != NULL) {
		KillTimer(m_pTimer);
		m_pTimer = NULL;
	}

	// Destroy ModPlugin
	if (m_pMP != NULL) {
		ModPlug_Destroy(m_pMP);
		m_pMP = NULL;
	}
}

// Loads a new Mod file
BOOL CMODPlayerDlg::ModPluginLoad(const CPath &p)
{
	CString sCaption;

	// Normazile the filename
	((CPath &)p).Canonicalize();

	// Stop any playback
	ModPlug_Stop(m_pMP);

	if (!ModPlug_Load(m_pMP, p)) return FALSE;

	// Set Window caption
	int i = p.FindFileName();
	if (i < 0) i = 0;
	sCaption.Format(TEXT("%s - %s"), theApp.m_pszAppName, p.m_strPath.GetString() + i);
	SetWindowText(sCaption);

	// We max out to 1 to avoid divide by zero errors
	dwModMaxPos = max(ModPlug_GetMaxPosition(m_pMP), 1);
	// We don't need the msecs
	dwModLen = ModPlug_GetSongLength(m_pMP) / 1000;

	return ModPlug_IsReady(m_pMP);
}

// CMODPlayerDlg message handlers
BOOL CMODPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// VIMP: We have to set this to NULL or else ModPluginCreate() will not work
	m_pMP = NULL;
	if (!ModPluginCreate()) return FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CMODPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		// Show an About dialog box using the standard ShellAbout
		CString sExtra;		// extra text
		CString sFormat;
		sFormat.LoadString(IDS_ABOUTEXT);
		if (!sFormat.IsEmpty()) {
			DWORD dwVer = ModPlug_GetVersion();
			sExtra.Format(sFormat, (int)HIBYTE(dwVer), (int)LOBYTE(dwVer));
			ShellAbout(m_hWnd, theApp.m_pszAppName, sExtra, GetIcon(TRUE));
		}
	}
	else
	{
		// The application is closing
		if (nID == SC_CLOSE) {
			// Destroy ModPlugin
			ModPluginDestroy();
		}
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMODPlayerDlg::OnPaint()
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
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMODPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// This method just displays the ModPlugin context menu
// BTW this is a big HACK!
void CMODPlayerDlg::OnBnClickedOptions()
{
	RECT rect1, rect2;
	CButton *myButton = (CButton *)GetDlgItem(IDC_OPTIONS);
	if (myButton == NULL) return;
	myButton->GetWindowRect(&rect2);
	GetWindowRect(&rect1);

	SendMessage(WM_RBUTTONDOWN, 0, MAKELONG(rect2.left - rect1.left, rect2.bottom - rect1.top - 30));
	SendMessage(WM_RBUTTONUP, 0, MAKELONG(rect2.left - rect1.left, rect2.bottom - rect1.top - 30));
}


void CMODPlayerDlg::OnTimer(UINT nIDEvent)
{
	// Do our stuff here
	if (ModPlug_IsPlaying(m_pMP)) {
		DWORD dwModCurTime = (DWORD)((float)dwModLen * ((float)ModPlug_GetCurrentPosition(m_pMP) / (float)dwModMaxPos));
		CString sTime;

		// Format the time
		sTime.Format(TEXT(
			"%.2d:%.2d:%.2d / %.2d:%.2d:%.2d"),
			(int)(dwModCurTime / 3600),
			(int)((dwModCurTime % 3600) / 60),
			(int)((dwModCurTime % 3600) % 60),
			(int)(dwModLen / 3600),
			(int)((dwModLen % 3600) / 60),
			(int)((dwModLen % 3600) % 60)
			);

		SetDlgItemText(IDC_TIME, sTime);
	}
	else {
		// This helps us progress to the next song in the playlist
		if (ModPlug_GetCurrentPosition(m_pMP) >= dwModMaxPos) {
			OnBnClickedNext();
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMODPlayerDlg::OnBnClickedOpen()
{
	BROWSEINFO bi;
	LPITEMIDLIST lpiidl;
	CString sSpec;
	TCHAR sDir[_MAX_PATH];

	sSpec.LoadString(IDS_BROWSEFORFOLDER);

	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = m_hWnd;
	bi.lpszTitle = sSpec;
	bi.ulFlags = BIF_VALIDATE | BIF_RETURNONLYFSDIRS | BIF_DONTGOBELOWDOMAIN | BIF_SHAREABLE | BIF_USENEWUI | BIF_UAHINT;

	lpiidl = SHBrowseForFolder(&bi);

	// Yuck!
	sSpec.Empty();
	ZeroMemory(sDir, sizeof(sDir));
	if (lpiidl != NULL) {
		if (SHGetPathFromIDList(lpiidl, sDir)) {
			sSpec = sDir;
		}
        CoTaskMemFree(lpiidl);
	}

	if (sSpec.IsEmpty() || !PathIsDirectory(sDir)) return;
	PathRemoveBackslash(sDir);

	// Build the playlist
	TCHAR *sExt[] = {TEXT("*.mod"), TEXT("*.mdz"), TEXT("*.s3m"), TEXT("*.s3z"), TEXT("*.xm"), TEXT("*.xmz"), TEXT("*.it"), TEXT("*.itz"), NULL};
	INT x = 0;

	csaPlaylist.RemoveAll();
	while (sExt[x] != NULL) {
		// Create a list of supported files
		intptr_t hFile;
		_finddata_t fd;

		sSpec.Format(TEXT("%s\\%s"), sDir, sExt[x]);
		hFile = _findfirst(sSpec.GetString(), &fd);
		if (hFile == -1) {
			x++;
			continue;
		}
		sSpec.Format(TEXT("%s\\%s"), sDir, fd.name);
		csaPlaylist.Add(sSpec);

		while (_findnext(hFile, &fd) == 0) {
			sSpec.Format(TEXT("%s\\%s"), sDir, fd.name);
			csaPlaylist.Add(sSpec);
		}

		_findclose(hFile);

		x++;
	}

	if (csaPlaylist.GetSize() < 1) {
		sSpec.LoadString(IDS_BROWSENOFILES);
		MessageBox(sSpec, NULL, MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// Reset current song index
	nCurSong = -1;
	OnBnClickedNext();
}

void CMODPlayerDlg::OnBnClickedPrevious()
{
	if (csaPlaylist.GetSize() < 1) return;

	nCurSong--;
	if (nCurSong < 0) nCurSong = csaPlaylist.GetSize() - 1;

	ModPluginLoad(CPath(csaPlaylist[nCurSong]));
	ModPlug_Play(m_pMP);
}

void CMODPlayerDlg::OnBnClickedNext()
{
	if (csaPlaylist.GetSize() < 1) return;

	nCurSong++;
	if (nCurSong >= csaPlaylist.GetSize()) nCurSong = 0;

	ModPluginLoad(CPath(csaPlaylist[nCurSong]));
	ModPlug_Play(m_pMP);
}

void CMODPlayerDlg::OnBnClickedShuffle()
{
	// Check if we have a valid playlist
	if (csaPlaylist.GetSize() <= 1) return;

	// Backup the playlist
	INT_PTR n;
	CStringArray csaPLBackup;
	n = csaPlaylist.GetSize();
	for (INT i = 0; i < n; i++) {
		csaPLBackup.Add(csaPlaylist[i]);
	}

	// Now we suffle the playlist from the backup
	INT_PTR x;
	csaPlaylist.RemoveAll();
	srand((unsigned int)time(NULL));
	for (INT i = 0; i < n; i++) {
		x = rand() % csaPLBackup.GetSize();
		csaPlaylist.Add(csaPLBackup[x]);
		csaPLBackup.RemoveAt(x);
	}

	// Reset current song pointer
	nCurSong = -1;
	OnBnClickedNext();
}
