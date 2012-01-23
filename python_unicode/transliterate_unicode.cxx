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

#include <stdint.h>
#include <Python.h>

#if Py_UNICODE_SIZE != 2
#error "This only works of Py_UNICODE is a uint16_t, sorry.
#endif

#include <transliterate.h>

PyObject *betacode_greek_to_unicode(PyObject *self, PyObject *args)
{
    char *input = NULL;
    int precombined = 0, asterisk_syntax = 0;
    
    if (!PyArg_ParseTuple(args, "s|ii", &input, &precombined, &asterisk_syntax))
    {
        return NULL;
    }

    size_t buflen = strlen(input);
    buflen += buflen >> 3; // 1 1/8th
    uint16_t *buffer = (uint16_t *)malloc(
        buflen*sizeof(uint16_t));
    size_t length = transliterate::betacode_greek_to_utf16(
        input, buffer, buflen, precombined, asterisk_syntax);

    PyObject *ret = Py_BuildValue("u#", buffer, (int)length);
    
    free(buffer);
    return ret;
}

PyObject *cjhebrew_to_unicode(PyObject *self, PyObject *args)
{
    char *input = NULL;
    
    if (!PyArg_ParseTuple(args, "s", &input))
    {
        return NULL;
    }

    size_t buflen = strlen(input);
    buflen += buflen >> 3; // 1 1/8th
    uint16_t *buffer = (uint16_t *)malloc(buflen*sizeof(uint16_t));
    size_t length = transliterate::cjhebrew_to_utf16(input, buffer, buflen);

    PyObject *ret = Py_BuildValue("u#", buffer, (int)length);
    
    free(buffer);
    return ret;
}

static PyMethodDef methods[] = {
    { "betacode_greek_to_unicode" , betacode_greek_to_unicode, METH_VARARGS,
      "Convert betacode for polytonic Greek into a unicode string.\n"
      "INPUT: ANSI encoded string of beta code\n"
      "PRECOMBINED: Output precombined unicode characters (default: false)\n"
      "ASTERISK_SYNTAX: Use *-syntax for capital letters (default: false)\n"},
    { "cjhebrew_to_unicode", cjhebrew_to_unicode, METH_VARARGS,
      "Convert cjhebrew into a unicode string.\n"
      "INPUT: ANSI encoded string of beta code\n"},
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC 
inittransliterate_unicode(void)
{
    // PyObject *m =
    Py_InitModule3("transliterate_unicode", methods,
                   "Functions to use libtransliterate's unicode "
                   "functions from Python");
}

