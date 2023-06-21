# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/WorkLoad/esp/esp-idf/components/bootloader/subproject"
  "D:/WorkLoad/TimeWizard/esp32/TimeWizard/build/bootloader"
  "D:/WorkLoad/TimeWizard/esp32/TimeWizard/build/bootloader-prefix"
  "D:/WorkLoad/TimeWizard/esp32/TimeWizard/build/bootloader-prefix/tmp"
  "D:/WorkLoad/TimeWizard/esp32/TimeWizard/build/bootloader-prefix/src/bootloader-stamp"
  "D:/WorkLoad/TimeWizard/esp32/TimeWizard/build/bootloader-prefix/src"
  "D:/WorkLoad/TimeWizard/esp32/TimeWizard/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/WorkLoad/TimeWizard/esp32/TimeWizard/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
