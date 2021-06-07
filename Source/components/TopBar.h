#pragma once

#include "JuceHeader.h"
#include "LookAndFeel.h"

class TopBar : public juce::Component
{
public:
    TopBar();
    void resized() override;

    class ClickableLabel : public juce::Label
    {
    public:
        std::function<void()> onClick {};
        void mouseUp (const juce::MouseEvent&) override
        {
            onClick();
        }
        void paint (juce::Graphics& g) override
        {
            using namespace juce;
            auto img = Drawable::createFromImageData (isOpen ? BinaryData::expand_more24px_svg : BinaryData::menu24px_svg, isOpen ? BinaryData::expand_more24px_svgSize : BinaryData::menu24px_svgSize);
            img->replaceColour (Colours::black, Colours::white);
            img->drawWithin (g, getLocalBounds().removeFromLeft (getHeight()).reduced (TickLookAndFeel::reducePixels * 2).toFloat(), RectanglePlacement::centred, 1.0f);
            auto alpha = isEnabled() ? 1.0f : 0.5f;
            auto& laf = getLookAndFeel();
            const Font font (laf.getLabelFont (*this));
            g.setColour (findColour (Label::textColourId).withMultipliedAlpha (alpha));
            g.setFont (font);
            auto textArea = laf.getLabelBorderSize (*this).subtractedFrom (getLocalBounds().withTrimmedLeft (getHeight() * 0.8));
            g.drawFittedText (getText(), textArea, getJustificationType(), jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())), getMinimumHorizontalScale());
            g.setColour (findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        bool isOpen { false };
    };
    ClickableLabel centerLabel;
    juce::DrawableButton leftButton;
    juce::DrawableButton rightButton;
};
