/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SaturationMonsterAudioProcessor::SaturationMonsterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    state = new juce::AudioProcessorValueTreeState(*this, nullptr);
    
    state->createAndAddParameter("drive", "Drive", "Drive", juce::NormalisableRange<float>(0.f, 1.f, 0.001), 1, nullptr, nullptr);
    state->createAndAddParameter("range", "Range", "Range", juce::NormalisableRange<float>(0.f, 1.f, 0.001), 1, nullptr, nullptr);
    state->createAndAddParameter("blend", "Blend", "Blend", juce::NormalisableRange<float>(0.f, 1.f, 0.001), 1, nullptr, nullptr);
    state->createAndAddParameter("gain", "Gain", "Gain", juce::NormalisableRange<float>(0.f, 1.f, 0.001), 1, nullptr, nullptr);

    state->state = juce::ValueTree("drive");
    state->state = juce::ValueTree("range");
    state->state = juce::ValueTree("blend");
    state->state = juce::ValueTree("gain");

}

SaturationMonsterAudioProcessor::~SaturationMonsterAudioProcessor()
{
}

//==============================================================================
const juce::String SaturationMonsterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SaturationMonsterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SaturationMonsterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SaturationMonsterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SaturationMonsterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SaturationMonsterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SaturationMonsterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SaturationMonsterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SaturationMonsterAudioProcessor::getProgramName (int index)
{
    return {};
}

void SaturationMonsterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SaturationMonsterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SaturationMonsterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SaturationMonsterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SaturationMonsterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i) {

            auto input = channelData[i];
            auto cleanOut = channelData[i];

            if (menuChoice == 1)
                //Hard Clipping
            {
                if (input > drive)
                {
                    input = drive;
                }
                else if (input < -drive)
                {
                    input = -drive;
                }
                else
                {
                    input = input;
                }
            }
            if (menuChoice == 2)
                //Soft Clipping 
            {
                if (input > drive)
                {
                    input = 1.0f - expf(-input);
                }
                else
                {
                    input = -1.0f + expf(input);
                }
            }
            if (menuChoice == 3)
                //
            {
                
            }
            channelData[i] = ((1 - blend) * cleanOut) + (blend * input);
        }
    }


    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    float drive = *state->getRawParameterValue("drive");
    float range = *state->getRawParameterValue("drive");
    float blend = *state->getRawParameterValue("drive");
    float gain = *state->getRawParameterValue("drive");

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);






    }
}

juce::AudioProcessorValueTreeState& SaturationMonsterAudioProcessor::getState() {

    return *state;
}

//==============================================================================
bool SaturationMonsterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SaturationMonsterAudioProcessor::createEditor()
{
    return new SaturationMonsterAudioProcessorEditor (*this);
}

//==============================================================================
void SaturationMonsterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

    juce::MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);

    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SaturationMonsterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);

    if (tree.isValid()) {
    
        state->state = tree;

    }
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SaturationMonsterAudioProcessor();
}
