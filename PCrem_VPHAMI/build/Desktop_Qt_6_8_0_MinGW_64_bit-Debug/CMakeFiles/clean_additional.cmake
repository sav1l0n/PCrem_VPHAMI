# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PCrem_VPHAMI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PCrem_VPHAMI_autogen.dir\\ParseCache.txt"
  "PCrem_VPHAMI_autogen"
  )
endif()
