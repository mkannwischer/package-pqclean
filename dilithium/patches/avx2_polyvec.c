--- upstream/avx2/polyvec.c
+++ upstream-patched/avx2/polyvec.c
@@ -5,6 +5,8 @@
 #include "ntt.h"
 #include "consts.h"
 
+#define UNUSED(x) (void)x
+
 /*************************************************
 * Name:        expand_mat
 *
@@ -24,7 +26,8 @@
   polyvec_matrix_expand_row3(&mat[3], NULL, rho);
 }
 
-void polyvec_matrix_expand_row0(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row0(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 0, 1, 2, 3);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -32,7 +35,8 @@
   poly_nttunpack(&rowa->vec[3]);
 }
 
-void polyvec_matrix_expand_row1(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row1(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 256, 257, 258, 259);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -40,7 +44,8 @@
   poly_nttunpack(&rowa->vec[3]);
 }
 
-void polyvec_matrix_expand_row2(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row2(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 512, 513, 514, 515);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -48,7 +53,8 @@
   poly_nttunpack(&rowa->vec[3]);
 }
 
-void polyvec_matrix_expand_row3(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row3(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 768, 769, 770, 771);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -96,7 +102,8 @@
   poly_nttunpack(&rowb->vec[0]);
 }
 
-void polyvec_matrix_expand_row3(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row3(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[1], &rowa->vec[2], &rowa->vec[3], &rowa->vec[4], rho, 769, 770, 771, 772);
   poly_nttunpack(&rowa->vec[1]);
   poly_nttunpack(&rowa->vec[2]);
@@ -174,7 +181,8 @@
   poly_nttunpack(&rowb->vec[2]);
 }
 
-void polyvec_matrix_expand_row3(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row3(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[3], &rowa->vec[4], &rowa->vec[5], &rowa->vec[6], rho, 771, 772, 773, 774);
   poly_nttunpack(&rowa->vec[3]);
   poly_nttunpack(&rowa->vec[4]);
@@ -221,7 +229,8 @@
   poly_nttunpack(&rowb->vec[2]);
 }
 
-void polyvec_matrix_expand_row7(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row7(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[3], &rowa->vec[4], &rowa->vec[5], &rowa->vec[6], rho, 1795, 1796, 1797, 1798);
   poly_nttunpack(&rowa->vec[3]);
   poly_nttunpack(&rowa->vec[4]);
@@ -341,9 +350,10 @@
 int polyvecl_chknorm(const polyvecl *v, int32_t bound)  {
   unsigned int i;
 
-  for(i = 0; i < L; ++i)
+  for(i = 0; i < L; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }
@@ -492,9 +502,10 @@
 int polyveck_chknorm(const polyveck *v, int32_t bound) {
   unsigned int i;
 
-  for(i = 0; i < K; ++i)
+  for(i = 0; i < K; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }

