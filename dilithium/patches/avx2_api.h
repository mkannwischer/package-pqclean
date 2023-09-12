--- upstream/avx2/api.h
+++ upstream-patched/avx2/api.h
@@ -4,85 +4,40 @@
 #include <stddef.h>
 #include <stdint.h>
 
-#define pqcrystals_dilithium2_PUBLICKEYBYTES 1312
-#define pqcrystals_dilithium2_SECRETKEYBYTES 2528
-#define pqcrystals_dilithium2_BYTES 2420
-
-#define pqcrystals_dilithium2_avx2_PUBLICKEYBYTES pqcrystals_dilithium2_PUBLICKEYBYTES
-#define pqcrystals_dilithium2_avx2_SECRETKEYBYTES pqcrystals_dilithium2_SECRETKEYBYTES
-#define pqcrystals_dilithium2_avx2_BYTES pqcrystals_dilithium2_BYTES
-
-int pqcrystals_dilithium2_avx2_keypair(uint8_t *pk, uint8_t *sk);
-
-int pqcrystals_dilithium2_avx2_signature(uint8_t *sig, size_t *siglen,
-                                        const uint8_t *m, size_t mlen,
-                                        const uint8_t *sk);
-
-int pqcrystals_dilithium2_avx2(uint8_t *sm, size_t *smlen,
-                              const uint8_t *m, size_t mlen,
-                              const uint8_t *sk);
-
-int pqcrystals_dilithium2_avx2_verify(const uint8_t *sig, size_t siglen,
-                                     const uint8_t *m, size_t mlen,
-                                     const uint8_t *pk);
-
-int pqcrystals_dilithium2_avx2_open(uint8_t *m, size_t *mlen,
-                                   const uint8_t *sm, size_t smlen,
-                                   const uint8_t *pk);
-
-
-#define pqcrystals_dilithium3_PUBLICKEYBYTES 1952
-#define pqcrystals_dilithium3_SECRETKEYBYTES 4000
-#define pqcrystals_dilithium3_BYTES 3293
-
-#define pqcrystals_dilithium3_avx2_PUBLICKEYBYTES pqcrystals_dilithium3_PUBLICKEYBYTES
-#define pqcrystals_dilithium3_avx2_SECRETKEYBYTES pqcrystals_dilithium3_SECRETKEYBYTES
-#define pqcrystals_dilithium3_avx2_BYTES pqcrystals_dilithium3_BYTES
-
-int pqcrystals_dilithium3_avx2_keypair(uint8_t *pk, uint8_t *sk);
-
-int pqcrystals_dilithium3_avx2_signature(uint8_t *sig, size_t *siglen,
-                                        const uint8_t *m, size_t mlen,
-                                        const uint8_t *sk);
-
-int pqcrystals_dilithium3_avx2(uint8_t *sm, size_t *smlen,
-                              const uint8_t *m, size_t mlen,
-                              const uint8_t *sk);
-
-int pqcrystals_dilithium3_avx2_verify(const uint8_t *sig, size_t siglen,
-                                     const uint8_t *m, size_t mlen,
-                                     const uint8_t *pk);
-
-int pqcrystals_dilithium3_avx2_open(uint8_t *m, size_t *mlen,
-                                   const uint8_t *sm, size_t smlen,
-                                   const uint8_t *pk);
-
-
-#define pqcrystals_dilithium5_PUBLICKEYBYTES 2592
-#define pqcrystals_dilithium5_SECRETKEYBYTES 4864
-#define pqcrystals_dilithium5_BYTES 4595
+#if DILITHIUM_MODE == 2
+#define CRYPTO_PUBLICKEYBYTES 1312
+#define CRYPTO_SECRETKEYBYTES 2560
+#define CRYPTO_BYTES 2420
+#define CRYPTO_ALGNAME "Dilithium2"
+#elif DILITHIUM_MODE == 3
+#define CRYPTO_PUBLICKEYBYTES 1952
+#define CRYPTO_SECRETKEYBYTES 4032
+#define CRYPTO_BYTES 3309
+#define CRYPTO_ALGNAME "Dilithium3"
+#elif DILITHIUM_MODE == 5
+#define CRYPTO_PUBLICKEYBYTES 2592
+#define CRYPTO_SECRETKEYBYTES 4896
+#define CRYPTO_BYTES 4627
+#define CRYPTO_ALGNAME "Dilithium5"
+#endif
 
-#define pqcrystals_dilithium5_avx2_PUBLICKEYBYTES pqcrystals_dilithium5_PUBLICKEYBYTES
-#define pqcrystals_dilithium5_avx2_SECRETKEYBYTES pqcrystals_dilithium5_SECRETKEYBYTES
-#define pqcrystals_dilithium5_avx2_BYTES pqcrystals_dilithium5_BYTES
 
-int pqcrystals_dilithium5_avx2_keypair(uint8_t *pk, uint8_t *sk);
+int PQCLEAN_NAMESPACE_crypto_sign_keypair(uint8_t *pk, uint8_t *sk);
 
-int pqcrystals_dilithium5_avx2_signature(uint8_t *sig, size_t *siglen,
+int PQCLEAN_NAMESPACE_crypto_sign_signature(uint8_t *sig, size_t *siglen,
                                         const uint8_t *m, size_t mlen,
                                         const uint8_t *sk);
 
-int pqcrystals_dilithium5_avx2(uint8_t *sm, size_t *smlen,
+int PQCLEAN_NAMESPACE_crypto_sign(uint8_t *sm, size_t *smlen,
                               const uint8_t *m, size_t mlen,
                               const uint8_t *sk);
 
-int pqcrystals_dilithium5_avx2_verify(const uint8_t *sig, size_t siglen,
+int PQCLEAN_NAMESPACE_crypto_sign_verify(const uint8_t *sig, size_t siglen,
                                      const uint8_t *m, size_t mlen,
                                      const uint8_t *pk);
 
-int pqcrystals_dilithium5_avx2_open(uint8_t *m, size_t *mlen,
+int PQCLEAN_NAMESPACE_crypto_sign_open(uint8_t *m, size_t *mlen,
                                    const uint8_t *sm, size_t smlen,
                                    const uint8_t *pk);
 
-
 #endif

