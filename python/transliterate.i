%module transliterate
%{
#include <transliterate.h>

char *greek_beta_to_utf8_w(char *beta)
{
    size_t buflen = strlen(beta) * 3;
    char *buffer = (char *)malloc(buflen);
    greek_beta_to_utf8(beta, buffer, buflen);
    return buffer;
}

char *greek_utf8_to_beta_w(char *utf8)
{
    size_t buflen = strlen(utf8);
    char *buffer = (char *)malloc(buflen);
    greek_utf8_to_beta(utf8, buffer, buflen);
    return buffer;
}
%}

%rename(greek_beta_to_utf8) greek_beta_to_utf8_w;
%rename(greek_utf8_to_beta) greek_utf8_to_beta_w;

char *greek_beta_to_utf8_w(char *beta);
char *greek_utf8_to_beta_w(char *utf8);
                            

