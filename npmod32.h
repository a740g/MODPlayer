///////////////////////////////////////////////////////////////////
//
//	MOD Plugin API Win32 C++ Header & Library
//
//	Copyright © Samuel Gomes, 2002-2022
//
//////////////////////////////////////////////////////////////////

#ifndef __NPMOD32_H_
#define __NPMOD32_H_

	// This links in npmod32.dll
#pragma comment (lib, "npmod32")

#define MP_ENTRY(_type_) extern "C" __declspec(dllimport) _type_ __stdcall

/*
ModPlugin mixer flags
The following two keys contains the ModPlugin settings:
HKEY_CURRENT_USER\Software\Olivier Lapicque\MOD Plugin\Quality
HKEY_CURRENT_USER\Software\Olivier Lapicque\MOD Plugin\Mixing_Rate
*/
#define MPMIX_STEREO 0x1
#define MPMIX_16BIT 0x2
#define MPMIX_DISABLE_OVERSAMPLING 0x10
#define MPMIX_BASS_EXPANSION 0x20
#define MPMIX_DOLBY_SURROUND 0x8
#define MPMIX_DISABLE_AUTOPLAY 0x40

/*
This function create a plugin, the same way it's done in HTML:
argc is the number of parameters on the command line,
argn is a pointer to an array of pointers to ASCIIZ strings (names of parameters),
and argv is the same thing, but the strings are the values for each parameter.
You should keep the return value to call the other functions.
*/
MP_ENTRY(LPVOID) ModPlug_Create(UINT nArgc, LPSTR sArgn[], LPSTR sArgv[]);

/*
This function is identical to ModPlug_Create, but you can simply use a string,
instead of an array of strings. Each keyword must be separated by a '|' character
(It works also with carriage return).
For example, the command should be sent as "loop|true|vucolor|#ff00ff|".

- volume="x": set the volume of the song to x.
  (Default="100", range="1" to "100")

- loop="true": Loop the song. (Default:"false")

- autostart="true": Start playing the song when loaded.
  (Default="false"). (Also "autoplay" on versions 1.31+)

- autonext="true": Jump to next mod when finished playing.
  (Default="false") This is useful only if you have more
  than one song in your page. (You should use loop="true"
  instead to make the same song loop)

- controls="none"/"stereo":
  * "none": don't display anything - use with care
   because there is no way the user will be able to stop the
   mod (besides exiting the page). (same as "hidden="true")
  * "stereo"(1.65+): the horizontal spectrum analyzer will
   be split for right/left, on each side of the plugin.
   In this case the number of bands will be (width - 184) / 16.
  NOTE (1.75+): The option controls="smallconsole" has been
  removed, it's now automatic if height < 20.

- hidden="true": same as controls="none".

- title="song_title": Displays the text "song_title" when
  the song is not yet loaded. (Default: displays "Loading...")

- shuffle="true" (1.57+): goes along with autonext="true".
  when a song finishes playing, the next song will be randomly
  chosen. The shuffle option is a global flag and should appear
  on the first EMBED section in the page. This flags sets
  the autonext="true" flag automatically.

- bgcolor="black"(default),"gray" (1.60+): Select a background color
  for the plugin.
  v1.75+: you can specify a color like bgcolor="#RRGGBB".

- spcolor="red"(default),"green","blue" (1.61+): Select the color of
  the spectrum analyzer.
  v1.75+: you can specify a color like spcolor="#RRGGBB".

- vucolor="color1", vucolorhi="color2" (1.75+): you can now change
  the color of the VU-meter. The default for vucolor is green, and
  is red for vucolorhi.

- spcolorhi: defines the top-color of the spectrum analyzer (1.75+).
  The default color is red. The middle color will be the mix between
  spcolor and spcolorhi.

- autoload="false" (1.77+): if autoload is "false", the file will not
  start loading unless the user tries to play the mod. The default is
  autoload="true".

- If you want to enable the VU-Meter, the width parameter
  should be set to "168". The VU-Meter cannot be used with
  the controls="smallconsole" option.

- If the plugin is hidden (with controls="none" or hidden commands),
  autostart will be set to "true".

- You can enable the spectrum analyzer by setting a height
  of 96 (bottom spectrum) or a width of 336 (right spectrum).

- v1.61+: You can have from 3 to 80 bands in your right spectrum
  analyzer: set the width parameter to 176+(numbands*8).
  The frequency range is between 86Hz (left) and 11KHz (right).

- v1.65+: With the stereo spectrum, the number of bands on each
  side will be (width - 184) / 16.
*/
MP_ENTRY(LPVOID) ModPlug_CreateEx(LPCSTR sArgs);

/*
This function destroys a plugin created by ModPlug_Create.
pPlugin is the return value from ModPlug_Create.
*/
MP_ENTRY(BOOL) ModPlug_Destroy(LPVOID pPlugin);

/*
This function should be called immediately after ModPlug_Create.
hwnd is the handle of the window where you want the plugin to be.
You are responsible for correctly sizing this window:
the parameters SRC, WIDTH, HEIGHT, ALIGN and BORDER are ignored.
*/
MP_ENTRY(BOOL) ModPlug_SetWindow(LPVOID pPlugin, HWND hwnd);

/*
This function will read a mod file and start to play if you specified autostart=true in the
command line. lpszFileName is the file name, and can be of any type: mod/s3m/mdz/xm...
*/
MP_ENTRY(BOOL) ModPlug_Load(LPVOID pPlugin, LPCSTR sFileName);

/*
This function causes the mod to start playing.
*/
MP_ENTRY(BOOL) ModPlug_Play(LPVOID pPlugin);

/*
This function causes the mod to stop playing.
*/
MP_ENTRY(BOOL) ModPlug_Stop(LPVOID pPlugin);

/*
Returns the version of npmod32.dll.
*/
MP_ENTRY(DWORD) ModPlug_GetVersion();

/*
Returns TRUE is a song is correctly loaded.
*/
MP_ENTRY(BOOL) ModPlug_IsReady(LPVOID pPlugin);

/*
Returns TRUE is the plugin is currently playing a song.
*/
MP_ENTRY(BOOL) ModPlug_IsPlaying(LPVOID pPlugin);

/*
Returns the maximum position of the song.
*/
MP_ENTRY(DWORD) ModPlug_GetMaxPosition(LPVOID pPlugin);

/*
Returns the current playing position. (Between 0 and ModPlug_GetMaxPosition)
*/
MP_ENTRY(DWORD) ModPlug_GetCurrentPosition(LPVOID pPlugin);

/*
Sets the current playing position.
*/
MP_ENTRY(BOOL) ModPlug_SetCurrentPosition(LPVOID pPlugin, DWORD nPos);

/*
Returns the current volume (Between 0 and 100)
*/
MP_ENTRY(DWORD) ModPlug_GetVolume(LPVOID pPlugin);

/*
Sets the current volume (Between 0 and 100)
*/
MP_ENTRY(BOOL) ModPlug_SetVolume(LPVOID pPlugin, DWORD nVol);

/*
Returns the length of the song.
*/
MP_ENTRY(DWORD) ModPlug_GetSongLength(LPVOID pPlugin);

#endif
