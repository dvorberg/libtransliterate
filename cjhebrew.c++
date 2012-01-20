#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"
#include "util.h"
#include "code_tables.h"

class cjhebrew_to_utf16_trie_t:
    public trie<char, uint16_t>,
    public code_container
{
public:
    void add_pair(const char *beta, uint16_t codepoint) {
        add((char *)beta, codepoint);
    }

    cjhebrew_to_utf16_trie_t() {
        root = new trie<char, uint16_t>::node(0);
        add_cjhebrew_code_table(this);
    }
};

cjhebrew_to_utf16_trie_t *cjhebrew_to_utf16_trie =
    new cjhebrew_to_utf16_trie_t();

/* Return true, if the char p points to is the last consonant in a word. */
inline int last_consonant(char *p)
{
    
    while(*p == 'i' || *p == 'e' || *p == 'E'
          || *p == ':' || *p == 'a' || *p == '/'
          || *p == 'A' || *p == 'o' || *p == 'u'
          || *p == '*' || *p == '-' || *p == '|')
    {
        p++;
    };

    if (between_words(*p))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    

int cjhebrew_to_utf16(char *cjhebrew,
                      uint16_t *output_buffer,
                      int buffer_length)
{
    // Make a temporary copy of the
    char *input = strdup(cjhebrew);

    // Those of the k, m, n, p and .s codes that are the last in a
    // word will converted to upper case to create end-variants of
    // their respecive Hebrew glyphs.
    for (char *p = input; *p != 0; p++)
    {        
        if (*p == 'k' || *p == 'm' || *p == 'n' || *p == 'p' || (
                *p == 's' && p != input && *(p-1) == '.'))
        {
            if ( last_consonant(p) )
            {
                *p = upcase(*p);
            }
        }
    }

    // Perform the conversion.
    int ret = cjhebrew_to_utf16_trie->process(input, output_buffer,
                                              buffer_length);

    free(input);
    return ret;
}


