import sys
from distutils.core import setup, Extension 
from Cython.Build import cythonize
import os
ORA_HOME=os.environ['ORACLE_HOME'];
ORA_INC=ORA_HOME + '/rdbms/public/'
ORA_LIB=ORA_HOME + '/lib/'

print(ORA_INC)
compileArgs= ['-std=c++11','-I' + ORA_INC]
 
#Extension - First argument is module name and second argument is sources for which module need to be build
moduleDetails = Extension("*", ["*.pyx"],
                extra_compile_args=compileArgs,
                language='c++',
                libraries=["clntsh"],
                library_dirs=[ORA_LIB])

			
setup(
    ext_modules=cythonize(moduleDetails)
)
