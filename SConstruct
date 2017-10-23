#!/usr/bin/python

import os

# Add debug flags
AddOption('--dbg', action='append_const', dest='cflags', const='-g')

# Scons environement
env = Environment(tools = ['default', 'cxxtest'])
env.MergeFlags(GetOption('cflags'))

# Add source directory to include path (important for subdirectories)
env.Append(CPPPATH=['.'])

# Output directory
buildDir = '#build'

# Build program
programName = 'SWE1D_corecli'
Export('env')
env.srcFiles = []
SConscript(os.path.join('src', 'SConscript'),
    variant_dir=os.path.join(buildDir, 'build_'+programName),
    duplicate=0)
Import('env')
env.Program(os.path.join(buildDir, programName), env.srcFiles)