/*
  ==============================================================================

    SagaComponent.h
    Created: 9 Jun 2014 12:11:44am

  ==============================================================================
*/

#ifndef SAGACOMPONENT_H_INCLUDED
#define SAGACOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SagaComponent    : public Component
{
public:
    SagaComponent();
    ~SagaComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SagaComponent)
};


#endif  // SAGACOMPONENT_H_INCLUDED
