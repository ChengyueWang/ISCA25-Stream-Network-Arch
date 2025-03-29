unset LD_LIBRARY_PATH

# export XILINX_VITIS=/tools/Xilinx/Vitis/2024.1
export XILINX_VITIS=$XILINX_INSTALL_PATH/Vitis/2024.1
export DSPLIB_VITIS=$VITIS_LIB
export COMMON_IMAGE_VERSAL=$VERSAL_COMMON_LOC
source $PETALINUX_INSTALL/2024.1/environment-setup-cortexa72-cortexa53-xilinx-linux
tgt_plat=xilinx_vck190_base_202410_1

export PLATFORM_REPO_PATHS=$XILINX_VITIS/base_platforms
export ROOTFS=$COMMON_IMAGE_VERSAL/rootfs.ext4
export IMAGE=$COMMON_IMAGE_VERSAL/Image
source $XILINX_VITIS/settings64.sh
export PLATFORM=$PLATFORM_REPO_PATHS/$tgt_plat/$tgt_plat\.xpfm

echo ""
echo "Aiecompiler:"
which aiecompiler
echo ""
echo "Vivado:"
which vivado
echo ""
echo "Vitis:"
which vitis
echo ""
echo "Vitis HLS:"
which vitis_hls
echo ""
echo ""
echo "DSPLIBS"
echo "$DSPLIB_VITIS"
echo ""
