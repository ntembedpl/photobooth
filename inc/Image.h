/*
 * Image.h
 *
 *  Created on: Oct 20, 2017
 *      Author: robert
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "../inc/Element.h"

class Image:public Element {
public:
	Image(std::string path, int x, int y, double resize,std::string id);
	virtual ~Image();

	void draw(cv::Mat bg);
	void changeState();
	void changeValue(int x, int y);
	void Reload(std::string name);

private:
	int state;

	std::vector<cv::Mat> img_vector;
	std::string path;
};

#endif /* IMAGE_H_ */
