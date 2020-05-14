// ModPlugin API Win32 C++ Header & Library
// Copyright © Samuel Gomes (Blade), 2002-2005
// mailto: v_2samg@hotmail.com

#ifndef __NPMOD_H_
#define __NPMOD_H_

#define MP_ENTRY(_type_) extern "C" __declspec(dllimport) _type_ __stdcall

MP_ENTRY (LPVOID)	ModPlug_Create(UINT nArgc, LPSTR sArgn[], LPSTR sArgv[]);
MP_ENTRY (LPVOID)	ModPlug_CreateEx(LPCSTR sArgs);
MP_ENTRY (BOOL)		ModPlug_Destroy(LPVOID pPlugin);
MP_ENTRY (DWORD)	ModPlug_GetCurrentPosition(LPVOID pPlugin);
MP_ENTRY (DWORD)	ModPlug_GetMaxPosition(LPVOID pPlugin);
MP_ENTRY (DWORD)	ModPlug_GetSongLength(LPVOID pPlugin);
MP_ENTRY (DWORD)	ModPlug_GetVersion();
MP_ENTRY (DWORD)	ModPlug_GetVolume(LPVOID pPlugin);
MP_ENTRY (BOOL)		ModPlug_IsPlaying(LPVOID pPlugin);
MP_ENTRY (BOOL)		ModPlug_IsReady(LPVOID pPlugin);
MP_ENTRY (BOOL)		ModPlug_Load(LPVOID pPlugin, LPCSTR sFileName);
MP_ENTRY (BOOL)		ModPlug_Play(LPVOID pPlugin);
MP_ENTRY (BOOL)		ModPlug_SetCurrentPosition(LPVOID pPlugin, DWORD nPos);
MP_ENTRY (BOOL)		ModPlug_SetVolume(LPVOID pPlugin, DWORD nVol);
MP_ENTRY (BOOL)		ModPlug_SetWindow(LPVOID pPlugin, HWND hwnd);
MP_ENTRY (BOOL)		ModPlug_Stop(LPVOID pPlugin);

// ModPlugin mixer flags
#define MPMIX_STEREO 0x1
#define MPMIX_16BIT 0x2
#define MPMIX_DISABLE_OVERSAMPLING 0x10
#define MPMIX_BASS_EXPANSION 0x20
#define MPMIX_DOLBY_SURROUND 0x8
#define MPMIX_DISABLE_AUTOPLAY 0x40

/*
The following two keys contains the ModPlugin settings:
HKEY_CURRENT_USER\Software\Olivier Lapicque\MOD Plugin\Quality
HKEY_CURRENT_USER\Software\Olivier Lapicque\MOD Plugin\Mixing_Rate
*/

#endif
