FROM ubuntu:16.04

RUN apt-get update
RUN apt-get -y install make cmake gcc g++

# livlinear周りのインストール
RUN apt-get -y install liblinear-dev liblinear-tools liblinear3
# livsvm周りのインストール
RUN apt-get install -y libsvm-dev libsvm-tools libsvm3


# プロジェクト追加
ENV APP_DIR  /home/svm_sample
RUN mkdir -p $APP_DIR
ADD . $APP_DIR
WORKDIR $APP_DIR

# サンプルプログラムのビルド
RUN make
