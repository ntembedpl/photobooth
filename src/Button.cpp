/*
 * Button.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: robert
 */

#include "../inc/Button.h"

#include <iostream>

Button::Button(std::string path,int x, int y, std::string id) {

	this->pushed=0;
	this->active=1;
	this->path=path;
	this->img_u=cv::imread(this->path+"_"+std::to_string(this->pushed)+".png",cv::IMREAD_UNCHANGED);
	this->img_p=cv::imread(this->path+"_"+std::to_string(!this->pushed)+".png",cv::IMREAD_UNCHANGED);
	this->img_i=cv::imread(this->path+"_"+std::to_string(2)+".png",cv::IMREAD_UNCHANGED);

	this->x=x;
	this->y=y;

	this->width=this->img_p.cols;
	this->height=this->img_p.rows;

	this->id=id;
	this->pushed=false;
}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

void Button::draw(cv::Mat bg)
{
	if(this->active==0)
	{
		this->copy_transparent(this->img_i,bg);
	}
	else if(pushed)
	{
		this->copy_transparent(this->img_p,bg);
	}
	else
	{
		this->copy_transparent(this->img_u,bg);
	}
}

void Button::changeValue(int x, int y)
{

}

void Button::changeState()
{

}

void Button::Reload(std::string name)
{

}
