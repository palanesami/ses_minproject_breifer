# ses_minproject_briefer

## Overview 
> Briefer is the module intended to briefer the day activity or summary.
> It interfaces raspberry module with 16X2 LCD display. 
> LCD display is controlled through the GPIO interfaces.
> Exported the GPIO thru linux sys filesystem.
> Any 16 characters given from the application will be displayed.
> Application should extract the necessay data and do the api call with intended data.

## TOOLCHAIN 
> x-tools-aarch64-rpi3-linux-gnu-gcc14.tar.xz

## ENVIRONMENT SETUP
> untar in /opt/palanesami/
> export PATH=$PATH:/opt/palanesami/x-tools/aarch64-rpi3-linux-gnu/bin

## EXECUTE IN LINUX

> cmake . -DCMAKE_C_FLAGS="-v -std=gnu99 -I/opt/palanesami/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot/usr/include/ -L/opt/palanesami/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot/usr/lib -Werror"

> make

## EXECUTE IN RASPBERRY PI BOARD
> ./briefer “BITS”
