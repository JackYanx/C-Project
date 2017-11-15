#include "commen.h"
#include "HuffmanEncoder.h"
char buf[25501];
int main() {
	//6个1,5个2,4个3,3个4,2个5,1个6,共计21个字符
	//string s = "111211122232345334564";// , JNIEXPORT void JNICALL Java_org_andengine_opengl_util_BufferUtils_jniPut(JNIEnv *env, jclass, jobject pBuffer, jfloatArray pData, jint pLength, jint pOffset), 苟利国家生死以, 起因祸福避趋之, 私はあなたを愛しでます";
	string s = "作词：押入れP 作曲：押入れP 编曲：押入れP 呗：镜音リン 父（とう）さん母（かあ）さん 今（いま）までごめんto u sa n ka a sa n i ma ma de go me n爸爸媽媽 至今為止麻煩了膝（ひざ）を震（ふる）わせ 親指（おやゆび）しゃぶるhi za wo fu ru wa se o ya yu bi sha bu ru哆嗦著膝蓋 咬著大拇指兄（にい）さん姉（ねえ）さん それじゃあまたね ni i sa n ne e sa nso re ja a ma ta ne哥哥姐姐 那麼再見吧冴（さ）えない靴（くつ）の 踵（かかと）潰（つぶ）した sa e na i ku tsu no ka ka to tsu bu shi ta磨損的鞋子 擦破腳後跟見（み）え張（は）ったサイズで 型紙（かたがみ）を取（と）るmi e ha tta sa i zu de ka ta ga mi wo to ru誇張顯眼的尺寸下剪著紙何（なん）だっていいのさ 代（か）わりになれば nan da tte i i no sa ka wa ri ni na re ba那麼做成什麼樣才好呢愛（あい）されたいと 口（くち）を零（こぼ）したa i sa re ta i to ku chi wo ko bo shi ta念著好想被愛もっと丈夫（じょうぶ）な ハサミで mo tto jo u bu na ha sa mi de用更結實的剪刀顔（かお）を切（き）り取（と）るのさka o wo ki ri to ru no sa剪下這張臉吧全智全能（ぜんちぜんのう）の言葉（ことば）を ほら聞（き）かせてよ ze n chi ze n no u no ko to ba wo ho ra ki ka se te yo來讓我聽聽全智全能的話語吧脳（のう）みそ以外（いがい） もういらないとwhy not I don't knowno u mi so i ga i mo u i ra na i to  why not I don't know 頭腦以外再無需要近未来（きんみらい）創造（そうぞう） 明日（あす）の傷創（しょうそう） ただ揺（ゆ） らしてよki n mi ra i so u zo u a su no sho u so u ta da yu ra shi te yo近未來創造 明天的創傷 就這樣搖動吧 縫（ぬ）い目（め）の隙間（すきま）を埋（う）めておくれ nu i me no su ki ma wo u me te o ku re去埋入介面的縫隙間皆（みな）さんさようなら 先生（せんせい）お元気（げんき）で mi na sa n sa yo u na ra se n se i o ge n ki de大家再見了 老師保重啊高（たか）なった胸（むね）に 涎（よだれ）が垂（た）れるta ka na tta mu ne ni  yo da re ga ta re ru高鳴的胸中 淌下著口水正直者（しょうじきもの）は何（なに）を見（み）る？正直者（しょうじきもの）は馬 鹿（ばか）を見（み）る！sho u ji ki mo no wa na ni wo mi rusho u ji ki mo n owa ba ka wo mi ru老實人看著什麼？ 老實人看著笨蛋呢！正直者（しょうじきもの）は何（なに）を見（み）る？正直者（しょうじきもの）は馬 鹿（ばか）を見（み）る！sho u ji ki mo no wa na ni wo mi rusho u ji ki mo n owa ba ka wo mi ru老實人看著什麼？ 老實人看著笨蛋呢！あー、これじゃまだ足（た）りないよ a a ko re ja ma da ta ri na i yo啊，這樣還不夠哦もっと大（おお）きな ミシンで 心（こころ）貫（つらぬ）くのさmo tto o o ki na mi shi n de ko ko ro tsu ra nu ku no sa用再大一點的縫紉機 貫穿心臟吧全智全能（ぜんちぜんのう）の言葉（ことば）を ほら聞（き）かせてよze n chi ze n no u no ko to ba wo ho ra ki ka se te yo來讓我聽聽全智全能的話語吧脳（のう）みそ以外（いがい） もういらないと why not I don't knowno u mi so i ga i mo u i ra na i to  why not I don't know頭腦以外再無需要   why not, I don't know近未来（きんみらい）創造（そうぞう） 明日（あす）の傷創（しょうそう） ただ揺（ゆ） らしてよki n mi ra i so u zo u a su no sho u so u ta da yu ra shi te yo 近未來創造 明天的創傷 就這樣搖動吧縫（ぬ）い目（め）の隙間（すきま）を埋（う）めておくれnu i me no su ki ma wo u me te o ku re去埋入介面的縫隙間もう何（なに）も無（な）いよ 何（なに）も無（な）いよ 引（ひ）き剥（は）がされ てmo u na ni mo na i yo na ni mo na i yo hi ki ha ga sa re te已經一無所有啊 一無所有啊 被扯下來糸屑（いとくず）の 海（うみ）へと この細胞（さいぼう）もi to ku zu no u mi e to ko no sa i bo u mo這些細胞也向著線頭的海洋そうボクいないよ ボクいないよ 投（な）げ捨（す）てられてso u bo ku i na i yo bo ku i na i yo na ge su te ra re te是啊我不在了呢 我不在了呢 被丟棄了帰（かえ）る場所（ばしょ）すら何処（どこ）にも 無（な）いんだよka e ru ba sho su ra do ko ni mo na i n da yo就連回去的地方也不存在呢存在（そんざい）証明（しょうめい）。 あー、shut up ウソだらけの体（からだ）so n za i sho u me i a a shut up u so da ra ke no ka ra da存在證明。啊，shut up 充滿謊言的身體完成（かんせい）したいよ ズルしたいよ 今（いま）、解答（かいとう）を ka n se i shi ta i yo zu ru shi ta i yo i ma ka i to u wo好想完成啊 好想瞞騙過 現在將那解答変（か）われないの？ 飼（か）われたいの？ka wa re na i no ka wa re ta i no無法改變嗎？想被飼養嗎？何（なに）も無（な）い？ こんなのボクじゃない！na ni mo na i ko n na no bo ku ja nai一無所有嗎？這都不是我！縫（ぬ）い目（め）は解（と）けて引（ひ）き千切（ちぎ）れたnu i me wa to ke te hi ki chi gi re ta鬆開線頭扯成粉碎煮（に）え立（た）ったデイズで 命火（いのちび）を裁（た）つni e ta tta de i zu de i no chi bi wo ta tsu沸騰的DAYS 裁剪著生命誰（だれ）だっていいのさ 代（か）わりになればda re da tte i i no sa ka wa ri ni na re ba無論誰都好 來成為替代吧";
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