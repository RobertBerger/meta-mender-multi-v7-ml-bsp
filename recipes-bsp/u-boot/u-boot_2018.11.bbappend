# In this version of U-Boot we don't need this mender patch:

SRC_URI_remove := "file://0006-env-Kconfig-Add-descriptions-so-environment-options-.patch"

# U-Boot version specific patches for all machines:

FILESEXTRAPATHS_prepend := "${THISDIR}/${PV}:"

# In case you want to create something with mkimage this restores
# backwards compatibility, which was broken in U-Boot 2018.11

SRC_URI_append = "\
     file://0001-New-item-at-list-end-for-backwards-compatibility.patch \
"

# U-Boot verssion and machine specific changes:

FILESEXTRAPATHS_prepend := "${THISDIR}/${PV}/${MACHINE}:"

# patches
# appends and += do not play well;)
#SRC_URI_append_am335x-phytec-wega = " \
#    file://0001-read-env-from-ext4.patch \
#"

# this would be the hack for lava
# try to solve this on the lava end
# sample see 2017.06 dir beagle bone black
#SRC_URI_append_beagle-bone-black = " \
#        file://0001-read-env-from-ext4.patch \
#        file://0002-default-AUTOBOOT_PROMPT-for-LAVA.patch \
#        file://0003-SYS_PROMPT-LAVA-compatible.patch \
#"

#SRC_URI_append_beagle-bone-black = " \
#    file://0001-read-env-from-ext4.patch \
#"

SRC_URI_append_beagle-bone-black = " \
	file://0001-removed-ENV_IS_IN_FAT.patch \
"

SRC_URI_append_beagle-bone-green = " \
        file://0001-removed-ENV_IS_IN_FAT.patch \
"

SRC_URI_append_beagle-bone-black-wireless = " \
        file://0001-removed-ENV_IS_IN_FAT.patch \
"

SRC_URI_append_imx6q-phytec-mira-rdk-nand = " \
	file://0001-try-to-fix-CONFIG_ENV_IS_IN_MMC.patch \
"
