/*
 * ConfigReader.h
 *
 *  Created on: Jan 21, 2018
 *      Author: robert
 */

#include <string>
#include <opencv2/opencv.hpp>
#include <fstream>

#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

class ConfigReader {
public:
	ConfigReader(std::string path);
	virtual ~ConfigReader();

	std::string crioPath;

	struct
	{
		std::string language;
		std::string custom_program_path;
		std::string scripts;
		std::string usbPort;
		int crioVolume;
	} config;

    void increaseCrio();
	void resetCrio();

private:
	void Parse(std::string path);
};

#endif /* CONFIGREADER_H_ */
