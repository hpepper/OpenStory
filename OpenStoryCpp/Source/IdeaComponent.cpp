/*
  ==============================================================================

    IdeaComponent.cpp
    Created: 5 Jun 2014 8:42:19pm
    Author:  Henrik Koch

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "IdeaComponent.h"
#include "IdeaListComponent.h"
#include "IdeaNewComponent.h"

//==============================================================================
IdeaComponent::IdeaComponent()
: m_LocalTab(TabbedButtonBar::TabsAtTop)
{
    m_LocalTab.addTab("List", Colour(0,0,0), new IdeaListComponent(),  true);
    m_LocalTab.addTab("New", Colour(0,0,0), new IdeaNewComponent(),  true);
    addAndMakeVisible(m_LocalTab);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

IdeaComponent::~IdeaComponent()
{
}


void IdeaComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
   m_LocalTab.setBounds (getLocalBounds().reduced (4));
}
