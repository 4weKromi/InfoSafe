# makefile for InfoSafe
appName = InfoSafe.exe
CC = g++
ver = c++11
heads = head.h
objects = diskOperate.o interface.o authenticate.o md5.o main.o
srcs = diskOperate.cpp interface.cpp main.cpp hash/md5.cpp authenticate.cpp

build:
	$(CC) -Wall -c $(srcs) -std=$(ver)
	$(CC) -s $(objects) -o $(appName)
clean:
	del $(objects) $(srcs) $(heads)
	del makefile