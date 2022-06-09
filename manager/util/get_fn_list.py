import sys

from pycparser import c_ast, parse_file
import json


class FuncDefVisitor(c_ast.NodeVisitor):
    def visit_FuncDef(self, node):
        # print('%s at %s' % (node.decl.name, node.decl.coord))
        print(f"{node.decl.name} {node.decl.coord.line} {node.decl.coord.column} {'static' in node.decl.storage}")


gRomVer = ""

def show_func_defs(filename):
    include_paths = [
        "-E",
        "-D_LANGUAGE_C",
        "-DF3DEX2_GBI",
        "-I/home/user/n64/decomp/bt",
        "-I/home/user/n64/decomp/bt/include",
        "-I/home/user/n64/decomp/bt/include/2.0L",

        f"-DVERSION_{gRomVer.upper()}=1",

        # "-DVERSION_USA=1",
        # "-DVERSION_JPN=1",
        # "-DVERSION_EUR=1",
        # "-DVERSION_AUS=1",

        # "-T/home/user/n64/decomp/bt/ver/usa/syms/undefined.txt",
        # "-T/home/user/n64/decomp/bt/ver/usa/syms/DLL.txt",
    ]

    # Command:
    # gcc -E -D_LANGUAGE_C -DF3DEX2_GBI -I/home/user/n64/decomp/bt -I/home/user/n64/decomp/bt/include -I/home/user/n64/decomp/bt/include/2.0L -DVERSION_USA=1 ../src/dlls/fxkern.c > OUTPUT.txt

    # ast = parse_file(
    #     filename
    #     ,use_cpp=True
    #     ,cpp_args=include_paths
    #     # ,cpp_path="/usr/bin/gcc"
    # )


    ast = parse_file(
        filename
        ,use_cpp=False
        ,cpp_args=include_paths
        # ,cpp_path="/usr/bin/gcc"
    )




    v = FuncDefVisitor()
    v.visit(ast)


if __name__ == "__main__":

    if len(sys.argv) > 2:
        gRomVer  = sys.argv[1]
        filename = sys.argv[2]
    else:
        gRomVer  = "usa"
        # filename = "../../src/dlls/fxkern.c"
        filename = "../../manager/OUTPUT.txt"
    
    show_func_defs(filename)





