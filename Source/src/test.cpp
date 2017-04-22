/* test.cpp
テスト用プログラム.
実際の完成品には取り込まない.
*/

#include <iostream>
#include <string>
#include <vector>

#include "./firewall/check_in_denger_list.cpp"

/* --- テスト用プログラム --- */
int main()
{
  // 変数の初期化
  std::string test_string = "hogehoge";
  std::vector<std::string> test_list = {"a","b","c"};

  // 文字のチェック
  CheckInDengerList *check_in_denger_list;
  check_in_denger_list = new CheckInDengerList(&test_string,&test_list);
  std::cout << check_in_denger_list->isSafe() << std::endl;

  // メモリの確保
  delete check_in_denger_list;
}
