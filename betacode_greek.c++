#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"
#include "util.h"
#include "code_tables.h"

class forward_greek_trie: public trie<char, uint16_t>, public code_container
{
public:
    virtual void add_pair(char *beta, uint16_t *utf16) {
        add(beta, utf16);
    }

    /* Return true if c is a whitespace character. */
    virtual int between_words(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == 0 || c == ','
            || c == ':' || c == ';' || c == '.';
    }
};
    
class asterisk_combining_trie_t: public forward_greek_trie
{
public:
    asterisk_combining_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_asterisk_code_table(this);
        add_specials_code_table(this);
        finalize();
    }
};
asterisk_combining_trie_t *asterisk_combining_trie =
    new asterisk_combining_trie_t();


class asterisk_precombined_trie_t: public forward_greek_trie
{
public:
    asterisk_precombined_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_precombined_asterisk_code_table(this);
        add_specials_code_table(this);
        finalize();
    }
};

asterisk_precombined_trie_t *asterisk_precombined_trie =
    new asterisk_precombined_trie_t();



class case_combining_trie_t: public forward_greek_trie
{
public:
    case_combining_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_case_code_table(this);
        add_specials_code_table(this);
        finalize();
    }

    inline int upcase_letter(uint16_t c) {
        //          Α              Ω
        return c >= 0x0391 && c <= 0x03A9;
    }

    inline int capital_modifyer(uint16_t c) {
        return c == 0x0313 || c == 0x0314 || c == 0x0301 || c == 0x0300;
    }
};

case_combining_trie_t *case_combining_trie =
    new case_combining_trie_t();


class case_precombined_trie_t: public forward_greek_trie
{
public:
    case_precombined_trie_t() {
        root = new forward_greek_trie::node(0);
        add_greek_precombined_case_code_table(this);
        add_specials_code_table(this);
        finalize();
    }
};

case_precombined_trie_t *case_precombined_trie =
    new case_precombined_trie_t();


forward_greek_trie *forward_tries_utf16[2][2] =
{ { new case_combining_trie_t(),
    new case_precombined_trie_t() },
  { new asterisk_combining_trie_t(),
    new asterisk_precombined_trie_t() }};




namespace transliterate
{
    size_t betacode_greek_to_utf16(char *betacode,
                                   uint16_t *output_buffer,
                                   size_t buffer_length,
                                   int precombined = false,
                                   int asterisk_syntax = false)
    {
        if (precombined) precombined = 1;
        if (asterisk_syntax) asterisk_syntax = 1;
    
        return forward_tries_utf16[asterisk_syntax][precombined]->process(
            betacode, output_buffer, buffer_length);
    }
}
