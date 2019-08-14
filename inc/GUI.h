/*
 * GUI.h
 *
 *  Created on: Sep 27, 2017
 *      Author: robert
 */

#ifndef GUI_H_
#define GUI_H_

#include <string>
#include "../inc/Screen.h"
#include <opencv2/highgui/highgui_c.h> 

class GUI {
public:
	GUI(std::string data_path,std::string WindowName, int posX, int posY);
	virtual ~GUI();

	std::string path;
	int actual_screen;
	bool enable;

	void add_screen(int bg);
	void delete_screen(int number);
	void draw_screen();
	void turnBoxes();

	std::vector<std::unique_ptr<Screen>> screen_vector;
	cv::VideoCapture capture;

private:
	int x_res;
	int y_res;
	std::string WinName;
	double fps;
};

#endif /* GUI_H_ */
