## ローカルでコンパイル
###コンパイルオプション

libsvm

`g++ -g -Wall -std=c++0x -I{lib-svmのフォルダパス}/include -L{lib-svmのフォルダパス}/lib libsvm_sample.cpp -lsvm`

liblinear  

`g++ -g -Wall -std=c++0x -I{lib-linearのフォルダパス}/include -L{lib-linearのフォルダパス}/lib libsvm_sample.cpp -llinear`


## Docker
### Dockerのビルド
`docker build -t svm:0.1 .`

### Dockerの実行
`docker run -it --rm svm:0.1 /bin/bash`
