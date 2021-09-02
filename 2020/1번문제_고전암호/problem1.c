#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEYSIZE 5
#define BLOCKSIZE 257
#define GUESSSIZE 11881376

float expectedCount[26] = { 20.98919, 3.83444, 7.14974, 10.93021, 32.64414, 5.72596, 5.17855, 15.66158, 17.97972,
	0.39321, 1.98404, 10.34425, 6.18342, 17.34493, 19.29299, 4.95753, 0.24415, 15.38659, 16.26039,
	23.27392, 7.08806, 2.51346, 6.06520, 0.38550, 5.07318, 0.19018 }; // 알파벳에 대한 기대값
int alphabetCount[GUESSSIZE][32] = { 0, }; // 복호화 한 결과값에 대한 알파벳 빈도
float ChiValue[GUESSSIZE] = { 0, }; // 카이제곱 값

void keyRecovery();
int compare(const void* a, const void* b);
void decryption(int key[KEYSIZE][KEYSIZE]);
/*
{3,19, 11, 2, 3}
{9, 7, 12, 20, 13}
{12, 18, 4, 9, 0}
{17, 24, 13, 11, 21}
{18, 12, 6, 16, 23}
*/
int main() {
	int key[KEYSIZE][KEYSIZE] = {{3,19, 11, 2, 3}, {17, 24, 13, 11, 21} ,{12, 18, 4, 9, 0} ,{9, 7, 12, 20, 13}, {18, 12, 6, 16, 23}};
	
	//keyRecovery();

	decryption(key);

}

void keyRecovery() {
	
	char ct[1286] = "HRDKHUBHAAMAEQMTMZSHGBAKFUBHAASYRXUNKYUAATQCTLUTOGEWVAJGVEIIYTKIOTQRXXQVSQLISVVOCNGCUXPKPIUBOHTVKCFKWNJSEZYSSUTUOESIXKAPVFXNZHAOQTLCGYJVAEHLNNKEESQMKSHKKDFCNZSRHRDKHSDKFXVPTGMKRUPZBIKEVNYEKXMFXKFYMWYUDZDENEWNKDAOUXGPCXZDLCSNFGCMCSNUAOJDBLQTAHEWYZCHQJYKSNUWOKQKONZGOKDXGUXKEMWQMCFGUEAVKHDIIATCHVTGYMGKJMLNPCNAYKMIRWEETIYQKELEGLQOVKISFNUDAJQIQYBXQTMZSHGBAKFZRCNWRSODAFKKXWGAZGDBIUDDHCUDFRFOVSZXADSHYSGLTQBMNEMKDCFSOZSRDYLIHIAXCMGMFEIDNZKOVJEOIEFNWWQEDRLZYZIZXADSHYSGLJYFWDUAKSIOGOZOXWYPBUFEPNBIRJUJNDZJJYMURKNCIKPWLRMRIAGVSXTYNIWPROHLDHQOMBEKZURQCLQOVKISFNUAFQBHGPCLHZTPJVPXIZKLQSNVKIJAEITTNVSVWNFYVATDEMKDCTGIHKZTVGZYXTYQEDBACFMNCAHRDKHSDKFXZXXGMJOSLPSZBMOILMMWRALAFFMNXXDYFBIYQVVOHSWKGBIRJGTBYQLKIJAEQBTAXGFGAVUIJADHQKLFWRJXYFVIGGQZNBHSUIYOZALSKIABLWQNXNXKOAJAIKHXODXWORVDOGBMHOPLQJZALQJZALIKTKLENZHQAVYUEUFEVLUXHGOWNMGWXUIAHGQOMNCKFQLIPBNKVWDLNGMJCOBFKIGBYWPAHMMPQLUTOGECXITZVVAJEOIDCNWMFNLOBGQXCYFWQFWVXWRKWYGBFHJVLBAWBOUQEKHZHSZZIZARYITDCLQFPGBTJMQVSQLIHPEJONCYMZWTVJVZOBOMOHPSXMPUKVAGXIPOQUQUQBCKXZJSZAHEWYHAEMKOJCCCFBEUKVNCAWANSNXISVVOWHQGQFBGWKQEGBIFRGIZUJQWIMFANTGBHWGVAGXIPOQUQTTRMWDHDGRFENKYPZVCLNQAUBTZSRYGVGOWSVROENABMZTOHZRQFUEVPLLIODEYRYLUTOGPYAFHJFIVOSFMPBSHLEKWYWJYTFYETAZQCRFTFHOMACOQVTWKLKYMGIMQDSYNWMFNIEITWMBVVWANBQFVUSKZOTLCCWABAGHWZBZHRDKHDTUOMUUUGQICHNUUQFJYUCQUO"; //1285자 암호문
	int text[BLOCKSIZE][6] = { 0 }; // 암호문을 5개 단위로 묶음
	int count = 0;
	int key[KEYSIZE+1][KEYSIZE] = { 0, };
	int pt[BLOCKSIZE] = { 0 };
	int i, j, a1, a2, a3, a4, a5;

	for (i = 0; i < BLOCKSIZE; i++) { // 5개 단위로 쪼깨기
		for (j = 0; j < KEYSIZE; j++) {
			text[i][j] = ct[count] - 'A';
			count++;
		}
	}

	count = 0;
	for (a1 = 0; a1 < 26; a1++) {
		for (a2 = 0; a2 < 26; a2++) {
			for (a3 = 0; a3 < 26; a3++) {
				for (a4 = 0; a4 < 26; a4++) {
					for (a5 = 0; a5 < 26; a5++) {
						for (i = 0; i < BLOCKSIZE; i++) {
							// 추측한 키 복호화 후, 알파벳 빈도 측정
							pt[i] = (a1 * text[i][0] + a2 * text[i][1] + a3 * text[i][2] + a4 * text[i][3] + a5 * text[i][4]) % 26;
							alphabetCount[count][pt[i]]++;
						}
						// 그 때의 키 값 저장
						alphabetCount[count][26] = a1;
						alphabetCount[count][27] = a2;
						alphabetCount[count][28] = a3;
						alphabetCount[count][29] = a4;
						alphabetCount[count][30] = a5;

						// 카이제곱 통계값 계산
						for (int j = 0; j < 26; j++) {
							ChiValue[count] += (float)((expectedCount[j] - (float)alphabetCount[count][j]) * (expectedCount[j] - (float)alphabetCount[count][j]) / expectedCount[j]);

						}
						// 그 때의 카이제곱 값 저장
						alphabetCount[count][31] = (int)ChiValue[count];
						count++;
					}
				}
			}
		}
	}
	// 정렬
	qsort(ChiValue, GUESSSIZE, sizeof(float), compare);
	
	// 상위 5개 값일 때의 키 값 출력
	printf("\n------------- Chi-square, guess key List -------------\n\n");
	count = 0;
	for (i = 0; i < GUESSSIZE; i++) {
		if ((int)ChiValue[0] == alphabetCount[i][31] || (int)ChiValue[1] == alphabetCount[i][31]
			|| (int)ChiValue[2] == alphabetCount[i][31] || (int)ChiValue[3] == alphabetCount[i][31] || (int)ChiValue[4] == alphabetCount[i][31]) {
			printf("Chi-square = %d Key = [%02x %02x %02x %02x %02x]\n", alphabetCount[i][31], alphabetCount[i][26], alphabetCount[i][27], alphabetCount[i][28], alphabetCount[i][29], alphabetCount[i][30]);
			for (j = 0; j < KEYSIZE; j++) {
				key[count++][j] = alphabetCount[i][26 + j];
				
			}
		}
	}

}

int compare(const void* a, const void* b)    // 오름차순 비교 함수 구현
{
	int num1 = *(int*)a;    // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴
	int num2 = *(int*)b;    // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴

	if (num1 < num2)    // a가 b보다 작을 때는
		return -1;      // -1 반환

	if (num1 > num2)    // a가 b보다 클 때는
		return 1;       // 1 반환

	return 0;    // a와 b가 같을 때는 0 반환
}

void decryption(int key[KEYSIZE][KEYSIZE]) {
	
	char ct[1286] = "HRDKHUBHAAMAEQMTMZSHGBAKFUBHAASYRXUNKYUAATQCTLUTOGEWVAJGVEIIYTKIOTQRXXQVSQLISVVOCNGCUXPKPIUBOHTVKCFKWNJSEZYSSUTUOESIXKAPVFXNZHAOQTLCGYJVAEHLNNKEESQMKSHKKDFCNZSRHRDKHSDKFXVPTGMKRUPZBIKEVNYEKXMFXKFYMWYUDZDENEWNKDAOUXGPCXZDLCSNFGCMCSNUAOJDBLQTAHEWYZCHQJYKSNUWOKQKONZGOKDXGUXKEMWQMCFGUEAVKHDIIATCHVTGYMGKJMLNPCNAYKMIRWEETIYQKELEGLQOVKISFNUDAJQIQYBXQTMZSHGBAKFZRCNWRSODAFKKXWGAZGDBIUDDHCUDFRFOVSZXADSHYSGLTQBMNEMKDCFSOZSRDYLIHIAXCMGMFEIDNZKOVJEOIEFNWWQEDRLZYZIZXADSHYSGLJYFWDUAKSIOGOZOXWYPBUFEPNBIRJUJNDZJJYMURKNCIKPWLRMRIAGVSXTYNIWPROHLDHQOMBEKZURQCLQOVKISFNUAFQBHGPCLHZTPJVPXIZKLQSNVKIJAEITTNVSVWNFYVATDEMKDCTGIHKZTVGZYXTYQEDBACFMNCAHRDKHSDKFXZXXGMJOSLPSZBMOILMMWRALAFFMNXXDYFBIYQVVOHSWKGBIRJGTBYQLKIJAEQBTAXGFGAVUIJADHQKLFWRJXYFVIGGQZNBHSUIYOZALSKIABLWQNXNXKOAJAIKHXODXWORVDOGBMHOPLQJZALQJZALIKTKLENZHQAVYUEUFEVLUXHGOWNMGWXUIAHGQOMNCKFQLIPBNKVWDLNGMJCOBFKIGBYWPAHMMPQLUTOGECXITZVVAJEOIDCNWMFNLOBGQXCYFWQFWVXWRKWYGBFHJVLBAWBOUQEKHZHSZZIZARYITDCLQFPGBTJMQVSQLIHPEJONCYMZWTVJVZOBOMOHPSXMPUKVAGXIPOQUQUQBCKXZJSZAHEWYHAEMKOJCCCFBEUKVNCAWANSNXISVVOWHQGQFBGWKQEGBIFRGIZUJQWIMFANTGBHWGVAGXIPOQUQTTRMWDHDGRFENKYPZVCLNQAUBTZSRYGVGOWSVROENABMZTOHZRQFUEVPLLIODEYRYLUTOGPYAFHJFIVOSFMPBSHLEKWYWJYTFYETAZQCRFTFHOMACOQVTWKLKYMGIMQDSYNWMFNIEITWMBVVWANBQFVUSKZOTLCCWABAGHWZBZHRDKHDTUOMUUUGQICHNUUQFJYUCQUO"; //1285자 암호문
	int text[BLOCKSIZE][6] = { 0 }; // 암호문을 5개 단위로 묶음
	int count = 0;
	int pt[BLOCKSIZE][KEYSIZE] = { 0 };
	int i, j, a1, a2, a3, a4, a5;
	char ret[BLOCKSIZE * KEYSIZE] = { 0, };

	for (i = 0; i < BLOCKSIZE; i++) { // 5개 단위로 쪼깨기
		for (j = 0; j < KEYSIZE; j++) {
			text[i][j] = ct[count] - 'A';
			count++;
		}
	}

	
	for (i = 0; i < BLOCKSIZE; i++) {
		for (j = 0; j < KEYSIZE; j++) {
			pt[i][j] = (text[i][0]*key[j][0] + text[i][1]*key[j][1] + text[i][2]*key[j][2] + text[i][3]*key[j][3] + text[i][4]*key[j][4]) % 26;
			ret[5*i+j] = pt[i][j]+'A';
		}
	}
	printf("\n------------- Decryption Key -------------\n");

	for (i = 0; i < KEYSIZE; i++) {
		for (j = 0; j < KEYSIZE; j++) {
			printf("%02x ", key[j][i]);
		}
		printf("\n");
	}
	
	printf("\n------------- Decryption Result -------------\n");
	for (i = 0; i < BLOCKSIZE; i++) {
		for(j = 0; j < KEYSIZE; j++) {
			printf("%c", ret[5*i+j]);
		}
		if ((5 * i + j) % 50 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	
}