#pragma once

namespace tremolo {
/**
 * Class facilitating transition to and from bypassed state over a single block.
 *
 * It allows 2 things:
 *  - detecting that a bypass state transition takes place
 *  - fade-in and fade-out of dry (unprocessed) and wet (processed) buffers
 *    according to the transition type
 *
 * Use the following code in the processBlock() method of your plugin processor:
 *
 * @code
 * //...
 *
 * bypassTransitionSmoother.setBypass(parameters.bypassed);
 *
 * if (bypassTransitionSmoother.isTransitioning()) {
 *   bypassTransitionSmoother.setDryBuffer(buffer);
 *
 *   yourAudioEffectClassInstance.process(buffer);
 *
 *   bypassTransitionSmoother.mixToWetBuffer(buffer);
 *
 *   return;
 * }
 *
 * // avoid processing if bypassed, process otherwise...
 * @endcode
 *
 * Alternatively, you can unconditionally call setDryBuffer() and
 * mixToWetBuffer(), like this:
 *
 * @code
 * //...
 *
 * bypassTransitionSmoother.setBypass(parameters.bypassed);
 *
 * if (parameters.bypassed && !bypassTransitionSmoother.isTransitioning()) {
 *   // avoid processing if the plugin is bypassed
 *   return;
 * }
 *
 * bypassTransitionSmoother.setDryBuffer(buffer);
 * yourAudioEffectClassInstance.process(buffer);
 * bypassTransitionSmoother.mixToWetBuffer(buffer);
 *
 * // no more processing necessary
 * @endcode
 *
 * Remember to call prepare() in prepareToPlay(),
 * setBypassForced() in setStateInformation(), and reset() in
 * releaseResources().
 */
class BypassTransitionSmoother {
public:
  /*explicit BypassTransitionSmoother(double crossfadeLengthSecondsValue = 0.01)
      : crossfadeLengthSeconds{crossfadeLengthSecondsValue} {
    jassert(0.0 < crossfadeLengthSeconds);
  }*/

  explicit BypassTransitionSmoother(double crossfadeLengthSecondsValue = 0.01);

  void prepare(const juce::dsp::ProcessSpec& spec);

  void setBypass(bool bypass) noexcept;

  void setBypassForced(bool bypass) noexcept;

  [[nodiscard]] bool isTransitioning() const noexcept;

  void setDryBuffer(const juce::AudioBuffer<float>& buffer) noexcept;

  void mixToWetBuffer(juce::AudioBuffer<float>& buffer) noexcept;

  void reset() noexcept;

private:
  double crossfadeLengthSeconds = 0.0;
  double sampleRateHz = 0.0;
  juce::LinearSmoothedValue<float> dryGain{0.f};
  juce::LinearSmoothedValue<float> wetGain{1.f};
  juce::AudioBuffer<float> dryBuffer;
};
}  // namespace tremolo
