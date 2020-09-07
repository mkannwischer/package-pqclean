--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-256/src/parameters.h
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-256/src/parameters.h
@@ -9,7 +9,7 @@
 #include "api.h"
 
 #define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
+#define BITMASK(a, size) ((1UL << ((a) % (size))) - 1) /*!< Create a mask*/
 
 
 /*

