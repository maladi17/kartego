#include "parser.h"
#include <string>
#include <mutex>
#include <iostream>
#include <thread>

using namespace std;

extern "C" {
#include "pktheaders.h"
}
std::mutex mtx;


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
					
					edian = get_edianDemand(h, i, pkts);
					if (to<from || 0>from || pkt[i].size-1 < to) {
						std::cout << "wrong demand configurations"<< std::endl;
						exit(1);
					}
					if (edian) {
						for (int j = to; j > from-1; j--) { // iterator on the bytes to be changed
							pkt[i].data[j] = inc_field(&carry, (int)(pkt[i].data[j]));
							if (carry == 0)
								break;
						}
					}
					else {
						for (int j = from; j < to+1; j++) { 
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


     //This function will be called from a thread

     void call_from_thread(int tid, Json::Value &pkts, pcap_t* alldev, struct packetC *pkt) {

		 int inter = 0;
		 
		 int size = pkts.size(), max = 0;
		 int from = 0, to = 0, edian = 0, times = 0; // 1 = le, 0 = be
		 int carry = 0;
		 mtx.lock();
		 pkt[tid] = buildJsonArrDemand(tid, main_fileRead, pkts); //because we both create and delete the temp file in here.
		 mtx.unlock();

		 if (pkt[tid].size > max)  // wtf??
			 max = pkt[tid].size;
		 times = getTimesFromConf(tid, pkts);
		 for (int y = 0; y < times; y++) { //iterator on the times
			 if (y != 0) {
				 for (int h = 0; h < get_sizeDemands(tid, pkts); h++) { //iterator on the demands
					 carry = 0;
					 from = GetfromDemand(h, tid, pkts);
					 to = GettoDemand(h, tid, pkts);

					 edian = get_edianDemand(h, tid, pkts);
					 if (to<from || 0>from || pkt[tid].size - 1 < to) {
						 std::cout << "wrong demand configurations" << std::endl;
						 exit(1);
					 }
					 if (edian) {
						 for (int j = to; j > from - 1; j--) { // iterator on the bytes to be changed
							 pkt[tid].data[j] = inc_field(&carry, (int)(pkt[tid].data[j]));
							 if (carry == 0)
								 break;
						 }
					 }
					 else {
						 for (int j = from; j < to + 1; j++) {
							 pkt[tid].data[j] = inc_field(&carry, (int)(pkt[tid].data[j]));
							 if (carry == 0)
								 break;
						 }
					 }
				 }
			 }
			 sendOne(pkt[tid], inter, alldev);
		 }
	
}
	 
	 int initC2RWiththreads(std::string confF) {

		 Json::Value& pkts = arrpkts(confF);
		 std::thread t[packetN];
		 int inter = 0;
		 pcap_t* alldev = selectDev(&inter);
		 int size = pkts.size(), max = 0;
		 struct packetC pkt[packetN];
		 
		 for (int i = 0; i < packetN && i < size; i++) {// iterator on all the packets
			 t[i] = std::thread(call_from_thread, i, pkts, alldev,pkt );
			
		 }
		 for (int i = 0; i < pkts.size(); ++i) {
			 t[i].join();
		 }
		 return 0;
	 }