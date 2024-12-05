/*
 * fnv_64 - 64 bit Fowler/Noll/Vo hash of a buffer or string
 *
 * @(#) $Revision: 5.5 $
 * @(#) $Id: fnv64.c,v 5.5 2012/03/21 01:38:12 chongo Exp $
 * @(#) $Source: /usr/local/src/cmd/fnv/RCS/fnv64.c,v $
 *
 ***
 *
 * Fowler/Noll/Vo hash
 *
 * The basis of this hash algorithm was taken from an idea sent
 * as reviewer comments to the IEEE POSIX P1003.2 committee by:
 *
 *      Phong Vo (http://www.research.att.com/info/kpv/)
 *      Glenn Fowler (http://www.research.att.com/~gsf/)
 *
 * In a subsequent ballot round:
 *
 *      Landon Curt Noll (http://www.isthe.com/chongo/)
 *
 * improved on their algorithm.  Some people tried this hash
 * and found that it worked rather well.  In an EMail message
 * to Landon, they named it the ``Fowler/Noll/Vo'' or FNV hash.
 *
 * FNV hashes are designed to be fast while maintaining a low
 * collision rate. The FNV speed allows one to quickly hash lots
 * of data while maintaining a reasonable collision rate.  See:
 *
 *      http://www.isthe.com/chongo/tech/comp/fnv/index.html
 *
 * for more details as well as other forms of the FNV hash.
 *
 ***
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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "longlong.h"
#include "fnv.h"

#define WIDTH 64	/* bit width of hash */

#define BUF_SIZE (32*1024)	/* number of bytes to hash at a time */

static char *usage =
"usage: %s [-b bcnt] [-m] [-s arg] [-t code] [-v] [arg ...]\n"
"\n"
"\t-b bcnt\tmask off all but the lower bcnt bits (default 64)\n"
"\t-m\tmultiple hashes, one per line for each arg\n"
"\t-s\thash arg as a string (ignoring terminating NUL bytes)\n"
"\t-t code\t  test hash code: (0 ==> generate test vectors\n"
"\t\t\t\t   1 ==> validate against FNV test vectors)\n"
"\t-v\tverbose mode, print arg after hash (implies -m)\n"
"\targ\tstring (if -s was given) or filename (default stdin)\n"
"\n"
"\tNOTE: Programs that begin with fnv0 implement the FNV-0 hash.\n"
"\t      The FNV-0 hash is historic FNV algorithm that is now deprecated.\n"
"\n"
"\tSee http://www.isthe.com/chongo/tech/comp/fnv/index.html for more info.\n"
"\n"
"\t@(#) FNV Version: %s\n";
static char *program;	/* our name */


/*
 * test_fnv64 - test the FNV64 hash
 *
 * given:
 *	hash_type	type of FNV hash to test
 *	init_hval	initial hash value
 *	mask	  	lower bit mask
 *	v_flag	  	1 => print test failure info on stderr
 *	code	  0 ==> generate FNV test vectors
 *		  1 ==> validate against FNV test vectors
 *
 * returns:	0 ==> OK, else test vector failure number
 */
static int
test_fnv64(enum fnv_type hash_type, Fnv64_t init_hval,
	   Fnv64_t mask, int v_flag, int code)
{
    struct test_vector *t;	/* FNV test vestor */
    Fnv64_t hval;		/* current hash value */
    int tstnum;			/* test vector that failed, starting at 1 */

    /*
     * print preamble if generating test vectors
     */
    if (code == 0) {
	switch (hash_type) {
	case FNV0_64:
	    printf("struct fnv0_64_test_vector fnv0_64_vector[] = {\n");
	    break;
	case FNV1_64:
	    printf("struct fnv1_64_test_vector fnv1_64_vector[] = {\n");
	    break;
	case FNV1a_64:
	    printf("struct fnv1a_64_test_vector fnv1a_64_vector[] = {\n");
	    break;
	default:
	    unknown_hash_type(program, hash_type, 12);	/* exit(12) */
	    /*NOTREACHED*/
    	}
    }

    /*
     * loop thru all test vectors
     */
    for (t = fnv_test_str, tstnum = 1; t->buf != NULL; ++t, ++tstnum) {

        /*
	 * compute the FNV hash
	 */
	hval = init_hval;
	switch (hash_type) {
	case FNV0_64:
	case FNV1_64:
	    hval = fnv_64_buf(t->buf, t->len, hval);
	    break;
	case FNV1a_64:
	    hval = fnv_64a_buf(t->buf, t->len, hval);
	    break;
	default:
	    unknown_hash_type(program, hash_type, 13);	/* exit(13) */
	    /*NOTREACHED*/
	}

	/*
	 * print the vector
	 */
#if defined(HAVE_64BIT_LONG_LONG)
	/*
	 * HAVE_64BIT_LONG_LONG testing
	 */
	switch (code) {
	case 0:		/* generate the test vector */
	    printf("    { &fnv_test_str[%d], (Fnv64_t) 0x%016llxULL },\n",
	    	   tstnum-1, hval & mask);
	    break;

	case 1:		/* validate against test vector */
	    switch (hash_type) {
	    case FNV0_64:
		if ((hval&mask) != (fnv0_64_vector[tstnum-1].fnv0_64 & mask)) {
		    if (v_flag) {
		    	fprintf(stderr, "%s: failed fnv0_64 test # %d\n",
				program, tstnum);
		    	fprintf(stderr, "%s: test # 1 is 1st test\n", program);
			fprintf(stderr,
			    "%s: expected 0x%016llx != generated: 0x%016llx\n",
			    program,
			    (hval&mask),
			    (fnv0_64_vector[tstnum-1].fnv0_64 & mask));
		    }
		    return tstnum;
		}
	    	break;
	    case FNV1_64:
		if ((hval&mask) != (fnv1_64_vector[tstnum-1].fnv1_64 & mask)) {
		    if (v_flag) {
		    	fprintf(stderr, "%s: failed fnv1_64 test # %d\n",
				program, tstnum);
		    	fprintf(stderr, "%s: test # 1 is 1st test\n", program);
			fprintf(stderr,
			    "%s: expected 0x%016llx != generated: 0x%016llx\n",
			    program,
			    (hval&mask),
			    (fnv1_64_vector[tstnum-1].fnv1_64 & mask));
		    }
		    return tstnum;
		}
	    	break;
	    case FNV1a_64:
		if ((hval&mask) != (fnv1a_64_vector[tstnum-1].fnv1a_64 &mask)) {
		    if (v_flag) {
		    	fprintf(stderr, "%s: failed fnv1a_64 test # %d\n",
				program, tstnum);
		    	fprintf(stderr, "%s: test # 1 is 1st test\n", program);
			fprintf(stderr,
			    "%s: expected 0x%016llx != generated: 0x%016llx\n",
			    program,
			    (hval&mask),
			    (fnv1a_64_vector[tstnum-1].fnv1a_64 & mask));
		    }
		    return tstnum;
		}
	    	break;
	    }
	    break;

    	default:
	    fprintf(stderr, "%s: -m %d not implemented yet\n", program, code);
	    exit(14);
    	}
#else /* HAVE_64BIT_LONG_LONG */
	/*
	 * non HAVE_64BIT_LONG_LONG testing
	 */
	switch (code) {
	case 0:		/* generate the test vector */
	    printf("    { &fnv_test_str[%d], "
	    	   "(Fnv64_t) {0x%08lxUL, 0x%08lxUL} },\n",
	    	   tstnum-1,
		   (hval.w32[0] & mask.w32[0]),
		   (hval.w32[1] & mask.w32[1]));
	    break;

	case 1:		/* validate against test vector */
	    switch (hash_type) {
	    case FNV0_64:
		if (((hval.w32[0] & mask.w32[0]) !=
		     (fnv0_64_vector[tstnum-1].fnv0_64.w32[0] &
		      mask.w32[0])) &&
		    ((hval.w32[1] & mask.w32[1]) !=
		     (fnv0_64_vector[tstnum-1].fnv0_64.w32[1] &
		      mask.w32[1]))) {
		    if (v_flag) {
		    	fprintf(stderr, "%s: failed fnv0_64 test # %d\n",
				program, tstnum);
		    	fprintf(stderr, "%s: test # 1 is 1st test\n", program);
			fprintf(stderr,
			    "%s: expected 0x%08llx%08llx != "
			    "generated: 0x%08llx%08llx\n",
			    program,
			    (hval.w32[0] & mask.w32[0]),
			    (hval.w32[1] & mask.w32[1]),
			    ((fnv0_64_vector[tstnum-1].fnv0_64.w32[0] &
			     mask.w32[0])),
			    ((fnv0_64_vector[tstnum-1].fnv0_64.w32[1] &
			     mask.w32[1])));
		    }
		    return tstnum;
		}
	    	break;
	    case FNV1_64:
		if (((hval.w32[0] & mask.w32[0]) !=
		     (fnv1_64_vector[tstnum-1].fnv1_64.w32[0] &
		      mask.w32[0])) &&
		    ((hval.w32[1] & mask.w32[1]) !=
		     (fnv1_64_vector[tstnum-1].fnv1_64.w32[1] &
		      mask.w32[1]))) {
		    if (v_flag) {
		    	fprintf(stderr, "%s: failed fnv1_64 test # %d\n",
				program, tstnum);
		    	fprintf(stderr, "%s: test # 1 is 1st test\n", program);
			fprintf(stderr,
			    "%s: expected 0x%08llx%08llx != "
			    "generated: 0x%08llx%08llx\n",
			    program,
			    (hval.w32[0] & mask.w32[0]),
			    (hval.w32[1] & mask.w32[1]),
			    ((fnv1_64_vector[tstnum-1].fnv1_64.w32[0] &
			     mask.w32[0])),
			    ((fnv1_64_vector[tstnum-1].fnv1_64.w32[1] &
			     mask.w32[1])));
		    }
		    return tstnum;
		}
	    	break;
	    case FNV1a_64:
		if (((hval.w32[0] & mask.w32[0]) !=
		     (fnv1a_64_vector[tstnum-1].fnv1a_64.w32[0] &
		      mask.w32[0])) &&
		    ((hval.w32[1] & mask.w32[1]) !=
		     (fnv1a_64_vector[tstnum-1].fnv1a_64.w32[1] &
		      mask.w32[1]))) {
		    if (v_flag) {
		    	fprintf(stderr, "%s: failed fnv1a_64 test # %d\n",
				program, tstnum);
		    	fprintf(stderr, "%s: test # 1 is 1st test\n", program);
			fprintf(stderr,
			    "%s: expected 0x%08llx%08llx != "
			    "generated: 0x%08llx%08llx\n",
			    program,
			    (hval.w32[0] & mask.w32[0]),
			    (hval.w32[1] & mask.w32[1]),
			    ((fnv1a_64_vector[tstnum-1].fnv1a_64.w32[0] &
			     mask.w32[0])),
			    ((fnv1a_64_vector[tstnum-1].fnv1a_64.w32[1] &
			     mask.w32[1])));
		    }
		    return tstnum;
		}
	    	break;
	    }
	    break;

    	default:
	    fprintf(stderr, "%s: -m %d not implemented yet\n", program, code);
	    exit(15);
    	}
#endif /* HAVE_64BIT_LONG_LONG */
    }

    /*
     * print completion if generating test vectors
     */
    if (code == 0) {
#if defined(HAVE_64BIT_LONG_LONG)
	printf("    { NULL, (Fnv64_t) 0 }\n");
#else /* HAVE_64BIT_LONG_LONG */
	printf("    { NULL, (Fnv64_t) {0,0} }\n");
#endif /* HAVE_64BIT_LONG_LONG */
	printf("};\n");
    }

    /*
     * no failures, return code 0 ==> all OK
     */
    return 0;
}


/*
 * main - the main function
 *
 * See the above usage for details.
 */
int
main(int argc, char *argv[])
{
    char buf[BUF_SIZE+1];	/* read buffer */
    int readcnt;		/* number of characters written */
    Fnv64_t hval;		/* current hash value */
    int s_flag = 0;		/* 1 => -s was given, hash args as strings */
    int m_flag = 0;		/* 1 => print multiple hashes, one per arg */
    int v_flag = 0;		/* 1 => verbose hash print */
    int b_flag = WIDTH;		/* -b flag value */
    int t_flag = -1;		/* FNV test vector code (0=>print, 1=>test) */
    enum fnv_type hash_type = FNV_NONE;	/* type of FNV hash to perform */
    Fnv64_t bmask;		/* mask to apply to output */
    extern char *optarg;	/* option argument */
    extern int optind;		/* argv index of the next arg */
    int fd;			/* open file to process */
    char *p;
    int i;

    /*
     * parse args
     */
    program = argv[0];
    while ((i = getopt(argc, argv, "b:mst:v")) != -1) {
	switch (i) {
	case 'b':	/* bcnt bit mask count */
	    b_flag = atoi(optarg);
	    break;
	case 'm':	/* print multiple hashes, one per arg */
	    m_flag = 1;
	    break;
	case 's':	/* hash args as strings */
	    s_flag = 1;
	    break;
	case 't':	/* FNV test vector code */
	    t_flag = atoi(optarg);
	    if (t_flag < 0 || t_flag > 1) {
		fprintf(stderr, "%s: -t code must be 0 or 1\n", program);
		fprintf(stderr, usage, program, FNV_VERSION);
		exit(1);
	    }
	    m_flag = 1;
	    break;
	case 'v':	/* verbose hash print */
	    m_flag = 1;
	    v_flag = 1;
	    break;
	default:
	    fprintf(stderr, usage, program, FNV_VERSION);
	    exit(1);
	}
    }
    /* -t code incompatible with -b, -m and args */
    if (t_flag >= 0) {
    	if (b_flag != WIDTH) {
	    fprintf(stderr, "%s: -t code incompatible with -b\n", program);
	    exit(2);
	}
    	if (s_flag != 0) {
	    fprintf(stderr, "%s: -t code incompatible with -s\n", program);
	    exit(3);
	}
	if (optind < argc) {
	    fprintf(stderr, "%s: -t code incompatible args\n", program);
	    exit(4);
	}
    }
    /* -s requires at least 1 arg */
    if (s_flag && optind >= argc) {
	fprintf(stderr, usage, program, FNV_VERSION);
	exit(5);
    }
    /* limit -b values */
    if (b_flag < 0 || b_flag > WIDTH) {
	fprintf(stderr, "%s: -b bcnt: %d must be >= 0 and < %d\n",
		program, b_flag, WIDTH);
	exit(6);
    }
#if defined(HAVE_64BIT_LONG_LONG)
    if (b_flag == WIDTH) {
	bmask = (Fnv64_t)0xffffffffffffffffULL;
    } else {
	bmask = (Fnv64_t)((1ULL << b_flag) - 1ULL);
    }
#else /* HAVE_64BIT_LONG_LONG */
    if (b_flag == WIDTH) {
	bmask.w32[0] = 0xffffffffUL;
	bmask.w32[1] = 0xffffffffUL;
    } else if (b_flag >= WIDTH/2) {
	bmask.w32[0] = 0xffffffffUL;
	bmask.w32[1] = ((1UL << (b_flag-(WIDTH/2))) - 1UL);
    } else {
	bmask.w32[0] = ((1UL << b_flag) - 1UL);
	bmask.w32[1] = 0UL;
    }
#endif /* HAVE_64BIT_LONG_LONG */

    /*
     * start with the initial basis depending on the hash type
     */
    p = strrchr(program, '/');
    if (p == NULL) {
	p = program;
    } else {
	++p;
    }
    if (strcmp(p, "fnv064") == 0 || strcmp(p, "no64bit_fnv064") == 0) {
	/* using non-recommended FNV-0 and zero initial basis */
	hval = FNV0_64_INIT;
	hash_type = FNV0_64;
    } else if (strcmp(p, "fnv164") == 0 || strcmp(p, "no64bit_fnv164") == 0) {
	/* using FNV-1 and non-zero initial basis */
	hval = FNV1_64_INIT;
	hash_type = FNV1_64;
    } else if (strcmp(p, "fnv1a64") == 0 || strcmp(p, "no64bit_fnv1a64") == 0) {
	 /* start with the FNV-1a initial basis */
	hval = FNV1A_64_INIT;
	hash_type = FNV1a_64;
    } else {
	fprintf(stderr, "%s: unknown program name, unknown hash type\n",
		program);
	exit(7);
    }

    /*
     * FNV test vector processing, if needed
     */
    if (t_flag >= 0) {
	int code;		/* test vector that failed, starting at 1 */

	/*
	 * perform all tests
	 */
	code = test_fnv64(hash_type, hval, bmask, v_flag, t_flag);

	/*
	 * evaluate the tests
	 */
	if (code == 0) {
	    if (v_flag) {
	    	printf("passed\n");
	    }
	    exit(0);
	} else {
	    printf("failed vector (1 is 1st test): %d\n", code);
	    exit(8);
	}
    }

    /*
     * string hashing
     */
    if (s_flag) {

	/* hash any other strings */
	for (i=optind; i < argc; ++i) {
	    switch (hash_type) {
	    case FNV0_64:
	    case FNV1_64:
		hval = fnv_64_str(argv[i], hval);
	    	break;
	    case FNV1a_64:
		hval = fnv_64a_str(argv[i], hval);
		break;
	    default:
		unknown_hash_type(program, hash_type, 9);	/* exit(9) */
		/*NOTREACHED*/
	    }
	    if (m_flag) {
		print_fnv64(hval, bmask, v_flag, argv[i]);
	    }
	}


    /*
     * file hashing
     */
    } else {

	/*
	 * case: process only stdin
	 */
	if (optind >= argc) {

	    /* case: process only stdin */
	    while ((readcnt = read(0, buf, BUF_SIZE)) > 0) {
		switch (hash_type) {
		case FNV0_64:
		case FNV1_64:
		    hval = fnv_64_buf(buf, readcnt, hval);
		    break;
		case FNV1a_64:
		    hval = fnv_64a_buf(buf, readcnt, hval);
		    break;
		default:
		    unknown_hash_type(program, hash_type, 10);	/* exit(10) */
		    /*NOTREACHED*/
		}
	    }
	    if (m_flag) {
		print_fnv64(hval, bmask, v_flag, "(stdin)");
	    }

	} else {

	    /*
	     * process any other files
	     */
	    for (i=optind; i < argc; ++i) {

		/* open the file */
		fd = open(argv[i], O_RDONLY);
		if (fd < 0) {
		    fprintf(stderr, "%s: unable to open file: %s\n",
			    program, argv[i]);
		    exit(4);
		}

		/*  hash the file */
		while ((readcnt = read(fd, buf, BUF_SIZE)) > 0) {
		    switch (hash_type) {
		    case FNV0_64:
		    case FNV1_64:
			hval = fnv_64_buf(buf, readcnt, hval);
			break;
		    case FNV1a_64:
			hval = fnv_64a_buf(buf, readcnt, hval);
			break;
		    default:
			unknown_hash_type(program, hash_type, 11);/* exit(11) */
			/*NOTREACHED*/
		    }
		}

		/* finish processing the file */
		if (m_flag) {
		    print_fnv64(hval, bmask, v_flag, argv[i]);
		}
		close(fd);
	    }
	}
    }

    /*
     * report hash and exit
     */
    if (!m_flag) {
	print_fnv64(hval, bmask, v_flag, "");
    }
    return 0;	/* exit(0); */
}
