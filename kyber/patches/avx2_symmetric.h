--- upstream/avx2/symmetric.h
+++ upstream-patched/avx2/symmetric.h
@@ -8,10 +8,10 @@
 #include "fips202.h"
 #include "fips202x4.h"
 
-typedef keccak_state xof_state;
+typedef shake128ctx xof_state;
 
 #define kyber_shake128_absorb KYBER_NAMESPACE(kyber_shake128_absorb)
-void kyber_shake128_absorb(keccak_state *s,
+void kyber_shake128_absorb(xof_state *s,
                            const uint8_t seed[KYBER_SYMBYTES],
                            uint8_t x,
                            uint8_t y);
@@ -28,6 +28,7 @@
 #define hash_g(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)
 #define xof_absorb(STATE, SEED, X, Y) kyber_shake128_absorb(STATE, SEED, X, Y)
 #define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) shake128_squeezeblocks(OUT, OUTBLOCKS, STATE)
+#define xof_ctx_release(STATE) shake128_ctx_release(STATE)
 #define prf(OUT, OUTBYTES, KEY, NONCE) kyber_shake256_prf(OUT, OUTBYTES, KEY, NONCE)
 #define rkprf(OUT, KEY, INPUT) kyber_shake256_rkprf(OUT, KEY, INPUT)
 

