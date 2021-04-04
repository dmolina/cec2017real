from ctypes import CDLL, POINTER, c_char, c_char_p, c_int, c_double
import os

global dimension

def init(algname, funcid, size, dll_path=CDLL(os.path.abspath('libcec17_test_func.so'))):
    global dimension
    dimension = size
    functions = dll_path
    functions.cec17_init.argtypes = [c_char_p, c_int, c_int]
    functions.cec17_init.restype = None
    functions.cec17_init(c_char_p(algname.encode('utf-8')), c_int(funcid), c_int(dimension))

def print_output(dll_path=CDLL(os.path.abspath('libcec17_test_func.so'))):
    functions = dll_path
    functions.cec17_print_output.argtypes = None
    functions.cec17_print_output.restype = None
    functions.cec17_print_output()

def error(fit, dll_path=CDLL(os.path.abspath('libcec17_test_func.so'))):
    functions = dll_path
    functions.cec17_error.argtypes = [c_double]
    functions.cec17_error.restype = c_double
    error = functions.cec17_error(c_double(fit))
    return error


def fitness(sol, dim, dll_path=CDLL(os.path.abspath('libcec17_test_func.so'))):
    global dimension
    functions = dll_path
    sol_type = POINTER(c_double*dimension)
    functions.cec17_fitness.argtypes = [sol_type]
    functions.cec17_fitness.restype = c_double

    solc = (c_double * dimension)()

    for i, value in enumerate(sol):
        solc[i] = value

    return functions.cec17_fitness(sol_type(solc))
