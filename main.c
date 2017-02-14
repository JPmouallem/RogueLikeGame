/*
    Jean-Pierre Mouallem
    0914064
    mouallej@mail.uoguelph.ca
    A2
    02/17/2016
*/

#include "A2.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
Main
Gathers the name of the input file using argv
IN: argc and argv to get the input file name from users
ERROR: Missing agruments
*/
int main(int argc, char * argv[])
{

    if (argc < 1){

        printf("Missing argument: Name of data file.\n");
        exit(1);

    }

    srand(time(NULL));

    readLine(argv);
    return 0;
}
