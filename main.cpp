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

int demoCounter = 0;
bool demoFlag = false;
bool touch_flag = false;

auto config = std::make_unique<ConfigReader>("./data/config");
auto control = std::make_unique<Control>();
auto programs = std::make_unique<Programs>(config->config.custom_program_path, config->config.usbPort);

auto gui1 = std::make_unique<GUI>("./data/Screen1/" + config->config.language, "1", 0, 0);

Touch touch;

void touch_callback(int event, int x, int y, int flags, void *) {


    if (event == 1) {

        demoCounter = 0;
        if (demoFlag == true) {
            demoFlag = false;
            SendFrame(config->config.usbPort, 0, 0, 0, 0, 0);
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
}

void screen0() {
    gui1->add_screen(0);
}

void screen1() {
    gui1->add_screen(1);
    //gui1->screen_vector[gui1->actual_screen]->add_video("/vid", 0, 0, "video", 1280, 800, false);
    gui1->screen_vector[gui1->actual_screen]->add_button("/crio", 200, 500, "crio");
    gui1->screen_vector[gui1->actual_screen]->add_button("/hot", 500, 500, "hot");
    gui1->screen_vector[gui1->actual_screen]->add_button("/manual", 800, 500, "manual");
}

void screen2() {
    gui1->add_screen(1);
    gui1->screen_vector[gui1->actual_screen]->add_image("/digit", 500, 500, "digit1");
}


int main() {

    SendFrame(config->config.usbPort, "Demo");
    int f = system((config->config.scripts + "config.sh").c_str());

    cv::setMouseCallback("1", touch_callback);

    screen0();
    screen1();
    screen2();

    gui1->actual_screen = 0;

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


    while (1) {

        gui1->draw_screen();

        char key = cv::waitKey(20);
        if (key == 'd') {
            gui1->turnBoxes();
        } else if (key == 'a') {
            break;
        }

        if (touch_flag == true) {
            touch_flag = false;

        }


    }

    return 0;
}
