#ifndef CL_COMMON_H
#define CL_COMMON_H

#include "cl_config.h"

/* Prepend extern "C" if we're in a C++
   compiler. */
#ifdef __cplusplus
#define CL_EXTERN_C extern "C"
#else
#define CL_EXTERN_C
#endif

/* Default to setting CL_EXPORTED to the result
   of our extern "C" check. */
#ifndef CL_EXPORTED
#define CL_EXPORTED CL_EXTERN_C
#endif

#endif