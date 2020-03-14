#if (!defined INQUERY_CORE_HEADER_INCLUDED)
#define INQUERY_CORE_HEADER_INCLUDED


#if (defined __GNUC__ || defined __clang__)
#   define inq_likely(p) (__builtin_expect (!!(p), 1))
#else
#   define inq_likely(p) (p)
#endif


#if (defined __GNUC__ || defined __clang__)
#   define inq_unlikely(p) (__builtin_expect (!!(p), 0))
#else
#   define inq_unlikely(p) (p)
#endif


#endif /* INQUERY_CORE_HEADER_INCLUDED */

