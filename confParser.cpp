
#include <fstream>
#include "Json.h"
#include "parser.h"
#include <stdlib.h>
extern "C" {
#include "pktheaders.h"
}

using namespace std;

Json::Value arrpkts(string fileName) {
	ifstream ifs(fileName);
	if (!ifs) {     // If the file was not found, then file is 0, i.e. !file=1 or true.
		cout << "could not find the file." << '\n';
		exit(1);    // The file was not found.
	}

	Json::Reader reader;
	Json::Value obj;

	reader.parse(ifs, obj); // reader can also read strings
	Json::Value& pkts = obj["pkt"]; // array of characters
	return pkts;
}


int GetfromDemand(int Dindex, int Pindex, Json::Value pkts) {


	
	return pkts[Pindex]["demands"]["details"][Dindex]["from"].asUInt();
}

int getTimesFromConf(int index, Json::Value pkts) {

	return  pkts[index]["times"].asUInt();
}

int GettoDemand(int Dindex, int Pindex, Json::Value pkts) {


	return pkts[Pindex]["demands"]["details"][Dindex]["to"].asUInt();
}

int get_edianDemand(int Dindex, int Pindex, Json::Value pkts) {

	return pkts[Pindex]["demands"]["details"][Dindex]["format"].asUInt();
}

struct packetC buildJsonArrDemand(int index, struct packetC(*fp)(int, int, char[200], int, int), Json::Value pkts) {

	char test[200];
	
	if (pkts[index]["isCommented"].asUInt() && pkts[index]["ispcap"].asUInt()) {
		cout << "file cannot be both hex stream and commented." << '\n';
		exit(1);    // The file was not found.
	}

	if (pkts[index]["isCommented"].asUInt()) {
		strcpy(test, (pkts[index]["path"].asString()).c_str());
		comments_killer(test);

		memset(test, '\0', sizeof(test));
		strncpy(test, "temp.txt", 8);
		return fp(pkts[index]["size"].asUInt(), pkts[index]["isCommented"].asUInt(), test, pkts[index]["times"].asUInt(), pkts[index]["delays"].asUInt());
	}
	else if (pkts[index]["ispcap"].asUInt()) {
		strcpy(test, (pkts[index]["path"].asString()).c_str());
		hexstream2tool(test);
		memset(test, '\0', sizeof(test));
		strncpy(test, "temp.txt", 8);
		return fp(pkts[index]["size"].asUInt(), pkts[index]["ispcap"].asUInt(), test, pkts[index]["times"].asUInt(), pkts[index]["delays"].asUInt());

	}
	strcpy(test, (pkts[index]["path"].asString()).c_str());
	return fp(pkts[index]["size"].asUInt(), pkts[index]["isCommented"].asUInt(), test, pkts[index]["times"].asUInt(), pkts[index]["delays"].asUInt());
}


int get_sizeDemands(int index, Json::Value pkts) {


	return  pkts[index]["conditions"]["size"].asUInt();
}


/*
void getAllInCell(int index, Json::Value& pkts) {

for (int i = 0; i < pkts.size(); i++) {
number = pkts[i]["number"].asUInt();
path = pkts[i]["path"].asString();
isPcap = pkts[i]["ispcap"].asBool();
isCommented = pkts[i]["isCommented"].asBool();
times = pkts[i]["times"].asUInt();
delays = pkts[i]["delays"].asUInt();
pktSize = pkts[i]["size"].asUInt();
demandSize = pkts[i]["demands"]["size"].asUInt();
conditionSize = pkts[i]["conditions"]["size"].asUInt();

const Json::Value& demands = pkts[i]["demands"]["details"]; // array of characters

for (int j = 0; j < demandSize; j++) {
cout << "    from: " << pkts[i]["demands"]["details"][j]["from"].asUInt();
cout << "    to: " << pkts[i]["demands"]["details"][j]["to"].asUInt();
cout << "    type: " << pkts[i]["demands"]["details"][j]["type"].asString();
cout << "    in: " << pkts[i]["demands"]["details"][j]["in"].asUInt();
cout << "    format: " << pkts[i]["demands"]["details"][j]["format"].asString();
}
const Json::Value& conditions = pkts[i]["conditions"]["details"]; // array of characters
for (int j = 0; j < conditionSize; j++) {
cout << "    index: " << pkts[i]["conditions"]["details"][j]["index"].asUInt();
cout << "    eq: " << pkts[i]["conditions"]["details"][j]["eq"].asString();
cout << "    then: " << pkts[i]["conditions"]["details"][j]["then"].asUInt();
cout << "    changesTo: " << pkts[i]["conditions"]["details"][j]["changesTo"].asString();

}

}
}
*/