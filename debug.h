#ifndef __DEBUG_H
#define __DEBUG_H

#ifndef NDEBUG
#define __DP printf
#define __DEXE
#else
#define __DP 1 ? (void) 0 : printf
#define __DEXE 1 ? (void) 0 :
#endif

#endif
