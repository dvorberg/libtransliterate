// -*- mode: c++; encoding: utf-8; -*_
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

%module transliterate
%{
#include <transliterate.h>

char *betacode_greek_to_utf8(char *beta,
                             int precombined = 0,
                             int asterisk_syntax = 0)
{
    // Take a good guess at how many characters the unicode string is
    // going to contain.
    size_t buflen16 = strlen(beta);
    // Increase size by 1/4th to make sure there's enough room.
    buflen16 += buflen16 >> 2;

    // Allocate a buffer.
    uint16_t *buffer16 = (uint16_t *)malloc(buflen16 * sizeof(uint16_t));

    // Do the conversion.
    size_t length = transliterate::betacode_greek_to_utf16(
        beta, buffer16, buflen16);
    
    // The output buffer size we calculated take * 1.5
    size_t buflen8 = 2*buflen16;

    // Allocate the buffer
    char *buffer8 = (char *)malloc(buflen8);

    // UTF-16 to -8 conversion
    transliterate::utf16_to_utf8(buffer16, buffer8, buflen8);
    free(buffer16);

    return buffer8;
}

%}

%rename(greek_beta_to_utf8) greek_beta_to_utf8_w;
%rename(greek_utf8_to_beta) greek_utf8_to_beta_w;

char *betacode_greek_to_utf8(char *beta,
                             int precombined = 0,
                             int asterisk_syntax = 0);



