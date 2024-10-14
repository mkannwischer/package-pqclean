--- upstream/avx2/poly.c
+++ upstream-patched/avx2/poly.c
@@ -611,6 +611,7 @@
   stream256_state state;
   stream256_init(&state, seed, nonce);
   poly_uniform_gamma1_preinit(a, &state);
+  stream256_release(&state);
 }
 
 void poly_uniform_gamma1_4x(poly *a0,
@@ -670,12 +671,12 @@
   unsigned int i, b, pos;
   uint64_t signs;
   ALIGNED_UINT8(SHAKE256_RATE) buf;
-  keccak_state state;
+  shake256incctx state;
 
-  shake256_init(&state);
-  shake256_absorb(&state, seed, CTILDEBYTES);
-  shake256_finalize(&state);
-  shake256_squeezeblocks(buf.coeffs, 1, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, seed, CTILDEBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(buf.coeffs, sizeof buf, &state);
 
   memcpy(&signs, buf.coeffs, 8);
   pos = 8;
@@ -684,7 +685,7 @@
   for(i = N-TAU; i < N; ++i) {
     do {
       if(pos >= SHAKE256_RATE) {
-        shake256_squeezeblocks(buf.coeffs, 1, &state);
+        shake256_inc_squeeze(buf.coeffs, sizeof buf, &state);
         pos = 0;
       }
 
@@ -695,6 +696,7 @@
     c->coeffs[b] = 1 - 2*(signs & 1);
     signs >>= 1;
   }
+  shake256_inc_ctx_release(&state);
 }
 
 /*************************************************

