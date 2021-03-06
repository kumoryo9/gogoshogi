#ifndef GAMEDEF
#define GAMEDEF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define DEBUG_MODE  // デバッグ時以外はコメントアウトすること！


/************************
 * 定数および構造体の定義
 ************************/

#define USER  1   // これらはユーザーとAIを表す定数であり、変更しない事とする
#define AI    -1  // よって、これらの具体値に依存するコードを書いても良い

#define FU    1
#define KIN   2
#define GIN   3
#define KAKU  4
#define HISHA 5
#define OU    6
#define NARI  8  // 例えば歩が成った場合は FU + NARI と書く

typedef struct {        // 盤面を(持ち駒とセットで)入れておく構造体
    int board[5][5];    // 盤面
    int user_stock[7];  // ユーザーの持ち駒
    int ai_stock[7];    // AIの持ち駒
    int next_player;    // 次に駒を打つプレイヤー ( AI または USER )
} Board;

typedef struct {     // 駒の移動を表す構造体
    int from_stock;  // 持ち駒を打つ場合その種類、打たない場合0
    int from_x;      // 既存の駒を動かす場合のもとの座標
    int from_y;      // 持ち駒を打つ場合は何でも良い
    int to_x;        // 駒の移動先の座標
    int to_y;
    int turn_over;   // 移動後に成るか否か
} Action;


/*****************************
 * ユーティリティー関数の定義
 *   - debug_print
 *   - print_board_for_debug
 *   - abort_game
 *****************************/

void debug_print(const char *msg, ...) {
    // デバッグプリント用の関数
    // ほぼprintf関数と変わらないが、末尾に改行が入る
    // #define DEBUG_MODE としてDEBUG_MODEを定義すればデバッグプリントが有効になる

#ifdef DEBUG_MODE
    va_list ap;
    va_start(ap, msg);
    vprintf(msg, ap);
    puts("");
    fflush(stdin);
    va_end(ap);
#endif  /* DEBUG_MODE */
}

void print_board_for_debug(Board *b) {
    // 盤面をプリントするデバッグ用の関数
    // "全"は成銀を、赤字は相手の駒を表す

#ifdef DEBUG_MODE
    static const char *piece_ch[] = {
            "　", "歩", "金", "銀", "角", "飛", "王",
            "??", "??", "と", "??", "全", "馬", "龍", "??",
    };

    // 盤面のプリント
    puts("  ＡＢＣＤＥ");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", 5 - i);
        for (int j = 0; j < 5; ++j) {
            int piece = b->board[i][j];

            // ユーザーの駒かAIの駒かによって色を変える
            if (piece < 0) {
                printf("\x1b[31m");
            } else {
                printf("\x1b[39m");
            }

            printf("%s", piece_ch[abs(piece)]);
        }
        printf("\x1b[39m\n");
    }

    // ユーザーの持ち駒のプリント
    puts("");
    printf("user: ");
    for (int piece = 0; piece < 7; ++piece) {
        int count = b->user_stock[piece];
        for (int i = 0; i < count; ++i)
            printf("%s", piece_ch[piece]);
    }

    // AIの持ち駒のプリント
    puts("");
    printf("ai  : ");
    for (int piece = 0; piece < 7; ++piece) {
        int count = b->ai_stock[piece];
        for (int i = 0; i < count; ++i)
            printf("%s", piece_ch[piece]);
    }

    printf("\n\n");
#endif  /* DEBUG_MODE */
}

void abort_game(int loser) {
    // ゲームを強制終了する
    // loser引数には USER または AI を指定し、これは敗者を表す
    // この関数はエラー時の強制終了に用いることが望ましい

    debug_print("abort called.");

    if (loser == AI) {
        puts("You Win");
    } else if (loser == USER) {
        puts("You Lose");
    } else {
        debug_print("unknown value of the argument loser: %d", loser);
    }

    exit(1);
}


#endif  /* GAMEDEF */