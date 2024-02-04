import bpmod
from bpmod import StoredValues

sv = StoredValues()

sv.wow = 123
sv.bacon = "good"
sv.age = 1234
sv['wow'] = 555
b = sv['bacon']
b = 'great'
sv.bacon = b
sv['new thing'] = 0000
sv.delItem('new thing')
d = sv.getValues()
print(d)