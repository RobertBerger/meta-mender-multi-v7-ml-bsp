inherit kernel
require recipes-kernel/linux/linux-yocto.inc

SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git;protocol=git;bareclone=1;branch=${KBRANCH}"

# SRC_URI += "file://defconfig"

SRC_URI += "file://multi-v7-ml-mender-bsp.scc \
            file://multi-v7-ml-mender-bsp.cfg \
           "
# multi-v7-ml-mender-bsp-user-config.cfg and
# multi-v7-ml-mender-bsp-user-patches.scc are
# included by multi-v7-ml-mender-bsp.scc
# removed from SRC_URI to avoid double inclusion
# and like this avoiding applying same patch twice

LINUX_VERSION_EXTENSION ?= "-custom"

PV = "${LINUX_VERSION}+git${SRCPV}"

# Let's try an in-tree defconfig:
KERNEL_DEFCONFIG ?= "multi_v7_defconfig"
KBUILD_DEFCONFIG ?= "multi_v7_defconfig"
KCONFIG_MODE="--alldefconfig"

COMPATIBLE_MACHINE_am335x-phytec-wega = "am335x-phytec-wega"
COMPATIBLE_MACHINE_imx6q-phytec-mira-rdk-nand = "imx6q-phytec-mira-rdk-nand"
COMPATIBLE_MACHINE_beagle-bone-black = "beagle-bone-black"
COMPATIBLE_MACHINE_beagle-bone-green = "beagle-bone-green"
COMPATIBLE_MACHINE_beagle-bone-black-wireless = "beagle-bone-black-wireless"
