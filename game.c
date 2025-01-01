//
//  game.c
//  Extension OS X
//
//  Created by Dan Messing on 1/26/18.
//  Copyright © 2018 Panic, Inc. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "string.h"


static PlaydateAPI* pd = NULL;
#include "pocketpy.h"


#define ADD_ENUM(name) py_newint(py_emplacedict(mod, py_name(#name)), name)


static py_Type tp_json_reader;
static py_Type tp_outlvol;
static py_Type tp_synthDeallocFunc;
static py_Type tp_FileOptions;
static py_Type tp_PDTextWrappingMode;
static py_Type tp_SoundWaveform;
static py_Type tp_AudioSample;
static py_Type tp_outrvol;
static py_Type tp_DelayLineTap;
static py_Type tp_LCDSpriteDrawFunction;
static py_Type tp_signalDeallocFunc;
static py_Type tp_FileStat;
static py_Type tp_PDSynthSignalValue;
static py_Type tp_PDButtonCallbackFunction;
static py_Type tp_SoundSource;
static py_Type tp_ControlSignal;
static py_Type tp_LCDBitmap;
static py_Type tp_SoundSource_synth;
static py_Type tp_LCDBitmapFlip;
static py_Type tp_PDSynthSignal;
static py_Type tp_LCDFont;
static py_Type tp_SamplePlayer;
static py_Type tp_MicSource;
static py_Type tp_PDStringEncoding;
static py_Type tp_LCDVideoPlayer;
static py_Type tp_LCDSpriteCollisionFilterProc;
static py_Type tp_json_encoder;
static py_Type tp_TwoPoleFilter;
static py_Type tp_PDCallbackFunction;
static py_Type tp_SoundSource_instrument;
static py_Type tp_LCDBitmapTable;
static py_Type tp_const_luaL_Reg;
static py_Type tp_SoundFormat;
static py_Type tp_AudioInputFunction;
static py_Type tp_LCDBitmapDrawMode;
static py_Type tp_LuaUDObject;
static py_Type tp_PDRect;
static py_Type tp_SoundChannel;
static py_Type tp_synthSetParameterFunc;
static py_Type tp_synthRenderFunc;
static py_Type tp_effectProc;
static py_Type tp_BitCrusher;
static py_Type tp_RingModulator;
static py_Type tp_SoundSequence;
static py_Type tp_signalNoteOffFunc;
static py_Type tp_TwoPoleFilterType;
static py_Type tp_signalNoteOnFunc;
static py_Type tp_source;
static py_Type tp_LFOType;
static py_Type tp_PDSynthLFO;
static py_Type tp_MIDINote;
static py_Type tp_signalStepFunc;
static py_Type tp_synthNoteOnFunc;
static py_Type tp_const_lua_val;
static py_Type tp_LCDFontGlyph;
static py_Type tp_OnePoleFilter;
static py_Type tp_SDFile_userdata;
static py_Type tp_const_lua_reg;
static py_Type tp_uint32_t;
static py_Type tp_LCDColor;
static py_Type tp_LCDRect;
static py_Type tp_Overdrive;
static py_Type tp_struct_json_decoder;
static py_Type tp_synthCopyUserdataFunc;
static py_Type tp_SequenceTrack;
static py_Type tp_LCDPolygonFillRule;
static py_Type tp_PDButtons;
static py_Type tp_LCDFontPage;
static py_Type tp_LCDFontData;
static py_Type tp_FilePlayer;
static py_Type tp_va_list;
static py_Type tp_AudioSourceFunction;
static py_Type tp_writeFunc;
static py_Type tp_lua_CFunction;
static py_Type tp_rvol;
static py_Type tp_synthReleaseFunc;
static py_Type tp_lvol;
static py_Type tp_SoundEffect;
static py_Type tp_SequenceFinishedCallback;
static py_Type tp_struct_PDDateTime;
static py_Type tp_SDFile;
static py_Type tp_sndCallbackProc;
static py_Type tp_PDSynth;
static py_Type tp_PDPeripherals;
static py_Type tp_DelayLine;
static py_Type tp_json_value;
static py_Type tp_LCDSpriteUpdateFunction;
static py_Type tp_RingMoOverdrivedulator;
static py_Type tp_LCDLineCapStyle;
static py_Type tp_PDTextAlignment;
static py_Type tp_len;
static py_Type tp_PDSynthEnvelope;
static py_Type tp_LCDSprite;
static py_Type tp_PDSynthInstrument;
static py_Type tp_int16_t;
inline  void py_add_types(py_GlobalRef mod) {
    py_Type SoundSequence_type = py_newtype("SoundSequence", tp_object, mod, NULL);
    py_Type LCDVideoPlayer_type = py_newtype("LCDVideoPlayer", tp_object, mod, NULL);
    py_Type signalStepFunc_type = py_newtype("signalStepFunc", tp_object, mod, NULL);
    py_Type SequenceFinishedCallback_type = py_newtype("SequenceFinishedCallback", tp_object, mod, NULL);
    py_Type PDSynthSignalValue_type = py_newtype("PDSynthSignalValue", tp_object, mod, NULL);
    py_Type LCDBitmap_type = py_newtype("LCDBitmap", tp_object, mod, NULL);
    py_Type SoundWaveform_type = py_newtype("SoundWaveform", tp_object, mod, NULL);
    py_Type LCDFontData_type = py_newtype("LCDFontData", tp_object, mod, NULL);
    py_Type signalDeallocFunc_type = py_newtype("signalDeallocFunc", tp_object, mod, NULL);
    py_Type SoundFormat_type = py_newtype("SoundFormat", tp_object, mod, NULL);
    py_Type PDButtonCallbackFunction_type = py_newtype("PDButtonCallbackFunction", tp_object, mod, NULL);
    py_Type PDSynthEnvelope_type = py_newtype("PDSynthEnvelope", tp_object, mod, NULL);
    py_Type PDRect_type = py_newtype("PDRect", tp_object, mod, NULL);
    py_Type SDFile_userdata_type = py_newtype("SDFile_userdata", tp_object, mod, NULL);
    py_Type synthNoteOnFunc_type = py_newtype("synthNoteOnFunc", tp_object, mod, NULL);
    py_Type len_type = py_newtype("len", tp_object, mod, NULL);
    py_Type PDCallbackFunction_type = py_newtype("PDCallbackFunction", tp_object, mod, NULL);
    py_Type MicSource_type = py_newtype("MicSource", tp_object, mod, NULL);
    py_Type AudioSourceFunction_type = py_newtype("AudioSourceFunction", tp_object, mod, NULL);
    py_Type SoundSource_type = py_newtype("SoundSource", tp_object, mod, NULL);
    py_Type LCDLineCapStyle_type = py_newtype("LCDLineCapStyle", tp_object, mod, NULL);
    py_Type synthSetParameterFunc_type = py_newtype("synthSetParameterFunc", tp_object, mod, NULL);
    py_Type va_list_type = py_newtype("va_list", tp_object, mod, NULL);
    py_Type PDSynth_type = py_newtype("PDSynth", tp_object, mod, NULL);
    py_Type SoundEffect_type = py_newtype("SoundEffect", tp_object, mod, NULL);
    py_Type LCDFontPage_type = py_newtype("LCDFontPage", tp_object, mod, NULL);
    py_Type struct_json_decoder_type = py_newtype("struct_json_decoder", tp_object, mod, NULL);
    py_Type PDPeripherals_type = py_newtype("PDPeripherals", tp_object, mod, NULL);
    py_Type LCDFontGlyph_type = py_newtype("LCDFontGlyph", tp_object, mod, NULL);
    py_Type RingMoOverdrivedulator_type = py_newtype("RingMoOverdrivedulator", tp_object, mod, NULL);
    py_Type PDSynthInstrument_type = py_newtype("PDSynthInstrument", tp_object, mod, NULL);
    py_Type signalNoteOnFunc_type = py_newtype("signalNoteOnFunc", tp_object, mod, NULL);
    py_Type const_lua_reg_type = py_newtype("const_lua_reg", tp_object, mod, NULL);
    py_Type synthCopyUserdataFunc_type = py_newtype("synthCopyUserdataFunc", tp_object, mod, NULL);
    py_Type PDTextWrappingMode_type = py_newtype("PDTextWrappingMode", tp_object, mod, NULL);
    py_Type LCDSpriteDrawFunction_type = py_newtype("LCDSpriteDrawFunction", tp_object, mod, NULL);
    py_Type SequenceTrack_type = py_newtype("SequenceTrack", tp_object, mod, NULL);
    py_Type uint32_t_type = py_newtype("uint32_t", tp_object, mod, NULL);
    py_Type LCDPolygonFillRule_type = py_newtype("LCDPolygonFillRule", tp_object, mod, NULL);
    py_Type LCDRect_type = py_newtype("LCDRect", tp_object, mod, NULL);
    py_Type LCDSpriteUpdateFunction_type = py_newtype("LCDSpriteUpdateFunction", tp_object, mod, NULL);
    py_Type FileStat_type = py_newtype("FileStat", tp_object, mod, NULL);
    py_Type json_reader_type = py_newtype("json_reader", tp_object, mod, NULL);
    py_Type PDSynthLFO_type = py_newtype("PDSynthLFO", tp_object, mod, NULL);
    py_Type TwoPoleFilter_type = py_newtype("TwoPoleFilter", tp_object, mod, NULL);
    py_Type SoundSource_synth_type = py_newtype("SoundSource_synth", tp_object, mod, NULL);
    py_Type SamplePlayer_type = py_newtype("SamplePlayer", tp_object, mod, NULL);
    py_Type PDSynthSignal_type = py_newtype("PDSynthSignal", tp_object, mod, NULL);
    py_Type lvol_type = py_newtype("lvol", tp_object, mod, NULL);
    py_Type TwoPoleFilterType_type = py_newtype("TwoPoleFilterType", tp_object, mod, NULL);
    py_Type outrvol_type = py_newtype("outrvol", tp_object, mod, NULL);
    py_Type signalNoteOffFunc_type = py_newtype("signalNoteOffFunc", tp_object, mod, NULL);
    py_Type PDStringEncoding_type = py_newtype("PDStringEncoding", tp_object, mod, NULL);
    py_Type outlvol_type = py_newtype("outlvol", tp_object, mod, NULL);
    py_Type synthReleaseFunc_type = py_newtype("synthReleaseFunc", tp_object, mod, NULL);
    py_Type const_lua_val_type = py_newtype("const_lua_val", tp_object, mod, NULL);
    py_Type effectProc_type = py_newtype("effectProc", tp_object, mod, NULL);
    py_Type LuaUDObject_type = py_newtype("LuaUDObject", tp_object, mod, NULL);
    py_Type const_luaL_Reg_type = py_newtype("const_luaL_Reg", tp_object, mod, NULL);
    py_Type FileOptions_type = py_newtype("FileOptions", tp_object, mod, NULL);
    py_Type source_type = py_newtype("source", tp_object, mod, NULL);
    py_Type Overdrive_type = py_newtype("Overdrive", tp_object, mod, NULL);
    py_Type DelayLineTap_type = py_newtype("DelayLineTap", tp_object, mod, NULL);
    py_Type OnePoleFilter_type = py_newtype("OnePoleFilter", tp_object, mod, NULL);
    py_Type LFOType_type = py_newtype("LFOType", tp_object, mod, NULL);
    py_Type AudioInputFunction_type = py_newtype("AudioInputFunction", tp_object, mod, NULL);
    py_Type PDButtons_type = py_newtype("PDButtons", tp_object, mod, NULL);
    py_Type DelayLine_type = py_newtype("DelayLine", tp_object, mod, NULL);
    py_Type SDFile_type = py_newtype("SDFile", tp_object, mod, NULL);
    py_Type LCDSprite_type = py_newtype("LCDSprite", tp_object, mod, NULL);
    py_Type sndCallbackProc_type = py_newtype("sndCallbackProc", tp_object, mod, NULL);
    py_Type int16_t_type = py_newtype("int16_t", tp_object, mod, NULL);
    py_Type AudioSample_type = py_newtype("AudioSample", tp_object, mod, NULL);
    py_Type json_value_type = py_newtype("json_value", tp_object, mod, NULL);
    py_Type lua_CFunction_type = py_newtype("lua_CFunction", tp_object, mod, NULL);
    py_Type LCDColor_type = py_newtype("LCDColor", tp_object, mod, NULL);
    py_Type SoundSource_instrument_type = py_newtype("SoundSource_instrument", tp_object, mod, NULL);
    py_Type BitCrusher_type = py_newtype("BitCrusher", tp_object, mod, NULL);
    py_Type RingModulator_type = py_newtype("RingModulator", tp_object, mod, NULL);
    py_Type LCDFont_type = py_newtype("LCDFont", tp_object, mod, NULL);
    py_Type LCDBitmapTable_type = py_newtype("LCDBitmapTable", tp_object, mod, NULL);
    py_Type FilePlayer_type = py_newtype("FilePlayer", tp_object, mod, NULL);
    py_Type PDTextAlignment_type = py_newtype("PDTextAlignment", tp_object, mod, NULL);
    py_Type json_encoder_type = py_newtype("json_encoder", tp_object, mod, NULL);
    py_Type ControlSignal_type = py_newtype("ControlSignal", tp_object, mod, NULL);
    py_Type writeFunc_type = py_newtype("writeFunc", tp_object, mod, NULL);
    py_Type LCDBitmapDrawMode_type = py_newtype("LCDBitmapDrawMode", tp_object, mod, NULL);
    py_Type LCDSpriteCollisionFilterProc_type = py_newtype("LCDSpriteCollisionFilterProc", tp_object, mod, NULL);
    py_Type rvol_type = py_newtype("rvol", tp_object, mod, NULL);
    py_Type struct_PDDateTime_type = py_newtype("struct_PDDateTime", tp_object, mod, NULL);
    py_Type LCDBitmapFlip_type = py_newtype("LCDBitmapFlip", tp_object, mod, NULL);
    py_Type synthDeallocFunc_type = py_newtype("synthDeallocFunc", tp_object, mod, NULL);
    py_Type MIDINote_type = py_newtype("MIDINote", tp_object, mod, NULL);
    py_Type synthRenderFunc_type = py_newtype("synthRenderFunc", tp_object, mod, NULL);
    py_Type SoundChannel_type = py_newtype("SoundChannel", tp_object, mod, NULL);
}

static bool py_system_error(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    pd->system->error(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_system_logToConsole(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char** _0 = py_tostr(py_arg(0));
    pd->system->logToConsole(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_system_getCurrentTimeMilliseconds(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    unsigned int r_type = pd->system->getCurrentTimeMilliseconds();
    py_newobject(py_retval(), r_type, 0, sizeof(unsigned int));
    return true;
}
static bool py_system_getSecondsSinceEpoch(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    unsigned int _0 = py_toint(py_arg(0));
    unsigned int r_type = pd->system->getSecondsSinceEpoch(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(unsigned int));
    return true;
}
static bool py_system_resetElapsedTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->system->resetElapsedTime();
    py_newnone(py_retval());
    return true;
}
static bool py_system_getElapsedTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    float r_type = pd->system->getElapsedTime();
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_system_getTimezoneOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int32_t r_type = pd->system->getTimezoneOffset();
    py_newobject(py_retval(), r_type, 0, sizeof(int32_t));
    return true;
}
static bool py_system_convertEpochToDateTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    uint32_t* _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_struct_PDDateTime);
    struct PDDateTime* _1 = (struct PDDateTime*)py_touserdata(py_arg(1));
    pd->system->convertEpochToDateTime(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_system_convertDateTimeToEpoch(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_struct_PDDateTime);
    struct PDDateTime* _0 = (struct PDDateTime*)py_touserdata(py_arg(0));
    uint32_t r_type = pd->system->convertDateTimeToEpoch(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(uint32_t));
    return true;
}
static bool py_system_shouldDisplay24HourTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->system->shouldDisplay24HourTime();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_system_getFlipped(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->system->getFlipped();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_system_getReduceFlashing(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->system->getReduceFlashing();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_system_formatString(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    char _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    int r_type = pd->system->formatString(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_system_vaFormatString(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_str);
    char _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_va_list);
    va_list* _2 = (va_list*)py_touserdata(py_arg(2));
    int r_type = pd->system->vaFormatString(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_system_parseString(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    int r_type = pd->system->parseString(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_system_setUpdateCallback(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDCallbackFunction);
    PDCallbackFunction* _0 = (PDCallbackFunction*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    pd->system->setUpdateCallback(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_system_setSerialMessageCallback(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    pd->system->setSerialMessageCallback(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_system_drawFPS(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->system->drawFPS(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_system_getBatteryPercentage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    float r_type = pd->system->getBatteryPercentage();
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_system_getBatteryVoltage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    float r_type = pd->system->getBatteryVoltage();
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_getCurrentTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    uint32_t r_type = pd->sound->getCurrentTime();
    py_newobject(py_retval(), r_type, 0, sizeof(uint32_t));
    return true;
}
static bool py_sound_getDefaultChannel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    SoundChannel* r_type = pd->sound->getDefaultChannel();
    py_newobject(py_retval(), r_type, 0, sizeof(SoundChannel*));
    return true;
}
static bool py_sound_addChannel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    int r_type = pd->sound->addChannel(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_addSource(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_AudioSourceFunction);
    AudioSourceFunction* _0 = (AudioSourceFunction*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    SoundSource* r_type = pd->sound->addSource(_0, _1, _2);
    py_newobject(py_retval(), r_type, 0, sizeof(SoundSource*));
    return true;
}
static bool py_sound_removeSource(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSource);
    SoundSource* _0 = (SoundSource*)py_touserdata(py_arg(0));
    int r_type = pd->sound->removeSource(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_removeChannel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    int r_type = pd->sound->removeChannel(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_setMicCallback(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_AudioInputFunction);
    struct AudioInputFunction* _0 = (struct AudioInputFunction*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    int r_type = pd->sound->setMicCallback(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_setOutputsActive(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->setOutputsActive(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_newChannel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    SoundChannel* r_type = pd->sound->channel->newChannel();
    py_newobject(py_retval(), r_type, 0, sizeof(SoundChannel*));
    return true;
}
static bool py_sound_channel_freeChannel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    pd->sound->channel->freeChannel(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_addSource(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_SoundSource);
    SoundSource* _1 = (SoundSource*)py_touserdata(py_arg(1));
    pd->sound->channel->addSource(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_removeSource(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_SoundSource);
    SoundSource* _1 = (SoundSource*)py_touserdata(py_arg(1));
    int r_type = pd->sound->channel->removeSource(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_channel_addEffect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_SoundEffect);
    SoundEffect* _1 = (SoundEffect*)py_touserdata(py_arg(1));
    pd->sound->channel->addEffect(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_removeEffect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_SoundEffect);
    SoundEffect* _1 = (SoundEffect*)py_touserdata(py_arg(1));
    pd->sound->channel->removeEffect(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_setVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->channel->setVolume(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_getVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    float r_type = pd->sound->channel->getVolume(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_channel_setVolumeModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->channel->setVolumeModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_getVolumeModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->channel->getVolumeModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_channel_setPan(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->channel->setPan(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_setPanModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->channel->setPanModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_channel_getPanModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->channel->getPanModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_channel_addCallbackSource(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_AudioSourceFunction);
    AudioSourceFunction* _1 = (AudioSourceFunction*)py_touserdata(py_arg(1));
    void* _2 = py_touserdata(py_arg(2)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    SoundSource* r_type = pd->sound->channel->addCallbackSource(_0, _1, _2, _3);
    py_newobject(py_retval(), r_type, 0, sizeof(SoundSource*));
    return true;
}
static bool py_sound_channel_getDryLevelSignal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->channel->getDryLevelSignal(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_channel_getWetLevelSignal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundChannel);
    SoundChannel* _0 = (SoundChannel*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->channel->getWetLevelSignal(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_source_setVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SoundSource);
    SoundSource* _0 = (SoundSource*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->source->setVolume(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_source_getVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SoundSource);
    SoundSource* _0 = (SoundSource*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->source->getVolume(_0, &_1, &_2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_source_isPlaying(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSource);
    SoundSource* _0 = (SoundSource*)py_touserdata(py_arg(0));
    int r_type = pd->sound->source->isPlaying(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sample_newSampleBuffer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    AudioSample* r_type = pd->sound->sample->newSampleBuffer(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(AudioSample*));
    return true;
}
static bool py_sound_sample_loadIntoSample(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_AudioSample);
    AudioSample* _0 = (AudioSample*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    pd->sound->sample->loadIntoSample(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sample_load(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    AudioSample* r_type = pd->sound->sample->load(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(AudioSample*));
    return true;
}
static bool py_sound_sample_getData(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_AudioSample);
    AudioSample* _0 = (AudioSample*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint8_t _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_SoundFormat);
    SoundFormat* _2 = (SoundFormat*)py_touserdata(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    uint32_t* _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    uint32_t* _4 = py_toint(py_arg(4));
    pd->sound->sample->getData(_0, _1, _2, _3, _4);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sample_freeSample(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_AudioSample);
    AudioSample* _0 = (AudioSample*)py_touserdata(py_arg(0));
    pd->sound->sample->freeSample(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sample_getLength(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_AudioSample);
    AudioSample* _0 = (AudioSample*)py_touserdata(py_arg(0));
    float r_type = pd->sound->sample->getLength(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_newPlayer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    FilePlayer* r_type = pd->sound->fileplayer->newPlayer();
    py_newobject(py_retval(), r_type, 0, sizeof(FilePlayer*));
    return true;
}
static bool py_sound_fileplayer_freePlayer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    pd->sound->fileplayer->freePlayer(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_loadIntoPlayer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    int r_type = pd->sound->fileplayer->loadIntoPlayer(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_pause(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    pd->sound->fileplayer->pause(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_play(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    int r_type = pd->sound->fileplayer->play(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_isPlaying(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    int r_type = pd->sound->fileplayer->isPlaying(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_setBufferLength(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->fileplayer->setBufferLength(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_getLength(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    float r_type = pd->sound->fileplayer->getLength(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_setFinishCallback(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_sndCallbackProc);
    sndCallbackProc* _1 = (sndCallbackProc*)py_touserdata(py_arg(1));
    void* _2 = py_touserdata(py_arg(2)); // This is a callback function, this will not work but allows for compling
    pd->sound->fileplayer->setFinishCallback(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_didUnderrun(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    int r_type = pd->sound->fileplayer->didUnderrun(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_setLoopRange(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->fileplayer->setLoopRange(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_setOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->fileplayer->setOffset(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_getOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    float r_type = pd->sound->fileplayer->getOffset(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_setRate(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->fileplayer->setRate(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_getRate(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    float r_type = pd->sound->fileplayer->getRate(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_fileplayer_setStopOnUnderrun(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->fileplayer->setStopOnUnderrun(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_setVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->fileplayer->setVolume(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_getVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->fileplayer->getVolume(_0, &_1, &_2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_fileplayer_stop(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_FilePlayer);
    FilePlayer* _0 = (FilePlayer*)py_touserdata(py_arg(0));
    pd->sound->fileplayer->stop(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_getLength(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    float r_type = pd->sound->sampleplayer->getLength(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_sampleplayer_isPlaying(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    int r_type = pd->sound->sampleplayer->isPlaying(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sampleplayer_newPlayer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    SamplePlayer* r_type = pd->sound->sampleplayer->newPlayer();
    py_newobject(py_retval(), r_type, 0, sizeof(SamplePlayer*));
    return true;
}
static bool py_sound_sampleplayer_play(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    int r_type = pd->sound->sampleplayer->play(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sampleplayer_setFinishCallback(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_sndCallbackProc);
    sndCallbackProc* _1 = (sndCallbackProc*)py_touserdata(py_arg(1));
    void* _2 = py_touserdata(py_arg(2)); // This is a callback function, this will not work but allows for compling
    pd->sound->sampleplayer->setFinishCallback(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_setOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->sampleplayer->setOffset(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_getOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    float r_type = pd->sound->sampleplayer->getOffset(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_sampleplayer_setPlayRange(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    pd->sound->sampleplayer->setPlayRange(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_setPaused(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->sampleplayer->setPaused(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_setRate(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->sampleplayer->setRate(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_getRate(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    float r_type = pd->sound->sampleplayer->getRate(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_sampleplayer_setSample(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_AudioSample);
    AudioSample* _1 = (AudioSample*)py_touserdata(py_arg(1));
    pd->sound->sampleplayer->setSample(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_setVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->sampleplayer->setVolume(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_getVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->sampleplayer->getVolume(_0, &_1, &_2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_stop(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    pd->sound->sampleplayer->stop(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sampleplayer_freePlayer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SamplePlayer);
    SamplePlayer* _0 = (SamplePlayer*)py_touserdata(py_arg(0));
    pd->sound->sampleplayer->freePlayer(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_newSynth(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    PDSynth* r_type = pd->sound->synth->newSynth();
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynth*));
    return true;
}
static bool py_sound_synth_freeSynth(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    pd->sound->synth->freeSynth(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_copy(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PDSynth* r_type = pd->sound->synth->copy(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynth*));
    return true;
}
static bool py_sound_synth_setWaveform(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_SoundWaveform);
    SoundWaveform* _1 = (SoundWaveform*)py_touserdata(py_arg(1));
    pd->sound->synth->setWaveform(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setGenerator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(9);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_synthRenderFunc);
    synthRenderFunc* _2 = (synthRenderFunc*)py_touserdata(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_synthNoteOnFunc);
    synthNoteOnFunc* _3 = (synthNoteOnFunc*)py_touserdata(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_synthReleaseFunc);
    synthReleaseFunc* _4 = (synthReleaseFunc*)py_touserdata(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_synthSetParameterFunc);
    synthSetParameterFunc* _5 = (synthSetParameterFunc*)py_touserdata(py_arg(5));
    PY_CHECK_ARG_TYPE(6, tp_synthDeallocFunc);
    synthDeallocFunc* _6 = (synthDeallocFunc*)py_touserdata(py_arg(6));
    PY_CHECK_ARG_TYPE(7, tp_synthCopyUserdataFunc);
    struct synthCopyUserdataFunc* _7 = (struct synthCopyUserdataFunc*)py_touserdata(py_arg(7));
    void* _8 = py_touserdata(py_arg(8)); // This is a callback function, this will not work but allows for compling
    pd->sound->synth->setGenerator(_0, _1, _2, _3, _4, _5, _6, _7, _8);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setSample(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_AudioSample);
    AudioSample* _1 = (AudioSample*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    uint32_t* _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    uint32_t* _3 = py_toint(py_arg(3));
    pd->sound->synth->setSample(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setWavetable(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_AudioSample);
    AudioSample* _1 = (AudioSample*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    int r_type = pd->sound->synth->setWavetable(_0, _1, _2, _3, _4);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_synth_setAttackTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->synth->setAttackTime(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setDecayTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->synth->setDecayTime(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setSustainLevel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->synth->setSustainLevel(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setReleaseTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->synth->setReleaseTime(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_clearEnvelope(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    pd->sound->synth->clearEnvelope(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_getEnvelope(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PDSynthEnvelope* r_type = pd->sound->synth->getEnvelope(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthEnvelope*));
    return true;
}
static bool py_sound_synth_setTranspose(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->synth->setTranspose(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setFrequencyModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->synth->setFrequencyModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_getFrequencyModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->synth->getFrequencyModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_synth_setAmplitudeModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->synth->setAmplitudeModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_getAmplitudeModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->synth->getAmplitudeModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_synth_playNote(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    uint32_t* _4 = py_toint(py_arg(4));
    pd->sound->synth->playNote(_0, _1, _2, _3, _4);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_playMIDINote(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    uint32_t* _4 = py_toint(py_arg(4));
    pd->sound->synth->playMIDINote(_0, _1, _2, _3, _4);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_noteOff(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    pd->sound->synth->noteOff(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_setVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->synth->setVolume(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_isPlaying(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    int r_type = pd->sound->synth->isPlaying(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_synth_getParameterCount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    int r_type = pd->sound->synth->getParameterCount(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_synth_setParameter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    int r_type = pd->sound->synth->setParameter(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_synth_setParameterModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_PDSynthSignalValue);
    PDSynthSignalValue* _2 = (PDSynthSignalValue*)py_touserdata(py_arg(2));
    pd->sound->synth->setParameterModulator(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_synth_getParameterModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynth);
    PDSynth* _0 = (PDSynth*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PDSynthSignalValue* r_type = pd->sound->synth->getParameterModulator(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_instrument_newInstrument(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    PDSynthInstrument* r_type = pd->sound->instrument->newInstrument();
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthInstrument*));
    return true;
}
static bool py_sound_instrument_freeInstrument(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    pd->sound->instrument->freeInstrument(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_addVoice(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynth);
    PDSynth* _1 = (PDSynth*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float _4 = py_tofloat(py_arg(4));
    int r_type = pd->sound->instrument->addVoice(_0, _1, _2, _3, _4);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_instrument_playNote(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    uint32_t* _4 = py_toint(py_arg(4));
    PDSynth* r_type = pd->sound->instrument->playNote(_0, _1, _2, _3, _4);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynth*));
    return true;
}
static bool py_sound_instrument_playMIDINote(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    uint32_t* _4 = py_toint(py_arg(4));
    PDSynth* r_type = pd->sound->instrument->playMIDINote(_0, _1, _2, _3, _4);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynth*));
    return true;
}
static bool py_sound_instrument_noteOff(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    uint32_t* _2 = py_toint(py_arg(2));
    pd->sound->instrument->noteOff(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_setPitchBend(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->instrument->setPitchBend(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_setPitchBendRange(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->instrument->setPitchBendRange(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_setTranspose(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->instrument->setTranspose(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_allNotesOff(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    pd->sound->instrument->allNotesOff(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_setVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->instrument->setVolume(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_getVolume(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->instrument->getVolume(_0, &_1, &_2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_instrument_activeVoiceCount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthInstrument);
    PDSynthInstrument* _0 = (PDSynthInstrument*)py_touserdata(py_arg(0));
    int r_type = pd->sound->instrument->activeVoiceCount(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_signal_newSignal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_signalStepFunc);
    signalStepFunc* _0 = (signalStepFunc*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_signalNoteOnFunc);
    signalNoteOnFunc* _1 = (signalNoteOnFunc*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_signalNoteOffFunc);
    signalNoteOffFunc* _2 = (signalNoteOffFunc*)py_touserdata(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_signalDeallocFunc);
    signalDeallocFunc* _3 = (signalDeallocFunc*)py_touserdata(py_arg(3));
    void* _4 = py_touserdata(py_arg(4)); // This is a callback function, this will not work but allows for compling
    PDSynthSignal* r_type = pd->sound->signal->newSignal(_0, _1, _2, _3, _4);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignal*));
    return true;
}
static bool py_sound_signal_freeSignal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthSignal);
    PDSynthSignal* _0 = (PDSynthSignal*)py_touserdata(py_arg(0));
    pd->sound->signal->freeSignal(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_signal_getValue(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthSignal);
    PDSynthSignal* _0 = (PDSynthSignal*)py_touserdata(py_arg(0));
    float r_type = pd->sound->signal->getValue(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_signal_setValueOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthSignal);
    PDSynthSignal* _0 = (PDSynthSignal*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->signal->setValueOffset(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_signal_setValueScale(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthSignal);
    PDSynthSignal* _0 = (PDSynthSignal*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->signal->setValueScale(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_signal_newSignalForValue(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthSignalValue);
    PDSynthSignalValue* _0 = (PDSynthSignalValue*)py_touserdata(py_arg(0));
    PDSynthSignal* r_type = pd->sound->signal->newSignalForValue(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignal*));
    return true;
}
static bool py_sound_lfo_newLFO(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LFOType);
    LFOType* _0 = (LFOType*)py_touserdata(py_arg(0));
    PDSynthLFO* r_type = pd->sound->lfo->newLFO(*_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthLFO*));
    return true;
}
static bool py_sound_lfo_freeLFO(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    pd->sound->lfo->freeLFO(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setType(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LFOType);
    LFOType* _1 = (LFOType*)py_touserdata(py_arg(1));
    pd->sound->lfo->setType(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setRate(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->lfo->setRate(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setPhase(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->lfo->setPhase(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setStartPhase(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->lfo->setStartPhase(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setCenter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->lfo->setCenter(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setDepth(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->lfo->setDepth(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setArpeggiation(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->lfo->setArpeggiation(_0, _1, &_2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setDelay(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->lfo->setDelay(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_setRetrigger(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->lfo->setRetrigger(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_lfo_getValue(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    float r_type = pd->sound->lfo->getValue(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_lfo_setGlobal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthLFO);
    PDSynthLFO* _0 = (PDSynthLFO*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->lfo->setGlobal(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_newEnvelope(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PDSynthEnvelope* r_type = pd->sound->envelope->newEnvelope(_0, _1, _2, _3);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthEnvelope*));
    return true;
}
static bool py_sound_envelope_freeEnvelope(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    pd->sound->envelope->freeEnvelope(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setAttack(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->envelope->setAttack(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setDecay(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->envelope->setDecay(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setSustain(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->envelope->setSustain(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setRelease(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->envelope->setRelease(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setCurvature(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->envelope->setCurvature(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setVelocitySensitivity(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->envelope->setVelocitySensitivity(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setRateScaling(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    pd->sound->envelope->setRateScaling(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setLegato(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->envelope->setLegato(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_setRetrigger(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->envelope->setRetrigger(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_envelope_getValue(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDSynthEnvelope);
    PDSynthEnvelope* _0 = (PDSynthEnvelope*)py_touserdata(py_arg(0));
    float r_type = pd->sound->envelope->getValue(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_effect_newEffect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_effectProc);
    effectProc* _0 = (effectProc*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    SoundEffect* r_type = pd->sound->effect->newEffect(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(SoundEffect*));
    return true;
}
static bool py_sound_effect_freeEffect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundEffect);
    SoundEffect* _0 = (SoundEffect*)py_touserdata(py_arg(0));
    pd->sound->effect->freeEffect(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_setMix(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundEffect);
    SoundEffect* _0 = (SoundEffect*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->setMix(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_setMixModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundEffect);
    SoundEffect* _0 = (SoundEffect*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->setMixModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_getMixModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundEffect);
    SoundEffect* _0 = (SoundEffect*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->getMixModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_setUserdata(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundEffect);
    SoundEffect* _0 = (SoundEffect*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    pd->sound->effect->setUserdata(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_getUserdata(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundEffect);
    SoundEffect* _0 = (SoundEffect*)py_touserdata(py_arg(0));
    void* r_type = pd->sound->effect->getUserdata(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(void*));
    return true;
}
static bool py_sound_effect_twopolefilter_newFilter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    TwoPoleFilter* r_type = pd->sound->effect->twopolefilter->newFilter();
    py_newobject(py_retval(), r_type, 0, sizeof(TwoPoleFilter*));
    return true;
}
static bool py_sound_effect_twopolefilter_freeFilter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    pd->sound->effect->twopolefilter->freeFilter(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_twopolefilter_setType(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_TwoPoleFilterType);
    TwoPoleFilterType* _1 = (TwoPoleFilterType*)py_touserdata(py_arg(1));
    pd->sound->effect->twopolefilter->setType(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_twopolefilter_setFrequency(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->twopolefilter->setFrequency(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_twopolefilter_setFrequencyModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->twopolefilter->setFrequencyModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_twopolefilter_getFrequencyModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->twopolefilter->getFrequencyModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_twopolefilter_setGain(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->twopolefilter->setGain(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_twopolefilter_setResonance(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->twopolefilter->setResonance(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_twopolefilter_setResonanceModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->twopolefilter->setResonanceModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_twopolefilter_getResonanceModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_TwoPoleFilter);
    TwoPoleFilter* _0 = (TwoPoleFilter*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->twopolefilter->getResonanceModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_onepolefilter_newFilter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    OnePoleFilter* r_type = pd->sound->effect->onepolefilter->newFilter();
    py_newobject(py_retval(), r_type, 0, sizeof(OnePoleFilter*));
    return true;
}
static bool py_sound_effect_onepolefilter_freeFilter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_OnePoleFilter);
    OnePoleFilter* _0 = (OnePoleFilter*)py_touserdata(py_arg(0));
    pd->sound->effect->onepolefilter->freeFilter(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_onepolefilter_setParameter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_OnePoleFilter);
    OnePoleFilter* _0 = (OnePoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->onepolefilter->setParameter(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_onepolefilter_setParameterModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_OnePoleFilter);
    OnePoleFilter* _0 = (OnePoleFilter*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->onepolefilter->setParameterModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_onepolefilter_getParameterModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_OnePoleFilter);
    OnePoleFilter* _0 = (OnePoleFilter*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->onepolefilter->getParameterModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_bitcrusher_newBitCrusher(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    BitCrusher* r_type = pd->sound->effect->bitcrusher->newBitCrusher();
    py_newobject(py_retval(), r_type, 0, sizeof(BitCrusher*));
    return true;
}
static bool py_sound_effect_bitcrusher_freeBitCrusher(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_BitCrusher);
    BitCrusher* _0 = (BitCrusher*)py_touserdata(py_arg(0));
    pd->sound->effect->bitcrusher->freeBitCrusher(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_bitcrusher_setAmount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_BitCrusher);
    BitCrusher* _0 = (BitCrusher*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->bitcrusher->setAmount(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_bitcrusher_setAmountModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_BitCrusher);
    BitCrusher* _0 = (BitCrusher*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->bitcrusher->setAmountModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_bitcrusher_getAmountModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_BitCrusher);
    BitCrusher* _0 = (BitCrusher*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->bitcrusher->getAmountModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_bitcrusher_setUndersampling(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_BitCrusher);
    BitCrusher* _0 = (BitCrusher*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->bitcrusher->setUndersampling(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_bitcrusher_setUndersampleModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_BitCrusher);
    BitCrusher* _0 = (BitCrusher*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->bitcrusher->setUndersampleModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_bitcrusher_getUndersampleModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_BitCrusher);
    BitCrusher* _0 = (BitCrusher*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->bitcrusher->getUndersampleModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_ringmodulator_newRingmod(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    RingModulator* r_type = pd->sound->effect->ringmodulator->newRingmod();
    py_newobject(py_retval(), r_type, 0, sizeof(RingModulator*));
    return true;
}
static bool py_sound_effect_ringmodulator_setFrequency(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_RingModulator);
    RingModulator* _0 = (RingModulator*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->ringmodulator->setFrequency(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_ringmodulator_setFrequencyModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_RingModulator);
    RingModulator* _0 = (RingModulator*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->ringmodulator->setFrequencyModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_ringmodulator_getFrequencyModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_RingModulator);
    RingModulator* _0 = (RingModulator*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->ringmodulator->getFrequencyModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_overdrive_newOverdrive(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    Overdrive* r_type = pd->sound->effect->overdrive->newOverdrive();
    py_newobject(py_retval(), r_type, 0, sizeof(Overdrive*));
    return true;
}
static bool py_sound_effect_overdrive_freeOverdrive(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_Overdrive);
    Overdrive* _0 = (Overdrive*)py_touserdata(py_arg(0));
    pd->sound->effect->overdrive->freeOverdrive(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_overdrive_setGain(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_Overdrive);
    Overdrive* _0 = (Overdrive*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->overdrive->setGain(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_overdrive_setLimit(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_Overdrive);
    Overdrive* _0 = (Overdrive*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->overdrive->setLimit(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_overdrive_setLimitModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_Overdrive);
    Overdrive* _0 = (Overdrive*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->overdrive->setLimitModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_overdrive_getLimitModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_RingMoOverdrivedulator);
    struct RingMoOverdrivedulator* _0 = (struct RingMoOverdrivedulator*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->overdrive->getLimitModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_overdrive_setOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_Overdrive);
    Overdrive* _0 = (Overdrive*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->overdrive->setOffset(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_overdrive_setOffsetModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_Overdrive);
    Overdrive* _0 = (Overdrive*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->overdrive->setOffsetModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_overdrive_getOffsetModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_RingMoOverdrivedulator);
    struct RingMoOverdrivedulator* _0 = (struct RingMoOverdrivedulator*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->overdrive->getOffsetModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_delayline_newDelayLine(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    DelayLine* r_type = pd->sound->effect->delayline->newDelayLine(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(DelayLine*));
    return true;
}
static bool py_sound_effect_delayline_freeDelayLine(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_DelayLine);
    DelayLine* _0 = (DelayLine*)py_touserdata(py_arg(0));
    pd->sound->effect->delayline->freeDelayLine(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_delayline_setLength(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_DelayLine);
    DelayLine* _0 = (DelayLine*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->effect->delayline->setLength(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_delayline_setFeedback(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_DelayLine);
    DelayLine* _0 = (DelayLine*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->effect->delayline->setFeedback(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_delayline_addTap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_DelayLine);
    DelayLine* _0 = (DelayLine*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    DelayLineTap* r_type = pd->sound->effect->delayline->addTap(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(DelayLineTap*));
    return true;
}
static bool py_sound_effect_delayline_freeTap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_DelayLineTap);
    DelayLineTap* _0 = (DelayLineTap*)py_touserdata(py_arg(0));
    pd->sound->effect->delayline->freeTap(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_delayline_setTapDelay(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_DelayLineTap);
    DelayLineTap* _0 = (DelayLineTap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->effect->delayline->setTapDelay(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_delayline_setTapDelayModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_DelayLineTap);
    DelayLineTap* _0 = (DelayLineTap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthSignalValue);
    PDSynthSignalValue* _1 = (PDSynthSignalValue*)py_touserdata(py_arg(1));
    pd->sound->effect->delayline->setTapDelayModulator(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_effect_delayline_getTapDelayModulator(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_DelayLineTap);
    DelayLineTap* _0 = (DelayLineTap*)py_touserdata(py_arg(0));
    PDSynthSignalValue* r_type = pd->sound->effect->delayline->getTapDelayModulator(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthSignalValue*));
    return true;
}
static bool py_sound_effect_delayline_setTapChannelsFlipped(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_DelayLineTap);
    DelayLineTap* _0 = (DelayLineTap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->effect->delayline->setTapChannelsFlipped(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_newSequence(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    SoundSequence* r_type = pd->sound->sequence->newSequence();
    py_newobject(py_retval(), r_type, 0, sizeof(SoundSequence*));
    return true;
}
static bool py_sound_sequence_freeSequence(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    pd->sound->sequence->freeSequence(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_loadMIDIFile(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    int r_type = pd->sound->sequence->loadMIDIFile(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sequence_play(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_SequenceFinishedCallback);
    SequenceFinishedCallback* _1 = (SequenceFinishedCallback*)py_touserdata(py_arg(1));
    void* _2 = py_touserdata(py_arg(2)); // This is a callback function, this will not work but allows for compling
    pd->sound->sequence->play(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_stop(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    pd->sound->sequence->stop(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_isPlaying(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    int r_type = pd->sound->sequence->isPlaying(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sequence_getTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    uint32_t r_type = pd->sound->sequence->getTime(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(uint32_t));
    return true;
}
static bool py_sound_sequence_setTime(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    pd->sound->sequence->setTime(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_setLoops(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    pd->sound->sequence->setLoops(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_getTempo(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    float r_type = pd->sound->sequence->getTempo(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_sound_sequence_setTempo(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    pd->sound->sequence->setTempo(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_getLength(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    int r_type = pd->sound->sequence->getLength(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sequence_getTrackCount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    int r_type = pd->sound->sequence->getTrackCount(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sequence_addTrack(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    SequenceTrack* r_type = pd->sound->sequence->addTrack(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(SequenceTrack*));
    return true;
}
static bool py_sound_sequence_getTrackAtIndex(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    unsigned int _1 = py_toint(py_arg(1));
    SequenceTrack* r_type = pd->sound->sequence->getTrackAtIndex(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(SequenceTrack*));
    return true;
}
static bool py_sound_sequence_setTrackAtIndex(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_SequenceTrack);
    SequenceTrack* _1 = (SequenceTrack*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    unsigned int _2 = py_toint(py_arg(2));
    pd->sound->sequence->setTrackAtIndex(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_allNotesOff(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    pd->sound->sequence->allNotesOff(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_sequence_getCurrentStep(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    int r_type = pd->sound->sequence->getCurrentStep(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_sequence_setCurrentStep(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_SoundSequence);
    SoundSequence* _0 = (SoundSequence*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    pd->sound->sequence->setCurrentStep(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_controlsignal_newSignal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    ControlSignal* r_type = pd->sound->controlsignal->newSignal();
    py_newobject(py_retval(), r_type, 0, sizeof(ControlSignal*));
    return true;
}
static bool py_sound_controlsignal_freeSignal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_ControlSignal);
    ControlSignal* _0 = (ControlSignal*)py_touserdata(py_arg(0));
    pd->sound->controlsignal->freeSignal(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_controlsignal_clearEvents(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_ControlSignal);
    ControlSignal* _0 = (ControlSignal*)py_touserdata(py_arg(0));
    pd->sound->controlsignal->clearEvents(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_controlsignal_addEvent(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_ControlSignal);
    ControlSignal* _0 = (ControlSignal*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    pd->sound->controlsignal->addEvent(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_controlsignal_removeEvent(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_ControlSignal);
    ControlSignal* _0 = (ControlSignal*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->controlsignal->removeEvent(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_controlsignal_getMIDIControllerNumber(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_ControlSignal);
    ControlSignal* _0 = (ControlSignal*)py_touserdata(py_arg(0));
    int r_type = pd->sound->controlsignal->getMIDIControllerNumber(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_track_newTrack(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    SequenceTrack* r_type = pd->sound->track->newTrack();
    py_newobject(py_retval(), r_type, 0, sizeof(SequenceTrack*));
    return true;
}
static bool py_sound_track_freeTrack(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    pd->sound->track->freeTrack(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_setInstrument(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDSynthInstrument);
    PDSynthInstrument* _1 = (PDSynthInstrument*)py_touserdata(py_arg(1));
    pd->sound->track->setInstrument(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_getInstrument(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PDSynthInstrument* r_type = pd->sound->track->getInstrument(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(PDSynthInstrument*));
    return true;
}
static bool py_sound_track_addNoteEvent(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    uint32_t* _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float _4 = py_tofloat(py_arg(4));
    pd->sound->track->addNoteEvent(_0, _1, _2, _3, _4);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_removeNoteEvent(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sound->track->removeNoteEvent(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_clearNotes(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    pd->sound->track->clearNotes(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_getLength(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    int r_type = pd->sound->track->getLength(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_track_getIndexForStep(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    int r_type = pd->sound->track->getIndexForStep(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_track_getNoteAtIndex(int argc, py_Ref argv) {
    PY_CHECK_ARGC(6);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    uint32_t* _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    uint32_t* _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float* _4 = (float*)py_touserdata(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_float);
    float _5 = py_tofloat(py_arg(5));
    int r_type = pd->sound->track->getNoteAtIndex(_0, _1, _2, _3, _4, &_5);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_track_getControlSignalCount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    pd->sound->track->getControlSignalCount(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_getControlSignal(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->track->getControlSignal(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_getSignalForController(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    pd->sound->track->getSignalForController(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_clearControlEvents(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    pd->sound->track->clearControlEvents(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sound_track_activeVoiceCount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    int r_type = pd->sound->track->activeVoiceCount(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_track_getPolyphony(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    int r_type = pd->sound->track->getPolyphony(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sound_track_setMuted(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_SequenceTrack);
    SequenceTrack* _0 = (SequenceTrack*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sound->track->setMuted(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_display_getHeight(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->display->getHeight();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_display_getWidth(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->display->getWidth();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_display_setInverted(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    pd->display->setInverted(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_display_setMosaic(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    unsigned int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    unsigned int _1 = py_toint(py_arg(1));
    pd->display->setMosaic(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_display_setFlipped(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->display->setFlipped(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_display_setRefreshRate(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    pd->display->setRefreshRate(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_display_setScale(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    unsigned int _0 = py_toint(py_arg(0));
    pd->display->setScale(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_display_setOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->display->setOffset(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_file_geterr(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    const char** r_type = pd->file->geterr();
    py_newobject(py_retval(), r_type, 0, sizeof(const char**));
    return true;
}
static bool py_file_unlink(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    int r_type = pd->file->unlink(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_mkdir(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    int r_type = pd->file->mkdir(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_rename(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    int r_type = pd->file->rename(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_stat(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_FileStat);
    FileStat* _1 = (FileStat*)py_touserdata(py_arg(1));
    int r_type = pd->file->stat(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_open(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_FileOptions);
    FileOptions* _1 = (FileOptions*)py_touserdata(py_arg(1));
    SDFile* r_type = pd->file->open(_0, *_1);
    py_newobject(py_retval(), r_type, 0, sizeof(SDFile*));
    return true;
}
static bool py_file_close(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SDFile);
    SDFile* _0 = (SDFile*)py_touserdata(py_arg(0));
    int r_type = pd->file->close(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_flush(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SDFile);
    SDFile* _0 = (SDFile*)py_touserdata(py_arg(0));
    int r_type = pd->file->flush(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_read(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SDFile);
    SDFile* _0 = (SDFile*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(2, tp_int);
    unsigned int _2 = py_toint(py_arg(2));
    int r_type = pd->file->read(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_seek(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SDFile);
    SDFile* _0 = (SDFile*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    int r_type = pd->file->seek(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_tell(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_SDFile);
    SDFile* _0 = (SDFile*)py_touserdata(py_arg(0));
    int r_type = pd->file->tell(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_file_write(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_SDFile);
    SDFile* _0 = (SDFile*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(2, tp_int);
    unsigned int _2 = py_toint(py_arg(2));
    int r_type = pd->file->write(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_pushContext(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    pd->graphics->pushContext(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_popContext(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->graphics->popContext();
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setStencil(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    pd->graphics->setStencil(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setStencilImage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->graphics->setStencilImage(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setDrawMode(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmapDrawMode);
    LCDBitmapDrawMode* _0 = (LCDBitmapDrawMode*)py_touserdata(py_arg(0));
    LCDBitmapDrawMode r_type = pd->graphics->setDrawMode(*_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmapDrawMode));
    return true;
}
static bool py_graphics_setClipRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    pd->graphics->setClipRect(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setScreenClipRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    pd->graphics->setScreenClipRect(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_clearClipRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->graphics->clearClipRect();
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setLineCapStyle(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDLineCapStyle);
    LCDLineCapStyle* _0 = (LCDLineCapStyle*)py_touserdata(py_arg(0));
    pd->graphics->setLineCapStyle(*_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setFont(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDFont);
    LCDFont* _0 = (LCDFont*)py_touserdata(py_arg(0));
    pd->graphics->setFont(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setTextTracking(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    pd->graphics->setTextTracking(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_getTextTracking(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->graphics->getTextTracking();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_setTextLeading(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    pd->graphics->setTextLeading(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_clearBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDColor);
    LCDColor* _1 = (LCDColor*)py_touserdata(py_arg(1));
    pd->graphics->clearBitmap(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_copyBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    LCDBitmap* r_type = pd->graphics->copyBitmap(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_checkMaskCollision(int argc, py_Ref argv) {
    PY_CHECK_ARGC(9);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_LCDBitmapFlip);
    LCDBitmapFlip* _3 = (LCDBitmapFlip*)py_touserdata(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_LCDBitmap);
    LCDBitmap* _4 = (LCDBitmap*)py_touserdata(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_int);
    int _5 = py_toint(py_arg(5));
    PY_CHECK_ARG_TYPE(6, tp_int);
    int _6 = py_toint(py_arg(6));
    PY_CHECK_ARG_TYPE(7, tp_LCDBitmapFlip);
    LCDBitmapFlip* _7 = (LCDBitmapFlip*)py_touserdata(py_arg(7));
    PY_CHECK_ARG_TYPE(8, tp_LCDRect);
    LCDRect* _8 = (LCDRect*)py_touserdata(py_arg(8));
    int r_type = pd->graphics->checkMaskCollision(_0, _1, _2, *_3, _4, _5, _6, *_7, *_8);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_drawBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_LCDBitmapFlip);
    LCDBitmapFlip* _3 = (LCDBitmapFlip*)py_touserdata(py_arg(3));
    pd->graphics->drawBitmap(_0, _1, _2, *_3);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_drawScaledBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float _4 = py_tofloat(py_arg(4));
    pd->graphics->drawScaledBitmap(_0, _1, _2, _3, _4);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_drawRotatedBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(8);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float _4 = py_tofloat(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_float);
    float _5 = py_tofloat(py_arg(5));
    PY_CHECK_ARG_TYPE(6, tp_float);
    float _6 = py_tofloat(py_arg(6));
    PY_CHECK_ARG_TYPE(7, tp_float);
    float _7 = py_tofloat(py_arg(7));
    pd->graphics->drawRotatedBitmap(_0, _1, _2, _3, _4, _5, _6, _7);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_freeBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    pd->graphics->freeBitmap(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_getBitmapData(int argc, py_Ref argv) {
    PY_CHECK_ARGC(6);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    uint8_t _4 = py_toint(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_int);
    uint8_t _5 = py_toint(py_arg(5));
    pd->graphics->getBitmapData(_0, _1, _2, _3, _4, _5);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_getBitmapPixel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    LCDSolidColor r_type = pd->graphics->getBitmapPixel(_0, _1, _2);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSolidColor));
    return true;
}
static bool py_graphics_loadBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    LCDBitmap* r_type = pd->graphics->loadBitmap(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_loadIntoBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmap);
    LCDBitmap* _1 = (LCDBitmap*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_str);
    const char* _2 = py_tostr(py_arg(2));
    pd->graphics->loadIntoBitmap(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_newBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_LCDColor);
    LCDColor* _2 = (LCDColor*)py_touserdata(py_arg(2));
    LCDBitmap* r_type = pd->graphics->newBitmap(_0, _1, _2);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_tileBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(6);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_LCDBitmapFlip);
    LCDBitmapFlip* _5 = (LCDBitmapFlip*)py_touserdata(py_arg(5));
    pd->graphics->tileBitmap(_0, _1, _2, _3, _4, *_5);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_rotatedBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    LCDBitmap* r_type = pd->graphics->rotatedBitmap(_0, _1, _2, _3, _4);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_setBitmapMask(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmap);
    LCDBitmap* _1 = (LCDBitmap*)py_touserdata(py_arg(1));
    int r_type = pd->graphics->setBitmapMask(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_getBitmapMask(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    LCDBitmap* r_type = pd->graphics->getBitmapMask(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_getTableBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmapTable);
    LCDBitmapTable* _0 = (LCDBitmapTable*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    LCDBitmap* r_type = pd->graphics->getTableBitmap(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_loadBitmapTable(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    LCDBitmapTable* r_type = pd->graphics->loadBitmapTable(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmapTable*));
    return true;
}
static bool py_graphics_loadIntoBitmapTable(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmapTable);
    LCDBitmapTable* _1 = (LCDBitmapTable*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_str);
    const char* _2 = py_tostr(py_arg(2));
    pd->graphics->loadIntoBitmapTable(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_newBitmapTable(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    LCDBitmapTable* r_type = pd->graphics->newBitmapTable(_0, _1, _2);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmapTable*));
    return true;
}
static bool py_graphics_freeBitmapTable(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmapTable);
    LCDBitmapTable* _0 = (LCDBitmapTable*)py_touserdata(py_arg(0));
    pd->graphics->freeBitmapTable(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_getBitmapTableInfo(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmapTable);
    LCDBitmapTable* _0 = (LCDBitmapTable*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    pd->graphics->getBitmapTableInfo(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_drawText(int argc, py_Ref argv) {
    /*PY_CHECK_ARG_TYPE(0, tp_str);
    char* _0 = py_tostr(py_arg(0));*/
    PY_CHECK_ARGC(5);
    void* _0 = py_touserdata(py_arg(0)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(1, tp_int);
    size_t _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_PDStringEncoding);
    PDStringEncoding* _2 = (PDStringEncoding*)py_touserdata(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    int r_type = pd->graphics->drawText(_0, _1, *_2, _3, _4);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_getFontHeight(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDFont);
    LCDFont* _0 = (LCDFont*)py_touserdata(py_arg(0));
    uint8_t r_type = pd->graphics->getFontHeight(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(uint8_t));
    return true;
}
static bool py_graphics_getFontPage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDFont);
    LCDFont* _0 = (LCDFont*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    LCDFontPage* r_type = pd->graphics->getFontPage(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDFontPage*));
    return true;
}
static bool py_graphics_getPageGlyph(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_LCDFontPage);
    LCDFontPage* _0 = (LCDFontPage*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_LCDBitmap);
    LCDBitmap* _2 = (LCDBitmap*)py_touserdata(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    LCDFontGlyph* r_type = pd->graphics->getPageGlyph(_0, _1, _2, _3);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDFontGlyph*));
    return true;
}
static bool py_graphics_getGlyphKerning(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDFontGlyph);
    LCDFontGlyph* _0 = (LCDFontGlyph*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint32_t* _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    uint32_t* _2 = py_toint(py_arg(2));
    int r_type = pd->graphics->getGlyphKerning(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_getTextWidth(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_LCDFont);
    LCDFont* _0 = (LCDFont*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(2, tp_int);
    size_t _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_PDStringEncoding);
    PDStringEncoding* _3 = (PDStringEncoding*)py_touserdata(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    int r_type = pd->graphics->getTextWidth(_0, _1, _2, *_3, _4);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_loadFont(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    LCDFont* r_type = pd->graphics->loadFont(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDFont*));
    return true;
}
static bool py_graphics_makeFontFromData(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDFontData);
    LCDFontData* _0 = (LCDFontData*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    LCDFont* r_type = pd->graphics->makeFontFromData(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDFont*));
    return true;
}
static bool py_graphics_drawEllipse(int argc, py_Ref argv) {
    PY_CHECK_ARGC(8);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_float);
    float _5 = py_tofloat(py_arg(5));
    PY_CHECK_ARG_TYPE(6, tp_float);
    float _6 = py_tofloat(py_arg(6));
    PY_CHECK_ARG_TYPE(7, tp_LCDColor);
    LCDColor* _7 = (LCDColor*)py_touserdata(py_arg(7));
    pd->graphics->drawEllipse(_0, _1, _2, _3, _4, _5, _6, _7);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_fillEllipse(int argc, py_Ref argv) {
    PY_CHECK_ARGC(7);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float _4 = py_tofloat(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_float);
    float _5 = py_tofloat(py_arg(5));
    PY_CHECK_ARG_TYPE(6, tp_LCDColor);
    LCDColor* _6 = (LCDColor*)py_touserdata(py_arg(6));
    pd->graphics->fillEllipse(_0, _1, _2, _3, _4, _5, _6);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_drawLine(int argc, py_Ref argv) {
    PY_CHECK_ARGC(6);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_LCDColor);
    LCDColor* _5 = (LCDColor*)py_touserdata(py_arg(5));
    pd->graphics->drawLine(_0, _1, _2, _3, _4, _5);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_drawRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_LCDColor);
    LCDColor* _4 = (LCDColor*)py_touserdata(py_arg(4));
    pd->graphics->drawRect(_0, _1, _2, _3, _4);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_fillRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_LCDColor);
    LCDColor* _4 = (LCDColor*)py_touserdata(py_arg(4));
    pd->graphics->fillRect(_0, _1, _2, _3, _4);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_fillTriangle(int argc, py_Ref argv) {
    PY_CHECK_ARGC(7);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_int);
    int _5 = py_toint(py_arg(5));
    PY_CHECK_ARG_TYPE(6, tp_LCDColor);
    LCDColor* _6 = (LCDColor*)py_touserdata(py_arg(6));
    pd->graphics->fillTriangle(_0, _1, _2, _3, _4, _5, _6);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_fillPolygon(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_LCDColor);
    LCDColor* _2 = (LCDColor*)py_touserdata(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_LCDPolygonFillRule);
    LCDPolygonFillRule* _3 = (LCDPolygonFillRule*)py_touserdata(py_arg(3));
    pd->graphics->fillPolygon(_0, _1, _2, *_3);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_clear(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDColor);
    LCDColor* _0 = (LCDColor*)py_touserdata(py_arg(0));
    pd->graphics->clear(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_display(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->graphics->display();
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_getDebugBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    LCDBitmap* r_type = pd->graphics->getDebugBitmap();
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_getDisplayFrame(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    uint8_t* r_type = pd->graphics->getDisplayFrame();
    py_newobject(py_retval(), r_type, 0, sizeof(uint8_t*));
    return true;
}
static bool py_graphics_getDisplayBufferBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    LCDBitmap* r_type = pd->graphics->getDisplayBufferBitmap();
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_graphics_getFrame(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    uint8_t* r_type = pd->graphics->getFrame();
    py_newobject(py_retval(), r_type, 0, sizeof(uint8_t*));
    return true;
}
static bool py_graphics_copyFrameBufferBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    LCDBitmap* r_type = pd->graphics->copyFrameBufferBitmap();
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_system_getLanguage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    PDLanguage r_type = pd->system->getLanguage();
    py_newobject(py_retval(), r_type, 0, sizeof(PDLanguage));
    return true;
}
static bool py_graphics_markUpdatedRows(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->graphics->markUpdatedRows(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setDrawOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->graphics->setDrawOffset(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setColorToPattern(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_LCDColor);
    LCDColor* _0 = (LCDColor*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmap);
    LCDBitmap* _1 = (LCDBitmap*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    pd->graphics->setColorToPattern(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_setPixel(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_LCDColor);
    LCDColor* _2 = (LCDColor*)py_touserdata(py_arg(2));
    pd->graphics->setPixel(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_video_loadVideo(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    LCDVideoPlayer* r_type = pd->graphics->video->loadVideo(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDVideoPlayer*));
    return true;
}
static bool py_graphics_video_freePlayer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDVideoPlayer);
    LCDVideoPlayer* _0 = (LCDVideoPlayer*)py_touserdata(py_arg(0));
    pd->graphics->video->freePlayer(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_video_setContext(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDVideoPlayer);
    LCDVideoPlayer* _0 = (LCDVideoPlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmap);
    LCDBitmap* _1 = (LCDBitmap*)py_touserdata(py_arg(1));
    int r_type = pd->graphics->video->setContext(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_graphics_video_getContext(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDVideoPlayer);
    LCDVideoPlayer* _0 = (LCDVideoPlayer*)py_touserdata(py_arg(0));
    struct LCBitmap* r_type = pd->graphics->video->getContext(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(struct LCBitmap*));
    return true;
}
static bool py_graphics_video_useScreenContext(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDVideoPlayer);
    LCDVideoPlayer* _0 = (LCDVideoPlayer*)py_touserdata(py_arg(0));
    pd->graphics->video->useScreenContext(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_video_renderFrame(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDVideoPlayer);
    LCDVideoPlayer* _0 = (LCDVideoPlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->graphics->video->renderFrame(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_graphics_video_getError(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDVideoPlayer);
    LCDVideoPlayer* _0 = (LCDVideoPlayer*)py_touserdata(py_arg(0));
    const char** r_type = pd->graphics->video->getError(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(const char**));
    return true;
}
static bool py_graphics_video_getInfo(int argc, py_Ref argv) {
    PY_CHECK_ARGC(6);
    PY_CHECK_ARG_TYPE(0, tp_LCDVideoPlayer);
    LCDVideoPlayer* _0 = (LCDVideoPlayer*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_int);
    int _5 = py_toint(py_arg(5));
    pd->graphics->video->getInfo(_0, _1, _2, &_3, _4, _5);
    py_newnone(py_retval());
    return true;
}
static bool py_system_setPeripheralsEnabled(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_PDPeripherals);
    PDPeripherals* _0 = (PDPeripherals*)py_touserdata(py_arg(0));
    pd->system->setPeripheralsEnabled(*_0);
    py_newnone(py_retval());
    return true;
}
static bool py_system_getAccelerometer(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->system->getAccelerometer(&_0, &_1, &_2);
    py_newnone(py_retval());
    return true;
}
static bool py_system_getButtonState(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDButtons);
    PDButtons* _0 = (PDButtons*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDButtons);
    PDButtons* _1 = (PDButtons*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_PDButtons);
    PDButtons* _2 = (PDButtons*)py_touserdata(py_arg(2));
    pd->system->getButtonState(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_system_setButtonCallback(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_PDButtonCallbackFunction);
    PDButtonCallbackFunction* _0 = (PDButtonCallbackFunction*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    pd->system->setButtonCallback(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_system_getCrankAngle(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    float r_type = pd->system->getCrankAngle();
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_system_getCrankChange(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    float r_type = pd->system->getCrankChange();
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_system_isCrankDocked(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->system->isCrankDocked();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_system_setAutoLockDisabled(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    pd->system->setAutoLockDisabled(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_system_setCrankSoundsDisabled(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    int r_type = pd->system->setCrankSoundsDisabled(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_json_decode(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_struct_json_decoder);
    struct json_decoder* _0 = (json_decoder*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_json_reader);
    json_reader* _1 = (json_reader*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_json_value);
    json_value* _2 = (json_value*)py_touserdata(py_arg(2));
    int r_type = pd->json->decode(_0, *_1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_json_decodeString(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_struct_json_decoder);
    struct json_decoder* _0 = (json_decoder*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_json_value);
    json_value* _2 = (json_value*)py_touserdata(py_arg(2));
    int r_type = pd->json->decodeString(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_json_initEncoder(int argc, py_Ref argv) {
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_json_encoder);
    json_encoder* _0 = (json_encoder*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_writeFunc);
    struct writeFunc* _1 = (struct writeFunc*)py_touserdata(py_arg(1));
    void* _2 = py_touserdata(py_arg(2)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    pd->json->initEncoder(_0, _1, _2, _3);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_addFunction(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_lua_CFunction);
    lua_CFunction* _0 = (lua_CFunction*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_str);
    const char* _2 = py_tostr(py_arg(2));
    int r_type = pd->lua->addFunction(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_lua_registerClass(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_const_lua_reg);
    const lua_reg* _1 = (lua_reg*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_const_lua_val);
    const lua_val* _2 = (lua_val*)py_touserdata(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_int);
    int _3 = py_toint(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_str);
    const char* _4 = py_tostr(py_arg(4));
    int r_type = pd->lua->registerClass(_0, _1, _2, _3, _4);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_lua_start(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->lua->start();
    py_newnone(py_retval());
    return true;
}
static bool py_lua_stop(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->lua->stop();
    py_newnone(py_retval());
    return true;
}
static bool py_lua_getArgType(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    const char* _1 = py_tostr(py_arg(1));
    enum LuaType r_type = pd->lua->getArgType(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(enum LuaType));
    return true;
}
static bool py_lua_getArgCount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->lua->getArgCount();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_lua_argIsNil(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    int r_type = pd->lua->argIsNil(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_lua_getArgBool(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    int r_type = pd->lua->getArgBool(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_lua_getArgFloat(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    float r_type = pd->lua->getArgFloat(_0);
    py_newfloat(py_retval(), r_type);
    return true;
}
static bool py_lua_getArgInt(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    int r_type = pd->lua->getArgInt(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_lua_getArgString(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    const char** r_type = pd->lua->getArgString(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(const char**));
    return true;
}
static bool py_lua_getSprite(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    LCDSprite* r_type = pd->lua->getSprite(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite*));
    return true;
}
static bool py_lua_getArgBytes(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    size_t _1 = py_toint(py_arg(1));
    const char** r_type = pd->lua->getArgBytes(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(const char**));
    return true;
}
static bool py_lua_getBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    LCDBitmap* r_type = pd->lua->getBitmap(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_lua_pushBool(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    pd->lua->pushBool(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushFloat(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    pd->lua->pushFloat(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushInt(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    pd->lua->pushInt(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushNil(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->lua->pushNil();
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushString(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    char _0 = py_tostr(py_arg(0));
    pd->lua->pushString(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushBytes(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    char _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    size_t _1 = py_toint(py_arg(1));
    pd->lua->pushBytes(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushFunction(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_lua_CFunction);
    lua_CFunction* _0 = (lua_CFunction*)py_touserdata(py_arg(0));
    pd->lua->pushFunction(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushBitmap(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDBitmap);
    LCDBitmap* _0 = (LCDBitmap*)py_touserdata(py_arg(0));
    pd->lua->pushBitmap(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushSprite(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->lua->pushSprite(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_pushObject(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    void* _0 = py_touserdata(py_arg(0)); // This is a callback function, this will not work but allows for compling
    PY_CHECK_ARG_TYPE(1, tp_str);
    char _1 = py_tostr(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    LuaUDObject* r_type = pd->lua->pushObject(_0, _1, _2);
    py_newobject(py_retval(), r_type, 0, sizeof(LuaUDObject*));
    return true;
}
static bool py_lua_getArgObject(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_str);
    char _1 = py_tostr(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_LuaUDObject);
    LuaUDObject* _2 = (LuaUDObject*)py_touserdata(py_arg(2));
    void* r_type = pd->lua->getArgObject(_0, _1, _2);
    py_newobject(py_retval(), r_type, 0, sizeof(void*));
    return true;
}
static bool py_lua_retainObject(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LuaUDObject);
    LuaUDObject* _0 = (LuaUDObject*)py_touserdata(py_arg(0));
    LuaUDObject* r_type = pd->lua->retainObject(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LuaUDObject*));
    return true;
}
static bool py_lua_releaseObject(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LuaUDObject);
    LuaUDObject* _0 = (LuaUDObject*)py_touserdata(py_arg(0));
    pd->lua->releaseObject(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_setUserValue(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LuaUDObject);
    LuaUDObject* _0 = (LuaUDObject*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->lua->setUserValue(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_lua_getUserValue(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LuaUDObject);
    LuaUDObject* _0 = (LuaUDObject*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    int r_type = pd->lua->getUserValue(_0, _1);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_lua_callFunction(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_str);
    const char* _0 = py_tostr(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_str);
    const char* _2 = py_tostr(py_arg(2));
    int r_type = pd->lua->callFunction(_0, _1, _2);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sprite_newSprite(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    LCDSprite* r_type = pd->sprite->newSprite();
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite*));
    return true;
}
static bool py_sprite_copy(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    LCDSprite* r_type = pd->sprite->copy(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite*));
    return true;
}
static bool py_sprite_freeSprite(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->sprite->freeSprite(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setBounds(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDRect);
    PDRect* _1 = (PDRect*)py_touserdata(py_arg(1));
    pd->sprite->setBounds(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_moveTo(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sprite->moveTo(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_moveBy(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sprite->moveBy(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getPosition(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float* _1 = py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float* _2 = py_touserdata(py_arg(2));
    pd->sprite->getPosition(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setCenter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sprite->setCenter(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getCenter(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float* _1 = py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float* _2 = py_touserdata(py_arg(2));
    pd->sprite->getCenter(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setImage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmap);
    LCDBitmap* _1 = (LCDBitmap*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_LCDBitmapFlip);
    LCDBitmapFlip* _2 = (LCDBitmapFlip*)py_touserdata(py_arg(2));
    pd->sprite->setImage(_0, _1, *_2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getImage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    LCDBitmap* r_type = pd->sprite->getImage(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmap*));
    return true;
}
static bool py_sprite_setSize(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    pd->sprite->setSize(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setZIndex(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int16_t* _1 = py_toint(py_arg(1));
    pd->sprite->setZIndex(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getZIndex(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    int16_t r_type = pd->sprite->getZIndex(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(int16_t));
    return true;
}
static bool py_sprite_setTag(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint8_t _1 = py_toint(py_arg(1));
    pd->sprite->setTag(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getTag(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    uint8_t r_type = pd->sprite->getTag(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(uint8_t));
    return true;
}
static bool py_sprite_setDrawMode(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmapDrawMode);
    LCDBitmapDrawMode* _1 = (LCDBitmapDrawMode*)py_touserdata(py_arg(1));
    pd->sprite->setDrawMode(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setImageFlip(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmapFlip);
    LCDBitmapFlip* _1 = (LCDBitmapFlip*)py_touserdata(py_arg(1));
    pd->sprite->setImageFlip(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getImageFlip(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    LCDBitmapFlip r_type = pd->sprite->getImageFlip(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDBitmapFlip));
    return true;
}
static bool py_sprite_setStencil(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmap);
    LCDBitmap* _1 = (LCDBitmap*)py_touserdata(py_arg(1));
    pd->sprite->setStencil(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setStencilImage(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDBitmap);
    LCDBitmap* _1 = (LCDBitmap*)py_touserdata(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    pd->sprite->setStencilImage(_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setStencilPattern(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    uint8_t _1 = py_toint(py_arg(1));
    pd->sprite->setStencilPattern(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_clearStencil(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->sprite->clearStencil(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setClipRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDRect);
    LCDRect* _1 = (LCDRect*)py_touserdata(py_arg(1));
    pd->sprite->setClipRect(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_clearClipRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->sprite->clearClipRect(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setClipRectsInRange(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_LCDRect);
    LCDRect* _0 = (LCDRect*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    pd->sprite->setClipRectsInRange(*_0, _1, _2);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_clearClipRectsInRange(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sprite->clearClipRectsInRange(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setUpdatesEnabled(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sprite->setUpdatesEnabled(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_updatesEnabled(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    int r_type = pd->sprite->updatesEnabled(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sprite_setVisible(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sprite->setVisible(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_isVisible(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    int r_type = pd->sprite->isVisible(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sprite_setOpaque(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sprite->setOpaque(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setAlwaysRedraw(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    pd->sprite->setAlwaysRedraw(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_markDirty(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->sprite->markDirty(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_addDirtyRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDRect);
    LCDRect* _0 = (LCDRect*)py_touserdata(py_arg(0));
    pd->sprite->addDirtyRect(*_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setIgnoresDrawOffset(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sprite->setIgnoresDrawOffset(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setUpdateFunction(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDSpriteUpdateFunction);
    LCDSpriteUpdateFunction* _1 = (LCDSpriteUpdateFunction*)py_touserdata(py_arg(1));
    pd->sprite->setUpdateFunction(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setDrawFunction(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDSpriteDrawFunction);
    LCDSpriteDrawFunction* _1 = (LCDSpriteDrawFunction*)py_touserdata(py_arg(1));
    pd->sprite->setDrawFunction(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setUserdata(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    void* _1 = py_touserdata(py_arg(1)); // This is a callback function, this will not work but allows for compling
    pd->sprite->setUserdata(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getUserdata(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    void* r_type = pd->sprite->getUserdata(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(void*));
    return true;
}
static bool py_sprite_addSprite(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->sprite->addSprite(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_removeSprite(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->sprite->removeSprite(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_removeSprites(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sprite->removeSprites(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_removeAllSprites(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->sprite->removeAllSprites();
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_getSpriteCount(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    int r_type = pd->sprite->getSpriteCount();
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sprite_drawSprites(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->sprite->drawSprites();
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_updateAndDrawSprites(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->sprite->updateAndDrawSprites();
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_resetCollisionWorld(int argc, py_Ref argv) {
    PY_CHECK_ARGC(0);

    pd->sprite->resetCollisionWorld();
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setCollisionsEnabled(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    pd->sprite->setCollisionsEnabled(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_collisionsEnabled(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    int r_type = pd->sprite->collisionsEnabled(_0);
    py_newint(py_retval(), r_type);
    return true;
}
static bool py_sprite_setCollideRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_PDRect);
    PDRect* _1 = (PDRect*)py_touserdata(py_arg(1));
    pd->sprite->setCollideRect(_0, *_1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_clearCollideRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    pd->sprite->clearCollideRect(_0);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_setCollisionResponseFunction(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_LCDSpriteCollisionFilterProc);
    LCDSpriteCollisionFilterProc* _1 = (LCDSpriteCollisionFilterProc*)py_touserdata(py_arg(1));
    pd->sprite->setCollisionResponseFunction(_0, _1);
    py_newnone(py_retval());
    return true;
}
static bool py_sprite_checkCollisions(int argc, py_Ref argv) {
    PY_CHECK_ARGC(6);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float* _3 = py_touserdata(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float* _4 = py_touserdata(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_int);
    int _5 = py_toint(py_arg(5));
    SpriteCollisionInfo* r_type = pd->sprite->checkCollisions(_0, _1, _2, _3, _4, _5);
    py_newobject(py_retval(), r_type, 0, sizeof(SpriteCollisionInfo*));
    return true;
}
static bool py_sprite_moveWithCollisions(int argc, py_Ref argv) {
    PY_CHECK_ARGC(6);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float* _3 = py_touserdata(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_float);
    float* _4 = py_touserdata(py_arg(4));
    PY_CHECK_ARG_TYPE(5, tp_int);
    int _5 = py_toint(py_arg(5));
    SpriteCollisionInfo* r_type = pd->sprite->moveWithCollisions(_0, _1, _2, _3, _4, _5);
    py_newobject(py_retval(), r_type, 0, sizeof(SpriteCollisionInfo*));
    return true;
}
static bool py_sprite_querySpritesAtPoint(int argc, py_Ref argv) {
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_int);
    int _2 = py_toint(py_arg(2));
    LCDSprite** r_type = pd->sprite->querySpritesAtPoint(_0, _1, _2);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite**));
    return true;
}
static bool py_sprite_querySpritesInRect(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    LCDSprite** r_type = pd->sprite->querySpritesInRect(_0, _1, _2, _3, _4);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite**));
    return true;
}
static bool py_sprite_querySpritesAlongLine(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    LCDSprite** r_type = pd->sprite->querySpritesAlongLine(_0, _1, _2, _3, _4);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite**));
    return true;
}
static bool py_sprite_querySpriteInfoAlongLine(int argc, py_Ref argv) {
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float _0 = py_tofloat(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_float);
    float _1 = py_tofloat(py_arg(1));
    PY_CHECK_ARG_TYPE(2, tp_float);
    float _2 = py_tofloat(py_arg(2));
    PY_CHECK_ARG_TYPE(3, tp_float);
    float _3 = py_tofloat(py_arg(3));
    PY_CHECK_ARG_TYPE(4, tp_int);
    int _4 = py_toint(py_arg(4));
    SpriteQueryInfo* r_type = pd->sprite->querySpriteInfoAlongLine(_0, _1, _2, _3, _4);
    py_newobject(py_retval(), r_type, 0, sizeof(SpriteQueryInfo*));
    return true;
}
static bool py_sprite_overlappingSprites(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_LCDSprite);
    LCDSprite* _0 = (LCDSprite*)py_touserdata(py_arg(0));
    PY_CHECK_ARG_TYPE(1, tp_int);
    int _1 = py_toint(py_arg(1));
    LCDSprite** r_type = pd->sprite->overlappingSprites(_0, _1);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite**));
    return true;
}
static bool py_sprite_allOverlappingSprites(int argc, py_Ref argv) {
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int _0 = py_toint(py_arg(0));
    LCDSprite** r_type = pd->sprite->allOverlappingSprites(_0);
    py_newobject(py_retval(), r_type, 0, sizeof(LCDSprite**));
    return true;
}

inline void py_add_funcs(py_GlobalRef mod) {
    py_bindfunc(mod, "system_error", &py_system_error);
    py_bindfunc(mod, "system_logToConsole", &py_system_logToConsole);
    py_bindfunc(mod, "system_getCurrentTimeMilliseconds", &py_system_getCurrentTimeMilliseconds);
    py_bindfunc(mod, "system_getSecondsSinceEpoch", &py_system_getSecondsSinceEpoch);
    py_bindfunc(mod, "system_resetElapsedTime", &py_system_resetElapsedTime);
    py_bindfunc(mod, "system_getElapsedTime", &py_system_getElapsedTime);
    py_bindfunc(mod, "system_getTimezoneOffset", &py_system_getTimezoneOffset);
    py_bindfunc(mod, "system_convertEpochToDateTime", &py_system_convertEpochToDateTime);
    py_bindfunc(mod, "system_convertDateTimeToEpoch", &py_system_convertDateTimeToEpoch);
    py_bindfunc(mod, "system_shouldDisplay24HourTime", &py_system_shouldDisplay24HourTime);
    py_bindfunc(mod, "system_getFlipped", &py_system_getFlipped);
    py_bindfunc(mod, "system_getReduceFlashing", &py_system_getReduceFlashing);
    py_bindfunc(mod, "system_formatString", &py_system_formatString);
    py_bindfunc(mod, "system_vaFormatString", &py_system_vaFormatString);
    py_bindfunc(mod, "system_parseString", &py_system_parseString);
    py_bindfunc(mod, "system_setUpdateCallback", &py_system_setUpdateCallback);
    py_bindfunc(mod, "system_setSerialMessageCallback", &py_system_setSerialMessageCallback);
    py_bindfunc(mod, "system_drawFPS", &py_system_drawFPS);
    py_bindfunc(mod, "system_getBatteryPercentage", &py_system_getBatteryPercentage);
    py_bindfunc(mod, "system_getBatteryVoltage", &py_system_getBatteryVoltage);
    py_bindfunc(mod, "sound_getCurrentTime", &py_sound_getCurrentTime);
    py_bindfunc(mod, "sound_getDefaultChannel", &py_sound_getDefaultChannel);
    py_bindfunc(mod, "sound_addChannel", &py_sound_addChannel);
    py_bindfunc(mod, "sound_addSource", &py_sound_addSource);
    py_bindfunc(mod, "sound_removeSource", &py_sound_removeSource);
    py_bindfunc(mod, "sound_removeChannel", &py_sound_removeChannel);
    py_bindfunc(mod, "sound_setMicCallback", &py_sound_setMicCallback);
    py_bindfunc(mod, "sound_setOutputsActive", &py_sound_setOutputsActive);
    py_bindfunc(mod, "sound_channel_newChannel", &py_sound_channel_newChannel);
    py_bindfunc(mod, "sound_channel_freeChannel", &py_sound_channel_freeChannel);
    py_bindfunc(mod, "sound_channel_addSource", &py_sound_channel_addSource);
    py_bindfunc(mod, "sound_channel_removeSource", &py_sound_channel_removeSource);
    py_bindfunc(mod, "sound_channel_addEffect", &py_sound_channel_addEffect);
    py_bindfunc(mod, "sound_channel_removeEffect", &py_sound_channel_removeEffect);
    py_bindfunc(mod, "sound_channel_setVolume", &py_sound_channel_setVolume);
    py_bindfunc(mod, "sound_channel_getVolume", &py_sound_channel_getVolume);
    py_bindfunc(mod, "sound_channel_setVolumeModulator", &py_sound_channel_setVolumeModulator);
    py_bindfunc(mod, "sound_channel_getVolumeModulator", &py_sound_channel_getVolumeModulator);
    py_bindfunc(mod, "sound_channel_setPan", &py_sound_channel_setPan);
    py_bindfunc(mod, "sound_channel_setPanModulator", &py_sound_channel_setPanModulator);
    py_bindfunc(mod, "sound_channel_getPanModulator", &py_sound_channel_getPanModulator);
    py_bindfunc(mod, "sound_channel_addCallbackSource", &py_sound_channel_addCallbackSource);
    py_bindfunc(mod, "sound_channel_getDryLevelSignal", &py_sound_channel_getDryLevelSignal);
    py_bindfunc(mod, "sound_channel_getWetLevelSignal", &py_sound_channel_getWetLevelSignal);
    py_bindfunc(mod, "sound_source_setVolume", &py_sound_source_setVolume);
    py_bindfunc(mod, "sound_source_getVolume", &py_sound_source_getVolume);
    py_bindfunc(mod, "sound_source_isPlaying", &py_sound_source_isPlaying);
    py_bindfunc(mod, "sound_sample_newSampleBuffer", &py_sound_sample_newSampleBuffer);
    py_bindfunc(mod, "sound_sample_loadIntoSample", &py_sound_sample_loadIntoSample);
    py_bindfunc(mod, "sound_sample_load", &py_sound_sample_load);
    py_bindfunc(mod, "sound_sample_getData", &py_sound_sample_getData);
    py_bindfunc(mod, "sound_sample_freeSample", &py_sound_sample_freeSample);
    py_bindfunc(mod, "sound_sample_getLength", &py_sound_sample_getLength);
    py_bindfunc(mod, "sound_fileplayer_newPlayer", &py_sound_fileplayer_newPlayer);
    py_bindfunc(mod, "sound_fileplayer_freePlayer", &py_sound_fileplayer_freePlayer);
    py_bindfunc(mod, "sound_fileplayer_loadIntoPlayer", &py_sound_fileplayer_loadIntoPlayer);
    py_bindfunc(mod, "sound_fileplayer_pause", &py_sound_fileplayer_pause);
    py_bindfunc(mod, "sound_fileplayer_play", &py_sound_fileplayer_play);
    py_bindfunc(mod, "sound_fileplayer_isPlaying", &py_sound_fileplayer_isPlaying);
    py_bindfunc(mod, "sound_fileplayer_setBufferLength", &py_sound_fileplayer_setBufferLength);
    py_bindfunc(mod, "sound_fileplayer_getLength", &py_sound_fileplayer_getLength);
    py_bindfunc(mod, "sound_fileplayer_setFinishCallback", &py_sound_fileplayer_setFinishCallback);
    py_bindfunc(mod, "sound_fileplayer_didUnderrun", &py_sound_fileplayer_didUnderrun);
    py_bindfunc(mod, "sound_fileplayer_setLoopRange", &py_sound_fileplayer_setLoopRange);
    py_bindfunc(mod, "sound_fileplayer_setOffset", &py_sound_fileplayer_setOffset);
    py_bindfunc(mod, "sound_fileplayer_getOffset", &py_sound_fileplayer_getOffset);
    py_bindfunc(mod, "sound_fileplayer_setRate", &py_sound_fileplayer_setRate);
    py_bindfunc(mod, "sound_fileplayer_getRate", &py_sound_fileplayer_getRate);
    py_bindfunc(mod, "sound_fileplayer_setStopOnUnderrun", &py_sound_fileplayer_setStopOnUnderrun);
    py_bindfunc(mod, "sound_fileplayer_setVolume", &py_sound_fileplayer_setVolume);
    py_bindfunc(mod, "sound_fileplayer_getVolume", &py_sound_fileplayer_getVolume);
    py_bindfunc(mod, "sound_fileplayer_stop", &py_sound_fileplayer_stop);
    py_bindfunc(mod, "sound_sampleplayer_getLength", &py_sound_sampleplayer_getLength);
    py_bindfunc(mod, "sound_sampleplayer_isPlaying", &py_sound_sampleplayer_isPlaying);
    py_bindfunc(mod, "sound_sampleplayer_newPlayer", &py_sound_sampleplayer_newPlayer);
    py_bindfunc(mod, "sound_sampleplayer_play", &py_sound_sampleplayer_play);
    py_bindfunc(mod, "sound_sampleplayer_setFinishCallback", &py_sound_sampleplayer_setFinishCallback);
    py_bindfunc(mod, "sound_sampleplayer_setOffset", &py_sound_sampleplayer_setOffset);
    py_bindfunc(mod, "sound_sampleplayer_getOffset", &py_sound_sampleplayer_getOffset);
    py_bindfunc(mod, "sound_sampleplayer_setPlayRange", &py_sound_sampleplayer_setPlayRange);
    py_bindfunc(mod, "sound_sampleplayer_setPaused", &py_sound_sampleplayer_setPaused);
    py_bindfunc(mod, "sound_sampleplayer_setRate", &py_sound_sampleplayer_setRate);
    py_bindfunc(mod, "sound_sampleplayer_getRate", &py_sound_sampleplayer_getRate);
    py_bindfunc(mod, "sound_sampleplayer_setSample", &py_sound_sampleplayer_setSample);
    py_bindfunc(mod, "sound_sampleplayer_setVolume", &py_sound_sampleplayer_setVolume);
    py_bindfunc(mod, "sound_sampleplayer_getVolume", &py_sound_sampleplayer_getVolume);
    py_bindfunc(mod, "sound_sampleplayer_stop", &py_sound_sampleplayer_stop);
    py_bindfunc(mod, "sound_sampleplayer_freePlayer", &py_sound_sampleplayer_freePlayer);
    py_bindfunc(mod, "sound_synth_newSynth", &py_sound_synth_newSynth);
    py_bindfunc(mod, "sound_synth_freeSynth", &py_sound_synth_freeSynth);
    py_bindfunc(mod, "sound_synth_copy", &py_sound_synth_copy);
    py_bindfunc(mod, "sound_synth_setWaveform", &py_sound_synth_setWaveform);
    py_bindfunc(mod, "sound_synth_setGenerator", &py_sound_synth_setGenerator);
    py_bindfunc(mod, "sound_synth_setSample", &py_sound_synth_setSample);
    py_bindfunc(mod, "sound_synth_setWavetable", &py_sound_synth_setWavetable);
    py_bindfunc(mod, "sound_synth_setAttackTime", &py_sound_synth_setAttackTime);
    py_bindfunc(mod, "sound_synth_setDecayTime", &py_sound_synth_setDecayTime);
    py_bindfunc(mod, "sound_synth_setSustainLevel", &py_sound_synth_setSustainLevel);
    py_bindfunc(mod, "sound_synth_setReleaseTime", &py_sound_synth_setReleaseTime);
    py_bindfunc(mod, "sound_synth_clearEnvelope", &py_sound_synth_clearEnvelope);
    py_bindfunc(mod, "sound_synth_getEnvelope", &py_sound_synth_getEnvelope);
    py_bindfunc(mod, "sound_synth_setTranspose", &py_sound_synth_setTranspose);
    py_bindfunc(mod, "sound_synth_setFrequencyModulator", &py_sound_synth_setFrequencyModulator);
    py_bindfunc(mod, "sound_synth_getFrequencyModulator", &py_sound_synth_getFrequencyModulator);
    py_bindfunc(mod, "sound_synth_setAmplitudeModulator", &py_sound_synth_setAmplitudeModulator);
    py_bindfunc(mod, "sound_synth_getAmplitudeModulator", &py_sound_synth_getAmplitudeModulator);
    py_bindfunc(mod, "sound_synth_playNote", &py_sound_synth_playNote);
    py_bindfunc(mod, "sound_synth_playMIDINote", &py_sound_synth_playMIDINote);
    py_bindfunc(mod, "sound_synth_noteOff", &py_sound_synth_noteOff);
    py_bindfunc(mod, "sound_synth_setVolume", &py_sound_synth_setVolume);
    py_bindfunc(mod, "sound_synth_isPlaying", &py_sound_synth_isPlaying);
    py_bindfunc(mod, "sound_synth_getParameterCount", &py_sound_synth_getParameterCount);
    py_bindfunc(mod, "sound_synth_setParameter", &py_sound_synth_setParameter);
    py_bindfunc(mod, "sound_synth_setParameterModulator", &py_sound_synth_setParameterModulator);
    py_bindfunc(mod, "sound_synth_getParameterModulator", &py_sound_synth_getParameterModulator);
    py_bindfunc(mod, "sound_instrument_newInstrument", &py_sound_instrument_newInstrument);
    py_bindfunc(mod, "sound_instrument_freeInstrument", &py_sound_instrument_freeInstrument);
    py_bindfunc(mod, "sound_instrument_addVoice", &py_sound_instrument_addVoice);
    py_bindfunc(mod, "sound_instrument_playNote", &py_sound_instrument_playNote);
    py_bindfunc(mod, "sound_instrument_playMIDINote", &py_sound_instrument_playMIDINote);
    py_bindfunc(mod, "sound_instrument_noteOff", &py_sound_instrument_noteOff);
    py_bindfunc(mod, "sound_instrument_setPitchBend", &py_sound_instrument_setPitchBend);
    py_bindfunc(mod, "sound_instrument_setPitchBendRange", &py_sound_instrument_setPitchBendRange);
    py_bindfunc(mod, "sound_instrument_setTranspose", &py_sound_instrument_setTranspose);
    py_bindfunc(mod, "sound_instrument_allNotesOff", &py_sound_instrument_allNotesOff);
    py_bindfunc(mod, "sound_instrument_setVolume", &py_sound_instrument_setVolume);
    py_bindfunc(mod, "sound_instrument_getVolume", &py_sound_instrument_getVolume);
    py_bindfunc(mod, "sound_instrument_activeVoiceCount", &py_sound_instrument_activeVoiceCount);
    py_bindfunc(mod, "sound_signal_newSignal", &py_sound_signal_newSignal);
    py_bindfunc(mod, "sound_signal_freeSignal", &py_sound_signal_freeSignal);
    py_bindfunc(mod, "sound_signal_getValue", &py_sound_signal_getValue);
    py_bindfunc(mod, "sound_signal_setValueOffset", &py_sound_signal_setValueOffset);
    py_bindfunc(mod, "sound_signal_setValueScale", &py_sound_signal_setValueScale);
    py_bindfunc(mod, "sound_signal_newSignalForValue", &py_sound_signal_newSignalForValue);
    py_bindfunc(mod, "sound_lfo_newLFO", &py_sound_lfo_newLFO);
    py_bindfunc(mod, "sound_lfo_freeLFO", &py_sound_lfo_freeLFO);
    py_bindfunc(mod, "sound_lfo_setType", &py_sound_lfo_setType);
    py_bindfunc(mod, "sound_lfo_setRate", &py_sound_lfo_setRate);
    py_bindfunc(mod, "sound_lfo_setPhase", &py_sound_lfo_setPhase);
    py_bindfunc(mod, "sound_lfo_setStartPhase", &py_sound_lfo_setStartPhase);
    py_bindfunc(mod, "sound_lfo_setCenter", &py_sound_lfo_setCenter);
    py_bindfunc(mod, "sound_lfo_setDepth", &py_sound_lfo_setDepth);
    py_bindfunc(mod, "sound_lfo_setArpeggiation", &py_sound_lfo_setArpeggiation);
    py_bindfunc(mod, "sound_lfo_setDelay", &py_sound_lfo_setDelay);
    py_bindfunc(mod, "sound_lfo_setRetrigger", &py_sound_lfo_setRetrigger);
    py_bindfunc(mod, "sound_lfo_getValue", &py_sound_lfo_getValue);
    py_bindfunc(mod, "sound_lfo_setGlobal", &py_sound_lfo_setGlobal);
    py_bindfunc(mod, "sound_envelope_newEnvelope", &py_sound_envelope_newEnvelope);
    py_bindfunc(mod, "sound_envelope_freeEnvelope", &py_sound_envelope_freeEnvelope);
    py_bindfunc(mod, "sound_envelope_setAttack", &py_sound_envelope_setAttack);
    py_bindfunc(mod, "sound_envelope_setDecay", &py_sound_envelope_setDecay);
    py_bindfunc(mod, "sound_envelope_setSustain", &py_sound_envelope_setSustain);
    py_bindfunc(mod, "sound_envelope_setRelease", &py_sound_envelope_setRelease);
    py_bindfunc(mod, "sound_envelope_setCurvature", &py_sound_envelope_setCurvature);
    py_bindfunc(mod, "sound_envelope_setVelocitySensitivity", &py_sound_envelope_setVelocitySensitivity);
    py_bindfunc(mod, "sound_envelope_setRateScaling", &py_sound_envelope_setRateScaling);
    py_bindfunc(mod, "sound_envelope_setLegato", &py_sound_envelope_setLegato);
    py_bindfunc(mod, "sound_envelope_setRetrigger", &py_sound_envelope_setRetrigger);
    py_bindfunc(mod, "sound_envelope_getValue", &py_sound_envelope_getValue);
    py_bindfunc(mod, "sound_effect_newEffect", &py_sound_effect_newEffect);
    py_bindfunc(mod, "sound_effect_freeEffect", &py_sound_effect_freeEffect);
    py_bindfunc(mod, "sound_effect_setMix", &py_sound_effect_setMix);
    py_bindfunc(mod, "sound_effect_setMixModulator", &py_sound_effect_setMixModulator);
    py_bindfunc(mod, "sound_effect_getMixModulator", &py_sound_effect_getMixModulator);
    py_bindfunc(mod, "sound_effect_setUserdata", &py_sound_effect_setUserdata);
    py_bindfunc(mod, "sound_effect_getUserdata", &py_sound_effect_getUserdata);
    py_bindfunc(mod, "sound_effect_twopolefilter_newFilter", &py_sound_effect_twopolefilter_newFilter);
    py_bindfunc(mod, "sound_effect_twopolefilter_freeFilter", &py_sound_effect_twopolefilter_freeFilter);
    py_bindfunc(mod, "sound_effect_twopolefilter_setType", &py_sound_effect_twopolefilter_setType);
    py_bindfunc(mod, "sound_effect_twopolefilter_setFrequency", &py_sound_effect_twopolefilter_setFrequency);
    py_bindfunc(mod, "sound_effect_twopolefilter_setFrequencyModulator", &py_sound_effect_twopolefilter_setFrequencyModulator);
    py_bindfunc(mod, "sound_effect_twopolefilter_getFrequencyModulator", &py_sound_effect_twopolefilter_getFrequencyModulator);
    py_bindfunc(mod, "sound_effect_twopolefilter_setGain", &py_sound_effect_twopolefilter_setGain);
    py_bindfunc(mod, "sound_effect_twopolefilter_setResonance", &py_sound_effect_twopolefilter_setResonance);
    py_bindfunc(mod, "sound_effect_twopolefilter_setResonanceModulator", &py_sound_effect_twopolefilter_setResonanceModulator);
    py_bindfunc(mod, "sound_effect_twopolefilter_getResonanceModulator", &py_sound_effect_twopolefilter_getResonanceModulator);
    py_bindfunc(mod, "sound_effect_onepolefilter_newFilter", &py_sound_effect_onepolefilter_newFilter);
    py_bindfunc(mod, "sound_effect_onepolefilter_freeFilter", &py_sound_effect_onepolefilter_freeFilter);
    py_bindfunc(mod, "sound_effect_onepolefilter_setParameter", &py_sound_effect_onepolefilter_setParameter);
    py_bindfunc(mod, "sound_effect_onepolefilter_setParameterModulator", &py_sound_effect_onepolefilter_setParameterModulator);
    py_bindfunc(mod, "sound_effect_onepolefilter_getParameterModulator", &py_sound_effect_onepolefilter_getParameterModulator);
    py_bindfunc(mod, "sound_effect_bitcrusher_newBitCrusher", &py_sound_effect_bitcrusher_newBitCrusher);
    py_bindfunc(mod, "sound_effect_bitcrusher_freeBitCrusher", &py_sound_effect_bitcrusher_freeBitCrusher);
    py_bindfunc(mod, "sound_effect_bitcrusher_setAmount", &py_sound_effect_bitcrusher_setAmount);
    py_bindfunc(mod, "sound_effect_bitcrusher_setAmountModulator", &py_sound_effect_bitcrusher_setAmountModulator);
    py_bindfunc(mod, "sound_effect_bitcrusher_getAmountModulator", &py_sound_effect_bitcrusher_getAmountModulator);
    py_bindfunc(mod, "sound_effect_bitcrusher_setUndersampling", &py_sound_effect_bitcrusher_setUndersampling);
    py_bindfunc(mod, "sound_effect_bitcrusher_setUndersampleModulator", &py_sound_effect_bitcrusher_setUndersampleModulator);
    py_bindfunc(mod, "sound_effect_bitcrusher_getUndersampleModulator", &py_sound_effect_bitcrusher_getUndersampleModulator);
    py_bindfunc(mod, "sound_effect_ringmodulator_newRingmod", &py_sound_effect_ringmodulator_newRingmod);
    py_bindfunc(mod, "sound_effect_ringmodulator_setFrequency", &py_sound_effect_ringmodulator_setFrequency);
    py_bindfunc(mod, "sound_effect_ringmodulator_setFrequencyModulator", &py_sound_effect_ringmodulator_setFrequencyModulator);
    py_bindfunc(mod, "sound_effect_ringmodulator_getFrequencyModulator", &py_sound_effect_ringmodulator_getFrequencyModulator);
    py_bindfunc(mod, "sound_effect_overdrive_newOverdrive", &py_sound_effect_overdrive_newOverdrive);
    py_bindfunc(mod, "sound_effect_overdrive_freeOverdrive", &py_sound_effect_overdrive_freeOverdrive);
    py_bindfunc(mod, "sound_effect_overdrive_setGain", &py_sound_effect_overdrive_setGain);
    py_bindfunc(mod, "sound_effect_overdrive_setLimit", &py_sound_effect_overdrive_setLimit);
    py_bindfunc(mod, "sound_effect_overdrive_setLimitModulator", &py_sound_effect_overdrive_setLimitModulator);
    py_bindfunc(mod, "sound_effect_overdrive_getLimitModulator", &py_sound_effect_overdrive_getLimitModulator);
    py_bindfunc(mod, "sound_effect_overdrive_setOffset", &py_sound_effect_overdrive_setOffset);
    py_bindfunc(mod, "sound_effect_overdrive_setOffsetModulator", &py_sound_effect_overdrive_setOffsetModulator);
    py_bindfunc(mod, "sound_effect_overdrive_getOffsetModulator", &py_sound_effect_overdrive_getOffsetModulator);
    py_bindfunc(mod, "sound_effect_delayline_newDelayLine", &py_sound_effect_delayline_newDelayLine);
    py_bindfunc(mod, "sound_effect_delayline_freeDelayLine", &py_sound_effect_delayline_freeDelayLine);
    py_bindfunc(mod, "sound_effect_delayline_setLength", &py_sound_effect_delayline_setLength);
    py_bindfunc(mod, "sound_effect_delayline_setFeedback", &py_sound_effect_delayline_setFeedback);
    py_bindfunc(mod, "sound_effect_delayline_addTap", &py_sound_effect_delayline_addTap);
    py_bindfunc(mod, "sound_effect_delayline_freeTap", &py_sound_effect_delayline_freeTap);
    py_bindfunc(mod, "sound_effect_delayline_setTapDelay", &py_sound_effect_delayline_setTapDelay);
    py_bindfunc(mod, "sound_effect_delayline_setTapDelayModulator", &py_sound_effect_delayline_setTapDelayModulator);
    py_bindfunc(mod, "sound_effect_delayline_getTapDelayModulator", &py_sound_effect_delayline_getTapDelayModulator);
    py_bindfunc(mod, "sound_effect_delayline_setTapChannelsFlipped", &py_sound_effect_delayline_setTapChannelsFlipped);
    py_bindfunc(mod, "sound_sequence_newSequence", &py_sound_sequence_newSequence);
    py_bindfunc(mod, "sound_sequence_freeSequence", &py_sound_sequence_freeSequence);
    py_bindfunc(mod, "sound_sequence_loadMIDIFile", &py_sound_sequence_loadMIDIFile);
    py_bindfunc(mod, "sound_sequence_play", &py_sound_sequence_play);
    py_bindfunc(mod, "sound_sequence_stop", &py_sound_sequence_stop);
    py_bindfunc(mod, "sound_sequence_isPlaying", &py_sound_sequence_isPlaying);
    py_bindfunc(mod, "sound_sequence_getTime", &py_sound_sequence_getTime);
    py_bindfunc(mod, "sound_sequence_setTime", &py_sound_sequence_setTime);
    py_bindfunc(mod, "sound_sequence_setLoops", &py_sound_sequence_setLoops);
    py_bindfunc(mod, "sound_sequence_getTempo", &py_sound_sequence_getTempo);
    py_bindfunc(mod, "sound_sequence_setTempo", &py_sound_sequence_setTempo);
    py_bindfunc(mod, "sound_sequence_getLength", &py_sound_sequence_getLength);
    py_bindfunc(mod, "sound_sequence_getTrackCount", &py_sound_sequence_getTrackCount);
    py_bindfunc(mod, "sound_sequence_addTrack", &py_sound_sequence_addTrack);
    py_bindfunc(mod, "sound_sequence_getTrackAtIndex", &py_sound_sequence_getTrackAtIndex);
    py_bindfunc(mod, "sound_sequence_setTrackAtIndex", &py_sound_sequence_setTrackAtIndex);
    py_bindfunc(mod, "sound_sequence_allNotesOff", &py_sound_sequence_allNotesOff);
    py_bindfunc(mod, "sound_sequence_getCurrentStep", &py_sound_sequence_getCurrentStep);
    py_bindfunc(mod, "sound_sequence_setCurrentStep", &py_sound_sequence_setCurrentStep);
    py_bindfunc(mod, "sound_controlsignal_newSignal", &py_sound_controlsignal_newSignal);
    py_bindfunc(mod, "sound_controlsignal_freeSignal", &py_sound_controlsignal_freeSignal);
    py_bindfunc(mod, "sound_controlsignal_clearEvents", &py_sound_controlsignal_clearEvents);
    py_bindfunc(mod, "sound_controlsignal_addEvent", &py_sound_controlsignal_addEvent);
    py_bindfunc(mod, "sound_controlsignal_removeEvent", &py_sound_controlsignal_removeEvent);
    py_bindfunc(mod, "sound_controlsignal_getMIDIControllerNumber", &py_sound_controlsignal_getMIDIControllerNumber);
    py_bindfunc(mod, "sound_track_newTrack", &py_sound_track_newTrack);
    py_bindfunc(mod, "sound_track_freeTrack", &py_sound_track_freeTrack);
    py_bindfunc(mod, "sound_track_setInstrument", &py_sound_track_setInstrument);
    py_bindfunc(mod, "sound_track_getInstrument", &py_sound_track_getInstrument);
    py_bindfunc(mod, "sound_track_addNoteEvent", &py_sound_track_addNoteEvent);
    py_bindfunc(mod, "sound_track_removeNoteEvent", &py_sound_track_removeNoteEvent);
    py_bindfunc(mod, "sound_track_clearNotes", &py_sound_track_clearNotes);
    py_bindfunc(mod, "sound_track_getLength", &py_sound_track_getLength);
    py_bindfunc(mod, "sound_track_getIndexForStep", &py_sound_track_getIndexForStep);
    py_bindfunc(mod, "sound_track_getNoteAtIndex", &py_sound_track_getNoteAtIndex);
    py_bindfunc(mod, "sound_track_getControlSignalCount", &py_sound_track_getControlSignalCount);
    py_bindfunc(mod, "sound_track_getControlSignal", &py_sound_track_getControlSignal);
    py_bindfunc(mod, "sound_track_getSignalForController", &py_sound_track_getSignalForController);
    py_bindfunc(mod, "sound_track_clearControlEvents", &py_sound_track_clearControlEvents);
    py_bindfunc(mod, "sound_track_activeVoiceCount", &py_sound_track_activeVoiceCount);
    py_bindfunc(mod, "sound_track_getPolyphony", &py_sound_track_getPolyphony);
    py_bindfunc(mod, "sound_track_setMuted", &py_sound_track_setMuted);
    py_bindfunc(mod, "display_getHeight", &py_display_getHeight);
    py_bindfunc(mod, "display_getWidth", &py_display_getWidth);
    py_bindfunc(mod, "display_setInverted", &py_display_setInverted);
    py_bindfunc(mod, "display_setMosaic", &py_display_setMosaic);
    py_bindfunc(mod, "display_setFlipped", &py_display_setFlipped);
    py_bindfunc(mod, "display_setRefreshRate", &py_display_setRefreshRate);
    py_bindfunc(mod, "display_setScale", &py_display_setScale);
    py_bindfunc(mod, "display_setOffset", &py_display_setOffset);
    py_bindfunc(mod, "file_geterr", &py_file_geterr);
    py_bindfunc(mod, "file_unlink", &py_file_unlink);
    py_bindfunc(mod, "file_mkdir", &py_file_mkdir);
    py_bindfunc(mod, "file_rename", &py_file_rename);
    py_bindfunc(mod, "file_stat", &py_file_stat);
    py_bindfunc(mod, "file_open", &py_file_open);
    py_bindfunc(mod, "file_close", &py_file_close);
    py_bindfunc(mod, "file_flush", &py_file_flush);
    py_bindfunc(mod, "file_read", &py_file_read);
    py_bindfunc(mod, "file_seek", &py_file_seek);
    py_bindfunc(mod, "file_tell", &py_file_tell);
    py_bindfunc(mod, "file_write", &py_file_write);
    py_bindfunc(mod, "graphics_pushContext", &py_graphics_pushContext);
    py_bindfunc(mod, "graphics_popContext", &py_graphics_popContext);
    py_bindfunc(mod, "graphics_setStencil", &py_graphics_setStencil);
    py_bindfunc(mod, "graphics_setStencilImage", &py_graphics_setStencilImage);
    py_bindfunc(mod, "graphics_setDrawMode", &py_graphics_setDrawMode);
    py_bindfunc(mod, "graphics_setClipRect", &py_graphics_setClipRect);
    py_bindfunc(mod, "graphics_setScreenClipRect", &py_graphics_setScreenClipRect);
    py_bindfunc(mod, "graphics_clearClipRect", &py_graphics_clearClipRect);
    py_bindfunc(mod, "graphics_setLineCapStyle", &py_graphics_setLineCapStyle);
    py_bindfunc(mod, "graphics_setFont", &py_graphics_setFont);
    py_bindfunc(mod, "graphics_setTextTracking", &py_graphics_setTextTracking);
    py_bindfunc(mod, "graphics_getTextTracking", &py_graphics_getTextTracking);
    py_bindfunc(mod, "graphics_setTextLeading", &py_graphics_setTextLeading);
    py_bindfunc(mod, "graphics_clearBitmap", &py_graphics_clearBitmap);
    py_bindfunc(mod, "graphics_copyBitmap", &py_graphics_copyBitmap);
    py_bindfunc(mod, "graphics_checkMaskCollision", &py_graphics_checkMaskCollision);
    py_bindfunc(mod, "graphics_drawBitmap", &py_graphics_drawBitmap);
    py_bindfunc(mod, "graphics_drawScaledBitmap", &py_graphics_drawScaledBitmap);
    py_bindfunc(mod, "graphics_drawRotatedBitmap", &py_graphics_drawRotatedBitmap);
    py_bindfunc(mod, "graphics_freeBitmap", &py_graphics_freeBitmap);
    py_bindfunc(mod, "graphics_getBitmapData", &py_graphics_getBitmapData);
    py_bindfunc(mod, "graphics_getBitmapPixel", &py_graphics_getBitmapPixel);
    py_bindfunc(mod, "graphics_loadBitmap", &py_graphics_loadBitmap);
    py_bindfunc(mod, "graphics_loadIntoBitmap", &py_graphics_loadIntoBitmap);
    py_bindfunc(mod, "graphics_newBitmap", &py_graphics_newBitmap);
    py_bindfunc(mod, "graphics_tileBitmap", &py_graphics_tileBitmap);
    py_bindfunc(mod, "graphics_rotatedBitmap", &py_graphics_rotatedBitmap);
    py_bindfunc(mod, "graphics_setBitmapMask", &py_graphics_setBitmapMask);
    py_bindfunc(mod, "graphics_getBitmapMask", &py_graphics_getBitmapMask);
    py_bindfunc(mod, "graphics_getTableBitmap", &py_graphics_getTableBitmap);
    py_bindfunc(mod, "graphics_loadBitmapTable", &py_graphics_loadBitmapTable);
    py_bindfunc(mod, "graphics_loadIntoBitmapTable", &py_graphics_loadIntoBitmapTable);
    py_bindfunc(mod, "graphics_newBitmapTable", &py_graphics_newBitmapTable);
    py_bindfunc(mod, "graphics_freeBitmapTable", &py_graphics_freeBitmapTable);
    py_bindfunc(mod, "graphics_getBitmapTableInfo", &py_graphics_getBitmapTableInfo);
    py_bindfunc(mod, "graphics_drawText", &py_graphics_drawText);
    py_bindfunc(mod, "graphics_getFontHeight", &py_graphics_getFontHeight);
    py_bindfunc(mod, "graphics_getFontPage", &py_graphics_getFontPage);
    py_bindfunc(mod, "graphics_getPageGlyph", &py_graphics_getPageGlyph);
    py_bindfunc(mod, "graphics_getGlyphKerning", &py_graphics_getGlyphKerning);
    py_bindfunc(mod, "graphics_getTextWidth", &py_graphics_getTextWidth);
    py_bindfunc(mod, "graphics_loadFont", &py_graphics_loadFont);
    py_bindfunc(mod, "graphics_makeFontFromData", &py_graphics_makeFontFromData);
    py_bindfunc(mod, "graphics_drawEllipse", &py_graphics_drawEllipse);
    py_bindfunc(mod, "graphics_fillEllipse", &py_graphics_fillEllipse);
    py_bindfunc(mod, "graphics_drawLine", &py_graphics_drawLine);
    py_bindfunc(mod, "graphics_drawRect", &py_graphics_drawRect);
    py_bindfunc(mod, "graphics_fillRect", &py_graphics_fillRect);
    py_bindfunc(mod, "graphics_fillTriangle", &py_graphics_fillTriangle);
    py_bindfunc(mod, "graphics_fillPolygon", &py_graphics_fillPolygon);
    py_bindfunc(mod, "graphics_clear", &py_graphics_clear);
    py_bindfunc(mod, "graphics_display", &py_graphics_display);
    py_bindfunc(mod, "graphics_getDebugBitmap", &py_graphics_getDebugBitmap);
    py_bindfunc(mod, "graphics_getDisplayFrame", &py_graphics_getDisplayFrame);
    py_bindfunc(mod, "graphics_getDisplayBufferBitmap", &py_graphics_getDisplayBufferBitmap);
    py_bindfunc(mod, "graphics_getFrame", &py_graphics_getFrame);
    py_bindfunc(mod, "graphics_copyFrameBufferBitmap", &py_graphics_copyFrameBufferBitmap);
    py_bindfunc(mod, "system_getLanguage", &py_system_getLanguage);
    py_bindfunc(mod, "graphics_markUpdatedRows", &py_graphics_markUpdatedRows);
    py_bindfunc(mod, "graphics_setDrawOffset", &py_graphics_setDrawOffset);
    py_bindfunc(mod, "graphics_setColorToPattern", &py_graphics_setColorToPattern);
    py_bindfunc(mod, "graphics_setPixel", &py_graphics_setPixel);
    py_bindfunc(mod, "graphics_video_loadVideo", &py_graphics_video_loadVideo);
    py_bindfunc(mod, "graphics_video_freePlayer", &py_graphics_video_freePlayer);
    py_bindfunc(mod, "graphics_video_setContext", &py_graphics_video_setContext);
    py_bindfunc(mod, "graphics_video_getContext", &py_graphics_video_getContext);
    py_bindfunc(mod, "graphics_video_useScreenContext", &py_graphics_video_useScreenContext);
    py_bindfunc(mod, "graphics_video_renderFrame", &py_graphics_video_renderFrame);
    py_bindfunc(mod, "graphics_video_getError", &py_graphics_video_getError);
    py_bindfunc(mod, "graphics_video_getInfo", &py_graphics_video_getInfo);
    py_bindfunc(mod, "system_setPeripheralsEnabled", &py_system_setPeripheralsEnabled);
    py_bindfunc(mod, "system_getAccelerometer", &py_system_getAccelerometer);
    py_bindfunc(mod, "system_getButtonState", &py_system_getButtonState);
    py_bindfunc(mod, "system_setButtonCallback", &py_system_setButtonCallback);
    py_bindfunc(mod, "system_getCrankAngle", &py_system_getCrankAngle);
    py_bindfunc(mod, "system_getCrankChange", &py_system_getCrankChange);
    py_bindfunc(mod, "system_isCrankDocked", &py_system_isCrankDocked);
    py_bindfunc(mod, "system_setAutoLockDisabled", &py_system_setAutoLockDisabled);
    py_bindfunc(mod, "system_setCrankSoundsDisabled", &py_system_setCrankSoundsDisabled);
    py_bindfunc(mod, "json_decode", &py_json_decode);
    py_bindfunc(mod, "json_decodeString", &py_json_decodeString);
    py_bindfunc(mod, "json_initEncoder", &py_json_initEncoder);
    py_bindfunc(mod, "lua_addFunction", &py_lua_addFunction);
    py_bindfunc(mod, "lua_registerClass", &py_lua_registerClass);
    py_bindfunc(mod, "lua_start", &py_lua_start);
    py_bindfunc(mod, "lua_stop", &py_lua_stop);
    py_bindfunc(mod, "lua_getArgType", &py_lua_getArgType);
    py_bindfunc(mod, "lua_getArgCount", &py_lua_getArgCount);
    py_bindfunc(mod, "lua_argIsNil", &py_lua_argIsNil);
    py_bindfunc(mod, "lua_getArgBool", &py_lua_getArgBool);
    py_bindfunc(mod, "lua_getArgFloat", &py_lua_getArgFloat);
    py_bindfunc(mod, "lua_getArgInt", &py_lua_getArgInt);
    py_bindfunc(mod, "lua_getArgString", &py_lua_getArgString);
    py_bindfunc(mod, "lua_getSprite", &py_lua_getSprite);
    py_bindfunc(mod, "lua_getArgBytes", &py_lua_getArgBytes);
    py_bindfunc(mod, "lua_getBitmap", &py_lua_getBitmap);
    py_bindfunc(mod, "lua_pushBool", &py_lua_pushBool);
    py_bindfunc(mod, "lua_pushFloat", &py_lua_pushFloat);
    py_bindfunc(mod, "lua_pushInt", &py_lua_pushInt);
    py_bindfunc(mod, "lua_pushNil", &py_lua_pushNil);
    py_bindfunc(mod, "lua_pushString", &py_lua_pushString);
    py_bindfunc(mod, "lua_pushBytes", &py_lua_pushBytes);
    py_bindfunc(mod, "lua_pushFunction", &py_lua_pushFunction);
    py_bindfunc(mod, "lua_pushBitmap", &py_lua_pushBitmap);
    py_bindfunc(mod, "lua_pushSprite", &py_lua_pushSprite);
    py_bindfunc(mod, "lua_pushObject", &py_lua_pushObject);
    py_bindfunc(mod, "lua_getArgObject", &py_lua_getArgObject);
    py_bindfunc(mod, "lua_retainObject", &py_lua_retainObject);
    py_bindfunc(mod, "lua_releaseObject", &py_lua_releaseObject);
    py_bindfunc(mod, "lua_setUserValue", &py_lua_setUserValue);
    py_bindfunc(mod, "lua_getUserValue", &py_lua_getUserValue);
    py_bindfunc(mod, "lua_callFunction", &py_lua_callFunction);
    py_bindfunc(mod, "sprite_newSprite", &py_sprite_newSprite);
    py_bindfunc(mod, "sprite_copy", &py_sprite_copy);
    py_bindfunc(mod, "sprite_freeSprite", &py_sprite_freeSprite);
    py_bindfunc(mod, "sprite_setBounds", &py_sprite_setBounds);
    py_bindfunc(mod, "sprite_moveTo", &py_sprite_moveTo);
    py_bindfunc(mod, "sprite_moveBy", &py_sprite_moveBy);
    py_bindfunc(mod, "sprite_getPosition", &py_sprite_getPosition);
    py_bindfunc(mod, "sprite_setCenter", &py_sprite_setCenter);
    py_bindfunc(mod, "sprite_getCenter", &py_sprite_getCenter);
    py_bindfunc(mod, "sprite_setImage", &py_sprite_setImage);
    py_bindfunc(mod, "sprite_getImage", &py_sprite_getImage);
    py_bindfunc(mod, "sprite_setSize", &py_sprite_setSize);
    py_bindfunc(mod, "sprite_setZIndex", &py_sprite_setZIndex);
    py_bindfunc(mod, "sprite_getZIndex", &py_sprite_getZIndex);
    py_bindfunc(mod, "sprite_setTag", &py_sprite_setTag);
    py_bindfunc(mod, "sprite_getTag", &py_sprite_getTag);
    py_bindfunc(mod, "sprite_setDrawMode", &py_sprite_setDrawMode);
    py_bindfunc(mod, "sprite_setImageFlip", &py_sprite_setImageFlip);
    py_bindfunc(mod, "sprite_getImageFlip", &py_sprite_getImageFlip);
    py_bindfunc(mod, "sprite_setStencil", &py_sprite_setStencil);
    py_bindfunc(mod, "sprite_setStencilImage", &py_sprite_setStencilImage);
    py_bindfunc(mod, "sprite_setStencilPattern", &py_sprite_setStencilPattern);
    py_bindfunc(mod, "sprite_clearStencil", &py_sprite_clearStencil);
    py_bindfunc(mod, "sprite_setClipRect", &py_sprite_setClipRect);
    py_bindfunc(mod, "sprite_clearClipRect", &py_sprite_clearClipRect);
    py_bindfunc(mod, "sprite_setClipRectsInRange", &py_sprite_setClipRectsInRange);
    py_bindfunc(mod, "sprite_clearClipRectsInRange", &py_sprite_clearClipRectsInRange);
    py_bindfunc(mod, "sprite_setUpdatesEnabled", &py_sprite_setUpdatesEnabled);
    py_bindfunc(mod, "sprite_updatesEnabled", &py_sprite_updatesEnabled);
    py_bindfunc(mod, "sprite_setVisible", &py_sprite_setVisible);
    py_bindfunc(mod, "sprite_isVisible", &py_sprite_isVisible);
    py_bindfunc(mod, "sprite_setOpaque", &py_sprite_setOpaque);
    py_bindfunc(mod, "sprite_setAlwaysRedraw", &py_sprite_setAlwaysRedraw);
    py_bindfunc(mod, "sprite_markDirty", &py_sprite_markDirty);
    py_bindfunc(mod, "sprite_addDirtyRect", &py_sprite_addDirtyRect);
    py_bindfunc(mod, "sprite_setIgnoresDrawOffset", &py_sprite_setIgnoresDrawOffset);
    py_bindfunc(mod, "sprite_setUpdateFunction", &py_sprite_setUpdateFunction);
    py_bindfunc(mod, "sprite_setDrawFunction", &py_sprite_setDrawFunction);
    py_bindfunc(mod, "sprite_setUserdata", &py_sprite_setUserdata);
    py_bindfunc(mod, "sprite_getUserdata", &py_sprite_getUserdata);
    py_bindfunc(mod, "sprite_addSprite", &py_sprite_addSprite);
    py_bindfunc(mod, "sprite_removeSprite", &py_sprite_removeSprite);
    py_bindfunc(mod, "sprite_removeSprites", &py_sprite_removeSprites);
    py_bindfunc(mod, "sprite_removeAllSprites", &py_sprite_removeAllSprites);
    py_bindfunc(mod, "sprite_getSpriteCount", &py_sprite_getSpriteCount);
    py_bindfunc(mod, "sprite_drawSprites", &py_sprite_drawSprites);
    py_bindfunc(mod, "sprite_updateAndDrawSprites", &py_sprite_updateAndDrawSprites);
    py_bindfunc(mod, "sprite_resetCollisionWorld", &py_sprite_resetCollisionWorld);
    py_bindfunc(mod, "sprite_setCollisionsEnabled", &py_sprite_setCollisionsEnabled);
    py_bindfunc(mod, "sprite_collisionsEnabled", &py_sprite_collisionsEnabled);
    py_bindfunc(mod, "sprite_setCollideRect", &py_sprite_setCollideRect);
    py_bindfunc(mod, "sprite_clearCollideRect", &py_sprite_clearCollideRect);
    py_bindfunc(mod, "sprite_setCollisionResponseFunction", &py_sprite_setCollisionResponseFunction);
    py_bindfunc(mod, "sprite_checkCollisions", &py_sprite_checkCollisions);
    py_bindfunc(mod, "sprite_moveWithCollisions", &py_sprite_moveWithCollisions);
    py_bindfunc(mod, "sprite_querySpritesAtPoint", &py_sprite_querySpritesAtPoint);
    py_bindfunc(mod, "sprite_querySpritesInRect", &py_sprite_querySpritesInRect);
    py_bindfunc(mod, "sprite_querySpritesAlongLine", &py_sprite_querySpritesAlongLine);
    py_bindfunc(mod, "sprite_querySpriteInfoAlongLine", &py_sprite_querySpriteInfoAlongLine);
    py_bindfunc(mod, "sprite_overlappingSprites", &py_sprite_overlappingSprites);
    py_bindfunc(mod, "sprite_allOverlappingSprites", &py_sprite_allOverlappingSprites);
}

inline void py_add_enums(py_GlobalRef mod) {
    ADD_ENUM(kMicInputAutodetect);
    ADD_ENUM(kMicInputInternal);
    ADD_ENUM(kLFOTypeSampleAndHold);
    ADD_ENUM(kLineCapStyleButt);
    ADD_ENUM(kDrawModeFillWhite);
    ADD_ENUM(kDrawModeNXOR);
    ADD_ENUM(kSound16bitStereo);
    ADD_ENUM(kDrawModeFillBlack);
    ADD_ENUM(kDrawModeCopy);
    ADD_ENUM(kPolygonFillEvenOdd);
    ADD_ENUM(kJSONFalse);
    ADD_ENUM(kAlignTextRight);
    ADD_ENUM(kColorClear);
    ADD_ENUM(kBitmapFlippedX);
    ADD_ENUM(kButtonUp);
    ADD_ENUM(kWaveformPOVosim);
    ADD_ENUM(kColorXOR);
    ADD_ENUM(kJSONString);
    ADD_ENUM(kWrapWord);
    ADD_ENUM(kBitmapFlippedXY);
    ADD_ENUM(kBitmapFlippedY);
    ADD_ENUM(kJSONTrue);
    ADD_ENUM(kLFOTypeSine);
    ADD_ENUM(kSoundADPCMStereo);
    ADD_ENUM(kBitmapUnflipped);
    ADD_ENUM(kLFOTypeTriangle);
    ADD_ENUM(kButtonLeft);
    ADD_ENUM(kASCIIEncoding);
    ADD_ENUM(kTypeString);
    ADD_ENUM(kButtonB);
    ADD_ENUM(kFileReadData);
    ADD_ENUM(kTypeThread);
    ADD_ENUM(kFileRead);
    ADD_ENUM(kFileWrite);
    ADD_ENUM(kJSONInteger);
    ADD_ENUM(kAlignTextLeft);
    ADD_ENUM(kWaveformSawtooth);
    ADD_ENUM(kLFOTypeFunction);
    ADD_ENUM(kButtonA);
    ADD_ENUM(kButtonRight);
    ADD_ENUM(kWrapClip);
    ADD_ENUM(kJSONTable);
    ADD_ENUM(kLineCapStyleRound);
    ADD_ENUM(kPDLanguageEnglish);
    ADD_ENUM(kTypeTable);
    ADD_ENUM(kWaveformTriangle);
    ADD_ENUM(kTypeInt);
    ADD_ENUM(kWaveformSquare);
    ADD_ENUM(kTypeFunction);
    ADD_ENUM(kPDLanguageJapanese);
    ADD_ENUM(kTypeFloat);
    ADD_ENUM(kFilterTypeHighShelf);
    ADD_ENUM(kPDLanguageUnknown);
    ADD_ENUM(kWaveformPODigital);
    ADD_ENUM(kTypeNil);
    ADD_ENUM(kFilterTypeBandPass);
    ADD_ENUM(kColorBlack);
    ADD_ENUM(kDrawModeWhiteTransparent);
    ADD_ENUM(kFilterTypePEQ);
    ADD_ENUM(kUTF8Encoding);
    ADD_ENUM(kButtonDown);
    ADD_ENUM(kLineCapStyleSquare);
    ADD_ENUM(kLFOTypeSquare);
    ADD_ENUM(kWrapCharacter);
    ADD_ENUM(kFilterTypeNotch);
    ADD_ENUM(kWaveformSine);
    ADD_ENUM(kTypeBool);
    ADD_ENUM(kFilterTypeHighPass);
    ADD_ENUM(kMicInputHeadset);
    ADD_ENUM(kDrawModeBlackTransparent);
    ADD_ENUM(kFilterTypeLowShelf);
    ADD_ENUM(kSound8bitMono);
    ADD_ENUM(kFilterTypeLowPass);
    ADD_ENUM(kLFOTypeArpeggiator);
    ADD_ENUM(kWaveformNoise);
    ADD_ENUM(kJSONFloat);
    ADD_ENUM(kPolygonFillNonZero);
    ADD_ENUM(kSound16bitMono);
    ADD_ENUM(kWaveformPOPhase);
    ADD_ENUM(kAlignTextCenter);
    ADD_ENUM(k16BitLEEncoding);
    ADD_ENUM(kJSONNull);
    ADD_ENUM(kColorWhite);
    ADD_ENUM(kLFOTypeSawtoothDown);
    ADD_ENUM(kSound8bitStereo);
    ADD_ENUM(kDrawModeInverted);
    ADD_ENUM(kTypeObject);
    ADD_ENUM(kDrawModeXOR);
    ADD_ENUM(kSoundADPCMMono);
    ADD_ENUM(kFileAppend);
    ADD_ENUM(kJSONArray);
    ADD_ENUM(kLFOTypeSawtoothUp);
}

inline void python_playdate() {
    py_GlobalRef play_mod = py_newmodule("playdate");
    py_add_types(play_mod);
    py_add_funcs(play_mod);
    py_add_enums(play_mod);
}


char* open_file(const char* filename) {
    FileStat stat;
    pd->file->stat(filename, &stat);
    SDFile* filehandle = pd->file->open(filename, kFileRead);
    if (!filehandle) { 
        pd->file->geterr();
       
    }
    else {
        void* file_content = pd->system->realloc(NULL, stat.size);

        pd->file->read(filehandle, file_content, stat.size);

        pd->file->close(filehandle);
        return (char*)file_content;
    }
    return NULL;
  
}

py_ItemRef a;
bool ok;
char* m= NULL;
// game initialization
void setupGame(void)
{
    // Add Playdate modules
    python_playdate();

    // Open main.py
    m = open_file("main.py");
    if (m != NULL) {
        pd->system->logToConsole(m);
        // Run main file
        ok = py_exec(m, "__main__", EXEC_MODE, NULL);

        py_Name name = py_name("update");
        /// Get variable in the `__main__` module.
        py_ItemRef a = py_getglobal(name);
    }

   
}

void setPDPtr(PlaydateAPI* p) {
    pd = p;
}


// main update function
int update(void* ud)
{
    if (m != NULL) {
        py_exec("try:\n\tupdate()\nexcept Exception as e:\n\tplaydate.system_logToConsole(e)", "__main__", EXEC_MODE, NULL);

    }

	return 1;
}
