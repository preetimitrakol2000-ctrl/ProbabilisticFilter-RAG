import ctypes
import os
import sys

class FilterBridge:
    def __init__(self):
        if not os.path.exists("./libbloom.so") and not os.path.exists("./libbloom.dll"):
            if sys.platform.startswith("win"):
                os.system("gcc -shared -o libbloom.dll bloom_filter.c")
                lib_path = "./libbloom.dll"
            else:
                os.system("gcc -shared -fPIC -o libbloom.so bloom_filter.c")
                lib_path = "./libbloom.so"
        else:
            lib_path = "./libbloom.dll" if sys.platform.startswith("win") else "./libbloom.so"

        self.lib = ctypes.CDLL(lib_path)
        self.lib.init_bloom_filter.restype = ctypes.c_void_p
        self.lib.insert_metadata_key.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.test_metadata_key.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.test_metadata_key.restype = ctypes.c_int
        
        self.filter_ptr = self.lib.init_bloom_filter()

    def add_key(self, metadata_key: str):
        self.lib.insert_metadata_key(self.filter_ptr, metadata_key.encode('utf-8'))

    def contains_key(self, metadata_key: str) -> bool:
        return self.lib.test_metadata_key(self.filter_ptr, metadata_key.encode('utf-8')) == 1
