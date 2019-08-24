/*
 * Image.cpp
 *
 *  Created on: Oct 20, 2017
 *      Author: robert
 */

#include "../inc/Image.h"
#include <iostream>

Image::Image(std::string path, int x, int y, double resize,std::string id) {
	this->resize=resize;
	this->state=0;
	this->path=path;
	this->x=x;
	this->y=y;

	cv::Mat img=cv::imread(this->path+"_"+std::to_string(this->state)+".png",cv::IMREAD_UNCHANGED);
	this->width=img.cols;
	this->height=img.rows;

	while(img.cols!=0)
	{
		cv::resize(img,img,cv::Size(),resize,resize,1);
		this->img_vector.push_back(img);
		this->state++;
		img=cv::imread(this->path+"_"+std::to_string(this->state)+".png",cv::IMREAD_UNCHANGED);
	}

	this->id=id;
	this->state=0;
    this->active=1;

}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

void Image::draw(cv::Mat bg)
{
	this->copy_transparent(this->img_vector[this->state],bg);
}

void Image::changeValue(int x, int y)
{
	this->state=x;
}

void Image::changeState()
{
	this->state=(this->state+1)%this->img_vector.size();
}

void Image::Reload(std::string name)
{
    this->state=0;
    this->path=name;

    cv::Mat img=cv::imread(this->path+"_"+std::to_string(this->state)+".png",cv::IMREAD_UNCHANGED);
    this->width=img.cols;
    this->height=img.rows;

    this->img_vector.clear();

    while(img.cols!=0)
    {
        cv::resize(img,img,cv::Size(),resize,resize,1);
        this->img_vector.push_back(img);
        this->state++;
        img=cv::imread(this->path+"_"+std::to_string(this->state)+".png",cv::IMREAD_UNCHANGED);
    }

    this->state=0;
}
