import bpmod
from bpmod import Store
s = Store()
s.setHeaderLines([
    "# header file"
])
s.writeLine('out.txt',"big money")
s.setTailLines(
    [f"tailing line {i}" for i in range(0,1)]
)
test="test"
s.writeArgs(1,2,3,F="out.txt")
s.storedValues.one = 1
s.storedValues.two = 2
s.storedValues.three = 3.0
s.storedValues.cool = "shadow wizard money gang: we love casting spells!"
VALUE = 0
def run_func():
    global VALUE,s
    VALUE+=1
    if (VALUE==0): print("wow does this work!")
    # print(f'called #{VALUE}')
    s.writeLine('out.txt',f'called #{VALUE}')

if __name__ == '__main__':
    pass