--- upstream/crypto_core/multsntrup857/avx/mult1024.c
+++ upstream-patched/crypto_core/multsntrup857/avx/mult1024.c
@@ -15,6 +15,26 @@
 #define mulhrs_x16 _mm256_mulhrs_epi16
 #define signmask_x16(x) _mm256_srai_epi16((x),15)
 
+typedef union {
+  int16 v[512];
+  int16x16 _dummy;
+} vec512;
+
+typedef union {
+  int16 v[8][512];
+  int16x16 _dummy;
+} vec8x512;
+
+typedef union {
+  int16 v[1024];
+  int16x16 _dummy;
+} vec1024;
+
+typedef union {
+  int16 v[4*512];
+  int16x16 _dummy;
+} vec2048;
+
 static inline int16x16 squeeze_5167_x16(int16x16 x)
 {
   return sub_x16(x,mullo_x16(mulhrs_x16(x,const_x16(6)),const_x16(5167)));
@@ -92,9 +112,10 @@
     store_x16(&fpad[3][j],f3);
   }
 
-  for (i = 0;i < 4;++i)
+  for (i = 0;i < 4;++i) {
     for (j = 256;j < 512;++j)
       fpad[i][j] = 0;
+  }
 }
 
 static void unstride(int16 f[2048],const int16 fpad[4][512])
@@ -129,13 +150,75 @@
   }
 }
 
-#define ALIGNED __attribute((aligned(512)))
-
-static const ALIGNED int16 y_7681[512] = {
-#include "precomp7681.inc"
+static const vec512 y_7681 = { .v = {
+-3593,3364,1701,2237,2194,2557,834,-1599,514,438,2555,-1887,103,1881,-549,-1738,
+-3777,-2830,1414,1986,2456,1525,2495,-1993,2956,-679,2440,-810,2804,3555,1535,-3689,
+-3625,617,2319,-2816,3696,-1483,-2250,3706,-1399,-1760,2535,638,2043,396,2310,-3600,
+3182,-1921,2876,-2088,-1100,-1296,121,2006,-1321,-1305,-3772,-7,-1431,3174,3153,3266,
+3593,-3364,-1701,-2237,-2194,-2557,-834,1599,-514,-438,-2555,1887,-103,-1881,549,1738,
+3777,2830,-1414,-1986,-2456,-1525,-2495,1993,-2956,679,-2440,810,-2804,-3555,-1535,3689,
+3625,-617,-2319,2816,-3696,1483,2250,-3706,1399,1760,-2535,-638,-2043,-396,-2310,3600,
+-3182,1921,-2876,2088,1100,1296,-121,-2006,1321,1305,3772,7,1431,-3174,-3153,-3266,
+-1532,-3816,783,-921,-2160,2762,3310,727,2789,-373,-3456,-1497,-2385,-2391,-2426,2883,
+1919,2233,-1056,2743,-2649,3750,-1168,1521,2919,-2175,-1166,-2572,-3405,-660,3831,-1681,
+404,-2764,1799,1386,-859,1390,-2133,-1464,-194,-3692,-1054,-1350,2732,3135,-915,2224,
+-486,-2835,2665,3428,-2579,1598,-3480,1533,-3417,-730,-1698,3145,2113,-1756,-2,-3588,
+1532,3816,-783,921,2160,-2762,-3310,-727,-2789,373,3456,1497,2385,2391,2426,-2883,
+-1919,-2233,1056,-2743,2649,-3750,1168,-1521,-2919,2175,1166,2572,3405,660,-3831,1681,
+-404,2764,-1799,-1386,859,-1390,2133,1464,194,3692,1054,1350,-2732,-3135,915,-2224,
+486,2835,-2665,-3428,2579,-1598,3480,-1533,3417,730,1698,-3145,-2113,1756,2,3588,
+-1404,-509,-1689,-3752,3335,2812,-1519,1669,-402,-2345,2963,370,3745,83,-796,642,
+-2874,-1403,777,3677,-1084,-3763,-188,692,-429,1338,124,-293,3366,-3408,3163,-1837,
+1012,3343,-2262,-2460,-2532,592,893,-3287,1931,2303,-3208,-2083,3214,826,2258,2965,
+-2130,2937,-2070,-3657,-1441,-2005,2386,2167,3723,2515,589,-3312,-3334,-1526,-3781,-791,
+1404,509,1689,3752,-3335,-2812,1519,-1669,402,2345,-2963,-370,-3745,-83,796,-642,
+2874,1403,-777,-3677,1084,3763,188,-692,429,-1338,-124,293,-3366,3408,-3163,1837,
+-1012,-3343,2262,2460,2532,-592,-893,3287,-1931,-2303,3208,2083,-3214,-826,-2258,-2965,
+2130,-2937,2070,3657,1441,2005,-2386,-2167,-3723,-2515,-589,3312,3334,1526,3781,791,
+658,1278,-226,1649,-436,17,-1181,1242,-3434,451,-3770,3581,2719,1779,-1144,-1509,
+-1476,-929,3542,2161,-236,3744,-1203,179,-3550,-2786,-3450,1586,-3461,-3547,1072,2918,
+-715,2230,2767,2072,1121,-2422,3794,1070,2891,222,1295,3568,2998,-434,2589,-2339,
+670,1348,-2378,-3177,-2071,2001,151,2059,2340,-1712,2815,3693,3314,-1151,2247,-1407,
+-658,-1278,226,-1649,436,-17,1181,-1242,3434,-451,3770,-3581,-2719,-1779,1144,1509,
+1476,929,-3542,-2161,236,-3744,1203,-179,3550,2786,3450,-1586,3461,3547,-1072,-2918,
+715,-2230,-2767,-2072,-1121,2422,-3794,-1070,-2891,-222,-1295,-3568,-2998,434,-2589,2339,
+-670,-1348,2378,3177,2071,-2001,-151,-2059,-2340,1712,-2815,-3693,-3314,1151,-2247,1407,
+  }
 } ;
-static const ALIGNED int16 y_10753[512] = {
-#include "precomp10753.inc"
+static const vec512 y_10753 = { .v = {
+1018,-5175,-3364,5063,-376,1341,4855,2503,3085,2982,-4744,1284,-2576,-193,3062,-4129,
+-223,-4095,-3784,-4035,357,-1931,-2236,-918,-1299,-1287,-4876,268,-4189,4616,2984,3091,
+3688,-2629,425,-4875,-2413,341,-730,-3012,2388,-4513,4742,4,1085,2565,4379,-2790,
+-4188,5213,4544,-1520,-3686,3823,2695,-4347,-1009,-205,-4102,-3550,-544,-2178,847,2935,
+-1018,5175,3364,-5063,376,-1341,-4855,-2503,-3085,-2982,4744,-1284,2576,193,-3062,4129,
+223,4095,3784,4035,-357,1931,2236,918,1299,1287,4876,-268,4189,-4616,-2984,-3091,
+-3688,2629,-425,4875,2413,-341,730,3012,-2388,4513,-4742,-4,-1085,-2565,-4379,2790,
+4188,-5213,-4544,1520,3686,-3823,-2695,4347,1009,205,4102,3550,544,2178,-847,-2935,
+5116,400,2234,2206,1068,3169,-635,326,1615,-3615,3198,5064,-512,-4580,-2998,-4828,
+-2684,-151,-4123,-779,-1586,-578,-970,1006,2213,-1458,567,454,2774,116,4734,5156,
+-1324,5294,-864,-2740,-1268,-4286,472,-2884,675,5114,-794,-4808,-3057,2981,-5341,-1356,
+2973,636,3337,1572,-3715,-2737,467,336,-2271,-909,-5023,-1841,-2045,4977,3441,-886,
+-5116,-400,-2234,-2206,-1068,-3169,635,-326,-1615,3615,-3198,-5064,512,4580,2998,4828,
+2684,151,4123,779,1586,578,970,-1006,-2213,1458,-567,-454,-2774,-116,-4734,-5156,
+1324,-5294,864,2740,1268,4286,-472,2884,-675,-5114,794,4808,3057,-2981,5341,1356,
+-2973,-636,-3337,-1572,3715,2737,-467,-336,2271,909,5023,1841,2045,-4977,-3441,886,
+-3260,73,569,-834,-4859,2487,825,-4403,5120,2788,-2279,5268,4003,2625,-2813,5068,
+693,5107,-4973,-1782,-4967,2529,4393,-1053,4519,-1160,-4328,2205,1204,-1663,-3535,-3096,
+-3360,4891,-4889,-2113,-554,2605,-4000,-4720,-1056,3995,-2151,-1893,5356,3891,279,3125,
+3419,-1927,152,-1111,-2963,5334,1510,-4670,1689,-2449,355,-2807,-624,3827,5083,-4540,
+3260,-73,-569,834,4859,-2487,-825,4403,-5120,-2788,2279,-5268,-4003,-2625,2813,-5068,
+-693,-5107,4973,1782,4967,-2529,-4393,1053,-4519,1160,4328,-2205,-1204,1663,3535,3096,
+3360,-4891,4889,2113,554,-2605,4000,4720,1056,-3995,2151,1893,-5356,-3891,-279,-3125,
+-3419,1927,-152,1111,2963,-5334,-1510,4670,-1689,2449,-355,2807,624,-3827,-5083,4540,
+-3524,3760,-2657,1381,-5015,-4621,4784,5215,4428,-1722,4254,2439,1639,-40,-2374,1930,
+-1573,-3570,-2196,-5172,4447,-1132,1635,854,-5005,1349,-1122,2117,2419,3241,-663,-3148,
+458,4601,4782,-4250,3135,573,-2015,-3453,-4408,2909,-5313,2118,-778,-2087,1409,-4144,
+2139,-2624,3410,-2428,-2662,2230,-2062,5309,-1992,4359,97,2050,2283,-2680,2237,274,
+3524,-3760,2657,-1381,5015,4621,-4784,-5215,-4428,1722,-4254,-2439,-1639,40,2374,-1930,
+1573,3570,2196,5172,-4447,1132,-1635,-854,5005,-1349,1122,-2117,-2419,-3241,663,3148,
+-458,-4601,-4782,4250,-3135,-573,2015,3453,4408,-2909,5313,-2118,778,2087,-1409,4144,
+-2139,2624,-3410,2428,2662,-2230,2062,-5309,1992,-4359,-97,-2050,-2283,2680,-2237,-274,
+  }
 } ;
 /*
   can also compute these on the fly, and share storage,
@@ -152,18 +235,20 @@
 
 static void mult1024(int16 h[2048],const int16 f[1024],const int16 g[1024])
 {
-  ALIGNED int16 fgpad[8][512];
-#define fpad fgpad
-#define gpad (fgpad+4)
+  vec8x512 fgpad;
+#define fpad (fgpad.v)
+#define gpad (fgpad.v+4)
 #define hpad fpad
-  ALIGNED int16 h_7681[2048];
-  ALIGNED int16 h_10753[2048];
+  vec2048 aligned_h_7681;
+  vec2048 aligned_h_10753;
+#define h_7681 (aligned_h_7681.v)
+#define h_10753 (aligned_h_10753.v)
   int i;
 
   stride(fpad,f);
   stride(gpad,g);
 
-  ntt512_7681(fgpad[0],8);
+  ntt512_7681(fgpad.v[0],8);
 
   for (i = 0;i < 512;i += 16) {
     int16x16 f0 = squeeze_7681_x16(load_x16(&fpad[0][i]));
@@ -196,7 +281,7 @@
     int16x16 h4 = sub_x16(d1d2d3,e13);
     int16x16 h5 = sub_x16(d2d3,e23);
     int16x16 h6 = d3;
-    int16x16 twist = load_x16(&y_7681[i]);
+    int16x16 twist = load_x16(&y_7681.v[i]);
     h4 = mulmod_7681_x16(h4,twist);
     h5 = mulmod_7681_x16(h5,twist);
     h6 = mulmod_7681_x16(h6,twist);
@@ -210,12 +295,12 @@
   }
 
   invntt512_7681(hpad[0],4);
-  unstride(h_7681,hpad);
+  unstride(h_7681,(const int16(*)[512]) hpad);
 
   stride(fpad,f);
   stride(gpad,g);
 
-  ntt512_10753(fgpad[0],8);
+  ntt512_10753(fgpad.v[0],8);
 
   for (i = 0;i < 512;i += 16) {
     int16x16 f0 = squeeze_10753_x16(load_x16(&fpad[0][i]));
@@ -248,7 +333,7 @@
     int16x16 h4 = sub_x16(d1d2d3,e13);
     int16x16 h5 = sub_x16(d2d3,e23);
     int16x16 h6 = d3;
-    int16x16 twist = load_x16(&y_10753[i]);
+    int16x16 twist = load_x16(&y_10753.v[i]);
     h4 = mulmod_10753_x16(h4,twist);
     h5 = mulmod_10753_x16(h5,twist);
     h6 = mulmod_10753_x16(h6,twist);
@@ -262,7 +347,7 @@
   }
 
   invntt512_10753(hpad[0],4);
-  unstride(h_10753,hpad);
+  unstride(h_10753,(const int16(*)[512]) hpad);
 
   for (i = 0;i < 2048;i += 16) {
     int16x16 u1 = load_x16(&h_10753[i]);
@@ -297,9 +382,11 @@
 
 int crypto_core(unsigned char *outbytes,const unsigned char *inbytes,const unsigned char *kbytes,const unsigned char *cbytes)
 {
-  ALIGNED int16 f[1024];
-  ALIGNED int16 g[1024];
-  ALIGNED int16 fg[2048];
+  vec1024 x1, x2;
+  vec2048 x3;
+#define f (x1.v)
+#define g (x2.v)
+#define fg (x3.v)
 #define h f
   int i;
   int16x16 x;
@@ -316,14 +403,14 @@
     store_x16(&f[i],x);
   }
   for (i = 0;i < p;++i) {
-    int8 gi = kbytes[i];
+    int8 gi = (int8) kbytes[i];
     int8 gi0 = gi&1;
-    g[i] = gi0-(gi&(gi0<<1));
+    g[i] = (int16) (gi0-(gi&(gi0<<1)));
   }
 
   mult1024(fg,f,g);
 
-  fg[0] -= fg[p-1];
+  fg[0] = (int16) (fg[0] - fg[p-1]);
   for (i = 0;i < 1024;i += 16) {
     int16x16 fgi = load_x16(&fg[i]);
     int16x16 fgip = load_x16(&fg[i + p]);

