#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include "pktheaders.h"


#define commandN 9

char commands[commandN][20] = { "exit","interfaces", "banner", "size", "add","env", "commented", "pcap2tool", "send" };

int compare_string(char *first, char *second) {
	while (*first == *second) {
		if (*first == '\0' || *second == '\0')
			break;

		first++;
		second++;
	}

	if (*first == '\0' && *second == '\0')
		return 0;
	else
		return -1;
}


int compare_commands(char *userIn) {
	int i, res;
	char command[15];

	for (i = 0; i<commandN; i++) {
		res = compare_string(commands[i], userIn);
		if (!res)
			return i;
	}
	return -1;
}


int cmd_main()
{
	char buf[BUFSIZ];
	char word[20];
	int ret, pktSize = 0, del = 0;
	struct packetC pkt[packetN];
	int occupiedinArr = 0;
	char path[200];
	int max = 100;
	int times = 1, delay = 1;
	banner();
	helperCommands();
	printf("let's start =]\n");
	printf("\n your command is my job:\n");

	while (1) {
		printf("\n~~~>");
		gets(word);
		ret = compare_commands(word);
		switch (ret) {
		case(0):
			printf("you chose to end the program. May the force be with you!  ");
			return 0;


		case(1):
			printf("the following are your interfaces: \n");
			viewInterfaces();
			break;

		case(2):
			banner();
			break;

		case(3):

			printf("Enter your packet size: ");

			if (fgets(buf, sizeof(buf), stdin) != NULL)
			{
				pktSize = atoi(buf);
				printf("You entered %d as your packet size\n", pktSize);
			}
			break;

		case(4):

			if (occupiedinArr < packetN) {
				memset(path, '\0', sizeof(path));
				printf("please enter a path (like C:/Users/Adi/Documents/Visual/Projects 2/kartego/packet.txt): \n");
				scanf("%200[^\n]%*c", path);
				printf("enter number of times to run:\n");
				scanf("%d", &times);
				printf("enter seconds for delay to run:\n");
				scanf("%d", &delay);
				pkt[occupiedinArr] = main_fileRead(pktSize, 0, path, times,delay);
				occupiedinArr = occupiedinArr + 1;
				if (max < pktSize)
					max = pktSize;
			}
			else if (occupiedinArr == packetN)
				printf("the packets array is full. try to send those in order to get a choise to send others.");
			break;
		case(5):


			printf("size of wanted file is %d\n", pktSize);
			printf("currently %d are waiting in the stack", occupiedinArr);


			break;

		case(6):
			if (occupiedinArr < packetN) {
				memset(path, '\0', sizeof(path));
				printf("please enter your file path:");
				scanf("%200[^\n]%*c", path);
				comments_killer(path);
				memset(path, '\0', sizeof(path));
				strncpy(path, "temp.txt", 8);
				printf("enter number of times to run:\n");
				scanf("%d", &times);
				printf("enter seconds for delay to run:\n");
				scanf("%d", &delay);
				pkt[occupiedinArr] = main_fileRead(pktSize, 1, path, times,delay);
				
				occupiedinArr = occupiedinArr + 1;
				if (max < pktSize)
					max = pktSize;
			}
			else if (occupiedinArr == packetN)
				printf("the packets array is full. try to send those in order to get a choise to send others.");
			break;

		case(7):
			if (occupiedinArr < packetN) {
				printf("please enter your file path:");
				scanf("%200[^\n]%*c", path);
				hexstream2tool(path);
				memset(path, '\0', sizeof(path));
				strncpy(path, "temp.txt", 8);
				printf("enter number of times to run:\n");
				scanf("%d", &times);
				printf("enter seconds for delay to run:\n");
				scanf("%d", &delay);
				pkt[occupiedinArr] = main_fileRead(pktSize, 1, path, times,delay);
				occupiedinArr = occupiedinArr + 1;
				
				if (pktSize > max)
					max = pktSize;
			}
			else if (occupiedinArr == packetN)
				printf("the packets array is full. try to send those in order to get a choise to send others.");
			break;

		case(8):
			if (occupiedinArr == 0)
				printf("the packets array was free in send file.");

			else if (pkt) {
				main_send(pkt, occupiedinArr, max);
				occupiedinArr = 0;
			}
		
			break;
		default:
			printf("\nthe following is our commands:\n");
			helperCommands();

		}
	}
	return 0;
}