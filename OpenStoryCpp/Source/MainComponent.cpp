/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "IdeaComponent.h"
#include "StoryComponent.h"
#include "SagaComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
: m_TopTab(TabbedButtonBar::TabsAtTop)
{
    m_TopTab.addTab("Ideas", Colour(0,0,250), new IdeaComponent(),  true);
    m_TopTab.addTab("Saga", Colour(0,200,0), new SagaComponent(),  true);
    m_TopTab.addTab("Story", Colour(0,150,0), new StoryComponent(),  true);
    addAndMakeVisible(m_TopTab);
    btIdeas.setButtonText("Ideas");
    //addAndMakeVisible(btIdeas);
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
    //btIdeas.setBounds (10,10,50,20);
    m_TopTab.setBounds (getLocalBounds().reduced (4));
}
