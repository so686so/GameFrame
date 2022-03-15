#!/bin/bash

echo -e "##### CLEAN CMAKE #####"

rm -vrf *.a
rm -rf CMakeFiles
rm -vrf cmake_install.cmake
rm -vrf CMakeCache.txt
rm -vrf install_manifest.txt

rm -vrf Makefile
rm -vrf runFile

echo -e "######## CLEAR ########"
