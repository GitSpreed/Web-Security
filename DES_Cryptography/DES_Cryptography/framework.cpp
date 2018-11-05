#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <cstdlib> 
#include "DES.h"

using namespace std;

int main() {

	const string file_origin = "Test_Data/in.txt";
	const string file_ciphertext = "Test_Data/out.txt";
	const string file_decry = "Test_Data/decry.txt";
	const string file_key = "Test_Data/key.txt";

	DES des;

	//������Կ
	byte key[8];
	srand(time(0));
	for (int i = 0; i < 8; i++) {
		key[i] = rand() % 256;
	}
	block k(key, 8);
	des.setKey(k);
	
	//��ȡԭ��
	ifstream inf(file_origin);
	ofstream outf(file_ciphertext);
	ofstream def(file_decry);
	stringstream buf;

	buf << inf.rdbuf();
	string origin = buf.str();
	int len = origin.length();

	string ciphertext = "";
	string decry = "";

	byte data[8];
	for (int i = 0; i < len; i += BYTE_NUM) {
		int end = (i + BYTE_NUM < len ? BYTE_NUM : len - i);
		for (int j = 0; j < end; j++) {
			data[j] = origin[i + j];
		}
		block d(data, BYTE_NUM);
		des.setData(d);
		//����
		ciphertext += des.encryption().toString();
		//����
		decry += des.decryption().toString();
	}
	outf << ciphertext;
	def << decry;
	outf.close();
	inf.close();
	def.close();

	//����˴μ��ܵ���Կ
	outf.open(file_key);
	outf << k.toString();
	outf.close();

	return 0;
}
