# ISCA25-Stream-Network-Arch

This repository provides an open-source implementation of **RSN-XNN** for the paper **Reconfigurable Stream Network Architecture**.

## Try RSN-XNN on the VCK190 Board with Ready-To-Go Image and Data

**Precompiled image and data** are available at Zenodo **(https://doi.org/10.5281/zenodo.15102698)**:
1. sd_card.img  
  Bootable image ready to be flashed to a microSD card for the VCK190 FPGA board. This image contains the precompiled bitstream for RSN-XNN.
2. python_gold.zip  
  A zipped package containing input, weights, and expected output data for running BERT-LARGE inference.

**Hardware Requirements**
1. FPGA Evaluation Board VCK190 
2. Local Computer for On-Board FPGA Evaluation  
   - Can be Linux Desktop/MacBook/Windows
   - Required capabilities:
     - Serial port (USB-UART) connection to VCK190
     - On the same local network as the VCK190 to enable SSH  
3. USB-C Cable 
   - For USB-UART connection between the local computer and VCK190  
4. Ethernet Cable  
   - Either connect VCK190 and the local computer directly  
   - **Or** connect both VCK190 and the local computer to the same router
5. microSD Card Adapter 
   - For flashing the microSD card on your local computer  


**VCK190 detailed installation and tutorials can be found in the official documentation**

VCK190 Evaluation Board User Guide (UG1366)
https://docs.amd.com/r/en-US/ug1366-vck190-eval-bd/Overview?tocId=j6sqKcAeZywOsdV9KLDvrg

Setting up the Board and Application Deployment
https://xilinx.github.io/vck190-ethernet-trd/2022.1/build/html/docs/platform/docs/app_deployment.html

**Step-by-Step Guide**

**Step 1:** Flash the microSD Card

Example (in macOS):
1. Insert the microSD card into your local computer (using the SD card adapter if needed).  
2. Identify the device name by running:
   ```bash
   diskutil list
   ```
   Suppose `/dev/disk4` is the microSD card.
3. Unmount the disk:
   ```bash
   diskutil unmountDisk /dev/disk4
   ```
4. Flash the image onto the card:
   ```bash
   sudo dd bs=4m if=sd_card.img of=/dev/disk4 conv=sync status=progress
   ```
5. Once complete, insert the microSD card into the VCK190 board.

**Step 2:** Log into the VCK190 via Serial Port

Example (in macOS):
1. Connect the USB-C cable between your local computer and the VCK190 board.  
2. Install [picocom](https://formulae.brew.sh/formula/picocom):
   ```bash
   brew install picocom
   ```
3. Find the serial port:
   ```bash
   ls /dev/tty.*
   ```
   You might see something like:
   ```
   /dev/tty.usbserial-2822031419610
   /dev/tty.usbserial-2822031419611
   /dev/tty.usbserial-2822031419612
   /dev/tty.usbserial-2822031419613
   ...
   ```
4. Start picocom (you can try all 4 ports to see which one prompts for the username):
   ```bash
   picocom -b 115200 -r -l /dev/tty.usbserial-2822031419611
   ```
5. The first time you log in, enter the username:
   ```
   petalinux
   ```
   Then set your password as prompted.

**Step 3:** Get the VCK190 Board’s IP Address

1. Connect the VCK190 to the router to which your local computer is connected.
2. In the VCK190’s terminal (via serial console), run:
   ```bash
   ifconfig
   ```
   Look for the `inet` address on `eth0`, for example `192.168.0.128`.

**Step 4:** Transfer Data to the VCK190

1. From your local computer, check if VCK190 is reachable:
   ```bash
   ssh petalinux@192.168.0.128
   ```
2. Transfer the python_gold.zip files to VCK190:
   ```bash
   scp -r python_gold.zip petalinux@192.168.0.128:~
   ```

**Step 5:** Run the Inference on the VCK190

1. Log into the VCK190 (via serial console or SSH).  
2. Copy `python_gold.zip` to `/home/root/`, then unzip:
   ```bash
   cp /home/petalinux/python_gold.zip /home/root/python_gold.zip
   cd /home/root
   unzip python_gold.zip
   ```
3. Switch to the root user:
   ```bash
   sudo su
   ```
4. Change directory to where the bitstream is located:
   ```bash
   cd /run/media/mmcblk0p1
   ```
5. Run the provided script:
   ```bash
   ./run_script.sh
   ```


## Generate Reference Data: Get `python_gold.zip` Using BERT_HuggingFace/ (Approximate 20 Minutes)

You can use **`isca25-rsn.sif`** (available at [Zenodo](https://doi.org/10.5281/zenodo.15102698))—a container with all the required packages installed to generate the `python_gold.zip` file.

1. Install apptainer
2. Build the sandbox container:
   ```bash
   apptainer build --sandbox isca25-rsn-sandbox isca25-rsn.sif
   ```
3. Specify `SANDBOX_LOC` and `CUR_RSN_WORKSPACE` in `env.sh`.
4. Run the BERT script:
   ```bash
   ./bert.sh
   ```

**Alternatively,** you can run it directly on a system with the necessary Python packages:

1. Install dependencies:
   ```bash
   apt install -y python3 python3-pip python3-venv
   pip install torch torchvision torchaudio transformers numpy
   ```
2. Run the script:
   ```bash
   cd BERT_HuggingFace
   rm -rf output
   rm -rf python_gold
   ./run.sh 6
   ./run.sh 8
   ./clean.sh
   ```

After completion, you should see a `python_gold/` folder under `BERT_HuggingFace/`, which is equivalent to the `python_gold.zip` file provided at [Zenodo](https://doi.org/10.5281/zenodo.15102698).




## Compile RSN-XNN: Generate `sd_card.img` Using **RSN-XNN-FPGA/** (May Take Over 12 Hours)

1. Prerequisites:
   - **AMD Vitis™ Unified Software Platform 2024.1**  
   - **Versal common image** (from *Common Images for Embedded Vitis™ Platforms - 2024.1*)  
   - **[Vitis_Libraries](https://github.com/Xilinx/Vitis_Libraries)**  
   - **Valid licenses** for the above software packages  

2. Configuration
   In `env.sh`, specify the following environment variables:
   - `CUR_RSN_WORKSPACE`: Path to the `ISCA25-Stream-Network-Arch` repository  
   - `VITIS_LIB`: Path to the directory where you git cloned `Vitis_Libraries`  
   - `XILINX_INSTALL_PATH`: Path where Vitis (and related tools like Vivado, Vitis_HLS) is installed; typically `/tools/Xilinx`  
   - `VERSAL_COMMON_LOC`: Path to the unzipped “Versal common image” (`xilinx-versal-common-v2024.1`) downloaded from  
     [Xilinx website](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-platforms/2024-1.html)  
   - `PETALINUX_INSTALL`: Installation path set when running `./sdk.sh` under `xilinx-versal-common-v2024.1`  
   - `BUILD_LOC`: Path where the runtime build files are stored, which can be frequently read and written (usually on the server, it is necessary to distinguish between IO intense files and read only files)

3. **If Using a Slurm Workload Manager**  
   - Open `fpga-submit.batch` and adjust the settings as supported by your system:
     ```bash
     #SBATCH --cpus-per-task=48
     #SBATCH --mem=180G
     #SBATCH -p batch
     #SBATCH -w c04
     ```
   - Submit the job:
     ```bash
     sbatch fpga-submit.batch
     ```

4. **If Not Using Slurm or Running in an Interactive Session**  
   - On your machine or via an interactive Slurm session (e.g., `srun -c48 --mem=180G --pty bash`), run:
     ```bash
     ./fpga.sh
     ```

5. After completion, you can find the compiled `sd_card.img` at: `RSN-XNN-FPGA/build/gemm_32x32x32/x1/hw/package/sd_card.img`



## Explanation for RSN-XNN-FPGA  
```
RSN-XNN-FPGA.........................top-level directory for RSN-XNN FPGA build
|__init_env.sh.......................script for sourcing environment variables
|__compile_hw.sh.....................launch command for hardware compilation
|__Makefile..........................top-level makefile with recipes for building the design
|__design............................contains all source code and configuration files for the design
   |__aie_src........................AI Engine source files (Runing at AIE)
   |__directives.....................additional build directives or constraints
   |__exec_scripts...................contains run_scripts.sh for launching the execution on VCK190
   |__host_app_src...................source code for the host application (Runing at CPU)
   |__pl_src.........................source code for the PL side (Runing at FPGA)
   |__profiling_configs..............contains xrt.ini configuration file
   |__system_configs.................specifies system-level connections between FPGA, AIE, and CPU 
   |__host_different_config..........alternative host_app_src folders for testing different problem settings
   |__dma_hls_csynth.rpt.............reference RSN-XNN report for HLS-based (C/C++) synthesis 
   |__full_util_routed.rpt...........reference RSN-XNN report containing overall resource utilization after routing

```
