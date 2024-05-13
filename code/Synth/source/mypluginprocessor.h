//------------------------------------------------------------------------
// Copyright(c) 2024 fhw.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

// Custom header files
#include "synthParams.h"

namespace MyCompanyName {

//------------------------------------------------------------------------
//  SynthProcessor
//------------------------------------------------------------------------
class SynthProcessor : public Steinberg::Vst::AudioEffect
{
public:
	SynthProcessor ();
	~SynthProcessor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new SynthProcessor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

protected:
	float fOsc1 = default_Osc1;
	float fOsc2 = default_Osc2;
	float fOsc1Phase = 0.f;
	float fOsc2Phase = 0.f;
	float fFrequency = 0.f;
	float fVolume = 0.f;
	float fDeltaAngle = 0.f;
	float fOsc1Mode = 0.f;
	float fOsc2Mode = 0.f;

	float fOscAttack = 0.f;
	float fOscDecay = 0.f;
	float fOscSustain = 0.f;
	float fOscRelease = 0.f;
};

class EnvelopeGenerator {
public:
	/** ENVELOPE GENERATOR INFO */

	// Enum specific to finite state machine
	enum EnvelopeStage {
		ENVELOPE_STAGE_OFF = 0,
		ENVELOPE_STAGE_ATTACK,
		ENVELOPE_STAGE_DECAY,
		ENVELOPE_STAGE_SUSTAIN,
		ENVELOPE_STAGE_RELEASE,
		kNumEnvelopeStages
	};
	void enterStage(EnvelopeStage newStage);
	EnvelopeStage getCurrentStage();
	const double minimumLevel;

	EnvelopeGenerator() :
		minimumLevel(0.0001),
		currentStage(ENVELOPE_STAGE_OFF),
		currentLevel(minimumLevel),
		multiplier(1.0),
		currentSampleIndex(0),
		nextStageSampleIndex(0) {
		stageValue[ENVELOPE_STAGE_OFF] = 0.0f;
		stageValue[ENVELOPE_STAGE_ATTACK] = 0.01f;
		stageValue[ENVELOPE_STAGE_DECAY] = 0.5f;
		stageValue[ENVELOPE_STAGE_SUSTAIN] = 0.1f;
		stageValue[ENVELOPE_STAGE_RELEASE] = 1.0f;
	};
private:
	EnvelopeStage currentStage;
	double currentLevel;
	double multiplier;
	double stageValue[kNumEnvelopeStages];
	void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
	unsigned long long currentSampleIndex;
	unsigned long long nextStageSampleIndex;
};


#define TWO_PI (3.14159265f * 2.f)

//------------------------------------------------------------------------
} // namespace MyCompanyName
