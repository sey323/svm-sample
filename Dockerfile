FROM ubuntu:16.04

RUN apt-get update
RUN apt-get -y install make cmake gcc g++

# liblinear周りのインストール
RUN apt-get -y install liblinear-dev liblinear-tools liblinear3
# libsvm周りのインストール
RUN apt-get -y install libsvm-dev libsvm-tools libsvm3

# プロジェクト追加
ENV APP_DIR  /home/svm_sample
RUN mkdir -p $APP_DIR
WORKDIR $APP_DIR
