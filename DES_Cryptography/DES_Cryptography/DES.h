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

	//������Ҫ���ܵ�����
	void setData(const block&);

	//���ü������õ�64λ��Կ
	void setKey(const block&);

	//��������
	block encryption();

	//��������
	block decryption();
	
private:
	block data;
	block keys[17];
	
	//IP�û�
	void IP_replacement(const int []);

	//����T
	void iterateT(const block&);

	//feistel�ֺ���
	block f(const block&, const block&);

	//E��չ
	block E_extends(const block&);

	//S��ѡ��
	block s_box(const block&);

	//P�û�
	block p_replacement(const block&);

	//PC1�û�
	block PC_1_replacement(const block&);

	//PC2ѹ��
	block PC_2_compress(const block&);

	//LS�û�
	block LS_replacement(const block&, int);

	//����64λ��Կ������16��48λ����Կ
	void createKeys();
};

#endif
