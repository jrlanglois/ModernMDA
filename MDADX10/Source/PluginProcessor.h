#ifndef DX10_AUDIOPROCESSOR_H
#define DX10_AUDIOPROCESSOR_H

#include "JuceHeader.h"

//==============================================================================
class MDAProcessorParameter : public AudioProcessorParameter
{
public:
    MDAProcessorParameter (float initialValue,
                           const PropertySet& props);

    //==============================================================================
    float getValue() const override;
    void setValue (float newValue) override;
    float getDefaultValue() const override;
    String getName (int maximumStringLength) const override;
    String getLabel() const override;
    int getNumSteps() const override;
    float getValueForText (const String& text) const override;

private:
    //==============================================================================
    PropertySet props;
    float value;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MDAProcessorParameter)
};

//==============================================================================
class MDAProcessor : public AudioProcessor
{
    MDAProcessor() { setPlayConfigDetails (0, 2, 44100.0, 1024); }

    //==============================================================================
    void addParameter (const String& name,
                       const String& label,
                       int numSteps,
                       float defaultValue);

    //==============================================================================
    const String getInputChannelName (int channelIndex) const override  { return channelIndexToString (channelIndex); }
    const String getOutputChannelName (int channelIndex) const override { return channelIndexToString (channelIndex); }

private:
    //==============================================================================
    static String channelIndexToString (int index)
    {
        return TRANS ("Channel #").replace ("#", String (index + 1), true);
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MDAProcessor)        
};

//==============================================================================
class MDADX10AudioProcessor : public MDAProcessor
{
public:
    MDADX10AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const String getName() const override;
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    enum Configuration
    {
        maxVoices   = 8,
        kMax        = 32,
        sustainNote = 128,
        eventBuffer = 120,
        eventsDone  = 99999999
    };

    //==============================================================================
    class DX10Program;
    class DX10Voice;
    OwnedArray<DX10Program> programs;
    OwnedArray<DX10Voice> voices;
    ScopedPointer<DX10Program> currentProgram;

    //==============================================================================
    double Fs;
    float tune, rati, ratf, ratio;  //Modulator ratio
    float catt, cdec, crel;         //Carrier envelope
    float depth, dept2, mdec, mrel; //Modulator envelope
    float lfo0, lfo1, dlfo, modWhl, MW, pbend, velSens, volume, vibrato; //LFO and CC
    float rich, modMix;
    int currentProgramIndex, K;
    bool sustain;

    //==============================================================================
    void addProgram (const String& name,
                     float p0, float p1, float p2, float p3,
                     float p4, float p5, float p6, float p7,
                     float p8, float p9, float p10, float p11,
                     float p12, float p13, float p14, float p15);

    void updateParameters();

    void noteOn (int note, int velocity);
    void noteOff (int note);
    void flagEventsBuffer (float newFzip, int newK);
    void processMidi (MidiBuffer& midiMessages);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MDADX10AudioProcessor)
};

#endif //DX10_AUDIOPROCESSOR_H