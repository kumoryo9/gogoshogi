#ifndef GAMEDEF
#define GAMEDEF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


/************************
 * 定数および構造体の定義
 ************************/

#define FU    1
#define KIN   2
#define GIN   3
#define KAKU  4
#define HISHA 5
#define OU    6
#define NARI  8  // 例えば歩が成った場合は FU + NARI と書く

typedef struct {         // 盤面を(持ち駒とセットで)入れておく構造体
    int board[5][5];     // 盤面
    int user_pieces[7];  // ユーザーの持ち駒
    int ai_pieces[7];    // AIの持ち駒
} Board;


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
    // "NG"は成銀を、赤字は相手の駒を表す

#ifdef DEBUG_MODE
    static const char *piece_ch[] = {
            "　", "歩", "金", "銀", "角", "飛", "王",
            "??", "??", "と", "??", "NG", "馬", "龍", "??",
    };

    // 盤面のプリント
    puts("  ＡＢＣＤＥ");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", i + 1);
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
        puts("");
    }

    // ユーザーの持ち駒のプリント
    puts("");
    printf("user: ");
    for (int piece = 0; piece < 7; ++piece) {
        int count = b->user_pieces[piece];
        for (int i = 0; i < count; ++i)
            printf("%s", piece_ch[piece]);
    }

    // AIの持ち駒のプリント
    puts("");
    printf("ai  : ");
    for (int piece = 0; piece < 7; ++piece) {
        int count = b->ai_pieces[piece];
        for (int i = 0; i < count; ++i)
            printf("%s", piece_ch[piece]);
    }

    printf("\n\n");
#endif  /* DEBUG_MODE */
}

void abort_game(const char *loser) {
    // ゲームを強制終了する
    // loser引数には敗者を文字列で指定し、その値は"ai"または"user"とする

    debug_print("abort called.");

    if (!strcmp(loser, "user")) {
        puts("You Lose");
    } else if (!strcmp(loser, "ai")) {
        puts("You Win");
    } else {
        debug_print("unknown value of the argument loser: %s", loser);
    }

    exit(1);
}


#endif  /* GAMEDEF */