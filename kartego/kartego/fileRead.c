#include <stdio.h>
#include <stdlib.h> // For exit() function
#include <ctype.h>
#include "pcap.h"

int ishexadecimal(char *line){
	int i = 0;
	int res;
	while(line[i] != '\n' ){
		if(!isxdigit(line[i])){
			printf("%c not a hexadecimal!!!",line[i] );
			return -1;
		}

		if(i==2){
			printf("too much in the line" );
			return -1;
		}

		i++;
	}
	if(line[i] == '\n' && i==0){
			printf("this is a blank" );
			return -1;
		}
	return 1;
}

int main_fileRead( int size) {

FILE* filePointer;
char buffer[255];
int j = 0;
u_char hexC;
int num;
u_char *packet;
    packet = (unsigned char *)malloc(size * sizeof(int));

if ((filePointer = fopen("packet.txt", "r")) == NULL) {
        printf("Error! opening file");
		printf("the packet.txt does not exists in the app folder. see ya.");
		free(packet);
        exit(1);
    }

while(fgets(buffer, size, filePointer)) {
   
	if(ishexadecimal(buffer) == 1 && j < size)
	{
		 
		num = (int)strtol(buffer, NULL, 16);       // number base 16
		packet[j] = (unsigned char)num;
		j++;
	}
	else
	{
		printf("file is not ok!!! please remove empty lines besides the last one and ensure only to hex chars in each line.");
		free(packet);
		exit(1);
		return -1;
	}
}

fclose(filePointer);
main_send(packet, size, j);

    return 0;
}