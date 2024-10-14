--- upstream/ref/polyvec.h
+++ upstream-patched/ref/polyvec.h
@@ -28,8 +28,7 @@
 void polyvecl_invntt_tomont(polyvecl *v);
 #define polyvecl_pointwise_poly_montgomery DILITHIUM_NAMESPACE(polyvecl_pointwise_poly_montgomery)
 void polyvecl_pointwise_poly_montgomery(polyvecl *r, const poly *a, const polyvecl *v);
-#define polyvecl_pointwise_acc_montgomery \
-        DILITHIUM_NAMESPACE(polyvecl_pointwise_acc_montgomery)
+#define polyvecl_pointwise_acc_montgomery DILITHIUM_NAMESPACE(polyvecl_pointwise_acc_montgomery)
 void polyvecl_pointwise_acc_montgomery(poly *w,
                                        const polyvecl *u,
                                        const polyvecl *v);

