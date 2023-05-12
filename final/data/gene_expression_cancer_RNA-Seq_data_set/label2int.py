import sys

KNOWN_LABEL = ["KIRC", "BRCA", "LUAD"]
UNKNOWN_LABEL = ["COAD", "PRAD"]

label_map = {"KIRC" : 1, "BRCA": 2, "LUAD": 3, "COAD": 4, "PRAD": 5}

try:
    while True:
        print(label_map[input().strip()])
except:
    pass
