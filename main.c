#include "gamedef.c"


// debug_print関数を積極的に利用し、随所にエラーメッセージを散りばめること！

Board create_board(int is_user_first) {
    // Board型の盤面を作って初期化し、戻り値として返す
    // is_user_firstが1ならユーザーが先手、0ならAIが先手
}

Action get_user_action() {
    // ユーザー入力を受けて、その文字列をAction型の変数に翻訳して返す
    // 例えば"3CGI"が入力された場合、aをAction型の変数として
    //   a.from_stock = GI, a.to_x = 2, a.to_y = 2, a.turn_over = 0
    // となる。なお、この場合 a.from_x, a.from_y は何でも良い。
}

const char *move_piece(Board *b, Action action, const char *player) {
    // actionで示される行動をもとに、盤面bを変更する
    // player引数には"ai"または"user"が指定され、これは現在駒を動かしているプレイヤーを表す
    // この関数内で、種々のエラーチェックを行うが、エラー毎にdebug_printを徹底すること！
    // 駒を動かしたことにより決着がついた場合、勝者を表す文字列を返す
    // 例えばユーザーが勝った場合、 return "user"; とする
    // 勝敗が付いていなければ NULL を返す
    // 恐らくこの関数を書くのは大変 (課題のサイトの「反則手をさした場合」の項を参照)
    // さらに細分化する余地がありそう
}

Action get_ai_action(Board *b) {
    // 盤面bを受け取って、次にAIがどう打つべきかを決定する
    // 次の行動はAction型の変数にして返す
}

void display_action(Action action) {
    // actionの表す行動を、"2A3A"等の文字列に変換してプリントする
}

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

    // 初期化済みの盤面を作る
    Board b = create_board(is_user_first);
    print_board_for_debug(&b);

    // ゲームのループをまわし、勝者を決める
    const char *winner;
    if (is_user_first) {
        for (int i = 0; i < 150; i += 2) {  // 150手以内
            // ユーザーの行動を取ってきて駒を動かす
            Action user_action = get_user_action();
            winner = move_piece(&b, user_action, "user");
            print_board_for_debug(&b);
            if (winner != NULL)  // 決着が付いているか？
                break;

            // AIの行動を取ってきて駒を動かす
            Action ai_action = get_ai_action(&b);
            display_action(ai_action);
            winner = move_piece(&b, ai_action, "ai");
            print_board_for_debug(&b);
            if (winner != NULL)  // 決着が付いているか？
                break;
        }
    } else {
        for (int i = 0; i < 150; i += 2) {  // 以下同上
            Action ai_action = get_ai_action(&b);
            display_action(ai_action);
            winner = move_piece(&b, ai_action, "ai");
            print_board_for_debug(&b);
            if (winner != NULL)
                break;

            Action user_action = get_user_action();
            winner = move_piece(&b, user_action, "user");
            print_board_for_debug(&b);
            if (winner != NULL)
                break;
        }
    }

    // 勝敗の表示
    if (!strcmp(winner, "user")) {
        puts("You Win");
    } else if (!strcmp(winner, "ai")) {
        puts("You Lose");
    } else {
        puts("Draw");
    }

    return 0;
}