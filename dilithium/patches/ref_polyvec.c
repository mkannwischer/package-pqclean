--- upstream/ref/polyvec.c
+++ upstream-patched/ref/polyvec.c
@@ -16,9 +16,11 @@
 void polyvec_matrix_expand(polyvecl mat[K], const uint8_t rho[SEEDBYTES]) {
   unsigned int i, j;
 
-  for(i = 0; i < K; ++i)
-    for(j = 0; j < L; ++j)
-      poly_uniform(&mat[i].vec[j], rho, (i << 8) + j);
+  for(i = 0; i < K; ++i) {
+    for(j = 0; j < L; ++j) {
+      poly_uniform(&mat[i].vec[j], rho, (uint16_t) ((i << 8) + j));
+    }
+  }
 }
 
 void polyvec_matrix_pointwise_montgomery(polyveck *t, const polyvecl mat[K], const polyvecl *v) {
@@ -43,7 +45,7 @@
   unsigned int i;
 
   for(i = 0; i < L; ++i)
-    poly_uniform_gamma1(&v->vec[i], seed, L*nonce + i);
+    poly_uniform_gamma1(&v->vec[i], seed, (uint16_t) (L*nonce + i));
 }
 
 void polyvecl_reduce(polyvecl *v) {
@@ -139,9 +141,10 @@
 int polyvecl_chknorm(const polyvecl *v, int32_t bound)  {
   unsigned int i;
 
-  for(i = 0; i < L; ++i)
+  for(i = 0; i < L; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }
@@ -291,9 +294,10 @@
 int polyveck_chknorm(const polyveck *v, int32_t bound) {
   unsigned int i;
 
-  for(i = 0; i < K; ++i)
+  for(i = 0; i < K; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }
@@ -374,11 +378,11 @@
 *              - const polyveck *u: pointer to input vector
 *              - const polyveck *h: pointer to input hint vector
 **************************************************/
-void polyveck_use_hint(polyveck *w, const polyveck *u, const polyveck *h) {
+void polyveck_use_hint(polyveck *w, const polyveck *v, const polyveck *h) {
   unsigned int i;
 
   for(i = 0; i < K; ++i)
-    poly_use_hint(&w->vec[i], &u->vec[i], &h->vec[i]);
+    poly_use_hint(&w->vec[i], &v->vec[i], &h->vec[i]);
 }
 
 void polyveck_pack_w1(uint8_t r[K*POLYW1_PACKEDBYTES], const polyveck *w1) {

