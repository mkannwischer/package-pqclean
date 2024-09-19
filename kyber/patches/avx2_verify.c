--- upstream/avx2/verify.c
+++ upstream-patched/avx2/verify.c
@@ -2,6 +2,7 @@
 #include <stdint.h>
 #include <immintrin.h>
 #include "verify.h"
+#include "compat.h"
 
 /*************************************************
 * Name:        verify
@@ -57,15 +58,7 @@
   size_t i;
   __m256i xvec, rvec, bvec;
 
-#if defined(__GNUC__) || defined(__clang__)
-  // Prevent the compiler from
-  //    1) inferring that b is 0/1-valued, and
-  //    2) handling the two cases with a branch.
-  // This is not necessary when verify.c and kem.c are separate translation
-  // units, but we expect that downstream consumers will copy this code and/or
-  // change how it is built.
-  __asm__("" : "+r"(b) : /* no inputs */);
-#endif
+  PQCLEAN_PREVENT_BRANCH_HACK(b);
 
   bvec = _mm256_set1_epi64x(-(uint64_t)b);
   for(i=0;i<len/32;i++) {

