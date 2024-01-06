#include <MJScore.h>

#define BAUDRATE                (115200)

MJScore score;

int tehai[MJSCORE_INPUT_TEHAI_NUM];  //手牌
int fuuro[20];  //フーロ
int dora[11];   //ドラ

void set() {
	/*          手牌等の情報入力         */
	/***************************************************/
	//初期化
	memset(tehai,0,sizeof(tehai));
	memset(fuuro,0,sizeof(fuuro));
	memset(dora,0,sizeof(dora));

	//ドラ
  // 表示牌の枚数
	dora[0] = 0;

  // 1～5枚目のドラ表示牌
  dora[1] = 0;
  dora[2] = 0;
  dora[3] = 0;
  dora[4] = 0;
	dora[5] = 0;

  // 1～5枚目の裏ドラ表示牌
  dora[6] = 0;  
  dora[7] = 0;
  dora[8] = 0;
  dora[9] = 0;
  dora[10] = 0;

	//手牌
  // 萬子 (0, 10 は未定義)
  tehai[1] = 0;
  tehai[2] = 0;
  tehai[3] = 0;
  tehai[4] = 0;
  tehai[5] = 0;
  tehai[6] = 0;
  tehai[7] = 0;
  tehai[8] = 0;
  tehai[9] = 0;

  // 筒子 (20 は未定義)
	tehai[11] = 0;
  tehai[12] = 0;
  tehai[13] = 1;
  tehai[14] = 1;
  tehai[15] = 1;
  tehai[16] = 0;
  tehai[17] = 3;
  tehai[18] = 0;
  tehai[19] = 0;

  // 索子 (30 は未定義)
	tehai[21] = 0;
  tehai[22] = 3;
  tehai[23] = 0;
  tehai[24] = 0;
  tehai[25] = 0;
  tehai[26] = 0;
  tehai[27] = 2;
  tehai[28] = 0;
  tehai[29] = 0;

  // 東南西北
	tehai[31] = 0;
  tehai[32] = 0;
  tehai[33] = 0;
  tehai[34] = 0;

  // 白發中
  tehai[35] = 0;
	tehai[36] = 0;
  tehai[37] = 0;

  // 赤の5萬・5筒・5索
	tehai[38] = 0;
  tehai[39] = 0;
  tehai[40] = 0;

	//フーロ牌
  fuuro[0] = MJScore::CHII;
  fuuro[1] = 2;
  fuuro[2] = 2;
  fuuro[3] = 3;
	/***************************************************/

	//ルール入力	
	score.Avail_Akahai(false); //赤牌有り
	score.Avail_Kuitan(true); //クイタン有り
	score.Avail_ManganKiriage(false); //満貫切り上げ有り	
	score.Avail_Ba1500(false); //場千五有り
	score.Avail_DoubleKokushi13(false); //国士13面待ちダブル役満有り
	score.Avail_DoubleTyuuren9(false);  //九連宝燈9面待ちダブル役満有り
	score.Avail_DoubleDaisuusii(false); //大四喜ダブル役満有り
	score.Avail_DoubleSuttan(false);  //四暗刻単騎ダブル役満有り

	//特殊役成立フラグ入力	
	score.Is_Riichi(false); //リーチ
	score.Is_Tenhou(false); //天和	
	score.Is_Tiihou(false); //地和	
	score.Is_DoubleRiichi(false); //ダブルリーチ	
	score.Is_Ippatu(false); //一発	
	score.Is_Tyankan(false);  //チャンカン	
	score.Is_Rinsyan(false);  //リンシャン	
	score.Is_NagashiMangan(false);  //流し満貫
	score.Is_Haitei(false); //ハイテイ

	//必須情報入力
	score.Set_Tehai(tehai); //手牌
	score.Set_Agarihai(15); //あがり牌
	score.Set_Bakaze(31);   //場風
	score.Set_Jikaze(32);   //自風

	//追加情報入力
	score.Set_Tumoagari(true);  //ツモあがりかどうか		
	score.Set_Honba(0); //N本場		
	score.Set_KyoutakuRIichi(0);  //供託リーチ
	score.Set_Fuuro(fuuro); //フーロ牌入力		
//	score.Set_Dora(dora); //ドラ牌入力
  score.Set_Dorasuu(2); //ドラ数入力
}

void setup() {
  Serial.begin(BAUDRATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  set();

	score.Run(); //実行

	//エラーコード取得
	//-1:未計算
	//0:正常終了
	//1:「非フーロ牌+フーロ数*3」が14枚でないor手牌に0未満か5以上のデータがある
	//2:あがり牌情報がないor手牌にあがり牌がない
	//3:あがっていない
	//4:場風か自風情報がない
	//5:鳴きリーチしている
	//6:役がない
  Serial.println(score.Get_ErrorCode());

	//結果
	//役名の配列取得
	string result[20];  //サイズは20以上
	score.Get_Yakuname(result); //参照渡し
	//表示
	for(int i=0; !result[i].empty(); i++) {
		Serial.print(result[i].c_str());
		if(score.Get_Fan() < MJScore::YAKUMAN) {
      Serial.print("飜");
    }
    Serial.println();
	}

	//結果取得
  Serial.print("親ツモ＝"); Serial.println(score.Get_OyaTumo()); //親ツモ
	Serial.print("親ロン＝"); Serial.println(score.Get_OyaRon());  //親ロン
  Serial.print("子ツモ親＝"); Serial.println(score.Get_KoTumoOya());  //子ツモ親
	Serial.print("子ツモ子＝"); Serial.println(score.Get_KoTumoKo()); //子ツモ子
	Serial.print("子ロン＝"); Serial.println(score.Get_KoRon());  //子ロン
	Serial.print("符＝"); Serial.println(score.Get_Fu()); //符 -1で符が関係無い役
	Serial.print("役数＝"); Serial.println(score.Get_Fan());  //役数
	Serial.print("ドラ数(裏、赤除く)＝"); Serial.println(score.Get_Dorasuu());  //ドラ数(赤除く)
	Serial.print("裏ドラ数＝"); Serial.println(score.Get_Uradorasuu()); //裏ドラ数
	Serial.print("赤ドラ数＝"); Serial.println(score.Get_Akadorasuu()); //赤ドラ数		
	Serial.print("最終的に親が貰う点数（ロン）＝"); Serial.println(score.Get_TokutenOya()); //最終的に親が貰う点数（ロン）		
	Serial.print("最終的に子が貰う点数（ロン）＝"); Serial.println(score.Get_TokutenKo());  //最終的に子が貰う点数（ロン）		
	Serial.print("最終的に親が貰う点数（ツモ）＝"); Serial.println(score.Get_TokutenOyaTumo()); //最終的に親が貰う点数（ツモ）	
	Serial.print("最終的に子が貰う点数（ツモ）＝"); Serial.println(score.Get_TokutenKoTumo());  //最終的に子が貰う点数（ツモ）		
	if(score.Get_Ismangan()) {
    Serial.println("満貫"); //満貫かどうか
  }

  Serial.println("役テーブル");
	bool yakutable[60];
	score.Get_Yakutable(yakutable);	 //成立役のテーブル
  for (int i = 0; i < 60; i++) {
    Serial.print(yakutable[i]);
  }
  Serial.println();
}

void loop() {
}
