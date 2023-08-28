--- upstream/ref/kem.c
+++ upstream-patched/ref/kem.c
@@ -163,7 +163,7 @@
   rkprf(ss,sk+KYBER_SECRETKEYBYTES-KYBER_SYMBYTES,ct);
 
   /* Copy true key to return buffer if fail is false */
-  cmov(ss,kr,KYBER_SYMBYTES,!fail);
+  cmov(ss,kr,KYBER_SYMBYTES, (uint8_t) (1 - fail));
 
   return 0;
 }

