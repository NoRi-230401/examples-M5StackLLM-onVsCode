# examples-M5StackLLM-onVsCode

VsCode環境下で M5Stack LLM-Module のサンプルソフトを動かしたい方へ<br>
次のリンク先の公式examplesをVsCode環境用にすぐに試用できるようにしたものです。<br>
 https://github.com/m5stack/M5Module-LLM/tree/main/examples

<br>
<br>

## examples
公式examples（ソフト６本）
<b>
- KWS_ASR<br>
- SerialTextAssistant<br>
- TextAssistant<br>
- TTS<br>
- VoiceAssistant<br>
- YOLO<br>
</b>
<br><br>

SerialTextAssistantを日本語表示できるように修正したソフト<br>
- <b>SerialTextAssistant-jp</b><br>
<br>
全部で７本のソフトを用意しました。<br>
<br>
<br>

## 使用方法

<b>src/main.cpp 内のコメントをはずしてコンパイルする</b><br>
<br><br>
<b>（例）"TTS.cpp"をコンパイルする場合</b><br>
<br>
// #include "../examples/KWS_ASR.cpp"<br>
// #include "../examples/SerialTextAssistant.cpp"<br>
// #include "../examples//TextAssistant.cpp"<br>
#include "../examples/TTS.cpp"<br>
// #include "../examples/VoiceAssistant.cpp"<br>
// #include "../examples/YOLO.cpp"<br>
// #include "../examples/SerialTextAssistant-jp.cpp"<br>
<br>
コメントに（する／はずす）だけで７本のソフトを簡単に試すことができます。<br>
<br>
<br>

## 対応機種
LLM-Moduleと繋ぐM5Stack本体の機種は、次の３種に対応しています。<br>
<b>M5Stack Basic</b><br>
<b>M5Stack Core2</b> <br>
<b>M5Stack CoreS3</b><br>

<br>
platformio.ini で機種ごとに対応したものを用意しています。<br>
<b>VsCodeの下部の「Switch PlatformIO Project enviroment」</b>で選択してご使用ください。<br>
VsCodeで下図の赤枠の付近を押すと切替えることができます。<br>
<br>

![画像](images/env00.png)<br>
<br>
M5Stack Basic  ->  <b>[env:m5stack-basic]</b><br>
M5Stack Core2  ->  <b>[env:m5stack-core2]</b><br>
M5Stack CoreS3 ->  <b>[env:m5stack-cores3]</b><br>
<br>

<b>
※ M5Stack Core2(for AWS)を使用して動作確認を実施しています。<br>
BASIC および CoreS3での確認をおこなっていませんのでご了承ください。<br>
不具合等があった場合には、「X」にてご連絡いただければ幸いです。<br>
</b>
<br>


<br>

## SD-Updater対応
M5Stack Core2(Ver1.0 and AWS) 用ですが、SD-Updater対応版にすることができます。<br>
VsCodeの下部の「Switch PlatformIO Project enviroment」で
<b>[env:m5stack-core2-sdu]</b> を選択してください。<br>
<br>
コンパイル後に ".pio/m5stack-core2-sdu"フォルダ下にfirmware.binが作成されます。<br>
名前を変えSD直下に設置すると他SD-Updater対応ソフトと切替えて使用することができます。<br>
<br>
SD-Updater対応の他ソフトは、下記リンクから取得することができます。<br>
https://github.com/NoRi-230401/BinsPack-for-StackChan-Core2<br>
<br>


