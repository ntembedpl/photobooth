/*
 * Control.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: robert
 */

#include "../inc/Control.h"

Control::Control() {
	// TODO Auto-generated constructor stub
	this->blue=0;
	this->red=0;
	this->fan=0;
	this->crio=0;
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

void Control::SetParams(int red,int blue,int fan,int crio)
{
	this->red=red;
	this->blue=blue;
	this->fan=fan;
	this->crio=crio;
}
