{
    "name": "Timeless 82",
    "vendorId": "0xFFFE",
    "productId": "0x003C",
    "keycodes": ["qmk_lighting"],
    "menus": [
      {
        "label": "Lighting",
        "content": [
          {
            "label": "Backlight",
            "content": [
              {
                "label": "Brightness",
                "type": "range",
                "options": [0, 255],
                "content": ["id_qmk_rgb_matrix_brightness", 3, 1]
              },
              {
                "label": "Effect",
                "type": "dropdown",
                "content": ["id_qmk_rgb_matrix_effect", 3, 2],
                "options": [
                    ["All Off", 0],
                    ["SOLID_COLOR", 1],
                    ["BREATHING", 2],
                    ["CYCLE_ALL", 3],
                    ["CYCLE_LEFT_RIGHT", 4],
                    ["CYCLE_UP_DOWN", 5],
                    ["RAINBOW_MOVING_CHEVRON", 6],
                    ["CYCLE_OUT_IN", 7],
                    ["CYCLE_OUT_IN_DUAL", 8],
                    ["CYCLE_PINWHEEL", 9],
                    ["CYCKE_SPIRAL", 10],
                    ["DUAL_BEACON", 11],
                    ["RAINBOW_BEACON", 12],
                    ["RAINDROPS", 13],
                    ["TYPING_HEATMAP", 14],
                    ["SOLID_REACTIVE_SIMPLE", 15],
                    ["SOLID_REACTIVE", 16],
                    ["SOLID_REACTIVE_NEXUS", 17],
                    ["MATRIX_MULTISPLASH", 18]
                  ]
              },
              {
                "showIf": "{id_qmk_rgb_matrix_effect} != 0",
                "label": "Effect Speed",
                "type": "range",
                "options": [0, 255],
                "content": ["id_qmk_rgb_matrix_effect_speed", 3, 3]
              },
              {
                "showIf": "{id_qmk_rgb_matrix_effect} != 0 && {id_qmk_rgb_matrix_effect} != 24 && {id_qmk_rgb_matrix_effect} != 28 && {id_qmk_rgb_matrix_effect} != 29 && {id_qmk_rgb_matrix_effect} != 32",
                "label": "Color",
                "type": "color",
                "content": ["id_qmk_rgb_matrix_color", 3, 4]
              }
            ]
          }
        ]
      }
    ],
    "matrix": {"rows": 6, "cols": 16},
    "customKeycodes": [
        {"name":"BT_HOST1","title":"BT_HOST1","shortName":"BT_HOST1"},
        {"name":"BT_HOST2","title":"BT_HOST2","shortName":"BT_HOST2"},
        {"name":"BT_HOST3","title":"BT_HOST3","shortName":"BT_HOST3"},
        {"name":"BT_2_4G", "title":"BT_2_4G", "shortName":"BT_2_4G"},
        {"name":"BT_USB",  "title":"BT_USB",  "shortName":"BT_USB"},
        {"name":"BT_VOL",  "title":"BT_VOL",  "shortName":"BT_VOL"},
        {"name":"LCD_HOME,",  "title":"LCD_HOME",  "shortName":"LCD_HOME"},
        {"name":"LCD_PAGE,",  "title":"LCD_PAGE",  "shortName":"LCD_PAGE"}
    ],
    "layouts": {
        "labels": [
            "ISO Enter",
            "Split Left Shift"
        ],
        "keymap":
        [
            [
              {
                "x": 2.5,
                "c": "#777777"
              },
              "0,0",
              {
                "x": 0.25,
                "c": "#cccccc"
              },
              "0,1",
              "0,2",
              "0,3",
              "0,4",
              "0,5",
              "0,6",
              "0,7",
              "0,8",
              "0,9",
              "0,10",
              "0,11",
              "0,12",
              {
                "x": 2.25
              },
              "0,15\n\n\n\n\n\n\n\n\ne0"
            ],
            [
              {
                "y": 0.25,
                "x": 2.5
              },
              "1,0",
              "1,1",
              "1,2",
              "1,3",
              "1,4",
              "1,5",
              "1,6",
              "1,7",
              "1,8",
              "1,9",
              "1,10",
              "1,11",
              "1,12",
              {
                "c": "#aaaaaa",
                "w": 2
              },
              "1,13",
              {
                "x": 0.5,
                "c": "#cccccc"
              },
              "1,15"
            ],
            [
              {
                "x": 2.5,
                "c": "#aaaaaa",
                "w": 1.5
              },
              "2,0",
              {
                "c": "#cccccc"
              },
              "2,1",
              "2,2",
              "2,3",
              "2,4",
              "2,5",
              "2,6",
              "2,7",
              "2,8",
              "2,9",
              "2,10",
              "2,11",
              "2,12",
              {
                "w": 1.5
              },
              "2,13\n\n\n0,0",
              {
                "x": 0.5
              },
              "2,15",
              {
                "x": 1.25,
                "c": "#777777",
                "w": 1.25,
                "h": 2,
                "w2": 1.5,
                "h2": 1,
                "x2": -0.25
              },
              "3,13\n\n\n0,1"
            ],
            [
              {
                "x": 2.5,
                "c": "#aaaaaa",
                "w": 1.75
              },
              "3,0",
              {
                "c": "#cccccc"
              },
              "3,1",
              {
                "x": 1
              },
              "3,3",
              "3,4",
              "3,5",
              "3,6",
              "3,7",
              "3,8",
              "3,9",
              "3,10",
              "3,11",
              {
                "c": "#777777",
                "w": 2.25
              },
              "3,13\n\n\n0,0",
              {
                "x": 0.5,
                "c": "#cccccc"
              },
              "3,15",
              {
                "x": 0.25
              },
              "3,12\n\n\n0,1"
            ],
            [
              {
                "c": "#aaaaaa",
                "w": 1.25
              },
              "4,0\n\n\n1,1",
              {
                "c": "#cccccc"
              },
              "4,1\n\n\n1,1",
              {
                "x": 0.25,
                "c": "#aaaaaa",
                "w": 2.25
              },
              "4,0\n\n\n1,0",
              {
                "c": "#cccccc"
              },
              "4,2",
              "4,3",
              "4,4",
              "4,5",
              "4,6",
              "4,7",
              "4,8",
              "4,9",
              "4,10",
              "4,11",
              {
                "c": "#aaaaaa",
                "w": 1.75
              },
              "4,13",
              {
                "x": 1.5,
                "c": "#cccccc"
              },
              "4,15"
            ],
            [
              {
                "y": -0.75,
                "x": 16.75
              },
              "4,14"
            ],
            [
              {
                "y": -0.25,
                "x": 2.5,
                "c": "#aaaaaa",
                "w": 1.25
              },
              "5,0",
              {
                "w": 1.25
              },
              "5,1",
              {
                "w": 1.25
              },
              "5,2",
              {
                "c": "#cccccc",
                "w": 6.25
              },
              "5,5",
              {
                "c": "#aaaaaa",
                "w": 1.24
              },
              "5,10",
              {
                "x": 0.009999999999999787,
                "w": 1.25
              },
              "5,11"
            ],
            [
              {
                "y": -0.75,
                "x": 15.75,
                "c": "#cccccc"
              },
              "5,13",
              "5,14",
              "5,15"
            ],
            [
              {
                "rx": 9.6,
                "ry": 4.3,
                "y": -1.0499999999999998,
                "x": -4.35
              },
              "3,2"
            ]
          ]
    }
}
