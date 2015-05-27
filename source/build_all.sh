#!/bin/bash
base_dir='../../bin'
build_script="build_release.sh"
while getopts rdDhc name
do
        case $name in
          d)build_script="build_debug.sh";;
          D)build_script="build_doc.sh";;
          h)echo "$0 [-d(ebug)|-r(elease)|-D(oc)|-c(lean)]";;
          c)build_script="clean.sh";;
          *)echo "Invalid arg! see -h for help";;
        esac
done

cd debug_util
$base_dir/$build_script
cd -

cd hrir
$base_dir/$build_script
cd -

cd ai_evol
$base_dir/$build_script
cd -

cd shrir
$base_dir/$build_script
cd -



