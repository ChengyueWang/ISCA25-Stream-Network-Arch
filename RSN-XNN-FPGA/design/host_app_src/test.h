#pragma once

#include "comm.h"

// Function to reorder a 4096 element array according to specified blocks
void reorderArray_4096(float* array) {
  const int blockSize = 512;  // Each block size
  const int numBlocks = 8;    // Number of blocks
  float temp[4096];           // Temporary array to hold reordered data

  // Define the new order for blocks
  int newOrder[numBlocks] = {0, 2, 4, 6, 1, 3, 5, 7};

  // Perform the reordering
  for (int i = 0; i < numBlocks; ++i) {
    std::copy(array + newOrder[i] * blockSize, array + (newOrder[i] + 1) * blockSize,
              temp + i * blockSize);
  }

  // Copy the reordered data back to the original array
  std::copy(temp, temp + 4096, array);
}

void matrix_add(float* matrix, float* matrix_added, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i * col + j] = matrix[i * col + j] + matrix_added[i * col + j];
    }
  }
}

void layer_normalization_no_weightbias(float* matrix, int row, int col) {
  std::cout << "layer_normalization_no_weightbias" << std::endl;
  float* matrix_normalized = (float*)malloc(row * col * sizeof(float));
  for (int i = 0; i < row; i++) {
    float sum = 0;
    for (int j = 0; j < col; j++) {
      sum += matrix[i * col + j];
    }
    float mean = sum / col;
    float variance = 0;
    for (int j = 0; j < col; j++) {
      variance += (matrix[i * col + j] - mean) * (matrix[i * col + j] - mean);
    }
    variance = variance / col;
    for (int j = 0; j < col; j++) {
      matrix_normalized[i * col + j] = (matrix[i * col + j] - mean) / sqrt(variance + 0.00001);
    }
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i * col + j] = matrix_normalized[i * col + j];
    }
  }
  free(matrix_normalized);
}

void replicate_matrix(float* matrix, int row, int col, int num_replicate) {
  std::cout << "replicate_matrix row = " << row << " col = " << col
            << " num_replicate = " << num_replicate << std::endl;
  for (int i = 1; i < num_replicate; i++) {
    for (int j = 0; j < row; j++) {
      for (int k = 0; k < col; k++) {
        matrix[i * row * col + j * col + k] = matrix[j * col + k];
      }
    }
  }
}

void matrix_scale(float* matrix, float scale, int row, int col) {
  std::cout << "matrix_scale" << std::endl;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i * col + j] = matrix[i * col + j] * scale;
    }
  }
}

int load_data(const std::string& filename, float* data, size_t num_elements) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error opening file.\n";
    return -1;
  }

  size_t index = 0;
  while (file >> data[index] && index < num_elements) {
    index++;
  }
  if (index != num_elements) {
    std::cerr << "File does not contain enough data. Expected " << num_elements
              << " values, but got " << index << ".\n";
    return -1;
  } else {
    std::cout << "Data loaded successfully. First element: " << data[0]
              << " Last element: " << data[num_elements - 1] << std::endl;
  }
}

void calculate_matrix_with_bias(float* host_inA_port, float* host_inB_port, float* bias,
                                float* gold_val, int A, int B, int K) {
  std::cout << "calculate_matrix_with_bias" << std::endl;
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < B; j++) {
      float sum = 0;
      for (int k = 0; k < K; k++) {
        sum += host_inA_port[i * K + k] * host_inB_port[k * B + j];
      }
      gold_val[i * B + j] = sum + bias[j];
      // printf("bias = %f\n", bias[j]);
      // printf("sum = %f\n", sum);
    }
  }
}

void add_matrix_with_bias(float* matrix, float* bias, int A, int B) {
  std::cout << "add_matrix_with_bias" << std::endl;
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < B; j++) {
      matrix[i * B + j] += bias[j];
    }
  }
}

void init_matrix(float* matrix, int row, int col, float val) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i * col + j] = val;
    }
  }
}

// block size 128*64
void init_matrix_blocked(float* matrix, int row, int col, int block_row, int block_col) {
  for (int i = 0; i < row / block_row; i++) {
    for (int j = 0; j < col / block_col; j++) {
      for (int k = 0; k < block_row; k++) {
        for (int l = 0; l < block_col; l++) {
          matrix[(i * block_row + k) * col + j * block_col + l] = (i * col / block_col + j) * 1.0;
        }
      }
    }
  }
}

// Initialize the matrix with random values
void init_matrix_random(float* matrix, int row, int col) {
  // Seed the random number generator
  srand(time(NULL));
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i * col + j] = (float)rand() / RAND_MAX;  // Random float between 0 and 1
    }
  }
}

void print_matrix_to_file(const std::string& filename, const float* matrix, int row, int col) {
#ifdef SW_EMU_PRINT
  std::ofstream outFile(filename);
  if (!outFile.is_open()) {
    std::cerr << "Error opening file for writing: " << filename << std::endl;
    return;
  }
  // Print matrix size
  outFile << "Size: (" << row << ", " << col << ")\n";
  // Print column headers
  outFile << "      ";  // Indentation for row headers
  for (int j = 0; j < col; j++) {
    outFile << std::setw(7) << j;
  }
  outFile << "\n";

  // Print matrix data with row headers
  for (int i = 0; i < row; i++) {
    outFile << std::setw(7) << i;  // Row header
    for (int j = 0; j < col; j++) {
      outFile << std::setw(7) << std::fixed << std::setprecision(4) << matrix[i * col + j];
      // outFile << std::setw(7) << matrix[i * col + j] << " " ;
    }
    outFile << "\n";
  }

  outFile.close();
#endif
}

void calculate_matrix(float* host_inA_port, float* host_inB_port, float* gold_val, int A, int B,
                      int K) {
  std::cout << "calculate_matrix" << std::endl;
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < B; j++) {
      float sum = 0;
      for (int k = 0; k < K; k++) {
        sum += host_inA_port[i * K + k] * host_inB_port[k * B + j];
      }
      gold_val[i * B + j] = sum;
    }
  }
}

void transpose_matrix(float* matrix, float* transposed_matrix, int row, int col) {
  std::cout << "transpose_matrix" << std::endl;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      transposed_matrix[j * row + i] = matrix[i * col + j];
    }
  }
}

void calculate_softmax(float* host_inA_port, float* gold_val, int A, int B) {
  std::cout << "calculate_softmax" << std::endl;
  for (int i = 0; i < A; i++) {
    float sum = 0;
    for (int j = 0; j < B; j++) {
      sum += exp(host_inA_port[i * B + j]);
    }
    for (int j = 0; j < B; j++) {
      gold_val[i * B + j] = exp(host_inA_port[i * B + j]) / sum;
    }
  }
}

void convert_simple_to_blocked_layout(float* matrix, int row, int col, int block_row,
                                      int block_col) {
  std::cout << "convert_simple_to_blocked_layout row = " << row << " col = " << col
            << " block_row = " << block_row << " block_col = " << block_col << std::endl;
  // Initialize block dimensions

  int total_blocks_row = row / block_row;
  int total_blocks_col = col / block_col;

  // Allocate memory for the blocked matrix
  float* blocked_matrix = (float*)malloc(col * row * sizeof(float));
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
                          block_c * block_row * block_col + r * block_col + c;

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

void convert_blocked_to_2AXI_layout(float* matrix, int row, int col) {
  std::cout << "convert_blocked_to_2AXI_layout row = " << row << " col = " << col << std::endl;

  // Allocate memory for the blocked matrix
  float* blocked_matrix = (float*)malloc(col * row * sizeof(float));
  if (!blocked_matrix) {
    printf("Memory allocation failed\n");
    return;
  }

  for (int i = 0; i < row * col; i = i + 128 * 64) {
    for (int r = 0; r < 128; r = r + 32) {
      for (int s = 0; s < 16; s = s + 1) {
        for (int c = 0; c < 64; c++) {
          blocked_matrix[i + (r + s) * 64 + c] = matrix[i + (r + s * 2) * 64 + c];
          blocked_matrix[i + (r + s + 16) * 64 + c] = matrix[i + (r + s * 2 + 1) * 64 + c];
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

void convert_input_weight_gold_to_2AXI(float* fmap0_embedding, float* weight0_query,
                                       float* load_gold_query, ParamsOneLayer params) {
  params.print();
  int A = params.getMatrixDim_A();
  int B = params.getMatrixDim_B();
  int K = params.getMatrixDim_K();

  convert_simple_to_blocked_layout(fmap0_embedding, A, K, 128, 64);
  convert_simple_to_blocked_layout(weight0_query, K, B, 128, 64);
  convert_simple_to_blocked_layout(load_gold_query, A, B, 128, 64);

  convert_blocked_to_2AXI_layout(fmap0_embedding, A, K);
  convert_blocked_to_2AXI_layout(weight0_query, K, B);
  convert_blocked_to_2AXI_layout(load_gold_query, A, B);
}

void convert_weight_gold_to_2AXI(float* weight0_query, float* load_gold_query,
                                 ParamsOneLayer params) {
  params.print();
  int A = params.getMatrixDim_A();
  int B = params.getMatrixDim_B();
  int K = params.getMatrixDim_K();

  convert_simple_to_blocked_layout(weight0_query, K, B, 128, 64);
  convert_simple_to_blocked_layout(load_gold_query, A, B, 128, 64);

  convert_blocked_to_2AXI_layout(weight0_query, K, B);
  convert_blocked_to_2AXI_layout(load_gold_query, A, B);
}

void generate_data_onelayer_with_bias(float* host_inA_port, float* host_inB_port, float* bias,
                                      float* host_outC_port, float* gold_val,
                                      ParamsOneLayer params) {
  std::cout << "generate_data_onelayer_with_bias" << std::endl;
  params.print();
  int A = params.getMatrixDim_A();
  int B = params.getMatrixDim_B();
  int K = params.getMatrixDim_K();

  std::cout << "init matrices" << std::endl;

  init_matrix(host_inA_port, A, K, 1.0);
  init_matrix(host_inB_port, K, B, 1.0);
  init_matrix(host_outC_port, A, B, 0.0);

  init_matrix(bias, 1, B, 1.0);
  // init_matrix_blocked (bias, 1, B, 1, 1);

  // init_matrix_blocked (host_inA_port, A, K, 128, 64);
  // init_matrix_blocked (host_inB_port, K, B, 128, 64);

  // init_matrix_blocked (host_inA_port, A, K, 256, 128);
  // init_matrix_blocked (host_inB_port, K, B, 128, 1024);

  // for (int r=0; r<16; r++){
  //     for (int c=0; c<16; c++){
  //         host_inA_port[r*K+c] = r+1;
  //     }
  // }
  // for (int r=0; r<16; r++){
  //     for (int c=0; c<16; c++){
  //         host_inB_port[r*B+c] = r+1;
  //     }
  // }
  // for (int i=0; i<4; i++){
  //     host_inA_port[i] = i+1;
  //     host_inB_port[i] = i+1;
  // }

  // init_matrix_random (host_inA_port, A, K);
  // init_matrix_random (host_inB_port, K, B);
  // init_matrix_random (bias, 1, B);

  calculate_matrix_with_bias(host_inA_port, host_inB_port, bias, gold_val, A, B, K);

  std::string file_name =
      "/home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/0_onelayer_";

  print_matrix_to_file(file_name + "inA_matrix.txt", host_inA_port, A, K);
  print_matrix_to_file(file_name + "inB_matrix.txt", host_inB_port, K, B);
  print_matrix_to_file(file_name + "gold_val_matrix.txt", gold_val, A, B);

  convert_simple_to_blocked_layout(host_inA_port, A, K, 128, 64);
  print_matrix_to_file(file_name + "inA_matrix_blocked.txt", host_inA_port, A, K);

  convert_simple_to_blocked_layout(host_inB_port, K, B, 128, 64);
  print_matrix_to_file(file_name + "inB_matrix_blocked.txt", host_inB_port, K, B);

  convert_simple_to_blocked_layout(gold_val, A, B, 128, 64);
  print_matrix_to_file(file_name + "gold_val_matrix_blocked.txt", gold_val, A, B);

  convert_blocked_to_2AXI_layout(host_inA_port, A, K);
  print_matrix_to_file(file_name + "inA_matrix_2AXI.txt", host_inA_port, A, K);

  convert_blocked_to_2AXI_layout(host_inB_port, K, B);
  print_matrix_to_file(file_name + "inB_matrix_2AXI.txt", host_inB_port, K, B);

  convert_blocked_to_2AXI_layout(gold_val, A, B);
  print_matrix_to_file(file_name + "gold_val_matrix_2AXI.txt", gold_val, A, B);
}

void generate_data_onelayer(float* host_inA_port, float* host_inB_port, float* host_outC_port,
                            float* gold_val, ParamsOneLayer params) {
  std::cout << "generate_data_onelayer" << std::endl;
  params.print();
  int A = params.getMatrixDim_A();
  int B = params.getMatrixDim_B();
  int K = params.getMatrixDim_K();

  std::cout << "init matrices" << std::endl;

  init_matrix(host_inA_port, A, K, 0.0);
  init_matrix(host_inB_port, K, B, 0.0);
  init_matrix(host_outC_port, A, B, 0.0);

  init_matrix_blocked(host_inA_port, A, K, 128, 64);
  init_matrix_blocked(host_inB_port, K, B, 128, 64);

  // init_matrix_blocked (host_inA_port, A, K, 256, 128);
  // init_matrix_blocked (host_inB_port, K, B, 128, 1024);

  // for (int r=0; r<16; r++){
  //     for (int c=0; c<16; c++){
  //         host_inA_port[r*K+c] = r+1;
  //     }
  // }
  // for (int r=0; r<16; r++){
  //     for (int c=0; c<16; c++){
  //         host_inB_port[r*B+c] = r+1;
  //     }
  // }
  // for (int i=0; i<4; i++){
  //     host_inA_port[i] = i+1;
  //     host_inB_port[i] = i+1;
  // }

  // init_matrix_random (host_inA_port, A, K);
  // init_matrix_random (host_inB_port, K, B);

  calculate_matrix(host_inA_port, host_inB_port, gold_val, A, B, K);

  std::string file_name =
      "/home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/0_onelayer_";

  print_matrix_to_file(file_name + "inA_matrix.txt", host_inA_port, A, K);
  print_matrix_to_file(file_name + "inB_matrix.txt", host_inB_port, K, B);
  print_matrix_to_file(file_name + "gold_val_matrix.txt", gold_val, A, B);

  convert_simple_to_blocked_layout(host_inA_port, A, K, 128, 64);
  print_matrix_to_file(file_name + "inA_matrix_blocked.txt", host_inA_port, A, K);

  convert_simple_to_blocked_layout(host_inB_port, K, B, 128, 64);
  print_matrix_to_file(file_name + "inB_matrix_blocked.txt", host_inB_port, K, B);

  convert_simple_to_blocked_layout(gold_val, A, B, 128, 64);
  print_matrix_to_file(file_name + "gold_val_matrix_blocked.txt", gold_val, A, B);

  convert_blocked_to_2AXI_layout(host_inA_port, A, K);
  print_matrix_to_file(file_name + "inA_matrix_2AXI.txt", host_inA_port, A, K);

  convert_blocked_to_2AXI_layout(host_inB_port, K, B);
  print_matrix_to_file(file_name + "inB_matrix_2AXI.txt", host_inB_port, K, B);

  convert_blocked_to_2AXI_layout(gold_val, A, B);
  print_matrix_to_file(file_name + "gold_val_matrix_2AXI.txt", gold_val, A, B);
}

void generate_data_fusedlayer(float* host_L1_inA, float* host_L1_inB, float* host_L2_inB,
                              float* host_L2_outC, float* gold_val, ParamsFusedLayer params) {
  std::cout << "generate_data_fusedlayer" << std::endl;
  params.print();

  int num_layer = params.num_layer;

  init_matrix(host_L1_inA, 512, 64 * num_layer, 1.0);
  init_matrix(host_L1_inB, 512, 64 * num_layer, 1.0);
  init_matrix(host_L2_inB, 512, 64 * num_layer, 1.0);
  init_matrix(host_L2_outC, 512, 64 * num_layer, 0);

  std::string file_name =
      "/home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/0_fuse_";

  init_matrix_blocked(host_L1_inA, 512, 64 * num_layer, 128, 64);
  init_matrix_blocked(host_L1_inB, 512, 64 * num_layer, 128, 64);
  init_matrix_blocked(host_L2_inB, 512, 64 * num_layer, 128, 64);

  // init_matrix_random(host_L1_inA, 512, 64);
  // init_matrix_random(host_L1_inB, 512, 64);
  // init_matrix_random(host_L2_inB, 512, 64);

  for (int l = 0; l < num_layer; l++) {
    float* curlayer_L1_outC = (float*)malloc(512 * 512 * sizeof(float));
    float* curlayer_softmax_out = (float*)malloc(512 * 512 * sizeof(float));
    float* curlayer_transposed = (float*)malloc(512 * 512 * sizeof(float));
    float* curlayer_L1_inA = (float*)malloc(64 * 512 * sizeof(float));
    float* curlayer_L1_inB = (float*)malloc(64 * 512 * sizeof(float));
    float* curlayer_L2_inB = (float*)malloc(64 * 512 * sizeof(float));
    float* curlayer_L2_outC = (float*)malloc(64 * 512 * sizeof(float));

    // assert(num_layer <=16);

    for (int i = 0; i < 512; i++) {
      for (int j = 0; j < 64; j++) {
        curlayer_L1_inA[i * 64 + j] = host_L1_inA[i * 64 * num_layer + 64 * l + j];
        curlayer_L1_inB[i * 64 + j] = host_L1_inB[i * 64 * num_layer + 64 * l + j];
        curlayer_L2_inB[i * 64 + j] = host_L2_inB[i * 64 * num_layer + 64 * l + j];
      }
    }

    transpose_matrix(curlayer_L1_inB, curlayer_transposed, 512, 64);
    calculate_matrix(curlayer_L1_inA, curlayer_transposed, curlayer_L1_outC, 512, 512, 64);

    calculate_softmax(curlayer_L1_outC, curlayer_softmax_out, 512, 512);
    calculate_matrix(curlayer_softmax_out, curlayer_L2_inB, curlayer_L2_outC, 512, 64, 512);

    // calculate_matrix(curlayer_L1_outC, curlayer_L2_inB, curlayer_L2_outC, 512, 64, 512);

    std::cout << "move data back" << std::endl;
    for (int i = 0; i < 512; i++) {
      for (int j = 0; j < 64; j++) {
        gold_val[i * 64 * num_layer + 64 * l + j] = curlayer_L2_outC[i * 64 + j];
      }
    }

    print_matrix_to_file(file_name + "0_l" + to_string(l) + "_L1_outC.txt", curlayer_L1_outC, 512,
                         512);
    print_matrix_to_file(file_name + "0_l" + to_string(l) + "_softmax_out.txt",
                         curlayer_softmax_out, 512, 512);
    free(curlayer_L1_outC);
    free(curlayer_softmax_out);
    free(curlayer_transposed);
    free(curlayer_L1_inA);
    free(curlayer_L1_inB);
    free(curlayer_L2_inB);
    free(curlayer_L2_outC);
  }

  print_matrix_to_file(file_name + "L1_inA_matrix.txt", host_L1_inA, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "L1_inB_matrix.txt", host_L1_inB, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "L2_inB_matrix.txt", host_L2_inB, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "gold_L2_outC.txt", gold_val, 512, 64 * num_layer);

  convert_simple_to_blocked_layout(host_L1_inA, 512, 64 * num_layer, 128, 64);
  convert_simple_to_blocked_layout(host_L1_inB, 512, 64 * num_layer, 128, 64);
  convert_simple_to_blocked_layout(host_L2_inB, 512, 64 * num_layer, 128, 64);
  convert_simple_to_blocked_layout(gold_val, 512, 64 * num_layer, 128, 64);

  print_matrix_to_file(file_name + "L1_inA_matrix_blocked.txt", host_L1_inA, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "L1_inB_matrix_blocked.txt", host_L1_inB, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "L2_inB_matrix_blocked.txt", host_L2_inB, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "gold_L2_outC_blocked.txt", gold_val, 512, 64 * num_layer);

  convert_blocked_to_2AXI_layout(host_L1_inA, 512, 64 * num_layer);
  convert_blocked_to_2AXI_layout(host_L1_inB, 512, 64 * num_layer);
  convert_blocked_to_2AXI_layout(host_L2_inB, 512, 64 * num_layer);
  convert_blocked_to_2AXI_layout(gold_val, 512, 64 * num_layer);

  print_matrix_to_file(file_name + "L1_inA_matrix_2AXI.txt", host_L1_inA, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "L1_inB_matrix_2AXI.txt", host_L1_inB, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "L2_inB_matrix_2AXI.txt", host_L2_inB, 512, 64 * num_layer);
  print_matrix_to_file(file_name + "gold_L2_outC_2AXI.txt", gold_val, 512, 64 * num_layer);
}

void valid(float* host_outC_port, float* gold_val, size_t size) {
  int wrong_count = 0;
  for (int i = 0; i < size; i++) {
    if ((gold_val[i] - host_outC_port[i]) * (gold_val[i] - host_outC_port[i]) > 0.01) {
      if (wrong_count < 10) {
        std::cout << "Error: gold_val[" << i << "] = " << gold_val[i] << " != host_outC_port[" << i
                  << "] = " << host_outC_port[i] << std::endl;
      }
      wrong_count++;
    }
  }
  if (wrong_count > 0) {
    std::cout << "Validation failed! " << wrong_count << " errors found." << std::endl;
  } else {
    std::cout << "Validation passed!" << std::endl;
  }

  std::cout << "host_outC_port[0:7] = " << std::endl;
  for (int i = 0; i < 8; i++) {
    printf("%f ", host_outC_port[i]);
  }
  std::cout << "gold_val[0:7] = " << std::endl;
  for (int i = 0; i < 8; i++) {
    printf("%f ", gold_val[i]);
  }

  std::cout << std::endl;
}

void cal_mulweight_add_prev_layer(float* pre_layer, float* weight_mul_pre_layer, float* gold_val,
                                  int A, int B) {
  std::cout << "cal_mulweight_add_prev_layer" << std::endl;
  float* pre_layer_tmp = (float*)malloc(A * B * sizeof(float));
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < B; j++) {
      pre_layer_tmp[i * B + j] = pre_layer[i * B + j] * weight_mul_pre_layer[j];
    }
  }
  matrix_add(gold_val, pre_layer_tmp, A, B);
  free(pre_layer_tmp);
}

void generate_data_onelayer_norm(float* input, float* pre_layer, float* weight_mul_pre_layer,
                                 float* weight_dense, float* bias_dense, float* output,
                                 float* gold_val, ParamsOneLayer params) {
  std::cout << "generate_data_onelayer_norm" << std::endl;
  params.print();
  int A = params.getMatrixDim_A();
  int B = params.getMatrixDim_B();
  int K = params.getMatrixDim_K();

  std::cout << "init matrices" << std::endl;
  init_matrix(output, A, B, 0.0);
  init_matrix_blocked(input, A, K, 128, 64);
  init_matrix_blocked(pre_layer, A, B, 128, 512);
  init_matrix_blocked(weight_mul_pre_layer, 1, B, 1, 256);
  init_matrix_blocked(weight_dense, K, B, 128, 512);
  init_matrix_blocked(bias_dense, 1, B, 1, 256);

  // init_matrix(input, A, K, 0.0);
  // init_matrix(pre_layer, A, B, 0.0);
  // init_matrix(weight_mul_pre_layer, 1, B, 1.0);
  // init_matrix(weight_dense, K, B, 0.0);
  // init_matrix(bias_dense, 1, B, 0.0);

  // init_matrix_random(input, A, K);
  // init_matrix_random(pre_layer, A, B);
  // init_matrix_random(weight_mul_pre_layer, 1, B);
  // init_matrix_random(weight_dense, K, B);
  // init_matrix_random(bias_dense, 1, B);

  if (params.enable_bias == true) {
    std::cout << "NOT CALCULATE" << std::endl;
    // calculate_matrix_with_bias(input, weight_dense, bias_dense, gold_val, A, B, K);
  } else {
    calculate_matrix(input, weight_dense, gold_val, A, B, K);
  }

  if (params.enable_addmul_pre_layer == true) {
    cal_mulweight_add_prev_layer(pre_layer, weight_mul_pre_layer, gold_val, A, B);
  }

  if (params.enable_norm == true) {
    layer_normalization_no_weightbias(gold_val, A, B);
  }

  std::string file_name =
      "/home/cw4/github/versal-float32/19-gelu-norm-bias/design/pl_src/output/0_onelayer_";

  print_matrix_to_file(file_name + "input.txt", input, A, K);
  convert_simple_to_blocked_layout(input, A, K, 128, 64);
  print_matrix_to_file(file_name + "input_blocked.txt", input, A, K);
  convert_blocked_to_2AXI_layout(input, A, K);
  print_matrix_to_file(file_name + "input_2AXI.txt", input, A, K);

  print_matrix_to_file(file_name + "pre_layer.txt", pre_layer, A, B);
  convert_simple_to_blocked_layout(pre_layer, A, B, 128, 64);
  print_matrix_to_file(file_name + "pre_layer_blocked.txt", pre_layer, A, B);
  convert_blocked_to_2AXI_layout(pre_layer, A, B);
  print_matrix_to_file(file_name + "pre_layer_2AXI.txt", pre_layer, A, B);

  print_matrix_to_file(file_name + "weight_mul_pre_layer.txt", weight_mul_pre_layer, 1, B);

  print_matrix_to_file(file_name + "weight_dense.txt", weight_dense, K, B);
  convert_simple_to_blocked_layout(weight_dense, K, B, 128, 64);
  print_matrix_to_file(file_name + "weight_dense_blocked.txt", weight_dense, K, B);
  convert_blocked_to_2AXI_layout(weight_dense, K, B);
  print_matrix_to_file(file_name + "weight_dense_2AXI.txt", weight_dense, K, B);

  print_matrix_to_file(file_name + "bias_dense.txt", bias_dense, 1, B);

  print_matrix_to_file(file_name + "gold_val.txt", gold_val, A, B);
  convert_simple_to_blocked_layout(gold_val, A, B, 128, 64);
  print_matrix_to_file(file_name + "gold_val_blocked.txt", gold_val, A, B);
  convert_blocked_to_2AXI_layout(gold_val, A, B);
  print_matrix_to_file(file_name + "gold_val_2AXI.txt", gold_val, A, B);
}
