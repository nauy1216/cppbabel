####################################################################################
#                                                                                  #
#  Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>                           #
#                                                                                  #
#  This file is part of RTTR (Run Time Type Reflection)                            #
#  License: MIT License                                                            #
#                                                                                  #
#  Permission is hereby granted, free of charge, to any person obtaining           #
#  a copy of this software and associated documentation files (the "Software"),    #
#  to deal in the Software without restriction, including without limitation       #
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,        #
#  and/or sell copies of the Software, and to permit persons to whom the           #
#  Software is furnished to do so, subject to the following conditions:            #
#                                                                                  #
#  The above copyright notice and this permission notice shall be included in      #
#  all copies or substantial portions of the Software.                             #
#                                                                                  #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   #
#  SOFTWARE.                                                                       #
#                                                                                  #
####################################################################################

####################################################################################
# Welcome to the CMake build system for RTTR.
# This file contains several helper function to make the life easier with cmake.
####################################################################################

####################################################################################
# create hierarchical source groups, useful for big VS-Projects
# FILE_LIST <= a list of files with absolute path
####################################################################################
function (createSrcGroups FILE_LIST )
  # we want to get the relative path from the
  # current source dir
  string(LENGTH ${CMAKE_CURRENT_SOURCE_DIR} curDirLen)
  set(TMP_FILE_LIST ${${FILE_LIST}})

  foreach ( SOURCE ${TMP_FILE_LIST} )
    string(LENGTH ${SOURCE} fullPathLen)
    math(EXPR RelPathLen ${fullPathLen}-${curDirLen})
    string(SUBSTRING ${SOURCE} ${curDirLen} ${RelPathLen} curStr)

    string ( REGEX REPLACE "[\\/]" "\\\\" normPath ${curStr} )
    string ( REGEX MATCH "\\\\(.*)\\\\" ouput ${normPath} )
    if(NOT CMAKE_MATCH_1 STREQUAL "")
      source_group ( ${CMAKE_MATCH_1} FILES ${SOURCE} )
    endif()
  endforeach()
endfunction()

####################################################################################
# Create a UnityFile. This is a file which inlcudes all other source files.
# This is usefull, when you want a fast rebuild.
# _UNITY_FILE <= The name of the UnityFile
# _SRC_FILES <= The list of source files
####################################################################################
function(generateUnityFile _UNITY_FILE _SRC_FILES)
  set(files ${${_SRC_FILES}})
  # Generate a unique filename for the unity build translation unit
  set(unit_build_file ${CMAKE_CURRENT_BINARY_DIR}/ub_${_UNITY_FILE}.cpp)
  set_source_files_properties(${files} PROPERTIES HEADER_FILE_ONLY true)
  # Open the ub file
  FILE(WRITE ${unit_build_file} "// Unity Build generated by CMake\n")
  # Add include statement for each translation unit
  foreach(sourceFile ${files} )
    #FILE( APPEND ${unit_build_file} "#include <${CMAKE_CURRENT_SOURCE_DIR}/${sourceFile}>\n")
    FILE( APPEND ${unit_build_file} "#include \"${sourceFile}\"\n")
  endforeach()
  # Complement list of translation units with the name of ub
  set(${_UNITY_FILE} ${unit_build_file} PARENT_SCOPE)
  source_group("Generated Files" FILES ${unit_build_file})
endfunction()

####################################################################################
# Returns the name of the Directory, where the file in the FILE_PATH is located.
####################################################################################
function(getNameOfDir FILE_PATH DIR_NAME)
  get_filename_component(HAS_FILE_IN_PATH ${${FILE_PATH}} EXT)
  if (HAS_FILE_IN_PATH)
    get_filename_component(PATH_WITHOUT_FILENAME ${${FILE_PATH}} PATH)
    get_filename_component(NAME_OF_DIR  ${PATH_WITHOUT_FILENAME} NAME)
    set(${DIR_NAME} ${NAME_OF_DIR} PARENT_SCOPE)
  else()
    get_filename_component(NAME_OF_DIR ${${FILE_PATH}} NAME)
    set(${DIR_NAME} ${NAME_OF_DIR} PARENT_SCOPE)
  endif()
endfunction()

####################################################################################
# Returns relative path from the given file path; starting from CMAKE_CURRENT_SOURCE_DIR
####################################################################################

function(getRelativePath FILE_PATH RELATIVE_PATH)
  string(LENGTH ${CMAKE_CURRENT_SOURCE_DIR} CUR_DIR_LEN)
  get_filename_component(PATH_WITHOUT_FILE ${${FILE_PATH}} PATH)
  string(LENGTH ${PATH_WITHOUT_FILE} FULL_PATH_LEN)
  math(EXPR REL_PATH_LEN ${FULL_PATH_LEN}-${CUR_DIR_LEN})
  math(EXPR REL_PATH_START "${CUR_DIR_LEN}")
  string(SUBSTRING ${PATH_WITHOUT_FILE} ${REL_PATH_START} ${REL_PATH_LEN} REL_PATH)
  string(REGEX REPLACE "^/" "" out_path "${REL_PATH}")
  set(${RELATIVE_PATH} ${out_path} PARENT_SCOPE)
endfunction()

####################################################################################
# Loads a FOLDER, which should contain a FOLDER.cmake.
# In this file all source and header files should be declared.
# In this cmake files all files have to be declared relative.
# They will be read with absolut path.
# FOLDER <= The name of the folder
# _HEADER_FILES => The list of header files
# _SOURCE_FILES => The list of source files
# [OPTIONAL] 3rdArg => performs the installation of the header and source files
####################################################################################
function(loadFolder FOLDER _HEADER_FILES _SOURCE_FILES)
  set(FULL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}.cmake)
  include(${FULL_PATH})
  get_filename_component(ABS_PATH_TO_FILES ${FULL_PATH} PATH)
  set(shouldInstall ${ARGV3})
  set(QT_MOC_HEADERS)
  set(QT_UI_FILES)
  set(QT_QRC_FILES)

  foreach(headerFile ${HEADER_FILES} )
    if (${headerFile} MATCHES ".*.h.in$")
      string ( REGEX REPLACE ".h.in$" ".h" out_path ${headerFile} )
      configure_file(${headerFile} ${CMAKE_CURRENT_BINARY_DIR}/${out_path} @ONLY)
      set(FULL_HEADER_PATH ${ABS_PATH_TO_FILES}/${headerFile})
      getRelativePath(FULL_HEADER_PATH REL_PATH)
      set(FULL_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/${out_path})
      if (REL_PATH)
        string ( REGEX REPLACE "[\\/]" "\\\\" normalized_path ${REL_PATH} )
        source_group ( ${normalized_path} FILES ${FULL_HEADER_PATH} )
      endif()
      list(APPEND ALL_HPP_FILES ${FULL_HEADER_PATH})
    elseif (${headerFile} MATCHES ".*.rc.in$")
      string ( REGEX REPLACE ".rc.in$" ".rc" out_path ${headerFile} )
      configure_file(${headerFile} ${CMAKE_CURRENT_BINARY_DIR}/${out_path} @ONLY)
      source_group("Generated Files" FILES ${CMAKE_CURRENT_BINARY_DIR}/${out_path})
      list(APPEND ALL_HPP_FILES ${CMAKE_CURRENT_BINARY_DIR}/${out_path})
    elseif (${headerFile} MATCHES ".*.ui$")
        set(FULL_HEADER_PATH ${ABS_PATH_TO_FILES}/${headerFile})
        list(APPEND QT_UI_FILES ${FULL_HEADER_PATH})
        list(APPEND ALL_HPP_FILES ${FULL_HEADER_PATH})
    elseif (${headerFile} MATCHES ".*.qrc$")
        set(FULL_HEADER_PATH ${ABS_PATH_TO_FILES}/${headerFile})
        list(APPEND QT_QRC_FILES ${FULL_HEADER_PATH})
        list(APPEND ALL_HPP_FILES ${FULL_HEADER_PATH})
    else()
      set(FULL_HEADER_PATH ${ABS_PATH_TO_FILES}/${headerFile})
      file(STRINGS ${FULL_HEADER_PATH} var REGEX "Q_OBJECT")
      if(var)
         list(APPEND QT_MOC_HEADERS ${FULL_HEADER_PATH})
      endif()

      # returns the relative path, from the current source dir
      getRelativePath(FULL_HEADER_PATH REL_PATH)
      list(APPEND HEADER_LIST_OF_CUR_DIR ${FULL_HEADER_PATH})
    endif()
    # get the name of the current directory
    getNameOfDir(CMAKE_CURRENT_SOURCE_DIR DIRNAME)
    if (${shouldInstall})
      if (NOT ${FULL_HEADER_PATH} MATCHES ".*_p.h$") # we don't want to install header files which are marked as private
        install(FILES ${FULL_HEADER_PATH} DESTINATION "include/${DIRNAME}/${REL_PATH}" PERMISSIONS OWNER_READ)
      endif()
    endif()
  endforeach()

  # and now the source files
  list(APPEND QML_SOURCES)
  foreach(srcFile ${SOURCE_FILES} )
    # the source_group placement doesn't work at the moment
     if (${srcFile} MATCHES ".*.qml$")
       string(REGEX REPLACE "[\\/]" "_" qrc_resource_file ${srcFile} )
       string(REGEX REPLACE ".qml$" ".qrc" qrc_resource_file ${qrc_resource_file} )
       set(qrc_resource_file ${CMAKE_CURRENT_BINARY_DIR}/${qrc_resource_file})
       file(WRITE ${qrc_resource_file} "<!DOCTYPE RCC><RCC version=\"1.0\"><qresource prefix=\"/\"><file alias=\"${srcFile}\">${ABS_PATH_TO_FILES}/${srcFile}</file></qresource></RCC>")
       qt5_add_resources(compiled_resource_file ${qrc_resource_file})
       source_group("Generated Files" FILES ${compiled_resource_file})
       source_group("Generated Files" FILES ${qrc_resource_file})
       list(APPEND QML_SOURCES ${compiled_resource_file})
     elseif (${srcFile} MATCHES ".*.ui$")
        set(FULL_SRC_PATH ${ABS_PATH_TO_FILES}/${srcFile})
        list(APPEND QT_UI_FILES ${FULL_SRC_PATH})
        list(APPEND SOURCE_LIST_OF_CUR_DIR ${FULL_SRC_PATH})
    elseif (${srcFile} MATCHES ".*.qrc$")
        set(FULL_SRC_PATH ${ABS_PATH_TO_FILES}/${srcFile})
        list(APPEND QT_QRC_FILES ${FULL_SRC_PATH})
        list(APPEND SOURCE_LIST_OF_CUR_DIR ${FULL_SRC_PATH})
     else()
       list(APPEND SOURCE_LIST_OF_CUR_DIR ${ABS_PATH_TO_FILES}/${srcFile})
     endif()

    list(APPEND SOURCE_LIST_OF_CUR_DIR ${ABS_PATH_TO_FILES}/${srcFile})
  endforeach()

  list(APPEND QT_MOC_SOURCES)

  if (QT_MOC_HEADERS)
    qt5_wrap_cpp(QT_MOC_SOURCES ${QT_MOC_HEADERS})
    source_group("Generated Files" FILES ${QT_MOC_SOURCES})
  endif()

  list(APPEND QT_UI_SOURCES)
  if (QT_UI_FILES)
    qt5_wrap_ui(QT_UI_SOURCES ${QT_UI_FILES})
    source_group("Generated Files" FILES ${QT_UI_SOURCES})
  endif()

  list(APPEND QT_QRC_SOURCES)
  if (QT_QRC_FILES)
    qt5_add_resources(QT_QRC_SOURCES ${QT_QRC_FILES})
    source_group("Generated Files" FILES ${QT_QRC_SOURCES})
  endif()

  list(APPEND ALL_HPP_FILES ${${_HEADER_FILES}} ${HEADER_LIST_OF_CUR_DIR})
  list(APPEND ALL_CPP_FILES ${${_SOURCE_FILES}} ${SOURCE_LIST_OF_CUR_DIR} ${QT_MOC_SOURCES} ${QT_UI_SOURCES} ${QT_QRC_SOURCES} ${QML_SOURCES})
  set(${_HEADER_FILES} ${ALL_HPP_FILES} PARENT_SCOPE)
  set(${_SOURCE_FILES} ${ALL_CPP_FILES} PARENT_SCOPE)

  createSrcGroups(HEADER_LIST_OF_CUR_DIR)
  createSrcGroups(SOURCE_LIST_OF_CUR_DIR)
  message( STATUS "${FOLDER} directory included" )
endfunction()

####################################################################################
# This function checks if the current generator is used for a Viusal Studio build
# _INPUT This variable will be set to TRUE if its a Visual Studio build, otherwise to FALSE.
####################################################################################
function (is_vs_based_build _INPUT)
  if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
    set(${_INPUT} TRUE PARENT_SCOPE)
  else()
    set(${_INPUT} FALSE PARENT_SCOPE)
  endif()
endfunction()

####################################################################################
# Copy a release dependency in the correct CMAKE_RUNTIME_OUTPUT_DIRECTORY
# _INPUT The full path of the dependency incl. FileName
# _OUTPUT The directory where the libraries should be installed.
# OPTIONAL: RELATIVE Path - as third argument an optional relative path can be specified
####################################################################################

function(copy_dependency_release _INPUT _OUTPUT)
  is_vs_based_build(VS_BUILD)

  # when this is a DEBUG build we dont copy the files
  if(NOT VS_BUILD)
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
      return()
    endif()
  endif()
  # as third argument an optional relative path can be specified
  set(REL_PATH ${ARGV2})
  set(_PATH ${_INPUT})
  # make the path to normal path with / as dir separator
  string ( REGEX REPLACE "[\\/]" "/" FILE_PATH ${_PATH} )
  get_filename_component(FILE_NAME ${FILE_PATH} NAME)

  if (VS_BUILD)
    if (IS_DIRECTORY ${_INPUT})
      file(COPY ${_INPUT} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/${REL_PATH})
    else()
      configure_file(${FILE_PATH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/${REL_PATH}/${FILE_NAME} COPYONLY)
      configure_file(${FILE_PATH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RelWithDebInfo/${REL_PATH}/${FILE_NAME} COPYONLY)
      configure_file(${FILE_PATH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MinSizeRel/${REL_PATH}/${FILE_NAME} COPYONLY)
    endif()
  else()
    if (IS_DIRECTORY ${_INPUT})
      file(COPY ${_INPUT} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${REL_PATH})
    else()
      configure_file(${FILE_PATH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${REL_PATH}/${FILE_NAME} COPYONLY)
    endif()
  endif()

  if (IS_DIRECTORY ${_INPUT})
    install(DIRECTORY
            ${FILE_PATH}
            DESTINATION ${_OUTPUT}/${REL_PATH}
            CONFIGURATIONS Release)
  else()
    install(FILES
            ${FILE_PATH}
            DESTINATION ${_OUTPUT}/${REL_PATH}
            CONFIGURATIONS Release)
  endif()
endfunction()

####################################################################################
# Copy a debug dependency in the correct CMAKE_RUNTIME_OUTPUT_DIRECTORY
# _INPUT The full path of the dependency incl. FileName
# _OUTPUT The directory where the libraries should be installed.
# OPTIONAL: RELATIVE Path - as third argument an optional relative path can be specified
####################################################################################

function(copy_dependency_debug _INPUT _OUTPUT)
  is_vs_based_build(VS_BUILD)

  # when this is NOT a DEBUG build we dont copy the files
  if(NOT VS_BUILD)
    if(NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug)
      return()
    endif()
  endif()
  # as third argument an optional relative path can be specified
  set(REL_PATH ${ARGV2})
  set(_PATH ${_INPUT})
  # make the path to normal path with / as dir separator
  string ( REGEX REPLACE "[\\/]" "////" FILE_PATH ${_PATH} )
  get_filename_component(FILE_NAME ${FILE_PATH} NAME)

  if (VS_BUILD)
    if (IS_DIRECTORY ${_INPUT})
      file(COPY ${_INPUT} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/${REL_PATH})
     else()
      configure_file(${FILE_PATH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/${REL_PATH}/${FILE_NAME} COPYONLY)
    endif()
  else()
    if (IS_DIRECTORY ${_INPUT})
      file(COPY ${_INPUT} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${REL_PATH})
    else()
      configure_file(${FILE_PATH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${REL_PATH}/${FILE_NAME} COPYONLY)
    endif()
  endif()

 if (IS_DIRECTORY ${_INPUT})
   install(DIRECTORY
           ${FILE_PATH}
           DESTINATION ${_OUTPUT}/${REL_PATH}
           CONFIGURATIONS Debug)
 else()
   install(FILES
           ${FILE_PATH}
           DESTINATION ${_OUTPUT}/${REL_PATH}
           CONFIGURATIONS Debug)
  endif()
endfunction()

####################################################################################
# Creates a PreCompiled Header
# _PRECOMPILED_HEADER The full path of the dependency incl. FileName
# _SRC_FILES (Only works with CPP files)
####################################################################################
function(activate_precompiled_headers _PRECOMPILED_HEADER _SOURCE_FILES)
  set(SRC_FILES ${${_SOURCE_FILES}})
  get_filename_component(pch_basename ${_PRECOMPILED_HEADER} NAME_WE)
  set(pch_abs ${CMAKE_CURRENT_SOURCE_DIR}/${_PRECOMPILED_HEADER})
  set(pch_unity ${CMAKE_CURRENT_BINARY_DIR}/${pch_basename}.cpp)

  if(MSVC)
    # First specify the name of the PCH file
    # it seems to be that nmake build cant handle the $(IntDir) variable
    if(NOT MSVC_IDE)
      set(pch_bin ${CMAKE_CURRENT_BINARY_DIR}/${pch_basename}.pch)
    else()
      set(pch_bin "$(IntDir)/${pch_basename}.pch")
    endif()
    # Generate precompiled header translation unit
    if (NOT EXISTS ${pch_unity})
      file(WRITE ${pch_unity} "// Precompiled header unity generated by CMake\n")
      file(APPEND ${pch_unity} "#include <${pch_abs}>\n")
    endif()
    # this creates the precompild header
    set_source_files_properties(${pch_unity}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${pch_abs}\" /Fp\"${pch_bin}\""
                                           OBJECT_OUTPUTS "${pch_bin}")
    # Update properties of source files to use the precompiled header.
    # Additionally, force the inclusion of the precompiled header at beginning of each source file.
    set_source_files_properties(${SRC_FILES}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${pch_abs}\" /FI\"${pch_abs}\" /Fp\"${pch_bin}\""
                                           OBJECT_DEPENDS "${pch_bin}")
    # Finally, update the source file collection to contain the precompiled header translation unit
    set(${_SOURCE_FILES} ${pch_unity} ${pch_abs} ${${_SOURCE_FILES}} PARENT_SCOPE)

    source_group("Generated Files" FILES ${pch_unity})
    get_filename_component(PATH_TO_PCH ${_PRECOMPILED_HEADER} DIRECTORY)
    if (PATH_TO_PCH)
        string ( REGEX REPLACE "[\\/]" "\\\\" normalized_path ${PATH_TO_PCH} )
        source_group(${normalized_path} FILES ${pch_abs})
    endif()
  endif()
endfunction()

####################################################################################
# Adds warnings compiler options to the target depending on the category
# target Target name
####################################################################################
function( set_compiler_warnings target)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS "-Werror"
                 "-Wall")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(WARNINGS "-Werror"
                 "-Wall")
  elseif(MSVC)
    set(WARNINGS "/WX"
                 "/W4")
  endif()

  target_compile_options(${target} PRIVATE ${WARNINGS}) 
endfunction()

####################################################################################
# Adds or replace a compiler option
# _OLD_OPTION The option which should be replaced
# _NEW_OPTION The new option which should be added
####################################################################################
function( replace_compiler_option _OLD_OPTION _NEW_OPTION)
  foreach(flag_var
          CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
          CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES ${_OLD_OPTION})
      # the whitespace after_OLD_OPTION is necessary to really match only the flag and not some sub flag (/MD should match by /MDd)
      string(REGEX REPLACE "${_OLD_OPTION} " "${_NEW_OPTION}" ${flag_var} "${${flag_var}}")
    else()
      set(${flag_var} "${${flag_var}} ${_NEW_OPTION}")
    endif()
   set(${flag_var} ${${flag_var}} PARENT_SCOPE)
  endforeach()
endfunction()

####################################################################################
# enables or disables the user of RTTI for all following source files.
# _ENABLE If true, will enable RTTI, otherwise will disable RTTI.
####################################################################################
macro(enable_rtti _ENABLE)
  set(enable_rtti_opt "")
  set(disable_rtti_opt "")
  if (MSVC)
    set(enable_rtti_opt "/GR")
    set(disable_rtti_opt "/GR-")
  elseif(CMAKE_COMPILER_IS_GNUCXX )
    set(enable_rtti_opt "-frtti")
    set(disable_rtti_opt "-fno-rtti")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(enable_rtti_opt "-frtti")
    set(disable_rtti_opt "-fno-rtti")
  else()
    message(FATAL_ERROR "Don't know how to enable/disable RTTI for this compiler.")
  endif()

  if (${_ENABLE})
    message(STATUS "Enabled: use of RTTI")
    replace_compiler_option("${disable_rtti_opt}" "${enable_rtti_opt}")
  else()
    message(STATUS "Disabled: use of RTTI")
    replace_compiler_option(${enable_rtti_opt} ${disable_rtti_opt})
  endif()
endmacro()


####################################################################################
# Returns the name of the used compiler.
# _COMPILER_NAME
####################################################################################
function(getCompilerName _COMPILER_NAME)
  if(MSVC_VERSION EQUAL 1400)
    set(COMPILER_NAME "vs2005")
  elseif(MSVC_VERSION EQUAL 1500)
    set(COMPILER_NAME "vs2008")
  elseif(MSVC_VERSION EQUAL 1600)
    set(COMPILER_NAME "vs2010")
  elseif(MSVC_VERSION EQUAL 1700)
    set(COMPILER_NAME "vs2012")
  elseif(MSVC_VERSION EQUAL 1800)
    set(COMPILER_NAME "vs2013")
  elseif(MSVC_VERSION EQUAL 1900)
    set(COMPILER_NAME "vs2015")
  elseif((MSVC_VERSION EQUAL 1910 OR MSVC_VERSION GREATER 1910) AND (MSVC_VERSION EQUAL 1919 OR MSVC_VERSION LESS 1919))
    set(COMPILER_NAME "vs2017")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(COMPILER_NAME "gcc")
    if(WIN32)
      execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-dumpversion" OUTPUT_VARIABLE GCC_VERSION_OUTPUT)
      string(REGEX REPLACE "([0-9]+\\.[0-9]+).*" "\\1" GCC_VERSION "${GCC_VERSION_OUTPUT}")
      set(COMPILER_NAME ${COMPILER_NAME}${GCC_VERSION})
    endif()
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
     set(COMPILER_NAME "clang")
  else()
    message(WARNING "Can not retrieve compiler name!")
    return()
  endif()

  set(${_COMPILER_NAME} ${COMPILER_NAME} PARENT_SCOPE)
endfunction()

####################################################################################
# This will install the PDB files also into the "bin" folder of the installation directory
# _TARGET_NAME The name of the target
####################################################################################

function(install_pdb_files _TARGET_NAME)
    if (MSVC)
        install(FILES $<TARGET_PDB_FILE:${_TARGET_NAME}> DESTINATION "bin" CONFIGURATIONS Debug RelWithDebInfo)
    endif()
endfunction()


####################################################################################
# Get environment variable, define it as ENV_$var and make sure backslashes are converted to forward slashes
# _COMPILER_NAME
####################################################################################
macro(getenv_path VAR)
   set(ENV_${VAR} $ENV{${VAR}})
   # replace won't work if var is blank
   if (ENV_${VAR})
     string( REGEX REPLACE "\\\\" "/" ENV_${VAR} ${ENV_${VAR}} )
   endif ()
endmacro()

macro(generateLibraryVersionVariables MAJOR MINOR PATCH PRODUCT_NAME PRODUCT_CPY_RIGHT PRODUCT_LICENSE)
  set(LIBRARY_VERSION_MAJOR ${MAJOR})
  set(LIBRARY_VERSION_MINOR ${MINOR})
  set(LIBRARY_VERSION_PATCH ${PATCH})
  set(LIBRARY_VERSION ${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH})
  set(LIBRARY_VERSION_STR "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH}")
  math(EXPR LIBRARY_VERSION_CALC "${LIBRARY_VERSION_MAJOR}*1000 + ${LIBRARY_VERSION_MINOR}*100 + ${LIBRARY_VERSION_PATCH}")
  set(LIBRARY_PRODUCT_NAME ${PRODUCT_NAME})
  set(LIBRARY_COPYRIGHT ${PRODUCT_CPY_RIGHT})
  set(LIBRARY_LICENSE ${PRODUCT_LICENSE})
endmacro()

function(get_latest_supported_cxx CXX_STANDARD)
    if (POLICY CMP0067)
        cmake_policy(SET CMP0067 NEW)
    endif()
    
    # we need to set CMAKE_CXX_STANDARD in order to use the flags for 'check_cxx_source_compiles'
    if(${CMAKE_VERSION} VERSION_LESS "3.8.0") 
        set(CMAKE_CXX_STANDARD 14)
    else()
        set(CMAKE_CXX_STANDARD 17)
    endif()    

    include(CheckCXXSourceCompiles)

    check_cxx_source_compiles("
                              #include <type_traits>
                              typedef void F();
                              typedef void G() noexcept;
                              
                              std::enable_if<
                                  !std::is_same<F, G>::value,
                                  int
                              >::type i = 42;
                              
                              int main() { return 0; }
                              "
                              HAS_NO_EXCEPT_TYPE_SIGNATURE_SUPPORT)

    check_cxx_source_compiles("
                              #include <type_traits>
                              struct foo { void func() const noexcept {} };
                              template<typename T>
                              void test_func(T)
                              {
                                  static_assert(std::is_member_function_pointer<T>::value, \"Failed\");
                              }
                              int main() { test_func(&foo::func); return 0; }
                              " 
                              HAS_STL_NO_EXCEPT_TYPE_SIGNATURE_SUPPORT)
                              
    check_cxx_source_compiles("
                              constexpr int abs(int x)
                              {
                                  if(x < 0) x = -x;
                                  return x;
                              }
                              
                              int main() { }
                              "
                              HAS_CXX_CONSTEXPR)
                              
    check_cxx_source_compiles( "
                               #include <type_traits>
                               template<typename T>
                               struct template_type_trait : std::false_type {};
                               
                               template<template < bool > class T, bool N>
                               struct template_type_trait<T<N>> : std::true_type {};
                               
                               template<template <std::size_t> class T, std::size_t N>
                               struct template_type_trait<T<N>> : std::true_type {};
                               
                               template<std::size_t T>
                               struct bar{};
                               
                               int main() { static bool foo = template_type_trait<bar<100>>::value;}
                               "
                               HAS_PARTIAL_SPECIALIZATION_FOR_ARRAYS)

    if (HAS_NO_EXCEPT_TYPE_SIGNATURE_SUPPORT AND HAS_STL_NO_EXCEPT_TYPE_SIGNATURE_SUPPORT AND
        HAS_PARTIAL_SPECIALIZATION_FOR_ARRAYS)
        set(MAX_CXX_STD 17)
    else()
        if (HAS_CXX_CONSTEXPR)
            set(MAX_CXX_STD 14)
        else()
            set(MAX_CXX_STD 11)
        endif()
    endif()
    
    set(${CXX_STANDARD} ${MAX_CXX_STD} PARENT_SCOPE)
endfunction()

