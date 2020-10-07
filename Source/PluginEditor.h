/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SaturationMonsterAudioProcessorEditor :
    public juce::AudioProcessorEditor,
    private juce::ComboBox::Listener

{
public:
    SaturationMonsterAudioProcessorEditor (SaturationMonsterAudioProcessor&);
    ~SaturationMonsterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    juce::ScopedPointer<juce::Slider> driveKnob;
    juce::ScopedPointer<juce::Slider> rangeKnob;
    juce::ScopedPointer<juce::Slider> blendKnob;
    juce::ScopedPointer<juce::Slider> gainKnob;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SaturationMonsterAudioProcessor& audioProcessor;
    
    juce::ComboBox disChoice;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationMonsterAudioProcessorEditor)
};
