/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	addParameter (tempo = new AudioParameterFloat ("tempo", "Arpeggiator Tempo", 10.0, 240.0, 120.0));
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	notes.clear();
	currentNote = 0;
	lastNoteValue = -1;
	time = 0.0;
	rate = static_cast<float> (sampleRate);
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void NewProjectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midi)
{
	// the audio buffer in a midi effect will have zero channels!
	jassert (buffer.getNumChannels() == 0);
	
	// however we use the buffer to get timing information
	auto numSamples = buffer.getNumSamples();
	numSamples = 1024;
	
	// get note duration
	float speed = 60 / *tempo;
	auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (speed)))));
	
	MidiMessage msg;
	int ignore;
	
	for (MidiBuffer::Iterator it (midi); it.getNextEvent (msg, ignore);)
	{
		if      (msg.isNoteOn())  notes.add (msg.getNoteNumber());
		else if (msg.isNoteOff()) notes.removeValue (msg.getNoteNumber());
	}
	
	midi.clear();
	
	if ((time + numSamples) >= noteDuration)
	{
		auto offset = jmax (0, jmin ((int) (noteDuration - time), numSamples - 1));
		
		if (lastNoteValue > 0)
		{
			midi.addEvent (MidiMessage::noteOff (1, lastNoteValue), offset);
			lastNoteValue = -1;
		}
		
		if (notes.size() > 0)
		{
			currentNote = (currentNote + 1) % notes.size();
			lastNoteValue = notes[currentNote];
			midi.addEvent (MidiMessage::noteOn  (1, lastNoteValue, (uint8) 127), offset);
		}
		
	}
	
	time = (time + numSamples) % noteDuration;
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
