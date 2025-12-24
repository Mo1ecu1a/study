#!/bin/bash

BUILD_TUPE="Ninja"
BUILD_SUFFIX="ninja"
BUILD_FOLDER="build_$BUILD_SUFFIX"
SOURCE_FOLDER="Source"

if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"
cmake -G "$BUILD_TUPE" "../$SOURCE_FOLDER"
cmake --build .

arr[0]="build_sort.bat"
arr[1]="build_soft.bat"
arr_folder[0]="bubble_soft"
arr_folder[1]="menu_soft"

for i in 0 1; do
    cp "../$SOURCE_FOLDER/${arr_folder[$i]}/${arr[$i]}" "${arr_folder[$i]}"
done

cp "../run_tests.bat" .
