#!/bin/bash

# Check if the 'out' directory exists, if not, create it
if [ ! -d "output" ]; then
    mkdir output
fi

# Execute commands based on the input argument
if [ "$1" == "3" ]; then
    python3 03-print_24layers.py > output/03.txt
elif [ "$1" == "4" ]; then
    python3 04-print_1layer.py > output/04.txt
elif [ "$1" == "5" ]; then
    g++ -std=c++11  -o output/load_tensor 05-load_tensor.cpp && ./output/load_tensor
elif [ "$1" == "6" ]; then
    rm -rf output/06-python_gold/*
    python3 06-store_1layer.py > output/06.txt
elif [ "$1" == "7" ]; then
    rm -rf 07-cpp_out/*
    g++ -std=c++11  -o output/load_1layer 07-load_1layer.cpp && ./output/load_1layer
elif [ "$1" == "8" ]; then
    rm -rf output/07-cpp_out/*
    g++ -std=c++17  -o output/mergenorm1dense2 08-mergenorm1dense2.cpp && ./output/mergenorm1dense2
elif [ "$1" == "9" ]; then
    rm -rf 07-cpp_out/*
    g++ -std=c++11  -o output/norm_nobias 09-norm_nobias.cpp && ./output/norm_nobias
elif [ "$1" == "10" ]; then
    rm -rf 10-gold_384/*
    python3 10-store_1layer384.py > output/10.txt
elif [ "$1" == "11" ]; then
    rm -rf 11-cpp_out/*
    g++ -std=c++11  -o output/11 11-inputlen384.cpp && ./output/11
elif [ "$1" == "12" ]; then
    rm -rf 12-gold_384/*
    python3 12-24encoder384.py > output/12.txt
elif [ "$1" == "13" ]; then
    rm -rf 13-cpp_out/*
    g++ -std=c++11  -o output/13 13-24encoder384.cpp && ./output/13
else
    echo "Invalid input. Please use '4' or '3' as an argument."
fi