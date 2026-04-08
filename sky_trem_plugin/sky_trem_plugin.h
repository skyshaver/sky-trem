/*
==============================================================================

BEGIN_JUCE_MODULE_DECLARATION

   ID:            sky_trem_plugin
   vendor:        CloudMapMusic
   version:       1.0.0
   name:          Sky Trem Plugin
   description:   Rhythmic Tremolo Audio Plugin
   dependencies:  juce_audio_utils, juce_dsp

   website:       https://skyshaver.com
   license:       MIT

END_JUCE_MODULE_DECLARATION

==============================================================================
*/

#pragma once

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_events/juce_events.h>
#include <juce_dsp/juce_dsp.h>
#include <vector>
#include <memory>
#include <functional>
#include <ranges>
#include <algorithm>
#include <array>
#include <cmath>
#include <utility>

#include "include/Parameters.h"
#include "include/CustomLookAndFeel.h"
#include "include/JsonSerializer.h"
#include "include/Tremolo.h"
#include "include/BypassTransitionSmoother.h"
#include "include/PluginProcessor.h"
#include "include/LfoVisualizer.h"
#include "include/SkyRotarySlider01.h"
#include "include/SkyComboBox01.h"
#include "include/PluginEditor.h"

