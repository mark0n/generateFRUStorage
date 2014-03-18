# this module looks for srec_cat

find_program(SRECCAT_EXECUTABLE
  NAMES
  srec_cat
  PATHS
  /usr/local/bin
  /usr/bin
)

# handle the QUIETLY and REQUIRED arguments and set SRECCAT_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Sreccat REQUIRED_VARS SRECCAT_EXECUTABLE)