# BobCosmos: The Solar System written in C + OpenGL + glut
=======

Copyright 2008 João Filho Matos Figueiredo

Simple solar system written in C + openGL + FreeGLUT. 

This project was written in the year 2008 when I was still a student of Computer Science at the Federal University of Paraíba.

Requirements
----
* gcc
* OpenGL
* freeglut3


Compiling
---------

* Install freeglut3 (this will install OpenGL as well.)
* Compile and run :)
* See the commands:

```
    $ sudo apt-get install freeglut3-dev
    $ git clone https://github.com/joaomatosf/BobCosmos.git
    $ cd BobCosmos
    $ gcc -c texture.c
    $ gcc -o solar solar.c texture.o -lglut -lGLU -lGL -lm
    $ ./solar
    
```


Running precompiled
---------

* Install freeglut3 (this will install OpenGL as well.)
* run

```
    $ sudo apt-get install freeglut3-dev
    $ git clone https://github.com/joaomatosf/BobCosmos.git
    $ cd BobCosmos
    $ ./solar
    
```
