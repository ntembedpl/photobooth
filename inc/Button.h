/*
 * Button.h
 *
 *  Created on: Oct 18, 2017
 *      Author: robert
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include "../inc/Element.h"

class Button:public Element {
public:
	Button(std::string path, int x, int y, std::string id);
	virtual ~Button();

	void draw(cv::Mat bg);
	void changeValue(int x, int y);
	void Reload(std::string name);


private:
	int resize=0;

	void changeState();

	cv::Mat img_u,img_p,img_i;

	std::string path;
};

#endif /* BUTTON_H_ */
