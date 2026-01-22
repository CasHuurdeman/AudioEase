//
// Created by cashu on 13/01/2026.
//
//with code from https://www.youtube.com/watch?v=SLpeh-q3oIE
//

#pragma once
#include "PluginProcessor.h"

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
        g.setColour(juce::Colours::red);
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
        XYPad(juce::RangedAudioParameter* rapX, juce::RangedAudioParameter* rapY,
          juce::RangedAudioParameter* rapCircleX, juce::RangedAudioParameter* rapCircleY) :
          Comp(), m_rapX(*rapX), m_rapY(*rapY), m_rapCircleX(*rapCircleX), m_rapCircleY(*rapCircleY),
          attachX(m_rapX, [this](float) { repaint(); }, nullptr),
          attachY(m_rapY, [this](float) { repaint(); }, nullptr),
          attachCircleX(m_rapCircleX, [this](float) { repaint(); }, nullptr),
          attachCircleY(m_rapCircleY, [this](float) { repaint(); }, nullptr)
        {
            attachX.sendInitialUpdate();
            attachY.sendInitialUpdate();

            attachCircleX.sendInitialUpdate();
            attachCircleY.sendInitialUpdate();
        }


    protected:
        juce::RangedAudioParameter &m_rapX, &m_rapY, &m_rapCircleX, &m_rapCircleY;
        juce::ParameterAttachment attachX, attachY, attachCircleX, attachCircleY;

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

          g.setColour(juce::Colours::red);
          g.drawRoundedRectangle(bounds, thick, thick);

          float X = m_rapX.getValue();
          float Y = m_rapY.getValue();

          auto xPos = bounds.getX() + X * bounds.getWidth();
          auto yPos = bounds.getY() + Y * bounds.getHeight();

          g.fillRect(xPos - 2.f, yPos - 2.f, 5.f, 5.f);

        }

      //mouseDown --> on click
        void mouseDown(const juce::MouseEvent& event) override
        {
          attachCircleX.beginGesture();
          attachCircleY.beginGesture();

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

          attachCircleX.endGesture();
          attachCircleY.endGesture();
        }

        //sets the coordinates to the mouse coordinates
        void updatePointValues(const juce::Point<float>& pos)
        {
          attachCircleX.setValueAsPartOfGesture(m_rapX.convertFrom0to1(pos.x / bounds.getWidth()));
          attachCircleY.setValueAsPartOfGesture(m_rapY.convertFrom0to1(pos.y / bounds.getHeight()));
        }
    };

    struct Ears : public Comp
    {
      Ears(juce::RangedAudioParameter* rap):
      slider(juce::Slider::SliderStyle::LinearHorizontal, juce::Slider::TextEntryBoxPosition::TextBoxLeft),
      sliderAttachment(*rap, slider, nullptr)
      {
        juce::NormalisableRange<double> range(0.15,19, 0.005, 0.30,false);
        slider.setNormalisableRange(range);
      }

      juce::Slider slider;
      juce::SliderParameterAttachment sliderAttachment;
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

struct ParameterListener: public juce::Component
{
  ParameterListener(juce::RangedAudioParameter* rap):
    m_rap(*rap), m_attach(m_rap, [this](float) { repaint(); }, nullptr)
  {
  }

  void updateValue(auto value){ m_attach.setValueAsCompleteGesture(value);}

protected:
  juce::RangedAudioParameter &m_rap;
  juce::ParameterAttachment m_attach;
};


