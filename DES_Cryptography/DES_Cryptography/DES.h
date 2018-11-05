#ifndef DES_H
#define DES_H

#include <cstring>
#include "block.h"
#include "table.h"

using namespace std; 

class DES {
public:
	DES();
	DES(const block&);

	//设置需要加密的数据
	void setData(const block&);

	//设置加密所用的64位密钥
	void setKey(const block&);

	//加密数据
	block encryption();

	//解密数据
	block decryption();
	
private:
	block data;
	block keys[17];
	
	//IP置换
	void IP_replacement(const int []);

	//迭代T
	void iterateT(const block&);

	//feistel轮函数
	block f(const block&, const block&);

	//E扩展
	block E_extends(const block&);

	//S盒选择
	block s_box(const block&);

	//P置换
	block p_replacement(const block&);

	//PC1置换
	block PC_1_replacement(const block&);

	//PC2压缩
	block PC_2_compress(const block&);

	//LS置换
	block LS_replacement(const block&, int);

	//根据64位密钥，创建16个48位子密钥
	void createKeys();
};

#endif
