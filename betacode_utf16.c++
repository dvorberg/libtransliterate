#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"
#include "util.h"
#include "code_tables.h"

class greek_asterisk_beta_to_utf16_trie_t:
    public trie<char, uint16_t>,
    public code_container
{
public:
    void add_pair(const char *beta, uint16_t codepoint) {
        add((char *)beta, codepoint);
    }

    greek_asterisk_beta_to_utf16_trie_t() {
        root = new trie<char, uint16_t>::node(0);
        add_greek_asterisk_code_table(this);
        add_specials_code_table(this);
    }
};

greek_asterisk_beta_to_utf16_trie_t *greek_asterisk_beta_to_utf16_trie =
    new greek_asterisk_beta_to_utf16_trie_t();

int greek_case_beta_to_utf16(char *beta,
                             uint16_t *output_buffer,
                             int buffer_length)
{
    char *input = strdup(beta);

    uint16_t *ret_p = output_buffer;
    int current_output_length = 0;

    char *p = input;
    while (*p != 0)
    {
        uint16_t append = 0;
        
        if (*p == 's')
        {
            if ( between_words(*(p+1)) || *(p+1) == 0 )
            {
                append = 0x03C2; // Final sigma
            }
            else
            {
                append = 0x03C3; // Mid-sigma
            }
        }
        else if (*p == '*')
        {
            if (*(p+1) != 0)
            {
                if (*(p+1) >= 'a' && *(p+1) <= 'z')
                {
                    *(p+1) -= 'a' - 'A';
                }
                else
                {
                    append = (uint16_t)'*';
                }
            }
            else
            {
                append = (uint16_t)'*';
            }
            p++;
        }
        else
        {
            uint16_t utf16 = greek_asterisk_beta_to_utf16_trie->lookup_next(&p);
            if (utf16 == 0)
            {
                // We didn't find the byte sequence in the tree and so
                // we copy the next char verbatim and start over with the
                // char after that.
                append = (uint16_t)*p;
            }
            else
            {
                append = utf16;
            }
        }
    
        if (append != 0)
        {
            if (current_output_length + 1 < buffer_length)
            {
                *ret_p = append;
                *ret_p += sizeof(uint16_t);
                current_output_length++;
            }
            else
            {
                // We have reached the end of the output buffer.
                // There is nothing more to do for us but cleanup
                // and return to the caller.
                goto end;
            }

            p++;
        }
    }    
end:
    free(input);
    *ret_p = 0;
    return current_output_length + 1; // +1 because of the 0!
}


int greek_case_utf16_to_beta(uint16_t *beta,
                             char *output_buffer,
                             int buffer_length)
{

}
