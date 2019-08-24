/*
 * Video.cpp
 *
 *  Created on: Oct 20, 2017
 *      Author: robert
 */

#include "../inc/Video.h"

Video::Video(std::string path,int x, int y, std::string id, int width, int height, bool rectangle) {
	this->x=x;
	this->y=y;
	this->path=path;
	this->state=0;
    this->capture=cv::VideoCapture(this->path+"_"+std::to_string(this->state)+".avi");

	this->width=width;
	this->height=height;

	this->is_end=0;
	this->id=id;

	this->rectangle=rectangle;
    this->pause=0;
	this->capture >> this->frame;
	this->active=1;
}

Video::~Video() {
	// TODO Auto-generated destructor stub
}

void Video::draw(cv::Mat bg)
{
    if(this->pause==0) {
        this->capture >> this->frame;
    }

	if(frame.cols!=0)
	{
		cv::resize(this->frame,this->frame,cv::Size(this->width,this->height),0,0,1);
        this->frame.copyTo(bg(cv::Rect(this->x,this->y,this->frame.cols,this->frame.rows)));
	}
	else
	{
		state++;
		this->capture=cv::VideoCapture(this->path+"_"+std::to_string(this->state)+".mp4");
		this->capture >> this->frame;
		if(this->frame.cols==0)
		{
			state=0;
			this->capture=cv::VideoCapture(this->path+"_"+std::to_string(this->state)+".mp4");
			this->capture >> this->frame;
		}

		cv::resize(this->frame,this->frame,cv::Size(this->width,this->height),0,0,1);
		this->frame.copyTo(bg(cv::Rect(this->x,this->y,this->frame.cols,this->frame.rows)));
	}
	if(rectangle)
	{
		cv::rectangle(bg,cv::Point(this->x,this->y),cv::Point(this->x+this->width,this->y+this->height), cv::Scalar(0,0,0),10);
	}
}

void Video::changeValue(int x, int y)
{
	this->pause=x;
	if(y==0) {
		//this->capture.set(1, 0);
		//this->capture >> this->frame;
	}
}

void Video::changeState()
{
	//this->capture=cv::VideoCapture(0);
	//this->capture >> this->frame;
}

void Video::Reload(std::string name)
{

}
