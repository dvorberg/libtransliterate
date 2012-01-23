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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"
#include "code_tables.h"

class hebrew_to_utf16_trie_t:
    public trie<char, uint16_t>,
    public code_container
{
public:
    virtual void add_pair(char *beta, uint16_t *utf16) {
        add(beta, utf16);
    }

    /* Return true if c is a whitespace character. */
    virtual int between_words(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == 0 || c == '-';
    }
    
    hebrew_to_utf16_trie_t() {
        root = new trie<char, uint16_t>::node(0);
        add_hebrew_code_table(this);
        finalize();
    }
};
    
hebrew_to_utf16_trie_t *hebrew_to_utf16_trie =
    new hebrew_to_utf16_trie_t();


namespace transliterate
{
    size_t betacode_hebrew_to_utf16(char *hebrew,
                                    uint16_t *output_buffer,
                                    size_t buffer_length)
    {
        return hebrew_to_utf16_trie->process(hebrew, output_buffer,
                                             buffer_length);
    }
}

