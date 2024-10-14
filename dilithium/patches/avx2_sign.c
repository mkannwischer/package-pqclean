--- upstream/avx2/sign.c
+++ upstream-patched/avx2/sign.c
@@ -151,7 +151,7 @@
 *
 * Returns 0 (success) or -1 (context string too long)
 **************************************************/
-int crypto_sign_signature(uint8_t *sig, size_t *siglen, const uint8_t *m, size_t mlen,
+int crypto_sign_signature_ctx(uint8_t *sig, size_t *siglen, const uint8_t *m, size_t mlen,
                           const uint8_t *ctx, size_t ctxlen, const uint8_t *sk)
 {
   unsigned int i, n, pos;
@@ -167,7 +167,7 @@
     polyvecl y;
     polyveck w0;
   } tmpv;
-  keccak_state state;
+  shake256incctx state;
 
   if(ctxlen > 255)
     return -1;
@@ -181,15 +181,16 @@
   unpack_sk(rho, tr, key, &t0, &s1, &s2, sk);
 
   /* Compute CRH(tr, 0, ctxlen, ctx, msg) */
-  shake256_init(&state);
-  shake256_absorb(&state, tr, TRBYTES);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, tr, TRBYTES);
   mu[0] = 0;
   mu[1] = ctxlen;
-  shake256_absorb(&state, mu, 2);
-  shake256_absorb(&state, ctx, ctxlen);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_absorb(&state, mu, 2);
+  shake256_inc_absorb(&state, ctx, ctxlen);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
 #ifdef DILITHIUM_RANDOMIZED_SIGNING
   randombytes(rnd, RNDBYTES);
@@ -236,11 +237,12 @@
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
 
@@ -311,7 +313,7 @@
 *
 * Returns 0 (success)
 **************************************************/
-int crypto_sign(uint8_t *sm, size_t *smlen, const uint8_t *m, size_t mlen, const uint8_t *ctx, size_t ctxlen,
+int crypto_sign_ctx(uint8_t *sm, size_t *smlen, const uint8_t *m, size_t mlen, const uint8_t *ctx, size_t ctxlen,
                 const uint8_t *sk)
 {
   size_t i;
@@ -319,7 +321,7 @@
 
   for(i = 0; i < mlen; ++i)
     sm[CRYPTO_BYTES + mlen - 1 - i] = m[mlen - 1 - i];
-  ret = crypto_sign_signature(sm, smlen, sm + CRYPTO_BYTES, mlen, ctx, ctxlen, sk);
+  ret = crypto_sign_signature_ctx(sm, smlen, sm + CRYPTO_BYTES, mlen, ctx, ctxlen, sk);
   *smlen += mlen;
   return ret;
 }
@@ -339,7 +341,7 @@
 *
 * Returns 0 if signature could be verified correctly and -1 otherwise
 **************************************************/
-int crypto_sign_verify(const uint8_t *sig, size_t siglen, const uint8_t *m, size_t mlen, 
+int crypto_sign_verify_ctx(const uint8_t *sig, size_t siglen, const uint8_t *m, size_t mlen, 
                        const uint8_t *ctx, size_t ctxlen, const uint8_t *pk) {
   unsigned int i, j, pos = 0;
   /* polyw1_pack writes additional 14 bytes */
@@ -350,22 +352,23 @@
   polyvecl *row = rowbuf;
   polyvecl z;
   poly c, w1, h;
-  keccak_state state;
+  shake256incctx state;
 
   if(ctxlen > 255 || siglen != CRYPTO_BYTES)
     return -1;
 
   /* Compute CRH(H(rho, t1), msg) */
   shake256(mu, TRBYTES, pk, CRYPTO_PUBLICKEYBYTES);
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
   mu[0] = 0;
   mu[1] = ctxlen;
-  shake256_absorb(&state, mu, 2);
-  shake256_absorb(&state, ctx, ctxlen);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_absorb(&state, mu, 2);
+  shake256_inc_absorb(&state, ctx, ctxlen);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
   /* Expand challenge */
   poly_challenge(&c, sig);
@@ -411,19 +414,21 @@
   }
 
   /* Extra indices are zero for strong unforgeability */
-  for(j = pos; j < OMEGA; ++j)
+  for(j = pos; j < OMEGA; ++j) {
     if(hint[j]) return -1;
+  }
 
   /* Call random oracle and verify challenge */
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, buf.coeffs, K*POLYW1_PACKEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeeze(buf.coeffs, CTILDEBYTES, &state);
-  for(i = 0; i < CTILDEBYTES; ++i)
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, buf.coeffs, K*POLYW1_PACKEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(buf.coeffs, CTILDEBYTES, &state);
+  shake256_inc_ctx_release(&state);
+  for(i = 0; i < CTILDEBYTES; ++i) {
     if(buf.coeffs[i] != sig[i])
       return -1;
-
+  }
   return 0;
 }
 
@@ -443,7 +448,7 @@
 *
 * Returns 0 if signed message could be verified correctly and -1 otherwise
 **************************************************/
-int crypto_sign_open(uint8_t *m, size_t *mlen, const uint8_t *sm, size_t smlen,
+int crypto_sign_open_ctx(uint8_t *m, size_t *mlen, const uint8_t *sm, size_t smlen,
                      const uint8_t *ctx, size_t ctxlen, const uint8_t *pk) {
   size_t i;
 
@@ -451,7 +456,7 @@
     goto badsig;
 
   *mlen = smlen - CRYPTO_BYTES;
-  if(crypto_sign_verify(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, ctx, ctxlen, pk))
+  if(crypto_sign_verify_ctx(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, ctx, ctxlen, pk))
     goto badsig;
   else {
     /* All good, copy msg, return 0 */

