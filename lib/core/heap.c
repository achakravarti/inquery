/******************************************************************************
 *                     ___                                   
 *                    |_ _|_ __   __ _ _   _  ___ _ __ _   _ 
 *                     | || '_ \ / _` | | | |/ _ \ '__| | | |
 *                     | || | | | (_| | |_| |  __/ |  | |_| |
 *                    |___|_| |_|\__, |\__,_|\___|_|   \__, |
 *                                  |_|                |___/ 
 *
 * Inquery - India Query RESTful microservice
 * Copyright (c) 2020 Abhishek Chakravarti <abhishek@taranjali.org>. 
 * See the accompanying inquery/AUTHORS file for the full list of contributors.
 *
 * This is the inquery/lib/core/heap.c source file; it implements the heap 
 * management interface declared in the inquery/lib/core/core.h header file.
 *
 * This code is released under the GPLv3 License. See the accompanying 
 * inquery/LICENSE file or <http://opensource.org/licenses/GPL-3.0> for complete
 * licensing details.
 *
 * BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT YOU
 * HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/


#include <string.h>
#include "core.h"


/*
 * inquery_heap_new() - allocate new block of heap memory
 */
extern void *inquery_heap_new(size_t sz)
{
    void *bfr;

    inquery_assert (sz);
    inquery_require (bfr = malloc(sz));
    
    memset(bfr, 0, sz);
    return bfr;
}


/*
 * inquery_heap_resize() - resize existing block of heap memory
 */
extern void inquery_heap_resize(void **bfr, size_t sz)
{
    inquery_assert (bfr && *bfr && sz);
    inquery_require (*bfr = realloc(*bfr, sz));
}


/*
 * inquery_heap_free() - free existing block of heap memory
 */
extern void inquery_heap_free(void **bfr)
{
    if (inquery_likely (bfr && *bfr)) {
        free(*bfr);
        *bfr = NULL;
    }
}

