/*
 * Screen.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: robert
 */

#include <opencv2/highgui/highgui_c.h>
#include "../inc/Screen.h"

Screen::Screen(std::string data_path,int res_x,int res_y, std::string WindowName,int bg) {

	this->path=data_path;
	if(bg==0) {
		this->bg = cv::imread(this->path + "/bg.png", 1);
	}

	this->elements_num=0;

	this->res_x=res_x;
	this->res_y=res_y;

	this->debug=false;
	this->WinName=WindowName;
	this->img_bg=bg;

}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

void Screen::Draw(cv::Mat frame,double fps)
{
	cv::Mat bg_copy;

	if(this->img_bg==0) {
		bg_copy = this->bg.clone();
	}
	else if(this->img_bg==1)
	{
		cv::resize(frame,frame,cv::Size(1920,1080),0,0,0);
		bg_copy=frame.clone();
	    this->bg=frame.clone();
    }

	for(auto i=0;i<this->element_vector.size();i++)
	{
		this->element_vector[i]->draw(bg_copy);
		if(this->debug)
		{
			this->element_vector[i]->draw_boundingBox(bg_copy);
		}
	}

	cv::putText(bg_copy,std::to_string(fps),cv::Point(30,80),CV_FONT_HERSHEY_COMPLEX,3.0,cv::Scalar(0,255,255),3);
	cv::imshow(WinName,bg_copy);
}

void Screen::draw_background()
{
	this->draw_background();
	cv::imshow(WinName,this->bg);
}

void Screen::add_button(std::string button_path,int x, int y, std::string id)
{
	this->element_vector.push_back(std::make_unique<Button>(this->path+button_path,x,y,id));
}

void Screen::add_image(std::string image_path,int x, int y, std::string id)
{
	this->element_vector.push_back(std::make_unique<Image>(this->path+image_path,x,y,1, id));
}

void Screen::add_trackbar(std::string radial_path,std::string slider_path, int x, int y, int maxValue, std::string id)
{
	this->element_vector.push_back(std::make_unique<TrackBar>(this->path+radial_path, this->path+slider_path, x, y, maxValue, id));
}

void Screen::add_video(std::string video_path, int x, int y,std::string id, int res_x, int res_y,bool rectangle)
{
	this->element_vector.push_back(std::make_unique<Video>(this->path+video_path,x,y,id,res_x,res_y,rectangle));
}

std::string Screen::touch_callback(int x, int y, int& n)
{
	for(auto i=0;i<this->element_vector.size();i++)
	{
		auto offset_x=this->element_vector[i]->x;
		auto offset_y=this->element_vector[i]->y;

		if((x>offset_x&&x<offset_x+this->element_vector[i]->width)
				&&(y>offset_y&&y<offset_y+this->element_vector[i]->height)&&(this->element_vector[i]->active==true))
		{
			n=i;
			return this->element_vector[i]->id;
		}
	}
	return " ";
}

void Screen::trackbarChangeValue(int x,int element)
{
	this->element_vector[element]->changeValue(x,1);
}

void Screen::setImage(int x,int element)
{
    this->element_vector[element]->changeValue(x,1);
}

void Screen::VideoStart(int element)
{
	this->element_vector[element]->changeValue(0,0);
}

void Screen::VideoStop(int element)
{
	this->element_vector[element]->changeValue(1,0);
}

void Screen::VideoToggle(int element)
{
    this->element_vector[element]->changeValue(!this->element_vector[element]->pause,1);
}

void Screen::change_value(int element)
{
	this->element_vector[element]->changeState();
}

void Screen::resetVideo(int element)
{
    this->element_vector[element]->changeState();
}

std::string Screen::GetPath()
{
	return this->path;
}
