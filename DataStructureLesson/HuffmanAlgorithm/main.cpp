#include "commen.h"
#include "HuffmanEncoder.h"

int main() {
	HuffmanEncoder mEncoder;
	mEncoder.build("��ѹ�����ļ�","ѹ���õ��ļ�");
	mEncoder.encode();
	cin.get();
	return 0;
}