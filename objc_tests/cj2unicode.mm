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
        size_t buflen = strlen(argv[a]) * 4; // Chars!
        uint16_t *buffer = (uint16_t *)malloc(buflen * sizeof(uint16_t));
        int length = cjhebrew_to_utf16(argv[a], buffer, buflen);

        NSString *out = [[NSString alloc]
                            initWithCharactersNoCopy: buffer
                                              length: length
                                        freeWhenDone: YES];
        printf("%s", [out UTF8String]);

        if ( a < argc-1 )
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }

    [pool release];
    
    return 0;
}
