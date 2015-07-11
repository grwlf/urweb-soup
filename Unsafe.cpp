#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" {
#include "Unsafe.h"
}

using namespace std;

uw_Basis_string uw_Unsafe_s2xhead (struct uw_context *ctx, uw_Basis_string s) {return s;}
uw_Basis_string uw_Unsafe_s2xbody (struct uw_context *ctx, uw_Basis_string s) {return s;}
