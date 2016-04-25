#!/usr/bin/python
import sys
import shutil

if len(sys.argv) < 2:
    print "Provide the number of tasks"
    sys.exit(1)
count = int(sys.argv[1])
for i in range(ord('A'), ord('A') + count):
    task = chr(i)
    shutil.copyfile("template.cpp", task + ".cpp")
    with open("CMakeLists.txt", "a") as cmake:
        cmake.write("add_executable({0} {0}.cpp)\n".format(task))
