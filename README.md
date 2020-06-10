# MODPlayer
![Screenshot](screenshot.gif)  
Tracker music player (mod, s3m, xm, it) using MOD Plugin playback engine by Olivier Lapicque: https://www.castlex.com/

What you need to compile and use this code:

1. Visual C++ Express 2010 or better.

2. ModPlugin DLL (incuded).

3. MOD Plugin import library and the header files. Created by me.
Creating the header file was easy but the import library was a pain.
The ModPlugin DLL uses the fastcall calling convention but uses cdecl naming convention (doh).
So finally I created an import library using function ordinals.

You can also dynamically load the DLL. But I always like load time linkage (don't ask me why).

As usual, I do not accept responsibility for any effects, adverse or otherwise, that this code may have on you, your computer, your sanity, your dog, and anything else that you can think of. Use it at your own risk. Have fun.