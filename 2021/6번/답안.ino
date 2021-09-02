#pragma GCC optimize ("-O3")

typedef unsigned char   u8;
typedef unsigned short  u16;
//typedef unsigned int  u32;

// round: #128
#define NUM_ROUND   128 

// key_gen constant
#define CONST_VAL   0xab00cd00 

// rotation left
#define ROL(X) ((X<<1) | (X>>31)) 

// s_box: 4-bit x #16
u32 s_box[16] = {0x3, 0x9, 0x6, 0xf, 0xe, 0x5, 0xd, 0x4, 0xc, 0x7, 0xa, 0x2, 0xb, 0x1, 0x8, 0x0}; 

// key generation
void new_bs_keygen(u32* r_key, u32 m_key){
  r_key[0] = (m_key + 0) ^ 2868956416;
  r_key[1] = (m_key + 1) ^ 1442945537;
  r_key[2] = (m_key + 2) ^ 2885891074;
  r_key[3] = (m_key + 3) ^ 1476814853;
  r_key[4] = (m_key + 4) ^ 2953629706;
  r_key[5] = (m_key + 5) ^ 1612292117;
  r_key[6] = (m_key + 6) ^ 3224584234;
  r_key[7] = (m_key + 7) ^ 2154201173;
  r_key[8] = (m_key + 8) ^ 13435051;
  r_key[9] = (m_key + 9) ^ 26870102;
  r_key[10] = (m_key + 10) ^ 53740204;
  r_key[11] = (m_key + 11) ^ 107480408;
  r_key[12] = (m_key + 12) ^ 214960816;
  r_key[13] = (m_key + 13) ^ 429921632;
  r_key[14] = (m_key + 14) ^ 859843264;
  r_key[15] = (m_key + 15) ^ 1719686528;
  r_key[16] = (m_key + 16) ^ 3439373056;
  r_key[17] = (m_key + 17) ^ 2583778817;
  r_key[18] = (m_key + 18) ^ 872590339;
  r_key[19] = (m_key + 19) ^ 1745180678;
  r_key[20] = (m_key + 20) ^ 3490361356;
  r_key[21] = (m_key + 21) ^ 2685755417;
  r_key[22] = (m_key + 22) ^ 1076543539;
  r_key[23] = (m_key + 23) ^ 2153087078;
  r_key[24] = (m_key + 24) ^ 11206861;
  r_key[25] = (m_key + 25) ^ 22413722;
  r_key[26] = (m_key + 26) ^ 44827444;
  r_key[27] = (m_key + 27) ^ 89654888;
  r_key[28] = (m_key + 28) ^ 179309776;
  r_key[29] = (m_key + 29) ^ 358619552;
  r_key[30] = (m_key + 30) ^ 717239104;
  r_key[31] = (m_key + 31) ^ 1434478208;
  r_key[32] = (m_key + 32) ^ 2868956416;
  r_key[33] = (m_key + 33) ^ 1442945537;
  r_key[34] = (m_key + 34) ^ 2885891074;
  r_key[35] = (m_key + 35) ^ 1476814853;
  r_key[36] = (m_key + 36) ^ 2953629706;
  r_key[37] = (m_key + 37) ^ 1612292117;
  r_key[38] = (m_key + 38) ^ 3224584234;
  r_key[39] = (m_key + 39) ^ 2154201173;
  r_key[40] = (m_key + 40) ^ 13435051;
  r_key[41] = (m_key + 41) ^ 26870102;
  r_key[42] = (m_key + 42) ^ 53740204;
  r_key[43] = (m_key + 43) ^ 107480408;
  r_key[44] = (m_key + 44) ^ 214960816;
  r_key[45] = (m_key + 45) ^ 429921632;
  r_key[46] = (m_key + 46) ^ 859843264;
  r_key[47] = (m_key + 47) ^ 1719686528;
  r_key[48] = (m_key + 48) ^ 3439373056;
  r_key[49] = (m_key + 49) ^ 2583778817;
  r_key[50] = (m_key + 50) ^ 872590339;
  r_key[51] = (m_key + 51) ^ 1745180678;
  r_key[52] = (m_key + 52) ^ 3490361356;
  r_key[53] = (m_key + 53) ^ 2685755417;
  r_key[54] = (m_key + 54) ^ 1076543539;
  r_key[55] = (m_key + 55) ^ 2153087078;
  r_key[56] = (m_key + 56) ^ 11206861;
  r_key[57] = (m_key + 57) ^ 22413722;
  r_key[58] = (m_key + 58) ^ 44827444;
  r_key[59] = (m_key + 59) ^ 89654888;
  r_key[60] = (m_key + 60) ^ 179309776;
  r_key[61] = (m_key + 61) ^ 358619552;
  r_key[62] = (m_key + 62) ^ 717239104;
  r_key[63] = (m_key + 63) ^ 1434478208;
  r_key[64] = (m_key + 64) ^ 2868956416;
  r_key[65] = (m_key + 65) ^ 1442945537;
  r_key[66] = (m_key + 66) ^ 2885891074;
  r_key[67] = (m_key + 67) ^ 1476814853;
  r_key[68] = (m_key + 68) ^ 2953629706;
  r_key[69] = (m_key + 69) ^ 1612292117;
  r_key[70] = (m_key + 70) ^ 3224584234;
  r_key[71] = (m_key + 71) ^ 2154201173;
  r_key[72] = (m_key + 72) ^ 13435051;
  r_key[73] = (m_key + 73) ^ 26870102;
  r_key[74] = (m_key + 74) ^ 53740204;
  r_key[75] = (m_key + 75) ^ 107480408;
  r_key[76] = (m_key + 76) ^ 214960816;
  r_key[77] = (m_key + 77) ^ 429921632;
  r_key[78] = (m_key + 78) ^ 859843264;
  r_key[79] = (m_key + 79) ^ 1719686528;
  r_key[80] = (m_key + 80) ^ 3439373056;
  r_key[81] = (m_key + 81) ^ 2583778817;
  r_key[82] = (m_key + 82) ^ 872590339;
  r_key[83] = (m_key + 83) ^ 1745180678;
  r_key[84] = (m_key + 84) ^ 3490361356;
  r_key[85] = (m_key + 85) ^ 2685755417;
  r_key[86] = (m_key + 86) ^ 1076543539;
  r_key[87] = (m_key + 87) ^ 2153087078;
  r_key[88] = (m_key + 88) ^ 11206861;
  r_key[89] = (m_key + 89) ^ 22413722;
  r_key[90] = (m_key + 90) ^ 44827444;
  r_key[91] = (m_key + 91) ^ 89654888;
  r_key[92] = (m_key + 92) ^ 179309776;
  r_key[93] = (m_key + 93) ^ 358619552;
  r_key[94] = (m_key + 94) ^ 717239104;
  r_key[95] = (m_key + 95) ^ 1434478208;
  r_key[96] = (m_key + 96) ^ 2868956416;
  r_key[97] = (m_key + 97) ^ 1442945537;
  r_key[98] = (m_key + 98) ^ 2885891074;
  r_key[99] = (m_key + 99) ^ 1476814853;
  r_key[100] = (m_key + 100) ^ 2953629706;
  r_key[101] = (m_key + 101) ^ 1612292117;
  r_key[102] = (m_key + 102) ^ 3224584234;
  r_key[103] = (m_key + 103) ^ 2154201173;
  r_key[104] = (m_key + 104) ^ 13435051;
  r_key[105] = (m_key + 105) ^ 26870102;
  r_key[106] = (m_key + 106) ^ 53740204;
  r_key[107] = (m_key + 107) ^ 107480408;
  r_key[108] = (m_key + 108) ^ 214960816;
  r_key[109] = (m_key + 109) ^ 429921632;
  r_key[110] = (m_key + 110) ^ 859843264;
  r_key[111] = (m_key + 111) ^ 1719686528;
  r_key[112] = (m_key + 112) ^ 3439373056;
  r_key[113] = (m_key + 113) ^ 2583778817;
  r_key[114] = (m_key + 114) ^ 872590339;
  r_key[115] = (m_key + 115) ^ 1745180678;
  r_key[116] = (m_key + 116) ^ 3490361356;
  r_key[117] = (m_key + 117) ^ 2685755417;
  r_key[118] = (m_key + 118) ^ 1076543539;
  r_key[119] = (m_key + 119) ^ 2153087078;
  r_key[120] = (m_key + 120) ^ 11206861;
  r_key[121] = (m_key + 121) ^ 22413722;
  r_key[122] = (m_key + 122) ^ 44827444;
  r_key[123] = (m_key + 123) ^ 89654888;
  r_key[124] = (m_key + 124) ^ 179309776;
  r_key[125] = (m_key + 125) ^ 358619552;
  r_key[126] = (m_key + 126) ^ 717239104;
  r_key[127] = (m_key + 127) ^ 1434478208;
}

u32 s_box_gen(u32 text){ 
  u32 output = 0;
  u32 temp = 0; 
  int i = 0;

  for(i=0;i<8;i++){
    temp = ( ( text >> (4*i) ) & 0x0000000F ); 
    temp = s_box[temp];
    output = (output | ( temp << (4*i) ) ); 
  }

  return output; 
}

u32 p_box1_gen(u32 text){
  u32 p_idx[32] = {0, 8, 16, 24, 1, 9, 17, 25, 2, 10, 18, 26, 3, 11, 19, 27, 4, 12, 20, 28, 5, 13, 21, 29, 6, 14, 22, 30, 7, 15, 23, 31};
  u32 output = 0; 
  u32 temp = 0; 
  int i = 0;

  for(i=0;i<32;i++){
    temp = ((text>>i) & 0x00000001); 
    temp = (temp << p_idx[i]); 
    output = (output | temp);
  }

  return output; 
}

u32 p_box2_gen(u32 text){
  u32 p_idx[32] = {27, 1, 23, 30, 7, 22, 29, 16,  0, 4, 13, 18, 25, 17, 28, 31,  10, 14, 3, 5, 6, 2, 12, 11,  9, 8, 19, 26, 24, 20, 15, 21};
  u32 output = 0; 
  u32 temp = 0; 
  int i = 0;

  for(i=0;i<32;i++){
    temp = ((text>>i) & 0x00000001); 
    temp = (temp << p_idx[i]); 
    output = (output | temp);
  }

  return output; 
}

void new_bs_enc(u32* r_key, u32* text){ 
  u32* r_key_in = r_key;
  u32 text_in = *text;
  u8 bits[4] = {0};
  u8 tmp[4] = {0};
  int i;
  u32 new_pbox[32] = { 8, 9, 25, 22, 7, 29, 28, 14, 1, 19, 24, 10, 13, 31, 12, 6, 21, 20, 16, 17, 11, 5, 27, 3, 18, 4, 23, 30, 26, 2, 0, 15 };
  u32* T_ = (u32*)bits;
  u32* test = (u32*)tmp;
  u8* text_in_ = (u8*)(&text_in);
  
  // permutation1 + bitslice
  for (int j = 0; j < 32; j++) {
      switch (j % 4)
      {
      case 0:
          tmp[3] = tmp[3] | (((u8)text_in & 1) << (j >> 2)); // B3
          break;
      case 1:
          tmp[2] = tmp[2] | (((u8)text_in & 1) << (j >> 2)); // B2
          break;
      case 2:
          tmp[1] = tmp[1] | (((u8)text_in & 1) << (j >> 2)); // B1
          break;
      case 3:
          tmp[0] = tmp[0] | (((u8)text_in & 1) << (j >> 2)); // B0
          break;
      }
      text_in = text_in >> 1;
  }

  // sbox
  bits[3] = ((tmp[0] & (~tmp[3])) | (tmp[1] & (~tmp[3])) | ((~tmp[0]) & (~tmp[1]) & tmp[3])); // Y0
  bits[2] = ((~tmp[0]) & tmp[2]) | ((~tmp[0]) & tmp[1]) | (tmp[0] & (~tmp[1]) & (~tmp[2])); // Y1
  bits[1] = ((~tmp[1]) & tmp[2]) | ((~tmp[0]) & (~tmp[1]) & (~tmp[3])) | (tmp[1] & (~tmp[2]) & (~tmp[3])) | (tmp[0] & (~tmp[1]) & tmp[3]); // Y2
  bits[0] = ((~tmp[2]) & tmp[3]) | ((~tmp[0]) & (~tmp[1]) & (~tmp[2])) | ((~tmp[0]) & (~tmp[1]) & tmp[3]) | (tmp[0] & tmp[1] & (~tmp[2])) | ((~tmp[0]) & tmp[1] & tmp[2] & (~tmp[3])); // Y3

  // keyAddition
  text_in = *T_ ^ r_key_in[0];

  i = 1;
  while(i < NUM_ROUND) {
    *test = 0;

    // new_permutation
    for (int k = 0; k < 8; k++) {
      tmp[3] = tmp[3] | (((u8)(text_in >> new_pbox[k]) & 1) << k); // B3
      tmp[2] = tmp[2] | (((u8)(text_in >> new_pbox[k + 8]) & 1) << k); // B2
      tmp[1] = tmp[1] | (((u8)(text_in >> new_pbox[k + 16]) & 1) << k); // B1
      tmp[0] = tmp[0] | (((u8)(text_in >> new_pbox[k + 24]) & 1) << k); // B0
    }
    
    // sbox
    bits[3] = ((tmp[0] & (~tmp[3])) | (tmp[1] & (~tmp[3])) | ((~tmp[0]) & (~tmp[1]) & tmp[3])); // Y0
    bits[2] = ((~tmp[0]) | (~tmp[2])) & ((~tmp[0]) | (~tmp[1])) & (tmp[0] | tmp[1] | tmp[2]); // Y1
    bits[1] = ((~tmp[1]) & tmp[2]) | ((~tmp[0]) & (~tmp[1]) & (~tmp[3])) | (tmp[1] & (~tmp[2]) & (~tmp[3])) | (tmp[0] & (~tmp[1]) & tmp[3]); // Y2
    bits[0] = ((~tmp[2]) & tmp[3]) | ((~tmp[0]) & (~tmp[1]) & (~tmp[2])) | ((~tmp[0]) & (~tmp[1]) & tmp[3]) | (tmp[0] & tmp[1] & (~tmp[2])) | ((~tmp[0]) & tmp[1] & tmp[2] & (~tmp[3])); // Y3
    
    // keyAddition
    text_in = *T_ ^ r_key_in[i++];
  }
 
  u8 out[4] = {0};

  // permutation2
  out[3] = out[3] | (((text_in_[0]) & 1) << 3);
  text_in_[0] = text_in_[0] >> 1;
  out[0] = out[0] | (((text_in_[0]) & 1) << 1);
  text_in_[0] = text_in_[0] >> 1;
  out[2] = out[2] | (((text_in_[0]) & 1) << 7);
  text_in_[0] = text_in_[0] >> 1;
  out[3] = out[3] | (((text_in_[0]) & 1) << 6);
  text_in_[0] = text_in_[0] >> 1;
  out[0] = out[0] | (((text_in_[0]) & 1) << 7);
  text_in_[0] = text_in_[0] >> 1;
  out[2] = out[2] | (((text_in_[0]) & 1) << 6);
  text_in_[0] = text_in_[0] >> 1;
  out[3] = out[3] | (((text_in_[0]) & 1) << 5);
  text_in_[0] = text_in_[0] >> 1;
  out[2] = out[2] | (((text_in_[0]) & 1) << 0);
  out[0] = out[0] | (((text_in_[1]) & 1) << 0);
  text_in_[1] = text_in_[1] >> 1;
  out[0] = out[0] | (((text_in_[1]) & 1) << 4);
  text_in_[1] = text_in_[1] >> 1;
  out[1] = out[1] | (((text_in_[1]) & 1) << 5);
  text_in_[1] = text_in_[1] >> 1;
  out[2] = out[2] | (((text_in_[1]) & 1) << 2);
  text_in_[1] = text_in_[1] >> 1;
  out[3] = out[3] | (((text_in_[1]) & 1) << 1);
  text_in_[1] = text_in_[1] >> 1;
  out[2] = out[2] | (((text_in_[1]) & 1) << 1);
  text_in_[1] = text_in_[1] >> 1;
  out[3] = out[3] | (((text_in_[1]) & 1) << 4);
  text_in_[1] = text_in_[1] >> 1;
  out[3] = out[3] | (((text_in_[1]) & 1) << 7);
  out[1] = out[1] | (((text_in_[2]) & 1) << 2);
  text_in_[2] = text_in_[2] >> 1;
  out[1] = out[1] | (((text_in_[2]) & 1) << 6);
  text_in_[2] = text_in_[2] >> 1;
  out[0] = out[0] | (((text_in_[2]) & 1) << 3);
  text_in_[2] = text_in_[2] >> 1;
  out[0] = out[0] | (((text_in_[2]) & 1) << 5);
  text_in_[2] = text_in_[2] >> 1;
  out[0] = out[0] | (((text_in_[2]) & 1) << 6);
  text_in_[2] = text_in_[2] >> 1;
  out[0] = out[0] | (((text_in_[2]) & 1) << 2);
  text_in_[2] = text_in_[2] >> 1;
  out[1] = out[1] | (((text_in_[2]) & 1) << 4);
  text_in_[2] = text_in_[2] >> 1;
  out[1] = out[1] | (((text_in_[2]) & 1) << 3);
  out[1] = out[1] | (((text_in_[3]) & 1) << 1);
  text_in_[3] = text_in_[3] >> 1;
  out[1] = out[1] | (((text_in_[3]) & 1) << 0);
  text_in_[3] = text_in_[3] >> 1;
  out[2] = out[2] | (((text_in_[3]) & 1) << 3);
  text_in_[3] = text_in_[3] >> 1;
  out[3] = out[3] | (((text_in_[3]) & 1) << 2);
  text_in_[3] = text_in_[3] >> 1;
  out[3] = out[3] | (((text_in_[3]) & 1) << 0);
  text_in_[3] = text_in_[3] >> 1;
  out[2] = out[2] | (((text_in_[3]) & 1) << 4);
  text_in_[3] = text_in_[3] >> 1;
  out[1] = out[1] | (((text_in_[3]) & 1) << 7);
  text_in_[3] = text_in_[3] >> 1;
  out[2] = out[2] | (((text_in_[3]) & 1) << 5);
  
  *text = *(u32*)out;
}

u8 TEST_VECTOR(u32 in, u32 answer) { 
  return (in == answer);
}

void setup() {
  Serial.begin(115200); 
  pinMode(LED_BUILTIN, OUTPUT);

  // r_key : 32-bit x #128 
  u32 r_key[128] = {0, };

  // m_key : 32-bit
  u32 m_key[3]   = {0x12345678,0x01020304,0x55667788}; 
  
  // text: 32-bit
  u32 text[3]    = {0x90ABCDEF,0x0A0B0C0D,0xFFEEDDCC}; 
  u32 out_text[3]= {0xE4DE2FF8,0xE7F54BDC,0x53485E4F};

  Serial.println("-----------------");
  Serial.println("   TEST VECTOR ");
  Serial.println("-----------------");

  for(int i=0; i<3; i++) {
    new_bs_keygen(r_key, m_key[i]); 
    new_bs_enc(r_key, &text[i]);
    if(TEST_VECTOR(text[i], out_text[i])){ 
      Serial.println(">> CORRECT");
    }else{
      Serial.println(">> WRONG"); 
    }
  }
  Serial.println("-----------------");
  Serial.println("    BENCHMARK ");
  Serial.println("-----------------");

  // m_key : 32-bit
  u32 m_key_bench = 0x12345678; 
  
  // text: 32-bit
  u32 text_bench  = 0x90ABCDEF;

  u32 time1;
  u32 time2;
  time1 = millis(); 
  for(int i=0; i<64; i++) {
    new_bs_keygen(r_key, m_key_bench); 
    new_bs_enc(r_key, &text_bench);
  }
  time2 = millis();
  Serial.print(">> ");
  Serial.println((time2-time1));
  Serial.println("-----------------"); }

void loop() {
}