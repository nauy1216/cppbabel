#!/bin/bash

if [ -f CMakeCache.txt ]
then
  echo -e "\033[36m 存在CMakeCache.txt文件 \033[0m"
  mv  CMakeCache.txt  CMakeCache.txt.bak
fi

if [ ! -d dist ] 
then 
 echo -e "\033[36m dist不存在，创建dist \033[0m"
 mkdir dist
fi

cd ./dist && cmake .. && make

# 构建完之后恢复CMakeCache_bak.txt
cd ..
if [ -f CMakeCache.txt.bak ]
then
  echo -e "\033[36m 存在CMakeCache_bak.txt文件 \033[0m"
  mv CMakeCache.txt.bak CMakeCache.txt
fi

