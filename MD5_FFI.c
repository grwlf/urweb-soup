#include <types_cpp.h>
#include <urweb_cpp.h>

#include <MD5.h>

uw_Basis_string uw_MD5_FFI_md5(struct uw_context *ctx, uw_Basis_string s)
{
  md5_digest d;
  struct md5_sg sg = {.buf = s, .len = uw_Basis_strlen(ctx, s) };
  md5(&sg,d);

  size_t ds_sz = 4*sizeof(uint32_t)*2 + 1;
  char *ds = (char*) uw_malloc(ctx, ds_sz);
  md5_print_s(ds, ds_sz, d);
  return ds;
}
