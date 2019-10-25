#include <stdio.h>
#include <stdlib.h>
#include "util.h"

Util::Util(){}

// Reads in keyboard commands and feeds to main program
int Util::nextCommand(int *s, int*t, int *iFlag)
{
    char c;

    while(1) {

        scanf("%c", &c); // Reading in character for command
        
        // Ignore spaces
        if (c == ' ' || c == '\t' || c == '\n') {
            continue;
        }

        if (c == 'E' || c == 'e' || c == 'I' || c == 'i' || c == 'W' || c == 'w') { 
            if(c == 'E' || c == 'e') {
                printf("The program will now terminate\n");
            }
            else if(c == 'I' || c == 'i') {
                // Read in graph
            }
            else if(c == 'W' || c == 'w') {
                // Print graph info
            }

            break;
        }

        if (c == 'C' || c == 'c') {

            // Reading in source, destination, and flag value and checking 
            // whether integers were succesfully read
            if(scanf("%d", s) != 1 || scanf("%d", t) != 1 || scanf("%d", iFlag)
                    != 1) {

                while((getchar()) != '\n'); // Flushing input buffer 
                c  = 'O'; // Return an invalid command
            }
            else
                break;
        }
        
        printf("Invalid Command\n");
        while((getchar()) != '\n'); // Flushing input buffer 

    }
        return c;
}
