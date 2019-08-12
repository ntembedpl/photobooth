/*
 * TrackBar.h
 *
 *  Created on: Oct 20, 2017
 *      Author: robert
 */

#ifndef TRACKBAR_H_
#define TRACKBAR_H_

#include "../inc/Element.h"

class TrackBar:public Element {
public:
	TrackBar(std::string radial_path, std::string slider_path, int x, int y, int maxValue, std::string id);
	virtual ~TrackBar();

	void draw(cv::Mat bg);
	void changeState();
	void changeValue(int x, int y);
	void changeValue(int value);
	int getMaxValue();
    void Reload(std::string name);

    bool pushed;

private:
	cv::Mat radial, slider;

	int value, maxValue;
};

#endif /* TRACKBAR_H_ */
