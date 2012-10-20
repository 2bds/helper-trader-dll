#pragma once

#include <fstream>
#include <iostream>
#include <string>

const std::string xmlPath = "E:\\NEW LIBS\\RUBY\\BODY\\signals.xml";

void LOGGER(const std::wstring & response){
	std::ofstream of(std::string("logger.txt").c_str());
	std::string temp(response.length(),' ');
	std::copy(response.begin(), response.end(), temp.begin());
	if(of){
		of << temp;
		of.close();
	}
}

std::wstring readXmlFile(const std::string& path){
	std::string xmlText = "";
	std::string line;
	std::ifstream myfile(path.c_str());
	if (myfile.is_open()) {
		while(myfile.good())	{
			getline (myfile, line);
			xmlText += line;
		}
		myfile.close();
	}
	std::wstring xml(xmlText.length(),L' ');
	std::copy(xmlText.begin(), xmlText.end(), xml.begin());
	return xml;
}

std::string readXmlFile1(const std::string& path){
	std::string xmlText = "";
	std::string line;
	std::ifstream myfile(path.c_str());
	if (myfile.is_open()) {
		while(myfile.good())	{
			getline (myfile, line);
			xmlText += line;
		}
		myfile.close();
	}
	return xmlText;
}