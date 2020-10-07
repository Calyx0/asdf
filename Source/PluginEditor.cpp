/*
  ==============================================================================

                            Holy Productions

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SaturationMonsterAudioProcessorEditor::SaturationMonsterAudioProcessorEditor (SaturationMonsterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    Component::addAndMakeVisible(driveKnob = new juce::Slider("Drive")); 
    driveKnob->setSliderStyle(juce::Slider::Rotary);
    driveKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    
    Component::addAndMakeVisible(rangeKnob = new juce::Slider("Range"));
    rangeKnob->setSliderStyle(juce::Slider::Rotary);
    rangeKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);

    Component::addAndMakeVisible(blendKnob = new juce::Slider("Blend"));
    blendKnob->setSliderStyle(juce::Slider::Rotary);
    blendKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);

    Component::addAndMakeVisible(gainKnob = new juce::Slider("Gain"));
    gainKnob->setSliderStyle(juce::Slider::Rotary);
    gainKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);

    driveAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "drive", *driveKnob);
    rangeAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "range", *rangeKnob);
    blendAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);
    gainAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "gain", *gainKnob);

    Component::addAndMakeVisible(&disChoice);
    disChoice.addItem("Hard Clip", 1);
    disChoice.addItem("Soft Clip", 2);
    disChoice.addItem("Sine Foldover", 3);
    disChoice.addItem("Slew Limiter", 4);
    disChoice.addItem("Tanh Waveshaper", 5);
    disChoice.addItem("Square Waveshaper", 6);
    disChoice.setSelectedId(1);

    disChoice.addListener(this);

    double ratio = 5.0 / 3.0;
    setResizeLimits(500, 500 / ratio, 1500, 1500 / ratio);
    getConstrainer()->setFixedAspectRatio(ratio);
    Component::setSize(500.0, 500.0 / ratio);
}

SaturationMonsterAudioProcessorEditor::~SaturationMonsterAudioProcessorEditor()
{
}

//==============================================================================
void SaturationMonsterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Component::getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SaturationMonsterAudioProcessorEditor::resized()
{
    // Positions of knobs and subcomponents

    disChoice.setBounds(Component::getWidth() / 2, Component:: getHeight() / 4, Component::getWidth() / 4, Component::getHeight() / 9);

    driveKnob->setBounds(((Component::getWidth() / 5) * 1 - (100 / 2)), ((Component::getHeight() / 3)*2) - (100 / 2),100,100);
    rangeKnob->setBounds(((Component::getWidth() / 5) * 2 - (100 / 2)), ((Component::getHeight() / 3)*2) - (100 / 2), 100, 100);
    blendKnob->setBounds(((Component::getWidth() / 5) * 3 - (100 / 2)), ((Component::getHeight() / 3)*2) - (100 / 2), 100, 100);
    gainKnob->setBounds(((Component::getWidth() / 5) * 4 - (100 / 2)), ((Component::getHeight() / 3)*2) - (100 / 2), 100, 100);

}


void SaturationMonsterAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatWasChanged)
{
    processor.menuChoice = comboBoxThatWasChanged->getSelectedId();
}
