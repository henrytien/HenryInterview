#!/bin/sh

set_-x

SOURCE_DIR='../'
BUILD_DIR=${BUILD_DIR:-build}

mkdir -p $BUILD_DIR \
    && cd $BUILD_DIR \
    && cmake $SOURCE_DIR \
    && make $*
    