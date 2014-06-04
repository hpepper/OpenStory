/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    btIdeas.setButtonText("Ideas");
    addAndMakeVisible(btIdeas);
    setSize (500, 400);
}

MainContentComponent::~MainContentComponent()

{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffeeddff));

//    g.setFont (Font (16.0f));
//    g.setColour (Colours::black);
//    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
//    btIdeas.setBoundsRelative (0.05, 0.05, 0.90, 0.25);
  //btIdeas.changeWidthToFitText(10);
    btIdeas.setBounds (10,10,50,20);
}
