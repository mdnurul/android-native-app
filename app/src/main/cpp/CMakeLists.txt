# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("pddemo")

#add_subdirectory("source_dist_ford_dev" libs)
#add_subdirectory("pd_master")
#add_subdirectory("win")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++11-narrowing -Wcast-align -Wover-aligned -Wno-unused-but-set-variable --target=aarch64-linux-android33 -D__STDC_FORMAT_MACRO -fexceptions -fms-extensions -fpermissive -D_REENTRANT -DBUILD_SHARED_LIBS=on-Wno-unused-but-set-variable")

set(OpenCV_DIR D:/AndroidSDK/opencv-4.7.0-android-sdk/OpenCV-android-sdk/sdk/native)

include_directories(${OpenCV_DIR}/jni/include)
add_library( lib_opencv SHARED IMPORTED )
set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${OpenCV_DIR}/libs/${ANDROID_ABI}/libopencv_java4.so)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        pddemo

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        pddemo
        lib_opencv
        #ped_platform_lib
        #ped_core
        #ped_datatypes
        #ped_plugin
        #camera
        #camera_types
        #-lpthread
        #udi
        #nanopb_support
        #nanopb_valeo
        #ped_adab
        #ped_algo
        # Links the target library to the log library
        #"protobuf-2.5.0/src/libs_arm/libprotobuf.a"
        #"protobuf-2.5.0/src/libs_arm/libprotoc.a"
        # included in the NDK.
        ${log-lib}
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libped_platform_app.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libastl.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libcamera.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libcamera_types.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libcommon_wrapper.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libdbg.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libdlog.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libfnt.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libicamera_dal.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libimg.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libimgproc.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libiped_dal.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/liblalgebra.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libmemmgr.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libmon.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libmtd.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libnanopb_support.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libnanopb_valeo.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libosw.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libped_adab.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libped_algo.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libped_core.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libped_datatypes.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libped_debug.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libped_plugin.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libsol.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libsys.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libtyps.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libudi.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libview.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libview_datatypes.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libvmapper.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libvtg.a"
        )