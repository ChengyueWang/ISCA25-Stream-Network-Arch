#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <ctime>
#include <bitset>
#include <vector>
#include <iomanip>
#include "assert.h"
#include <math.h>

// g++ -std=c++11  -o cpp_out/load_tensor 05-load_tensor.cpp && ./cpp_out/load_tensor


void print_matrix_to_file(const std::string &filename, const float *matrix, int row, int col) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    // Print matrix size
    outFile << "Size: (" << row << ", " << col << ")\n";
    // Print column headers
    outFile << "      "; // Indentation for row headers
    for (int j = 0; j < col; j++) {
        outFile << std::setw(7) << j;
    }
    outFile << "\n";
    // Print matrix data with row headers
    for (int i = 0; i < row; i++) {
        outFile << std::setw(7) << i; // Row header
        for (int j = 0; j < col; j++) {
            outFile << std::setw(7) << std::fixed << std::setprecision(4) << matrix[i * col + j];
            // outFile << std::setw(7) << matrix[i * col + j] << " " ;
        }
        outFile << "\n";
    }
    outFile.close();
}


int main() {
    std::ifstream file("python_out/embedding.txt"); if (!file) { std::cerr << "Error opening file.\n"; return -1; }

    size_t num_elements = 512 * 1024;

    float* data  = (float*)malloc(num_elements * 4); 

    size_t index = 0;
    while (file >> data[index] && index < num_elements) {
        index++;
    }
    if (index != num_elements) {
        std::cerr << "File does not contain enough data. Expected " << num_elements << " values, but got " << index << ".\n";
        return -1;
    }else{
        std::cout << "Data loaded successfully. First element: " << data[0] << " Last element: " << data[num_elements - 1] << std::endl;
    }

    std::string filename = "cpp_out/embedding.txt";

    print_matrix_to_file( filename, data, 512, 1024);



    free(data);

    return 0;
}