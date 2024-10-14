--- upstream/ref/api.h
+++ upstream-patched/ref/api.h
@@ -1,98 +1,51 @@
-#ifndef API_H
-#define API_H
+#ifndef PQCLEAN_NAMESPACE_API_H
+#define PQCLEAN_NAMESPACE_API_H
 
 #include <stddef.h>
 #include <stdint.h>
 
-#define pqcrystals_dilithium2_PUBLICKEYBYTES 1312
-#define pqcrystals_dilithium2_SECRETKEYBYTES 2560
-#define pqcrystals_dilithium2_BYTES 2420
-
-#define pqcrystals_dilithium2_ref_PUBLICKEYBYTES pqcrystals_dilithium2_PUBLICKEYBYTES
-#define pqcrystals_dilithium2_ref_SECRETKEYBYTES pqcrystals_dilithium2_SECRETKEYBYTES
-#define pqcrystals_dilithium2_ref_BYTES pqcrystals_dilithium2_BYTES
-
-int pqcrystals_dilithium2_ref_keypair(uint8_t *pk, uint8_t *sk);
-
-int pqcrystals_dilithium2_ref_signature(uint8_t *sig, size_t *siglen,
-                                        const uint8_t *m, size_t mlen,
-                                        const uint8_t *ctx, size_t ctxlen,
-                                        const uint8_t *sk);
-
-int pqcrystals_dilithium2_ref(uint8_t *sm, size_t *smlen,
-                              const uint8_t *m, size_t mlen,
-                              const uint8_t *ctx, size_t ctxlen,
-                              const uint8_t *sk);
-
-int pqcrystals_dilithium2_ref_verify(const uint8_t *sig, size_t siglen,
-                                     const uint8_t *m, size_t mlen,
-                                     const uint8_t *ctx, size_t ctxlen,
-                                     const uint8_t *pk);
-
-int pqcrystals_dilithium2_ref_open(uint8_t *m, size_t *mlen,
-                                   const uint8_t *sm, size_t smlen,
-                                   const uint8_t *ctx, size_t ctxlen,
-                                   const uint8_t *pk);
-
-#define pqcrystals_dilithium3_PUBLICKEYBYTES 1952
-#define pqcrystals_dilithium3_SECRETKEYBYTES 4032
-#define pqcrystals_dilithium3_BYTES 3309
-
-#define pqcrystals_dilithium3_ref_PUBLICKEYBYTES pqcrystals_dilithium3_PUBLICKEYBYTES
-#define pqcrystals_dilithium3_ref_SECRETKEYBYTES pqcrystals_dilithium3_SECRETKEYBYTES
-#define pqcrystals_dilithium3_ref_BYTES pqcrystals_dilithium3_BYTES
-
-int pqcrystals_dilithium3_ref_keypair(uint8_t *pk, uint8_t *sk);
-
-int pqcrystals_dilithium3_ref_signature(uint8_t *sig, size_t *siglen,
-                                        const uint8_t *m, size_t mlen,
-                                        const uint8_t *ctx, size_t ctxlen,
-                                        const uint8_t *sk);
-
-int pqcrystals_dilithium3_ref(uint8_t *sm, size_t *smlen,
-                              const uint8_t *m, size_t mlen,
-                              const uint8_t *ctx, size_t ctxlen,
-                              const uint8_t *sk);
-
-int pqcrystals_dilithium3_ref_verify(const uint8_t *sig, size_t siglen,
-                                     const uint8_t *m, size_t mlen,
-                                     const uint8_t *ctx, size_t ctxlen,
-                                     const uint8_t *pk);
-
-int pqcrystals_dilithium3_ref_open(uint8_t *m, size_t *mlen,
-                                   const uint8_t *sm, size_t smlen,
-                                   const uint8_t *ctx, size_t ctxlen,
-                                   const uint8_t *pk);
-
-#define pqcrystals_dilithium5_PUBLICKEYBYTES 2592
-#define pqcrystals_dilithium5_SECRETKEYBYTES 4896
-#define pqcrystals_dilithium5_BYTES 4627
-
-#define pqcrystals_dilithium5_ref_PUBLICKEYBYTES pqcrystals_dilithium5_PUBLICKEYBYTES
-#define pqcrystals_dilithium5_ref_SECRETKEYBYTES pqcrystals_dilithium5_SECRETKEYBYTES
-#define pqcrystals_dilithium5_ref_BYTES pqcrystals_dilithium5_BYTES
-
-int pqcrystals_dilithium5_ref_keypair(uint8_t *pk, uint8_t *sk);
-
-int pqcrystals_dilithium5_ref_signature(uint8_t *sig, size_t *siglen,
-                                        const uint8_t *m, size_t mlen,
-                                        const uint8_t *ctx, size_t ctxlen,
-                                        const uint8_t *sk);
-
-int pqcrystals_dilithium5_ref(uint8_t *sm, size_t *smlen,
-                              const uint8_t *m, size_t mlen,
-                              const uint8_t *ctx, size_t ctxlen,
-                              const uint8_t *sk);
-
-int pqcrystals_dilithium5_ref_verify(const uint8_t *sig, size_t siglen,
-                                     const uint8_t *m, size_t mlen,
-                                     const uint8_t *ctx, size_t ctxlen,
-                                     const uint8_t *pk);
-
-int pqcrystals_dilithium5_ref_open(uint8_t *m, size_t *mlen,
-                                   const uint8_t *sm, size_t smlen,
-                                   const uint8_t *ctx, size_t ctxlen,
-                                   const uint8_t *pk);
-
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
+ 
+int PQCLEAN_NAMESPACE_crypto_sign_keypair(uint8_t *pk, uint8_t *sk);
+ 
+int PQCLEAN_NAMESPACE_crypto_sign_signature_ctx(uint8_t *sig, size_t *siglen,
+                                         const uint8_t *m, size_t mlen,
+                                         const uint8_t *ctx, size_t ctxlen,
+                                         const uint8_t *sk);
+ 
+int PQCLEAN_NAMESPACE_crypto_sign_ctx(uint8_t *sm, size_t *smlen,
+                               const uint8_t *m, size_t mlen,
+                               const uint8_t *ctx, size_t ctxlen,
+                               const uint8_t *sk);
+ 
+int PQCLEAN_NAMESPACE_crypto_sign_verify_ctx(const uint8_t *sig, size_t siglen,
+                                      const uint8_t *m, size_t mlen,
+                                      const uint8_t *ctx, size_t ctxlen,
+                                      const uint8_t *pk);
+ 
+int PQCLEAN_NAMESPACE_crypto_sign_open_ctx(uint8_t *m, size_t *mlen,
+                                    const uint8_t *sm, size_t smlen,
+                                    const uint8_t *ctx, size_t ctxlen,
+                                    const uint8_t *pk);
+
+#define PQCLEAN_NAMESPACE_crypto_sign_signature(sig, siglen, m, mlen, sk) PQCLEAN_NAMESPACE_crypto_sign_signature_ctx(sig, siglen, m, mlen, NULL, 0, sk)
+#define PQCLEAN_NAMESPACE_crypto_sign(sm, smlen, m, mlen, sk) PQCLEAN_NAMESPACE_crypto_sign_ctx(sm, smlen, m, mlen, NULL, 0, sk)
+#define PQCLEAN_NAMESPACE_crypto_sign_verify(sig, siglen, m, mlen, pk) PQCLEAN_NAMESPACE_crypto_sign_verify_ctx(sig, siglen, m, mlen, NULL, 0, pk)
+#define PQCLEAN_NAMESPACE_crypto_sign_open(m, mlen, sm, smlen, pk) PQCLEAN_NAMESPACE_crypto_sign_open_ctx(m, mlen, sm, smlen, NULL, 0, pk)
 
 #endif

