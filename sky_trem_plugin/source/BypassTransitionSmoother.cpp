
namespace tremolo {

    BypassTransitionSmoother::BypassTransitionSmoother(double crossfadeLengthSecondsValue) : crossfadeLengthSeconds{ crossfadeLengthSecondsValue } {
        jassert(0.0 < crossfadeLengthSeconds);
    }

    void tremolo::BypassTransitionSmoother::prepare(const juce::dsp::ProcessSpec& spec) {
        sampleRateHz = spec.sampleRate;
        dryBuffer.setSize(static_cast<int>(spec.numChannels), static_cast<int>(spec.maximumBlockSize));
        dryGain.reset(spec.sampleRate, crossfadeLengthSeconds);
        wetGain.reset(spec.sampleRate, crossfadeLengthSeconds);
    }

    void BypassTransitionSmoother::setBypass(bool bypass) noexcept {
        const auto current = dryGain.getCurrentValue();
        const auto target = bypass ? 1.0f : 0.0f;
        const auto duration = crossfadeLengthSeconds * std::abs(target - current);

        dryGain.reset(sampleRateHz, duration);
        wetGain.reset(sampleRateHz, duration);

        dryGain.setCurrentAndTargetValue(current);
        dryGain.setTargetValue(target);

        wetGain.setCurrentAndTargetValue(1.0f - current);
        wetGain.setTargetValue(1.0f - target);
    }

    void BypassTransitionSmoother::setBypassForced(bool bypass) noexcept {
        dryGain.setCurrentAndTargetValue(bypass ? 1.0f : 0.0f);
        wetGain.setCurrentAndTargetValue(1.0f - dryGain.getTargetValue());
    }

    bool BypassTransitionSmoother::isTransitioning() const noexcept {
        return dryGain.isSmoothing() || wetGain.isSmoothing();
    }

    void BypassTransitionSmoother::setDryBuffer(const juce::AudioBuffer<float>& buffer) noexcept {
        jassert(buffer.getNumSamples() <= dryBuffer.getNumSamples());
        jassert(buffer.getNumChannels() <= dryBuffer.getNumChannels());

        for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {
            dryBuffer.copyFrom(channel, 0, buffer, channel, 0,
                buffer.getNumSamples());
        }
        dryGain.applyGain(dryBuffer, buffer.getNumSamples());
    }

    void BypassTransitionSmoother::mixToWetBuffer(juce::AudioBuffer<float>& buffer) noexcept {
        jassert(buffer.getNumSamples() <= dryBuffer.getNumSamples());
        jassert(buffer.getNumChannels() <= dryBuffer.getNumChannels());

        wetGain.applyGain(buffer, buffer.getNumSamples());
        for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {
            buffer.addFrom(channel, 0, dryBuffer, channel, 0, buffer.getNumSamples());
        }
    }

    void BypassTransitionSmoother::reset() noexcept {
        setBypassForced(false);
        dryBuffer.clear();
    }

} // namespace tremolo
