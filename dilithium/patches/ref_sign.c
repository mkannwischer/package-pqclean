--- upstream/ref/sign.c
+++ upstream-patched/ref/sign.c
@@ -90,7 +90,7 @@
   polyvecl mat[K], s1, y, z;
   polyveck t0, s2, w1, w0, h;
   poly cp;
-  keccak_state state;
+  shake256incctx state;
 
   rho = seedbuf;
   tr = rho + SEEDBYTES;
@@ -102,11 +102,12 @@
 
 
   /* Compute mu = CRH(tr, msg) */
-  shake256_init(&state);
-  shake256_absorb(&state, tr, TRBYTES);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, tr, TRBYTES);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
 #ifdef DILITHIUM_RANDOMIZED_SIGNING
   randombytes(rnd, RNDBYTES);
@@ -138,11 +139,12 @@
   polyveck_decompose(&w1, &w0, &w1);
   polyveck_pack_w1(sig, &w1);
 
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, sig, K*POLYW1_PACKEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeeze(sig, CTILDEBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, sig, K*POLYW1_PACKEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(sig, CTILDEBYTES, &state);
+  shake256_inc_ctx_release(&state);
   poly_challenge(&cp, sig); /* uses only the first SEEDBYTES bytes of sig */
   poly_ntt(&cp);
 
@@ -240,7 +242,7 @@
   poly cp;
   polyvecl mat[K], z;
   polyveck t1, w1, h;
-  keccak_state state;
+  shake256incctx state;
 
   if(siglen != CRYPTO_BYTES)
     return -1;
@@ -253,11 +255,12 @@
 
   /* Compute CRH(H(rho, t1), msg) */
   shake256(mu, CRHBYTES, pk, CRYPTO_PUBLICKEYBYTES);
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
   /* Matrix-vector multiplication; compute Az - c2^dt1 */
   poly_challenge(&cp, c); /* uses only the first SEEDBYTES bytes of c */
@@ -281,11 +284,12 @@
   polyveck_pack_w1(buf, &w1);
 
   /* Call random oracle and verify challenge */
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeeze(c2, CTILDEBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(c2, CTILDEBYTES, &state);
+  shake256_inc_ctx_release(&state);
   for(i = 0; i < CTILDEBYTES; ++i)
     if(c[i] != c2[i])
       return -1;

