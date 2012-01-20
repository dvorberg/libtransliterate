#include <stdint.h>

/* The UTF-8 functions will tabe a regular C string containing beta code
 * and convert it to precombined greek characters (where ὤ is one UTF-8
 * encoded glyph). Character (-sequences) not recognized will be copied
 * into the output buffer as-is. This means that character that's not
 * betacode will just stay as it is.
 *
 * char *beta          - input string
 * char *output_buffer - You must provide the output buffer and a...
 * int buffer_length   - in bytes.
 */
int greek_beta_to_utf8(char *beta, char *output_buffer, int buffer_length);

/* This function reverses the effect of the above function and leaves
 * any UTF-8 byte sequence it doesn't recognize as-is. */   
int greek_utf8_to_beta(char *beta, char *output_buffer, int buffer_length);
 


/* The UTF-16 functions will take a regular C string containing beta
 * code and convert it to an UTF-16 string, that is, a null-terminated
 * array of 16 bit unsigned integers.
 *
 * The parameters always mean the same:
 * char *beta - Beta input. ANSI encoded. Any character not recognized
 *     will be converted to 16 bit. This means that spaces and such will just
 *     work.
 * output_buffer - You must provide an output buffer and a...
 * buffer_length - which is always counting the number of characters
 *     (not bytes!)
 *
 * All functions return the number of characters (not bytes!) written to
 * the output buffer.
 */

/* This function creates combining characters, that is, for example
 * for ὤ will be represented as three characters: the omega, combining
 * smooth breathing and combining acute accent. This is what the TLG
 * beta code manual recommends.
 */
int greek_asterisk_beta_to_utf16(char *beta,
                                 uint16_t *output_buffer,
                                 int buffer_length);

/* This function understands the characters of the combining (default)
 * and precombined variety.*/
int greek_asterisk_utf16_to_beta(uint16_t *beta,
                                 char *output_buffer,
                                 int buffer_length);

int cjhebrew_to_utf16(char *cjhebrew,
                      uint16_t *output_buffer,
                      int buffer_length);
