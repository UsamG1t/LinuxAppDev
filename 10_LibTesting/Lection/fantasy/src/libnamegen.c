/* Fantasy name generator ANSI C header library
 * This is free and unencumbered software released into the public domain.
 *
 * The compile() function creates a name generator based on an input
 * pattern. The letters s, v, V, c, B, C, i, m, M, D, and d represent
 * different types of random replacements. Everything else is emitted
 * literally.
 *
 *   s - generic syllable
 *   v - vowel
 *   V - vowel or vowel combination
 *   c - consonant
 *   B - consonant or consonant combination suitable for beginning a word
 *   C - consonant or consonant combination suitable anywhere in a word
 *   i - insult
 *   m - mushy name
 *   M - mushy name ending
 *   D - consonant suited for a stupid person's name
 *   d - syllable suited for a stupid person's name (begins with a vowel)
 *
 * All characters between parenthesis () are emitted literally. For
 * example, the pattern "s(dim)", emits a random generic syllable
 * followed by "dim".
 *
 * Characters between angle brackets <> emit patterns from the table
 * above. Imagine the entire pattern is wrapped in one of these.
 *
 * In both types of groupings, a vertical bar | denotes a random choice.
 * Empty groups are allowed. For example, "(foo|bar)" emits either "foo"
 * or "bar". The pattern "<c|v|>" emits a constant, vowel, or nothing at
 * all.
 *
 * An exclamation point ! means to capitalize the component that follows
 * it. For example, "!(foo)" will emit "Foo" and "v!s" will emit a
 * lowercase vowel followed by a capitalized syllable, like "eRod".
 *
 * This library is based on the RinkWorks Fantasy Name Generator.
 * http://www.rinkworks.com/namegen/
 */
#include "namegen.h"
#include "const.h"

/* Generate a name into DST of LEN bytes from PATTERN and using SEED.
 *
 * The length must be non-zero. For best results, the lower 32 bits of
 * the seed should be thoroughly initialized. A particular seed will
 * produce the same results on all platforms.
 *
 * The return value is one of the above codes, indicating success or
 * that something went wrong. Truncation occurs when DST was too short.
 * Pattern is validated even when the output has been truncated.
 */

/* Implementation */

/* Rather than compile the pattern into some internal representation,
 * the name is generated directly from the pattern in a single pass
 * using reservoir sampling. If an alternate option is selected, the
 * output pointer is reset to "undo" the output for the previous group.
 * This means the output buffer may be written beyond the final output
 * length (but never beyond the buffer length).
 *
 * The substitution templates are stored in an efficient, packed form
 * that contains no pointers. This is to avoid cluttering up the
 * relocation table, but without any additional run-time overhead.
 */

/* Return offsets table offset for C, or -1 if not special.
 * The return value is suitable for namegen_offsets().
 */
static int
namegen_special(int c)
{
    if (c >= 0 && c < 128)
        return special[c];
    return -1;
}

/* Return offsets and number of offsets for special N.
 * Offsets point into namegen_argz.
 */
static int
namegen_offsets(int n, const short **offsets)
{
    *offsets = offsets_table + off_len[n * 2 + 0];
    return off_len[n * 2 + 1];
}

static unsigned long
namegen_rand32(unsigned long *s)
{
    unsigned long x = *s;
    x ^= x << 13;
    x ^= (x & 0xffffffffUL) >> 17;
    x ^= x << 5;
    return (*s = x) & 0xffffffffUL;
}

static int
namegen_cap(int c, int capitalize)
{
    return capitalize && c >= 'a' && c <= 'z' ? c & ~0x20 : c;
}

/* Copy a random substitution for template C into P, but only before E.
 */
static char *
namegen_copy(char *p, char *e, int c, unsigned long *seed, int capitalize)
{
    int n = namegen_special(c);
    if (n == -1) {
        if (p != e)
            *p++ = namegen_cap(c, capitalize);
    } else {
        const short *offsets;
        int count = namegen_offsets(n, &offsets);
        int select = namegen_rand32(seed) % count;
        const char *s = namegen_argz + offsets[select];
        while (*s) {
            int r = *s++;
            if (p != e)
                *p++ = namegen_cap(r, capitalize);
            capitalize = 0;
        }
    }
    return p;
}

int
namegen(char *dst, unsigned long len, const char *pattern, unsigned long *seed)
{
    int depth = 0;               /* Current nesting depth */
    char *p = dst;               /* Current output pointer */
    char *e = dst + len;         /* Maxiumum output pointer */
    int capitalize = 0;          /* Capitalize next item */

    /* Stacks */
    char *reset[NAMEGEN_MAX_DEPTH];     /* Reset pointer (undo generate) */
    unsigned long n[NAMEGEN_MAX_DEPTH]; /* Number of groups */
    unsigned long silent = 0;    /* Actively generating? */
    unsigned long literal = 0;   /* Current "mode" */
    unsigned long capstack = 0;  /* Initial capitalization state */

    n[0] = 1;
    reset[0] = dst;
    for (; *pattern; pattern++) {
        unsigned long bit; /* Bit for current depth */
        int c = *pattern;
        switch (c) {
            case '<':
                if (++depth == NAMEGEN_MAX_DEPTH) {
                    *dst = 0;
                    return NAMEGEN_TOO_DEEP;
                }
                bit = 1UL << depth;
                n[depth] = 1;
                reset[depth] = p;
                literal &= ~bit;
                silent &= ~bit;
                silent |= (silent << 1) & bit;
                capstack &= ~bit;
                capstack |= (unsigned long)capitalize << depth;
                break;

            case '(':
                if (++depth == NAMEGEN_MAX_DEPTH) {
                    *dst = 0;
                    return NAMEGEN_TOO_DEEP;
                }
                bit = 1UL << depth;
                n[depth] = 1;
                reset[depth] = p;
                literal |= bit;
                silent &= ~bit;
                silent |= (silent << 1) & bit;
                capstack &= ~bit;
                capstack |= (unsigned long)capitalize << depth;
                break;

            case '>':
                if (depth == 0) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                bit = 1UL << depth--;
                if (literal & bit) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                break;

            case ')':
                if (depth == 0) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                bit = 1UL << depth--;
                if (!(literal & bit)) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                break;

            case '|':
                bit = 1UL << depth;
                /* Stay silent if parent group is silent */
                if (!(silent & (bit >> 1))) {
                    if (namegen_rand32(seed) < 0xffffffffUL / ++n[depth]) {
                        /* Switch to this option */
                        p = reset[depth];
                        silent &= ~bit;
                        capitalize = !!(capstack & bit);
                    } else {
                        /* Skip this option */
                        silent |= bit;
                    }
                }
                break;

            case '!':
                capitalize = 1;
                break;

            default:
                bit = 1UL << depth;
                if (!(silent & bit)) {
                    if (literal & bit) {
                        /* Copy value literally */
                        if (p != e)
                            *p++ = namegen_cap(c, capitalize);
                    } else {
                        /* Copy a substitution */
                        p = namegen_copy(p, e, c, seed, capitalize);
                    }
                }
                capitalize = 0;
        }
    }

    if (depth) {
        *dst = 0;
        return NAMEGEN_INVALID;
    } else if (p == e) {
        p[-1] = 0;
        return NAMEGEN_TRUNCATED;
    } else {
        *p = 0;
        return NAMEGEN_SUCCESS;
    }
}
