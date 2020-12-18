#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xxhash.h"

#include "xxhash.c"

#ifdef COMPILE_DL_XXHASH
	ZEND_GET_MODULE(xxhash);
	#ifdef ZTS
		ZEND_TSRMLS_CACHE_DEFINE();
	#endif
#endif

PHP_MINFO_FUNCTION(xxhash)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xxhash support", "enabled");
	php_info_print_table_row(2, "extension version", PHP_XXHASH_VERSION);
	php_info_print_table_row(2, "xxhash release", "v0.6.1");
	php_info_print_table_end();
}

PHP_FUNCTION(xxhash32)
{
    char *arg = NULL;
    unsigned long long seed = 0;
    size_t arg_len, len;
    zend_string *strg;
	unsigned int sum;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &arg, &arg_len, &seed) == FAILURE || arg_len < 1) {
        return;
    }

    if (!seed) {
        seed = 0;
    }

	// compute the checksum
	sum = XXH32(arg, arg_len, seed);

	// return the checksum
	RETURN_LONG(sum);
}

PHP_FUNCTION(xxhash64)
{
	char *arg = NULL;
	unsigned long long seed = 0;
    size_t arg_len, len;
    zend_string *strg;
	unsigned long long sum;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &arg, &arg_len, &seed) == FAILURE || arg_len < 1) {
        return;
    }

    if (!seed) {
        seed = 0;
    }

	// compute the checksum
	sum = XXH64(arg, arg_len, seed);

    //convert to a signed long long
    sum = (signed long long)sum;

	// return the checksum
	RETURN_LONG(sum);
}

 // the first argument is the name of this arginfo block
    // the second argument is always zero (reserved for future use)
    // the third argument is if it returns a reference
    // the fourth argument is how many arguments are required
ZEND_BEGIN_ARG_INFO_EX(arginfo_xxhash32, 0, 0, 1)
    // the first argument to this
	ZEND_ARG_INFO(0, hash_string)
ZEND_END_ARG_INFO()

// the first argument is the name of this arginfo block
    // the second argument is always zero (reserved for future use)
    // the third argument is if it returns a reference
    // the fourth argument is how many arguments are required

ZEND_BEGIN_ARG_INFO_EX(arginfo_xxhash64, 0, 0, 1)
    // the first argument to this
	ZEND_ARG_INFO(0, hash_string)
ZEND_END_ARG_INFO()

const zend_function_entry xxhash_functions[] = {
	ZEND_FE(xxhash32, arginfo_xxhash32)
	ZEND_FE(xxhash64, arginfo_xxhash64)
	PHP_FE_END
};

zend_module_entry xxhash_module_entry = {
	STANDARD_MODULE_HEADER,
	"xxhash",
	xxhash_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(xxhash),
	PHP_XXHASH_VERSION,
	STANDARD_MODULE_PROPERTIES
};