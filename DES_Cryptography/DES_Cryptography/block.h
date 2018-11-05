#ifndef BLOCK_H
#define BLOCK_H

#include <sstream>
#include <string>

#define BYTE_NUM 8

typedef char byte;
typedef bool bit;

using namespace std;

//加密时的一个块，大小为8bytes（64bits）
class block {
public:
	//构造函数与析构函数
	block();
	block(bit);
	block(byte[], int);
	block(const block &);
	block& operator=(const block &);
	~block();
	
	//一些get，set方法
	bit get(int) const;
	block getDWord(int) const;
	void setOne(int);
	void setZero(int);
	void set(int , bit);
	void setDWord(int, const block&);
	void setHalfByte(int, const block&);

	//将前32位与后32位交换
	void reverse();
	
	//按位异或
	block operator^(const block &src);
	string toString() const;

private:
	byte *_data; 
};

#endif
