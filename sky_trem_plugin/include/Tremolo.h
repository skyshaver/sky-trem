#pragma once

//https://github.com/juce-framework/JUCE/blob/master/examples/DSP/OscillatorDemo.h

namespace sky_trem {

	class Tremolo {

	public:

		enum class LfoWaveform : size_t {
			SINE = 0,
			TRIANGLE = 1,
			SQUARE = 2
		};

		Tremolo();

		void prepare(double sampleRate, int expectedMaxFramesPerBlock);

		void process(juce::AudioBuffer<float>& buffer) noexcept;

		void setModulationRate(float modRate);

		void setLfoWaveform(LfoWaveform lfw);
		void updateLfoWaveform();

		void setGainInDB(float gainInDb);
		void updateGain();

		void reset() noexcept;
		float modDepth = 0.4f;

	private:

		static float triangle(float phase) {
			const auto ft = phase / juce::MathConstants<float>::twoPi; // ft is triangles frequency * time
			return 4.f * std::abs(ft - std::floor(ft + 0.5f)) - 1.f;
		}

		std::array<juce::dsp::Oscillator<float>, 3> lfos{
			juce::dsp::Oscillator<float> {[](auto phase) { return std::sin(phase);}},
			juce::dsp::Oscillator<float> { triangle },
			juce::dsp::Oscillator<float> {[](auto phase) { return phase < 0.0f ? -1.f : 1.f; }}
		};

		float getNextLfoValue();
		LfoWaveform currentLfo = LfoWaveform::SINE;
		LfoWaveform lfoToSet = currentLfo;
		juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> lfoSmoothed{};


		float getNextGainValue();
		float currentGain{ 1.f }; // value used to apply gain after dB translation
		float gainToSet = currentGain;
		juce::LinearSmoothedValue<float> gainSmoothed{ 1.f };

	};

}  // namespace sky_trem
