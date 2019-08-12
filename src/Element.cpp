/*
 * Element.cpp
 *
 *  Created on: Oct 7, 2017
 *      Author: robert
 */

#include "../inc/Element.h"
#include <iostream>

Element::Element() {

}

Element::~Element() {

}

void Element::copy_transparent(cv::Mat img, cv::Mat bg, int x_offset, int y_offset)
{
	std::vector<cv::Mat> channels;
	cv::split(img ,channels);

	for(int i=0;i<img.rows;i++)
	{
		for(int j=0;j<img.cols;j++)
		{
			if(channels[3].at<uchar>(i,j)>=50)
			{
				bg.at<cv::Vec3b>(this->y+i+y_offset,this->x+j+x_offset)[0]=img.at<cv::Vec4b>(i,j)[0];
				bg.at<cv::Vec3b>(this->y+i+y_offset,this->x+j+x_offset)[1]=img.at<cv::Vec4b>(i,j)[1];
				bg.at<cv::Vec3b>(this->y+i+y_offset,this->x+j+x_offset)[2]=img.at<cv::Vec4b>(i,j)[2];
				//bg.at<cv::Vec3b>(this->y+i,this->x+j+offset)[3]=img.at<cv::Vec4b>(i,j)[3];
			}
		}
	}
}

void Element::draw_boundingBox(cv::Mat bg)
{
	cv::rectangle(bg,cv::Point(this->x,this->y),cv::Point(this->x+this->width,this->y+this->height), cv::Scalar(0,0,0),2);
}

