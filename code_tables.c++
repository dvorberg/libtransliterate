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

#include "code_tables.h"

void add_greek_asterisk_code_table(code_container *container)
{
#include "greek_asterisk.inc"
}

void add_greek_case_code_table(code_container *container)
{
#include "greek_case.inc"
}

void add_greek_precombined_asterisk_code_table(code_container *container)
{
#include "greek_precombined_asterisk.inc"
}

void add_greek_precombined_case_code_table(code_container *container)
{
#include "greek_precombined_case.inc"
}

void add_hebrew_code_table(code_container *container)
{
#include "hebrew.inc"
}

void add_coptic_code_table(code_container *container)
{
#include "coptic.inc"
}

void add_specials_code_table(code_container *container)
{
#include "specials.inc"
}



void add_cjhebrew_code_table(code_container *container)
{
#include "cjhebrew.inc"
}
