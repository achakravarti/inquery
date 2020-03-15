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
 * This is the inquery/lib/core/object.c source file; it implements the object 
 * model interface declared in the inquery/lib/core/core.h header file.
 *
 * This code is released under the GPLv3 License. See the accompanying 
 * inquery/LICENSE file or <http://opensource.org/licenses/GPL-3.0> for complete
 * licensing details.
 *
 * BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT YOU
 * HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/


#include "core.h"


/*
 * inquery_object - reference counted object
 */
struct inquery_object {
    struct inquery_object_vtable vt;
    size_t nref;
    void *payload;
};


/*
 * payload_copy_default() - default copy callback for payload v-table
 */
static inline void *payload_copy_default(const void *payload)
{
    return (void *) payload;;
}


/*
 * payload_free_default() - default free callback for payload v-table
 */
static inline void payload_free_default(void *payload)
{
    (void) payload;
}


/*
 * inquery_object_new() - create new object
 */
extern inquery_object *inquery_object_new(void *payload,
        const struct inquery_object_vtable *vt)
{
    inquery_assert (payload);
    inquery_assert (vt);

    inquery_object *ctx = inquery_heap_new(sizeof *ctx);

    ctx->nref = 1;
    ctx->payload = payload;

    ctx->vt.payload_copy = vt->payload_copy 
            ? vt->payload_copy : payload_copy_default;
    ctx->vt.payload_free = vt->payload_free 
            ? vt->payload_free : payload_free_default;

    return ctx;
}


/*
 * inquery_object_new_noload() - create new object without payload
 */
extern inquery_object *inquery_object_new_noload(void)
{
    inquery_object *ctx = inquery_heap_new(sizeof *ctx);

    ctx->nref = 1;
    ctx->payload = NULL;

    ctx->vt.payload_copy = payload_copy_default;
    ctx->vt.payload_free = payload_free_default;

    return ctx;
}


/*
 * inquery_object_copy() - copy existing object
 */
extern inquery_object *inquery_object_copy(const inquery_object *ctx)
{
    inquery_assert (ctx);

    inquery_object *cp = (inquery_object *) ctx;
    cp->nref++;

    return cp;
}


/*
 * inquery_object_free() - free object from heap memory
 */
extern void inquery_object_free(inquery_object **ctx)
{
    inquery_object *hnd;

    if (inquery_likely (ctx && (hnd = *ctx))) {
        if (!--hnd->nref) {
            hnd->vt.payload_free(hnd->payload);
            inquery_heap_free(&hnd->payload);
            inquery_heap_free((void **) ctx);
        }
    }
}


/*
 * inquery_object_payload() - get constant handle to object payload
 */
extern const void *inquery_object_payload(const inquery_object *ctx)
{
    inquery_assert (ctx);

    return ctx->payload;
}


/*
 * inquery_object_payload_mutable() - get mutable handle to object payload
 */
extern void *inquery_object_payload_mutable(inquery_object **ctx)
{
    inquery_assert (ctx && *ctx);

    inquery_object *hnd = *ctx;
    if (hnd->nref > 1) {
        inquery_object *cp = inquery_object_new(
                hnd->vt.payload_copy(hnd->payload), &hnd->vt);
        inquery_object_free(ctx);
        *ctx = cp;
    }

    return (*ctx)->payload;
}

