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

template <typename key_char_type, typename value_char_type>
class trie
{
protected:
    class node
    {
    public:
        key_char_type key;
        value_char_type *value;
            
        node *sibling, *child;

        int childcount;
        node **children;

        node(key_char_type key) {
            this->key = key;

            sibling = NULL;
            child = NULL;

            childcount = 0;
            children = NULL;
        }                

        node *which_child_has_key(key_char_type key) {
            if (children == NULL)
            {
                // Pointer based lookup
                for ( node *here = child; here != NULL; here = here->sibling )
                {
                    if (here->key == key)
                    {
                        return here;
                    }
                }
            }
            else
            {
                int middle, count;
                middle = count = (childcount >> 1) + 1;
                while (true)
                {
                    if (count <= 2)
                    {
                        if (middle > 0 && children[middle-1]->key == key)
                        {
                            return children[middle-1];
                        }
                        else if (children[middle]->key == key)
                        {
                            return children[middle];
                        }
                        else if (middle < childcount-1 &&
                                 children[middle+1]->key == key)
                        {
                            return children[middle+1];
                        }
                        else
                        {
                            return NULL;
                        }
                    }
                    else
                    {
                        count = ( count >> 1) + 1;
                        if (children[middle]->key == key)
                        {
                            return children[middle];
                        }
                        else if (children[middle]->key > key)
                        {
                            middle -= count;
                            if (middle < 0) middle = 0;
                        }
                        else
                        {
                            middle += count;
                            if (middle > childcount-1) middle = childcount-1;
                        }
                    }
                }
            }
            
            return NULL;
        }

        void finalize() {
            if (children != NULL) delete children;
            
            childcount = 0;
            for (node *p = child; p != NULL; p = p->sibling)
            {
                childcount++;
                p->finalize();
            }

            if (childcount > 5)
            {
                children = new node*[childcount];

                int a = 0;
                for (node *p = child; p != NULL; p = p->sibling)
                {
                    children[a] = p;
                    a++;
                }

                // Sort them by key. Those keys are integers, so we can just
                // use < = and >.
                for ( a = 0; a < childcount; a++ )
                {
                    for ( int b = a + 1; b < childcount; b++ )
                    {
                        if ( children[a]->key > children[b]->key )
                        {
                            node *tmp = children[a];
                            children[a] = children[b];
                            children[b] = tmp;
                        }
                    }
                }
            }
        }
    };

    node *root;
    
public:
    trie() {
        root = new node(0);
    };
    
    void add(key_char_type *key, value_char_type *value) {
        node *here = root, *child = NULL;
        for (key_char_type *p = key; *p != 0; p += sizeof(key_char_type))
        {
            child = here->which_child_has_key(*p);
            if (child == NULL)
            {
                child = new node(*p);
                child->sibling = here->child;
                here->child = child;
            }
            here = child;
        }
        
        here->value = value;
    }

    /* Return true if c is a whitespace character. */
    virtual int between_words(key_char_type c) {
        return c == ' ' || c == '\t' || c == '\n' || c == 0;
    }
    
    value_char_type *lookup_next(key_char_type **buffer_p) {
        node *here = root, *child = NULL;

        // If we run into a dead end on the tree, we return the value
        // from the first node we met that carries one and reset the
        // buffer pointer to the char that brought us there.
        value_char_type *first_value = NULL;
        key_char_type *first_value_p = NULL;
        
        do
        {
            value_char_type key;
            if ( between_words(**buffer_p) )
            {
                key = ' ';
            }
            else
            {
                key = **buffer_p;
            }

            child = here->which_child_has_key(key);
            if (here->key == ' ') (*buffer_p)--;

            if (child == NULL)
            {
                if (here->value == 0)
                {
                    if (first_value == NULL)
                    {
                        return NULL;
                    }
                    else
                    {
                        *buffer_p = first_value_p;
                        return first_value;
                    }
                }
                else
                {
                    (*buffer_p)--;
                    return here->value;
                }
            }
            else
            {
                if (first_value == NULL)
                {
                    first_value = child->value;
                    first_value_p = *buffer_p;
                }
                here = child;
            }

            if (**buffer_p == 0) break;
            (*buffer_p)++;
        } while (true);

        return here->value;
    };

    virtual size_t process(key_char_type *input,
                           value_char_type *output_buffer,
                           int buffer_size) {        
        value_char_type *ret_p = output_buffer;
        size_t length = 0;

        key_char_type *p = input;
        value_char_type unrecognized[2];
        unrecognized[1] = 0;

        while (*p != 0)
        {
            value_char_type *append = NULL;

            if (between_words(*p))
            {
                unrecognized[0] = *p;
                append = unrecognized; 
            }
            else
            {
                value_char_type *result = lookup_next(&p);
                if (result == NULL)
                {
                    // We didn't find the byte sequence in the tree and so
                    // we copy the next char verbatim and start over with the
                    // char after that.
                    unrecognized[0] = *p;
                    append = unrecognized;
                }
                else
                {
                    append = result;
                }
            }
            
            int to_append = 0;
            for (value_char_type *q = append; *q != 0; q++)
            {
                to_append++;
            }
            
            if (length + to_append < buffer_size)
            {
                for (value_char_type *q = append; *q != 0; q++)
                {
                    *ret_p = *q;                    
                    *ret_p++;
                    length++;
                }
            }
            else
            {
                // We have reached the end of the output buffer.
                // There is nothing more to do for us but cleanup
                // and return to the caller.
                break;
            }

            if (*p != 0) p++;
        } // while
        
        *ret_p = 0;
        return length; // +1 because of the 0!
    }
    
    void finalize() {
        root->finalize();
    }
};

