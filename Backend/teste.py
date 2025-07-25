import ctypes
from ctypes import Structure, c_char, c_int, POINTER

# carrega a dll com o código da lista
lib = ctypes.CDLL("./lista.dll")

# define a struct Operation
class Operation(Structure):
    pass

Operation._fields_ = []