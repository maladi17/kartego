
#include <fstream>
#include "Json.h"
#include "parser.h"

using namespace std;


	confParser::confParser(string name) {
		fileName = name;
		ifstream ifs(fileName);
		Json::Reader reader;
		Json::Value obj;
		try {
			reader.parse(ifs, obj); // reader can also read strings
			const Json::Value& pkts = obj["pkt"]; // array of characters
			for (int i = 0; i < pkts.size(); i++) {
				number = pkts[i]["number"].asUInt();
				path = pkts[i]["path"].asString();
				isPcap = pkts[i]["ispcap"].asBool();
				isCommented = pkts[i]["isCommented"].asBool();
				times = pkts[i]["times"].asUInt();
				delays =  pkts[i]["delays"].asUInt();
				pktSize = pkts[i]["size"].asUInt();
				demandSize =  pkts[i]["demands"]["size"].asUInt();
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
		catch (int e)
		{
			cout << "An exception occurred in the configuration file. Exception Nr. " << e << '\n';
		}
	}
	

	int confParser::getNumber() {
		return number;
	}
	string confParser::getPath() {
		return path;
	}
	bool confParser::getIsPcap() {
		return isPcap;
	}
	bool confParser::getisCommented() {
		return isCommented;
	}
	int confParser::getTimes() {
		return times;
	}
	int confParser::getDelays() {
		return delays;
	}
	int confParser::getpktSize() {
		return pktSize;
	}
	int confParser::getdemandSize() {
		return demandSize;
	}
	int confParser::getconditionSize() {
		return conditionSize;
	}


