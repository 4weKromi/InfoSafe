# makefile for InfoSafe
appName = InfoSafe.exe
CC = g++
ver = c++11
heads = head
objects = diskOperate.o interface.o main.o
srcs = diskOperate.cpp interface.cpp main.cpp

build:
	$(CC) -Wall -c $(srcs) -std=$(ver)
	$(CC) -s $(objects) -o $(appName)
clean:
	del $(objects) $(srcs) $(heads)
	del makefile