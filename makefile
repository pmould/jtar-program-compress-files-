# Makefile for building executable client file

echo    = /bin/echo

executable: specFiles linking

specFiles:
	c++ -c file.cpp

linking:
	c++ -o jtar jtar.cpp file.o


