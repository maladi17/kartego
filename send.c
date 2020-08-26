#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pcap.h"
#include "pktheaders.h"

void delay(int mili) { // seconds = mili * 1000
	
	clock_t start = clock();
	while (clock() < start + mili) {}

}

int freeAll(struct packetC packet[30], int occupied) {
	int i;
	for (i = 0; i < occupied; i++)
		free(packet[i].data);
	return 1;
}

int main_send(struct packetC packet[30], int occupiedinArr, int max)
{
	pcap_t *fp;
	int j = 0;
	int h = 0;
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i = 0;
	u_int netmask;
	pcap_t *adhandle;
	char packet_filter[] = "ip and udp";
	struct bpf_program fcode;
	char errbuf[PCAP_ERRBUF_SIZE];
	

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		freeAll(packet, occupiedinArr);
		exit(1);
	}

	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		freeAll(packet, occupiedinArr);
		return -1;
	}

	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &inum);

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		freeAll(packet, occupiedinArr);
		return -1;
	}

	/* Jump to the selected adapter */
	for (d = alldevs, i = 0; i< inum - 1; d = d->next, i++);
	if ((fp = pcap_open(d->name,            // name of the device
		max,                // portion of the packet to capture (only the first capacity bytes)
		PCAP_OPENFLAG_PROMISCUOUS,  // promiscuous mode
		1000,               // read timeout
		NULL,               // authentication on the remote machine
		errbuf              // error buffer
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		freeAll(packet, occupiedinArr);
		return -1;
	}
	

	for (j = 0; j < occupiedinArr; j++) {
		/* Fill the rest of the packet */
		for (i = packet[j].size; i < packet[j].total; i++)
		{
			packet[j].data[i] = i % 256;
		}
	}

	
	for (j = 0; j < occupiedinArr; j++) {
		/* Send down the packet */
		for (h = 0; h < packet[j].times; h++) {
			if (pcap_sendpacket(fp, packet[j].data, packet[j].total) != 0)
			{
				fprintf(stderr, "\nError sending the packet: \n", pcap_geterr(fp));
				freeAll(packet, occupiedinArr);
				return -1;
			}
			printf("a packet was sent.\n\n");
			delay(packet[j].delay);
		}
	}
		freeAll(packet, occupiedinArr);
		
	
	return 0;
}