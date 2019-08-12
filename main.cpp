/*
 * main.cpp
 *
 *  Created on: Jul 31, 2017
 *  Author: robert
 */

#include <iostream>
#include <thread>
#include <string>
#include <memory>
#include <chrono>

#include "inc/Utils.h"
#include "inc/Touch.h"
#include "inc/ConfigReader.h"
#include "inc/Control.h"
#include "inc/Programs.h"

#define FrameTime 40
//#define intro
//#define crioTest

bool touch_flag = false;
bool demoFlag=false;
int demoCounter=0;

bool fan=false;
bool fan_temp=false;
bool arrow=false;

auto config = std::make_unique<ConfigReader>("./data/config");
auto control = std::make_unique<Control>();
auto programs = std::make_unique<Programs>(config->config.custom_program_path,config->config.usbPort);

auto gui2 = std::make_unique<GUI>("./data/Screen2/"+config->config.language,"2",1280,0);
auto gui1 = std::make_unique<GUI>("./data/Screen1/"+config->config.language,"1",0,0);

Touch touch;
bool trackbarFlag=false;

int tim=0;
int HotCold=0;

void touch_callback(int event, int x, int y, int flags, void*) {

	if (event == 1) {

        demoCounter=0;
        if(demoFlag==true)
        {
            demoFlag=false;
            SendFrame(config->config.usbPort,0,0,0,0,0);
        }

        if(touch.id=="trackbar1"||touch.id=="trackbar2")
        {
            trackbarFlag=true;
        }

		touch.n_1 = touch.n;
		touch.id = gui1->screen_vector[gui1->actual_screen]->touch_callback(x, y,
				touch.n);
		touch.x = x;
		touch.y = y;
		touch.previous_event = touch.event;
		touch.event = event;
		touch.screen = gui1->actual_screen;

		if (touch.id != " ") {
			gui1->screen_vector[gui1->actual_screen]->element_vector[touch.n]->pushed =
					true;
		}
	}
	if (event == 4) {

        trackbarFlag = false;

		touch.n_1 = touch.n;
		touch.id = gui1->screen_vector[gui1->actual_screen]->touch_callback(x, y,
				touch.n);
		touch.x = x;
		touch.y = y;
		touch.previous_event = touch.event;
		touch.event = event;
		touch.screen = gui1->actual_screen;

        gui1->screen_vector[gui1->actual_screen]->element_vector[touch.n_1]->pushed =
                false;
        gui1->screen_vector[gui1->actual_screen]->element_vector[touch.n]->pushed =
                false;

     if (touch.id != " ") {
			touch_flag = true;
		}
	}

    if(trackbarFlag==true)
    {
        if(touch.id=="trackbar1") {
            gui1->screen_vector[gui1->actual_screen]->element_vector[6]->changeValue(
                    int((float(x - 320) / 796) * 8), 1);
            HotCold=int((float(x - 320) / 796) * 8);
        }
        if(touch.id=="trackbar2") {
            gui1->screen_vector[gui1->actual_screen]->element_vector[7]->changeValue(
                    int((float(x - 320) / 796) * 7), 1);
            tim=int((float(x - 320) / 796) * 7);
        }
        //std::cout<<"value: "<<int((float(x-240)/800)*9) <<std::endl;
    }
}

void screen0() {
	gui1->add_screen();
	//gui1->screen_vector[gui1->actual_screen]->add_video("/intro", 0, 0, "intro",1280,800);
}

void screen1() {
	gui1->add_screen();

	gui1->screen_vector[gui1->actual_screen]->add_button("/crio", 638, 553, "crio");
	gui1->screen_vector[gui1->actual_screen]->add_button("/hot", 723, 455, "hot");
	gui1->screen_vector[gui1->actual_screen]->add_button("/manual", 569,645,
			"manual");
	gui1->screen_vector[gui1->actual_screen]->add_button("/else", 82, 511, "else");
	gui1->screen_vector[gui1->actual_screen]->add_button("/diag", 1076, 697,
			"diag");
	gui1->screen_vector[gui1->actual_screen]->add_button("/stop", 82,682,
			"stop");

	gui1->screen_vector[gui1->actual_screen]->add_image("/alarm", 1152, 697,
			"alarm");

	gui1->screen_vector[gui1->actual_screen]->add_image("/fan", 84, 400,//!!
			"fan");
	gui1->screen_vector[gui1->actual_screen]->add_image("/red",180, 400,
			"red");
	gui1->screen_vector[gui1->actual_screen]->add_image("/blue", 275, 400,
			"blue");
	gui1->screen_vector[gui1->actual_screen]->add_image("/pr", 1065, 480,//!!
			"pr");

	gui1->screen_vector[gui1->actual_screen]->add_video("/vid", 50, 25, "video", 640, 360, false);
//nowe
	gui1->screen_vector[gui1->actual_screen]->add_button("/pause", 184, 682,
			"pause");

    gui1->screen_vector[gui1->actual_screen]->add_image("/arrow", 385, 397,
                                                         "arrow");

    gui1->screen_vector[gui1->actual_screen]->add_image("/digit", 459, 456,
                                                        "digit1");
    gui1->screen_vector[gui1->actual_screen]->add_image("/digit", 513, 456,
                                                        "digit2");
    gui1->screen_vector[gui1->actual_screen]->add_image("/digit", 459, 521,
                                                        "digit3");
    gui1->screen_vector[gui1->actual_screen]->add_image("/digit", 513, 521,
                                                        "digit4");

}

void screen2() {
	gui1->add_screen();

	gui1->screen_vector[gui1->actual_screen]->add_button("/ret", 87, 600, "ret");
	gui1->screen_vector[gui1->actual_screen]->add_button("/start", 87, 350,
			"start");

	gui1->screen_vector[gui1->actual_screen]->add_button("/minus", 270,
			277, "minus1");
	gui1->screen_vector[gui1->actual_screen]->add_button("/minus", 270,
			481, "minus2");
	gui1->screen_vector[gui1->actual_screen]->add_button("/plus", 1126,  277,
			"plus1");
	gui1->screen_vector[gui1->actual_screen]->add_button("/plus", 1126,  481,
			"plus2");

	gui1->screen_vector[gui1->actual_screen]->add_trackbar("/r1", "/s1", 320,
			202,8, "trackbar1");
	gui1->screen_vector[gui1->actual_screen]->add_trackbar("/r1", "/s2", 320,
			406, 7, "trackbar2");

	//gui1->screen_vector[gui1->actual_screen]->add_image("/hot", 40, y - 165,
	//		"hot");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/cold", 1190, y - 165,
	//		"cold");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/time", 40, y + 135,
	//		"time");

	//gui1->screen_vector[gui1->actual_screen]->add_image("/max", x-440, y - 120, "max1");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/max", x+360, y - 120, "max2");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/5050", x-50, y - 120, "5050");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/7030", x-250, y - 120, "7030");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/3070", x+150, y - 120, "3070");

	//gui1->screen_vector[gui1->actual_screen]->add_image("/5", x-425, y + 180, "5");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/10", x-265, y + 180, "10");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/15", x-105, y + 180, "15");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/20", x+55, y + 180, "20");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/25", x+215, y + 180, "25");
	//gui1->screen_vector[gui1->actual_screen]->add_image("/30", x+375, y + 180, "30");
}

void screen3() {
	gui1->add_screen();

	gui1->screen_vector[gui1->actual_screen]->add_button("/ret", 120, 320, "ret");

//blue
	gui1->screen_vector[gui1->actual_screen]->add_button("/on", 822, 301,
			"on1");
	gui1->screen_vector[gui1->actual_screen]->add_button("/off", 956, 301,
			"off1");
//red
	gui1->screen_vector[gui1->actual_screen]->add_button("/on", 822, 415,
			"on2");
	gui1->screen_vector[gui1->actual_screen]->add_button("/off", 956, 415,
			"off2");

//fan	
	gui1->screen_vector[gui1->actual_screen]->add_button("/on", 822, 190,
			"on3");
	gui1->screen_vector[gui1->actual_screen]->add_button("/off", 956, 190,
			"off3");
//crio
	gui1->screen_vector[gui1->actual_screen]->add_button("/push", 823, 531,
			"push");
	gui1->screen_vector[gui1->actual_screen]->add_button("/reset", 1180, 700,
			"reset");


	gui1->screen_vector[gui1->actual_screen]->add_image("/blue", 738, 313,
			"blue");
	gui1->screen_vector[gui1->actual_screen]->add_image("/red", 738, 422,
			"red");
	gui1->screen_vector[gui1->actual_screen]->add_image("/fan", 730, 214,
			"fan");
	gui1->screen_vector[gui1->actual_screen]->add_image("/crio", 736, 545,
			"crio");
//nowe
	//gui1->screen_vector[gui1->actual_screen]->add_image("/video", 352, 301,
			//"video");//!!
	gui1->screen_vector[gui1->actual_screen]->add_button("/v1", 376, 194,
			"v1");
	gui1->screen_vector[gui1->actual_screen]->add_button("/v2", 531, 194,
			"v2");
	gui1->screen_vector[gui1->actual_screen]->add_button("/v3", 376, 470,
			"v3");
	gui1->screen_vector[gui1->actual_screen]->add_button("/v4", 531, 470,
			"v4");
	gui1->screen_vector[gui1->actual_screen]->add_image("/imgVid", 352, 301, "30");
}

void screen4() {
	gui1->add_screen();

	gui1->screen_vector[gui1->actual_screen]->add_button("/ret", 120, 320, "ret");
	gui1->screen_vector[gui1->actual_screen]->add_button("/pr1", 895, 206,
			"pr1");
	gui1->screen_vector[gui1->actual_screen]->add_button("/pr2",1034 , 206,
			"pr2");
	gui1->screen_vector[gui1->actual_screen]->add_button("/pr3", 895, 335,
			"pr3");
	gui1->screen_vector[gui1->actual_screen]->add_button("/pr4",1034 , 335,
			"pr4");
	gui1->screen_vector[gui1->actual_screen]->add_button("/pr5", 895, 464,
			"pr5");
	gui1->screen_vector[gui1->actual_screen]->add_button("/pr6", 1034, 464,
			"pr6");
}

void screen5() {
	gui2->add_screen();
	//gui2->screen_vector[gui2->actual_screen]->add_video("/intro", 0, 0, "intro",1280,800);
}

void screen6() {
	gui2->add_screen();
	//gui2->screen_vector[gui2->actual_screen]->add_video("/vid", 0, 0, "video", 1280, 800);

    gui2->screen_vector[gui2->actual_screen]->add_image("/blue", 1200, 30,
                                                        "blue");
    gui2->screen_vector[gui2->actual_screen]->add_image("/red", 1100, 30,
                                                        "red");
    gui2->screen_vector[gui2->actual_screen]->add_image("/digit", 580, 630,
                                                        "digit1");
    gui2->screen_vector[gui2->actual_screen]->add_image("/digit", 640, 630,
                                                        "digit2");
    //gui2->screen_vector[gui2->actual_screen]->add_image("/sep", 640, 700,
      //                                                  "separator");
    gui2->screen_vector[gui2->actual_screen]->add_image("/digit", 580, 700,
                                                        "digit3");
    gui2->screen_vector[gui2->actual_screen]->add_image("/digit", 640, 700,
                                                        "digit4");
}

void setClock(int seconds, std::unique_ptr<GUI>&gui)
{
    int minutesDecimal, minutesUnit, secondsDecimal, secondsUnit;

    minutesDecimal=(seconds/60)/10;
    minutesUnit=(seconds/60)%10;

    secondsDecimal=(seconds-((10*minutesDecimal+minutesUnit)*60))/10;
    secondsUnit=(seconds-((10*minutesDecimal+minutesUnit)*60))-(secondsDecimal*10);

	gui->screen_vector[1]->setImage(minutesDecimal,3);
	gui->screen_vector[1]->setImage(minutesUnit,4);
	gui->screen_vector[1]->setImage(secondsDecimal,5);
	gui->screen_vector[1]->setImage(secondsUnit,6);
}

void setClock_2(int seconds, std::unique_ptr<GUI>&gui)
{
    int minutesDecimal, minutesUnit, secondsDecimal, secondsUnit;

    minutesDecimal=(seconds/60)/10;
    minutesUnit=(seconds/60)%10;

    secondsDecimal=(seconds-((10*minutesDecimal+minutesUnit)*60))/10;
    secondsUnit=(seconds-((10*minutesDecimal+minutesUnit)*60))-(secondsDecimal*10);

    gui->screen_vector[1]->setImage(minutesDecimal,14);
    gui->screen_vector[1]->setImage(minutesUnit,15);
    gui->screen_vector[1]->setImage(secondsDecimal,16);
    gui->screen_vector[1]->setImage(secondsUnit,17);
}

void DemoClock()
{
	for(;;) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (demoFlag == false) {
            demoCounter++;

            if(gui1->enable==false){
                demoCounter=0;
            }
#ifdef DEBUG
            std::cout<<demoCounter<<std::endl;
#endif
			if(demoCounter>30&&demoFlag==false)
			{
                SendFrame(config->config.usbPort,0,0,0,0,0);
                demoCounter=0;
				demoFlag=true;
                SendFrame(config->config.usbPort,"Demo");
                gui1->actual_screen = 1;//NEW!!!
            }
		}
	}
}

void Clock()
{
    for(;;) {

        if (gui1->enable == true) {
            //gui2->screen_vector[1]->setImage(0,1);
            //gui2->screen_vector[1]->setImage(0,2);
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        } else {
            if (programs->isEnd == false) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                int time = programs->GetTime();
                if (time >= 0) {
                    //setClock(time, gui2);
                    setClock_2(time,gui1);
                }
                else
                {
                    //setClock(0, gui2);
                    setClock_2(0,gui1);//NEW!!!
                    arrow=false;
                    gui1->screen_vector[gui1->actual_screen]->VideoStart(13);
                }
            }
        }
    }
}

void ProgramTimer()
{
#define SECONDS 10
    for(;;) {
        if (gui1->enable == true) {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        } else {

            gui1->screen_vector[1]->setImage(0, 8);
            gui1->screen_vector[1]->setImage(0, 9);

            //gui2->screen_vector[1]->setImage(0, 1);
            //gui2->screen_vector[1]->setImage(0, 2);

            fan = false;
            if (programs->signals.fan == true) {
                fan = true;
            }
            if (programs->signals.redFuture == true) {
               // gui2->screen_vector[1]->setImage(1, 2);
                gui1->screen_vector[1]->setImage(1, 8);
            }
            if (programs->signals.blueFuture == true) {
                //gui2->screen_vector[1]->setImage(1, 1);
                gui1->screen_vector[1]->setImage(1, 9);
            }
//            if (programs->signals.redFuture == true) {
//                gui2->screen_vector[1]->setImage(1, 2);
//            }
//            if (programs->signals.blueFuture == true) {
//                gui2->screen_vector[1]->setImage(1, 1);
//            }
//            if (programs->signals.redFuture == true) {
//                gui1->screen_vector[1]->setImage(1, 8);
//            }
//            if (programs->signals.blueFuture == true) {
//                gui1->screen_vector[1]->setImage(1, 9);
//            }
#ifdef DEBUG
            std::cout<<"czeka..."<<std::endl;
#endif
            for(int i=0;i<SECONDS*2;i++)
            {
                if (programs->isEnd == false) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
				while(programs->isPause==true);
            }
#ifdef DEBUG
            std::cout<<programs->ActualTime-SECONDS<<std::endl;
#endif

            programs->Refresh();

            fan = false;
            if (programs->signals.fan == true) {
                fan = true;
            }

            for(int i=0;i<SECONDS*2;i++)
            {
                if (programs->isEnd == false) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
				while(programs->isPause==true);
			}
#ifdef DEBUG
            std::cout<<"10 s"<<std::endl;
#endif
           // gui2->screen_vector[1]->setImage(0, 1);
            //gui2->screen_vector[1]->setImage(0, 2);

            if((programs->ActualTime-(SECONDS*2))>0) {
                for (int i = 0; i < (programs->ActualTime - SECONDS*2) * 2; i++) {
                    if (programs->isEnd == false) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
					while(programs->isPause==true);
				}
            }
        }
    }
}

//void ProgramTimer()
//{
//    for(;;) {
//        if (gui1->enable == true) {
//            std::this_thread::sleep_for(std::chrono::microseconds(1));
//        } else {
//
//            for(int i=0;i<(programs->ActualTime-2)*2;i++)
//            {
//                if (programs->isEnd == false) {
//                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//                }
//            }
//
//            if (programs->signals.redFuture == true) {
//                gui2->screen_vector[1]->setImage(1, 2);
//            }
//            if (programs->signals.blueFuture == true) {
//                gui2->screen_vector[1]->setImage(1, 1);
//            }
//
//            for(int i=0;i<4;i++)
//            {
//                if (programs->isEnd == false) {
//                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//                }
//            }
//            //std::this_thread::sleep_for(std::chrono::seconds(2));
//
//            if (programs->isEnd == false) {
//
//                programs->Refresh();
//
//                gui1->screen_vector[1]->setImage(0, 8);
//                gui1->screen_vector[1]->setImage(0, 9);
//
//                gui2->screen_vector[1]->setImage(0, 1);
//                gui2->screen_vector[1]->setImage(0, 2);
//                fan = false;
//
//                if (programs->signals.redActual == true) {
//                    gui1->screen_vector[1]->setImage(1, 8);
//                }
//                if (programs->signals.blueActual == true) {
//                    gui1->screen_vector[1]->setImage(1, 9);
//                }
//                if (programs->signals.fan == true) {
//                    fan = true;
//                }
//            }
//        }
//    }
//}

int main() {

    SendFrame(config->config.usbPort,"Demo");
    int f=system((config->config.scripts+"config.sh").c_str());

	cv::setMouseCallback("1", touch_callback);

	screen0();
	screen1();
	screen2();
	screen3();
	screen4();

	screen5();
	screen6();

	gui1->actual_screen = 0;
	gui2->actual_screen = 0;

#ifdef intro
	//comment to disable intro
    gui1->screen_vector[0]->VideoStart(0);
    gui2->screen_vector[0]->VideoStart(0);
    system(("mplayer -vo null "+gui1->path+"/s0/intro.avi &").c_str());
	while(gui1->screen_vector[gui1->actual_screen]->element_vector[0]->is_end==0)
	{
		std::chrono::steady_clock::time_point begin=std::chrono::steady_clock::now();
		gui1->draw_screen();
		gui2->draw_screen();
		cv::waitKey(1);
		std::chrono::steady_clock::time_point end=std::chrono::steady_clock::now();
		auto count=std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
		if(count<FrameTime)
		{
			cv::waitKey(FrameTime-count);
		}
	}
#endif
	gui1->actual_screen = 1;
	gui2->actual_screen = 1;

    std::thread(ProgramTimer).detach();
    std::thread(Clock).detach();
	std::thread(DemoClock).detach();

    if(config->config.crioVolume<0)
    {
        gui1->screen_vector[1]->setImage(1,6);
    }

    gui1->screen_vector[gui1->actual_screen]->element_vector[5]->active =
            false;
    gui1->screen_vector[gui1->actual_screen]->element_vector[12]->active =
            false;

#ifdef crioTest
	//uncomment to test Crio
	int counter=0;
	while(cv::waitKey(3000)!='x')
	{
		programs->TestCrio();
		counter++;
		std::cout<<"usedCrio: "<<counter<<std::endl;
	}
#endif

    while(1)
{
	std::chrono::steady_clock::time_point begin=std::chrono::steady_clock::now();
	//gui2->draw_screen();

	gui1->draw_screen();

    char key=cv::waitKey(1);
	if(key=='d')
	{
		gui1->turnBoxes();
	}
	else if(key=='a')
	{
		break;
	}

	if(gui1->actual_screen==1&&fan==true&&fan_temp==false)
    {
		gui1->screen_vector[gui1->actual_screen]->change_value(7);
        fan_temp=true;
	}
    if(gui1->actual_screen==1&&fan==false&&fan_temp==true)
    {
        gui1->screen_vector[gui1->actual_screen]->change_value(7);
        fan_temp=false;
    }
    if(arrow==true)
    {
        gui1->screen_vector[gui1->actual_screen]->change_value(13);
    }

	if(touch_flag==true)
	{
		touch_flag=false;
		int signal=main_touch(control,touch,gui1,config);

        if(signal==12)
        {
            gui1->screen_vector[1]->VideoStop(11);
            //gui2->screen_vector[1]->VideoStop(0);

            gui1->screen_vector[gui1->actual_screen]->element_vector[0]->active =
					true;
			gui1->screen_vector[gui1->actual_screen]->element_vector[1]->active =
					true;
			gui1->screen_vector[gui1->actual_screen]->element_vector[2]->active =
					true;
			gui1->screen_vector[gui1->actual_screen]->element_vector[3]->active =
					true;
			gui1->screen_vector[gui1->actual_screen]->element_vector[4]->active =
					true;

            gui1->screen_vector[gui1->actual_screen]->element_vector[5]->active =
                    false;
            gui1->screen_vector[gui1->actual_screen]->element_vector[12]->active =
                    false;

            gui1->enable=true;

            gui1->screen_vector[1]->setImage(0,8);
            gui1->screen_vector[1]->setImage(0,9);

           // gui2->screen_vector[1]->setImage(0,1);
           // gui2->screen_vector[1]->setImage(0,2);

            gui1->screen_vector[1]->setImage(0,10);

            fan=false;
            programs->Stop();
            setClock(0,gui2);
            arrow=false;
            gui1->screen_vector[gui1->actual_screen]->VideoStart(13);
        }

        else if(signal==14)
        {
            gui1->screen_vector[1]->resetVideo(11);
            //gui2->screen_vector[1]->resetVideo(0);
        }

		else if(signal==13)
		{
			programs->Pause();
			gui1->screen_vector[1]->VideoToggle(11);
			//gui2->screen_vector[1]->VideoToggle(0);
            //arrow=!arrow;
		}

        else if((signal>=1&&signal<=11))
        {
            programs->SetProgramID(signal);
            gui1->screen_vector[1]->VideoStart(11);
            //gui2->screen_vector[1]->VideoStart(0);

			gui1->screen_vector[gui1->actual_screen]->element_vector[0]->active =
					false;
			gui1->screen_vector[gui1->actual_screen]->element_vector[1]->active =
					false;
			gui1->screen_vector[gui1->actual_screen]->element_vector[2]->active =
					false;
			gui1->screen_vector[gui1->actual_screen]->element_vector[3]->active =
					false;
			gui1->screen_vector[gui1->actual_screen]->element_vector[4]->active =
					false;

            gui1->screen_vector[gui1->actual_screen]->element_vector[5]->active =
                    true;
            gui1->screen_vector[gui1->actual_screen]->element_vector[12]->active =
                    true;
            gui1->enable=false;

            arrow=true;
        }
	}

    if(programs->isEnd==true&&gui1->enable==false){
        gui1->enable=true;
        programs->Stop();

        gui1->screen_vector[1]->VideoStop(11);
        //gui2->screen_vector[1]->VideoStop(0);

        gui1->screen_vector[1]->setImage(0,10);

        gui1->screen_vector[gui1->actual_screen]->element_vector[0]->active =
                true;
        gui1->screen_vector[gui1->actual_screen]->element_vector[1]->active =
                true;
        gui1->screen_vector[gui1->actual_screen]->element_vector[2]->active =
                true;
        gui1->screen_vector[gui1->actual_screen]->element_vector[3]->active =
                true;
        gui1->screen_vector[gui1->actual_screen]->element_vector[4]->active =
                true;

        gui1->screen_vector[gui1->actual_screen]->element_vector[5]->active =
                false;
        gui1->screen_vector[gui1->actual_screen]->element_vector[12]->active =
                false;
    }

	std::chrono::steady_clock::time_point end=std::chrono::steady_clock::now();
	auto count=std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
	if(count<FrameTime)
	{
		cv::waitKey(FrameTime-count);
	}
	//std::cout<<"fps: "<<1000/double(count)<<std::endl;
}

return 0;
}
