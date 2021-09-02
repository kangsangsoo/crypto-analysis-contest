
// �ڵ� ������ ���� ����
// 1. LoadingPowerTraces �Լ� ���� fopen �Լ��� ���� ���� ���� ��ġ�� Ȯ��
// 2. ReadingC �Լ� ���� fopen �Լ��� ��ȣ�� ���� ��ġ�� Ȯ��

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

unsigned char sbox[256] = // sbox ���̺�
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

unsigned char rsbox[256] = // sbox ���� ���̺�
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

unsigned char HwTable[256] = // �ع� ����Ʈ ���̺� 
{ 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
  3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
  3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
  6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4,
  4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7,
  6, 7, 7, 8 };

unsigned char CipherText[1025][16]; // ��ȣ�� 
char PowerTraces[20000][1025]; // ���� ���� 
unsigned char LastKey[16] = { 0x22, 0xE5, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x5B, 0x2C, 0x00, 0x9B, 0x00, 0x00 }; // 10 ���� Ű, �𸣴� ���� ��� 0x00���� ����.

unsigned char state[16];
unsigned char AK_10[1025][16]; // 10���� InvKeyAddition ��� 
unsigned char SB_10[1025][16]; // 10���� InvShiftRows, InvSubBytes ���
unsigned char AK_9[1025][16]; // 9���� InvKeyAddition ���
unsigned char MC_9[1025][16]; // 9���� InvMixColumns ���
unsigned char SB_9[1025][16]; // 9���� InvShiftRows, InvSubBytes ���

int sum; 
int SUM[4];
unsigned char m[4][1025]; // �߰��� -> �عֿ���Ʈ ��ȯ ���

double P; // ������ ������ ����

double mx[4][10000]; // ������ ������ �迭
int ttt[4][10000]; // ���� ���� ���� ������ �迭
int countvar[4]; // ī�����ϴ� ����


double aver_p[20000]; // ���� ���� ���
double aver_h; // �ع� ����Ʈ ���

// ������ = sigma2 / (sqrt(sigma2) * sqrt(sigma3))
double sigma1;
double sigma2;
double sigma3[20000];

// InvMixColumns ��ũ�� �Լ�
// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

// �������� ���� �о���� �Լ�
void LoadingPowerTraces(void) {
	FILE* fp1 = fopen("PowerConsumption.txt", "r"); //���� ��ġ �Է� �ʿ�
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

// ��ȣ�� �о���� �Լ�
void ReadingC(void) {
	FILE* fp = fopen("exam.txt", "rb"); // ���� ��ġ �Է� �ʿ�
	for (int i = 0; i < 1025; i++) {
		for (int j = 0; j < 16; j++) {
			CipherText[i][j] = getc(fp);
		}
	}
}



//
//   ��ȣ��C   -> 10���� InvShiftRows ->   �� �� 1    ->    9���� InvShiftRows - >    �� �� 2
// 00 04 08 12                           00 04 08 12                                 00 04 08 12
// 01 05 09 13                           13 01 05 09                                 09 13 01 05
// 02 06 10 14                           10 14 02 06                                 02 06 10 14
// 03 07 11 15                           07 11 15 03                                 11 15 03 07
//
//  9���� Ű
//   a   e   i   m
//   b   f   j   n 
//   c   g   k   o
//   d   h   l   p
//  1�� 2�� 3�� 4��
//
// �߰����� 8���� KeyAddition ����̸� �̰��� ��ȣ���� ��ȣȭ�Ͽ��� �� 9���� InvSubBytes �����.
// ����1 �ڵ忡���� 9������ 1���� ������.
// ���� ��ȣ�� C������ ���1�� 1�� 00, 13, 10, 07�� ������.
// 9���� Ű  a�� 0~255, b, c, d =0���� �����Ͽ� ���� ������ ������ ��� ���� ������.

// FIRST, .., FOURTH�� �� ������ ��ȣ���� ��ġ ����
#define FIRST 0  
#define SECOND 13
#define THIRD 10
#define FOURTH 7
int numbering[4] = { FIRST, SECOND, THIRD, FOURTH };


int main(void) {
	LoadingPowerTraces(); // ���� ���� �о�ͼ� PowerTraces �迭�� ����
	ReadingC(); // ��ȣ�� �о�ͼ� CipherText �迭�� ����

	// ���� ���� ���� 20000���̿��� �� ���������� 1025���� ����� ���ϰ� �л��� ����.
	for (int i = 0; i < 20000; i++) {
		sum = 0;
		for (int j = 0; j < 1025; j++) {
			sum += PowerTraces[i][j];
		}
		aver_p[i] = (double)sum / 1025; // i������ ���
		for (int j = 0; j < 1025; j++) {
			sigma3[i] += ((double)PowerTraces[i][j] - aver_p[i]) * ((double)PowerTraces[i][j] - aver_p[i]); // i������ �л�
		}
	}

	// �߰��� ��� ����
	for (int e = 0; e < 1025; e++) {
		// 10���� InvKeyAddtion 
		AK_10[e][FIRST] = LastKey[FIRST] ^ CipherText[e][FIRST];
		AK_10[e][SECOND] = LastKey[SECOND] ^ CipherText[e][SECOND];
		AK_10[e][THIRD] = LastKey[THIRD] ^ CipherText[e][THIRD];
		AK_10[e][FOURTH] = LastKey[FOURTH] ^ CipherText[e][FOURTH];
		// 10���� InvShiftRows, InvSubBytes 
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
			// 9���� InvKeyAddtion
			AK_9[e][FIRST] = a ^ SB_10[e][FIRST];
			AK_9[e][SECOND] = 0x00 ^ SB_10[e][SECOND];
			AK_9[e][THIRD] = 0x00 ^ SB_10[e][THIRD];
			AK_9[e][FOURTH] = 0x00 ^ SB_10[e][FOURTH];

			// 9���� InvMixColumns
			unsigned char aa, bb, cc, dd;

			aa = AK_9[e][FIRST];
			bb = AK_9[e][SECOND];
			cc = AK_9[e][THIRD];
			dd = AK_9[e][FOURTH];
			MC_9[e][FIRST] = Multiply(aa, 0x0e) ^ Multiply(bb, 0x0b) ^ Multiply(cc, 0x0d) ^ Multiply(dd, 0x09);
			MC_9[e][SECOND] = Multiply(aa, 0x09) ^ Multiply(bb, 0x0e) ^ Multiply(cc, 0x0b) ^ Multiply(dd, 0x0d);
			MC_9[e][THIRD] = Multiply(aa, 0x0d) ^ Multiply(bb, 0x09) ^ Multiply(cc, 0x0e) ^ Multiply(dd, 0x0b);
			MC_9[e][FOURTH] = Multiply(aa, 0x0b) ^ Multiply(bb, 0x0d) ^ Multiply(cc, 0x09) ^ Multiply(dd, 0x0e);

			// 9���� InvShiftRows, InvSubBytes
			SB_9[e][FIRST] = rsbox[MC_9[e][FIRST]];
			SB_9[e][SECOND] = rsbox[MC_9[e][SECOND]];
			SB_9[e][THIRD] = rsbox[MC_9[e][THIRD]];
			SB_9[e][FOURTH] = rsbox[MC_9[e][FOURTH]];

			// ���� �߰��� SB_9�� �عֿ���Ʈ �𵨷� ��ȯ
			m[0][e] = HwTable[SB_9[e][FIRST]];
			m[1][e] = HwTable[SB_9[e][SECOND]];
			m[2][e] = HwTable[SB_9[e][THIRD]];
			m[3][e] = HwTable[SB_9[e][FOURTH]];

			// ����� ���ϱ� ���� ��� ���� ����
			SUM[0] += m[0][e];
			SUM[1] += m[1][e];
			SUM[2] += m[2][e];
			SUM[3] += m[3][e];
		}
		for (int k = 0; k < 4; k++) {
			aver_h = (double)SUM[k] / 1025; // ��� ���ϱ�
			for (int i = 0; i < 10000; i++) { 
				sigma1 = 0;
				sigma2 = 0;
				for (int e = 0; e < 1025; e++) {
					double z = (double)m[k][e] - aver_h; 
					sigma1 += z * z; // �л� ���ϱ�
					sigma2 += z * (double)(PowerTraces[10000 + i][e] - aver_p[10000 + i]); // cov(����, �߰���) ���ϱ�
				}
				P = sigma2 / sqrt(sigma1) / sqrt(sigma3[10000 + i]); // ������ ���ϱ�

				// �������� 0.3�� ���ų� ũ�� ���ǹ��ϴٰ� �Ǵ��ϰ� �迭�� ������
				if (abs(P) >= 0.3) {
					mx[k][countvar[k]] = P;
					ttt[k][countvar[k]] = 10000 + i;
					countvar[k]++;
				}
			}
		}
	}

	// <ǥ 1>�� ���� ��� ���
	for (int i = 0; i < 4; i++) {
		printf("�߰������� ��ȣ���� %d��° ��ġ ���� ��� (M''[%d])\n", numbering[i], i);
		printf("���� t���� ������ r����\n");
		for (int j = 0; j < countvar[i]; j++) {
			printf("%d, %f\n", ttt[i][j], mx[i][j]);
		}
		printf("\n");
	}
}