#include "commen.h"
#include "HuffmanEncoder.h"
int main() {
	//6��1,5��2,4��3,3��4,2��5,1��6,����21���ַ�
	string s = "111211122232345334564";
	HuffmanEncoder mEncoder;
	mEncoder.init(s);
	mEncoder.encode();
	return 0;
}