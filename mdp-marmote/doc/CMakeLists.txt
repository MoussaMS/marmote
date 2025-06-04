# configured documentation tools and intermediate build results
set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")
set_directory_properties(PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES "${BINARY_BUILD_DIR};${CMAKE_CURRENT_BINARY_DIR}/public"
  )

if(BUILD_DOC_DOXYGEN)
  find_package(Doxygen REQUIRED)

  configure_file(Doxyfile.in ${BINARY_BUILD_DIR}/Doxyfile IMMEDIATE @ONLY)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-theme/custom.css
    ${BINARY_BUILD_DIR}/doxygen-theme/custom.css
    COPYONLY)
  add_custom_target(doc
      WORKING_DIRECTORY ${BINARY_BUILD_DIR}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/public/doxygen
      COMMAND ${DOXYGEN_EXECUTABLE} ${BINARY_BUILD_DIR}/Doxyfile
      COMMENT "Building Doxygen doc")
endif()

if(BUILD_DOC_WEBSITE)
  find_program(SPHINX_EXECUTABLE sphinx-build)
  if(NOT SPHINX_EXECUTABLE)
    message(FATAL_ERROR "sphinx-build not found! Aborting...")
  endif()
 find_program(TECTONIC_EXECUTABLE tectonic)
  if(NOT TECTONIC_EXECUTABLE)
    message(FATAL_ERROR "tectonic not found! Aborting...")
  endif()

  add_custom_target(doc-website-files
    WORKING_DIRECTORY ${BINARY_BUILD_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/html/source ${BINARY_BUILD_DIR}/html/source
    COMMENT "Making build copy of website source files"
    )

  add_custom_target(doc-website-latex
    WORKING_DIRECTORY ${BINARY_BUILD_DIR}
    COMMAND ${TECTONIC_EXECUTABLE} --outfmt pdf -o ${BINARY_BUILD_DIR}/html/source/media ${CMAKE_CURRENT_SOURCE_DIR}/latex/manual.tex
    DEPENDS doc-website-files
    COMMENT "Building latex manual with ${TECTONIC_EXECUTABLE}"
    )

  message("PYTHON_BUILD_PATH = ${PYTHON_BUILD_PATH}")
  add_custom_target(doc-website
    WORKING_DIRECTORY ${BINARY_BUILD_DIR}
    COMMAND PYTHONPATH=${PYTHON_BUILD_PATH} ${SPHINX_EXECUTABLE} ${BINARY_BUILD_DIR}/html/source ${CMAKE_CURRENT_BINARY_DIR}/public
    DEPENDS doc-website-latex
    COMMENT "Building web site with ${SPHINX_EXECUTABLE}"
    )

endif()
