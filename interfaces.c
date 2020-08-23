#include "pcap.h"




/* Print all the available information on the given interface */
void ifprint(pcap_if_t *d)
{
	pcap_addr_t *a;
	char ip6str[128];

	/* Name */
	printf("%s\n", d->name);

	/* Description */
	if (d->description)
		printf("\tDescription: %s\n", d->description);

	/* Loopback Address*/
	printf("\tLoopback: %s\n", (d->flags & PCAP_IF_LOOPBACK) ? "yes" : "no");

	/* IP addresses */
	for (a = d->addresses; a; a = a->next) {
		printf("\tAddress Family: #%d\n", a->addr->sa_family);
	}
	printf("\n");
}



void viewInterfaces()
{


	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];

	/* Retrieve the device list from the local machine */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
		exit(1);
	}

	/* Print the list */
	for (d = alldevs; d != NULL; d = d->next)
	{


		printf("%d. %s", ++i, d->name);
		if (d->description) {

			printf(" (%s)\n", d->description);


		}
		else
			printf(" (No description available)\n");


		ifprint(d);

	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return;
	}

	/* We don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);

}