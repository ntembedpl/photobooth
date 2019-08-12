/*
 * Video.h
 *
 *  Created on: Oct 20, 2017
 *      Author: robert
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#include "../inc/Element.h"

class Video:public Element {
public:
	Video(std::string path,int x, int y, std::string id, int width, int height, bool rectangle);
	virtual ~Video();

	cv::VideoCapture capture;

	std::string path;

	void draw(cv::Mat bg);
	void changeValue(int x, int y);
	void changeState();
    void resetVideo();
	void Reload(std::string name);


private:

	bool rectangle;
    cv::Mat frame;
};

#endif /* VIDEO_H_ */
