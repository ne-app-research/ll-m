#! /bin/sh

## To be used for curl -fsSL https://install.ll.ne-app.eu | sh

echo "==> LL-M: DOWNLOADING REPOSITORY..."

ORG=ne-app-research
PROFILE=release

MKDIR=mkdir

SRC=ll-m
VCS=git
FLAGS=clone --recurse-submodules -j8
DIST=ll-${ORG}-${PROFILE}

${MKDIR} ${DIST}

${GIT} ${FLAGS} https://github.com/ne-app-research/${SRC}.git ${DIST}/${SRC}
