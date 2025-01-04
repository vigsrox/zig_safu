#!/bin/bash
set -e -u

CMD_PATH=$(realpath "$(dirname "$0")")
BASE_DIR=${CMD_PATH}
ZIG_BUILD_PARAM=${ZIG_BUILD_PARAM:-"-j$(nproc)"}

BUILD_TYPE="${1:-Debug}"

BUILD_DIR="$BASE_DIR/build/$BUILD_TYPE"
RESULT_DIR="$BUILD_DIR/result"
DIST_DIR="$BUILD_DIR/dist"
export LOCAL_INSTALL_DIR=${LOCAL_INSTALL_DIR:-"${DIST_DIR}"}

echo -e "\n#### Building safu ($BUILD_TYPE) ####"
mkdir -p "$RESULT_DIR" "$DIST_DIR"
DEST_DIR="${LOCAL_INSTALL_DIR}" 
zig build --prefix ${DEST_DIR} -Doptimize=${BUILD_TYPE} ${ZIG_BUILD_PARAM} --summary all 2>&1 | tee "$RESULT_DIR/build_log.txt"

re=${PIPESTATUS[0]}

exit "$re"
