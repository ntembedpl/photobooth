/*
 * Control.h
 *
 *  Created on: Jan 21, 2018
 *      Author: robert
 */

#ifndef CONTROL_H_
#define CONTROL_H_

class Control {
public:
	Control();
	virtual ~Control();

	void SetParams(int red,int blue,int fan,int crio);

	int red;
	int blue;
	int fan;
	int crio;
};

#endif /* CONTROL_H_ */
