/*
 * GUI.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: robert
 */

#include "../inc/GUI.h"

GUI::GUI(std::string data_path,std::string WindowName,int posX, int posY) {
	this->path=data_path;

	this->actual_screen=-1;
	this->enable=true;
	this->WinName=WindowName;

	cv::namedWindow(this->WinName,CV_WINDOW_NORMAL);
	cv::moveWindow(this->WinName,posX,posY);
	cv::setWindowProperty(this->WinName,CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

void GUI::add_screen()
{
	this->actual_screen++;
	screen_vector.push_back(std::make_unique<Screen>(this->path+"/s"+std::to_string(this->actual_screen),this->x_res,this->y_res,this->WinName));
}

void GUI::delete_screen(int number)
{
	this->screen_vector.erase(this->screen_vector.begin()+number);
}

void GUI::draw_screen()
{
	this->screen_vector[this->actual_screen]->Draw();
}

void GUI::turnBoxes()
{
	this->screen_vector[this->actual_screen]->debug=!this->screen_vector[this->actual_screen]->debug;
}
