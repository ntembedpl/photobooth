/*
 * GUI.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: robert
 */

#include "../inc/GUI.h"
#include <thread>

GUI::GUI(std::string data_path,std::string WindowName,int posX, int posY) {
	this->path=data_path;

	this->actual_screen=-1;
	this->enable=true;
	this->WinName=WindowName;

	cv::namedWindow(this->WinName,CV_WINDOW_NORMAL);
	cv::moveWindow(this->WinName,posX,posY);
	cv::setWindowProperty(this->WinName,CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);

	this->capture=cv::VideoCapture(2);
    this->capture.set(cv::CAP_PROP_FOURCC,cv::VideoWriter::fourcc('M','J','P','G'));
	this->capture.set(cv::CAP_PROP_FRAME_WIDTH,2304);
	this->capture.set(cv::CAP_PROP_FRAME_HEIGHT,1536);
	this->capture.set(cv::CAP_PROP_FPS,60);
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

void GUI::add_screen(int bg)
{
	this->actual_screen++;

		screen_vector.push_back(
				std::make_unique<Screen>(this->path + "/s" + std::to_string(this->actual_screen), this->x_res,
										 this->y_res, this->WinName,bg));
}

void GUI::delete_screen(int number)
{
	this->screen_vector.erase(this->screen_vector.begin()+number);
}

void GUI::draw_screen()
{
	int64 start=cv::getTickCount();

	cv::Mat temp;
	this->capture>>temp;
	this->screen_vector[this->actual_screen]->Draw(temp,this->fps);
	//std::this_thread::sleep_for(std::chrono::milliseconds(2000));


	//if (diff.count() < 20) {
		//cv::waitKey(20 - count);
	//}
	this->fps=cv::getTickFrequency()/(cv::getTickCount()-start);
}

void GUI::turnBoxes()
{
	this->screen_vector[this->actual_screen]->debug=!this->screen_vector[this->actual_screen]->debug;
}
