//
// Created by studiofigura on 13.02.18.
//

#include "../inc/Programs.h"

Programs::Programs(std::string path, std::string port)
{
    this->path=path;
    this->port_=port;
    this->isEnd=true;
    this->isPause=false;
    this->ActualTime=10;

    this->actualCommand="";
    this->futureCommand="";
    this->ClearSignals();
}

Programs::~Programs() {}

void Programs::ClearSignals()
{
    this->signals.blueActual=false;
    this->signals.redActual=false;
    this->signals.fan=false;

    this->signals.redFuture=false;
    this->signals.blueFuture=false;
}

bool Programs::GetActualTime()
{
        std::string line;
        getline(this->file, line);

        if (line == "") {
            return false;
        } else {
            this->ActualTime = std::stoi(line);
            return true;
        }
}

void Programs::Debug()
{
    std::cout<<"time: "<<this->ActualTime<<std::endl;
    std::cout<<"actual: " << this->actualCommand << std::endl;
    std::cout<<"future: " << this->futureCommand << std::endl;
}

int Programs::Refresh()
{
    if(this->isPause==false) {
        if (this->GetActualTime() == false) {
            this->actualCommand = this->futureCommand;
            this->Parse();
            if(this->actualCommand!="") {
                SendFrame(this->port_, this->actualCommand);
            }

            this->isEnd = true;
            this->file.close();

#ifdef DEBUG
            this->Debug();
#endif
            return 0;
        }

        this->actualCommand = this->futureCommand;
        getline(this->file, this->futureCommand);

        this->Parse();
        SendFrame(this->port_, this->actualCommand);
#ifdef DEBUG
        this->Debug();
#endif
    }
}

void Programs::SetProgram(std::string path)
{
    this->isEnd=false;
    std::cout<<path;

    this->file.open(path);

    std::string line;
    getline(this->file,line);
    std::cout<<line<<std::endl;
    this->OverallTime=std::stoi(line);

    this->isPause=false;

    this->Refresh();

    SendFrame(this->port_, "NASTAWA000-05:050-5:0:0");
}
void Programs::Stop()
{
    this->isEnd=true;
    this->file.close();
    this->OverallTime=0;
    this->ActualTime=10;

    this->actualCommand="";
    this->futureCommand="";

    this->ClearSignals();
}

void Programs::Pause()
{
    this->isPause=!this->isPause;
}

void Programs::Parse()
{
    this->ClearSignals();
    int red,blue,fan,t1,t2,crio;
    sscanf(this->actualCommand.c_str(),"NASTAWA%03d-%02d:%03d-%02d:%01d:%01d", &red,&t1,&blue,&t2,&fan,&crio);

    if(red>0)
    {
        this->signals.redActual=true;
    }
    if(blue>0)
    {
        this->signals.blueActual=true;
    }
    if(fan>0)
    {
        this->signals.fan=true;
    }

    sscanf(this->futureCommand.c_str(),"NASTAWA%03d-%02d:%03d-%02d:%01d:%01d", &red,&t1,&blue,&t2,&fan,&crio);

    if(red>0)
    {
        this->signals.redFuture=true;
    }
    if(blue>0)
    {
        this->signals.blueFuture=true;
    }

    if(this->actualCommand=="")
    {
        this->signals.blueActual=false;
        this->signals.redActual=false;
        this->signals.fan=false;
    }

    std::cout<<this->signals.redActual<<","<<this->signals.blueActual<<","<<this->signals.fan<<","<<this->signals.redFuture<<","<<this->signals.blueFuture<<std::endl;
}

void Programs::SetProgramID(int ID)
{
    switch(ID)
    {
        case 1:
        {
            this->actualProgram=this->path+"hot";
            break;
        }
        case 2:
        {
            this->actualProgram=this->path+"crio";
            break;
        }
        case 3:
        {
            this->actualProgram=this->path+"manual";
            break;
        }
        case 4:
        {
            this->actualProgram=this->path+"pr1";
            break;
        }
        case 5:
        {
            this->actualProgram=this->path+"pr2";
            break;
        }
        case 6:
        {
            this->actualProgram=this->path+"pr3";
            break;
        }
        case 7:
        {
            this->actualProgram=this->path+"pr4";
            break;
        }
        case 8:
        {
            this->actualProgram=this->path+"pr5";
            break;
        }
        case 9:
        {
            this->actualProgram=this->path+"pr6";
            break;
        }
        case 10:
        {
            this->actualProgram=this->path+"pr7";
            break;
        }
        case 11:
        {
            this->actualProgram=this->path+"pr8";
            break;
        }
    }
    this->file.close();
    this->SetProgram(this->actualProgram);
}

int Programs::GetTime()
{
    if(this->isPause==false) {
        this->OverallTime--;
    }
    return this->OverallTime;
}

void Programs::TestCrio()
{
        SendFrame(this->port_, "NASTAWA000-05:000-05:0:1");
}