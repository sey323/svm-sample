/*
*name        :libsvm_sample.c
*auter       :Seiichirou Nomura
*discription :svm Learning
*date        :20161208-20170110
*/
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<sstream> //文字ストリーム


#include"svm.h"

using namespace std;

void count_row_col( const char* , int*, int*);
struct TRAIN_DATA *load_to_train( const char* );
svm_model *libsvm_data_make( const struct TRAIN_DATA* );
int libsvm_predict( const struct TRAIN_DATA*, const svm_model* );

//学習データ保存用の構造体
typedef struct TRAIN_DATA{
  int train_num;//学習に用いるデータ数
  double label;//教師用ラベル
  int data_num;//学習に用いる素性データ数
  double *data;//素性データの配列
}TRAIN_DATA;

/*
*CSVファイルの行と列を数える
*/
void count_row_col( const char *filename , int *row , int *col ){
  int col_num , row_num;

  //ファイルを読み込んで行列を数える
  ifstream ifs(filename);
  row_num = col_num = 0;
  if(!ifs){
    cout<<"入力エラー"<<endl;
  }else{
    string buf;
    while (getline(ifs, buf)) {
      istringstream stream(buf);
      string token;
      if(row_num == 0 ){//カンマ区切りで分割
        while ( getline( stream, token , ','))col_num++;
      }
      row_num++;
    }
  }
  //行列の値をポインタに渡す
  (*col) = col_num;
  (*row) = row_num;
}

/*
*CSVファイルから学習データを取得する
*/
struct TRAIN_DATA *load_to_train( const char *train_filename ){
  int row, col;
  struct TRAIN_DATA *t_data;

  //CSVファイルの行列を取得する
  count_row_col( train_filename , &row , &col );

  //学習に用いるデータを保存する配列の初期化
  t_data = (struct TRAIN_DATA* )malloc( sizeof(struct TRAIN_DATA) * row + 1);
  for( int i = 0 ; i < row ; i++ ){
    t_data[i].train_num = 0;
    t_data[i].label = 0;
    t_data[i].data_num = 0;
    t_data[i].data = (double* )malloc( sizeof(double) * (col - 1));
  }

  //csvファイルを1行ずつ読み込む
  ifstream ifs(train_filename);
  string buf;
  int i = 0 , j = 0;
  while(getline(ifs,buf)){
    t_data[i].train_num = row;
    t_data[i].data_num = col - 1;

    string token;
    istringstream stream(buf);
    //1行のうち、文字列とコンマを分割する
    while(getline(stream,token,',') ){
      double temp = (double)stod(token);
      if( j == 0 ){//行の先頭はラベルとして扱う
        t_data[i].label = temp;
      }else{
        //すべて文字列として読み込まれるためdouble型に変換
        t_data[i].data[j-1] = temp;
      }
      j++;
    }
    i++;
    j = 0;
  }
  return t_data;
}

/*
*特徴量から学習データの作成
*/
svm_model *libsvm_data_make( const struct TRAIN_DATA *t_data ){
  svm_problem prob;
  svm_node* prob_vec;

  //素性データ数
  int train_num = t_data[0].train_num;
  int data_num = t_data[0].data_num;

  cout << "learning datas :" << train_num << endl;

  //学習データの数
  prob.l = train_num;
  //学習データの数だけラベルを用意
  prob.x = new svm_node *[ prob.l ];
  //各学習データのラベル
  prob.y = new double[ prob.l ];
  prob_vec = new svm_node[  prob.l *  ( data_num + 1)  ];// 学習データの枚数 * 素性データ数　+ 特徴点のクトルの終端コード)
  for( int i = 0 ; i < prob.l; i++){
    //ラベルをふる
    prob.y[ i ] = t_data[i].label;
    prob.x[ i ] = prob_vec + i * ( data_num + 1);

    //データの数だけ繰り返す
    for( int j = 0; j < data_num; j++){
      prob.x[ i ][ j ].index = j;
      prob.x[ i ][ j ].value = t_data[ i ].data[ j ];
    }
    //末尾は-1
    prob.x[ i ][ data_num ].index = -1;
  }

  // 学習する識別器のパラメータ
  svm_parameter param;
  param.svm_type =  C_SVC;// SVCとかSVRとか
  param.kernel_type = LINEAR;// RBF（放射基底関数）カーネルとかLINEAR（線形）カーネルとかPOLY（多項式）カーネルとか
  param.C = 8096;// SVMにおけるコスト：大きいほどハードマージン
  param.gamma = 0.1;// カーネルとかで使われるパラメータ

  // その他
  param.coef0 = 0;
  param.cache_size = 100;
  param.eps = 1e-3;
  param.shrinking = 1;
  param.probability = 0;

  // その他状況（svm_typeやカーネル）に応じて必要なもの
  param.degree = 3;
  param.nu = 0.5;
  param.p = 0.1;
  param.nr_weight = 0;
  param.weight_label = nullptr;
  param.weight = nullptr;

  //学習する
  cout << "Ready to train ..." << endl;
  svm_model* model = svm_train( &prob, &param );
  cout << "Finished ..." << endl;

  //後始末
  delete[] prob.y;
  delete[] prob.x;
  delete[] prob_vec;
  svm_destroy_param(&param);

  return model;
}

/*
*libsvmによる検定
*/
int libsvm_predict( const struct TRAIN_DATA *t_data , const svm_model *model ){
  int data_num = t_data->data_num;
  svm_node test[ data_num ];

  cout << "predict training samples ..." << endl;

  for( int i = 0 ; i < data_num; i++){
    test[i].index = i;
    test[i].value = t_data->data[i];
  }
  test[data_num].index = -1;

  // libsvmによるpredict
  const auto result = static_cast<int>( svm_predict( model, test ) );

  return result;
}

/*
*実行関数
*/
int main(int argc, char* argv[])
{
  char train_filename[248] , svm_filename[248];

  //コンソール入力をpathに代入
  strcpy( train_filename, argv[ 1 ] );
  strcpy( svm_filename , argv[ 2 ] );

  //CSVファイルから学習データを作成
  struct TRAIN_DATA* t_data;
  t_data = load_to_train( train_filename );

  //学習データの作成
  svm_model* model = libsvm_data_make( t_data );
  // 学習結果のファイル出力
  svm_save_model( svm_filename , model );

  //テスト用データの作成
  struct TRAIN_DATA* test;
  test = (struct TRAIN_DATA* )malloc( sizeof(struct TRAIN_DATA));
  test->data = (double*)malloc( sizeof(double) * 10);
  test->data_num = 10;
  for(int j = 0; j < 10 ; j++){
    test->data[j] = 0.4;
  }

  //予測
  int result = libsvm_predict( test , model );
  cout << "done" << endl;
  cout << "RESULT : correct =" << result << endl;

  // 後始末
  free(t_data);
  free(test);
  svm_free_and_destroy_model( &model );

  return 0;
}
