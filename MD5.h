/*
 * Adopted from http://rosettacode.org/wiki/MD5#C
 */

#ifndef PUREMD5_H
#define PUREMD5_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

typedef unsigned md5_unsigned_t;
typedef short md5_short_t;


typedef md5_unsigned_t md5_digest[4];

static md5_unsigned_t md5_f0( md5_unsigned_t abcd[] ) { return ( abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);}
static md5_unsigned_t md5_f1( md5_unsigned_t abcd[] ) { return ( abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);}
static md5_unsigned_t md5_f2( md5_unsigned_t abcd[] ) { return  abcd[1] ^ abcd[2] ^ abcd[3];}
static md5_unsigned_t md5_f3( md5_unsigned_t abcd[] ) { return abcd[2] ^ (abcd[1] |~ abcd[3]);}

typedef md5_unsigned_t (*DgstFctn)(md5_unsigned_t a[]);

inline static md5_unsigned_t *md5_calcKs( md5_unsigned_t *k)
{
  double s, pwr;
  int i;

  pwr = pow( 2, 32);
  for (i=0; i<64; i++) {
    s = fabs(sin(1+i));
    k[i] = (md5_unsigned_t)( s * pwr );
  }
  return k;
}

inline static md5_unsigned_t md5_rol( md5_unsigned_t v, md5_short_t amt )
{
  md5_unsigned_t  msk1 = (1<<amt) -1;
  return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}

struct md5_sg {
  const char *buf;
  size_t len;
};

inline static void md5(const struct md5_sg *sg, md5_digest h)
{
  md5_digest h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
  DgstFctn ff[] = { &md5_f0, &md5_f1, &md5_f2, &md5_f3 };
  md5_short_t M[] = { 1, 5, 3, 7 };
  md5_short_t O[] = { 0, 1, 5, 0 };
  md5_short_t rot0[] = { 7,12,17,22};
  md5_short_t rot1[] = { 5, 9,14,20};
  md5_short_t rot2[] = { 4,11,16,23};
  md5_short_t rot3[] = { 6,10,15,21};
  md5_short_t *rots[] = {rot0, rot1, rot2, rot3 };
  md5_unsigned_t kspace[64];
  md5_unsigned_t *k = 0;

  memset(h,0,sizeof(md5_unsigned_t) * 4);

  md5_digest abcd;
  memset(abcd,0,sizeof(md5_unsigned_t) * 4);
  DgstFctn fctn;
  md5_short_t m, o, g;
  md5_unsigned_t f;
  md5_short_t *rotn;
  union {
    md5_unsigned_t w[16];
    char     b[64];
  }mm;
  int os = 0;
  int grp, grps, q, p;
  uint8_t *msg2;

  if (k==NULL) k= md5_calcKs(kspace);

  for (q=0; q<4; q++) h[q] = h0[q];   // initialize


  {
    uint8_t *msg3;
    const struct md5_sg *sg2;
    int mlen;
   
    sg2 = sg;
    mlen = 0;
    while(sg2->buf != NULL) {
      mlen += sg2->len;
      sg2++;
    }

    grps  = 1 + (mlen+8)/64;
    msg2 = (uint8_t*)malloc( 64*grps);

    sg2 = sg;
    msg3 = msg2;
    while(sg2->buf != NULL) {
      memcpy(msg3, sg2->buf, sg2->len);
      msg3 += sg2->len;
      sg2++;
    }

    msg2[mlen] = (uint8_t)0x80;  
    q = mlen + 1;
    while (q < 64*grps) { msg2[q] = 0; q++ ; }
    {
      typedef union uwb {
        md5_unsigned_t w;
        uint8_t b[4];
      } WBunion;

      WBunion u;
      u.w = 8*mlen;
      q -= 8;
      memcpy(msg2+q, &u.w, 4 );
    }
  }

  for (grp=0; grp<grps; grp++)
  {
    memcpy( mm.b, msg2+os, 64);
    for(q=0;q<4;q++) abcd[q] = h[q];
    for (p = 0; p<4; p++) {
      fctn = ff[p];
      rotn = rots[p];
      m = M[p]; o= O[p];
      for (q=0; q<16; q++) {
        g = (m*q + o) % 16;
        f = abcd[1] + md5_rol( abcd[0]+ fctn(abcd) + k[q+16*p] + mm.w[g], rotn[q%4]);

        abcd[0] = abcd[3];
        abcd[3] = abcd[2];
        abcd[2] = abcd[1];
        abcd[1] = f;
      }
    }
    for (p=0; p<4; p++)
      h[p] += abcd[p];
    os += 64;
  }
}

static inline void md5_fprint(FILE* f, md5_unsigned_t* d)
{
  int j,k;
  union uwb {
    md5_unsigned_t w;
    uint8_t b[4];
  } u;

  for (j=0;j<4; j++) {
    u.w = d[j];
    for (k=0;k<4;k++) fprintf(f, "%02x",u.b[k]);
  }
}

static inline void md5_print_s(char* s, size_t sz, md5_unsigned_t* d)
{
  int j,k;
  union uwb {
    md5_unsigned_t w;
    uint8_t b[4];
  } u;

  for (j=0;j<4; j++) {
    u.w = d[j];
    for (k=0;k<4 && sz>0;k++) {
      snprintf(s, sz, "%02x", u.b[k]);
      s+=2;
      sz-=2;
    }
  }
}

/* Print md5 sum byte by byte, most significant bytes go first */
static inline void md5_fprint_words(FILE* f, md5_unsigned_t* d)
{
  int j;

  for (j=0;j<4; j++) {
    fprintf(f, "%u",d[j]);
    if(j<3) putc(' ', f);
  }
}

/* Return 1 if md5 digests are equal */
static inline int md5_eq(md5_digest d1, md5_digest d2)
{
  return (0 == memcmp(d1,d2,4*sizeof(md5_unsigned_t)) ? 1 : 0);
}

#endif
