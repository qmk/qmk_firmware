/*
 * have_ulong64 - Determine if we have a 64 bit unsigned long long
 *
 * usage:
 *	have_ulong64 > longlong.h
 *
 * Not all systems have a 'long long type' so this may not compile on
 * your system.
 *
 * This prog outputs the define:
 *
 *	HAVE_64BIT_LONG_LONG
 *		defined ==> we have a 64 bit unsigned long long
 *		undefined ==> we must simulate a 64 bit unsigned long long
 */
/*
 *
 * Please do not copyright this code.  This code is in the public domain.
 *
 * LANDON CURT NOLL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL LANDON CURT NOLL BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * By:
 *	chongo <Landon Curt Noll> /\oo/\
 *      http://www.isthe.com/chongo/
 *
 * Share and Enjoy!	:-)
 */

/*
 * have the compiler try its hand with unsigned and signed long longs
 */
#if ! defined(NO64BIT_LONG_LONG)
unsigned long long val = 1099511628211ULL;
#endif /* NO64BIT_LONG_LONG */

int
main(void)
{
	/*
	 * ensure that the length of long long val is what we expect
	 */
#if defined(NO64BIT_LONG_LONG)
	printf("#undef HAVE_64BIT_LONG_LONG\t/* no */\n");
#else /* NO64BIT_LONG_LONG */
	if (val == 1099511628211ULL && sizeof(val) == 8) {
		printf("#define HAVE_64BIT_LONG_LONG\t/* yes */\n");
	}
#endif /* NO64BIT_LONG_LONG */

	/* exit(0); */
	return 0;
}
