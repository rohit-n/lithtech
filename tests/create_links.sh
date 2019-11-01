#!/bin/bash

R=(
tests/DynResDLL/libtestCRes.so
NOLF2/ClientRes/TO2/libCRes.so
)
S=(
tests/CShell/libCShell.so
NOLF2/ClientShellDLL/TO2/libCShell.so
)
RES=$(for f in ${R[@]}; do [[ "${f}" =~ ${1:-test} ]] && echo $f; done)
SHELL=$(for f in ${S[@]}; do [[ "${f}" =~ ${2:-test} ]] && echo $f; done)

ln -svfT ../sdk/rez/Engine.REZ ./engine.rez
ln -svfT ../test/NOLF2/game.rez ./game.rez
ln -svfT ${RES} ./libCRes.so
ln -svfT ${SHELL} ./libCShell.so
ln -svfT runtime/render_a/src/sys/ogl/libOGLRender.so ./libOGLRender.so
