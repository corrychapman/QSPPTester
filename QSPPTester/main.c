
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


int comp(const void *s1, const void *s2);

int comp(const void *s1, const void *s2){
    return (strcmp(*(char **)s1, *(char **)s2));
}




typedef int cmp_t(const void *, const void *);

static inline char *med3(char *, char *, char *, cmp_t *, void *);
static inline void swapfunc(char *, char *, size_t, int, int);

static inline void
swapfunc(char *a, char *b, size_t n, int swaptype_long, int swaptype_int)
{
    if (swaptype_long <= 1)
    { size_t i = (n) / sizeof (long); long *pi = (long *) (a); long *pj = (long *) (b); do { long t = *pi; *pi++ = *pj; *pj++ = t; } while (--i > 0); }
    else if (swaptype_int <= 1)
    { size_t i = (n) / sizeof (int); int *pi = (int *) (a); int *pj = (int *) (b); do { int t = *pi; *pi++ = *pj; *pj++ = t; } while (--i > 0); }
    else
    { size_t i = (n) / sizeof (char); char *pi = (char *) (a); char *pj = (char *) (b); do { char t = *pi; *pi++ = *pj; *pj++ = t; } while (--i > 0); }
}

static inline char *
med3(char *a, char *b, char *c, cmp_t *cmp, void *thunk
     
     __attribute__((unused))
     
     )
{
    return (cmp((a), (b))) < 0 ?
    ((cmp((b), (c))) < 0 ? b : ((cmp((a), (c))) < 0 ? c : a ))
    :((cmp((b), (c))) > 0 ? b : ((cmp((a), (c))) < 0 ? a : c ));
}




void
qsort2(void *a, size_t n, size_t es, cmp_t *cmp)

{
    char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
    size_t d1, d2;
    int cmp_result;
    int swaptype_long, swaptype_int, swap_cnt;
    
loop: swaptype_long = ((char *)a - (char *)0) % sizeof(long) || es % sizeof(long) ? 2 : es == sizeof(long) ? 0 : 1;;
    swaptype_int = ((char *)a - (char *)0) % sizeof(int) || es % sizeof(int) ? 2 : es == sizeof(int) ? 0 : 1;;
    swap_cnt = 0;
    if (n < 7) {
        for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
            for (pl = pm;
                 pl > (char *)a && (cmp((pl - es), (pl))) > 0;
                 pl -= es)
                if (swaptype_long == 0) { long t = *(long *)(pl); *(long *)(pl) = *(long *)(pl - es); *(long *)(pl - es) = t; } else if (swaptype_int == 0) { int t = *(int *)(pl); *(int *)(pl) = *(int *)(pl - es); *(int *)(pl - es) = t; } else swapfunc(pl, pl - es, es, swaptype_long, swaptype_int);
        return;
    }
    pm = (char *)a + (n / 2) * es;
    if (n > 7) {
        pl = a;
        pn = (char *)a + (n - 1) * es;
        if (n > 40) {
            size_t d = (n / 8) * es;
            
            pl = med3(pl, pl + d, pl + 2 * d, cmp, ((void*)0));
            pm = med3(pm - d, pm, pm + d, cmp, ((void*)0));
            pn = med3(pn - 2 * d, pn - d, pn, cmp, ((void*)0));
        }
        pm = med3(pl, pm, pn, cmp, ((void*)0));
    }
    if (swaptype_long == 0) { long t = *(long *)(a); *(long *)(a) = *(long *)(pm); *(long *)(pm) = t; } else if (swaptype_int == 0) { int t = *(int *)(a); *(int *)(a) = *(int *)(pm); *(int *)(pm) = t; } else swapfunc(a, pm, es, swaptype_long, swaptype_int);
    pa = pb = (char *)a + es;
    
    pc = pd = (char *)a + (n - 1) * es;
    for (;;) {
        while (pb <= pc && (cmp_result = (cmp((pb), (a)))) <= 0) {
            if (cmp_result == 0) {
                swap_cnt = 1;
                if (swaptype_long == 0) { long t = *(long *)(pa); *(long *)(pa) = *(long *)(pb); *(long *)(pb) = t; } else if (swaptype_int == 0) { int t = *(int *)(pa); *(int *)(pa) = *(int *)(pb); *(int *)(pb) = t; } else swapfunc(pa, pb, es, swaptype_long, swaptype_int);
                pa += es;
            }
            pb += es;
        }
        while (pb <= pc && (cmp_result = (cmp((pc), (a)))) >= 0) {
            if (cmp_result == 0) {
                swap_cnt = 1;
                if (swaptype_long == 0) { long t = *(long *)(pc); *(long *)(pc) = *(long *)(pd); *(long *)(pd) = t; } else if (swaptype_int == 0) { int t = *(int *)(pc); *(int *)(pc) = *(int *)(pd); *(int *)(pd) = t; } else swapfunc(pc, pd, es, swaptype_long, swaptype_int);
                pd -= es;
            }
            pc -= es;
        }
        if (pb > pc)
            break;
        if (swaptype_long == 0) { long t = *(long *)(pb); *(long *)(pb) = *(long *)(pc); *(long *)(pc) = t; } else if (swaptype_int == 0) { int t = *(int *)(pb); *(int *)(pb) = *(int *)(pc); *(int *)(pc) = t; } else swapfunc(pb, pc, es, swaptype_long, swaptype_int);
        swap_cnt = 1;
        pb += es;
        pc -= es;
    }
    if (swap_cnt == 0) {
        for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
            for (pl = pm;
                 pl > (char *)a && (cmp((pl - es), (pl))) > 0;
                 pl -= es)
                if (swaptype_long == 0) { long t = *(long *)(pl); *(long *)(pl) = *(long *)(pl - es); *(long *)(pl - es) = t; } else if (swaptype_int == 0) { int t = *(int *)(pl); *(int *)(pl) = *(int *)(pl - es); *(int *)(pl - es) = t; } else swapfunc(pl, pl - es, es, swaptype_long, swaptype_int);
        return;
    }
    
    pn = (char *)a + n * es;
    d1 = ((pa - (char *)a) < (pb - pa) ? pa - (char *)a : pb - pa);
    if ((d1) > 0) swapfunc(a, pb - d1, d1, swaptype_long, swaptype_int);
    d1 = ((pd - pc) < (pn - pd - es) ? pd - pc : pn - pd - es);
    if ((d1) > 0) swapfunc(pb, pn - d1, d1, swaptype_long, swaptype_int);
    
    d1 = pb - pa;
    d2 = pd - pc;
    if (d1 <= d2) {
        
        if (d1 > es) {
            
            
            
            qsort2(a, d1 / es, es, cmp);
            
        }
        if (d2 > es) {
            
            
            a = pn - d2;
            n = d2 / es;
            goto loop;
        }
    } else {
        
        if (d2 > es) {
            
            
            
            qsort2(pn - d2, d2 / es, es, cmp);
            
        }
        if (d1 > es) {
            
            
            n = d1 / es;
            goto loop;
        }
    }
}


int main(){
    
    char *data[] = {"rat", "dog", "apple", "monkey", "gerbil"};
    
    qsort2(data, 5, sizeof(char *), comp);
    
    for (int i = 0; i < 5; i++)
        printf("\n%d: %s", i+1, data[i]);
    
    printf("\n");
    
    return 0;
    
}
