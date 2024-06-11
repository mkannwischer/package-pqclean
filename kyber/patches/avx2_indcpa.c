--- upstream/avx2/indcpa.c
+++ upstream-patched/avx2/indcpa.c
@@ -20,7 +20,7 @@
 *              serialized vector of polynomials pk and the
 *              public seed used to generate the matrix A.
 *              The polynomial coefficients in pk are assumed to
-*              lie in the invertal [0,q], i.e. pk must be reduced
+*              lie in the interval [0,q], i.e. pk must be reduced
 *              by polyvec_reduce().
 *
 * Arguments:   uint8_t *r: pointer to the output serialized public key
@@ -58,7 +58,7 @@
 *
 * Description: Serialize the secret key.
 *              The polynomial coefficients in sk are assumed to
-*              lie in the invertal [0,q], i.e. sk must be reduced
+*              lie in the interval [0,q], i.e. sk must be reduced
 *              by polyvec_reduce().
 *
 * Arguments:   - uint8_t *r: pointer to output serialized secret key
@@ -89,7 +89,7 @@
 *              compressed and serialized vector of polynomials b
 *              and the compressed and serialized polynomial v.
 *              The polynomial coefficients in b and v are assumed to
-*              lie in the invertal [0,q], i.e. b and v must be reduced
+*              lie in the interval [0,q], i.e. b and v must be reduced
 *              by polyvec_reduce() and poly_reduce(), respectively.
 *
 * Arguments:   uint8_t *r: pointer to the output serialized ciphertext
@@ -233,7 +233,7 @@
   ALIGNED_UINT8(REJ_UNIFORM_AVX_NBLOCKS*SHAKE128_RATE) buf[4];
   __m256i f;
   keccakx4_state state;
-  keccak_state state1x;
+  xof_state state1x;
 
   f = _mm256_loadu_si256((__m256i *)seed);
   _mm256_store_si256(buf[0].vec, f);
@@ -337,14 +337,14 @@
   _mm256_store_si256(buf[0].vec, f);
   buf[0].coeffs[32] = 2;
   buf[0].coeffs[33] = 2;
-  shake128_absorb_once(&state1x, buf[0].coeffs, 34);
+  shake128_absorb(&state1x, buf[0].coeffs, 34);
   shake128_squeezeblocks(buf[0].coeffs, REJ_UNIFORM_AVX_NBLOCKS, &state1x);
   ctr0 = rej_uniform_avx(a[2].vec[2].coeffs, buf[0].coeffs);
   while(ctr0 < KYBER_N) {
     shake128_squeezeblocks(buf[0].coeffs, 1, &state1x);
     ctr0 += rej_uniform(a[2].vec[2].coeffs + ctr0, KYBER_N - ctr0, buf[0].coeffs, SHAKE128_RATE);
   }
-
+  xof_ctx_release(&state1x);
   poly_nttunpack(&a[2].vec[2]);
 }
 #elif KYBER_K == 4

