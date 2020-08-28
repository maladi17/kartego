#pragma once
#include "pcap.h"
#define commandN 9
#define packetN 30
struct packetC {
	u_char *data;
	int size; //currently owned
	int total; // size of packet
	int times; // times to run
	int delay; // miliseconds of delay after last
	
};

typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

/* IPv4 header */
typedef struct ip_header{
    u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
    u_char  tos;            // Type of service 
    u_short tlen;           // Total length 
    u_short identification; // Identification
    u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
    u_char  ttl;            // Time to live
    u_char  proto;          // Protocol
    u_short crc;            // Header checksum
    ip_address  saddr;      // Source address
    ip_address  daddr;      // Destination address
    u_int   op_pad;         // Option + Padding
}ip_header;



/* UDP header*/
typedef struct udp_header{
    u_short sport;          // Source port
    u_short dport;          // Destination port
    u_short len;            // Datagram length
    u_short crc;            // Checksum
}udp_header;

struct packetC main_fileRead(int size, int isComment, char path[200], int times, int delay);
int main_send(struct packetC packet[packetN], int occupiedinArr, int max);
int comments_killer(char path[200]);
int hexstream2tool(char path2[200]);
int cmd_main();
void sendOne(struct packetC pkt, int inum, pcap_t* fp);
pcap_t* selectDev(int *num);