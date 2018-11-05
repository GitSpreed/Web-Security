#include "block.h"


block::block() {
	_data = new byte[BYTE_NUM];
	for (int  i = 0; i < BYTE_NUM; i++) {
		_data[i] = 0;
	}
}

block::block(bit init) {
	_data = new byte[BYTE_NUM];
	byte num = 0;
	if (init) {
		num = 255;
	} else {
		num = 0;
	}	
	for (int  i = 0; i < BYTE_NUM; i++) {
		_data[i] = num;
	}
}

block::block(byte init[], int len) {
	int top = (len < BYTE_NUM ? len : BYTE_NUM);
	int i = 0;
	_data = new byte[BYTE_NUM];
	for (; i < top; i++) {
		_data[i] = init[i];
	}
	for(; i < BYTE_NUM; i++) {
		_data[i] = 0;
	}
}

block::block(const block &src) {
	_data = new byte[BYTE_NUM];
	for (int i = 0; i < BYTE_NUM; i++) {
		_data[i] = src._data[i];
	}
}

block& block::operator=(const block &src) {
	/*if (_data != null) delete []_data;
	_data = new byte[BYTE_NUM];*/
	for (int i = 0; i < BYTE_NUM; i++) {
		_data[i] = src._data[i];
	}
	return *this;
}

block::~block() {
	delete []_data;
}

bool block::get(int index) const {
	if (index < 0 || index > BYTE_NUM * 8) throw "ERROR: The Index is out of block's range!";
	byte num = 1 << (index % 8);
	return (_data[index / 8] & num) != 0;
}

block block::getDWord(int index) const {
	block ret;
	ret._data[0] = _data[index * 2];
	ret._data[1] = _data[index * 2 + 1]; 
	return ret;
}

void block::setOne(int index) {
	if (index < 0 || index > BYTE_NUM * 8) throw "ERROR: The Index is out of block's range!";
	byte num = 1 << (index % 8);
	_data[index / 8] |= num;
}

void block::setZero(int index) {
	if (index < 0 || index > BYTE_NUM * 8) throw "ERROR: The Index is out of block's range!";
	byte num = ~(1 << (index % 8));
	_data[index / 8] &= num;
}

void block::set(int index, bit b) {
	if (b) {
		this->setOne(index);
	} else {
		this->setZero(index);
	}
}

void block::setDWord(int index, const block &src) {
	_data[index * 2] = src._data[0];
	_data[index * 2 + 1] = src._data[1];
}
void block::setHalfByte(int index, const block &src) {
	byte b = src._data[0];
	byte num = 10; //00001111
	if (index % 2 == 1) {
		b = b << 4;
		num = num << 4;
	}
	_data[index / 2] = _data[index / 2] & (~num) | b;
}

block block::operator^(const block &src) {
	block ret(*this);
	for (int i = 0; i < BYTE_NUM; i++) {
		ret._data[i] ^= src._data[i];
	}
	return ret;
}

string block::toString() const
{
	stringstream buf;
	for (int i = 0; i < BYTE_NUM; i++) {
		buf << (char)_data[i];
	}
	return buf.str();
}

void block::reverse() {
	byte exchange = _data[0];
	_data[0] = _data[2];
	_data[2] = exchange;
	
	exchange = _data[1];
	_data[1] = _data[3];
	_data[3] = exchange;
}
