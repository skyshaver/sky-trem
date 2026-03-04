#pragma once

namespace sky_trem {

	class BypassTransitionSmoother {
	public:

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
		juce::LinearSmoothedValue<float> dryGain{ 0.f };
		juce::LinearSmoothedValue<float> wetGain{ 1.f };
		juce::AudioBuffer<float> dryBuffer;
	};
}  // namespace sky_trem
