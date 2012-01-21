#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "transliterate.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Usage: %s <beta code>\n", argv[0]);
        exit(-1);
    }
    else
    {
        for( int a = 1; a < argc; a++ )
        {
            int buflen = strlen(argv[a]);
            char *buffer = new char[buflen];
            greek_utf8_to_beta(argv[a], buffer, buflen);
            printf("%s", buffer);
            delete buffer;
        }
        printf("\n");
    }
}

