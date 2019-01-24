#@TYPE: Machine
#@NAME: common include file for all (compatible) machines

#@DESCRIPTION: Machine configuration for mender/multi-v7 compatible systems

# please note, that multi-v7 is dummy machine
# and actually just a copy of imx6q-phytec-mira-rdk-nand
# we try to build multi-v7 images, which are supposed to run
# on all the boards
# but can still load board specific images on boards
@ the prompt (multi-v7) or (${MACHINE}) should show the running image

# the default MACHINE_EXTRA_RRECOMMENDS
# would not install the kernel modules on the core-image-minimal rootfs
# we could also build a core-image-basic to get them included or:
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " kernel-modules kernel-devicetree"

# we also want to build u-boot
EXTRA_IMAGEDEPENDS += "u-boot"

DEFAULTTUNE = "armv7a-neon"
include conf/machine/include/arm/arch-armv7a.inc

IMAGE_FSTYPES += "sdimg"

# zedboard:  ttyPS0
# sitara:    ttyO0
# i.mx6:     ttymxc1
# i.mx6 wand:ttymxc0
# cyclone-v: ttyS0

SERIAL_CONSOLES = "115200;ttyPS0 115200;ttyO0 115200;ttymxc1 115200;ttymxc0 115200;ttyS0"
SERIAL_CONSOLES_CHECK = "${SERIAL_CONSOLES}"

#PREFERRED_VERSION_u-boot ?= "2018.07%"
#PREFERRED_PROVIDER_u-boot-mkimage-native ?= "u-boot-mkimage-native"

PREFERRED_VERSION_u-boot ?= "2018.11%"
PREFERRED_PROVIDER_u-boot-mkimage-native ?= "u-boot-tools-native"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-yocto-custom"

# kernel version
KERNEL_VERSION_PATCHLEVEL="4.19"
KERNEL_SUBLEVEL="13"
PREFERRED_VERSION_linux-yocto-custom = "${KERNEL_VERSION_PATCHLEVEL}.${KERNEL_SUBLEVEL}%"

KERNEL_IMAGETYPE = "zImage"
# Mender says:
# .Found more than one dtb specified in KERNEL_DEVICETREE. 
# .Only one should be specified. Choosing the last one.
# .!!! The device tree which belongs to the board has to be last !!!

# add new device tree once here
KERNEL_DEVICE_TREE_ALL = "am335x-boneblack.dtb \
                          am335x-bonegreen.dtb \
                          am335x-wega-rdk.dtb \
			  imx6q-phytec-mira-rdk-nand.dtb \
			 "
# add new device tree per MACHINE here - at the end:
KERNEL_DEVICETREE_am335x-phytec-wega = "${KERNEL_DEVICE_TREE_ALL} am335x-wega-rdk.dtb"
KERNEL_DEVICETREE_imx6q-phytec-mira-rdk-nand = "${KERNEL_DEVICE_TREE_ALL} imx6q-phytec-mira-rdk-nand.dtb"
KERNEL_DEVICETREE_multi-v7 = "${KERNEL_DEVICE_TREE_ALL} imx6q-phytec-mira-rdk-nand.dtb"
KERNEL_DEVICETREE_beagle-bone-black = "${KERNEL_DEVICE_TREE_ALL} am335x-boneblack.dtb"
KERNEL_DEVICETREE_beagle-bone-green = "${KERNEL_DEVICE_TREE_ALL} am335x-bonegreen.dtb"

# SPL_BINARY:
SPL_BINARYNAME_am335x-phytec-wega = "MLO"
SPL_BINARYNAME_imx6q-phytec-mira-rdk-nand = "SPL"
SPL_BINARYNAME_multi-v7 = "SPL"
SPL_BINARYNAME_beagle-bone-black = "MLO"
SPL_BINARYNAME_beagle-bone-green = "MLO"
SPL_BINARYNAME_beagle-bone-black-wireless = "MLO"
SPL_BINARY = "${SPL_BINARYNAME}"

# UBOOT_SUFFIX:
UBOOT_SUFFIX = "img"

# UBOOT defconfig:
UBOOT_MACHINE_am335x-phytec-wega = "pcm051_rev3_defconfig"
UBOOT_MACHINE_imx6q-phytec-mira-rdk-nand = "pcm058_defconfig"
UBOOT_MACHINE_multi-v7 = "pcm058_defconfig"
UBOOT_MACHINE_beagle-bone-black = "am335x_evm_defconfig"
UBOOT_MACHINE_beagle-bone-green = "am335x_evm_defconfig"

# added some default MACHINE_FEATURES
MACHINE_FEATURES = "usbgadget usbhost vfat alsa"

IMAGE_BOOT_FILES = "${KERNEL_IMAGETYPE} ${KERNEL_DEVICETREE}"
