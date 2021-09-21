# Projeto-CG - OpenGL Kitchen

[Vídeo AB1](https://youtu.be/iyVwzpTRPTk) \
[Vídeo AB2](https://youtu.be/zxhTEXvyNx4)

# Prerequisites

* C Compiler
* OpenGL and GLUT

# How to build and run

## Linux

### To compile
```bash
gcc -o libs/camera/camera.o -c libs/camera/camera.c && gcc -o libs/draws/draw.o -c libs/draws/draw.c && gcc -o libs/animations/animation.o -c libs/animations/animation.c && gcc -o libs/loader/loader.o -c libs/loader/loader.c && gcc main.c libs/**/*.o -o main.out -lglut -lGL -lGLU -lm
```

### To run
```bash
./main.out
```


## Windows

### To compile
```bash
gcc -o libs/camera/camera.o -c libs/camera/camera.c -I"Your path to \freeglut\include" -L"Your path to \freeglut\lib" -lfreeglut -lopengl32 -lglu32 -lm;
gcc -o libs/draws/draw.o -c libs/draws/draw.c -I"Your path to \freeglut\include" -L"Your path to \freeglut\lib" -lfreeglut -lopengl32 -lglu32 -lm;
gcc -o libs/animations/animation.o -c libs/animations/animation.c -I"Your path to \freeglut\include" -L"Your path to \freeglut\lib" -lfreeglut -lopengl32 -lglu32 -lm;
gcc -o libs/loader/loader.o -c libs/loader/loader.c -I"Your path to \freeglut\include" -L"Your path to \freeglut\lib" -lfreeglut -lopengl32 -lglu32 -lm;
gcc main.c libs/**/*.o -o main.exe -I"Your path to \freeglut\include" -L"Your path to \freeglut\lib" -lfreeglut -lopengl32 -lglu32 -lm
```

### To run
```bash
./main.exe
```

# Objects

- [Free3D](https://free3d.com/)
- [TurboSquid](https://www.turbosquid.com/)
- [cgtrader](https://www.cgtrader.com/)


# Controls

### Movement Controls

- Mouse > Look around
- W, A, S, D > Move Forwards, Left, Backwards and Right _(Capslock cannot be active)_

###  Objects Controls

- 1 > Open and Close the door
- 2 > Open and Close the window
- 3 > Turn on the lamp
- 4 > Turn off the lamp