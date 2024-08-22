--- upstream/ref/kem.h
+++ upstream-patched/ref/kem.h
@@ -10,11 +10,11 @@
 #define CRYPTO_BYTES           KYBER_SSBYTES
 
 #if   (KYBER_K == 2)
-#define CRYPTO_ALGNAME "Kyber512"
+#define CRYPTO_ALGNAME "ML-KEM-512"
 #elif (KYBER_K == 3)
-#define CRYPTO_ALGNAME "Kyber768"
+#define CRYPTO_ALGNAME "ML-KEM-768"
 #elif (KYBER_K == 4)
-#define CRYPTO_ALGNAME "Kyber1024"
+#define CRYPTO_ALGNAME "ML-KEM-1024"
 #endif
 
 #define crypto_kem_keypair_derand KYBER_NAMESPACE(keypair_derand)

