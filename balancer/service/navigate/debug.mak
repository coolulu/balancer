#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := bin

#Toolchain
CC := gcc
CXX := g++
LD := $(CXX)
AR := ar
OBJCOPY := objcopy

#Additional flags
PREPROCESSOR_MACROS := 
INCLUDE_DIRS := ../../../depend/cpp/muduo ../../../depend/cpp/rapidjson/include ../../../depend/cpp/zlib ../../../depend/cpp/protobuf/src
LIBRARY_DIRS := ../../../depend/cpp/lib
LIBRARY_NAMES := pthread muduo_net_cpp11 muduo_base_cpp11 muduo_http z protobuf
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -O0 -std=c++11
CXXFLAGS := -ggdb -ffunction-sections -O0 -std=c++11
ASFLAGS := 
LDFLAGS := -Wl,-gc-sections
COMMONFLAGS := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
IS_LINUX_PROJECT := 1
