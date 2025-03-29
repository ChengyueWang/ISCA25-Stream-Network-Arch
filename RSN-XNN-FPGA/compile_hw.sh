#!/bin/bash

# Function to perform removal operations
# remove_files() {
#     rm -rf build/gemm_32x32x32/x1/hw/_x
#     rm build/gemm_32x32x32/x1/hw/dma_hls.hw.xo
#     rm -rf build/gemm_32x32x32/x1/hw/package
#     echo "Selected files and directories have been removed."
# }

# # Prompt user to confirm the removal
# read -p "Run remove operations? (y/n): " confirm
# if [[ "$confirm" =~ ^[Yy]$ ]]; then
#     remove_files
# else
#     echo "Skipping removal operations."
# fi

# Check if the user provided the required parameter for `PL_FREQ`
# if [ -z "$1" ]; then
#     echo "Error: Please provide the PL_FREQ value as the first argument."
#     exit 1
# fi

# Run the make command with the provided PL_FREQ
make kernels xsa package TARGET=hw EN_TRACE=1 PL_FREQ=$TARGET_FREQ


