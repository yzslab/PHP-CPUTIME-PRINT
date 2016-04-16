/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_cputime.h"
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

/* If you declare any globals in php_cputime.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(cputime)
*/

/* True global resources - no need for thread safety here */
static int le_cputime;
static clock_t start_time;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("cputime.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_cputime_globals, cputime_globals)
    STD_PHP_INI_ENTRY("cputime.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_cputime_globals, cputime_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_cputime_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_cputime_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "cputime", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_cputime_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_cputime_init_globals(zend_cputime_globals *cputime_globals)
{
	cputime_globals->global_value = 0;
	cputime_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(cputime)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(cputime)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cputime)
{
#if defined(COMPILE_DL_CPUTIME) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	start_time = times(NULL);
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(cputime)
{
	clock_t end_time, clock_time;
	long clockticks;
	clockticks = sysconf(_SC_CLK_TCK);
	struct tms cpu_times;
	end_time = times(&cpu_times);
	clock_time = clock();
	printf("uid: %ld, gid: %ld, euid: %ld, egid: %ld, Natural time: %lf s, User time: %.9lf s, System time: %.9lf s, Total by clock(): %lf s\n", (long) getuid(), (long) getgid(), (long) geteuid(), (long) getegid(), (end_time - start_time) / 100.,  1. * cpu_times.tms_utime / clockticks, 1. * cpu_times.tms_stime / clockticks, 1. * clock_time / CLOCKS_PER_SEC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cputime)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "cputime support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ cputime_functions[]
 *
 * Every user visible function must have an entry in cputime_functions[].
 */
const zend_function_entry cputime_functions[] = {
	PHP_FE(confirm_cputime_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in cputime_functions[] */
};
/* }}} */

/* {{{ cputime_module_entry
 */
zend_module_entry cputime_module_entry = {
	STANDARD_MODULE_HEADER,
	"cputime",
	cputime_functions,
	PHP_MINIT(cputime),
	PHP_MSHUTDOWN(cputime),
	PHP_RINIT(cputime),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(cputime),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(cputime),
	PHP_CPUTIME_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CPUTIME
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(cputime)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
