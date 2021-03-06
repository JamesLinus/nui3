/*
 * Copyright 1999 Computing Research Labs, New Mexico State University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COMPUTING RESEARCH LAB OR NEW MEXICO STATE UNIVERSITY BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
 * OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef _h_ucpgba
#define _h_ucpgba

/*
 * $Id: ucpgba.h,v 1.4 1999/11/19 15:24:30 mleisher Exp $
 */

#ifdef __cplusplus
extern "C" {
#endif

#undef __
#ifdef __STDC__
#define __(x) x
#else
#define __(x) ()
#endif

/***************************************************************************
 *
 * Macros and types.
 *
 ***************************************************************************/

/*
 * These are the direction values that can appear in render runs and render
 * strings.
 */
#define UCPGBA_LTR 0
#define UCPGBA_RTL 1

/*
 * These are the flags for cursor motion.
 */
#define UCPGBA_CURSOR_VISUAL  0
#define UCPGBA_CURSOR_LOGICAL 1

/*
 * This structure is used to contain runs of text in a particular direction.
 */
typedef struct _ucrun_t {
    struct _ucrun_t *visual_prev;  /* Pointer to the previous visual run.    */
    struct _ucrun_t *visual_next;  /* Pointer to the next visual run.        */

    struct _ucrun_t *logical_prev; /* Pointer to the previous logical run.   */
    struct _ucrun_t *logical_next; /* Pointer to the next logical run.       */

    int32_t direction;                 /* Direction of the run.                  */

    int32_t cursor;                   /* Position of "cursor" in the string.    */

    uint32_t *chars;          /* List of characters for the run.        */
    uint32_t *positions;      /* List of original positions in source.  */

    uint32_t *source;         /* The source string.                     */
    uint32_t start;           /* Beginning offset in the source string. */
    uint32_t end;             /* Ending offset in the source string.    */
} ucrun_t;

/*
 * This represents a string of runs rendered up to a point that is not
 * platform specific.
 */
typedef struct _ucstring_t {
    int32_t direction;                /* Overall direction of the string.       */

    int32_t cursor_motion;            /* Logical or visual cursor motion flag.  */

    ucrun_t *cursor;              /* The run containing the "cursor."       */

    ucrun_t *logical_first;       /* First run in the logical order.        */
    ucrun_t *logical_last;        /* Last run in the logical order.         */

    ucrun_t *visual_first;        /* First run in the visual order.         */
    ucrun_t *visual_last;         /* Last run in the visual order.          */

    uint32_t *source;        /* The source string.                     */
    uint32_t start;          /* The beginning offset in the source.    */
    uint32_t end;            /* The ending offset in the source.       */
} ucstring_t;

/***************************************************************************
 *
 * API
 *
 ***************************************************************************/

/*
 * This creates and reorders the specified substring using the
 * "Pretty Good Bidi Algorithm."  A default direction is provided for cases
 * of a string containing no strong direction characters and the default
 * cursor motion should be provided.
 */
extern ucstring_t *ucstring_create __((uint32_t *source,
                                       uint32_t start,
                                       uint32_t end,
                                       int32_t default_direction,
                                       int32_t cursor_motion));
/*
 * This releases the string.
 */
extern void ucstring_free __((ucstring_t *string));

/*
 * This changes the cursor motion flag for the string.
 */
extern int32_t ucstring_set_cursor_motion __((ucstring_t *string,
                                          int32_t cursor_motion));

/*
 * This function will move the cursor to the right depending on the
 * type of cursor motion that was specified for the string.
 *
 * A 0 is returned if no cursor motion is performed, otherwise a
 * 1 is returned.
 */
extern int32_t ucstring_cursor_right __((ucstring_t *string, int32_t count));

/*
 * This function will move the cursor to the left depending on the
 * type of cursor motion that was specified for the string.
 *
 * A 0 is returned if no cursor motion is performed, otherwise a
 * 1 is returned.
 */
extern int32_t ucstring_cursor_left __((ucstring_t *string, int32_t count));

/*
 * This routine retrieves the direction of the run containing the cursor
 * and the actual position in the original text string.
 */
extern void ucstring_cursor_info __((ucstring_t *string, int32_t *direction,
                                     uint32_t *position));

#undef __

#ifdef __cplusplus
}
#endif

#endif /* _h_ucpgba */
