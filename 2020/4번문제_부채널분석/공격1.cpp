
// 코드 실행을 위한 조건
// 1. LoadingPowerTraces 함수 안의 fopen 함수의 전력 파형 파일 위치를 확인
// 2. ReadingC 함수 안의 fopen 함수의 암호문 파일 위치를 확인

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

unsigned char sbox[256] = // sbox 테이블
{ 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

unsigned char rsbox[256] = // sbox 역원 테이블
{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

unsigned char HwTable[256] = // 해밍 웨이트 테이블 
{ 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
  3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
  3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
  6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4,
  4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7,
  6, 7, 7, 8 };

unsigned char CipherText[1025][16]; // 암호문 
char PowerTraces[20000][1025]; // 전력 파형 
unsigned char LastKey[16] = { 0x22, 0xE5, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x5B, 0x2C, 0x00, 0x9B, 0x00, 0x00 }; // 10 라운드 키, 모르는 값의 경우 0x00으로 대입.

unsigned char state[16];
unsigned char AK_10[1025][16]; // 10라운드 InvKeyAddition 결과 
unsigned char SB_10[1025][16]; // 10라운드 InvShiftRows, InvSubBytes 결과
unsigned char AK_9[1025][16]; // 9라운드 InvKeyAddition 결과
unsigned char MC_9[1025][16]; // 9라운드 InvMixColumns 결과
unsigned char SB_9[1025][16]; // 9라운드 InvShiftRows, InvSubBytes 결과

int sum; 
int SUM[4];
unsigned char m[4][1025]; // 중간값 -> 해밍웨이트 변환 결과

double P; // 상관계수 저장할 변수

double mx[4][10000]; // 상관계수 저장할 배열
int ttt[4][10000]; // 전력 파형 구간 저장할 배열
int countvar[4]; // 카운팅하는 변수


double aver_p[20000]; // 전력 파형 평균
double aver_h; // 해밍 웨이트 평균

// 상관계수 = sigma2 / (sqrt(sigma2) * sqrt(sigma3))
double sigma1;
double sigma2;
double sigma3[20000];

// InvMixColumns 매크로 함수
// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

// 전력파형 파일 읽어오는 함수
void LoadingPowerTraces(void) {
	FILE* fp1 = fopen("PowerConsumption.txt", "r"); //파일 위치 입력 필요
	char temp[10000] = { 0 };
	for (int i = 0; i < 20000; i++) {
		fscanf(fp1, "%s", temp);
		int pre = 0;
		int nxt = 0;
		int p = 0;
		for (int j = 0; j <= strlen(temp); j++) {
			int k = 0;
			if (temp[j] == ',') {
				nxt = j - 1;
				char tem[5] = { 0,0,0,0,0 };
				for (int s = pre; s <= nxt; s++) {
					tem[k] = temp[s];
					k++;
				}
				PowerTraces[i][p] = atoi(tem);
				p++;
				pre = nxt + 2;
			}
			else if (p == 1024 && temp[j] == 0) {
				char tem[5] = { 0,0,0,0,0 };
				nxt = j - 1;
				for (int s = pre; s <= nxt; s++) {
					tem[k] = temp[s];
					k++;
				}
				PowerTraces[i][p] = atoi(tem);
			}
		}
	}
}

// 암호문 읽어오는 함수
void ReadingC(void) {
	FILE* fp = fopen("exam.txt", "rb"); // 파일 위치 입력 필요
	for (int i = 0; i < 1025; i++) {
		for (int j = 0; j < 16; j++) {
			CipherText[i][j] = getc(fp);
		}
	}
}



//
//   암호문C   -> 10라운드 InvShiftRows ->   결 과 1    ->    9라운드 InvShiftRows - >    결 과 2
// 00 04 08 12                           00 04 08 12                                 00 04 08 12
// 01 05 09 13                           13 01 05 09                                 09 13 01 05
// 02 06 10 14                           10 14 02 06                                 02 06 10 14
// 03 07 11 15                           07 11 15 03                                 11 15 03 07
//
//  9라운드 키
//   a   e   i   m
//   b   f   j   n 
//   c   g   k   o
//   d   h   l   p
//  1열 2열 3열 4열
//
// 중간값은 8라운드 KeyAddition 결과이며 이것은 암호문을 복호화하였을 때 9라운드 InvSubBytes 결과임.
// 공격1 코드에서는 9라운드의 1열을 공격함.
// 따라서 암호문 C에서의 결과1의 1열 00, 13, 10, 07을 공격함.
// 9라운드 키  a는 0~255, b, c, d =0으로 가정하여 전력 파형의 정보를 얻기 위한 공격임.

// FIRST, .., FOURTH에 에 공격할 암호문의 위치 저장
#define FIRST 0  
#define SECOND 13
#define THIRD 10
#define FOURTH 7
int numbering[4] = { FIRST, SECOND, THIRD, FOURTH };


int main(void) {
	LoadingPowerTraces(); // 전력 파형 읽어와서 PowerTraces 배열에 저장
	ReadingC(); // 암호문 읽어와서 CipherText 배열에 저장

	// 전력 파형 구간 20000길이에서 각 지점에서의 1025개의 평균을 구하고 분산을 구함.
	for (int i = 0; i < 20000; i++) {
		sum = 0;
		for (int j = 0; j < 1025; j++) {
			sum += PowerTraces[i][j];
		}
		aver_p[i] = (double)sum / 1025; // i구간의 평균
		for (int j = 0; j < 1025; j++) {
			sigma3[i] += ((double)PowerTraces[i][j] - aver_p[i]) * ((double)PowerTraces[i][j] - aver_p[i]); // i구간의 분산
		}
	}

	// 중간값 계산 시작
	for (int e = 0; e < 1025; e++) {
		// 10라운드 InvKeyAddtion 
		AK_10[e][FIRST] = LastKey[FIRST] ^ CipherText[e][FIRST];
		AK_10[e][SECOND] = LastKey[SECOND] ^ CipherText[e][SECOND];
		AK_10[e][THIRD] = LastKey[THIRD] ^ CipherText[e][THIRD];
		AK_10[e][FOURTH] = LastKey[FOURTH] ^ CipherText[e][FOURTH];
		// 10라운드 InvShiftRows, InvSubBytes 
		SB_10[e][FIRST] = rsbox[AK_10[e][FIRST]];
		SB_10[e][SECOND] = rsbox[AK_10[e][SECOND]];
		SB_10[e][THIRD] = rsbox[AK_10[e][THIRD]];
		SB_10[e][FOURTH] = rsbox[AK_10[e][FOURTH]];
	}

	// key(9,0) = a, key(9,1), key(9,2), key(9,3) = 0
	for (int a = 0; a < 256; a++) {
		SUM[0] = 0;
		SUM[1] = 0;
		SUM[2] = 0;
		SUM[3] = 0;
		aver_h = 0;
		sigma1 = 0;
		sigma2 = 0;
		for (int e = 0; e < 1025; e++) {
			// 9라운드 InvKeyAddtion
			AK_9[e][FIRST] = a ^ SB_10[e][FIRST];
			AK_9[e][SECOND] = 0x00 ^ SB_10[e][SECOND];
			AK_9[e][THIRD] = 0x00 ^ SB_10[e][THIRD];
			AK_9[e][FOURTH] = 0x00 ^ SB_10[e][FOURTH];

			// 9라운드 InvMixColumns
			unsigned char aa, bb, cc, dd;

			aa = AK_9[e][FIRST];
			bb = AK_9[e][SECOND];
			cc = AK_9[e][THIRD];
			dd = AK_9[e][FOURTH];
			MC_9[e][FIRST] = Multiply(aa, 0x0e) ^ Multiply(bb, 0x0b) ^ Multiply(cc, 0x0d) ^ Multiply(dd, 0x09);
			MC_9[e][SECOND] = Multiply(aa, 0x09) ^ Multiply(bb, 0x0e) ^ Multiply(cc, 0x0b) ^ Multiply(dd, 0x0d);
			MC_9[e][THIRD] = Multiply(aa, 0x0d) ^ Multiply(bb, 0x09) ^ Multiply(cc, 0x0e) ^ Multiply(dd, 0x0b);
			MC_9[e][FOURTH] = Multiply(aa, 0x0b) ^ Multiply(bb, 0x0d) ^ Multiply(cc, 0x09) ^ Multiply(dd, 0x0e);

			// 9라운드 InvShiftRows, InvSubBytes
			SB_9[e][FIRST] = rsbox[MC_9[e][FIRST]];
			SB_9[e][SECOND] = rsbox[MC_9[e][SECOND]];
			SB_9[e][THIRD] = rsbox[MC_9[e][THIRD]];
			SB_9[e][FOURTH] = rsbox[MC_9[e][FOURTH]];

			// 최종 중간값 SB_9를 해밍웨이트 모델려 변환
			m[0][e] = HwTable[SB_9[e][FIRST]];
			m[1][e] = HwTable[SB_9[e][SECOND]];
			m[2][e] = HwTable[SB_9[e][THIRD]];
			m[3][e] = HwTable[SB_9[e][FOURTH]];

			// 평균을 구하기 위해 모든 값을 더함
			SUM[0] += m[0][e];
			SUM[1] += m[1][e];
			SUM[2] += m[2][e];
			SUM[3] += m[3][e];
		}
		for (int k = 0; k < 4; k++) {
			aver_h = (double)SUM[k] / 1025; // 평균 구하기
			for (int i = 0; i < 10000; i++) { 
				sigma1 = 0;
				sigma2 = 0;
				for (int e = 0; e < 1025; e++) {
					double z = (double)m[k][e] - aver_h; 
					sigma1 += z * z; // 분산 구하기
					sigma2 += z * (double)(PowerTraces[10000 + i][e] - aver_p[10000 + i]); // cov(전력, 중간값) 구하기
				}
				P = sigma2 / sqrt(sigma1) / sqrt(sigma3[10000 + i]); // 상관계수 구하기

				// 상관계수가 0.3과 같거나 크면 유의미하다고 판단하고 배열에 저장함
				if (abs(P) >= 0.3) {
					mx[k][countvar[k]] = P;
					ttt[k][countvar[k]] = 10000 + i;
					countvar[k]++;
				}
			}
		}
	}

	// <표 1>과 같은 결과 출력
	for (int i = 0; i < 4; i++) {
		printf("중간값으로 암호문의 %d번째 위치 공격 결과 (M''[%d])\n", numbering[i], i);
		printf("구간 t에서 상관계수 r관찰\n");
		for (int j = 0; j < countvar[i]; j++) {
			printf("%d, %f\n", ttt[i][j], mx[i][j]);
		}
		printf("\n");
	}
}