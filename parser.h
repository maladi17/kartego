#pragma once
#include <string>
#include <iostream>
#include "Json.h"

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
	
	

	confParser::confParser(std::string name);
	int confParser::numPackets();
		struct packetC confParser::buildJsonArr(int index, struct packetC(*fp)(int, int, char[200], int, int));
	void confParser::getAllInCell(int index, Json::Value& pkts);
	int confParser::toDemand(int Dindex, int Pindex);
	int confParser::fromDemand(int Dindex, int Pindex);
	int confParser::get_edian(int Dindex, int Pindex);
	int confParser::get_demands_size(int index);
	int confParser::getTimes(int index);

};

int initC2R(std::string confF);