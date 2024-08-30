# ses_minproject_breifer

## TOOLCHAIN 
> x-tools-aarch64-rpi3-linux-gnu-gcc14.tar.xz

## ENVIRONMENT SETUP
> untar in /opt/palanesami/
> export PATH=$PATH:/opt/palanesami/x-tools/aarch64-rpi3-linux-gnu/bin

## EXECUTE IN LINUX

> cmake . -DCMAKE_C_FLAGS="-v -std=gnu99 -I/opt/palanesami/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot/usr/include/ -L/opt/palanesami/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot/usr/lib -Werror"

make

## EXECUTE IN RASPBERRY PI BOARD
> ./briefer
