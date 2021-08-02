:: Compile 
:: good as is

:: Main File
g++ -c -o Main.o ..\src\Main.c -I"C:\MinGW\freeglut\include"
:: gcc -c -o Main.o ..\src\Main.c

:: Note Manager
g++ -c -o NoteManager.o ..\src\NoteManager.c -I"C:\MinGW\freeglut\include"
:: gcc -c -o NoteManager.o ..\src\NoteManager.c

:: Image Drawer

copy ..\..\libraries\DrawingTools\ ..\src\
copy ..\libs\upng\ ..\src\upng\

g++ -c -o ImageDrawer.o ..\src\ImageDrawer.c -I"C:\MinGW\freeglut\include"
:: gcc -c -o ImageDrawer.o ..\src\ImageDrawer.h -I"C:\MinGW\freeglut\include"


:: U PNG
g++ -c -o upng.o ..\libs\upng\upng.c
:: gcc -c -o upng.o ..\libs\upng\upng.c

rem Real-Time Audio
:: g++ -c -o RtAudio.o "..\libs\rtaudio\RtAudio.cpp"

g++ -o RythmGame.exe Main.o ImageDrawer.o NoteManager.o upng.o -L"C:\MinGW\freeglut\lib" -lfreeglut -lopengl32 -Wl,--subsystem,windows

RythmGame.exe