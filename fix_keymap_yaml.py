from pathlib import Path
import sys
import yaml


def main(keymap_file):
    p = Path(keymap_file)
    assert p.exists()
    with p.open("rt") as f:
        y = yaml.safe_load(f.read())
    y["layout"]["qmk_layout"] = "LAYOUT_split_3x6_5"
    with p.open("wt") as f:
        f.write(yaml.dump(y))


if __name__ == "__main__":
    main(sys.argv[1])
