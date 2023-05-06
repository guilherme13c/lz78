import os

mypath = os.path.dirname(os.path.realpath(__file__))+"/test/"

def test():
    filenames = next(os.walk(mypath), (None, None, []))[2]

    os.system("rm -f lz78-compress test/*_compressed.lz78 test/*_decompressed.txt")
    os.system("g++ main.cpp -o lz78-compress")

    compress_ratio = dict()

    for file in filenames:
        file = mypath+file
        os.system(f"./lz78-compress -c {file} -o {file.replace('.txt', '_compressed.lz78')}")
        os.system(
            f"./lz78-compress -x {file.replace('.txt', '_compressed.lz78')} -o {file.replace('.txt', '_decompressed.txt')}")
        
        compress_ratio[file] = 1 - os.stat(
            file.replace('.txt', '_compressed.lz78')).st_size/os.stat(file).st_size
        
    for i in compress_ratio.keys():
        print(f"{i} => {compress_ratio[i]}")
        
    os.system("rm lz78-compress test/*_compressed.lz78 test/*_decompressed.txt")

if __name__ == "__main__":
    test()
