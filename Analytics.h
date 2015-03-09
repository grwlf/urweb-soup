#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <types_cpp.h>
#include <urweb_cpp.h>

#ifdef __cplusplus
extern "C" {
#endif

uw_Basis_string uw_Analytics_insert (struct uw_context *ctx, uw_Basis_string uid);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
