// -*- mode: objc; encoding: utf-8; -*_
//
// This file is part of libtransliterate
//
// Copyright 2012 by Diedrich Vorberg <diedrich@tux4web.de>
//
// All Rights Reserved.
//
// For more Information on orm see the README and LICENSE file.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.

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
        printf("%s\n", [out UTF8String]);

        char converted[2048];
        transliterate::utf16_to_utf8(
            buffer, converted, sizeof(converted));
        printf("%s\n", converted);
        

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
