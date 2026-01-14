//
// Created by cashu on 13/01/2026.
//
//with code from https://www.youtube.com/watch?v=SLpeh-q3oIE
//

#pragma once
#include "PluginEditor.h"

namespace comp
{
    struct Comp : public juce::Component
    {
       Comp(): juce::Component()
        {
//         setBufferedToImage(true);
        }
    protected:
      void paint(juce::Graphics& g) override {};
    };

    struct Label : public Comp
    {
      Label(juce::String txt) :
        Comp(), text(txt)
      {}
      juce::String text;

    protected:
      void paint(juce::Graphics& g) override
      {
        auto bounds = getLocalBounds().toFloat().reduced(2.f);
        g.setColour(juce::Colours::limegreen);
        auto font = g.getCurrentFont();
        auto strWidth = font.getStringWidthFloat(text);
        g.setFont(4.f * (float)getWidth()/strWidth);
        g.drawFittedText(text, bounds.toNearestInt(), juce::Justification::centred, 1);
        g.drawRoundedRectangle(bounds, 2.f, 2.f);
        for(auto i = 0; i < 2; ++i)
        {
          bounds = bounds.reduced(4.f);
          g.drawRoundedRectangle(bounds, 2.f, 2.f);
        }
      }
    };

    struct XYPad : public Comp //FIXME - if problem maybe because no RAP
    {
        XYPad() :
          Comp()
        {

        }

    protected:
        void paint(juce::Graphics& g) override
        {
          const auto thick = 2.f;
          const auto bounds = getLocalBounds().toFloat().reduced(thick);

          g.setColour(juce::Colours::limegreen);
          g.drawRoundedRectangle(bounds, thick, thick);
        }
    };
}

