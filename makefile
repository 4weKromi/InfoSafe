# makefile for InfoSafe
# https://github.com/4weKromi
appName = InfoSafe.exe
CC = g++
ver = c++11
heads = head.h
objects = chooseSet.o interface.o md5.o fileOperate.o main.o
srcs = chooseSet.cpp interface.cpp fileOperate.cpp main.cpp 

build:
	$(CC) -Wall -c $(srcs)hash/md5.cpp -std=$(ver)
	$(CC) -s $(objects) -o $(appName)
clean:
	del $(objects) $(srcs) $(heads)
	del makefile
	rmdir /s /q hash
