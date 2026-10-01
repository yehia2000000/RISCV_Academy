# CMake generated Testfile for 
# Source directory: /home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test
# Build directory: /home/yehia/nexus-am/apps/blur/RISCV_Academy/build/test/unit_test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[unit_tests_gem5]=] "/home/yehia/riscv/GEM5/build/RISCV/gem5.opt" "--remote-gdb-port=0" "-d" "/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/test/unit_test/unit_tests_gem5-m5out" "/home/yehia/riscv/GEM5/configs/example/kmhv3.py" "--raw-cpt" "--generic-rv-cpt=/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/test/unit_test/unit_tests.bin" "--disable-difftest")
set_tests_properties([=[unit_tests_gem5]=] PROPERTIES  FAIL_REGULAR_EXPRESSION "fail_regex-NOTFOUND" PASS_REGULAR_EXPRESSION "pass_regex-NOTFOUND" _BACKTRACE_TRIPLES "/home/yehia/nexus-am/apps/blur/RISCV_Academy/cmake/riscv_add_baremetal.cmake;164;add_test;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;29;riscv_add_gem5_run;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;0;")
add_test([=[unit_tests_qemu]=] "/usr/bin/qemu-riscv64" "-cpu" "max,vlen=128" "/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/test/unit_test/unit_tests_qemu")
set_tests_properties([=[unit_tests_qemu]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/yehia/nexus-am/apps/blur/RISCV_Academy/cmake/riscv_add_baremetal.cmake;225;add_test;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;35;riscv_add_qemu_run;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;0;")
add_test([=[Add_test_qemu]=] "/usr/bin/qemu-riscv64" "-cpu" "max,vlen=128" "/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/test/unit_test/Add_test_qemu")
set_tests_properties([=[Add_test_qemu]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/yehia/nexus-am/apps/blur/RISCV_Academy/cmake/riscv_add_baremetal.cmake;225;add_test;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;54;riscv_add_qemu_run;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;0;")
add_test([=[image_filter_test_qemu]=] "/usr/bin/qemu-riscv64" "-cpu" "max,vlen=128" "/home/yehia/nexus-am/apps/blur/RISCV_Academy/build/test/unit_test/image_filter_test_qemu")
set_tests_properties([=[image_filter_test_qemu]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/yehia/nexus-am/apps/blur/RISCV_Academy/cmake/riscv_add_baremetal.cmake;225;add_test;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;54;riscv_add_qemu_run;/home/yehia/nexus-am/apps/blur/RISCV_Academy/test/unit_test/CMakeLists.txt;0;")
