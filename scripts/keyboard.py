import subprocess
import json
from replacement import data as replace
import os



def test():
    result = subprocess.run([
        "qmk",
        "c2json",
        "keyboards/bastardkb/charybdis/4x6/keymaps/smierx/keymap.c",
        "--no-cpp",
    ],capture_output=True,text=True)

    data_json = json.loads(result.stdout)

    new_data_json = {
        "keyboard":"bastardkb/charybdis/4x6/v2/splinky_3",
        "keymap":"smierx",
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
        with open(f"images/charybdis/single/{layer}.svg","w") as file:
            result = subprocess.run([
                "keymap","draw","debug.yml","-s",layer
            ],stdout=file)

    with open("images/charybdis/complete.svg", "w") as file:
        result = subprocess.run(["keymap","draw","debug.yml"],stdout=file)
    counter = 0
    for layer in range(0,len(layers),4):
        with open(f"images/charybdis/block/{counter}.svg","w") as file:
            result = subprocess.run([
                "keymap", "draw", "debug.yml", "-s", f"L{layer}",f"L{layer+1}",f"L{layer+2}",f"L{layer+3}"
            ],stdout=file)
        counter += 1
    """base_path = "images/lily58/block"
    for file in os.listdir(base_path):
        if file.endswith(".svg"):
            # Pfad zur SVG-Datei
            input_svg = base_path + "/" + file

            # Pfad zur Ausgabe-PNG-Datei
            output_png = base_path + "/" + file.split(".svg")[0] + ".pdf"
            print(input_svg)
            # Konvertierung von SVG zu PNG
            cairosvg.svg2pdf(url=input_svg, write_to=output_png)

    """
def c2json(path,keymap):
    print(path+"/keymaps/"+keymap+"/keymap.c")
    result = subprocess.run([
        "qmk",
        "c2json",
        path+"/keymaps/"+keymap+"/keymap.c",
        "--no-cpp",
    ], capture_output=True, text=True)
    return json.loads(result.stdout)

def get_layer(layers):
    tmp = []
    for layer in layers:
        tmp_layer = []
        for x in layer:
            if x in data:
                tmp_layer.append(data[x])
            else:
                tmp_layer.append(x)
        tmp.append(tmp_layer)
    return tmp
if __name__ == "__main__":
    with open("scripts/config.json","r") as file:
        data = json.load(file)

    for board in data:
        print(board)
        tmp_data = c2json(board["path"],board["keymap"])
        tmp_result = {
            "keyboard": board["keyboard"],
            "keymap": board["keymap"],
            "layout": "LAYOUT",
            "layers": get_layer(tmp_data["layers"]),
        }
        tmp = []
        for layer in tmp_result["layers"]:
            tmp_layer = []
            for x in layer:
                if x in replace:
                    tmp_layer.append(replace[x])
                else:
                    tmp_layer.append(x)
            tmp.append(tmp_layer)
        tmp_result["layers"] = tmp
        with open("scripts/tmp.json", "w") as file:
            json.dump(tmp_result, file, indent=4)

        result = subprocess.run([
            "keymap", "parse", "-c", "10", "-q", "scripts/tmp.json"
        ], capture_output=True, text=True)

        with open("scripts/tmp.yml", "w") as file:
            file.write(result.stdout)

        if not os.path.exists(f"images/{board['name']}"):
            os.makedirs(f"images/{board['name']}")
            os.makedirs(f"images/{board['name']}/single")

        counter = 0

        for layer in tmp_data["layers"]:
            with open(f"images/{board['name']}/single/L{counter}.svg", "w") as file:
                result = subprocess.run([
                    "keymap", "draw", "scripts/tmp.yml", "-s", f"L{counter}"
                ], stdout=file)
            counter += 1

        with open(f"images/{board['name']}/complete.svg", "w") as file:
            result = subprocess.run(["keymap", "draw", "scripts/tmp.yml"],
                                    stdout=file)

