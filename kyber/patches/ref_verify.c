--- upstream/ref/verify.c
+++ upstream-patched/ref/verify.c
@@ -1,6 +1,7 @@
 #include <stddef.h>
 #include <stdint.h>
 #include "verify.h"
+#include "compat.h"
 
 /*************************************************
 * Name:        verify
@@ -41,15 +42,7 @@
 {
   size_t i;
 
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
 
   b = -b;
   for(i=0;i<len;i++)

