//=======================================================================
// Choong Huh
// 10957124
// HW2 ok.c
//=======================================================================

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	FALSE	0
#define	TRUE	1

#define MWS 	16		// Maximum Word Size

int ok(int fd, char *tempWord);

int main(int argc, char *argv[])
{
	int fd = open("/cs_Share/class/cs360/lib/webster", O_RDONLY, 0);
	
	/* Usage and precondition checking. Return error messages upon 
		file open failure or 
	*/
	if (fd < 0) 
		{
		fprintf(stderr, "FILE OPEN FAILURE\n");
		exit(0);
		}


	if (argc < 2)
		{
		fprintf(stderr, "Usage: ok <word>\n");
		exit(0);
		}

	int found = FALSE;

	char word[MWS];
	strcpy(word,argv[1]);

	found = ok(fd, word);
	
	if (found) 
		puts("yes");
	else 
		puts("no");
	
	close(fd);

return 0;
}

//========================================
// ok()
//
// Opens the dictionary and returns the file pointer

int ok(int fd, char *tempWord)
{
	int i;
	int bot = 0;
	int top = lseek(fd, 0, SEEK_END) / 16;
	int mid = (bot + top) / 2;
	int actual;
	int attempt = 16;

	char buffer[MWS];
	char word[MWS];
	
	/*Dictionary requires that the word be a 16-character long line, and ends with null terminator.
		remaining spaces in between are replaced as a blank ' '                           */

	for (i=0; i<15; i++)
	{
		if (tempWord[i] == '\0')
			break; 
		else
			word[i] = tempWord[i];			// The user-chosen word is being copied to word[]
		 
	}

	for (	; i<15; i++) 					// for the remainder of characters...
		word[i] = ' ';					// ' '

	word[15]='\0';						//null terminator is inserted to mark end


	i = 0;							// i set to zero, so we can traverse the word
								// char by char
	while (strcmp(buffer, word)!= 0)
	{
		lseek(fd, mid * 16, SEEK_SET);
		actual = read(fd, buffer, attempt);		// for each looping, buffer[] stores the program-chosen
		buffer[15]='\0';				// word to be compared with the user-chosen word.

		//printf("%s\n",buffer);
	
		if ((top-bot)==1) 				// we have narrowed the search interval  down to one word
			bot++;
	
		else if (bot == top) 				// Returning FALSE because 
			return FALSE; 				// Our word choice is not the same as the given word

		else if (word[i] > buffer[i]) 			// Must pick a higher search interval
		{
			bot = mid;
			mid = (top + bot) / 2;
			i = 0;
		}
		else if (word[i] < buffer[i]) 			// Must select a lower search interval
		{
			top = mid;
			mid = (top + bot)/2;
			i = 0;
		}
		else if (word[i] == buffer[i]) 
			i++; 					// Characters match up. Move to the next character
	}
	
	return TRUE;
}
