// macros.h - miscellaneous useful macros

#define EVER ;;

#define ARRLEN(a) (sizeof (a) / sizeof (a)[0])

#define EVEN(i) (((i) & 0x1) == 0x0)
#define  ODD(i) (((i) & 0x1) != 0x0)

#define ISUPPER(l) (((l) & 0x20) == 0x0)
#define ISLOWER(l) (((l) & 0x20) != 0x0)

#define TOUPPER(l) ((l) & 0x5f)
#define TOLOWER(l) ((l) | 0x20)

#define MULPOW2(m, n) ((m) << (n))
#define DIVPOW2(m, n) ((m) >> (n))

#define STRING1(x) #x
#define STRING2(x) STRING1(x)

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define SQR(x) ((x) * (x))

#define SGN(x) CMPR(x, 0)

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define DIM(x, y) MAX(x - y, 0)

#define CLMP(lo, x, hi) MAX(lo, MIN(x, hi))

#define CMPR(x, y) ((x) < (y) ? -1 : (x) > (y) ? 1 : 0)

#define SWAP(x, y) ((x) ^= (y), (y) ^= (x), (x) ^= (y))
