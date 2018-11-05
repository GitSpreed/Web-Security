#include "DES.h"

DES::DES(): data() {}

DES::DES(const block& src):data(src) {}

void DES::setData(const block &src) {
	data = src;
}

void DES::setKey(const block &src) {
	keys[0] = src;
	createKeys();
}

block DES::encryption() {
	IP_replacement(Table::IP);
	for (int i = 1; i <= 16; i++) {
		iterateT(keys[i]);
	}
	data.reverse();
	IP_replacement(Table::IP_back);
	return data;
}

block DES::decryption() {
	IP_replacement(Table::IP);
	for (int i = 16; i >= 1; i--) {
		iterateT(keys[i]);
	}
	data.reverse();
	IP_replacement(Table::IP_back);
	return data;
}

void DES::createKeys() {
	block temp = PC_1_replacement(keys[0]);
	for (int i = 1; i <= 16; i++) {
		temp = LS_replacement(temp, i);
		keys[i] = PC_2_compress(temp);
	}
}

void DES::IP_replacement(const int table[]) {
	block pre(data);
	for (int i = 0; i < 64; i++) {
		data.set(i, pre.get(table[i]-1));
	}
}

void DES::iterateT(const block& key) {
	block preL(data.getDWord(0));
	block preR(data.getDWord(1));
	
	data.setDWord(0, preR);
	data.setDWord(1, preL ^ f(preR, key));
}

block DES::f(const block &right, const block &key) {
	block er(E_extends(right));
	return p_replacement(s_box(er ^ key));
}

block DES::E_extends(const block &src) {
	block ret;
	for (int i = 0; i < 48; i++) {
		ret.set(i, src.get(Table::E_extend[i]-1));
	}
	return ret;
}

block DES::s_box(const block &src) {
	block ret;
	for (int i = 0; i < 8; i++) {
		int row = (src.get(i * 6) << 1) + src.get(i * 6 + 5);
		int col = (src.get(i * 6 + 1) << 3) +
				  (src.get(i * 6 + 2) << 2) +
				  (src.get(i * 6 + 3) << 1) +
				  src.get(i * 6 + 4);
		ret.setHalfByte(i, Table::S[i][row][col]-1);
	}
	return ret;
}

block DES::p_replacement(const block &src) {
	block ret;
	for (int i = 0; i < 32; i++) {
		ret.set(i, src.get(Table::P[i]-1));
	}
	return ret;
}

block DES::PC_1_replacement(const block &src) {
	block ret;
	for (int i = 0; i < 56; i++) {
		ret.set(i, src.get(Table::PC_1[i]-1));
	}
	return ret;
}

block DES::PC_2_compress(const block &src) {
	block ret;
	for (int i = 0; i < 48; i++) {
		ret.set(i, src.get(Table::PC_2[i]-1));
	}
	return ret;
}

block DES::LS_replacement(const block &src, int n) {
	block ret;
	int num = 2;
	if (n == 1 || n == 2 || n == 9 || n == 16) num = 1;
	for (int i = 0; i < 28; i++) {
		ret.set(i, src.get((i + num) % 28));
	}
	for (int i = 28; i < 56; i++) {
		ret.set(i, src.get((i + num) % 28 + 28));
	}
	return ret;
}
