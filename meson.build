project('eenum', 'cpp', default_options: ['cpp_std=c++20'])

if get_option('buildtype') == 'debug'
  add_project_arguments('-O0', '-g3', '-Wall',  language : 'cpp')
else
  add_project_arguments('-O3', '-Wall',  language : 'cpp')
endif

cpp = meson.get_compiler('cpp')
cmake = import('cmake')

ctre_pro = cmake.subproject('compile-time-regular-expressions')

catch2 = dependency('catch2')
ctre = ctre_pro.dependencies('ctre')

subdir('src')
subdir('test')