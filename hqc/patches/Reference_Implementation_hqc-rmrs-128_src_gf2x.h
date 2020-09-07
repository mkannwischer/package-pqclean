--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-128/src/gf2x.h
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-128/src/gf2x.h
@@ -9,6 +9,6 @@
 #include "rng.h"
 #include <stdint.h>
 
-void vect_mul(uint64_t *o, const uint32_t *v1, const uint64_t *v2, const uint16_t weight, AES_XOF_struct *ctx);
+void vect_mul(uint64_t *o, const uint32_t *a1, const uint64_t *a2, uint16_t weight, AES_XOF_struct *ctx);
 
 #endif

