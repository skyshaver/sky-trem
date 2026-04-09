#pragma once

//https://github.com/juce-framework/JUCE/blob/master/examples/DSP/OscillatorDemo.h

namespace sky_trem {

	class Tremolo {

	public:
		enum class LfoWaveform : size_t {
			Sine = 0,
			Triangle = 1,
			Square = 2,
			Sawtooh = 3
		};

		Tremolo();

		void prepare(double sampleRate, int expectedMaxFramesPerBlock);

		void process(juce::AudioBuffer<float>& buffer) noexcept;

		void setModulationRate(float modRate);

		void setModulationDepth(float modDepth);
		void updateModulationDepth();

		void setLfoWaveform(LfoWaveform lfw);
		void updateLfoWaveform();

		void setGainInDB(float gainInDb);
		void updateGain();		

		void reset() noexcept;		

	private:
		static float triangle(float phase) {
			const auto ft = phase / juce::MathConstants<float>::twoPi; // ft is triangles frequency * time
			return 4.f * std::abs(ft - std::floor(ft + 0.5f)) - 1.f;
		}

		std::array<juce::dsp::Oscillator<float>, 4> lfos {
			juce::dsp::Oscillator<float> { [](auto phase) { return std::sin(phase);} }, // sine
			juce::dsp::Oscillator<float> { triangle },
			juce::dsp::Oscillator<float> { [](auto phase) { return phase < 0.0f ? -1.f : 1.f; } }, // square
			juce::dsp::Oscillator<float> { [](auto phase) { return phase / juce::MathConstants<float>::pi; } } // sawtooth
		};

		float getNextLfoValue();
		LfoWaveform currentLfo = LfoWaveform::Sine;
		LfoWaveform lfoToSet = currentLfo;
		juce::LinearSmoothedValue<float> lfoSmoothed{};


		float getNextGainValue();
		float currentGain{ 1.f }; // value used to apply gain after dB translation
		float gainToSet = currentGain;
		juce::LinearSmoothedValue<float> gainSmoothed{ 1.f };

		float getNextModulationDepthValue();
		float currentModulationDepth{ 0.4f };
		float modulationDepthToSet = currentModulationDepth;
		juce::LinearSmoothedValue<float> modulationDepthSmoothed{ 0.4f };

	};

}  // namespace sky_trem
 