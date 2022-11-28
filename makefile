# Derek Oda & Seth Ball
# CS 474
# Project 3
# 11/20/2022
# Makefile for Project 3

all: a.exe

a.exe: Project3.c
	gcc Project3.c -o a.exe -lm -lpthread -lrt -mcmodel=large

run: a.exe
	./a.exe

clean: 
	rm -f a.exe