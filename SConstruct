#!/usr/bin/python

import os

# Scons environement
env = Environment(tools = ['default', 'cxxtest'])
env.Append(CXXFLAGS="-std=c++11")

# Add debug flags
# AddOption('--dbg', action='append_const', dest='cflags', const='-g')
debug = ARGUMENTS.get('debug', 0)
if int(debug):
   env.Append(CXXFLAGS = ['-g'])
   env.Append(CPPDEFINES=['DEBUG'])

# Add source directory to include path (important for subdirectories)
env.Append(CPPPATH=['.'])

# Output directory
buildDir = '#build'

# Build program
programName = 'SWE1D_solver'
Export('env')
SConscript(os.path.join('src', 'SConscript'),
    variant_dir=os.path.join(buildDir, 'build_'+programName),
    duplicate=0)
Import('env')