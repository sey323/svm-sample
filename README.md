# svm-sample

## 概要

c＋＋でsvmを実行する場合のサンプルコードです。

利用方法は下記のURLの記事を参照してください。

- [DockerでC++のsvmの開発環境を構築する(1)](https://qiita.com/sey323/items/40d37d93a66ac76619f1)
- [DockerでC++のsvmの開発環境を構築する(2)](https://qiita.com/sey323/items/1b2ad744a32c0843744a)

## QuickStart

### ローカルで実行する場合

libsvm

`g++ -g -Wall -std=c++0x -I{lib-svmのフォルダパス}/include -L{lib-svmのフォルダパス}/lib libsvm_sample.cpp -lsvm`

liblinear  

`g++ -g -Wall -std=c++0x -I{lib-linearのフォルダパス}/include -L{lib-linearのフォルダパス}/lib libsvm_sample.cpp -llinear`


## Docker

### Dockerのビルド

~~~
docker build -t svm:0.1 .
~~~

### Dockerの実行

~~~
docker run --rm -v `pwd`:/home/svm_sample -it svm:0.1 /bin/bash
~~~
