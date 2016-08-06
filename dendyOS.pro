TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    console/console.c \
    gdt/gdt.c \
    idt/idt.c \
    io/io.c \
    kernel/c/kmain.c \
    utility/utility.c

HEADERS += \
    console/console.h \
    gdt/gdt.h \
    idt/idt.h \
    io/io.h \
    kernel/c/kmain.h \
    utility/utility.h

DISTFILES += \
    makefile \
    kernel/asm/loader.s
