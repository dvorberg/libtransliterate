// -*- mode: c++; encoding: utf-8; -*-

#include <stdint.h>

#ifndef TRANSLITERATE_H
#define TRANSLITERATE_H

namespace transliterate
{
    // Betacode Greek
    size_t betacode_greek_to_utf16(char *betacode,
                                   uint16_t *output_buffer,
                                   size_t buffer_length,
                                   int precombined = false,
                                   int asterisk_syntax = false);

    // cjhebrew
    size_t cjhebrew_to_utf16(char *cjhebrew,
                             uint16_t *output_buffer,
                             size_t buffer_length);

    // Conversion to UTF-8.
    size_t utf16_to_utf8(uint16_t *input, char *buffer,
                         size_t buffer_length);
}

#endif
