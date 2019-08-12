/*
 * Utils.h
 *
 *  Created on: Jan 2, 2018
 *      Author: robert
 */

#ifndef UTILS_H_
#define UTILS_H_


#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

//#define DEBUG

int Initport(int fd);
int OpenPort(std::string port);

void SendFrame(std::string port, int red, int blue, int fan, int crio, int time);
void SendFrame(std::string port, std::string command);

void PrepareFile(std::string path, int HotCold, int time);

extern int HotCold;
extern int tim;

#endif /* UTILS_H_ */
