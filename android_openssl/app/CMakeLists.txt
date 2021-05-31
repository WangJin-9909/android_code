# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
# CMake版本
cmake_minimum_required(VERSION 3.4.1)

#设置库文件路径
set(JNI_LIBS_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

# 设置头文件加载的目录
#include_directories(D:/log/android_openssl/app/openssl_resouce/include)
include_directories(${JNI_LIBS_DIR}/include)


#动态方式加载
add_library(openssl SHARED IMPORTED )
add_library(ssl SHARED IMPORTED )

#引入第三方.so库，根据${ANDROID_ABI} 引用不同的库
#set_target_properties(openssl PROPERTIES IMPORTED_LOCATION D:/log/android_openssl/app/openssl_resouce/lib/${ANDROID_ABI}/libcrypto.so)
#set_target_properties(ssl PROPERTIES IMPORTED_LOCATION D:/log/android_openssl/app/openssl_resouce/lib/${ANDROID_ABI}/libssl.so)
set_target_properties(openssl PROPERTIES IMPORTED_LOCATION ${JNI_LIBS_DIR}/lib/${ANDROID_ABI}/libcrypto.so)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${JNI_LIBS_DIR}/lib/${ANDROID_ABI}/libssl.so)



# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 设置链接选项
target_link_libraries( # Specifies the target library.
                       native-lib
                       openssl
                       ssl

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )