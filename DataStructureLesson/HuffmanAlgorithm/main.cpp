#include "commen.h"
#include "HuffmanEncoder.h"
char buf[25501];
int main() {
	//6��1,5��2,4��3,3��4,2��5,1��6,����21���ַ�
	//string s = "111211122232345334564";// , JNIEXPORT void JNICALL Java_org_andengine_opengl_util_BufferUtils_jniPut(JNIEnv *env, jclass, jobject pBuffer, jfloatArray pData, jint pLength, jint pOffset), ��������������, �����������֮, ˽�Ϥ��ʤ���ۤ��Ǥޤ�";
	string s = "���ʣ�Ѻ���P ������Ѻ���P ������Ѻ���P �£�������� �����Ȥ�������ĸ������������ �񣨤��ޣ��ޤǤ����to u sa n ka a sa n i ma ma de go me n�ְ֋��� �����ֹ�韩��ϥ���Ҥ������𣨤դ룩�碌 �Hָ�������ӣ�����֤�hi za wo fu ru wa se o ya yu bi sha bu ru������ϥ�w ҧ����Ĵָ�֣��ˤ������󊗣��ͤ������� ���줸�㤢�ޤ��� ni i sa n ne e sa nso re ja a ma ta ne����� ���N��Ҋ�Ƀ꣨�������ʤ�ѥ�����ģ��� �ࣨ�����ȣ������Ĥ֣����� sa e na i ku tsu no ka ka to tsu bu shi taĥ�p��Ь�� �����_���Ҋ���ߣ��������ϣ��ä��������� �ͼ����������ߣ���ȡ���ȣ���mi e ha tta sa i zu de ka ta ga mi wo to ru�F���@�۵ĳߴ��¼������Σ��ʤ󣩤��äƤ����Τ� �����������ˤʤ�� nan da tte i i no sa ka wa ri ni na re ba���N����ʲ�N�Ӳź��ۣؐ����������줿���� �ڣ����������㣨���ܣ�����a i sa re ta i to ku chi wo ko bo shi ta�������뱻�ۤ�ä��ɷ򣨤��礦�֣��� �ϥ��ߤ� mo tto jo u bu na ha sa mi de�ø��Y���ļ�������������У�������ȡ���ȣ���Τ�ka o wo ki ri to ru no sa�����@��Ę��ȫ��ȫ�ܣ����������Τ��������~�����ȤУ��� �ۤ������������Ƥ� ze n chi ze n no u no ko to ba wo ho ra ki ka se te yo��׌��  ȫ��ȫ�ܵ�Ԓ�Z��×���Τ����ߤ����⣨�������� �⤦����ʤ���why not I don't knowno u mi so i ga i mo u i ra na i to  why not I don't know �^�X�����ٟo��Ҫ��δ��������ߤ餤�����죨���������� ���գ��������΂��������礦������ �����e���棩 �餷�Ƥ�ki n mi ra i so u zo u a su no sho u so u ta da yu ra shi te yo��δ�턓�� ����Ą��� ���@�ӓu�Ӱ� �p���̣���Ŀ���ᣩ��϶�g�������ޣ����񣨤�����Ƥ����� nu i me no su ki ma wo u me te o ku reȥ�������Ŀp϶�g�ԣ��ߤʣ����󤵤褦�ʤ� ���������󤻤�����Ԫ�ݣ����󤭣��� mi na sa n sa yo u na ra se n se i o ge n ki de�����Ҋ�� �ώ����ذ��ߣ��������ʤä��أ���ͣ��� �ѣ�����죩�������������ta ka na tta mu ne ni  yo da re ga ta re ru���Q������ ��������ˮ��ֱ�ߣ����礦������Σ��ϺΣ��ʤˣ���Ҋ���ߣ��룿��ֱ�ߣ����礦������Σ����R ¹���Ф�����Ҋ���ߣ��룡sho u ji ki mo no wa na ni wo mi rusho u ji ki mo n owa ba ka wo mi ru�ό��˿���ʲ�N�� �ό��˿��������أ���ֱ�ߣ����礦������Σ��ϺΣ��ʤˣ���Ҋ���ߣ��룿��ֱ�ߣ����礦������Σ����R ¹���Ф�����Ҋ���ߣ��룡sho u ji ki mo no wa na ni wo mi rusho u ji ki mo n owa ba ka wo mi ru�ό��˿���ʲ�N�� �ό��˿��������أ����`�����줸��ޤ��㣨������ʤ��� a a ko re ja ma da ta ri na i yo�����@��߀����Ŷ��äȴ󣨤��������� �ߥ���� �ģ�������؞���Ĥ�̣����Τ�mo tto o o ki na mi shi n de ko ko ro tsu ra nu ku no sa���ٴ�һ�c�Ŀp�x�C ؞�����K��ȫ��ȫ�ܣ����������Τ��������~�����ȤУ��� �ۤ������������Ƥ�ze n chi ze n no u no ko to ba wo ho ra ki ka se te yo��׌��  ȫ��ȫ�ܵ�Ԓ�Z��×���Τ����ߤ����⣨�������� �⤦����ʤ��� why not I don't knowno u mi so i ga i mo u i ra na i to  why not I don't know�^�X�����ٟo��Ҫ   why not, I don't know��δ��������ߤ餤�����죨���������� ���գ��������΂��������礦������ �����e���棩 �餷�Ƥ�ki n mi ra i so u zo u a su no sho u so u ta da yu ra shi te yo ��δ�턓�� ����Ą��� ���@�ӓu�Ӱɿp���̣���Ŀ���ᣩ��϶�g�������ޣ����񣨤�����Ƥ�����nu i me no su ki ma wo u me te o ku reȥ�������Ŀp϶�g�⤦�Σ��ʤˣ���o���ʣ����� �Σ��ʤˣ���o���ʣ����� �����ң��������ϣ������� ��mo u na ni mo na i yo na ni mo na i yo hi ki ha ga sa re te�ѽ�һ�o���а� һ�o���а� ��������м�����Ȥ������� �������ߣ��ؤ� ���μ����������ܤ�����i to ku zu no u mi e to ko no sa i bo u mo�@Щ����Ҳ�������^�ĺ��󤽤��ܥ����ʤ��� �ܥ����ʤ��� Ͷ���ʣ����Σ������Ƥ���so u bo ku i na i yo bo ku i na i yo na ge su te ra re te�ǰ��Ҳ������� �Ҳ������� ���G���ˎ�����������������Ф��磩����΄I���ɤ����ˤ� �o���ʣ��������ka e ru ba sho su ra do ko ni mo na i n da yo���B��ȥ�ĵط�Ҳ�������ش��ڣ����󤶤����^�������礦�ᤤ���� ���`��shut up �������餱���壨�������so n za i sho u me i a a shut up u so da ra ke no ka ra da�����C��������shut up ��M�e�Ե����w��ɣ����󤻤����������� ���뤷������ �񣨤��ޣ�����𣨤����Ȥ����� ka n se i shi ta i yo zu ru shi ta i yo i ma ka i to u wo������ɰ� ����m�_�^ �F�ڌ��ǽ���䣨�������ʤ��Σ� �������줿���Σ�ka wa re na i no ka wa re ta i no�o����׃�᣿�뱻��B�᣿�Σ��ʤˣ���o���ʣ����� ����ʤΥܥ�����ʤ���na ni mo na i ko n na no bo ku ja naiһ�o���І᣿�@�������ң��p���̣���Ŀ���ᣩ�Ͻ⣨�ȣ����������ң���ǧ�У��������줿nu i me wa to ke te hi ki chi gi re ta��_���^���ɷ����󣨤ˣ������������ä��ǥ����� ���𣨤��Τ��ӣ���ã�������ni e ta tta de i zu de i no chi bi wo ta tsu���v��DAYS �ü��������l�����죩���äƤ����Τ� �����������ˤʤ��da re da tte i i no sa ka wa ri ni na re ba�oՓ�l���� ��ɞ������";
	/*
	memset(buf, 0, 25501);
	char* p = buf;
	for (int i = 1; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			*p = (char)i;
			p++;
		}
	}
	string s(buf);
	*/
	HuffmanEncoder mEncoder;
	mEncoder.init(s);
	mEncoder.encode();
	cin.get();
	return 0;
}