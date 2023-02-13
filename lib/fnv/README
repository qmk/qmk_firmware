#=====================#
# Fowler/Noll/Vo hash #
#=====================#

The basis of this hash algorithm was taken from an idea sent
as reviewer comments to the IEEE POSIX P1003.2 committee by:

     Phong Vo (http://www.research.att.com/info/kpv)
     Glenn Fowler (http://www.research.att.com/~gsf/)

In a subsequent ballot round:

     Landon Curt Noll (http://www.isthe.com/chongo)

improved on their algorithm.  Some people tried this hash
and found that it worked rather well.  In an EMail message
to Landon, they named it the ``Fowler/Noll/Vo'' or FNV hash.

FNV hashes are designed to be fast while maintaining a low
collision rate. The FNV speed allows one to quickly hash lots
of data while maintaining a reasonable collision rate.  See:

     http://www.isthe.com/chongo/tech/comp/fnv/index.html

for more details as well as other forms of the FNV hash.
Comments, questions, bug fixes and suggestions welcome at
the address given in the above URL.


#==================#
# FNV hash utility #
#==================#

Two hash utilities (32 bit and 64 bit) are provided:

	fnv032 [-b bcnt] [-m] [-s arg] [-t code] [-v] [arg ...]
	fnv132 [-b bcnt] [-m] [-s arg] [-t code] [-v] [arg ...]
	fnv1a32 [-b bcnt] [-m] [-s arg] [-t code] [-v] [arg ...]

	fnv064 [-b bcnt] [-m] [-s arg] [-t code] [-v] [arg ...]
	fnv164 [-b bcnt] [-m] [-s arg] [-t code] [-v] [arg ...]
	fnv1a64 [-b bcnt] [-m] [-s arg] [-t code] [-v] [arg ...]

	-b bcnt	  mask off all but the lower bcnt bits (default: 32)
 	-m	  multiple hashes, one per line for each arg
	-s	  hash arg as a string (ignoring terminating NUL bytes)
	-t code	  0 ==> generate test vectors, 1 ==> test FNV hash
 	-v	  verbose mode, print arg after hash (implies -m)
	arg	  string (if -s was given) or filename (default stdin)

The fnv032, fnv064 implement the historic FNV-0 hash.
The fnv132, fnv164 implement the recommended FNV-1 hash.
The fnv1a32, fnv1a64 implement the recommended FNV-1a hash.

This is the original historic FNV algorithm with a 0 offset basis.
It is recommended that FNV-1, with a non-0 offset basis be used instead.

To test FNV hashes, try:

	fnv032 -t 1 -v
	fnv132 -t 1 -v
	fnv1a32 -t 1 -v

	fnv064 -t 1 -v
	fnv164 -t 1 -v
	fnv1a64 -t 1 -v

If you are compiling, try:

	make check


#==================#
# FNV hash library #
#==================#

The libfnv.a library implements both a 32 bit and a 64 bit FNV hash
on collections of bytes, a NUL terminated strings or on an open file
descriptor.

Here is the 32 bit FNV 1 hash:

	Fnv32_t fnv_32_buf(void *buf, int len, Fnv32_t hval);	/* byte buf */
	Fnv32_t fnv_32_str(char *string, Fnv32_t hval);		/* string */

Here is the 32 bit FNV 1a hash:

	Fnv32_t fnv_32a_buf(void *buf, int len, Fnv32_t hval);	/* byte buf */
	Fnv32_t fnv_32a_str(char *string, Fnv32_t hval);	/* string */

Here is the 64 bit FNV 1 hash:

	Fnv64_t fnv_64_buf(void *buf, int len, Fnv64_t hval);	/* byte buf */
	Fnv64_t fnv_64_str(char *string, Fnv64_t hval);		/* string */

Here is the 64 bit FNV 1a hash:

	Fnv64_t fnv_64a_buf(void *buf, int len, Fnv64_t hval);	/* byte buf */
	Fnv64_t fnv_64a_str(char *string, Fnv64_t hval);	/* string */

On the first call to a hash function, one must supply the initial basis
that is appropriate for the hash in question:

    FNV-0:	(not recommended)

	FNV0_32_INIT		/* 32 bit FNV-0 initial basis */
	FNV0_64_INIT		/* 64 bit FNV-0 initial basis */

    FNV-1:

	FNV1_32_INIT		/* 32 bit FNV-1 initial basis */
	FNV1_64_INIT		/* 64 bit FNV-1 initial basis */

    FNV-1a:

	FNV1A_32_INIT		/* 32 bit FNV-1a initial basis */
	FNV1A_64_INIT		/* 64 bit FNV-1a initial basis */

For example to perform a 64 bit FNV-1 hash:

	#include "fnv.h"

	Fnv64_t hash_val;

	hash_val = fnv_64_str("a string", FNV1_64_INIT);
	hash_val = fnv_64_str("more string", hash_val);

produces the same final hash value as:

	hash_val = fnv_64_str("a stringmore string", FNV1_64_INIT);

NOTE: If one used 'FNV0_64_INIT' instead of 'FNV1_64_INIT' one would get the
      historic FNV-0 hash instead recommended FNV-1 hash.

To perform a 32 bit FNV-1 hash:

	#include "fnv.h"

	Fnv32_t hash_val;

	hash_val = fnv_32_buf(buf, length_of_buf, FNV1_32_INIT);
	hash_val = fnv_32_str("more data", hash_val);

To perform a 64 bit FNV-1a hash:

	#include "fnv.h"

	Fnv64_t hash_val;

	hash_val = fnv_64a_buf(buf, length_of_buf, FNV1_64_INIT);
	hash_val = fnv_64a_str("more data", hash_val);

=-=

chongo <Landon Curt Noll> /\oo/\
http://www.isthe.com/chongo

Share and Enjoy!
