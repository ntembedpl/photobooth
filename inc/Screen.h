/*
 * Screen.h
 *
 *  Created on: Sep 28, 2017
 *      Author: robert
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "../inc/Element.h"
#include "../inc/Button.h"
#include "../inc/TrackBar.h"
#include "../inc/Video.h"
#include "../inc/Image.h"

#define _X 1332
#define _Y 780

class Screen {
public:
	Screen(std::string data_path,int rex_x,int res_y,std::string WindowName);
	virtual ~Screen();

	void add_button(std::string button_path, int x, int y, std::string id);
	void add_trackbar(std::string radial_path,std::string slider_path,
			int x, int y, int maxValue,std::string id);
	void add_video(std::string video_path, int x, int y,std::string id, int res_x=_X, int res_y=_Y, bool rectangle=false);
	void add_image(std::string image_path,int x, int y, std::string id);

	void Draw();

	std::string touch_callback(int x, int y, int& n);

	void trackbarChangeValue(int x,int element);
	void setImage(int x,int element);
	void VideoStart(int element);
	void VideoStop(int element);
    void VideoToggle(int element);

    void change_value(int element);

    void resetVideo(int element);

	std::string GetPath();

    std::vector<std::unique_ptr<Element>> element_vector;

	bool debug;

private:

	std::string path;
	std::string WinName;

	int elements_num;
	void draw_background();
	//void copy_transparent(Button button);

	cv::Mat bg;

	int res_x,res_y;
};

#endif /* SCREEN_H_ */
