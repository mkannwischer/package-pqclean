--- upstream/ref/sign.c
+++ upstream-patched/ref/sign.c
@@ -81,7 +81,7 @@
 *
 * Returns 0 (success) or -1 (context string too long)
 **************************************************/
-int crypto_sign_signature(uint8_t *sig,
+int crypto_sign_signature_ctx(uint8_t *sig,
                           size_t *siglen,
                           const uint8_t *m,
                           size_t mlen,
@@ -96,7 +96,7 @@
   polyvecl mat[K], s1, y, z;
   polyveck t0, s2, w1, w0, h;
   poly cp;
-  keccak_state state;
+  shake256incctx state;
 
   if(ctxlen > 255)
     return -1;
@@ -111,14 +111,15 @@
 
   /* Compute mu = CRH(tr, 0, ctxlen, ctx, msg) */
   mu[0] = 0;
-  mu[1] = ctxlen;
-  shake256_init(&state);
-  shake256_absorb(&state, tr, TRBYTES);
-  shake256_absorb(&state, mu, 2);
-  shake256_absorb(&state, ctx, ctxlen);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  mu[1] = (uint8_t)ctxlen;
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, tr, TRBYTES);
+  shake256_inc_absorb(&state, mu, 2);
+  shake256_inc_absorb(&state, ctx, ctxlen);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
 #ifdef DILITHIUM_RANDOMIZED_SIGNING
   randombytes(rnd, RNDBYTES);
@@ -150,11 +151,12 @@
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
   poly_challenge(&cp, sig);
   poly_ntt(&cp);
 
@@ -211,7 +213,7 @@
 *
 * Returns 0 (success) or -1 (context string too long)
 **************************************************/
-int crypto_sign(uint8_t *sm,
+int crypto_sign_ctx(uint8_t *sm,
                 size_t *smlen,
                 const uint8_t *m,
                 size_t mlen,
@@ -224,7 +226,7 @@
 
   for(i = 0; i < mlen; ++i)
     sm[CRYPTO_BYTES + mlen - 1 - i] = m[mlen - 1 - i];
-  ret = crypto_sign_signature(sm, smlen, sm + CRYPTO_BYTES, mlen, ctx, ctxlen, sk);
+  ret = crypto_sign_signature_ctx(sm, smlen, sm + CRYPTO_BYTES, mlen, ctx, ctxlen, sk);
   *smlen += mlen;
   return ret;
 }
@@ -244,7 +246,7 @@
 *
 * Returns 0 if signature could be verified correctly and -1 otherwise
 **************************************************/
-int crypto_sign_verify(const uint8_t *sig,
+int crypto_sign_verify_ctx(const uint8_t *sig,
                        size_t siglen,
                        const uint8_t *m,
                        size_t mlen,
@@ -261,7 +263,7 @@
   poly cp;
   polyvecl mat[K], z;
   polyveck t1, w1, h;
-  keccak_state state;
+  shake256incctx state;
 
   if(ctxlen > 255 || siglen != CRYPTO_BYTES)
     return -1;
@@ -274,15 +276,16 @@
 
   /* Compute CRH(H(rho, t1), msg) */
   shake256(mu, TRBYTES, pk, CRYPTO_PUBLICKEYBYTES);
-  shake256_init(&state);
-  shake256_absorb(&state, mu, TRBYTES);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, TRBYTES);
   mu[0] = 0;
-  mu[1] = ctxlen;
-  shake256_absorb(&state, mu, 2);
-  shake256_absorb(&state, ctx, ctxlen);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  mu[1] = (uint8_t)ctxlen;
+  shake256_inc_absorb(&state, mu, 2);
+  shake256_inc_absorb(&state, ctx, ctxlen);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
   /* Matrix-vector multiplication; compute Az - c2^dt1 */
   poly_challenge(&cp, c);
@@ -306,14 +309,16 @@
   polyveck_pack_w1(buf, &w1);
 
   /* Call random oracle and verify challenge */
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeeze(c2, CTILDEBYTES, &state);
-  for(i = 0; i < CTILDEBYTES; ++i)
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(c2, CTILDEBYTES, &state);
+  shake256_inc_ctx_release(&state);
+  for(i = 0; i < CTILDEBYTES; ++i) {
     if(c[i] != c2[i])
       return -1;
+  }
 
   return 0;
 }
@@ -334,7 +339,7 @@
 *
 * Returns 0 if signed message could be verified correctly and -1 otherwise
 **************************************************/
-int crypto_sign_open(uint8_t *m,
+int crypto_sign_open_ctx(uint8_t *m,
                      size_t *mlen,
                      const uint8_t *sm,
                      size_t smlen,
@@ -348,7 +353,7 @@
     goto badsig;
 
   *mlen = smlen - CRYPTO_BYTES;
-  if(crypto_sign_verify(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, ctx, ctxlen, pk))
+  if(crypto_sign_verify_ctx(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, ctx, ctxlen, pk))
     goto badsig;
   else {
     /* All good, copy msg, return 0 */

