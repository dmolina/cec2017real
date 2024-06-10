using Libdl

lib::Ptr{Nothing} = Ptr{Nothing}()
dim::Int = 0

"""
        cec17_init(algname::String, funcid::Int, size::Int, dir=joinpath(@__DIR__, ".."))

Init the cec17 benchmark for the funcid and size pass as parameter.

# Parameters:

- algname: The name of the algorithm (for output files).
- funcid: The id of the function to test (between 1 and 30).
- size: The size of the solution, it must be [2, 10, 30, 50, 100].
- dir: Directory of the library.

"""
function cec17_init(algname::String, funcid::Int, size::Int, dir=joinpath(@__DIR__, ".."))
    @assert !isempty(algname) "Error, algname must not be empty"
    @assert funcid >= 1 && funcid <= 30 "Error, funcid $(funcid) is not between 1 and 30"
    @assert size in [2, 10, 30, 50, 100] "Error, size $(size) is not {2, 10, 30, 50, 100}"
    global lib, dim
    lib = Libdl.dlopen(joinpath(@__DIR__, "..", "libcec17_test_func.so"))
    init = dlsym(lib, :cec17_init)
    ccall(init, Cvoid, (Cstring, Cint, Int), algname, funcid, size)
    dim = size
end

function cec17_print_output()
    global lib
    @assert lib !== Nothing "cec17_init must be applied"
    print_cec = dlsym(lib, :cec17_print_output)
    ccall(print_cec, Cvoid, (),)
end

function cec17_fitness(sol::Vector{Float64})
    global dim
    @assert dim > 0 "cec17_init must be applied"
    @assert length(sol) == dim
    global lib
    fitness = dlsym(lib, :cec17_fitness)
    ccall(fitness, Cdouble, (Ptr{Cdouble},), sol)
end

function cec17_error(fitness::Float64)
    global dim
    @assert dim > 0 "cec17_init must be applied"
    global lib
    error_fun = dlsym(lib, :cec17_error)
    ccall(error_fun, Cdouble, (Cdouble,), fitness)
end
