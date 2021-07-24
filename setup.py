from distutils.core import setup, Extension

setup(
    name="string_toolkit",
    version="1.0.0",
    description="Python wrapper for the string_toolkit.h C/C++ header",
    ext_modules=[
        Extension("st", ["python_binding.c"])
    ]
)