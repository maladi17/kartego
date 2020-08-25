#include <stdio.h>

void helperCommands()
{
	printf("\n	interfaces		view all your interfaces which can be used for sending and receiving packets.\n\n");
	printf("\n	banner			show the app banner...\n\n");
	printf("\n	size			set your wanted packet size has to be ran before the file command...\n\n");
	printf("\n	add				set your wanted file fields...\n\n");
	printf("\n	commented		set your wanted file fields and send which includes comments...\n\n");
	printf("\n	env 			gets environment variables...\n\n");
	printf("\n	pcap2tool 		transfer pcap file to the tool file...\n\n");
	printf("\n	send	 		send the pkt...\n\n");
	printf("\n	exit			attack is complete! time to run...\n\n");
	printf("\n\n\n");
}

void banner() {

	printf("kartego ");
	printf("\n\n Made by Magen Gide0n\n\n");
	printf("it is highly recommended to use wireshark for this one.\n");
}

