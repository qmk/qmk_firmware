#!/bin/sh
# NOTE: This script uses tabs for indentation

errcho() {
	echo "$@" >&2
}

USAGE="Usage: $0 [keyboard[:keymap[:target]]]"

# Check preconditions
for arg; do
	if [ "$arg" = "--help" ]; then
		echo "$USAGE"
		exit 0
	fi
done
if [ $# -gt 1 ]; then
	errcho "$USAGE"
	exit 1
fi

# Allow $RUNTIME to be overriden by the user as an environment variable
# Else check if either docker or podman exit and set them as runtime
# if none are found error out
if [ -z "$RUNTIME" ]; then
	if command -v docker >/dev/null 2>&1; then
		RUNTIME="docker"
	elif command -v podman >/dev/null 2>&1; then
		RUNTIME="podman"
	else
		errcho "Error: no compatible container runtime found."
		errcho "Either podman or docker are required."
		errcho "See https://podman.io/getting-started/installation"
		errcho "or https://docs.docker.com/install/#supported-platforms"
		errcho "for installation instructions."
		exit 2
	fi
fi
	

# Determine arguments
if [ $# -eq 0 ]; then
	printf "keyboard=" && read -r keyboard
	[ -n "$keyboard" ] && printf "keymap=" && read -r keymap
	[ -n "$keymap"   ] && printf "target=" && read -r target
else
	IFS=':' read -r keyboard keymap target x <<-EOF
	$1
	EOF
	if [ -n "$x" ]; then
		errcho "$USAGE"
		exit 1
	fi
fi
if [ -z "$keyboard" ]; then
	keyboard=all
fi
if [ -n "$target" ]; then
	# IF we are using docker on non Linux and docker-machine isn't working print an error
	# ELSE set usb_args
	if [ ! "$(uname)" = "Linux" ] && [ "$RUNTIME" = "docker" ] && ! docker-machine active >/dev/null 2>&1; then
		errcho "Error: target requires docker-machine to work on your platform"
		errcho "See http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos"
		errcho "Consider flashing with QMK Toolbox (https://github.com/qmk/qmk_toolbox) instead"
		exit 3
	else
		usb_args="--privileged -v /dev:/dev"
	fi
fi
dir=$(pwd -W 2>/dev/null) || dir=$PWD  # Use Windows path if on Windows

if [ "$RUNTIME" = "docker" ]; then
	uid_arg="--user $(id -u):$(id -g)"
fi

# Run container and build firmware
"$RUNTIME" run --rm -it $usb_args \
	$uid_arg \
	-w /qmk_firmware \
	-v "$dir":/qmk_firmware \
	-e ALT_GET_KEYBOARDS=true \
	-e SKIP_GIT="$SKIP_GIT" \
	-e MAKEFLAGS="$MAKEFLAGS" \
	qmkfm/qmk_cli \
	make "$keyboard${keymap:+:$keymap}${target:+:$target}"
