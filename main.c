#define DEBUG_MODE  // デバッグ時以外はコメントアウトすること！

#include "gamedef.c"


int main(int argc, char *argv[]) {
    // 引数の個数をチェック
    if (argc != 2) {
        puts("the number of command line arguments must be 2.");
        return -1;
    }

    // 先手か後手か
    int is_user_first;
    if (!strcmp(argv[1], "0")) {
        is_user_first = 1;
    } else if (!strcmp(argv[1], "1")) {
        is_user_first = 0;
    } else {
        puts("invalid command line argument.");
        return -1;
    }

    // 盤面を宣言し、初期化する
    Board b;
    init_board(&b, is_user_first);
    print_board_for_debug(&b);

    // ゲームのループをまわし、勝者を決める
    int winner;
    if (is_user_first) {
        for (int i = 0; i < 150; i += 2) {  // 150手以内
            //
            // ここは後々推敲する
            //
        }
    } else {
        for (int i = 0; i < 150; i += 2) {
            //
            // 同上
            //
        }
    }

    //
    // 勝ち負けの表示
    //

    return 0;
}