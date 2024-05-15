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

	// For Envelopes
	// Enum specific to finite state machine
	enum EnvelopeStage {
		ENVELOPE_STAGE_OFF = 0,
		ENVELOPE_STAGE_ATTACK,
		ENVELOPE_STAGE_DECAY,
		ENVELOPE_STAGE_SUSTAIN,
		ENVELOPE_STAGE_RELEASE,
		kNumEnvelopeStages
	};

	// Function to keep track of + enter new stages of Envelope Generator
	Steinberg::tresult PLUGIN_API enterStage(EnvelopeStage newStage, Steinberg::Vst::ProcessData& data);
	EnvelopeStage getCurrentStage();

	// Function that takes current sample and applies appropriate volume from Envelope 
	double nextSampleVolume(Steinberg::Vst::ProcessData& data);
	unsigned long long currentSampleIndex = 0;
	unsigned long long nextStageSampleIndex = 0;

	// default values
	const double minimumLevel = 0.0001f;
	EnvelopeStage currentStage = ENVELOPE_STAGE_OFF;
	double currentLevel = minimumLevel;
	double multiplier = 1.0f;

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

	float fOscAttack = default_Atk;
	float fOscDecay = default_Dec;
	float fOscSustain = default_Sus;
	float fOscRelease = default_Rel;

	double stageValue[kNumEnvelopeStages];
	void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
};

#define TWO_PI (3.14159265f * 2.f)

//------------------------------------------------------------------------
} // namespace MyCompanyName
