#!/bin/bash
### You can also run fpga.sh directly after logging into the server in interactive mode using: srun -c48 --mem=180G --pty bash
source env.sh 
source $CUR_RSN_WORKSPACE/env.sh
source $CUR_RSN_WORKSPACE/RSN-XNN-FPGA/init_env.sh
cd $CUR_RSN_WORKSPACE/RSN-XNN-FPGA/ 
source compile_hw.sh
cp -R $BUILD_LOC $CUR_RSN_WORKSPACE/RSN-XNN-FPGA
