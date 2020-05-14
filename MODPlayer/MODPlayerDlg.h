///////////////////////////////////////////////////////////////////
//
//	ModPlayer: Win32 Mod Player using ModPlugin DLL
//
//	Copyright (c) Samuel Gomes (Blade), 1998-2005
//	mailto: v_2samg@hotmail.com || gomes.samuel@gmail.com
//
///////////////////////////////////////////////////////////////////

// MODPlayerDlg.h : header file
//

#pragma once


// CMODPlayerDlg dialog
class CMODPlayerDlg : public CDialogEx
{
// Construction
public:
	CMODPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MODPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	LPVOID m_pMP;						// ModPlugin handle
	UINT_PTR m_pTimer;					// Window timer
	DWORD dwModMaxPos, dwModLen;		// Song length
	CStringArray csaPlaylist;			// Song playlist
	INT_PTR nCurSong;					// Current song in the playlist

	// Custom dialog methods
	BOOL ModPluginCreate();				// Created an instance of ModPlugin
	VOID ModPluginDestroy();			// Destroys the instance of ModPlugin
	BOOL ModPluginLoad(const CPath &p);	// Load a MOD file

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOptions();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedPrevious();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedShuffle();
};
