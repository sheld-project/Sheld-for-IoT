/* check_in_denger_list.cpp
事前にセットされた危険な文字列リストの値が
ターゲットに含まれていないか確認するプログラム
*/

#include <iostream>
#include <string>
#include <vector>


/* --- 指定された文字列が存在するか確認するプログラム --- */
class CheckInDengerList
{
private:
  // 安全か確認される側の（ターゲットの）データ
  std::string TargetString;
  // 事前に決められた危険な文字列リスト
  std::vector<std::string> DengerStringList;

public:
  /* クラス変数の初期化 */
  CheckInDengerList(
    // 引数としてのTargetString
    std::string arg_target,
    // 引数としてのDengerStringList
    std::vector<std::string> arg_list
  )
  {
    // プロパティの設定
    TargetString = arg_target;
    DengerStringList = arg_list;
  }

  /* TargetString内に、DengerStringListに
  格納された文字列が含まれていないか確認する */
  bool isSafe(){
      for(std::string denger_string : DengerStringList){
        // ヒットするか調べる（-1でノーヒット）
        int hit_count = (int)TargetString.find(denger_string);
        // ヒットした時
        if(hit_count != -1){
          return false;
        }
      }
      // 何もヒットしなかった時
      return true;
    }

    /* デストラクタの追加 */
  ~CheckInDengerList(){

  }
};
