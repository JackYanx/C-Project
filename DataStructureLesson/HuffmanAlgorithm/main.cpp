#include "commen.h"
#include "HuffmanEncoder.h"
int main() {
	//6��1,5��2,4��3,3��4,2��5,1��6,����21���ַ�
	string s = "111211122232345334564";// ��������������, �����������֮, ˽�Ϥ��ʤ���ۤ��Ǥޤ�";
	HuffmanEncoder mEncoder;
	mEncoder.init(s);
	mEncoder.encode();
	volatile int i = 0;
	volatile int& i1 = i;
	volatile int& i2 = i1;
	volatile int& i3 = i2;
	i3++;
	cout << i;
	return 0;
}