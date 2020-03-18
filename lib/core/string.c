#include <string.h>
#include "../sds/sds.h"
#include "core.h"


static void replace_first(inquery_string **h, const inquery_string *n, 
        const inquery_string *r)
{
    char *pos = strstr(*h, n);
    if (!pos)
        return;

    const size_t hsz = strlen(*h);
    const size_t nsz = strlen(n);
    const size_t rsz = strlen(r);
    const size_t diff = rsz - nsz;

    inquery_string *s = inquery_heap_new(hsz + diff + 1);
    size_t shifts = pos - *h;
    memcpy(s, *h, shifts);
    memcpy(s + shifts, r, rsz);
    memcpy(s + shifts + rsz, pos + nsz, hsz - shifts - nsz);
    s[hsz + diff] = '\0';

    inquery_string_free(h);
    *h = s;
}

extern inquery_string *inquery_string_new(const char *cstr)
{
    inquery_assert (cstr);

    size_t len = strlen(cstr);
    char *ctx = inquery_heap_new(len + 1);

    strncpy(ctx, cstr, len);
    ctx[len] = '\0';

    return ctx;
}


extern inquery_string *inquery_string_new_empty(void)
{
    return inquery_string_new("");
}


extern inquery_string *inquery_string_copy(const inquery_string *ctx)
{
    inquery_assert (ctx);

    return inquery_string_new(ctx);
}


extern void inquery_string_free(inquery_string **ctx)
{
    inquery_heap_free((void **) ctx);
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

    return strlen(ctx) + 1;
}


extern int inquery_string_cmp(const inquery_string *lhs, 
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return strcmp(lhs, rhs);
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

    inquery_string *oldstr = *ctx;
  
    size_t oldlen = strlen(oldstr);
    size_t addlen = strlen(add);
    size_t newlen = oldlen + addlen;

    inquery_string *newstr = inquery_heap_new(newlen + 1);
    strncpy(newstr, oldstr, oldlen);
    strncpy(newstr + oldlen, add, addlen);
    newstr[newlen] = '\0';

    inquery_heap_free((void **) ctx);
    *ctx = newstr;
}


extern size_t inquery_string_find(const inquery_string *ctx, 
        const inquery_string *what)
{
    inquery_assert (ctx && what);

    inquery_string *pos = strstr(ctx, what);
    return pos ? inquery_string_len(ctx) - inquery_string_len(pos) + 1 : 0;
}


extern size_t inquery_string_count(const inquery_string *ctx,
        const inquery_string *what)
{
    inquery_assert (ctx && what);

    size_t count = 0;
    const char *itr = ctx;

    while ((itr = strstr(itr, what))) {
        count++;
        itr++;
    }

    return count;
}


extern void inquery_string_replace(inquery_string **ctx, 
        const inquery_string *what, const inquery_string *with)
{
    inquery_assert(ctx && *ctx && what && *what && with);

    if (inquery_likely (!strstr(with, what))) {
        replace_first(ctx, what, with);
        while (strstr(*ctx, what))
            replace_first(ctx, what, with);

        return;
    }

    const char placeholder[] = { 0x1, 0x0 };
    replace_first(ctx, what, placeholder);
    while (strstr(*ctx, what))
        replace_first(ctx, what, placeholder);

    replace_first(ctx, placeholder, with);
    while (strstr(*ctx, placeholder))
        replace_first(ctx, placeholder, with);
}


extern void inquery_string_replace_first(inquery_string **ctx, 
        const inquery_string *what, const inquery_string *with)
{
    inquery_assert(ctx && *ctx && what && *what && with);
   
    replace_first(ctx, what, with); 
}

