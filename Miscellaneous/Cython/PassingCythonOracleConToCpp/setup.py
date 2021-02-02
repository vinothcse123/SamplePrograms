import sys
from distutils.core import setup, Extension 
from Cython.Build import cythonize

compileArgs= ['-std=c++11','-I/RMS/nrsp/vinoth/playground/odpi/include/']
 
#Extension - First argument is module name and second argument is sources for which module need to be build
moduleDetails = Extension("*", ["*.pyx"],
                extra_compile_args=compileArgs,
                language='c++',
                libraries=["odpic"],
                library_dirs=["/RMS/nrsp/vinoth/playground/odpi/lib/"])

			
setup(
    ext_modules=cythonize(moduleDetails)
)
