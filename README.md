# MODPlayer
![Screenshot](screenshot.gif)  
Tracker music player (mod, s3m, xm, it) using MOD Plugin playback engine by Olivier Lapicque: https://www.castlex.com/

What you need to compile and use this code:

1. Visual Studio 2019 Community or better

2. MOD Plugin DLL (incuded)

3. MOD Plugin import library and the header file created by me.
Creating the header file was easy but the import library was a pain.
The MOD Plugin DLL uses the fastcall calling convention but uses cdecl naming convention.
So finally I created an import library using function ordinals

You can also dynamically load the DLL. But I always like load time linkage to keep things simple.

As usual, I do not accept responsibility for any effects, adverse or otherwise, that this code may have on you, your computer, your sanity, your dog, and anything else that you can think of. Use it at your own risk. Have fun.