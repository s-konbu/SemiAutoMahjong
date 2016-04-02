#include "iodefine.h"
#include "Serial.h"

//==============================================================================
// S C I
//==============================================================================

#define buff_size_SCI1 64
typedef struct
{
  unsigned short read;
  unsigned short write;
  char buff[buff_size_SCI1];
}SCI_FIFO;

static SCI_FIFO tx1;


void init_SCI1(void)
{
  long i;

  STB.CR3.BIT._SCI1 = 0;	//クロック供給

  SCI1.SCSCR.BIT.TIE = 0; // 送信割込み:許可(1)/禁止(0)
  SCI1.SCSCR.BIT.RIE = 0; // 受信割込み:許可(1)/禁止(0)
  SCI2.SCSCR.BIT.TE  = 0; // 送信動作:許可(1)/禁止(0)
  SCI1.SCSCR.BIT.RE  = 0; // 受信動作:許可(1)/禁止(0)
  SCI1.SCSCR.BIT.MPIE = 0;// MP割込みイネーブル
  SCI1.SCSCR.BIT.TEIE = 0;// 送信終了割込み:許可(1)/禁止(0)

  SCI1.SCSCR.BIT.CKE  = 0;// クロックソース選択　調歩なので内部

  SCI1.SCSMR.BIT.CA   = 0;// 0:調歩同期、1:クロック同期
  SCI1.SCSMR.BIT.CHR  = 0;// 0:8ビットデータ、1:7ビットデータ
  SCI1.SCSMR.BIT._PE  = 0;// 0:パリティ禁止、1:パリティ許可
  SCI1.SCSMR.BIT.OE   = 0;// 0:偶数パリティ、1:奇数パリティ
  SCI1.SCSMR.BIT.STOP = 0;// 0:1ストップビット、1:2ストップビット
  SCI1.SCSMR.BIT.MP   = 0;// マルチプロセッサモード 0:禁止,1:許可
  SCI1.SCSMR.BIT.CKS  = 0;// クロックセレクト 00:1/1 , 01:1/4 , 10:1/16 , 11:1/64

  SCI1.SCBRR = 19;        //ボーレート 38400 bps

  for(i = 0;i<(SCI1.SCBRR*100*1);i++);//1bit期間待つ


  // TXD端子設定
  PFC.PACRL2.BIT.PA4MD= 1;// 000:PA4,001:TXD1,111:IRQ2
  PFC.PAIORL.BIT.B4 = 1;	//PA4を出力端子に

  // RXD端子設定
  //    PFC.PACRL1.BIT.PA3MD= 1;// 000:PA3,001:RXD1,111:IRQ1
  //	PFC.PAIORL.BIT.B3 = 0;	//PA4を入力端子に

  SCI1.SCSCR.BIT.TIE = 0; // 送信割込み:許可(1)/禁止(0)
  SCI1.SCSCR.BIT.RIE = 0; // 受信割込み:許可(1)/禁止(0)
  SCI1.SCSCR.BIT.TE  = 1; // 送信動作:許可(1)/禁止(0)
  SCI1.SCSCR.BIT.RE  = 1; // 受信動作:許可(1)/禁止(0)
  SCI1.SCSCR.BIT.MPIE = 0;// MP割込みイネーブル
  SCI1.SCSCR.BIT.TEIE = 0;// 送信終了割込み:許可(1)/禁止(0)

  INTC.IPRL.BIT._SCI1 = 1;

  tx1.read = 0;
  tx1.write = 0;

}
void test_SCI1(char c)	//一文字送信できるのかのテスト
{
  while(!SCI1.SCSSR.BIT.TDRE);
  SCI1.SCTDR = c;
  SCI1.SCSSR.BIT.TDRE = 0;
  while(!SCI1.SCSSR.BIT.TEND);
}

void interrpt_SCI1_TXI(void)
{
  char c;

  if(tx1.read != tx1.write)//データが溜まっているか
  {					//たまってる
    c = tx1.buff[tx1.read];
    tx1.read = inc_buff(tx1.read);
    SCI1.SCTDR = c;
    SCI1.SCSSR.BIT.TDRE = 0;//割り込みフラグクリア
  }else{				//もう空だね
    SCI1.SCSCR.BIT.TIE = 0;
  }
}

unsigned short inc_buff(unsigned short p)
{
  if(p < (buff_size_SCI1 -1))
  {
    p++;
  }else{
    p = 0;
  }
  return p;
}

void putc_SCI1(char c)
{
  unsigned short next_write = inc_buff(tx1.write);
  while(next_write == tx1.read);//バッファがあくま

  tx1.buff[tx1.write] = c;
  tx1.write = next_write;

  if(!SCI1.SCSCR.BIT.TIE)	//割り込みがOFFだったら
  {
    SCI1.SCSCR.BIT.TIE = 1;//割り込み許可TDREの初期値は1なのですぐ割り込みが発生する
  }
}

void puts_SCI1(char *str)
{
  while(*str != '\0')
  {
    putc_SCI1(*str);
    str++;
  }
}
