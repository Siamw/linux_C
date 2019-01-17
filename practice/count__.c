#include <stdio.h>
#include <stdlib.h>
 
 int main(int argc, char * argv[])
 {
    // This program reads a file from its arguments and prints a word by word. Additionally, it counts the words in the file.
	   if (argc < 2) return 1;
	    char * filename = argv[1];
		FILE * fp = fopen(filename, "r");
		    if (fp == NULL) return 1;
			   char c;
			   int count = 0;
				     while((c = fgetc(fp)) != EOF)
				    {
						      if(c == ' ' || c == '\n')								        {
										         printf("\n");
												          ++count;
														        }
																      else
																	        {
																			         printf("%c", c);
																					       }
																						      }
																							     fclose(fp);
																								  
																								     printf("This file has %d words in it.", count);
																									    return 0;
																										}
