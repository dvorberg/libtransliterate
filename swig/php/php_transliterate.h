/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#ifndef PHP_TRANSLITERATE_H
#define PHP_TRANSLITERATE_H

extern zend_module_entry transliterate_module_entry;
#define phpext_transliterate_ptr &transliterate_module_entry

#ifdef PHP_WIN32
# define PHP_TRANSLITERATE_API __declspec(dllexport)
#else
# define PHP_TRANSLITERATE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(transliterate);
PHP_MSHUTDOWN_FUNCTION(transliterate);
PHP_RINIT_FUNCTION(transliterate);
PHP_RSHUTDOWN_FUNCTION(transliterate);
PHP_MINFO_FUNCTION(transliterate);

ZEND_NAMED_FUNCTION(_wrap_greek_beta_to_utf8);
ZEND_NAMED_FUNCTION(_wrap_greek_utf8_to_beta);
#endif /* PHP_TRANSLITERATE_H */