/*
 * Element.h
 *
 *  Created on: Oct 7, 2017
 *      Author: robert
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

class Element {
public:
	Element();
	virtual ~Element();

	int resize, x, y, width, height, is_end, pause;
	bool pushed, active;

	std::string id;

	virtual void draw(cv::Mat bg)=0;
	virtual void changeState()=0;
	virtual void changeValue(int, int)=0;
    virtual void Reload(std::string name)=0;
	//virtual int getMaxValue()=0;


	void copy_transparent(cv::Mat img, cv::Mat bg, int x_offset=0, int y_offset=0);
	void draw_boundingBox(cv::Mat bg);

	bool rectangle;
};

#endif /* ELEMENT_H_ */
