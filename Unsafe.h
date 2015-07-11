#ifndef UNSAFE_H
#define UNSAFE_H

#include <types_cpp.h>
#include <urweb_cpp.h>

#ifdef __cplusplus
extern "C" {
#endif

uw_Basis_string uw_Unsafe_s2xhead (struct uw_context *ctx, uw_Basis_string s);
uw_Basis_string uw_Unsafe_s2xbody (struct uw_context *ctx, uw_Basis_string s);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
