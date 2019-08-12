/*
 * ConfigReader.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: robert
 */

#include "../inc/ConfigReader.h"

ConfigReader::ConfigReader(std::string path) {
	// TODO Auto-generated constructor stub
	this->crioPath=path+"/usedCrio";
	this->Parse(path+"/config.yml");
}

ConfigReader::~ConfigReader() {
	// TODO Auto-generated destructor stub
}

void ConfigReader::Parse(std::string path)
{
	cv::FileStorage file(path,cv::FileStorage::READ);

	if(!file["language"].empty())
	{
		file["language"]>>config.language;
	}
	if(!file["customProgram"].empty())
	{
		file["customProgram"]>>config.custom_program_path;
	}
	if(!file["usbPort"].empty())
	{
		file["usbPort"]>>config.usbPort;
	}
	if(!file["scripts"].empty())
	{
		file["scripts"]>>config.scripts;
	}
	if(!file["criovolume"].empty())
	{
		file["criovolume"]>>config.crioVolume;

		std::fstream file;
		file.open(this->crioPath);

		std::string number;
		getline(file,number);

		config.crioVolume-=std::stoi(number);
		file.close();
	}
	file.release();
}

void ConfigReader::increaseCrio()
{
    std::fstream file;
    file.open(this->crioPath);

    std::string number;
    getline(file,number);

    int num=std::stoi(number);
    file.close();
    num++;

    file.open(this->crioPath);

    std::string out=std::to_string(num);

    file.write(out.c_str(),out.size());
    file.close();
}

void ConfigReader::resetCrio()
{
    std::fstream file;
    file.open(this->crioPath,std::ios::out | std::ios::trunc);

    std::string out=std::to_string(0);

    file.write(out.c_str(),out.size());
    file.close();
}