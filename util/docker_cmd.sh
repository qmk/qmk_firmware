#!/bin/sh
# vim: set ft=sh ts=4 sw=4 noexpandtab
# NOTE: This script uses tabs for indentation

errcho() {
	echo "$@" >&2
}

USAGE="Usage: $0 <command>"

# Check preconditions
for arg; do
	if [ "$arg" = "--help" ]; then
		echo "$USAGE"
		exit 0
	fi
done

# Allow $RUNTIME to be overridden by the user as an environment variable
# Else check if either podman or docker exit and set them as runtime
# if none are found error out
if [ -z "$RUNTIME" ]; then
	if command -v podman >/dev/null 2>&1; then
		RUNTIME="podman"
	elif command -v docker >/dev/null 2>&1; then
		RUNTIME="docker"
	else
		errcho "Error: no compatible container runtime found."
		errcho "Either podman or docker are required."
		errcho "See https://podman.io/getting-started/installation"
		errcho "or https://docs.docker.com/install/#supported-platforms"
		errcho "for installation instructions."
		exit 2
	fi
fi


# IF we are using docker on non Linux and docker-machine isn't working print an error
# ELSE set usb_args
if [ ! "$(uname)" = "Linux" ] && [ "$RUNTIME" = "docker" ] && ! docker-machine active >/dev/null 2>&1; then
	errcho "Error: target requires docker-machine to work on your platform"
	errcho "See http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos"
	exit 3
else
	usb_args="--privileged -v /dev:/dev"
fi

qmk_firmware_dir=$(pwd -W 2>/dev/null) || qmk_firmware_dir=$PWD  # Use Windows path if on Windows
qmk_userspace_dir=""
userspace_docker_args=""

if [ -n "$QMK_USERSPACE" ] && [ -e "$QMK_USERSPACE/qmk.json" ]; then
	qmk_userspace_dir=$(cd "$QMK_USERSPACE" && pwd -W 2>/dev/null) || qmk_userspace_dir=$QMK_USERSPACE  # Use Windows path if on Windows
elif [ -n "$(which qmk 2>/dev/null)" ] && [ -n "$(qmk userspace-path)" ]; then
	qmk_userspace_dir=$(cd "$(qmk userspace-path)" && pwd -W 2>/dev/null) || qmk_userspace_dir=$(qmk userspace-path)  # Use Windows path if on Windows
fi

if [ -n "$qmk_userspace_dir" ]; then
	userspace_docker_args="-v $qmk_userspace_dir:/qmk_userspace:z -e QMK_USERSPACE=/qmk_userspace"
fi

if [ "$RUNTIME" = "docker" ]; then
	uid_arg="--user $(id -u):$(id -g)"
fi

# Run container and build firmware
"$RUNTIME" run --rm -it \
	$usb_args \
	$uid_arg \
	-w /qmk_firmware \
	-v "$qmk_firmware_dir":/qmk_firmware:z \
	$userspace_docker_args \
	-e SKIP_GIT="$SKIP_GIT" \
	-e SKIP_VERSION="$SKIP_VERSION" \
	-e MAKEFLAGS="$MAKEFLAGS" \
	ghcr.io/qmk/qmk_cli \
	"$@"
