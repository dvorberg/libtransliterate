// -*- mode: c++; encoding: utf-8; -*-
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

#include <stdint.h>

#ifndef TRANSLITERATE_H
#define TRANSLITERATE_H

/* The functions that do the transliteration accept a regular
 * null-terminated string as input and write their ouput into a buffer
 * of uint16_t quantities you provide, together with its maximun
 * length. The buffer will be null-terminated. The functions all
 * return the number of characters (equal to the number of uint16_t)
 * used. Other prameters are explained below.
 */

namespace transliterate
{
    // Betacode Greek

    /* This function has two special parameters:
     *
     * As a default, this function produces characters separate from
     * their diacritical marks. So ('W will be encoded as three
     * unicode characters ῾, ’, and Ω, that are to be combined and
     * represented as one glyph: Ὥ. If you set precombined=true, a
     * single unicode character will be used to represent the
     * sequence. The TLG Beta Code manual explicitly recommends to use
     * non-precombined characters when possible.
     *
     * The default (i.e. official) Beta Code syntax uses capital latin
     * characters only and marks Greek capitals with an asterisk '*':
     *
     *    *)IHSOU=S => Ἰησοῦς
     *
     * If you want to use this syntax, set asterisk_syntax=true,
     * otherwise Latin capitals are mapped to Greek capitals and
     * lowercase input to lowercase output.
     */
    size_t betacode_greek_to_utf16(char *betacode,
                                   uint16_t *output_buffer,
                                   size_t buffer_length,
                                   int precombined = false,
                                   int asterisk_syntax = false);

    // Betacode Hebrew
    /* Beta Code for Hebrew seems to be somewhat limited. I don't have
       real world data for it, to this remains largely untested. */
    size_t betacode_hebrew_to_utf16(char *betacode,
                                    uint16_t *output_buffer,
                                    size_t buffer_length);

    // Betacode Coptic
    /* I don't know much about Coptic, so this remains untedted. */
    size_t betacode_coptic_to_utf16(char *betacode,
                                    uint16_t *output_buffer,
                                    size_t buffer_length);

    
    // cjhebrew
    /* I use the cjhebrew quite a bit in LaTeX, so this function
     * should be fairly well tested. */
    size_t cjhebrew_to_utf16(char *cjhebrew,
                             uint16_t *output_buffer,
                             size_t buffer_length);

    // Conversion to UTF-8.    
    /* This is mainly used by the swig interface definition, but I
     * thought some may find it usefull right here in the library.     
     * Based on utf8.h and utf8.c written by Alexey Vatchenko. See
     * conversion.c++ for details.
     */
    size_t utf16_to_utf8(uint16_t *input, char *buffer,
                         size_t buffer_length);
}

#endif
