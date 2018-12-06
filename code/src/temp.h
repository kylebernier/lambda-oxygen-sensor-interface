/**
 * @file temp.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 November 07
 *
 * @brief Provides lookup table for temperature values in Celcius
 * 
 * Table was generated based on the resistance to temperature equations in CJ125 manual.
 * The temperatures are index to directly correlate to the resistance that is read from 
 * the CJ125.
 *
 */

#ifndef __TEMP_H
#define __TEMP_H

/** @brief Lookup array for temperature data */
int temp_Lookup[] = {285,281,276,266,261,256,251,241,235,230,224,218,207,201,195,189,176,169,162,156,149,134,127,119,112,96,87,79,70,61,43,34,24,14,-6,-17,-28,-39,-51,-75,-88,-100,-114,-141,-156,-171,-186,-202,-235,-253,-271,-290,-309,-350,-372,-394,-417,-467,-493,-520,-549,-579,-642,-676,-712,-750,-831,-875,-921,-970,-1022,-1135,-1198,-1264,-1335,-1494,-1582,-1678,-1781,-1894,-2153,-2302,-2467,-2651,-3090,-3355,-3659,-4012,-4426,-5515,-6252,-7185,-8406,-12476,-16258,-23073,-39009,-1.1944e+05,40166,24430,17670,13911,9858,8642,7711,6976,6381,5476,5124,4820,4555,4117,3933,3768,3619,3483,3247,3144,3048,2960,2801,2730,2663,2601,2542,2435,2386,2340,2296,2214,2176,2140,2106,2073,2012,1983,1955,1929,1904,1855,1833,1811,1790,1750,1731,1712,1694,1677,1644,1628,1613,1598,1570,1556,1543,1530,1517,1493,1481,1470,1459,1437,1427,1416,1406,1397,1378,1369,1360,1351,1333,1325,1317,1309,1301,1285,1278,1271,1263,1249,1242,1235,1228,1222,1209,1202,1196,1189,1177,1171,1165,1159,1153,1142,1136,1130,1125,1114,1108,1103,1097,1092,1081,1076,1071,1066,1055,1050,1045,1040,1035,1025,1019,1014,1009,999,994,989,984,979,969,963,958,953,943,937,932,927,922,911,905,900,894,888,877,871,865,859,847,841,834,828,821,808,801,793,786,771,763,755,747,739,721,712,703,693,673,662,651,640,628,602,589,575,560,529,512,494,475,455,411,387,362,334,274,240,203,163,119,17,-42,-107,-181,-361,-472,-601,-754,-938,-1448,-1815,-2310,-3012,-5942,-9910,-24385,79340,16423,6924,5530,4667,4081,3333,3080,2877,2709,2569,2347,2257,2179,2109,1992,1941,1896,1854,1816,1749,1719,1691,1665,1641,1597,1577,1558,1540,1508,1492,1478,1464,1451,1427,1416,1405,1394,1375,1365,1356,1348,1339,1324,1316,1309,1302,1289,1282,1276,1270,1264,1253,1248,1242,1237,1228,1223,1218,1214,1209,1201,1197,1193,1189,1181,1178,1174,1171,1167,1161,1157,1154,1151,1145,1142,1139,1136,1133,1128,1125,1123,1120,1115,1112,1110,1108,1105,1101,1098,1096,1094,1090,1088,1086,1084,1082,1078,1076,1074,1072,1068,1066,1065,1063,1061,1058,1056,1054,1053,1049,1048,1046,1045,1043,1040,1038,1037,1035,1034,1031,1030,1028,1027,1024,1023,1022,1020,1019,1016,1015,1014,1013,1010,1009,1008,1006,1005,1003,1002,1001,1000,997,996,995,994,993,991,990,989,988,986,985,984,983,982,980,979,978,977,975,974,973,972,971,969,968,967,967,965,964,963,962,961,960,959,958,957,955,955,954,953,952,951,950,949,948,947,946,945,945,944,942,942,941,940,939,938,937,937,936,934,934,933,932,931,930,930,929,928,927,926,926,925,924,923,922,922,921,920,919,919,918,917,916,916,915,914,913,913,912,912,911,910,909,909,908,907,906,906,905,905,904,903,903,902,901,900,900,899,899,898,897,897,896,895,895,894,894,893,892,892,891,891,890,889,889,888,888,887,886,886,885,884,884,883,883,882,882,881,881,880,879,879,878,878,877,877,876,876,875,874,874,874,873,873,872,871,871,871,870,869,869,868,868,867,867,866,866,866,865,864,864,864,863,862,862,862,861,860,860,860,859,859,858,858,857,857,856,856,856,855,854,854,854,853,853,852,852,851,851,850,850,850,849,849,848,848,848,847,846,846,846,845,845,844,844,844,843,843,842,842,842,841,841,840,840,840,839,839,838,838,838,837,837,836,836,836,835,835,835,834,834,833,833,833,832,832,831,831,831,830,830,830,829,829,828,828,828,828,827,827,826,826,826,825,825,825,824,824,823,823,823,823,822,822,821,821,821,820,820,820,819,819,819,818,818,818,817,817,817,816,816,816,815,815,815,814,814,814,813,813,813,812,812,812,811,811,811,811,810,810,810,809,809,809,808,808,808,807,807,807,807,806,806,806,805,805,805,804,804,804,803,803,803,803,802,802,802,801,801,801,800,800,800,800,799,799,799,799,798,798,798,797,797,797,796,796,796,796,795,795,795,795,794,794,794,793,793,793,793,792,792,792,791,791,791,791,790,790,790,790,789,789,789,789,788,788,788,788,787,787,787,787,786,786,786,785,785,785,785,784,784,784,784,783,783,783,783,782,782,782,782,782,781,781,781,781,780,780,780,780,779,779,779,779,778,778,778,778,777,777,777,777,776,776,776,776,775,775,775,775,774,774,774,774,773,773,773,773,773,772,772,772,772,771,771,771,771,770,770,770,770,770,769,769,769,769,768,768,768,768,768,767,767,767,767,766,766,766,766,766,765,765,765,765,765,764,764,764,764,763,763,763,763,763,762,762,762,762,762,761,761,761,761,761,760,760,760,760,760,759,759,759,759,759,758,758,758,758,758,757,757,757,757,757,756,756,756,756,756,755,755,755,755,755,754,754,754,754,754,753,753,753,753,753,752,752,752,752,752,751,751,751,751,751,751,750,750,750,750,750,749,749,749,749,749,749,748,748,748,748,747,747,747,747,747,747,746,746,746,746,746,745,745,745,745,745,745,744,744,744,744,744,744,743,743,743,743,743,742,742,742,742,742,742,741,741,741,741,741,741,740,740,740,740,740,740,739,739,739,739,739,738,738,738,738,738,738,737,737,737,737,737,737,737,736,736,736,736,736,735,735,735,735,735,735,734,734,734,734,734,734,734,733,733,733,733,733,732,732,732,732,732,732,732,731,731,731,731,731,731,730,730,730,730,730,730,729,729,729,729,729,729,729,728,728,728,728,728,728,727,727,727,727,727,727,727,726,726,726,726,726,726,725,725,725,725,725,725,725,724,724,724,724,724,724,723,723,723,723,723,723,723,722,722,722,722,722,722,722,721,721,721,721,721,721,721,720,720,720,720,720,720,720,719,719,719,719,719,719,719,718,718,718,718,718,718,718,717,717,717,717,717,717,717,717,716,716,716,716,716,716,716,715,715,715,715,715,715,714,714,714,714,714,714,714,714,714,713,713,713,713,713,713,713,712,712,712,712,712,712,712,711,711,711,711,711,711,711,711,710,710,710,710,710,710,710,709,709,709,709,709,709,709,709,708,708,708,708,708,708,708,708,707,707,707,707,707,707,707,707,706,706,706,706,706,706,706,706,705,705,705,705,705,705,705,705,704,704,704,704,704,704,704,704,703,703,703,703,703,703,703,703,703,702,702,702,702,702,702,702,702,701,701,701,701,701,701,701,701,700,700,700,700,700,700,700,700,699,699,699,699,699,699,699,699,699,698,698,698,698,698,698,698,698,697,697,697,697,697,697,697,697,697,696,696,696,696,696,696,696,696,696,695,695,695,695,695,695,695,695,695,694,694,694,694,694,694,694,694,694,693,693,693,693,693,693,693,693,693,692,692,692,692,692,692,692,692,692,691,691,691,691,691,691,691,691,691,691,690,690,690,690,690,690,690,690,690,689,689,689,689,689,689,689,689,689,688,688,688,688,688,688,688,688,688,688,687,687,687,687,687,687,687,687,687,687,686,686,686,686,686,686,686,686,686,686,685,685,685,685,685,685,685,685,685,685,684,684,684,684,684,684,684,684,684,683,683,683,683,683,683,683,683,683,683,683,682,682,682,682,682,682,682,682,682,682,681,681,681,681,681,681,681,681,681,681,681,680,680,680,680,680,680,680,680,680,680,679,679,679,679,679,679,679,679,679,679,679,678,678,678,678,678,678,678,678,678,678,678,677,677,677,677,677,677,677,677,677,677,676,676,676,676,676,676,676,676,676,676,676,675,675,675,675,675,675,675,675,675,675,675,674,674,674,674,674,674,674,674,674,674,674,674,673,673,673,673,673,673,673,673,673,673,673,672,672,672,672,672,672,672,672,672,672,672,672,671,671,671,671,671,671,671,671,671,671,671,670,670,670,670,670,670,670,670,670,670,670,670,669,669,669,669,669,669,669,669,669,669,669,669,668,668,668,668,668,668,668,668,668,668,668,667,667,667,667,667,667,667,667,667,667,667,667,667,666,666,666,666,666,666,666,666,666,666,666,666,665,665,665,665,665,665,665,665,665,665,665,665,665,664,664,664,664,664,664,664,664,664,664,664,664,663,663,663,663,663,663,663,663,663,663,663,663,663,662,662,662,662,662,662,662,662,662,662,662,662,662,662,661,661,661,661,661,661,661,661,661,661,661,661,661,660,660,660,660,660,660,660,660,660,660,660,660,660,659,659,659,659,659,659,659,659,659,659,659,659,659,658,658,658,658,658,658,658,658,658,658,658,658,658,658,657,657,657,657,657,657,657,657,657,657,657,657,657,657,656,656,656,656,656,656,656,656,656,656,656,656,656,656,655,655,655,655,655,655,655,655,655,655,655,655,655,655,654,654,654,654,654,654,654,654,654,654,654,654,654,654,653,653,653,653,653,653,653,653,653,653,653,653,653,653,653,652,652,652,652,652,652,652,652,652,652,652,652,652,652,652,651,651,651,651,651,651,651,651,651,651,651,651,651,651,651,650,650,650,650,650,650,650,650,650,650,650,650,650,650,650,649,649,649,649,649,649,649,649,649,649,649,649,649,649,649,649,648,648,648,648,648,648,648,648,648,648,648,648,648,648,648,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,646,646,646,646,646,646,646,646,646,646,646,646,646,646,646,645,645,645,645,645,645,645,645,645,645,645,645,645,645,645,645,645,644,644,644,644,644,644,644,644,644,644,644,644,644,644,644,644,644,643,643,643,643,643,643,643,643,643,643,643,643,643,643,643,643,642,642,642,642,642,642,642,642,642,642,642,642,642,642,642,642,642,641,641,641,641,641,641,641,641,641,641,641,641,641,641,641,641,641,641,640,640,640,640,640,640,640,640,640,640,640,640,640,640,640,640,640,640,639,639,639,639,639,639,639,639,639,639,639,639,639,639,639,639,639,639,638,638,638,638,638,638,638,638,638,638,638,638,638,638,638,638,638,638,637,637,637,637,637,637,637,637,637,637,637,637,637,637,637,637,637,637,636,636,636,636,636,636,636,636,636,636,636,636,636,636,636,636,636,636,636,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,619,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,599,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,598,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,597,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,596,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,595,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,594,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,593,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,592,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,591,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,589,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,588,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,587,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586,586}; 

#endif /* __TEMP_H */
