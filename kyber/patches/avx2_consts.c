--- upstream/avx2/consts.c
+++ upstream-patched/avx2/consts.c
@@ -12,143 +12,144 @@
 #define MONTSQLO (MONTSQHI*QINV % 65536)
 #define MASK 4095
 
-__attribute__((aligned(32)))
-const uint16_t qdata[928] = {
+
+const qdata_t qdata = {.as_arr = {
 #define _16XQ 0
-  Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q,
+    Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q,
 
 #define _16XQINV 16
-  QINV, QINV, QINV, QINV, QINV, QINV, QINV, QINV,
-  QINV, QINV, QINV, QINV, QINV, QINV, QINV, QINV,
+    QINV, QINV, QINV, QINV, QINV, QINV, QINV, QINV,
+    QINV, QINV, QINV, QINV, QINV, QINV, QINV, QINV,
 
 #define _16XV 32
-  V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V,
+    V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V,
 
 #define _16XFLO 48
-  FLO, FLO, FLO, FLO, FLO, FLO, FLO, FLO,
-  FLO, FLO, FLO, FLO, FLO, FLO, FLO, FLO,
+    FLO, FLO, FLO, FLO, FLO, FLO, FLO, FLO,
+    FLO, FLO, FLO, FLO, FLO, FLO, FLO, FLO,
 
 #define _16XFHI 64
-  FHI, FHI, FHI, FHI, FHI, FHI, FHI, FHI,
-  FHI, FHI, FHI, FHI, FHI, FHI, FHI, FHI,
+    FHI, FHI, FHI, FHI, FHI, FHI, FHI, FHI,
+    FHI, FHI, FHI, FHI, FHI, FHI, FHI, FHI,
 
 #define _16XMONTSQLO 80
-  MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
-  MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
-  MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
-  MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
+    MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
+    MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
+    MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
+    MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
 
 #define _16XMONTSQHI 96
-  MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
-  MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
-  MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
-  MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
+    MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
+    MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
+    MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
+    MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
 
 #define _16XMASK 112
-  MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK,
-  MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK,
+    MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK,
+    MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK,
 
 #define _ZETAS_EXP 128
-  31499, 31499,  2571,  2571, 14746, 14746,  2970,  2970,
-  13525, 13525, 13525, 13525, 13525, 13525, 13525, 13525,
-  53134, 53134, 53134, 53134, 53134, 53134, 53134, 53134,
-   1493,  1493,  1493,  1493,  1493,  1493,  1493,  1493,
-   1422,  1422,  1422,  1422,  1422,  1422,  1422,  1422,
-  44630, 44630, 44630, 44630, 27758, 27758, 27758, 27758,
-  61737, 61737, 61737, 61737, 49846, 49846, 49846, 49846,
-   3158,  3158,  3158,  3158,   622,   622,   622,   622,
-   1577,  1577,  1577,  1577,   182,   182,   182,   182,
-  59709, 59709, 17364, 17364, 39176, 39176, 36479, 36479,
-   5572,  5572, 64434, 64434, 21439, 21439, 39295, 39295,
-    573,   573,  2004,  2004,   264,   264,   383,   383,
-   2500,  2500,  1458,  1458,  1727,  1727,  3199,  3199,
-  59847, 59020,  1497, 30967, 41972, 20179, 20711, 25081,
-  52740, 26617, 16065, 53095,  9135, 64887, 39550, 27837,
-   1223,   652,  2777,  1015,  2036,  1491,  3047,  1785,
-    516,  3321,  3009,  2663,  1711,  2167,   126,  1469,
-  65202, 54059, 33310, 20494, 37798,   945, 50654,  6182,
-  32011, 10631, 29176, 36775, 47051, 17561, 51106, 60261,
-   2226,   555,  2078,  1550,   422,   177,  3038,  1574,
-   3083,  1159,  2552,  2727,  1739,  2457,   418,  3173,
-  11182, 13387, 51303, 43881, 13131, 60950, 23093,  5493,
-  33034, 30318, 46795, 12639, 20100, 18525, 19529, 52918,
-    430,   843,   871,   105,   587,  3094,  2869,  1653,
-    778,  3182,  1483,  1119,   644,   349,   329,  3254,
-    788,   788,  1812,  1812, 28191, 28191, 28191, 28191,
-  28191, 28191, 28191, 28191, 48842, 48842, 48842, 48842,
-  48842, 48842, 48842, 48842,   287,   287,   287,   287,
-    287,   287,   287,   287,   202,   202,   202,   202,
-    202,   202,   202,   202, 10690, 10690, 10690, 10690,
-   1359,  1359,  1359,  1359, 54335, 54335, 54335, 54335,
-  31164, 31164, 31164, 31164,   962,   962,   962,   962,
-   2127,  2127,  2127,  2127,  1855,  1855,  1855,  1855,
-   1468,  1468,  1468,  1468, 37464, 37464, 24313, 24313,
-  55004, 55004,  8800,  8800, 18427, 18427,  8859,  8859,
-  26676, 26676, 49374, 49374,  2648,  2648,  1017,  1017,
-    732,   732,   608,   608,  1787,  1787,   411,   411,
-   3124,  3124,  1758,  1758, 19884, 37287, 49650, 56638,
-  37227,  9076, 35338, 18250, 13427, 14017, 36381, 52780,
-  16832,  4312, 41381, 47622,  2476,  3239,  3058,   830,
-    107,  1908,  3082,  2378,  2931,   961,  1821,  2604,
-    448,  2264,   677,  2054, 34353, 25435, 58154, 24392,
-  44610, 10946, 24215, 16990, 10336, 57603, 43035, 10907,
-  31637, 28644, 23998, 48114,   817,   603,  1322,  1864,
-   2114,  1218,  2455,  2142,  2144,  2051,  1819,  2459,
-   3221,   996,   958,  1522, 20297,  2146, 15356, 33152,
-  59257, 50634, 54492, 14470, 44039, 45338, 23211, 48094,
-  41677, 45279,  7757, 23132,  1097,   610,  2044,   384,
-   3193,  1994,   220,  1670,  1799,   794,  2475,   478,
-   3021,   991,  1869,  1628,     0,     0,     0,     0,
+    31499, 31499,  2571,  2571, 14746, 14746,  2970,  2970,
+    13525, 13525, 13525, 13525, 13525, 13525, 13525, 13525,
+    53134, 53134, 53134, 53134, 53134, 53134, 53134, 53134,
+     1493,  1493,  1493,  1493,  1493,  1493,  1493,  1493,
+     1422,  1422,  1422,  1422,  1422,  1422,  1422,  1422,
+    44630, 44630, 44630, 44630, 27758, 27758, 27758, 27758,
+    61737, 61737, 61737, 61737, 49846, 49846, 49846, 49846,
+     3158,  3158,  3158,  3158,   622,   622,   622,   622,
+     1577,  1577,  1577,  1577,   182,   182,   182,   182,
+    59709, 59709, 17364, 17364, 39176, 39176, 36479, 36479,
+     5572,  5572, 64434, 64434, 21439, 21439, 39295, 39295,
+      573,   573,  2004,  2004,   264,   264,   383,   383,
+     2500,  2500,  1458,  1458,  1727,  1727,  3199,  3199,
+    59847, 59020,  1497, 30967, 41972, 20179, 20711, 25081,
+    52740, 26617, 16065, 53095,  9135, 64887, 39550, 27837,
+     1223,   652,  2777,  1015,  2036,  1491,  3047,  1785,
+      516,  3321,  3009,  2663,  1711,  2167,   126,  1469,
+    65202, 54059, 33310, 20494, 37798,   945, 50654,  6182,
+    32011, 10631, 29176, 36775, 47051, 17561, 51106, 60261,
+     2226,   555,  2078,  1550,   422,   177,  3038,  1574,
+     3083,  1159,  2552,  2727,  1739,  2457,   418,  3173,
+    11182, 13387, 51303, 43881, 13131, 60950, 23093,  5493,
+    33034, 30318, 46795, 12639, 20100, 18525, 19529, 52918,
+      430,   843,   871,   105,   587,  3094,  2869,  1653,
+      778,  3182,  1483,  1119,   644,   349,   329,  3254,
+      788,   788,  1812,  1812, 28191, 28191, 28191, 28191,
+    28191, 28191, 28191, 28191, 48842, 48842, 48842, 48842,
+    48842, 48842, 48842, 48842,   287,   287,   287,   287,
+      287,   287,   287,   287,   202,   202,   202,   202,
+      202,   202,   202,   202, 10690, 10690, 10690, 10690,
+     1359,  1359,  1359,  1359, 54335, 54335, 54335, 54335,
+    31164, 31164, 31164, 31164,   962,   962,   962,   962,
+     2127,  2127,  2127,  2127,  1855,  1855,  1855,  1855,
+     1468,  1468,  1468,  1468, 37464, 37464, 24313, 24313,
+    55004, 55004,  8800,  8800, 18427, 18427,  8859,  8859,
+    26676, 26676, 49374, 49374,  2648,  2648,  1017,  1017,
+      732,   732,   608,   608,  1787,  1787,   411,   411,
+     3124,  3124,  1758,  1758, 19884, 37287, 49650, 56638,
+    37227,  9076, 35338, 18250, 13427, 14017, 36381, 52780,
+    16832,  4312, 41381, 47622,  2476,  3239,  3058,   830,
+      107,  1908,  3082,  2378,  2931,   961,  1821,  2604,
+      448,  2264,   677,  2054, 34353, 25435, 58154, 24392,
+    44610, 10946, 24215, 16990, 10336, 57603, 43035, 10907,
+    31637, 28644, 23998, 48114,   817,   603,  1322,  1864,
+     2114,  1218,  2455,  2142,  2144,  2051,  1819,  2459,
+     3221,   996,   958,  1522, 20297,  2146, 15356, 33152,
+    59257, 50634, 54492, 14470, 44039, 45338, 23211, 48094,
+    41677, 45279,  7757, 23132,  1097,   610,  2044,   384,
+     3193,  1994,   220,  1670,  1799,   794,  2475,   478,
+     3021,   991,  1869,  1628,     0,     0,     0,     0,
 
 #define _ZETAS_INV_EXP 528
-  42405, 57780, 20258, 23860, 17443, 42326, 20199, 21498,
-  51067, 11045, 14903,  6280, 32385, 50181, 63391, 45240,
-   1701,  1460,  2338,   308,  2851,   854,  2535,  1530,
-   1659,  3109,  1335,   136,  2945,  1285,  2719,  2232,
-  17423, 41539, 36893, 33900, 54630, 22502,  7934, 55201,
-  48547, 41322, 54591, 20927, 41145,  7383, 40102, 31184,
-   1807,  2371,  2333,   108,   870,  1510,  1278,  1185,
-   1187,   874,  2111,  1215,  1465,  2007,  2726,  2512,
-  17915, 24156, 61225, 48705, 12757, 29156, 51520, 52110,
-  47287, 30199, 56461, 28310,  8899, 15887, 28250, 45653,
-   1275,  2652,  1065,  2881,   725,  1508,  2368,   398,
-    951,   247,  1421,  3222,  2499,   271,    90,   853,
-  16163, 16163, 38861, 38861, 56678, 56678, 47110, 47110,
-  56737, 56737, 10533, 10533, 41224, 41224, 28073, 28073,
-   1571,  1571,   205,   205,  2918,  2918,  1542,  1542,
-   2721,  2721,  2597,  2597,  2312,  2312,   681,   681,
-  34373, 34373, 34373, 34373, 11202, 11202, 11202, 11202,
-  64178, 64178, 64178, 64178, 54847, 54847, 54847, 54847,
-   1861,  1861,  1861,  1861,  1474,  1474,  1474,  1474,
-   1202,  1202,  1202,  1202,  2367,  2367,  2367,  2367,
-  16695, 16695, 16695, 16695, 16695, 16695, 16695, 16695,
-  37346, 37346, 37346, 37346, 37346, 37346, 37346, 37346,
-   3127,  3127,  3127,  3127,  3127,  3127,  3127,  3127,
-   3042,  3042,  3042,  3042,  3042,  3042,  3042,  3042,
-  64749, 64749,  1517,  1517, 12619, 46008, 47012, 45437,
-  52898, 18742, 35219, 32503, 60044, 42444,  4587, 52406,
-  21656, 14234, 52150, 54355,    75,  3000,  2980,  2685,
-   2210,  1846,   147,  2551,  1676,   460,   235,  2742,
-   3224,  2458,  2486,  2899,  5276, 14431, 47976, 18486,
-  28762, 36361, 54906, 33526, 59355, 14883, 64592, 27739,
-  45043, 32227, 11478,   335,   156,  2911,   872,  1590,
-    602,   777,  2170,   246,  1755,   291,  3152,  2907,
-   1779,  1251,  2774,  1103, 37700, 25987,   650, 56402,
-  12442, 49472, 38920, 12797, 40456, 44826, 45358, 23565,
-  34570, 64040,  6517,  5690,  1860,  3203,  1162,  1618,
-    666,   320,     8,  2813,  1544,   282,  1838,  1293,
-   2314,   552,  2677,  2106, 26242, 26242, 44098, 44098,
-   1103,  1103, 59965, 59965, 29058, 29058, 26361, 26361,
-  48173, 48173,  5828,  5828,   130,   130,  1602,  1602,
-   1871,  1871,   829,   829,  2946,  2946,  3065,  3065,
-   1325,  1325,  2756,  2756, 15691, 15691, 15691, 15691,
-   3800,  3800,  3800,  3800, 37779, 37779, 37779, 37779,
-  20907, 20907, 20907, 20907,  3147,  3147,  3147,  3147,
-   1752,  1752,  1752,  1752,  2707,  2707,  2707,  2707,
-    171,   171,   171,   171, 12403, 12403, 12403, 12403,
-  12403, 12403, 12403, 12403, 52012, 52012, 52012, 52012,
-  52012, 52012, 52012, 52012,  1907,  1907,  1907,  1907,
-   1907,  1907,  1907,  1907,  1836,  1836,  1836,  1836,
-   1836,  1836,  1836,  1836, 50791, 50791,   359,   359,
-  60300, 60300,  1932,  1932,     0,     0,     0,     0
+    42405, 57780, 20258, 23860, 17443, 42326, 20199, 21498,
+    51067, 11045, 14903,  6280, 32385, 50181, 63391, 45240,
+     1701,  1460,  2338,   308,  2851,   854,  2535,  1530,
+     1659,  3109,  1335,   136,  2945,  1285,  2719,  2232,
+    17423, 41539, 36893, 33900, 54630, 22502,  7934, 55201,
+    48547, 41322, 54591, 20927, 41145,  7383, 40102, 31184,
+     1807,  2371,  2333,   108,   870,  1510,  1278,  1185,
+     1187,   874,  2111,  1215,  1465,  2007,  2726,  2512,
+    17915, 24156, 61225, 48705, 12757, 29156, 51520, 52110,
+    47287, 30199, 56461, 28310,  8899, 15887, 28250, 45653,
+     1275,  2652,  1065,  2881,   725,  1508,  2368,   398,
+      951,   247,  1421,  3222,  2499,   271,    90,   853,
+    16163, 16163, 38861, 38861, 56678, 56678, 47110, 47110,
+    56737, 56737, 10533, 10533, 41224, 41224, 28073, 28073,
+     1571,  1571,   205,   205,  2918,  2918,  1542,  1542,
+     2721,  2721,  2597,  2597,  2312,  2312,   681,   681,
+    34373, 34373, 34373, 34373, 11202, 11202, 11202, 11202,
+    64178, 64178, 64178, 64178, 54847, 54847, 54847, 54847,
+     1861,  1861,  1861,  1861,  1474,  1474,  1474,  1474,
+     1202,  1202,  1202,  1202,  2367,  2367,  2367,  2367,
+    16695, 16695, 16695, 16695, 16695, 16695, 16695, 16695,
+    37346, 37346, 37346, 37346, 37346, 37346, 37346, 37346,
+     3127,  3127,  3127,  3127,  3127,  3127,  3127,  3127,
+     3042,  3042,  3042,  3042,  3042,  3042,  3042,  3042,
+    64749, 64749,  1517,  1517, 12619, 46008, 47012, 45437,
+    52898, 18742, 35219, 32503, 60044, 42444,  4587, 52406,
+    21656, 14234, 52150, 54355,    75,  3000,  2980,  2685,
+     2210,  1846,   147,  2551,  1676,   460,   235,  2742,
+     3224,  2458,  2486,  2899,  5276, 14431, 47976, 18486,
+    28762, 36361, 54906, 33526, 59355, 14883, 64592, 27739,
+    45043, 32227, 11478,   335,   156,  2911,   872,  1590,
+      602,   777,  2170,   246,  1755,   291,  3152,  2907,
+     1779,  1251,  2774,  1103, 37700, 25987,   650, 56402,
+    12442, 49472, 38920, 12797, 40456, 44826, 45358, 23565,
+    34570, 64040,  6517,  5690,  1860,  3203,  1162,  1618,
+      666,   320,     8,  2813,  1544,   282,  1838,  1293,
+     2314,   552,  2677,  2106, 26242, 26242, 44098, 44098,
+     1103,  1103, 59965, 59965, 29058, 29058, 26361, 26361,
+    48173, 48173,  5828,  5828,   130,   130,  1602,  1602,
+     1871,  1871,   829,   829,  2946,  2946,  3065,  3065,
+     1325,  1325,  2756,  2756, 15691, 15691, 15691, 15691,
+     3800,  3800,  3800,  3800, 37779, 37779, 37779, 37779,
+    20907, 20907, 20907, 20907,  3147,  3147,  3147,  3147,
+     1752,  1752,  1752,  1752,  2707,  2707,  2707,  2707,
+      171,   171,   171,   171, 12403, 12403, 12403, 12403,
+    12403, 12403, 12403, 12403, 52012, 52012, 52012, 52012,
+    52012, 52012, 52012, 52012,  1907,  1907,  1907,  1907,
+     1907,  1907,  1907,  1907,  1836,  1836,  1836,  1836,
+     1836,  1836,  1836,  1836, 50791, 50791,   359,   359,
+    60300, 60300,  1932,  1932,     0,     0,     0,     0
+  }
 };

