# このプロジェクトについて

IS22erの7班によるボードゲーム「5五将棋」用のAIです。  
ヘッダーファイルやMakefileは作らず、ソースコードを直接includeします。  
(例) `#include "hogehoge.c"`

# コードを書く上での取り決め

盤面は5×5の二次元配列で表し、空きマス、歩、金、銀、角、飛車、王の順に0, 1, 2, 3, 4, 5, 6とする。  
また、歩、銀、角、飛車が成った場合8を足す事とする。(代案があれば変更される可能性あり)  
以上の定数はマクロにしておくので、基本的にはマクロを使い可読性を上げるようにする。  
(例) `#define FU 1`

コード中では、5×5の盤面と持ち駒を入れる配列2つを構造体を用いて一纏めにして扱う。  
持ち駒を入れる配列は7個の要素を持つ配列(例: `int pieces[7]`)とし、インデックスをその駒を表す数字、各要素をその駒の枚数とする。  
(例) 持ち駒として歩を二枚持っているとき: `pieces[FU] = 2`

座標の取り方は以下。("2A3A"等の文字列と下のXY座標との変換は入出力の際に行う)  
![ジオメトリ](https://user-images.githubusercontent.com/79792475/142727582-45234b19-c525-463a-aea4-45e7ef3e4ed7.png)

# AIの取る戦略

評価関数を使う？  
詳細は未定。
