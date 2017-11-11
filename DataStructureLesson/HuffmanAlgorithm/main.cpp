#include "commen.h"
#include "HuffmanEncoder.h"
int main() {
	//6个1,5个2,4个3,3个4,2个5,1个6,共计21个字符
	string s = "111211122232345334564";// 苟利国家生死以, 起因祸福避趋之, 私はあなたを愛しでます";
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