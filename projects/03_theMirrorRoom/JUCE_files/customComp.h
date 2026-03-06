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
          juce::RangedAudioParameter* rapCircleX, juce::RangedAudioParameter* rapCircleY, juce::RangedAudioParameter* rapEars) :
          Comp(), m_rapX(*rapX), m_rapY(*rapY), m_rapCircleX(*rapCircleX), m_rapCircleY(*rapCircleY), m_rapEars(*rapEars),
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
        juce::RangedAudioParameter &m_rapX, &m_rapY, &m_rapCircleX, &m_rapCircleY, &m_rapEars;
        juce::ParameterAttachment attachX, attachY, attachCircleX, attachCircleY;


        juce::Rectangle<float> bounds;
        const float thick = 2.f;

        void resized() override
        {
          bounds = getLocalBounds().toFloat().reduced(thick);
        }



        void paint(juce::Graphics& g) override
        {

//==========================================LAMINATE BACKGROUND================================================
           g.setColour(juce::Colour(0xffffffff));
           g.fillRoundedRectangle(bounds, thick);
           g.setColour(juce::Colour(0xc880471c));
           g.fillRoundedRectangle(bounds, thick);

           //"grid to show how big it is"
           for (int i = 0; i < 50; i++)
           {
             g.setColour(juce::Colour(0x882e4543));
             float thickness = 0.02;
             float x = bounds.getX() + bounds.getWidth() * thickness*static_cast<float>(i);
             g.drawLine(x, bounds.getY(), x, bounds.getBottom());


             g.setColour(juce::Colour(0x992e1503));
             for (int j = 0; j < 5; j++)
             {
               float length = 0.2f * static_cast<float>(j) + static_cast<float>(i) * 0.0756778;
               while(length > 1) length -= 1;
               g.drawLine(x, bounds.getY() + bounds.getHeight() * length,
                 x + bounds.getWidth() * thickness, bounds.getY() + bounds.getHeight() * length);
             }
           }

  //======================================================GRID=========================================================
          g.setColour(juce::Colours::steelblue);

          g.drawLine(bounds.getX() + bounds.getWidth() * 0.5f, bounds.getY(), bounds.getX() + bounds.getWidth()* 0.5f, bounds.getBottom());
          g.drawLine(bounds.getX(), bounds.getY() + bounds.getHeight() * 0.5f, bounds.getRight(), bounds.getY() + bounds.getHeight() * 0.5f);

          g.setColour(juce::Colours::steelblue);
          g.drawRoundedRectangle(bounds, thick, thick);



//===============================================================RECEIVER=====================================================
          float xPos,yPos, X, Y;


          g.setColour (juce::Colours::white);

          float n = bounds.getWidth()/10;  //TODO - roomsize
          float radius = 3; //what is a?

          X = m_rapEars.convertFrom0to1(m_rapEars.getValue())/2.0f * n;
          Y = 0;

          xPos =  bounds.getCentreX() + X;
          yPos =  bounds.getCentreY() + Y;
          g.fillEllipse(xPos - radius,yPos - radius, 2*radius, 2*radius);

          xPos =  bounds.getCentreX() - X;
          yPos =  bounds.getCentreY() + Y;
          g.fillEllipse(xPos - radius,yPos - radius, 2*radius, 2*radius);


//====================================================SOURCE=================================================
          float sourceSize = bounds.getWidth()/10 * 0.2;

          X = m_rapX.getValue();
          Y = m_rapY.getValue();

          xPos = bounds.getX() + X * bounds.getWidth();
          yPos = bounds.getY() + Y * bounds.getHeight();

          g.setColour(juce::Colours::darkred);
          g.fillRect(xPos - sourceSize/2, yPos - sourceSize/2, sourceSize, sourceSize);
        }


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
        slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::darkred);
      }

      juce::Slider slider;
      juce::SliderParameterAttachment sliderAttachment;
    };

    struct CustomButton : public Comp
    {
      CustomButton(juce::RangedAudioParameter* rap, const std::string buttonText) :
      buttonAttachment(*rap, [this](float) { repaint(); }, nullptr)
      {
        button.setButtonText(buttonText);
        button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::darkred);
        button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
      }

      juce::TextButton button;
      juce::ParameterAttachment buttonAttachment;
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


