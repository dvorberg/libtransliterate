// -*- mode: c++; encoding: utf-8; -*_
//
// This file is part of libtransliterate
//
// This is based on utf8.h and utf8.c written by Alexey Vatchenko.
//

/*
 * Copyright (c) 2007 Alexey Vatchenko <av@bsdua.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma GCC diagnostic ignored "-Wbitwise-op-parentheses"

#include <arpa/inet.h>
#include <stdint.h>
#include <sys/types.h>
#include <wchar.h>

#define UTF8_IGNORE_ERROR		0x01
#define UTF8_SKIP_BOM			0x02

#define _NXT	0x80
#define _SEQ2	0xc0
#define _SEQ3	0xe0
#define _SEQ4	0xf0
#define _SEQ5	0xf8
#define _SEQ6	0xfc

#define _BOM	0xfeff

static int
__wchar_forbitten(wchar_t sym)
{

	/* Surrogate pairs */
	if (sym >= 0xd800 && sym <= 0xdfff)
		return (-1);

	return (0);
}

static int
__utf8_forbitten(u_char octet)
{

	switch (octet) {
	case 0xc0:
	case 0xc1:
	case 0xf5:
	case 0xff:
		return (-1);
	}

	return (0);
}

namespace transliterate
{
    size_t utf16_to_utf8(uint16_t *input, char *buffer,
                         size_t buffer_length)
    {
/*
 * DESCRIPTION
 *	This function translates UCS-4 symbols (given in local machine
 *	byte order) into UTF-8 string.
 *
 *	It takes the following arguments:
 *	in	- input unicode string. It can be null-terminated.
 *	insize	- size of input string in wide characters.
 *	out	- result buffer for utf8 string. If out is NULL,
 *		function returns size of result buffer.
 *	outsize - size of result buffer.
 *
 * RETURN VALUES
 *	The function returns size of result buffer (in bytes). Zero is returned
 *	in case of error.
 *
 * CAVEATS
 *	If UCS-4 string contains zero symbols, they will be translated
 *	as regular symbols.
 */

        // size_t wchar_to_utf8(const wchar_t *in, size_t insize,
        //                      char *out, size_t outsize,
        //                      int flags)

        int flags = 0;

        uint16_t *w, *wlim;
        wchar_t ch;
        u_char *p, *lim, *oc;
        size_t total, n;
        
        w = input;
        size_t insize = 0;
        for (wlim = input; *wlim != 0; wlim++)
        {
            insize++;
        };
        
        //size_t outsize = insize + (insize >> 1);
        //u_char *out = malloc( outsize ); // insize *= 1.5

        size_t outsize = buffer_length;
        u_char *out = (u_char *)buffer;
        
        p = (u_char *)out;
        lim = p + outsize;
        total = 0;
        for (; w < wlim; w++) {
            wchar_t W = (wchar_t)*w;
            
            if (__wchar_forbitten(W) != 0) {
                if ((flags & UTF8_IGNORE_ERROR) == 0)
                    return (0);
                else
                    continue;
            }
            
            if (W == _BOM && (flags & UTF8_SKIP_BOM) != 0)
                continue;
            
            if (W < 0) {
                if ((flags & UTF8_IGNORE_ERROR) == 0)
                    return (0);
                continue;
            } else if (W <= 0x0000007f)
                n = 1;
            else if (W <= 0x000007ff)
                n = 2;
            else if (W <= 0x0000ffff)
                n = 3;
            else if (W <= 0x001fffff)
                n = 4;
            else if (W <= 0x03ffffff)
                n = 5;
            else /* if (W <= 0x7fffffff) */
                n = 6;

            total += n;

            if (out == NULL)
                continue;

            if (lim - p <= n - 1)
                return (0);		/* no space left */

            /* make it work under different endians */
            ch = htonl(W);
            oc = (u_char *)&ch;
            switch (n) {
            case 1:
                *p = oc[3];
                break;

            case 2:
                p[1] = _NXT | oc[3] & 0x3f;
                p[0] = _SEQ2 | (oc[3] >> 6) | ((oc[2] & 0x07) << 2);
                break;

            case 3:
                p[2] = _NXT | oc[3] & 0x3f;
                p[1] = _NXT | (oc[3] >> 6) | ((oc[2] & 0x0f) << 2);
                p[0] = _SEQ3 | ((oc[2] & 0xf0) >> 4);
                break;

            case 4:
                p[3] = _NXT | oc[3] & 0x3f;
                p[2] = _NXT | (oc[3] >> 6) | ((oc[2] & 0x0f) << 2);
                p[1] = _NXT | ((oc[2] & 0xf0) >> 4) |
                    ((oc[1] & 0x03) << 4);
                p[0] = _SEQ4 | ((oc[1] & 0x1f) >> 2);
                break;

            case 5:
                p[4] = _NXT | oc[3] & 0x3f;
                p[3] = _NXT | (oc[3] >> 6) | ((oc[2] & 0x0f) << 2);
                p[2] = _NXT | ((oc[2] & 0xf0) >> 4) |
                    ((oc[1] & 0x03) << 4);
                p[1] = _NXT | (oc[1] >> 2);
                p[0] = _SEQ5 | oc[0] & 0x03;
                break;

            case 6:
                p[5] = _NXT | oc[3] & 0x3f;
                p[4] = _NXT | (oc[3] >> 6) | ((oc[2] & 0x0f) << 2);
                p[3] = _NXT | (oc[2] >> 4) | ((oc[1] & 0x03) << 4);
                p[2] = _NXT | (oc[1] >> 2);
                p[1] = _NXT | oc[0] & 0x3f;
                p[0] = _SEQ6 | ((oc[0] & 0x40) >> 6);
                break;
            }

            /*
             * NOTE: do not check here for forbitten UTF-8 characters.
             * They cannot appear here because we do proper convertion.
             */

            p += n;
        }

        *p = 0;
        return total;
    }
}    
