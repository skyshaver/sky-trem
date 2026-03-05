project(SkyTremPluginTest)

# Signals to CMake that we want to run tests from this directory.
enable_testing()

# Adds googletest.
cpmaddpackage(
  NAME
    GOOGLETEST
  GITHUB_REPOSITORY
    google/googletest
  VERSION
    1.16.0
  SOURCE_DIR
    ${LIB_DIR}/googletest
  OPTIONS
    "INSTALL_GTEST OFF"
    "gtest_force_shared_crt ON"
)



# Creates the test console application.
add_executable(SkyTremPluginTest  
  source/JsonSerializerTest.cpp      
)

# Configuration options that apply to the JUCE sources in the test target
target_compile_definitions(SkyTremPluginTest
  PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    # We need to re-export these definitions to the test project, because the tremolo_plugin module
    # does not define them
    JucePlugin_Manufacturer="$<TARGET_PROPERTY:SkyTremPlugin,JUCE_COMPANY_NAME>"
    JucePlugin_Name="$<TARGET_PROPERTY:SkyTremPlugin,JUCE_PLUGIN_NAME>"
    JucePlugin_VersionString="$<TARGET_PROPERTY:SkyTremPlugin,JUCE_VERSION>"
)

# Thanks to the fact that we link against the gtest_main library, we don't have to write the main function ourselves.
target_link_libraries(
  SkyTremPluginTest
  PRIVATE
    sky_trem::sky_trem_plugin
    GTest::gtest_main
    # wolfsound::wolfsound_dsp_utils
    juce::juce_recommended_warning_flags
)

# Adds googletest-specific CMake commands at our disposal.
include(GoogleTest)

# Add all tests defined with googletest to the CMake metadata
# so that these tests are run upon a call to ctest in the test
# projects' binary directory.
gtest_discover_tests(SkyTremPluginTest DISCOVERY_TIMEOUT 60 DISCOVERY_MODE PRE_TEST)

