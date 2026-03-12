import os
import platform
import setuptools
import sysconfig

k, _, _, _, m, _ = platform.uname()
cc = os.getenv("CC", sysconfig.get_config_var("CC"))

e_args = {
    "name": "pyc.ext",
    "sources": ["pyc/ext.c"],
}

if os.environ.get("USE_OMP") == "1":
    e_args["define_macros"] = [("HAVE_OMP", None)]
    if os.environ.get("USE_LLVM") == "1":
        e_args["extra_compile_args"] = ["/openmp:llvm"]
    else:
        e_args["extra_compile_args"] = ["/openmp"]

print(k, m, cc)
print(e_args)
setuptools.setup(ext_modules=[setuptools.Extension(**e_args)])
