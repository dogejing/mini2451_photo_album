#include "types.h"

#ifndef _PRINTF_H
#define _PRINTF_H

#ifndef va_arg
/*
 * Storage alignment properties
 */
#define	 NATIVE_INT		 int
#define  _AUPBND         (sizeof (NATIVE_INT) - 1)
#define  _ADNBND         (sizeof (NATIVE_INT) - 1)

/*
 * Variable argument list macro definitions
 */

#define _bnd(X, bnd)    (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_end(ap)      (void) 0
#define va_start(ap, A) (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))
#define va_arg(ap, T)   (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))



#endif /* va_arg */

extern int my_printf(const char *fmt, ...);
extern int my_scanf(const char * fmt, ...);
extern int vsprintf(char *buf, const char *fmt, va_list args);
extern int my_vsscanf(const char * buf, const char * fmt, va_list args);

#endif /* _PRINTF_H */




