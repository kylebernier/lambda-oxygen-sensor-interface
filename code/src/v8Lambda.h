/**
 * @file v8Lambda.h
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 November 07
 *
 * @brief Provides lookup table for lambda values
 *
 */

#ifndef __V8LAMBDA_H
#define __V8LAMBDA_H

int v8Lambda_Lookup[] = {614,614,614,614,614,614,614,614,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,620,620,620,620,620,620,620,620,620,620,620,620,620,620,621,621,621,621,621,621,621,621,621,621,621,621,621,621,622,622,622,622,622,622,622,622,622,622,622,622,622,623,623,623,623,623,623,623,623,623,623,623,623,624,624,624,624,624,624,624,624,624,624,624,624,625,625,625,625,625,625,625,625,625,625,625,625,626,626,626,626,626,626,626,626,626,626,627,627,627,627,627,627,627,627,627,627,627,627,628,628,628,628,628,628,628,628,628,628,629,629,629,629,629,629,629,629,629,629,630,630,630,630,630,630,630,630,630,630,631,631,631,631,631,631,631,631,631,631,632,632,632,632,632,632,632,632,632,633,633,633,633,633,633,633,633,633,634,634,634,634,634,634,634,634,634,635,635,635,635,635,635,635,635,635,636,636,636,636,636,636,636,636,637,637,637,637,637,637,637,637,638,638,638,638,638,638,638,638,638,639,639,639,639,639,639,639,639,640,640,640,640,640,640,640,640,641,641,641,641,641,641,641,642,642,642,642,642,642,642,642,643,643,643,643,643,643,643,644,644,644,644,644,644,644,644,645,645,645,645,645,645,645,646,646,646,646,646,646,647,647,647,647,647,647,647,647,648,648,648,648,648,648,649,649,649,649,649,649,649,650,650,650,650,650,650,651,651,651,651,651,651,651,652,652,652,652,652,652,652,653,653,653,653,653,653,654,654,654,654,654,654,655,655,655,655,655,655,656,656,656,656,656,656,657,657,657,657,657,657,658,658,658,658,658,658,659,659,659,659,659,660,660,660,660,660,660,661,661,661,661,661,661,662,662,662,662,662,662,663,663,663,663,664,664,664,664,664,664,665,665,665,665,665,665,666,666,666,666,666,667,667,667,667,667,668,668,668,668,668,669,669,669,669,669,670,670,670,670,670,671,671,671,671,671,672,672,672,672,672,673,673,673,673,673,674,674,674,674,674,675,675,675,675,675,676,676,676,676,677,677,677,677,677,678,678,678,678,678,679,679,679,679,680,680,680,680,680,681,681,681,681,682,682,682,682,682,683,683,683,683,684,684,684,684,685,685,685,685,685,686,686,686,686,687,687,687,687,688,688,688,688,689,689,689,689,690,690,690,690,691,691,691,691,692,692,692,692,692,693,693,693,693,694,694,694,694,695,695,695,695,696,696,696,697,697,697,697,698,698,698,698,699,699,699,699,700,700,700,700,701,701,701,701,702,702,702,703,703,703,703,704,704,704,705,705,705,705,705,706,706,706,707,707,707,708,708,708,708,709,709,709,710,710,710,710,711,711,711,711,712,712,712,713,713,713,714,714,714,714,715,715,715,716,716,716,717,717,717,718,718,718,718,719,719,719,720,720,720,721,721,721,721,722,722,722,723,723,723,724,724,724,725,725,725,725,726,726,726,727,727,728,728,728,728,729,729,729,730,730,730,731,731,731,732,732,732,733,733,733,734,734,734,735,735,735,736,736,737,737,737,737,738,738,739,739,739,740,740,740,740,741,741,742,742,742,743,743,743,744,744,745,745,745,745,746,746,747,747,747,748,748,748,749,749,750,750,750,751,751,751,752,752,752,753,753,754,754,755,755,755,755,756,756,757,757,757,758,758,759,759,759,760,760,761,761,762,762,762,763,763,763,764,764,764,765,765,766,766,766,767,767,768,768,769,769,769,770,770,771,771,772,772,773,773,773,774,774,775,775,775,776,776,777,777,777,778,778,779,779,779,780,781,781,781,782,782,783,783,783,784,785,785,785,786,786,787,787,787,788,789,789,789,790,790,791,791,792,792,793,793,793,794,795,795,795,796,796,797,797,798,798,799,799,800,800,800,801,802,802,802,803,803,804,804,805,805,806,806,807,807,808,808,809,809,810,810,811,811,812,812,813,813,814,814,815,815,816,817,817,817,818,818,819,819,820,820,821,822,822,822,823,824,824,825,825,826,826,827,827,828,829,829,829,830,830,831,832,832,833,833,834,834,835,835,836,837,837,837,838,839,839,840,840,841,842,842,843,843,844,844,845,845,846,847,847,848,849,849,850,850,851,851,852,852,853,854,854,855,855,856,857,857,858,858,859,860,860,861,861,862,863,863,864,865,865,866,866,867,868,868,869,869,870,871,871,872,872,873,874,875,875,876,877,877,878,878,879,880,880,881,882,882,883,884,884,885,886,886,887,887,888,889,889,890,891,892,892,893,893,894,895,896,896,897,898,898,899,899,901,901,902,902,903,904,905,905,906,907,908,908,909,910,910,911,912,912,913,914,915,915,916,917,918,918,919,920,921,921,922,923,924,924,925,925,927,927,928,928,930,930,931,932,932,933,934,935,935,937,937,938,939,939,940,941,942,942,944,944,945,946,946,948,948,949,950,950,952,952,953,954,955,956,956,957,958,959,960,960,961,962,963,964,964,965,966,967,968,968,970,971,971,972,973,974,975,975,976,978,978,979,980,980,982,983,983,984,985,986,987,988,988,990,991,991,992,993,994,995,996,996,998,999,999,1000,1002,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1012,1012,1013,1015,1016,1016,1017,1019,1019,1020,1021,1022,1023,1024,1025,1026,1027,1028,1029,1030,1031,1032,1033,1034,1035,1036,1037,1038,1039,1040,1041,1042,1043,1044,1045,1046,1047,1048,1049,1051,1051,1052,1053,1054,1056,1057,1057,1058,1060,1061,1062,1063,1064,1065,1066,1067,1068,1070,1071,1072,1072,1073,1075,1076,1077,1078,1080,1081,1081,1082,1083,1085,1086,1087,1088,1090,1091,1092,1093,1093,1095,1096,1097,1098,1100,1101,1102,1103,1104,1106,1107,1108,1109,1111,1112,1113,1114,1115,1116,1117,1118,1119,1121,1122,1123,1124,1125,1127,1128,1129,1130,1132,1133,1134,1135,1137,1139,1140,1141,1142,1143,1145,1146,1147,1148,1150,1151,1152,1153,1154,1156,1157,1158,1160,1162,1163,1164,1165,1166,1168,1169,1170,1171,1174,1175,1176,1177,1178,1180,1181,1183,1184,1186,1187,1188,1189,1190,1193,1194,1195,1196,1198,1200,1201,1202,1203,1205,1207,1208,1209,1211,1212,1214,1215,1216,1218,1220,1221,1222,1224,1226,1227,1228,1229,1232,1233,1234,1235,1238,1239,1240,1242,1243,1245,1247,1248,1249,1252,1253,1254,1255,1257,1259,1261,1262,1263,1264,1267,1268,1270,1271,1274,1275,1276,1278,1279,1282,1283,1284,1286,1288,1290,1291,1292,1294,1296,1298,1299,1301,1303,1305,1306,1307,1309,1312,1313,1314,1316,1319,1320,1322,1323,1324,1327,1329,1330,1332,1334,1336,1337,1339,1340,1343,1345,1346,1348,1351,1352,1354,1355,1357,1360,1361,1363,1364,1367,1369,1370,1372,1373,1377,1378,1380,1381,1384,1386,1387,1389,1391,1394,1395,1397,1399,1402,1403,1405,1407,1408,1412,1413,1415,1416,1420,1421,1423,1425,1426,1430,1431,1433,1435,1437,1440,1442,1443,1445,1448,1450,1452,1454,1455,1459,1461,1462,1464,1468,1469,1471,1473,1475,1478,1480,1482,1484,1487,1489,1491,1493,1495,1498,1500,1502,1504,1508,1510,1511,1513,1515,1519,1521,1523,1525,1529,1530,1532,1534,1536,1540,1542,1544,1546,1550,1552,1554,1556,1558,1562,1564,1566,1568,1572,1574,1576,1578,1580,1584,1586,1588,1590,1595,1597,1599,1601,1603,1607,1609,1612,1614,1618,1620,1622,1624,1627,1631,1633,1635,1638,1640,1644,1646,1649,1651,1655,1658,1660,1662,1664,1669,1671,1674,1676,1681,1683,1685,1688,1690,1695,1697,1699,1702,1706,1709,1711,1714,1716,1721,1723,1726,1728,1733,1736,1738,1741,1743,1748,1751,1753,1756,1761,1763,1766,1768,1771,1776,1779,1781,1784,1789,1792,1794,1797,1800,1805,1808,1810,1813,1818,1821,1824,1826,1829,1835,1837,1840,1843,1849,1851,1854,1857,1860,1865,1868,1871,1874,1880,1883,1886,1888,1891,1897,1900,1903,1906,1912,1915,1918,1921,1924,1930,1933,1936,1939,1942,1948,1952,1955,1958,1964,1967,1970,1973,1977,1983,1986,1989,1993,1999,2002,2006,2009,2012,2019,2022,2025,2029,2035,2039,2042,2045,2049,2056,2059,2063,2066,2073,2076,2080,2083,2087,2094,2098,2101,2105,2112,2116,2119,2123,2126,2134,2137,2141,2145,2152,2156,2160,2164,2167,2175,2179,2183,2186,2194,2198,2202,2206,2210,2218,2222,2225,2229,2237,2242,2246,2250,2254,2262,2266,2270,2274,2283,2287,2291,2295,2299,2308,2312,2316,2321,2325,2334,2338,2342,2347,2356,2360,2365,2369,2373,2382,2387,2392,2396,2405,2410,2415,2419,2424,2433,2438,2443,2447,2457,2462,2467,2471,2476,2486,2491,2496,2501,2511,2516,2521,2526,2531,2541,2546,2551,2556,2567,2572,2577,2583,2588,2598,2604,2609,2615,2625,2631,2636,2642,2647,2658,2664,2669,2675,2686,2692,2698,2703,2709,2721,2727,2732,2738,2750,2756,2762,2768,2774,2786,2792,2798,2804,2817,2823,2829,2835,2842,2854,2861,2867,2873,2886,2893,2899,2906,2912,2926,2932,2939,2946,2952,2966,2973,2980,2987,3001,3008,3015,3022,3029,3043,3050,3057,3064,3079,3086,3094,3101,3109,3123,3131,3139,3146,3161,3169,3177,3185,3192,3208,3216,3224,3232,3248,3256,3264,3272,3281,3297,3306,3314,3322,3339,3348,3356,3365,3374,3391,3400,3409,3417,3435,3444,3453,3462,3472,3490,3499,3508,3518,3537,3546,3556,3565,3575,3594,3604,3614,3624,3644,3654,3664,3674,3684,3705,3715,3725,3736,3757,3768,3778,3789,3800,3822,3833,3844,3855,3866,3888,3900,3911,3923,3946,3957,3969,3981,3993,4016,4028,4041,4053,4077,4090,4102,4115,4127,4153,4165,4178,4191,4217,4231,4244,4257,4271,4298,4311,4325,4339,4367,4381,4395,4409,4424,4453,4467,4482,4497,4527,4542,4557,4572,4587,4618,4634,4650,4666,4698,4714,4730,4746,4763,4796,4813,4830,4847,4881,4898,4916,4933,4951,4987,5005,5023,5041,5078,5097,5116,5135,5154,5193,5212,5232,5251,5291,5312,5332,5352,5373,5415,5436,5457,5479,5522,5544,5566,5588,5610,5656,5679,5702,5725,5748,5796,5820,5844,5868,5917,5942,5968,5993,6018,6070,6096,6123,6149,6203,6230,6258,6286,6314,6370,6399,6428,6457,6516,6546,6576,6607,6637,6700,6731,6763,6795,6860,6893,6927,6960,6994,7063,7098,7133,7169,7241,7277,7314,7352,7389,7466,7504,7544,7583,7663,7704,7745,7787,7829,7914,7958,8001,8046,8136,8181,8228,8274,8321,8417,8466,8515,8565,8667,8718,8770,8823,8876,8985,9040,9096,9153,9268,9327,9386,9446,9507,9631,9694,9758,9823,9955,10022,10090,10159,10229,10372,10445,10519,10593,10669,10824,10903,10983,11065,11231,11316,11402,11490,11578,11760,11853,11947,12043,12239,12339,12441,12544,12650,12865,12976,13088,13202,13437,13557,13679,13804,13930,14191,14324,14460,14599,14885,15031,15181,15333,15489,15809,15974,16143,16315,16669,16853,17040,17231,17426,17830,18039,18253,18471,18924,19159,19400,19646,19899,20424,20697,20977,21264,21863,22175,22495,22825,23165,23875,24246,24628,25023,25850,26284,26733,27197,27678,28690,29224,29777,30352,31570,32216,32888,33588,34319,35878,36711,37583,38497,39456,41522,42638,43815,45057,47764,49241,50812,52485,54271,58231,60433,62807,65374,71186,74494,78123,82121,86546,96991,1.0321e+05,1.1028e+05,1.1839e+05,1.3876e+05,1.5182e+05,1.6757e+05,1.8695e+05,2.1139e+05,2.8612e+05,3.4748e+05,4.4227e+05,6.0802e+05,2.421e+06,-4.9465e+06,-1.224e+06,-6.9862e+05,-4.889e+05,-3.056e+05,-2.5739e+05,-2.2234e+05,-1.9571e+05,-1.5792e+05,-1.4402e+05,-1.3238e+05,-1.2249e+05,-1.1398e+05,-1.0008e+05,-94339,-89221,-84632,-76746,-73333,-70213,-67348,-64711,-60014,-57915,-55958,-54131,-50815,-49307,-47886,-46546,-45280,-42945,-41867,-40842,-39867,-38052,-37206,-36397,-35623,-34882,-33490,-32835,-32206,-31601,-30458,-29918,-29396,-28893,-28407,-27484,-27044,-26619,-26208,-25422,-25047,-24684,-24331,-23988,-23331,-23016,-22709,-22411,-22121,-21564,-21295,-21034,-20779,-20288,-20051,-19820,-19595,-19374,-18948,-18742,-18541,-18344,-17963,-17779,-17598,-17422,-17248,-16913,-16750,-16590,-16433,-16129,-15982,-15837,-15695,-15555,-15283,-15151,-15021,-14894,-14646,-14525,-14406,-14289,-14174,-13950,-13841,-13733,-13627,-13421,-13320,-13221,-13123,-13027,-12839,-12747,-12656,-12567,-12393,-12307,-12223,-12140,-12059,-11899,-11820,-11743,-11667,-11517,-11444,-11372,-11301,-11231,-11093,-11025,-10958,-10893,-10763,-10700,-10637,-10576,-10514,-10395,-10336,-10277,-10220,-10107,-10052,-9997,-9943,-9889,-9784,-9732,-9681,-9630,-9580,-9482,-9433,-9385,-9338,-9245,-9199,-9154,-9109,-9064,-8977,-8934,-8891,-8849,-8766,-8725,-8685,-8645,-8605,-8527,-8488,-8450,-8412,-8338,-8301,-8265,-8229,-8193,-8123,-8088,-8054,-8020,-7953,-7920,-7887,-7855,-7822,-7759,-7727,-7696,-7665,-7605,-7575,-7545,-7515,-7486,-7428,-7400,-7372,-7344,-7288,-7261,-7234,-7207,-7180,-7128,-7102,-7076,-7050,-7000,-6975,-6950,-6925,-6901,-6853,-6829,-6805,-6782,-6735,-6712,-6689,-6667,-6644,-6600,-6578,-6556,-6535,-6492,-6471,-6450,-6429,-6408,-6368,-6347,-6327,-6307,-6268,-6248,-6229,-6210,-6191,-6153,-6134,-6115,-6097,-6079,-6042,-6024,-6007,-5989,-5954,-5936,-5919,-5902,-5885,-5851,-5834,-5818,-5801,-5769,-5753,-5737,-5721,-5705,-5673,-5658,-5642,-5627,-5597,-5581,-5566,-5552,-5537,-5507,-5493,-5478,-5464,-5436,-5422,-5408,-5394,-5380,-5352,-5339,-5325,-5312,-5285,-5272,-5259,-5246,-5233,-5207,-5194,-5182,-5169,-5144,-5132,-5120,-5107,-5095,-5071,-5059,-5047,-5035,-5012,-5000,-4989,-4977,-4966,-4943,-4932,-4920,-4909,-4887,-4876,-4865,-4854,-4844,-4822,-4812,-4801,-4790,-4770,-4759,-4749,-4739,-4728,-4708,-4698,-4688,-4678,-4668,-4649,-4639,-4629,-4620,-4601,-4591,-4582,-4572,-4563,-4544,-4535,-4526,-4517,-4499,-4490,-4481,-4472,-4463,-4446,-4437,-4428,-4420,-4402,-4394,-4385,-4377,-4369,-4352,-4344,-4335,-4327,-4311,-4303,-4295,-4287,-4279,-4263,-4255,-4247,-4240,-4224,-4216,-4209,-4201,-4194,-4178,-4171,-4164,-4156,-4141,-4134,-4127,-4120,-4112,-4098,-4091,-4084,-4077,-4063,-4056,-4049,-4042,-4035,-4021,-4015,-4008,-4001,-3988,-3981,-3974,-3968,-3961,-3948,-3942,-3935,-3929,-3916,-3910,-3903,-3897,-3891,-3878,-3872,-3866,-3860,-3848,-3842,-3836,-3830,-3824,-3812,-3806,-3800,-3794,-3788,-3777,-3771,-3765,-3759,-3748,-3742,-3737,-3731,-3726,-3714,-3709,-3703,-3698,-3687,-3682,-3676,-3671,-3666,-3655,-3650,-3644,-3639,-3629,-3623,-3618,-3613,-3608,-3598,-3593,-3588,-3583,-3573,-3568,-3563,-3558,-3553,-3543,-3538,-3533,-3528,-3519,-3514,-3509,-3505,-3500,-3490,-3486,-3481,-3476,-3467,-3463,-3458,-3453,-3449,-3440,-3435,-3431,-3426,-3418,-3413,-3409,-3404,-3400,-3391,-3387,-3383,-3378,-3370,-3366,-3361,-3357,-3353,-3345,-3341,-3336,-3332,-3324,-3320,-3316,-3312,-3308,-3300,-3296,-3292,-3288,-3284,-3276,-3272,-3268,-3264,-3257,-3253,-3249,-3245,-3241,-3234,-3230,-3226,-3222,-3215,-3211,-3208,-3204,-3200,-3193,-3189,-3186,-3182,-3175,-3171,-3168,-3164,-3161,-3153,-3150,-3146,-3143,-3136,-3133,-3129,-3126,-3122,-3116,-3112,-3109,-3105,-3099,-3095,-3092,-3089,-3085,-3079,-3076,-3072,-3069,-3063,-3059,-3056,-3053,-3050,-3043,-3040,-3037,-3034,-3028,-3025,-3022,-3018,-3015,-3009,-3006,-3003,-3000,-2994,-2991,-2988,-2985,-2982,-2976,-2973,-2970,-2967,-2962,-2959,-2956,-2953,-2950,-2944,-2941,-2939,-2936,-2930,-2927,-2924,-2922,-2919,-2913,-2911,-2908,-2905,-2902,-2897,-2894,-2892,-2889,-2883,-2881,-2878,-2875,-2873,-2868,-2865,-2862,-2860,-2854,-2852,-2849,-2847,-2844,-2839,-2837,-2834,-2831,-2826,-2824,-2821,-2819,-2816,-2812,-2809,-2807,-2804,-2799,-2797,-2794,-2792,-2790,-2785,-2782,-2780,-2778,-2773,-2771,-2768,-2766,-2764,-2759,-2757,-2754,-2752,-2747,-2745,-2743,-2741,-2738,-2734,-2732,-2729,-2727,-2723,-2720,-2718,-2716,-2714,-2709,-2707,-2705,-2703,-2699,-2696,-2694,-2692,-2690,-2686,-2684,-2682,-2679,-2675,-2673,-2671,-2669,-2667,-2663,-2661,-2659,-2657,-2653,-2651,-2649,-2647,-2645,-2641,-2639,-2637,-2635,-2633,-2629,-2627,-2625,-2623,-2619,-2617,-2615,-2613,-2611,-2607,-2606,-2604,-2602,-2598,-2596,-2594,-2592,-2591,-2587,-2585,-2583,-2581,-2578,-2576,-2574,-2572,-2570,-2567,-2565,-2563,-2561,-2558,-2556,-2554,-2552,-2551,-2547,-2545,-2544,-2542,-2538,-2537,-2535,-2533,-2532,-2528,-2527,-2525,-2523,-2520,-2518,-2516,-2515,-2513,-2510,-2508,-2506,-2505,-2502,-2500,-2498,-2497,-2495,-2492,-2490,-2489,-2487,-2484,-2482,-2481,-2479,-2477,-2474,-2473,-2471,-2470,-2467,-2465,-2463,-2462,-2460,-2457,-2456,-2454,-2453,-2451,-2448,-2447,-2445,-2444,-2441,-2439,-2438,-2436,-2435,-2432,-2430,-2429,-2428,-2425,-2423,-2422,-2420,-2419,-2416,-2415,-2413,-2412,-2409,-2408,-2406,-2405,-2403,-2401,-2399,-2398,-2397,-2394,-2392,-2391,-2390,-2388,-2386,-2384,-2383,-2382,-2379,-2378,-2376,-2375,-2374,-2371,-2370,-2368,-2367,-2364,-2363,-2362,-2361,-2359,-2357,-2355,-2354,-2353,-2350,-2349,-2348,-2347,-2345,-2343,-2342,-2340,-2339,-2337,-2335,-2334,-2333,-2332,-2329,-2328,-2327,-2326,-2323,-2322,-2321,-2320,-2318,-2316,-2315,-2314,-2312,-2310,-2309,-2308,-2307,-2305,-2303,-2302,-2301,-2300,-2299,-2296,-2295,-2294,-2293,-2291,-2289,-2288,-2287,-2286,-2284,-2283,-2282,-2281,-2278,-2277,-2276,-2275,-2274,-2272,-2271,-2270,-2269,-2266,-2265,-2264,-2263,-2262,-2260,-2259,-2258,-2257,-2255,-2254,-2253,-2252,-2251,-2249,-2248,-2247,-2245,-2243,-2242,-2241,-2240,-2239,-2237,-2236,-2235,-2234,-2232,-2231,-2230,-2229,-2228,-2226,-2225,-2224,-2224,-2222,-2221,-2220,-2219,-2218,-2216,-2215,-2214,-2213,-2211,-2210,-2209,-2208,-2207,-2205,-2204,-2204,-2203,-2201,-2200,-2199,-2198,-2197,-2195,-2194,-2193,-2193,-2192,-2190,-2189,-2188,-2187,-2185,-2184,-2184,-2183,-2182,-2180,-2179,-2178,-2177,-2176,-2175,-2174,-2173,-2172,-2171,-2170,-2169,-2168,-2166,-2165,-2165,-2164,-2163,-2161,-2160,-2160,-2159,-2157,-2156,-2155,-2155,-2154,-2152,-2151,-2151,-2150,-2148,-2147,-2147,-2146,-2145,-2143,-2143,-2142,-2141,-2139,-2139,-2138,-2137,-2136,-2135,-2134,-2133,-2132,-2131,-2130,-2129,-2129,-2128,-2126,-2125,-2125,-2124,-2122,-2122,-2121,-2120,-2119,-2118,-2117,-2117,-2116,-2114,-2114,-2113,-2112,-2111,-2110,-2109,-2109,-2108,-2106,-2106,-2105,-2104,-2104,-2102,-2101,-2101,-2100,-2099,-2098,-2097,-2097,-2096,-2094,-2094,-2093,-2092,-2092,-2090,-2090,-2089,-2088,-2087,-2086,-2086,-2085,-2084,-2083,-2082,-2082,-2081,-2080,-2079,-2078,-2078,-2077,-2076,-2075,-2074,-2074,-2073,-2072,-2071,-2071,-2070,-2069,-2068,-2067,-2067,-2066,-2065,-2064,-2064,-2063,-2062,-2061,-2061,-2060,-2059,-2058,-2058,-2057,-2056,-2055,-2055,-2054,-2053,-2052,-2052,-2051,-2050,-2050,-2049,-2048,-2047,-2047,-2046,-2045,-2044,-2044,-2043,-2042,-2042,-2041,-2040,-2039,-2039,-2038,-2038,-2037,-2036,-2035,-2035,-2034,-2034,-2033,-2032,-2031,-2031,-2030,-2029,-2029,-2028,-2028,-2027,-2026,-2025,-2025,-2024,-2023,-2023,-2022,-2022,-2021,-2020,-2020,-2019,-2018,-2018,-2017,-2016,-2016,-2015,-2014,-2014,-2013,-2012,-2012,-2011,-2011,-2010,-2009,-2009,-2008,-2008,-2007,-2006,-2006,-2005,-2005,-2004,-2003,-2003,-2002,-2001,-2001,-2000,-2000,-2000,-1999,-1998,-1998,-1997,-1996,-1996,-1995,-1995,-1994,-1993,-1993,-1992,-1992,-1991,-1991,-1990,-1990,-1989,-1988,-1988,-1987,-1987,-1986,-1986,-1985,-1985,-1984,-1983,-1983,-1982,-1982,-1981,-1981,-1980,-1980,-1979,-1978,-1978,-1978,-1977,-1977,-1976,-1975,-1975,-1975,-1974,-1973,-1973,-1973,-1972,-1971,-1971,-1970,-1970,-1969,-1969,-1968,-1968,-1968,-1967,-1966,-1966,-1965,-1965,-1964,-1964,-1963,-1963,-1962,-1962,-1961,-1961,-1960,-1960,-1960,-1959,-1959,-1958,-1958,-1957,-1957,-1956,-1956,-1955,-1955,-1955,-1954,-1953,-1953,-1953,-1952,-1951,-1951,-1951,-1950,-1950,-1949,-1949,-1949,-1948,-1947,-1947,-1947,-1946,-1946,-1945,-1945,-1945,-1944,-1943,-1943,-1943,-1942,-1942,-1941,-1941,-1941,-1940,-1940,-1939,-1939,-1939,-1938,-1938,-1937,-1937,-1937,-1936,-1936,-1935,-1935,-1934,-1934,-1934,-1933,-1933,-1932,-1932,-1932,-1931,-1931,-1930,-1930,-1930,-1929,-1929,-1928,-1928,-1928,-1927,-1927,-1926,-1926,-1926,-1925,-1925,-1925,-1924,-1924,-1923,-1923,-1923,-1922,-1922,-1922,-1921,-1921,-1920,-1920,-1920,-1919,-1919,-1919,-1918,-1918,-1918,-1917,-1917,-1917,-1916,-1916,-1915,-1915,-1915,-1915,-1914,-1914,-1913,-1913,-1913,-1912,-1912,-1912,-1911,-1911,-1911,-1910,-1910,-1910,-1909,-1909,-1909,-1908,-1908,-1908,-1907,-1907,-1907,-1906,-1906,-1906,-1905,-1905,-1905,-1904,-1904,-1904,-1903,-1903,-1903,-1903,-1902,-1902,-1902,-1901,-1901,-1901,-1900,-1900,-1900,-1900,-1899,-1899,-1899,-1898,-1898,-1898,-1897,-1897,-1897,-1896,-1896,-1896,-1896,-1895,-1895,-1895,-1895,-1894,-1894,-1894,-1893,-1893,-1893,-1893,-1892,-1892,-1892,-1891,-1891,-1891,-1891,-1890,-1890,-1890,-1890,-1889,-1889,-1889,-1888,-1888,-1888,-1888,-1887,-1887,-1887,-1887,-1886,-1886,-1886,-1886,-1885,-1885,-1885,-1885,-1884,-1884,-1884,-1884,-1883,-1883,-1883,-1883,-1882,-1882,-1882,-1882,-1881,-1881,-1881,-1881,-1880,-1880,-1880,-1880,-1879,-1879,-1879,-1879,-1879,-1878,-1878,-1878,-1878,-1877,-1877,-1877,-1877,-1876,-1876,-1876,-1876,-1876,-1875,-1875,-1875,-1875,-1875,-1874,-1874,-1874,-1874,-1873,-1873,-1873,-1873,-1873,-1872,-1872,-1872,-1872,-1872,-1871,-1871,-1871,-1871,-1871,-1870,-1870,-1870,-1870,-1870,-1869,-1869,-1869,-1869,-1869,-1868,-1868,-1868,-1868,-1868,-1867,-1867,-1867,-1867,-1867,-1866,-1866,-1866,-1866,-1866,-1866,-1865,-1865,-1865,-1865,-1865,-1865,-1864,-1864,-1864,-1864,-1864,-1863,-1863,-1863,-1863,-1863,-1863,-1862,-1862,-1862,-1862,-1862,-1862,-1861,-1861,-1861,-1861,-1861,-1861,-1861,-1860,-1860,-1860,-1860,-1860,-1859,-1859,-1859,-1859,-1859,-1859,-1859,-1858,-1858,-1858,-1858,-1858,-1858,-1858,-1857,-1857,-1857,-1857,-1857,-1857,-1857,-1856,-1856,-1856,-1856,-1856,-1856,-1856,-1855,-1855,-1855,-1855,-1855,-1855,-1855,-1854,-1854,-1854,-1854,-1854,-1854,-1854,-1854,-1853,-1853,-1853,-1853,-1853,-1853,-1853,-1853,-1852,-1852,-1852,-1852,-1852,-1852,-1852,-1852,-1851,-1851,-1851,-1851,-1851,-1851,-1851,-1851,-1851,-1850,-1850,-1850,-1850,-1850,-1850,-1850,-1850,-1850,-1849,-1849,-1849,-1849,-1849,-1849,-1849,-1849,-1849,-1849,-1848,-1848,-1848,-1848,-1848,-1848,-1848,-1848,-1848,-1848,-1848,-1847,-1847,-1847,-1847,-1847,-1847,-1847,-1847,-1847,-1847,-1846,-1846,-1846,-1846,-1846,-1846,-1846,-1846,-1846,-1846,-1846,-1846,-1846,-1845,-1845,-1845,-1845,-1845,-1845,-1845,-1845,-1845,-1845,-1845,-1845,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1844,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1843,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1842,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1841,-1840,-1840,-1840,-1840,-1840,-1840,-1840,-1840,-1840,-1840};

#endif /* __V8LAMBDA_H */