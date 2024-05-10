//------------------------------------------------------------------------
// Copyright(c) 2024 fhw.
//------------------------------------------------------------------------

#include "myplugincontroller.h"
#include "myplugincids.h"
#include "vstgui/plugin-bindings/vst3editor.h"

#include "pluginterfaces/base/ibstream.h"
#include "base/source/fstreamer.h"

#include "synthParams.h"

using namespace Steinberg;

namespace MyCompanyName {

//------------------------------------------------------------------------
// SynthController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API SynthController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters

	// Oscillator knobs
	setKnobMode(Vst::kLinearMode);
	parameters.addParameter(STR16("OSC"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_1);
	parameters.addParameter(STR16("OSC1 Shape"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_1_Shape);

	parameters.addParameter(STR16("OSC"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_2);
	parameters.addParameter(STR16("OSC2 Shape"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_2_Shape);

	parameters.addParameter(STR16("ATK"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_Attack);
	parameters.addParameter(STR16("DEC"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_Decay);
	parameters.addParameter(STR16("SUS"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_Sustain);
	parameters.addParameter(STR16("REL"), nullptr, 0, default_Osc1, Vst::ParameterInfo::kCanAutomate, kOsc_Release);

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SynthController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API SynthController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	IBStreamer streamer(state, kLittleEndian);

	float fval;
	if (streamer.readFloat(fval) == false) {
		return kResultFalse;
	}

	setParamNormalized(kOsc_1, fval);
	setParamNormalized(kOsc_1_Shape, fval);
	setParamNormalized(kOsc_2, fval);
	setParamNormalized(kOsc_2_Shape, fval);

	setParamNormalized(kOsc_Attack, fval);
	setParamNormalized(kOsc_Decay, fval);
	setParamNormalized(kOsc_Sustain, fval);
	setParamNormalized(kOsc_Release, fval);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SynthController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SynthController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API SynthController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
		auto* view = new VSTGUI::VST3Editor (this, "view", "myplugineditor.uidesc");
		return view;
	}
	return nullptr;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
