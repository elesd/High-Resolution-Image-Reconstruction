#!/bin/bash

if [ -f ./CMakeLists.txt ]
then
  project_script=`find ./ -name "PRO_*" | head -1`
  . $project_script
  if [ "$?" -eq "0" ]
  then 
    build_dir='./build/release'
    rm -rf $build_dir
    mkdir -p $build_dir
    cd $build_dir
    cmake -DCMAKE_BUILD_TYPE=Release ../../
    make install
  else
    echo "Environment initialisation failed"
  fi
else
  echo "You are not inside a project!"
fi
