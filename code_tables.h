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

#include <stdint.h>

/* This header defines a mix-in class that allows an object to be passed to
   the functions defined below. These functions will fill your code_container
   with the data from the corresponding .tbl file by calling your
   implementation of add_pair() consecutively.
*/

class code_container
{
public:
    virtual void add_pair(char *beta, uint16_t *utf16) = 0;
};

void add_greek_asterisk_code_table(code_container *container);
void add_greek_case_code_table(code_container *container);
void add_greek_precombined_asterisk_code_table(code_container *container);
void add_greek_precombined_case_code_table(code_container *container);
void add_hebrew_code_table(code_container *container);
void add_coptic_code_table(code_container *container);
void add_specials_code_table(code_container *container);

void add_cjhebrew_code_table(code_container *container);

