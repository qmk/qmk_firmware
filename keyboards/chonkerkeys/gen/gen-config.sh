#!/bin/bash -e

if [[ "$FIRMWARE_CONFIG_OUTPUT" == "" ]]
then
    FIRMWARE_CONFIG_OUTPUT="config.c"
fi

TARGET=$1

if [[ "$TARGET" == "" ]]
then
    echo "fatal: Missing target. Usage: gen-config [gen,gen-original,gen-max]"
    exit 1
fi

if [[ "$TARGET" == "gen" ]]
then
    echo "generating custom config..."
	python gen/src/ch-qmk-gen.py --firmware-version=$FIRMWARE_VERSION --config=$FIRMWARE_CONFIG --output=$FIRMWARE_CONFIG_OUTPUT
elif [[ "$TARGET" == "gen-original" ]]
then
    echo "generating original config..."
    python gen/src/ch-qmk-gen.py --firmware-version=1 --output=$FIRMWARE_CONFIG_OUTPUT --config="{ \
		\"layers\":[\"CH_ZOOM_WINDOWS\", \"CH_ZOOM_MACOS\"], \
		\"sizeOrdinals\": [ \
			[ \
				[0, 0, 129, 1], \
				[1, 0, 67, 65] \
			], \
			[ \
				[0, 0, 129, 1], \
				[1, 0, 67, 65] \
			] \
		], \
		\"keymaps\": [ \
   			[ \
        		[\"KC_NO\", \"KC_NO\", \"CH_ZOOM_LEAVE_MEETING\", \"CH_ZOOM_RAISE_HAND_TOGGLE\"], \
        		[\"CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE\", \"KC_NO\", \"CH_ZOOM_VIDEO_TOGGLE\", \"CH_ZOOM_MUTE_TOGGLE\"] \
    		], \
    		[ \
        		[\"CH_ZOOM_RAISE_HAND_TOGGLE\", \"CH_ZOOM_LEAVE_MEETING\", \"KC_NO\", \"KC_NO\"], \
        		[\"CH_ZOOM_MUTE_TOGGLE\", \"CH_ZOOM_VIDEO_TOGGLE\", \"KC_NO\", \"CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE\"] \
    		] \
		] \
	}"
elif [[ "$TARGET" == "gen-max" ]]
then
    echo "generating max config..."
    python gen/src/ch-qmk-gen.py --firmware-version=1 --output=$FIRMWARE_CONFIG_OUTPUT --config="{ \
		\"layers\":[\"CH_ZOOM_WINDOWS\", \"CH_ZOOM_MACOS\"], \
		\"sizeOrdinals\": [ \
			[ \
				[0, 0, 129, 0], \
				[1, 1, 1, 68], \
				[1, 1, 1, 68] \
			], \
			[ \
				[0, 0, 129, 0], \
				[1, 1, 1, 68], \
				[1, 1, 1, 68] \
			] \
		], \
		\"keymaps\": [ \
   			[ \
        		[\"KC_NO\", \"KC_NO\", \"CH_ZOOM_LEAVE_MEETING\", \"KC_NO\"], \
        		[\"KC_NO\", \"KC_NO\", \"CH_ZOOM_RAISE_HAND_TOGGLE\", \"CH_ZOOM_VIDEO_TOGGLE\"], \
        		[\"KC_NO\", \"KC_NO\", \"CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE\", \"CH_ZOOM_MUTE_TOGGLE\"] \
    		], \
    		[ \
        		[\"KC_NO\", \"CH_ZOOM_LEAVE_MEETING\", \"KC_NO\", \"KC_NO\"], \
        		[\"CH_ZOOM_VIDEO_TOGGLE\", \"CH_ZOOM_RAISE_HAND_TOGGLE\", \"KC_NO\", \"KC_NO\"], \
        		[\"CH_ZOOM_MUTE_TOGGLE\", \"CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE\", \"KC_NO\", \"KC_NO\"] \
    		] \
		] \
	}"
fi
