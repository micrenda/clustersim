/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"

unsigned int color_map_acid[500];
void init_color_map()
{
    color_map_acid[0] = 0xf4d4a5;
    color_map_acid[1] = 0xfcd88a;
    color_map_acid[2] = 0xb09ec8;
    color_map_acid[3] = 0x9eaac4;
    color_map_acid[4] = 0xfdce88;
    color_map_acid[5] = 0xc988aa;
    color_map_acid[6] = 0xd0ecbc;
    color_map_acid[7] = 0xbeb0d3;
    color_map_acid[8] = 0xeee0bb;
    color_map_acid[9] = 0x91a9cb;
    color_map_acid[10] = 0xf3d7b2;
    color_map_acid[11] = 0xbbd8d3;
    color_map_acid[12] = 0xb4caf3;
    color_map_acid[13] = 0xfccda3;
    color_map_acid[14] = 0xedd098;
    color_map_acid[15] = 0xa5bedc;
    color_map_acid[16] = 0xcb86d7;
    color_map_acid[17] = 0x8391c0;
    color_map_acid[18] = 0xa5b2d4;
    color_map_acid[19] = 0xedb0b5;
    color_map_acid[20] = 0xcfecc0;
    color_map_acid[21] = 0xcfe5bf;
    color_map_acid[22] = 0xc7bcb6;
    color_map_acid[23] = 0x8fb0d1;
    color_map_acid[24] = 0xbce2cb;
    color_map_acid[25] = 0xe5bead;
    color_map_acid[26] = 0xa9eae2;
    color_map_acid[27] = 0x9aa6bc;
    color_map_acid[28] = 0xf0d2b0;
    color_map_acid[29] = 0x9a8ec0;
    color_map_acid[30] = 0xe1cc63;
    color_map_acid[31] = 0xfdcc94;
    color_map_acid[32] = 0x7898c7;
    color_map_acid[33] = 0xf9ce99;
    color_map_acid[34] = 0xe8d998;
    color_map_acid[35] = 0x9faac0;
    color_map_acid[36] = 0xd3e1c0;
    color_map_acid[37] = 0x74dcff;
    color_map_acid[38] = 0x8a95c3;
    color_map_acid[39] = 0xf1d3b7;
    color_map_acid[40] = 0x9ba7d1;
    color_map_acid[41] = 0xbd8ed4;
    color_map_acid[42] = 0xd7e4b9;
    color_map_acid[43] = 0xe4b184;
    color_map_acid[44] = 0xc2a5b7;
    color_map_acid[45] = 0xc6e2b2;
    color_map_acid[46] = 0xf1e088;
    color_map_acid[47] = 0xa7dabb;
    color_map_acid[48] = 0x949fbd;
    color_map_acid[49] = 0x949fcc;
    color_map_acid[50] = 0xa38fc2;
    color_map_acid[51] = 0x8590be;
    color_map_acid[52] = 0xefe2ae;
    color_map_acid[53] = 0xa3aedb;
    color_map_acid[54] = 0xc9dfb0;
    color_map_acid[55] = 0xcdeabe;
    color_map_acid[56] = 0xebdfb7;
    color_map_acid[57] = 0xd8b8b9;
    color_map_acid[58] = 0xb2dedd;
    color_map_acid[59] = 0xab86d3;
    color_map_acid[60] = 0xf2b3a2;
    color_map_acid[61] = 0xe3bea3;
    color_map_acid[62] = 0xc1b1ce;
    color_map_acid[63] = 0xabcacc;
    color_map_acid[64] = 0xbeadd9;
    color_map_acid[65] = 0xbeafcc;
    color_map_acid[66] = 0xc1a8ab;
    color_map_acid[67] = 0xbea3d6;
    color_map_acid[68] = 0xabe7df;
    color_map_acid[69] = 0xd0a1b3;
    color_map_acid[70] = 0xf2ce6e;
    color_map_acid[71] = 0xafa3d5;
    color_map_acid[72] = 0x98a5d1;
    color_map_acid[73] = 0xd0bade;
    color_map_acid[74] = 0xd9c6a6;
    color_map_acid[75] = 0xa28bb9;
    color_map_acid[76] = 0xd9cd99;
    color_map_acid[77] = 0xb3a4cf;
    color_map_acid[78] = 0xffcc93;
    color_map_acid[79] = 0xffc983;
    color_map_acid[80] = 0xffc1c2;
    color_map_acid[81] = 0xffdc84;
    color_map_acid[82] = 0xffd799;
    color_map_acid[83] = 0xeaadb2;
    color_map_acid[84] = 0xeee3ab;
    color_map_acid[85] = 0xffd294;
    color_map_acid[86] = 0x95a7bf;
    color_map_acid[87] = 0xc8b3dc;
    color_map_acid[88] = 0xffb9a3;
    color_map_acid[89] = 0xa695c2;
    color_map_acid[90] = 0xffb08f;
    color_map_acid[91] = 0xffb58e;
    color_map_acid[92] = 0xfbd584;
    color_map_acid[93] = 0x9d73d5;
    color_map_acid[94] = 0xddf1c0;
    color_map_acid[95] = 0xff95af;
    color_map_acid[96] = 0xc4aaab;
    color_map_acid[97] = 0xc0ebd0;
    color_map_acid[98] = 0xc4a7d7;
    color_map_acid[99] = 0xaa8dcd;
    color_map_acid[100] = 0xf7d888;
    color_map_acid[101] = 0xbb9dd9;
    color_map_acid[102] = 0xc4efde;
    color_map_acid[103] = 0xaac7cf;
    color_map_acid[104] = 0xd5e9a2;
    color_map_acid[105] = 0xd5ecb4;
    color_map_acid[106] = 0xf3c361;
    color_map_acid[107] = 0xd5e0b6;
    color_map_acid[108] = 0x769ec2;
    color_map_acid[109] = 0xd5e6c6;
    color_map_acid[110] = 0xa1b3c9;
    color_map_acid[111] = 0xe9a5b2;
    color_map_acid[112] = 0xa1b4d5;
    color_map_acid[113] = 0xfcdda6;
    color_map_acid[114] = 0x8799bd;
    color_map_acid[115] = 0xfcd2ac;
    color_map_acid[116] = 0x96a7c5;
    color_map_acid[117] = 0xede2b4;
    color_map_acid[118] = 0x8794be;
    color_map_acid[119] = 0xede17f;
    color_map_acid[120] = 0xfcd091;
    color_map_acid[121] = 0xede0ac;
    color_map_acid[122] = 0xa1b9bd;
    color_map_acid[123] = 0x96a3b6;
    color_map_acid[124] = 0xfcd697;
    color_map_acid[125] = 0xb093d6;
    color_map_acid[126] = 0xfcca81;
    color_map_acid[127] = 0xb092da;
    color_map_acid[128] = 0x799cbc;
    color_map_acid[129] = 0x83c1d0;
    color_map_acid[130] = 0xdae5ad;
    color_map_acid[131] = 0xdeafc3;
    color_map_acid[132] = 0xe9bed2;
    color_map_acid[133] = 0xfcc35c;
    color_map_acid[134] = 0xa5e4db;
    color_map_acid[135] = 0xdaeab9;
    color_map_acid[136] = 0x96b2c8;
    color_map_acid[137] = 0xe9b995;
    color_map_acid[138] = 0xe9b979;
    color_map_acid[139] = 0xa190bd;
    color_map_acid[140] = 0xb0a1ca;
    color_map_acid[141] = 0xb0a5cf;
    color_map_acid[142] = 0xedcc9f;
    color_map_acid[143] = 0xa5d5d9;
    color_map_acid[144] = 0xcbecb7;
    color_map_acid[145] = 0xedd9b6;
    color_map_acid[146] = 0x87aecd;
    color_map_acid[147] = 0x9e0cd;
    color_map_acid[148] = 0xa186d7;
    color_map_acid[149] = 0xe99fae;
    color_map_acid[150] = 0xcfb3c2;
    color_map_acid[151] = 0xe99ab7;
    color_map_acid[152] = 0xa5bbd3;
    color_map_acid[153] = 0xf8d176;
    color_map_acid[154] = 0xb85ca5;
    color_map_acid[155] = 0xf8d09d;
    color_map_acid[156] = 0x8395bd;
    color_map_acid[157] = 0x6cb7d6;
    color_map_acid[158] = 0x8393c4;
    color_map_acid[159] = 0x8393cf;
    color_map_acid[160] = 0xb0c3a5;
    color_map_acid[161] = 0x92a0cd;
    color_map_acid[162] = 0xdab4cb;
    color_map_acid[163] = 0x285ed;
    color_map_acid[164] = 0xb483c4;
    color_map_acid[165] = 0xf8df8d;
    color_map_acid[166] = 0xf8dcac;
    color_map_acid[167] = 0x7d95c1;
    color_map_acid[168] = 0xcfdfae;
    color_map_acid[169] = 0xf8c08d;
    color_map_acid[170] = 0xb499cc;
    color_map_acid[171] = 0xb493c8;
    color_map_acid[172] = 0xdaabb1;
    color_map_acid[173] = 0x838ee8;
    color_map_acid[174] = 0xf8c99b;
    color_map_acid[175] = 0xa973c7;
    color_map_acid[176] = 0xf8ce86;
    color_map_acid[177] = 0xf8cf9b;
    color_map_acid[178] = 0x9286c8;
    color_map_acid[179] = 0xa59ab8;
    color_map_acid[180] = 0x9287b2;
    color_map_acid[181] = 0xda97b8;
    color_map_acid[182] = 0xa590cb;
    color_map_acid[183] = 0xcfe4b9;
    color_map_acid[184] = 0xb4a1e1;
    color_map_acid[185] = 0xcba8e2;
    color_map_acid[186] = 0xe9cbb3;
    color_map_acid[187] = 0xcbaa9b;
    color_map_acid[188] = 0xb4a3d7;
    color_map_acid[189] = 0xe9ca9c;
    color_map_acid[190] = 0xe9cd69;
    color_map_acid[191] = 0xb4a5d0;
    color_map_acid[192] = 0xcbacbe;
    color_map_acid[193] = 0xe9cca2;
    color_map_acid[194] = 0xa596bf;
    color_map_acid[195] = 0xa597ca;
    color_map_acid[196] = 0xe9cebd;
    color_map_acid[197] = 0x8f6fbb;
    color_map_acid[198] = 0xed9f92;
    color_map_acid[199] = 0xa95bc0;
    color_map_acid[200] = 0x83adc5;
    color_map_acid[201] = 0x929dbb;
    color_map_acid[202] = 0xda89cb;
    color_map_acid[203] = 0xe9daa1;
    color_map_acid[204] = 0xcbbbae;
    color_map_acid[205] = 0xe9dd89;
    color_map_acid[206] = 0xe9debe;
    color_map_acid[207] = 0xd2e7e2;
    color_map_acid[208] = 0xf085b9;
    color_map_acid[209] = 0xf4c9c3;
    color_map_acid[210] = 0xf4cf9b;
    color_map_acid[211] = 0xd2e3af;
    color_map_acid[212] = 0xd2e3c3;
    color_map_acid[213] = 0xe1b0b6;
    color_map_acid[214] = 0xb895cb;
    color_map_acid[215] = 0xb895a9;
    color_map_acid[216] = 0xd2e19c;
    color_map_acid[217] = 0x9eb6c0;
    color_map_acid[218] = 0xd6a1a7;
    color_map_acid[219] = 0xd2eab6;
    color_map_acid[220] = 0xb89ece;
    color_map_acid[221] = 0xf4c5bf;
    color_map_acid[222] = 0x9eb0d6;
    color_map_acid[223] = 0xd6bbb0;
    color_map_acid[224] = 0xf4dfa6;
    color_map_acid[225] = 0xb887c8;
    color_map_acid[226] = 0xf4dc9c;
    color_map_acid[227] = 0xf4d3aa;
    color_map_acid[228] = 0xa9b9d2;
    color_map_acid[229] = 0xa9bed1;
    color_map_acid[230] = 0xa9bcca;
    color_map_acid[231] = 0xf4d497;
    color_map_acid[232] = 0xd2c5a5;
    color_map_acid[233] = 0xd68baa;
    color_map_acid[234] = 0x8fa9ce;
    color_map_acid[235] = 0xa985b5;
    color_map_acid[236] = 0xf0a192;
    color_map_acid[237] = 0x9ad6e1;
    color_map_acid[238] = 0xe5d0bd;
    color_map_acid[239] = 0xe5d79a;
    color_map_acid[240] = 0xc7abb9;
    color_map_acid[241] = 0xa540cc;
    color_map_acid[242] = 0xadd9dc;
    color_map_acid[243] = 0xb471db;
    color_map_acid[244] = 0xb8a6cc;
    color_map_acid[245] = 0xd2dd98;
    color_map_acid[246] = 0x9e86b8;
    color_map_acid[247] = 0xbce7d6;
    color_map_acid[248] = 0xe5c2af;
    color_map_acid[249] = 0x9e80d6;
    color_map_acid[250] = 0xe5c5ac;
    color_map_acid[251] = 0xc7a49e;
    color_map_acid[252] = 0xbce3ce;
    color_map_acid[253] = 0xc7dea6;
    color_map_acid[254] = 0xd6eee1;
    color_map_acid[255] = 0x9ab7bd;
    color_map_acid[256] = 0xa17ebe;
    color_map_acid[257] = 0xd6edb5;
    color_map_acid[258] = 0xd6edbf;
    color_map_acid[259] = 0xd2a69d;
    color_map_acid[260] = 0xf0c6a0;
    color_map_acid[261] = 0xd6e8aa;
    color_map_acid[262] = 0xde71b2;
    color_map_acid[263] = 0xe5b6c6;
    color_map_acid[264] = 0xd6e7b0;
    color_map_acid[265] = 0xd6e7b1;
    color_map_acid[266] = 0xd6e7ba;
    color_map_acid[267] = 0xd6e4a6;
    color_map_acid[268] = 0xd6e4b3;
    color_map_acid[269] = 0xd6e1b9;
    color_map_acid[270] = 0x8b97d1;
    color_map_acid[271] = 0x8fd8df;
    color_map_acid[272] = 0x8fd9e6;
    color_map_acid[273] = 0x8fdcec;
    color_map_acid[274] = 0xf0d9a5;
    color_map_acid[275] = 0xe1efce;
    color_map_acid[276] = 0xf0dfa9;
    color_map_acid[277] = 0xf0dea0;
    color_map_acid[278] = 0x9aa8c3;
    color_map_acid[279] = 0xd6f1e2;
    color_map_acid[280] = 0x9aa9e4;
    color_map_acid[281] = 0xad8bd7;
    color_map_acid[282] = 0x923cd;
    color_map_acid[283] = 0xa50bf;
    color_map_acid[284] = 0xa50b9;
    color_map_acid[285] = 0xbca9a2;
    color_map_acid[286] = 0xb8e5c8;
    color_map_acid[287] = 0xbcaa9e;
    color_map_acid[288] = 0xb8e6c9;
    color_map_acid[289] = 0xbcacd1;
    color_map_acid[290] = 0xbcacdd;
    color_map_acid[291] = 0xad9cc6;
    color_map_acid[292] = 0xad9cc9;
    color_map_acid[293] = 0xe1c4b6;
    color_map_acid[294] = 0xf4b8c2;
    color_map_acid[295] = 0xc3a7d8;
    color_map_acid[296] = 0xad9ebd;
    color_map_acid[297] = 0xbca0d0;
    color_map_acid[298] = 0xbca2ad;
    color_map_acid[299] = 0xbca2cf;
    color_map_acid[300] = 0xd29ab3;
    color_map_acid[301] = 0xad94bb;
    color_map_acid[302] = 0x9ec5ca;
    color_map_acid[303] = 0x9a8abb;
    color_map_acid[304] = 0xfdc9a1;
    color_map_acid[305] = 0xdbe6c4;
    color_map_acid[306] = 0xdbe6ae;
    color_map_acid[307] = 0xfdcb86;
    color_map_acid[308] = 0xe8b0dd;
    color_map_acid[309] = 0xfdcc80;
    color_map_acid[310] = 0xac70e2;
    color_map_acid[311] = 0xdfaec4;
    color_map_acid[312] = 0xfdc094;
    color_map_acid[313] = 0xdbedc3;
    color_map_acid[314] = 0xfdc179;
    color_map_acid[315] = 0xa0abcb;
    color_map_acid[316] = 0xfdc383;
    color_map_acid[317] = 0xdfa3bd;
    color_map_acid[318] = 0xb19ddc;
    color_map_acid[319] = 0xdbe8b2;
    color_map_acid[320] = 0xdbe8b3;
    color_map_acid[321] = 0xa4e1f3;
    color_map_acid[322] = 0xdbe8cc;
    color_map_acid[323] = 0xa0acc6;
    color_map_acid[324] = 0xa0acd4;
    color_map_acid[325] = 0xcadabd;
    color_map_acid[326] = 0xa0aed3;
    color_map_acid[327] = 0xfdd99d;
    color_map_acid[328] = 0x869cc1;
    color_map_acid[329] = 0xfdd88a;
    color_map_acid[330] = 0xfddab0;
    color_map_acid[331] = 0xb184a1;
    color_map_acid[332] = 0x9b7ca6;
    color_map_acid[333] = 0xfddfc7;
    color_map_acid[334] = 0xfdd1ac;
    color_map_acid[335] = 0xdfb1bc;
    color_map_acid[336] = 0x97a5cc;
    color_map_acid[337] = 0xfdd0a7;
    color_map_acid[338] = 0xece0b8;
    color_map_acid[339] = 0xece098;
    color_map_acid[340] = 0xfdd387;
    color_map_acid[341] = 0xfdd284;
    color_map_acid[342] = 0xdfb487;
    color_map_acid[343] = 0x97a2b6;
    color_map_acid[344] = 0xecdab2;
    color_map_acid[345] = 0xdbc7bc;
    color_map_acid[346] = 0xf9a781;
    color_map_acid[347] = 0xecdebb;
    color_map_acid[348] = 0xcebfbc;
    color_map_acid[349] = 0xdbc39f;
    color_map_acid[350] = 0x9f0d8;
    color_map_acid[351] = 0xa08bda;
    color_map_acid[352] = 0xf9ac90;
    color_map_acid[353] = 0xceb0b8;
    color_map_acid[354] = 0xecd1a4;
    color_map_acid[355] = 0xa4c2da;
    color_map_acid[356] = 0xf57ca7;
    color_map_acid[357] = 0xd350c4;
    color_map_acid[358] = 0xecd59f;
    color_map_acid[359] = 0xb1a2dd;
    color_map_acid[360] = 0xb5ecd9;
    color_map_acid[361] = 0xeccf8d;
    color_map_acid[362] = 0xa094c2;
    color_map_acid[363] = 0xa095bd;
    color_map_acid[364] = 0x8a6d9d;
    color_map_acid[365] = 0x86b2ef;
    color_map_acid[366] = 0x9782ba;
    color_map_acid[367] = 0x8a65ab;
    color_map_acid[368] = 0x7c97c4;
    color_map_acid[369] = 0xf9c174;
    color_map_acid[370] = 0xf9c385;
    color_map_acid[371] = 0x9f657e;
    color_map_acid[372] = 0xdba69e;
    color_map_acid[373] = 0xb593a1;
    color_map_acid[374] = 0xdbaca6;
    color_map_acid[375] = 0x7c9ab2;
    color_map_acid[376] = 0x93a7c2;
    color_map_acid[377] = 0xf9d58b;
    color_map_acid[378] = 0xf9d7b2;
    color_map_acid[379] = 0xf9d6ae;
    color_map_acid[380] = 0x93afc5;
    color_map_acid[381] = 0x8298bd;
    color_map_acid[382] = 0x86d4e1;
    color_map_acid[383] = 0x8299c2;
    color_map_acid[384] = 0xa4b7e1;
    color_map_acid[385] = 0xa48bcc;
    color_map_acid[386] = 0xfdacbd;
    color_map_acid[387] = 0xe8d787;
    color_map_acid[388] = 0xf9e7a5;
    color_map_acid[389] = 0xa48ee1;
    color_map_acid[390] = 0x82a0ba;
    color_map_acid[391] = 0xdfc9bc;
    color_map_acid[392] = 0xf170c0;
    color_map_acid[393] = 0xa484b6;
    color_map_acid[394] = 0xe8dda5;
    color_map_acid[395] = 0xfdbf90;
    color_map_acid[396] = 0xe8c3b3;
    color_map_acid[397] = 0xcaa3a6;
    color_map_acid[398] = 0xe8c271;
    color_map_acid[399] = 0xb97fcc;
    color_map_acid[400] = 0x9385c0;
    color_map_acid[401] = 0xe8c0c0;
    color_map_acid[402] = 0xceecba;
    color_map_acid[403] = 0xfdbac1;
    color_map_acid[404] = 0xcee5b9;
    color_map_acid[405] = 0xcee5b1;
    color_map_acid[406] = 0xcee5db;
    color_map_acid[407] = 0xdfd49c;
    color_map_acid[408] = 0x34bac5;
    color_map_acid[409] = 0xcaafb8;
    color_map_acid[410] = 0xb1ebf9;
    color_map_acid[411] = 0xfdb07a;
    color_map_acid[412] = 0x9facce;
    color_map_acid[413] = 0x9facbc;
    color_map_acid[414] = 0x9fadc7;
    color_map_acid[415] = 0x9faec5;
    color_map_acid[416] = 0x9fafd3;
    color_map_acid[417] = 0xbdcfdb;
    color_map_acid[418] = 0x8e9ac4;
    color_map_acid[419] = 0x9faabc;
    color_map_acid[420] = 0x8e9ab4;
    color_map_acid[421] = 0x9fabd3;
    color_map_acid[422] = 0xb988a5;
    color_map_acid[423] = 0xa8b8da;
    color_map_acid[424] = 0xf19f77;
    color_map_acid[425] = 0xf5d389;
    color_map_acid[426] = 0xe0a88f;
    color_map_acid[427] = 0xf5d487;
    color_map_acid[428] = 0xf184d3;
    color_map_acid[429] = 0xbdddac;
    color_map_acid[430] = 0xacecde;
    color_map_acid[431] = 0xb994e2;
    color_map_acid[432] = 0xf5cea7;
    color_map_acid[433] = 0xb997a7;
    color_map_acid[434] = 0xd3e3bc;
    color_map_acid[435] = 0xf5c08a;
    color_map_acid[436] = 0xc2ddb2;
    color_map_acid[437] = 0x7095a8;
    color_map_acid[438] = 0xe0bfd0;
    color_map_acid[439] = 0x7093bb;
    color_map_acid[440] = 0x9fb0ca;
    color_map_acid[441] = 0xc2db97;
    color_map_acid[442] = 0xc6aada;
    color_map_acid[443] = 0xa890f0;
    color_map_acid[444] = 0xc6a8e6;
    color_map_acid[445] = 0xf1b094;
    color_map_acid[446] = 0xbde6d6;
    color_map_acid[447] = 0xc2eed5;
    color_map_acid[448] = 0xb9abce;
    color_map_acid[449] = 0xb9a8df;
    color_map_acid[450] = 0xacd4d4;
    color_map_acid[451] = 0xa899dc;
    color_map_acid[452] = 0x9f82c4;
    color_map_acid[453] = 0x9bcfcd;
    color_map_acid[454] = 0xf1b988;
    color_map_acid[455] = 0xe4c5a8;
    color_map_acid[456] = 0x9718a7;
    color_map_acid[457] = 0xf5eabc;
    color_map_acid[458] = 0xc6baa0;
    color_map_acid[459] = 0xaccecd;
    color_map_acid[460] = 0xacccd9;
    color_map_acid[461] = 0x8ea9d4;
    color_map_acid[462] = 0xf5e08d;
    color_map_acid[463] = 0xc6b1dc;
    color_map_acid[464] = 0x9ba6ba;
    color_map_acid[465] = 0xf1d38a;
    color_map_acid[466] = 0xb9c7d0;
    color_map_acid[467] = 0xd3b5bf;
    color_map_acid[468] = 0xbd8cdd;
    color_map_acid[469] = 0xf1d991;
    color_map_acid[470] = 0x9ba8c8;
    color_map_acid[471] = 0x8a99c4;
    color_map_acid[472] = 0xb9cade;
    color_map_acid[473] = 0xf1deb4;
    color_map_acid[474] = 0xf1de8f;
    color_map_acid[475] = 0xf1de9a;
    color_map_acid[476] = 0xf1c073;
    color_map_acid[477] = 0x9bb4ca;
    color_map_acid[478] = 0x9bb6e5;
    color_map_acid[479] = 0x9bb0c5;
    color_map_acid[480] = 0x9bb3cf;
    color_map_acid[481] = 0xb9d2e6;
    color_map_acid[482] = 0xc297cf;
    color_map_acid[483] = 0xf1c795;
    color_map_acid[484] = 0xc299d3;
    color_map_acid[485] = 0xd7e6a3;
    color_map_acid[486] = 0xd7e7b8;
    color_map_acid[487] = 0xd7e7c2;
    color_map_acid[488] = 0xd3abc6;
    color_map_acid[489] = 0x9bb9d3;
    color_map_acid[490] = 0xd3adac;
    color_map_acid[491] = 0xbd94cc;
    color_map_acid[492] = 0x7c0d5;
    color_map_acid[493] = 0xf5bfb5;
    color_map_acid[494] = 0xe0c3c8;
    color_map_acid[495] = 0xbda8a3;
    color_map_acid[496] = 0xac9fd5;
    color_map_acid[497] = 0xd395c6;
    color_map_acid[498] = 0x9b8edd;
    color_map_acid[499] = 0x9b8fc1;
}



unsigned int get_color_acid(unsigned int i, unsigned int n)
{
    return color_map_acid[i % 500];
}

unsigned int get_color_grad_rgb(unsigned int i, unsigned int n, unsigned int colors_size, unsigned int* colors)
{
	unsigned int ranges = colors_size - 1;
	
	unsigned int start_rgb;
	unsigned int end_rgb;
	
	double i_r;
	double n_r;
	
	
	
	
	if (i <= 0)
	{
		start_rgb = colors[0];
		end_rgb   = colors[1];
		
		i_r = 0.d;
		n_r = 1.d * n / ranges;
	}
	else if (i >= n)
	{
		start_rgb   = colors[colors_size - 2];
		end_rgb   	= colors[colors_size - 1];
		
		i_r = 1.d * n / ranges - 1;
		n_r = 1.d * n / ranges;
	}
	else
	{
		unsigned int lower_index = floor(1.d * ranges * i / n);  
		start_rgb = colors[lower_index];
		end_rgb	  = colors[lower_index+1];
		n_r = 1.d * n / ranges;
		i_r = fmod(i, n_r);
	}

	 
	
    unsigned short start_red   = (start_rgb & 0xff0000) >> 16;
    unsigned short start_green = (start_rgb & 0x00ff00) >>  8;
    unsigned short start_blue  = (start_rgb & 0x0000ff) >>  0;

    unsigned short end_red     = (end_rgb & 0xff0000) >> 16;
    unsigned short end_green   = (end_rgb & 0x00ff00) >>  8;
    unsigned short end_blue    = (end_rgb & 0x0000ff) >>  0;

    unsigned short color_red   = start_red   + round(1.f * (end_red   - start_red  ) * i_r / n_r);
    unsigned short color_green = start_green + round(1.f * (end_green - start_green) * i_r / n_r);
    unsigned short color_blue =  start_blue  + round(1.f * (end_blue  - start_blue ) * i_r / n_r);

    return (color_red << 16) + (color_green << 8) + (color_blue << 0);
}
