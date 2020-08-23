#include <stdlib.h>
#include <stdio.h>

#include "pcap.h"
#include "pktheaders.h"

int main_send(unsigned char *packet, int capacity, int owned)
{
	pcap_t *fp;


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
		free(packet);
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
		free(packet);
		return -1;
	}

	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &inum);

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		free(packet);
		return -1;
	}

	/* Jump to the selected adapter */
	for (d = alldevs, i = 0; i< inum - 1; d = d->next, i++);
	if ((fp = pcap_open(d->name,            // name of the device
		capacity,                // portion of the packet to capture (only the first capacity bytes)
		PCAP_OPENFLAG_PROMISCUOUS,  // promiscuous mode
		1000,               // read timeout
		NULL,               // authentication on the remote machine
		errbuf              // error buffer
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		free(packet);
		return -1;
	}


	
	/* Fill the rest of the packet */
	for (i = owned; i<capacity; i++)
	{
		packet[i] = i % 256;
	}

	/* Send down the packet */
	if (pcap_sendpacket(fp, packet, capacity) != 0)
	{
		fprintf(stderr, "\nError sending the packet: \n", pcap_geterr(fp));
		free(packet);
		return -1;
	}
	free(packet);
	return 0;
}