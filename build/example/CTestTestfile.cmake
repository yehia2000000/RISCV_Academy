# CMake generated Testfile for 
# Source directory: /home/yehia/nexus-am/apps/blur/RISCV_Academy/example
# Build directory: /home/yehia/nexus-am/apps/blur/RISCV_Academy/build/example
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[Add_example_gem5]=] "/home/yehia/riscv/GEM5/build/RISCV/gem5.opt" "--remote-gdb-port=0" "-d" "/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/example/Add_example_gem5-m5out" "/home/yehia/riscv/GEM5/configs/example/kmhv3.py" "--raw-cpt" "--generic-rv-cpt=/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/example/Add_example.bin" "--disable-difftest")
set_tests_properties([=[Add_example_gem5]=] PROPERTIES  FAIL_REGULAR_EXPRESSION "Example failed" PASS_REGULAR_EXPRESSION "Example passed\\." _BACKTRACE_TRIPLES "/home/yehia/nexus-am/apps/blur/RISCV_Academy/cmake/riscv_add_baremetal.cmake;164;add_test;/home/yehia/nexus-am/apps/blur/RISCV_Academy/example/CMakeLists.txt;15;riscv_add_gem5_run;/home/yehia/nexus-am/apps/blur/RISCV_Academy/example/CMakeLists.txt;0;")
add_test([=[Add_example_qemu]=] "/usr/bin/qemu-riscv64" "-cpu" "max,vlen=128" "/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/example/Add_example_qemu")
set_tests_properties([=[Add_example_qemu]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/yehia/nexus-am/apps/blur/RISCV_Academy/cmake/riscv_add_baremetal.cmake;225;add_test;/home/yehia/nexus-am/apps/blur/RISCV_Academy/example/CMakeLists.txt;20;riscv_add_qemu_run;/home/yehia/nexus-am/apps/blur/RISCV_Academy/example/CMakeLists.txt;0;")
