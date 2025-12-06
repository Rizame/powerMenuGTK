project('xdd', 'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++17'])

gtkmm_dep = dependency('gtkmm-4.0')

# Add include directory
include_dir = include_directories('include')

sources = files(
  'src/PowerMenu.cpp',
  'src/ConfirmDialog.cpp',
  'main.cpp',
)

executable('xdd', sources,
  dependencies: gtkmm_dep,
  include_directories: include_dir)  # <-- Add this

