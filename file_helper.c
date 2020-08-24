#include <stdio.h>
#include <stdlib.h>

/* Functions */
void check_comment(char);  // checks for both types of comments, then passes on control to below comments
void block_comment();   //  handles block or multiline comments
void single_comment();   // handles single line comments

						 /* 2 file pointers - 1st is for the file in which we check for comments,
						 and 2nd is the file in which we copy the code after removing comments  */
FILE *fp, *fp2;

int comments_killer(void)
{
	char path2[200];
	char c;
	printf("please enter your file path:");
	scanf("%200[^\n]%*c", path2);
	fp = fopen(path2, "r");   // open the first file in read mode
	if (fp == NULL) {
		printf("Error! opening file");
		printf("the your comment file.txt does not exists in the app folder. see ya.");
		
		exit(1);
	}

	fp2 = fopen("temp.txt", "w");   

	while ((c = fgetc(fp)) != EOF)       // read the file character by character
		check_comment(c);   // check for each character if it seems like the beginning of a comment

	
					//  close both the files at the end of the program
	fclose(fp);
	fclose(fp2);

	return 0;
}


//handles both types of comments
void check_comment(char c)
{
	char d;

	if (c == '/')   // if the character starts with '/', it 'could' be a comment
	{
		d = fgetc(fp);
		

		if (d == '/')   // else if the next character we read is '/', it is the beginning of single line comment
		{
			single_comment();// pass control to function that handles single line comment
			fputc('\n', fp2);
		}
		else
		{
			printf("error in file");
			exit(1);
		}
	}

	// again, if all above fails, we add the character as it is in the new file.
	else if (c == ' ') {  }

	else
		fputc(c, fp2);
}




// function that handles single line comments
void single_comment()
{
	char d, e;

	while ((d = fgetc(fp)) != EOF)  // the single line comment has started, read the character by character
	{
		/* keep reading the characters and do nothing,
		as they do not have to be copied into the new file (we are removing the comments)
		*/
		if (d == '\n')   // check if the comment ends (single comments end with '\n', or newline)
			return;  // if the comment 'has' ended, return from the function

	}

}

int hexstream2tool(void)
{
	char path2[200];
	char c;
	int letters = 0;
	printf("please enter your file path:");
	scanf("%200[^\n]%*c", path2);
	fp = fopen(path2, "r");   // open the first file in read mode
	if (fp == NULL) {
		printf("Error! opening file");
		printf("the your comment file.txt does not exists in the app folder. see ya.");

		exit(1);
	}

	fp2 = fopen("temp.txt", "w");

	while ((c = fgetc(fp)) != EOF) {      // read the file character by character
		fputc(c, fp2);
		letters = letters + 1;
		if (letters == 2) {
			letters = 0;
			fputc('\n', fp2);
		}
	}
							//  close both the files at the end of the program
	fclose(fp);
	fclose(fp2);

	return 0;
}

