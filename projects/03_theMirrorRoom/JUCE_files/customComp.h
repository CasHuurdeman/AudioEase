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

    struct XYPad : public Comp
    {
        XYPad(juce::RangedAudioParameter* rapX, juce::RangedAudioParameter* rapY) :
          Comp(), m_rapX(*rapX), m_rapY(*rapY),
          attachX(m_rapX, [this](float) { repaint(); }, nullptr),
          attachY(m_rapY, [this](float) { repaint(); }, nullptr)

        {
            attachX.sendInitialUpdate();
            attachY.sendInitialUpdate();
        }

    protected:
        juce::RangedAudioParameter &m_rapX, &m_rapY;
        juce::ParameterAttachment attachX, attachY;
        juce::Rectangle<float> bounds;
        const float thick = 2.f;

        void resized() override
        {
          bounds = getLocalBounds().toFloat().reduced(thick);
        }

        void paint(juce::Graphics& g) override
        {
          g.setColour(juce::Colour(0x22ffffff));

          g.drawLine(bounds.getX() + bounds.getWidth() * 0.5f, bounds.getY(), bounds.getX() + bounds.getWidth()* 0.5f, bounds.getBottom());
          g.drawLine(bounds.getX(), bounds.getY() + bounds.getHeight() * 0.5f, bounds.getRight(), bounds.getY() + bounds.getHeight() * 0.5f);

          g.setColour(juce::Colours::limegreen);
          g.drawRoundedRectangle(bounds, thick, thick);

          auto X = m_rapX.getValue();
          auto Y = m_rapY.getValue();

          auto xPos = bounds.getX() + X * bounds.getWidth();
          auto yPos = bounds.getY() + Y * bounds.getHeight();

          g.fillRect(xPos - 2.f, yPos - 2.f, 5.f, 5.f);
        }

      //mouseDown --> on click
        void mouseDown(const juce::MouseEvent& event) override
        {
          attachX.beginGesture();
          attachY.beginGesture();

          updatePointValues(event.position);
        }

        void mouseDrag(const juce::MouseEvent& event) override
        {
          updatePointValues(event.position);
        }

      //mouseUp --> on click release
        void mouseUp(const juce::MouseEvent& event) override
        {
          updatePointValues(event.position);

          attachX.endGesture();
          attachY.endGesture();
        }

        //sets the coordinates to the mouse coordinates
        void updatePointValues(const juce::Point<float>& pos)
        {
          attachX.setValueAsPartOfGesture(m_rapX.convertFrom0to1(pos.x / bounds.getWidth()));
          attachY.setValueAsPartOfGesture(m_rapY.convertFrom0to1(pos.y / bounds.getHeight()));
        }
    };
}

struct SpecialSlider
{
  SpecialSlider(juce::RangedAudioParameter* rap):
  slider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow),
  sliderAttachment(*rap, slider, nullptr)
  {}

  //TODO - no getter/setter?
  juce::Slider slider;
  juce::SliderParameterAttachment sliderAttachment;
};

