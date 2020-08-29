#pragma once
#include <string>
#include <iostream>
#include "Json.h"


int initC2RWithpointers(std::string confF);
Json::Value arrpkts(std::string fileName);
int GetfromDemand(int Dindex, int Pindex, Json::Value &pkts);
int getTimesFromConf(int index, Json::Value &pkts);
int GettoDemand(int Dindex, int Pindex, Json::Value &pkts);
int get_edianDemand(int Dindex, int Pindex, Json::Value &pkts);
struct packetC buildJsonArrDemand(int index, struct packetC(*fp)(int, int, char[200], int, int), Json::Value &pkts);
int get_sizeDemands(int index, Json::Value &pkts);

int initC2RWiththreads(std::string confF);