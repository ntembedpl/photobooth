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
	case 4: {
		change = Screen4_callback(control,touch, gui,config);
		break;
	}
	}
	return change;
}

int Screen0_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {
	std::cout << touch.id << std::endl;
	return 0;
}

int Screen1_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {
	if (touch.id == "diag") {
		gui->actual_screen = 3;
		return 0;
	} else if (touch.id == "manual") {
		gui->actual_screen = 2;
		return 0;
	} else if (touch.id == "else") {
		gui->actual_screen = 4;
		return 0;
	}
	else if (touch.id == "hot") {
		gui->screen_vector[1]->setImage(1,10);
		return 1;
	}
	else if (touch.id == "crio") {
		gui->screen_vector[1]->setImage(4,10);
        return 2;
	}
    else if (touch.id == "stop") {
        SendFrame(config->config.usbPort,0,0,0,0,0);
       control->SetParams(0,0,0,0);
        return 12;
    }
    else if (touch.id == "pause") {
        return 13;
    }
	return -1;
}

int Screen2_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {


#define HOT_SATURATION 8
#define TIME_SATURATION 7

	if (touch.id == "ret") {
		gui->actual_screen = 1;
        tim=1;
        HotCold=1;
		return 0;
	}
	else if (touch.id == "start") {
		gui->actual_screen = 1;
		gui->screen_vector[1]->setImage(2,10);
        gui->screen_vector[1]->setImage(0,11);

        tim=std::min(std::max(tim,0),TIME_SATURATION);
        HotCold=std::min(std::max(HotCold,0),HOT_SATURATION);

        PrepareFile(config->config.custom_program_path+"manual",(HotCold+1),(tim+1)*5*60);
        return 3;
	}
	else if (touch.id == "plus1") {
        HotCold+=1;
        HotCold=std::min(std::max(HotCold,0),HOT_SATURATION);

        gui->screen_vector[gui->actual_screen]->element_vector[6]->changeValue(
                HotCold, 1);
		return 0;
	} else if (touch.id == "plus2") {
        tim += 1;
        tim = std::min(std::max(tim, 0), TIME_SATURATION);

        gui->screen_vector[gui->actual_screen]->element_vector[7]->changeValue(
                tim, 1);
        return 0;
    }
    else if (touch.id == "minus1") {
        HotCold-=1;
        HotCold=std::min(std::max(HotCold,0),HOT_SATURATION);

        gui->screen_vector[gui->actual_screen]->element_vector[6]->changeValue(
                HotCold, 1);
        return 0;
    } else if (touch.id == "minus2") {
        tim-=1;
        tim=std::min(std::max(tim,0),TIME_SATURATION);

        gui->screen_vector[gui->actual_screen]->element_vector[7]->changeValue(
                tim, 1);
        return 0;
    }
	return -1;
}

int Screen3_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {

    int static flag=0;
	if (touch.id == "ret") {
		gui->actual_screen = 1;
		SendFrame(config->config.usbPort,0,0,0,0,0);
        control->SetParams(0,0,0,0);
		return 0;
	} else if (touch.id == "on1") {
		control->blue=100;
	}
    else if (touch.id == "v1") {
        //int f=system(("./"+config->config.scripts+"video.sh 0 "+config->config.language).c_str());
        //gui->screen_vector[gui->actual_screen]->element_vector[18]->Reload(gui->screen_vector[gui->actual_screen]->GetPath()+"/imgVid");
        return 14;
    }
    else if (touch.id == "v2") {
        //int f=system(("./"+config->config.scripts+"video.sh 1 "+config->config.language).c_str());
        //gui->screen_vector[gui->actual_screen]->element_vector[18]->Reload(gui->screen_vector[gui->actual_screen]->GetPath()+"/imgVid");
        return 14;
    }
    else if (touch.id == "v3") {
        //int f=system(("./"+config->config.scripts+"video.sh 2 "+config->config.language).c_str());
        //gui->screen_vector[gui->actual_screen]->element_vector[18]->Reload(gui->screen_vector[gui->actual_screen]->GetPath()+"/imgVid");
        return 14;
    }
    else if (touch.id == "v4") {
        //int f=system(("./"+config->config.scripts+"video.sh 3 "+config->config.language).c_str());
        //gui->screen_vector[gui->actual_screen]->element_vector[18]->Reload(gui->screen_vector[gui->actual_screen]->GetPath()+"/imgVid");
        return 14;
    }
    else if (touch.id == "off1") {
		control->blue=0;
	} else if (touch.id == "on2") {
		control->red=100;
	} else if (touch.id == "off2") {
		control->red=0;
	} else if (touch.id == "on3") {
		control->fan=1;
	} else if (touch.id == "off3") {
		control->fan=0;
	} else if (touch.id == "push") {
		control->crio=1;
        config->increaseCrio();
    } else if(touch.id == "reset")
    {
        if(flag==5)
        {
            flag=0;
            gui->actual_screen = 1;
            SendFrame(config->config.usbPort,0,0,0,0,0);
            control->SetParams(0,0,0,0);
            config->resetCrio();
            gui->screen_vector[1]->setImage(0,6);
        }
        else if (flag<5)
        {
            flag++;
        }
    }

	SendFrame(config->config.usbPort,control->blue,control->red,control->fan,control->crio,5);
	control->crio=0;

	return -1;
}

int Screen4_callback(std::unique_ptr<Control>&control,Touch touch, std::unique_ptr<GUI>&gui,std::unique_ptr<ConfigReader>&config) {
	if (touch.id == "ret") {
		gui->actual_screen = 1;
		return 0;
	} else {
		gui->screen_vector[1]->setImage(3,10);
        gui->screen_vector[1]->setImage(0,11);
        gui->actual_screen = 1;
	}

    if(touch.id == "pr1")
    {
        return 4;
    }
    else if(touch.id == "pr2")
    {
        return 5;
    }
    else if(touch.id == "pr3")
    {
        return 6;
    }
    else if(touch.id == "pr4")
    {
        return 7;
    }
    else if(touch.id == "pr5")
    {
        return 8;
    }
    else if(touch.id == "pr6")
    {
        return 9;
    }
    else if(touch.id == "pr7")
    {
        return 10;
    }
    else if(touch.id == "pr8")
    {
        return 11;
    }
	return -1;
}

