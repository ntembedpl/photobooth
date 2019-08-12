//
// Created by studiofigura on 13.02.18.
//

#ifndef OPERATOR_HMI_PROGRAMS_H
#define OPERATOR_HMI_PROGRAMS_H


#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>

#include "../inc/Utils.h"

class Programs {

public:

    Programs(std::string path,std::string port);
    virtual ~Programs();

    std::string ProgramName;
    int ActualTime, FutureTime, OverallTime;
    bool isEnd, isPause;
    int Refresh();

    void SetProgramID(int ID);
    void Stop();
    void Pause();
    void TestCrio();

    int GetTime();

    struct Signals
    {
        bool blueActual;
        bool redActual;
        bool fan;

        bool blueFuture;
        bool redFuture;
    }signals;

private:

    void Parse();
    bool GetActualTime();
    void ClearSignals();
    void SetProgram(std::string path);
    void Debug();

    std::fstream file;
    std::string actualCommand, futureCommand, actualProgram, path, port_;
};


#endif //OPERATOR_HMI_PROGRAMS_H
