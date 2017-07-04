FROM ubuntu:14.04

RUN apt-get update
RUN apt-get -y install make cmake gcc g++

# liblinearのインストール
RUN wget 'http://www.csie.ntu.edu.tw/~cjlin/cgi-bin/liblinear.cgi?+http://www.csie.ntu.edu.tw/~cjlin/liblinear+tar.gz' -O liblinear.tar.gz && tar xzvf liblinear.tar.gz
RUN cd liblinear-2.01 && make

# プロジェクト追加
ENV APP_DIR  /home/libliner_sample
RUN mkdir -p $APP_DIR
ADD . $APP_DIR
WORKDIR $APP_DIR

# 環境変数の追加
#ENV LINEARINC /usr/include/libliner
#ENV LINEARLIB /usr/lib
#RUN make
