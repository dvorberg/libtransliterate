#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"
#include "util.h"

/* The code_container is a mix in class that provides a virtual
 * add_code() method called by its constructor defined at the bottom
 * of this file. The add_codes() method will call add_code() for each
 * beta/utf8 pair and thus fill the code container.
 *
 * The custom trie classes here will subclass code_container,
 * implement their own add_code() and use it to fill in the codes in
 * the way usefull to the trie's purpose.
 */
class code_container
{
public:
    void add_codes();
    virtual void add_code(const char *beta, const char *utf8) = 0;
};



/* The forward_trie class is for the beta_to_utf8 trie.
 */
class forward_trie: public trie<char, char*>, public code_container
{
public:
    void add_code(const char *beta, const char *utf8) {
        add((char *)beta, (char *)utf8);
    }
    
    forward_trie() {
        root = new trie<char, char*>::node(0);
        add_codes();
        finalize();
    }
};

/* Define (and initialize!) the forward trie. */
forward_trie *beta_to_utf8_trie = new forward_trie();

/* The backward_trie class is for the utf8_to_beta trie.
 */
class backward_trie: public trie<char, char*>, public code_container
{
public:
    void add_code(const char *beta, const char *utf8) {
        add((char *)utf8, (char *)beta);
    }
    
    backward_trie() {
        root = new trie<char, char*>::node(0);
        add_codes();

        // Extra UTF-8 codes that won't get added by add_codes(), because
        // they are treated specially in beta_to_utf8().
        add_code("s", "σ");
        add_code("s", "ς");
        finalize();
    }
};

/* Define (and initialize!) the forward trie. */
backward_trie *utf8_to_beta_trie = new backward_trie();





/* The function for "forward" conversion, beta to utf8.
 * The function will return the number of bytes in output_buffer, including
 * the trailing \0.
 */
int greek_beta_to_utf8(char *beta,
                       char *output_buffer,
                       int output_buffer_length)
{
    char *input = strdup(beta);

    // memset(output_buffer, 0, output_buffer_length);
    char *ret_p = output_buffer;
    int current_output_length = 0;

    char unrecognized_buffer[2];
    unrecognized_buffer[1] = 0;
    
    char *p = input;
    while (*p != 0)
    {
        char *append = NULL;
        
        if (*p == 's')
        {
            if ( between_words(*(p+1)) )
            {
                append = (char *)"ς";
            }
            else
            {
                append = (char *)"σ";
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
                    append = (char *)"*";
                }
            }
            else
            {
                append = (char *)"*";
            }
            p++;
        }
        else if (between_words(*p))
        {
            append = (char *)" ";
            while (between_words(*(p+1)))
            {
                p++;
            }
        }    
        else
        {
            char *utf8 = beta_to_utf8_trie->lookup_next(&p);
            if (utf8 == NULL)
            {
                // We didn't find the byte sequence in the tree and so
                // we copy the next char verbatim and start over with the
                // char after that.
                unrecognized_buffer[0] = *p;
                append = unrecognized_buffer;
            }
            else
            {
                append = utf8;
            }
        }
    
        if (append != NULL)
        {
            if (current_output_length + strlen(append) < output_buffer_length)
            {
                // Copy the utf8 byte sequence to the output buffer.
                for(char *q = (char *)append; *q != 0; q++)
                {
                    *ret_p = *q;
                    *ret_p++;
                    current_output_length++;
                }
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


int greek_utf8_to_beta(char *utf8,
                       char *output_buffer, int output_buffer_length)
{
    char *ret_p = output_buffer;
    int current_output_length = 0;
    
    char unrecognized_buffer[2];
    unrecognized_buffer[1] = 0;
    
    for (char *p = utf8; *p != 0; p++)
    {
        char *append = NULL;
        
        if (between_words(*p))
        {
            while (between_words( *(p+1) ))
            {
                p++;
            }
            append = (char *)" ";
        }
        else
        {
            char *beta = utf8_to_beta_trie->lookup_next(&p);
            if (beta == NULL)
            {
                // We didn't find the byte sequence in the tree and so
                // we copy the next char verbatim and start over with the
                // char after that.
                unrecognized_buffer[0] = *p;
                append = unrecognized_buffer;
            }
            else
            {
                append = beta;
            }            
        }

        if (current_output_length + strlen(append) < output_buffer_length)
        {
            // Copy the utf8 byte sequence to the output buffer.
            for(char *q = append; *q != 0; q++)
            {
                *ret_p = *q;
                *ret_p++;
                current_output_length++;
            }
        }
        else
        {
            *ret_p = 0;
            return current_output_length + 1;
        }

        if (*p == 0) break;
    }

    *ret_p = 0;
    return current_output_length + 1;
}


/* The constructor for the code_container class, as discussed above. */

void code_container::add_codes()
{
    //container->add_code("*I)/", "Ἴ");
    add_code("O)", "Ὀ");
    add_code("i(=", "ἷ");
    add_code("a(/", "ἅ");
    add_code("i=", "ῖ");
    //add_code("*)E", "Ἐ");
    //add_code("*H)/", "Ἤ");
    add_code("i(/", "ἵ");
    add_code("(=U", "Ὗ");
    add_code("a\\", "ὰ");
    //add_code("*H)\\", "Ἢ");
    add_code("a/|", "ᾴ");
    add_code("a(=", "ἇ");
    add_code("I)", "Ἰ");
    add_code("u(=", "ὗ");
    //add_code("*)=H", "Ἦ");
    add_code("h=", "ῆ");
    add_code("I(", "Ἱ");
    add_code("(R", "Ῥ");
    add_code("O(", "Ὁ");
    add_code("(W", "Ὡ");
    add_code("(U", "Ὑ");
    add_code("h=|", "ῇ");
    add_code("(H", "Ἡ");
    add_code(")/H", "Ἤ");
    add_code("h|", "ῃ");
    add_code("(O", "Ὁ");
    //add_code("*)O", "Ὀ");
    add_code("e(/", "ἕ");
    add_code("(A", "Ἁ");
    add_code("(/I", "Ἷ");
    add_code("w\\", "ὼ");
    //add_code("*(H", "Ἡ");
    add_code("(E", "Ἑ");
    add_code("D", "Δ");
    add_code("w/|", "ῴ");
    add_code("H", "Η");
    add_code("e(\\", "ἓ");
    add_code("w=|", "ῷ");
    add_code("L", "Λ");
    add_code("i)=", "ἶ");
    //add_code("*E(/", "Ἕ");
    add_code("P", "Π");
    add_code("h(|", "ᾑ");
    add_code("O(/", "὏");
    add_code("i/+", "ΐ");
    add_code("T", "Τ");
    add_code("X", "Χ");
    add_code("(=W", "Ὧ");
    add_code("R(", "Ῥ");
    add_code("I)/", "Ἴ");
    add_code("u\\", "ὺ");
    //add_code("*)=W", "Ὦ");
    add_code("d", "δ");
    add_code("i(\\", "ἳ");
    add_code("W)/", "Ὤ");
    add_code("h", "η");
    add_code("a)/|", "ᾄ");
    add_code("l", "λ");
    add_code("W)", "Ὠ");
    add_code("W(", "Ὡ");
    add_code(")/O", "Ὄ");
    add_code("p", "π");
    add_code("t", "τ");
    add_code(")/I", "Ἴ");
    add_code("H(", "Ἡ");
    add_code("x", "χ");
    add_code(")/E", "Ἔ");
    add_code("a(\\", "ἃ");
    add_code("h/", "ή");
    add_code("h)=|", "ᾖ");
    //add_code("*W(=", "Ὧ");
    //add_code("*(/A", "Ἇ");
    add_code("(/E", "Ἕ");
    //add_code("*(/E", "Ἕ");
    add_code("(/A", "Ἇ");
    add_code("w)/", "ὤ");
    //add_code("*H(", "Ἡ");
    //add_code("*(/I", "Ἷ");
    //add_code("*(/H", "Ἧ");
    //add_code("*(/O", "὏");
    add_code("e/", "έ");
    add_code("w)", "ὠ");
    add_code("w(", "ὡ");
    add_code("(/W", "Ὧ");
    add_code("(/U", "Ὕ");
    //add_code("*(/W", "Ὧ");
    add_code("U(", "Ὑ");
    //add_code("*(/U", "Ὕ");
    //add_code("*(=U", "Ὗ");
    //add_code("*)/I", "Ἴ");
    add_code("w)=", "ὦ");
    add_code("h(\\", "ἣ");
    add_code("i\\+", "ῒ");
    //add_code("*O)/", "Ὄ");
    add_code("o/", "ό");
    add_code(")I", "Ἰ");
    add_code("E)", "Ἐ");
    add_code("E(", "Ἑ");
    add_code("o)", "ὀ");
    add_code("o(", "ὁ");
    add_code("e\\", "ὲ");
    add_code("u)=", "ὖ");
    add_code("W(/", "Ὧ");
    add_code("u/+", "ΰ");
    add_code("A)=", "Ἆ");
    add_code("I", "Ι");
    add_code("h(=", "ἧ");
    add_code("o)\\", "ὂ");
    add_code("w(\\", "ὣ");
    add_code("W(=", "Ὧ");
    add_code("h(=|", "ᾗ");
    add_code("u=", "ῦ");
    add_code("o)/", "ὄ");
    add_code("O)/", "Ὄ");
    add_code("C", "Ξ");
    add_code("w|", "ῳ");
    add_code("e)", "ἐ");
    add_code("e(", "ἑ");
    add_code("G", "Γ");
    add_code("K", "Κ");
    add_code("w(/", "ὥ");
    add_code("w/", "ώ");
    add_code("O", "Ο");
    //add_code("*I)", "Ἰ");
    add_code(")=A", "Ἆ");
    //add_code("*O(", "Ὁ");
    add_code("S", "Σ");
    add_code("o\\", "ὸ");
    //add_code("*I(", "Ἱ");
    add_code("W", "Ω");
    //add_code("*A)", "Ἀ");
    add_code("w(=", "ὧ");
    add_code("w)|", "ᾠ");
    add_code("W)=", "Ὦ");
    //add_code("*)=A", "Ἆ");
    add_code("a(/|", "ᾅ");
    add_code("i)", "ἰ");
    add_code("c", "ξ");
    add_code("g", "γ");
    //add_code("*(\\O", "Ὃ");
    add_code("a|", "ᾳ");
    add_code("k", "κ");
    //add_code("*)/W", "Ὤ");
    add_code("o", "ο");
    // add_code("s", "σ");
    add_code("H)", "Ἠ");
    add_code(")/A", "Ἄ");
    add_code("w", "ω");
    add_code("w)\\", "ὢ");
    add_code("r(", "ῤ");
    //add_code("*)/E", "Ἔ");
    add_code("o(/", "ὅ");
    //add_code("*A(", "Ἁ");
    //add_code("*)A", "Ἀ");
    //add_code("*)/H", "Ἤ");
    add_code("h)|", "ᾐ");
    add_code("u)/", "ὔ");
    //add_code("*)I", "Ἰ");
    //add_code("*W(", "Ὡ");
    //add_code("*W)", "Ὠ");
    add_code("h(", "ἡ");
    add_code("h)", "ἠ");
    //add_code("*(=W", "Ὧ");
    add_code(")=H", "Ἦ");
    //add_code("*O(/", "὏");
    //add_code("*R(", "Ῥ");
    add_code("h(/", "ἥ");
    //add_code("*E(", "Ἑ");
    add_code("(\\O", "Ὃ");
    //add_code("*(\\E", "Ἓ");
    add_code("u\\+", "ῢ");
    add_code(")\\*h", "Ἢ");
    add_code("(\\E", "Ἓ");
    add_code("h)\\", "ἢ");
    add_code("(\\A", "Ἃ");
    //add_code("*H)", "Ἠ");
    add_code("u/", "ύ");
    add_code("(I", "Ἱ");
    add_code("u)", "ὐ");
    add_code("u(", "ὑ");
    add_code("u+", "ϋ");
    add_code("(/O", "὏");
    add_code("u(\\", "ὓ");
    add_code("H)/", "Ἤ");
    //add_code("*(A", "Ἁ");
    add_code("a)=", "ἆ");
    add_code("B", "Β");
    //add_code("*(E", "Ἑ");
    //add_code("*A)=", "Ἆ");
    add_code("w(=|", "ᾧ");
    add_code("F", "Φ");
    //add_code("*(I", "Ἱ");
    add_code("u(/", "ὕ");
    add_code("H)\\", "Ἢ");
    add_code("h)=", "ἦ");
    //add_code("*(O", "Ὁ");
    add_code("N", "Ν");
    add_code("A)/", "Ἄ");
    add_code("R", "Ρ");
    //add_code("*(U", "Ὑ");
    add_code("(/H", "Ἧ");
    //add_code("*(W", "Ὡ");
    //add_code("*A)/", "Ἄ");
    add_code("w=", "ῶ");
    add_code("Z", "Ζ");
    add_code("i+/", "ΐ");
    add_code("E)/", "Ἔ");
    add_code("h)/", "ἤ");
    //add_code("*W(/", "Ὧ");
    //add_code("*)H", "Ἠ");
    add_code("b", "β");
    add_code("a=|", "ᾷ");
    add_code("h\\", "ὴ");
    add_code("f", "φ");
    add_code(")/W", "Ὤ");
    add_code("w|/", "ῴ");
    add_code("h)/|", "ᾔ");
    add_code("n", "ν");
    add_code("o(\\", "ὃ");
    add_code(")H", "Ἠ");
    add_code("r", "ρ");
    add_code(")O", "Ὀ");
    add_code(")A", "Ἀ");
    //add_code("*O)", "Ὀ");
    add_code("h/|", "ῄ");
    add_code("z", "ζ");
    add_code(")E", "Ἐ");
    add_code("u)\\", "ὒ");
    add_code("a)\\", "ἂ");
    //add_code("*A(=", "Ἇ");
    add_code(")\\H", "Ἢ");
    add_code("i\\", "ὶ");
    //add_code("*I(/", "Ἷ");
    add_code("e)\\", "ἒ");
    //add_code("*W)=", "Ὦ");
    add_code("A(", "Ἁ");
    //add_code("*A(/", "Ἇ");
    add_code("E(/", "Ἕ");
    add_code("(/*h", "Ἧ");
    //add_code("*W)/", "Ὤ");
    add_code(")=W", "Ὦ");
    //add_code("*E)/", "Ἔ");
    //add_code("*X", "Χ");
    //add_code("*Y", "Ψ");
    //add_code("*Z", "Ζ");
    //add_code("*T", "Τ");
    //add_code("*U", "Υ");
    //add_code("*W", "Ω");
    //add_code("*P", "Π");
    //add_code("*Q", "Θ");
    //add_code("*R", "Ρ");
    //add_code("*S", "Σ");
    //add_code("*L", "Λ");
    //add_code("*M", "Μ");
    //add_code("*N", "Ν");
    //add_code("*O", "Ο");
    //add_code("*H", "Η");
    //add_code("*I", "Ι");
    //add_code("*K", "Κ");
    //add_code("*D", "Δ");
    //add_code("*E", "Ε");
    //add_code("*F", "Φ");
    //add_code("*G", "Γ");
    //add_code("*A", "Α");
    //add_code("*B", "Β");
    //add_code("*C", "Ξ");
    add_code("A", "Α");
    add_code("E", "Ε");
    //add_code("*)/O", "Ὄ");
    //add_code("*)\\H", "Ἢ");
    add_code("a)", "ἀ");
    add_code("a(", "ἁ");
    add_code("M", "Μ");
    add_code("a/", "ά");
    add_code("Q", "Θ");
    add_code("i(", "ἱ");
    add_code("i+", "ϊ");
    add_code("U", "Υ");
    add_code("i/", "ί");
    add_code("Y", "Ψ");
    add_code("i)/", "ἴ");
    //add_code("*E)", "Ἐ");
    add_code("a=", "ᾶ");
    //add_code("*(\\A", "Ἃ");
    add_code("a", "α");
    //add_code("*)/A", "Ἄ");
    add_code("e", "ε");
    add_code("i", "ι");
    //add_code("*U(", "Ὑ");
    add_code("m", "μ");
    add_code("A(/", "Ἇ");
    add_code("q", "θ");
    add_code("A)", "Ἀ");
    add_code("a)/", "ἄ");
    //add_code("*(R", "Ῥ");
    add_code("u", "υ");
    add_code("I(/", "Ἷ");
    add_code("i)\\", "ἲ");
    add_code("y", "ψ");
    add_code("e)/", "ἔ");
    add_code("A(=", "Ἇ");

    add_code(":", "·"); // Greek middot
    add_code(";", ";"); // Greek question mark
}    
