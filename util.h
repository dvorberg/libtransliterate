/* Return true if c is a whitespace character. */
inline int between_words(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == 0 || c == ','
        || c == '.' || c == ';' || c == ':' || c == '-';
}

inline char upcase(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }
    else
    {
        return c;
    }
}

inline char downcase(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + ('a' - 'A');
    }
    else
    {
        return c;
    }
}
