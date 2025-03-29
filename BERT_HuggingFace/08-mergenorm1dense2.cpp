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
#include <filesystem>
namespace fs = std::filesystem;


void printMatrixToFile(float* matrix, int rows, int cols, const std::string& filename) {
    std::ofstream outfile(filename);  // Open the file for writing

    // Check if the file is open
    if (!outfile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    // Iterate through the matrix and write each element to the file
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Compute the linear index for the current element
            int index = i * cols + j;
            outfile << matrix[index] << std::endl;
        }
    }

    // Close the file
    outfile.close();
}




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


void calculate_matrix(float* host_inA_port, float* host_inB_port, float* gold_val, int A, int B, int K){
    std::cout<< "calculate_matrix" << std::endl;
    for (int i=0; i<A; i++){
        for (int j=0; j<B; j++){
            float sum = 0;
            for (int k=0; k<K; k++){
                sum += host_inA_port[i*K+k] * host_inB_port[k*B+j];
            }
            gold_val[i*B+j] = sum;
        }
    }
}

void transpose_matrix(float* matrix, float* transposed_matrix, int row, int col){
    std::cout<< "transpose_matrix" << std::endl;
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            transposed_matrix[j*row+i] = matrix[i*col+j];
        }
    }
}


void calculate_softmax(float* host_inA_port, float* gold_val, int A, int B){
    std::cout<< "calculate_softmax" << std::endl;
    for (int i=0; i<A; i++){
        float sum = 0;
        for (int j=0; j<B; j++){
            sum += exp(host_inA_port[i*B+j]);
        }
        for (int j=0; j<B; j++){
            gold_val[i*B+j] = exp(host_inA_port[i*B+j]) / sum;
        }
    }
}


void convert_simple_to_blocked_layout(float *matrix, int row, int col, int block_row, int block_col) {
    std::cout<< "convert_simple_to_blocked_layout row = " << row << " col = " << col << " block_row = " << block_row << " block_col = " << block_col << std::endl;
    // Initialize block dimensions

    int total_blocks_row = row / block_row;
    int total_blocks_col = col / block_col;

    // Allocate memory for the blocked matrix
    float *blocked_matrix = (float *)malloc(col * row * sizeof(float));
    if (!blocked_matrix) {
        printf("Memory allocation failed\n");
        return;
    }

    // Initialize blocked matrix to zero
    memset(blocked_matrix, 0, col * row * sizeof(float));

    // Rearrange to blocked layout
    for (int block_r = 0; block_r < total_blocks_row; ++block_r) {
        for (int block_c = 0; block_c < total_blocks_col; ++block_c) {
            // Calculate the starting position of this block in the blocked matrix
            int start_row = block_r * block_row;
            int start_col = block_c * block_col;

            // Copy the data from the simple matrix layout to the blocked matrix layout
            for (int r = 0; r < block_row; ++r) {
                for (int c = 0; c < block_col; ++c) {
                    int simple_row = start_row + r;
                    int simple_col = start_col + c;

                    // Compute the index in the simple layout
                    int simple_idx = simple_row * col + simple_col;

                    // Compute the index in the blocked layout
                    int block_idx = block_r * total_blocks_col * block_row * block_col +
                                    block_c * block_row * block_col +
                                    r * block_col + c;

                    // Assign value from simple layout to blocked layout
                    blocked_matrix[block_idx] = matrix[simple_idx];
                }
            }
        }
    }
    
    // copy the blocked matrix back to the original matrix
    for (int i = 0; i < row * col; i++) {
        matrix[i] = blocked_matrix[i];
    }

    // Free the blocked matrix after usage
    free(blocked_matrix);
}


// 64 512b AXI read is 4KB, each port reads 4KB stride data alternatively
// port 0 reads address 0, 1, 2, ... 63
// port 1 reads address 64, 65, 66, ... 127

// block size is 128*64
// each row has 64 elements (4 AXI read)  16 rows for 4KB

// put row 0 2 4, .. 30 in address 0, 1 , 2, ... 63
// put row 1 3 5, .. 31 in address 64, 65, 66, ... 127

void convert_blocked_to_2AXI_layout(float *matrix, int row, int col) {
    std::cout<< "convert_blocked_to_2AXI_layout row = " << row << " col = " << col << std::endl;

    // Allocate memory for the blocked matrix
    float *blocked_matrix = (float *)malloc(col * row * sizeof(float));
    if (!blocked_matrix) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i< row*col; i=i+128*64){
        for (int r=0; r<128; r=r+32){
            for (int s=0; s<16; s=s+1){
                for (int c=0; c<64; c++){
                    blocked_matrix[i+(r+s)*64+c] = matrix[i+(r+s*2)*64+c];
                    blocked_matrix[i+(r+s+16)*64+c] = matrix[i+(r+s*2+1)*64+c];
                }
            }
        }
        
    }

    // copy the blocked matrix back to the original matrix
    for (int i = 0; i < row * col; i++) {
        matrix[i] = blocked_matrix[i];
    }

    // Free the blocked matrix after usage
    free(blocked_matrix);
}



void valid (float * host_outC_port, float * gold_val, size_t size){
    int wrong_count = 0;
    for (int i=0; i<size; i++){
        if ( (gold_val[i] - host_outC_port[i])*(gold_val[i] - host_outC_port[i]) > 0.001 ){
            if (wrong_count < 10){
                std::cout << "Error: gold_val[" << i << "] = " << gold_val[i] << " != host_outC_port[" << i << "] = " << host_outC_port[i] << std::endl;
            }
            wrong_count++;
        }
    }
    if (wrong_count > 0){
        std::cout << "Validation failed! " << wrong_count << " errors found." << std::endl;
    }else{
        std::cout << "Validation passed!" << std::endl;
    }

    std::cout<<"host_outC_port[0:7] = " << std::endl;
    for (int i=0; i<8; i++){
        printf("%f ", host_outC_port[i]);
    }
}


void calculate_matrix_with_bias(float* host_inA_port, float* host_inB_port, float * bias, float* gold_val, int A, int B, int K){
    std::cout<< "calculate_matrix" << std::endl;
    for (int i=0; i<A; i++){
        for (int j=0; j<B; j++){
            float sum = 0;
            for (int k=0; k<K; k++){
                sum += host_inA_port[i*K+k] * host_inB_port[k*B+j];
            }
            gold_val[i*B+j] = sum + bias[j];
            // printf("bias = %f\n", bias[j]);
            // printf("sum = %f\n", sum);
        }
    }
}



int load_data(const std::string &filename, float *data, size_t num_elements) {

    std::ifstream file(filename);   
    if (!file) { std::cerr << "Error opening file.\n"; return -1; }

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

}

void matrix_scale(float* matrix, float scale, int row, int col){
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            matrix[i*col+j] = matrix[i*col+j] * scale;
        }
    }
}

void matrix_add(float* matrix, float* matrix_added, int row, int col){
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            matrix[i*col+j] = matrix[i*col+j] + matrix_added[i*col+j];
        }
    }
}

void layer_normalization(float* matrix, float * matrix_normalized, float* weight, float* bias, int row, int col){

    for (int i=0; i<row; i++){
        float sum = 0;
        for (int j=0; j<col; j++){
            sum += matrix[i*col+j];
        }
        float mean = sum / col;
        float variance = 0;
        for (int j=0; j<col; j++){
            variance += (matrix[i*col+j] - mean) * (matrix[i*col+j] - mean);
        }
        variance = variance / col;
        for (int j=0; j<col; j++){
            matrix_normalized[i*col+j] = (matrix[i*col+j] - mean) / sqrt(variance + 0.00001);
        }
    }

    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            matrix_normalized[i*col+j] = matrix_normalized[i*col+j] * weight[j] + bias[j];
        }
    }

}


void layer_normalization_no_weightbias(float* matrix, float * matrix_normalized, int row, int col){

    for (int i=0; i<row; i++){
        float sum = 0;
        for (int j=0; j<col; j++){
            sum += matrix[i*col+j];
        }
        float mean = sum / col;
        float variance = 0;
        for (int j=0; j<col; j++){
            variance += (matrix[i*col+j] - mean) * (matrix[i*col+j] - mean);
        }
        variance = variance / col;
        for (int j=0; j<col; j++){
            matrix_normalized[i*col+j] = (matrix[i*col+j] - mean) / sqrt(variance + 0.00001);
        }
    }

}


void cal_gelu (float* matrix, float* matrix_gelu, int row, int col){
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            matrix_gelu[i*col+j] = 0.5 * matrix[i*col+j] * (1 + tanh(0.79788456 * (matrix[i*col+j] + 0.044715 * matrix[i*col+j] * matrix[i*col+j] * matrix[i*col+j])));
        }
    }
}


int main() {

    std::string dir = "output/07-cpp_out";

    // Remove the directory if it exists
    if (fs::exists(dir)) {
        fs::remove_all(dir);
    }
    // Create the directory along with any necessary parent directories
    fs::create_directories(dir);


    bool load_success; 
    float* data_input  = (float*)malloc(512*4096 * 4); 
    float* data_weight  = (float*)malloc(1024*4096 * 4);
    float* data_bias  = (float*)malloc(4096 * 4);
    float* gold_val  = (float*)malloc(512*4096 * 4);

    float* data_query  = (float*)malloc(512*1024 * 4);
    float* data_key  = (float*)malloc(512*1024 * 4);
    float* data_value  = (float*)malloc(512*1024 * 4);
    float* self_attention  = (float*)malloc(512*1024 * 4);
    float* dense1 = (float*)malloc(512*1024 * 4);
    float* norm1 = (float*)malloc(512*1024 * 4);
    float* dense2 = (float*)malloc(512*4096 * 4);
    float* gelu = (float*)malloc(512*4096 * 4);
    float* dense3 = (float*)malloc(512*1024 * 4);
    float* norm2 = (float*)malloc(512*1024 * 4);


    load_success = load_data("output/06-python_gold/0-attention.self.query-input.txt", data_input, 512*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/0-attention.self.query-weight.txt", data_weight, 1024*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/0-attention.self.query-bias.txt", data_bias, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/0-attention.self.query-output.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    matrix_scale (data_weight, 1.0/8, 1024, 1024);
    matrix_scale (data_bias, 1.0/8, 1, 1024);
    calculate_matrix_with_bias (data_input, data_weight, data_bias, data_query, 512, 1024, 1024);
    print_matrix_to_file("output/07-cpp_out/0-attention.self.query-output.txt", data_query, 512, 1024);
    valid(data_query, gold_val, 512*1024);
    // matrix_scale (data_query, 1.0/8, 512, 1024);


    // load_success = load_data("output/06-python_gold/1-attention.self.key-input.txt", data_input, 512*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/1-attention.self.key-weight.txt", data_weight, 1024*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/1-attention.self.key-bias.txt", data_bias, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/1-attention.self.key-output.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    calculate_matrix_with_bias (data_input, data_weight, data_bias, data_key, 512, 1024, 1024);
    print_matrix_to_file("output/07-cpp_out/1-attention.self.key-output.txt", data_key, 512, 1024);
    valid(data_key, gold_val, 512*1024);

    // load_success = load_data("output/06-python_gold/2-attention.self.value-input.txt", data_input, 512*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/2-attention.self.value-weight.txt", data_weight, 1024*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/2-attention.self.value-bias.txt", data_bias, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/2-attention.self.value-output.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    calculate_matrix_with_bias (data_input, data_weight, data_bias, data_value, 512, 1024, 1024);
    print_matrix_to_file("output/07-cpp_out/2-attention.self.value-output.txt", data_value, 512, 1024);
    valid(data_value, gold_val, 512*1024);

    // attention 16 head
    for (int h=0; h<16; h++){
        float * q = (float*)malloc(512*64*4);
        float * k = (float*)malloc(512*64*4);
        float * k_transposed = (float*)malloc(512*64*4);
        float * v = (float*)malloc(512*64*4);
        float * qk = (float*)malloc(512*512*4);
        float * qk_softmax = (float*)malloc(512*512*4);
        float * qkv = (float*)malloc(512*64*4);

        for (int r=0; r<512; r++){
            for (int c=0; c<64; c++){
                q[r*64+c] = data_query[r*1024+h*64+c];
                k[r*64+c] = data_key[r*1024+h*64+c];
                v[r*64+c] = data_value[r*1024+h*64+c];
            }
        }
        transpose_matrix(k, k_transposed, 512, 64);
        calculate_matrix(q, k_transposed, qk, 512, 512, 64);
        // matrix_scale (qk, 1.0/8, 512, 512);
        print_matrix_to_file("output/07-cpp_out/2-attention.output.qk.txt", qk, 512, 512);
        calculate_softmax(qk, qk_softmax, 512, 512);
        print_matrix_to_file("output/07-cpp_out/2-attention.output.qk_softmax.txt", qk_softmax, 512, 512);
        calculate_matrix(qk_softmax, v, qkv, 512, 64, 512);
        print_matrix_to_file("output/07-cpp_out/2-attention.output.qkv.txt", qkv, 512, 64);

        for (int r=0; r<512; r++){
            for (int c=0; c<64; c++){
                self_attention[r*1024+h*64+c] = qkv[r*64+c];
            }
        }
    }
    load_success = load_data("output/06-python_gold/3-attention.output.dense-input.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    print_matrix_to_file("output/07-cpp_out/3-attention.output.dense-input.txt", self_attention, 512, 1024);
    valid(self_attention, gold_val, 512*1024);


    load_success = load_data("output/06-python_gold/3-attention.output.dense-weight.txt", data_weight, 1024*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/3-attention.output.dense-bias.txt", data_bias, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/3-attention.output.dense-output.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    calculate_matrix_with_bias (self_attention, data_weight, data_bias, dense1, 512, 1024, 1024);
    print_matrix_to_file("output/07-cpp_out/3-attention.output.dense-output.txt", dense1, 512, 1024);
    valid(dense1, gold_val, 512*1024);


    matrix_add (dense1, data_input, 512, 1024);
    load_success = load_data("output/06-python_gold/4-attention.output.LayerNorm-output.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    layer_normalization_no_weightbias(dense1, norm1, 512, 1024);
    print_matrix_to_file("output/07-cpp_out/4-attention.output.LayerNorm-output.txt", norm1, 512, 1024);
    valid(norm1, gold_val, 512*1024);

    printMatrixToFile(norm1, 512, 1024, "output/06-python_gold/4-fused_dense1_norm1_output.txt");


    float* norm1_weight = (float*)malloc(1024 * 4);
    float* norm1_bias = (float*)malloc(1024 * 4);
    load_success = load_data("output/06-python_gold/4-attention.output.LayerNorm-weight.txt", norm1_weight, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/4-attention.output.LayerNorm-bias.txt", norm1_bias, 1024); if (load_success == -1) return -1;

    float * norm1merged_weight = (float*)malloc(1024*4096 * 4);
    float * norm1merged_bias = (float*)malloc(4096 * 4);
    load_success = load_data("output/06-python_gold/5-intermediate.dense-weight.txt", data_weight, 1024*4096); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/5-intermediate.dense-bias.txt", data_bias, 4096); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/5-intermediate.dense-output.txt", gold_val, 512*4096); if (load_success == -1) return -1;

    float * norm1_wb = (float*)malloc(512*1024 * 4);
    float * norm1_weight_diag = (float*)malloc(1024*1024 * 4);
    for (int i=0; i<1024; i++){
        for (int j=0; j<1024; j++){
            if (i==j){
                norm1_weight_diag[i*1024+j] = norm1_weight[i];
            }else{
                norm1_weight_diag[i*1024+j] = 0;
            }
        }
    }
    // first add weight and bias to norm1, then calculate dense2
    // calculate_matrix_with_bias (norm1, norm1_weight_diag, norm1_bias, norm1_wb, 512, 1024, 1024);
    // calculate_matrix_with_bias (norm1_wb, data_weight, data_bias, dense2, 512, 4096, 1024);

    // merge norm1_weight and dense2_weight together
    // prepare weight offline
    calculate_matrix(norm1_weight_diag, data_weight, norm1merged_weight, 1024, 4096, 1024);
    calculate_matrix_with_bias(norm1_bias, data_weight, data_bias, norm1merged_bias, 1, 4096, 1024);
    // calculate dense2
    calculate_matrix_with_bias (norm1, norm1merged_weight, norm1merged_bias, dense2, 512, 4096, 1024);

    printMatrixToFile(norm1merged_weight, 1024, 4096, "output/06-python_gold/5-fused_norm1_dense2_weight.txt");
    printMatrixToFile(norm1merged_bias, 1, 4096, "output/06-python_gold/5-fused_norm1_dense2_bias.txt");

    // can merge norm1 to dense2, but norm1 need to be used in the norm2 calculation


    print_matrix_to_file("output/07-cpp_out/5-intermediate.dense-output.txt", dense2, 512, 4096);
    valid(dense2, gold_val, 512*4096);


    cal_gelu (dense2, gelu, 512, 4096);
    load_success = load_data("output/06-python_gold/6-output.dense-input.txt", gold_val, 512*4096); if (load_success == -1) return -1;
    print_matrix_to_file("output/07-cpp_out/6-output.dense-input.txt", gelu, 512, 4096);
    valid(gelu, gold_val, 512*4096);

    load_success = load_data("output/06-python_gold/6-output.dense-weight.txt", data_weight, 4096*1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/6-output.dense-bias.txt", data_bias, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/6-output.dense-output.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    
    matrix_add (data_bias, norm1_bias, 1, 1024);

    calculate_matrix_with_bias (gelu, data_weight, data_bias, dense3, 512, 1024, 4096);
    print_matrix_to_file("output/07-cpp_out/6-output.dense-output.txt", dense3, 512, 1024);
    valid(dense3, gold_val, 512*1024);


    calculate_matrix (norm1, norm1_weight_diag, norm1_wb, 512, 1024, 1024);
    matrix_add (dense3, norm1_wb, 512, 1024);
    
    load_success = load_data("output/06-python_gold/7-output.LayerNorm-weight.txt", data_weight, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/7-output.LayerNorm-bias.txt", data_bias, 1024); if (load_success == -1) return -1;
    load_success = load_data("output/06-python_gold/7-output.LayerNorm-output.txt", gold_val, 512*1024); if (load_success == -1) return -1;
    
    layer_normalization_no_weightbias(dense3, norm2, 512, 1024);
    printMatrixToFile(norm2, 512, 1024, "output/06-python_gold/7-fused_dense3_norm2.txt");

    layer_normalization (dense3, norm2, data_weight, data_bias, 512, 1024);
    print_matrix_to_file("output/07-cpp_out/7-output.LayerNorm-output.txt", norm2, 512, 1024);
    valid(norm2, gold_val, 512*1024);

    free(data_input);
    free(data_weight);
    free(data_bias);
    free(gold_val);
    free(self_attention);

    return 0;
}




    



