// -*- mode: objc; coding: utf-8; -*-

#import <stdio.h>
#import <Foundation/Foundation.h>
#import <transliterate.h>

int main(int argc, char **argv)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    if (argc <= 1)
    {
        printf("Usage: %s <cjhebrew>", argv[0]);
        exit(-1);
    }

    for (int a = 1; a < argc; a++)
    {
        size_t buflen = strlen(argv[a]) * 4;
        uint16_t *buffer = (uint16_t *)malloc(buflen * sizeof(uint16_t));
        int length = transliterate::betacode_greek_to_utf16(
            argv[a], buffer, buflen, 0, 0);

        NSString *out = [[NSString alloc]
                            initWithCharactersNoCopy: buffer
                                              length: length
                                        freeWhenDone: YES];
        printf("%s ", [out UTF8String]);

        printf("\n");
        for(int b = 0; b < length; b++)
        {
            printf("%x ", buffer[b]);
        }
        printf("\n");
    }
    printf("\n");

    [pool release];
    
    return 0;
}
