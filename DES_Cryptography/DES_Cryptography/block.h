#ifndef BLOCK_H
#define BLOCK_H

#include <sstream>
#include <string>

#define BYTE_NUM 8

typedef char byte;
typedef bool bit;

using namespace std;

//����ʱ��һ���飬��СΪ8bytes��64bits��
class block {
public:
	//���캯������������
	block();
	block(bit);
	block(byte[], int);
	block(const block &);
	block& operator=(const block &);
	~block();
	
	//һЩget��set����
	bit get(int) const;
	block getDWord(int) const;
	void setOne(int);
	void setZero(int);
	void set(int , bit);
	void setDWord(int, const block&);
	void setHalfByte(int, const block&);

	//��ǰ32λ���32λ����
	void reverse();
	
	//��λ���
	block operator^(const block &src);
	string toString() const;

private:
	byte *_data; 
};

#endif
