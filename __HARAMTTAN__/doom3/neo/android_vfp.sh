#!/bin/bash
# build hard-float vfp
set -e

export TOOLCHAIN=/opt/ndk/android_gcc_32
export ARCH=arm-linux-androideabi
export PATH=${TOOLCHAIN}/bin:${TOOLCHAIN}/${ARCH}/bin:${PATH}
export CXX=$ARCH-g++
export CC=$ARCH-gcc
#export CXX=g++
#export CC=gcc

	#BASEFLAGS='-march=armv5te -fno-builtin-sin -fno-builtin-sinf -fno-builtin-cosf -fno-builtin-cos -mtune=xscale -mfpu=vfp -mfloat-abi=softfp -Wl,--no-undefined -fexceptions -frtti -I/prog/games/dante-es2/libogg/include -L/prog/games/dante-es2/libogg/lib'\
scons \
	ARCH='arm' \
	BUILD='release' \
	\
	CC=$CC \
	CXX=$CXX \
	\
	NOCURL=1 \
	TARGET_ANDROID=1 \
	TARGET_D3XP=1 \
	BASEFLAGS='-march=armv5te -fno-builtin-sin -fno-builtin-sinf -fno-builtin-cosf -fno-builtin-cos -mtune=xscale -mfpu=vfp -mfloat-abi=softfp -Wl,--no-undefined -fexceptions -frtti -I/prog/games/dante-es2/libogg/include -L/prog/games/dante-es2/libogg/lib'\
	$*
