#include "parser.h"
#include <string>


using namespace std;

extern "C" {
#include "pktheaders.h"
}

u_char inc_field(int *carry, int val) { //no val check in pkt
	
	if (val + 1 == 256) {
		*carry = 1;
		return 0;
	}

	val = val + 1;
	*carry = 0;

	return (u_char)val;

}


int initC2RWithpointers(std::string confF) {
	
	Json::Value& pkts = arrpkts(confF);
	
	int inter = 0;
	pcap_t* alldev = selectDev(&inter);
	int size = pkts.size(), max = 0;
	struct packetC pkt[packetN];
	int from = 0, to = 0, edian = 0, times = 0; // 1 = le, 0 = be
	int carry = 0;
	for (int i = 0; i < packetN && i < size; i++) {// iterator on all the packets
		pkt[i] = buildJsonArrDemand(i, main_fileRead,pkts);
		if (pkt[i].size > max)
			max = pkt[i].size;
		times = getTimesFromConf(i, pkts);
		for (int y = 0; y < times; y++) { //iterator on the times
			if (y != 0) {
				for (int h = 0; h < get_sizeDemands(i, pkts); h++) { //iterator on the demands
					carry = 0;
					from = GetfromDemand(h, i, pkts);
					to = GettoDemand(h, i, pkts);
					//we need le check;
					edian = get_edianDemand(h, i, pkts);
					if (edian) {
						for (int j = to; j > from; j--) { //needed to against 30 check. iterator on the bytes to be changed
							pkt[i].data[j] = inc_field(&carry, (int)(pkt[i].data[j]));
							if (carry == 0)
								break;
						}
					}
					else {
						for (int j = from; j < to; j++) { //needed to against 30 check
							pkt[i].data[j] = inc_field(&carry, (int)(pkt[i].data[j]));
							if (carry == 0)
								break;
						}
					}
				}
			}
			sendOne(pkt[i], inter, alldev);
		}
	}




	return 0;
}


