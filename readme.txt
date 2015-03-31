CS360 Assignment 2
<ok.c>
Choong Huh

Description:

Program takes a word no longer than 15 characters from STDIN and does a binary search to see if it exists in a dictionary pre-loaded from the CS shared files [/cs_Share/class/cs360/lib/webster].

Program prints 'yes' if the word is found, and 'no' if it is not found. Wrong string formatting generates error printed to STDERR.

To compile:
gcc -std=c99 ok.c -o ok

To run:
./ok <seearch string>
