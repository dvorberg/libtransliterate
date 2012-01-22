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
void add_latin_code_table(code_container *container);
void add_coptic_code_table(code_container *container);
void add_specials_code_table(code_container *container);

void add_cjhebrew_code_table(code_container *container);

