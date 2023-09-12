--- upstream/avx2/sign.c
+++ upstream-patched/avx2/sign.c
@@ -161,7 +161,7 @@
     polyvecl y;
     polyveck w0;
   } tmpv;
-  keccak_state state;
+  shake256incctx state;
 
   rho = seedbuf;
   tr = rho + SEEDBYTES;
@@ -172,11 +172,12 @@
   unpack_sk(rho, tr, key, &t0, &s1, &s2, sk);
 
   /* Compute CRH(tr, msg) */
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
@@ -223,11 +224,12 @@
   polyveck_decompose(&w1, &tmpv.w0, &w1);
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
   poly_challenge(&c, sig);
   poly_ntt(&c);
 
@@ -329,18 +331,19 @@
   polyvecl *row = rowbuf;
   polyvecl z;
   poly c, w1, h;
-  keccak_state state;
+  shake256incctx state;
 
   if(siglen != CRYPTO_BYTES)
     return -1;
 
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
 
   /* Expand challenge */
   poly_challenge(&c, sig);
@@ -390,11 +393,12 @@
     if(hint[j]) return -1;
 
   /* Call random oracle and verify challenge */
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, buf.coeffs, K*POLYW1_PACKEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeeze(buf.coeffs, CTILDEBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, buf.coeffs, K*POLYW1_PACKEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(buf.coeffs, CTILDEBYTES, &state);
+  shake256_inc_ctx_release(&state);
   for(i = 0; i < CTILDEBYTES; ++i)
     if(buf.coeffs[i] != sig[i])
       return -1;

