#!/bin/bash

if [ -f ./CMakeLists.txt ]
then
  build_dir='./build'
  rm -rf $build_dir
else
  echo "You are not inside a project!"
fi
