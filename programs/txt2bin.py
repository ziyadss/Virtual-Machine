import os


__dir__ = os.path.dirname(os.path.realpath(__file__))

for fileName in os.listdir(__dir__):
    if fileName.endswith(".txt"):
        fileIn = open(os.path.join(__dir__, fileName), "r")
        input = map(lambda x: int(x, 16), fileIn.readlines())
        fileIn.close()

        bytePairs = map(lambda x: (x & 0x00FF, x >> 8), input)
        output = [byte for pair in bytePairs for byte in pair]

        fileOut = open(os.path.join(__dir__, fileName.replace(".txt", ".bin")), "wb")
        fileOut.write(bytes(output))
        fileOut.close()

        print("Converted:", fileName)
