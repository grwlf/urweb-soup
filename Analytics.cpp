#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" {
#include "Analytics.h"
}

using namespace std;

uw_Basis_string uw_Analytics_insert (struct uw_context *ctx, uw_Basis_string uid)
{
  const char *pattern = "<script>"
    "(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){"
    "(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),"
    "m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)"
    "})(window,document,'script','//www.google-analytics.com/analytics.js','ga');"
    "ga('create', '%s', 'auto');"
    "ga('send', 'pageview');"
    "</script>";

  int len = strlen(uid) + strlen(pattern);
  char *script = (char*)uw_malloc(ctx, len);
  snprintf(script, len, pattern, uid);
  return script;
}

