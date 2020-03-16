#include <string.h>
#include "../sds/sds.h"
#include "core.h"


static inquery_string *replace_first(const inquery_string *h, 
        const inquery_string *n, const inquery_string *r)
{
    char *pos = strstr(h, n);
    if (!pos)
        return inquery_string_copy(h);

    const size_t hsz = sdslen((const sds) h);
    const size_t nsz = sdslen((const sds) n);
    const size_t rsz = sdslen((const sds) r);
    const size_t diff = rsz - nsz;

    inquery_string *s = inquery_heap_new(hsz + diff + 1);

    size_t shifts = pos - h;
    memcpy(s, h, shifts);
    memcpy(s + shifts, r, rsz);
    memcpy(s + shifts + rsz, pos + nsz, hsz - shifts - nsz);

    s[hsz + diff] = '\0';
    return s;
}

extern inquery_string *inquery_string_new(const char *cstr)
{
    inquery_assert (cstr && *cstr);

    char *ctx = sdsnew(cstr);
    inquery_require (ctx);

    return ctx;
}


extern inquery_string *inquery_string_new_empty(void)
{
    char *ctx = sdsempty();
    inquery_require (ctx);

    return ctx;
}


extern inquery_string *inquery_string_copy(const inquery_string *ctx)
{
    inquery_assert (ctx);

    sds cp = sdsdup((const sds) ctx);
    inquery_require (cp);

    return cp;
}


extern void inquery_string_free(inquery_string **ctx)
{
    if (inquery_likely (ctx && *ctx)) {
        sdsfree(*ctx);
        *ctx = NULL;
    }
            
}


extern size_t inquery_string_len(const inquery_string *ctx)
{
    register size_t i = 0, len = 0;

    while (ctx[i]) {
        if ((ctx[i] & 0xC0) != 0x80)
            len++;
        i++;
    }

    return len;
}


extern size_t inquery_string_sz(const inquery_string *ctx)
{
    inquery_assert (ctx);

    return sdslen((const sds) ctx) + 1;
}


extern int inquery_string_cmp(const inquery_string *lhs, 
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return sdscmp((const sds) lhs, (const sds) rhs);
}


extern inline bool inquery_string_lt(const inquery_string *lhs,
        const inquery_string *rhs);


extern inline bool inquery_string_eq(const inquery_string *lhs,
        const inquery_string *rhs);


extern inline bool inquery_string_gt(const inquery_string *lhs,
        const inquery_string *rhs);


extern void inquery_string_add(inquery_string **ctx, const inquery_string *add)
{
    inquery_assert (ctx && *ctx && add);

    sds cp = sdsnew(*ctx);
    sdsfree(*ctx);
    *ctx = sdscat(cp, add);
}


extern size_t inquery_string_find(const inquery_string *haystack, 
        const inquery_string *needle)
{
    inquery_assert (haystack && needle);

    inquery_string *pos = strstr(haystack, needle);
    return pos ? inquery_string_len(haystack) - inquery_string_len(pos) + 1 : 0;
}


extern inquery_string *inquery_string_replace(const inquery_string *haystack, 
        const inquery_string *needle, const inquery_string *replace)
{
    inquery_assert(haystack && replace && needle && *needle);

    register inquery_string *r;
    if (inquery_likely (!strstr(replace, needle))) {
        r = replace_first(haystack, needle, replace);
        while (strstr(r, needle))
            r = replace_first(r, needle, replace);

        return r;
    }

    const char placeholder[] = { 0x1, 0x0 };
    r = replace_first(haystack, needle, placeholder);
    while (strstr(r, needle))
        r = replace_first(r, needle, placeholder);

    r = replace_first(r, placeholder, replace);
    while (strstr(r, placeholder))
        r = replace_first(r, placeholder, replace);

    return r;
}


extern inquery_string *inquery_string_replace_first(
        const inquery_string *haystack, const inquery_string *needle,
        const inquery_string *replace)
{
    inquery_assert(haystack && needle && *needle && replace);

    return replace_first(haystack, needle, replace);
}

