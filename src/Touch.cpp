/*
 * Touch.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: robert
 */

#include "../inc/Touch.h"
#include "../inc/ConfigReader.h"

int main_touch(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {
	int change = -1;
	switch (touch.screen) {
	case 0: {
		change = Screen0_callback(control,touch, gui, config);
		break;
	}
	case 1: {
		change = Screen1_callback(control,touch, gui,config);
		break;
	}
    case 2: {
        change = Screen2_callback(control,touch, gui,config);
        break;
    }
        case 3: {
            change = Screen3_callback(control,touch, gui,config);
            break;
        }
	}
	return change;
}

int Screen0_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {

    if(touch.id=="authors") {
        gui->actual_screen = 3;
        return 0;
    }
    else if(touch.id=="intro") {
        gui->actual_screen = 1;
        return 0;
    }

    return -1;
}

int Screen1_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {

    if(touch.id=="photo") {
        gui->actual_screen = 2;
        return 1;
    }

    return -1;
}

int Screen2_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {

    return -1;
}

int Screen3_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {

    if(touch.id=="team") {
        gui->actual_screen = 0;
        return 0;
    }

    return -1;
}

