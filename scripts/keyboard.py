import subprocess
import json
from replacement import data

result = subprocess.run([
    "qmk",
    "c2json",
    "keyboards/splitkb/aurora/lily58/keymaps/smierx-colemak-dh/keymap.c",
    "--no-cpp",
],capture_output=True,text=True)

data_json = json.loads(result.stdout)

new_data_json = {
    "keyboard":"splitkb/aurora/lily58/rev1",
    "keymap":"smierx-colemak-dh",
    "layout":"LAYOUT",
    "layers":[]
}
for layer in data_json["layers"]:
    tmp_layer = []
    for x in layer:
        if x in data:
            tmp_layer.append(data[x])
        else:
            tmp_layer.append(x)
    new_data_json["layers"].append(tmp_layer)

with open("debug.json","w") as file:
    json.dump(new_data_json,file,indent=4)

result = subprocess.run([
    "keymap","parse","-c","10","-q","debug.json"
],capture_output=True,text=True)

#TODO Bearbeitung yml

with open("debug.yml","w") as file:
    file.write(result.stdout)

layers = [
    "L0",
    "L1",
    "L2",
    "L3",
    "L4",
    "L5",
    "L6",
    "L7",
    "L8",
    "L9",
    "L10",
    "L11",
    "L12",
    "L13",
    "L14",
    "L15",
]#TODO aus yml auslesen

for layer in layers:
    result = subprocess.run([
        "keymap","draw","debug.yml","-s",layer
    ],capture_output=True,text=True)

    with open(f"{layer}.svg","w") as file:
        file.write(result.stdout)













