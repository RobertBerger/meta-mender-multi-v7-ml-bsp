OE/Yocto Project/BitBake prerequisites
======================================

Install the required prerequisites as defined in the Yocto Project manual for your build host:

https://www.yoctoproject.org/docs/latest/mega-manual/mega-manual.html#required-packages-for-the-build-host

Preferred lab setup
===================

Ideally you have a DHCP server which gives out IP addresses when booting from SD card.

Mender setup
============

I used a self hosted Mender Production Server.

Please follow the instructions here:

https://docs.mender.io/1.7/getting-started/requirements

https://docs.mender.io/1.7/administration/production-installation

https://docs.mender.io/1.7/artifacts/yocto-project/building-for-production

I added a layer with the keys called my-mender-layer.

variables
=========

```bash
#export BSP_BRANCH="thud-training-v4.19.x-next"
export BSP_BRANCH="master"

export POKY_BRANCH="2019-01-16-thud-2.6.1-pre-release"

export MENDER_BRANCH="thud"
```

poky
====

```bash
git clone git://github.com/RobertBerger/poky.git -b ${POKY_BRANCH}
```

meta-mender-multi-v7-ml-bsp
===========================

```bash
cd poky

git clone git://github.com/RobertBerger/meta-mender-multi-v7-ml-bsp.git -b ${BSP_BRANCH}
```

meta-mender
===========

```bash
git clone git://github.com/mendersoftware/meta-mender.git -b ${MENDER_BRANCH}
```

my-mender-layer
===============

Well you need your own here.
This is where you would git clone it.

supported BOARDS
================

```bash
ls meta-mender-multi-v7-ml-bsp/conf/machine/
```
```bash
am335x-phytec-wega.conf  beagle-bone-black.conf  beagle-bone-green.conf  common.inc  imx6q-phytec-mira-rdk-nand.conf
```
so we have those choices:

* am335x-phytec-wega

* beagle-bone-black

* beagle-bone-green

* imx6q-phytec-mira-rdk-nand

more might be added.

initial config
==============

for beagle-bone-black:

```bash
export BOARD="beagle-bone-black"

export TEMPLATECONF="meta-mender-multi-v7-ml-bsp/template-${BOARD}"

source oe-init-build-env ${BOARD}
```
My template adds ```my-mender-layer``` to ```conf/bblayers.conf```.
You might need to adjust this if necessary:

```bash
vim conf/bblayers.conf
```

Inspect/change if necessary ```site.conf```:

```bash
cp ../meta-mender-multi-v7-ml-bsp/template-common/site.conf.sample conf/site.conf
```

You might need to adjust the site.conf or better the site.conf.sample once it works for you.

Most likely you want to point DL_DIR and SSTATE_DIR to some dir which is non-volatile
and where you have write permissions. If you don't know what they are, just comment them out.

```bash
#DL_DIR = "/tmp/yocto-autobuilder/downloads"
#SSTATE_DIR ?= "/tmp/yocto-autobuilder/sstate/"
```

If you don't know what are mirros you most likely don't have any set up so comment this out:

```bash
#INHERIT += "own-mirrors"
#SOURCE_MIRROR_URL = "http://mirror/source_mirror_thud"
#SSTATE_MIRRORS ?= "file://.* http://mirror/sstate_mirror_thud/PATH;downloadfilename=PATH"
```

Mender requires systemd so those lines should be enabled in your conf/local.conf:

```bash
DISTRO_FEATURES_append = " systemd"
VIRTUAL-RUNTIME_init_manager = "systemd"
DISTRO_FEATURES_BACKFILL_CONSIDERED = "sysvinit"
VIRTUAL-RUNTIME_initscripts = ""
```

build
=====

```bash
bitbake core-image-minimal
```

The result of the build can be found under

```console
tmp/deploy/images/${BOARD}
```

flash
=====

I usually use the CLI for Etcher to flash the image, but with the GUI it should work as well.

If you don't already have it, download

https://www.balena.io/etcher/

And install it somewhere.

I would do the following in order to flash my image:

```bash
cd tmp/deploy/images/${BOARD}

sudo /opt/etcher/Etcher-cli-1.2.0-linux-x64/etcher core-image-minimal-${BOARD}.wic
```

first boot
==========

beagle-bone-black:

* press S2 while applying power to force booting from SD card


The system should start up and boot from SD card.


Tests
=====

```console
sysvinit:

				uenvcmd_mmc_all		uenvcmd_tftp_nfs

am335x-phytec-wega		OK			OK

beagle-bone-black 		OK			OK

mx6q-phytec-mira-rdk-nand       [1] OK                  [2]
```

[1] -->

loads by default uEnv from SPI flash

In order to use whats on the SD card:

Stop U-Boot from booting

```bash
# reset u-boot env
=> env default -a

# load uEnv.txt
=> ext4load mmc 0:1 0x18000000 uEnv.txt
=> env import -t 0x18000000 ${filesize}

# boot from SD card
=> run uenvcmd_mmc_all
```
------------
```bash
# to make it permanent

# reset u-boot env
=> env default -a

# load uEnv.txt
=> ext4load mmc 0:1 0x18000000 uEnv.txt
=> env import -t 0x18000000 ${filesize}

=> printe uenvcmd
uenvcmd=run uenvcmd_mmc_all

=> setenv bootcmd 'run uenvcmd'
=> saveenv
=> reset
```
[1] <--

[2] -->

Stop U-Boot from booting

```bash
# boot from SD card
=> run uenvcmd_tftp_nfs
```

------------

```bash
# to make it permanent

=> printe uenvcmd
uenvcmd=run uenvcmd_tftp_nfs

=> saveenv
=> reset
```
[2] <--

--------------------------------------------------------------------------
```console
systemd:

                        	uenvcmd_mmc_all         uenvcmd_tftp_nfs

beagle-bone-black		OK                             
```
