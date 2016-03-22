
if (NOT EXISTS "/nfs/2015/m/mfroehly/Downloads/glfw-3.1.2/unix/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/nfs/2015/m/mfroehly/Downloads/glfw-3.1.2/unix/install_manifest.txt\"")
endif()

file(READ "/nfs/2015/m/mfroehly/Downloads/glfw-3.1.2/unix/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/nfs/2015/m/mfroehly/Desktop/CMake.app/Contents/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/nfs/2015/m/mfroehly/Desktop/CMake.app/Contents/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()
