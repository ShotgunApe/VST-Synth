//------------------------------------------------------------------------
// Copyright(c) 2024 fhw.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kSynthProcessorUID (0x223C07BD, 0x4A86536D, 0x888E7462, 0x265A99DD);
static const Steinberg::FUID kSynthControllerUID (0x7594B3E0, 0xEBBC5E99, 0x97E438D5, 0x6CE0C589);

#define SynthVST3Category "Instrument"

//------------------------------------------------------------------------
} // namespace MyCompanyName
