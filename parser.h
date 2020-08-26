#pragma once
#include <string>
#include <iostream>

class confParser
{
	// Access specifier 
private:
	int number;
	std::string path;
	bool isPcap;
	bool isCommented;
	int times, delays, pktSize, demandSize, conditionSize;

public:

	// Data Members 
	std::string fileName;


	confParser(std::string name);
	int getNumber();
	std::string getPath();

	bool getIsPcap();

	bool getisCommented();

	int getTimes();

	int getDelays();

	int getpktSize();

	int getdemandSize();

	int getconditionSize();
};