--- upstream/ref/packing.h
+++ upstream-patched/ref/packing.h
@@ -18,7 +18,7 @@
              const polyveck *s2);
 
 #define pack_sig DILITHIUM_NAMESPACE(pack_sig)
-void pack_sig(uint8_t sig[CRYPTO_BYTES], const uint8_t c[SEEDBYTES], const polyvecl *z, const polyveck *h);
+void pack_sig(uint8_t sig[CRYPTO_BYTES], const uint8_t c[CTILDEBYTES], const polyvecl *z, const polyveck *h);
 
 #define unpack_pk DILITHIUM_NAMESPACE(unpack_pk)
 void unpack_pk(uint8_t rho[SEEDBYTES], polyveck *t1, const uint8_t pk[CRYPTO_PUBLICKEYBYTES]);
@@ -33,6 +33,6 @@
                const uint8_t sk[CRYPTO_SECRETKEYBYTES]);
 
 #define unpack_sig DILITHIUM_NAMESPACE(unpack_sig)
-int unpack_sig(uint8_t c[SEEDBYTES], polyvecl *z, polyveck *h, const uint8_t sig[CRYPTO_BYTES]);
+int unpack_sig(uint8_t c[CTILDEBYTES], polyvecl *z, polyveck *h, const uint8_t sig[CRYPTO_BYTES]);
 
 #endif

