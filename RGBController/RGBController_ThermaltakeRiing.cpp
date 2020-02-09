/*-----------------------------------------*\
|  RGBController_ThermaltakeRiing.cpp       |
|                                           |
|  Generic RGB Interface for Thermaltake    |
|  Riing controller                         |
|                                           |
|  Adam Honse (CalcProgrammer1) 2/9/2020    |
\*-----------------------------------------*/

#include "RGBController_ThermaltakeRiing.h"


RGBController_ThermaltakeRiing::RGBController_ThermaltakeRiing(ThermaltakeRiingController* riing_ptr)
{
    riing = riing_ptr;

    name = "Thermaltake Riing";

    type = DEVICE_TYPE_COOLER;

    /*-------------------------------------------------*\
    | Set size of colors array                          |
    \*-------------------------------------------------*/
    unsigned int led_count = 0;
    for (unsigned int channel_idx = 0; channel_idx < 5; channel_idx++)
    {
        led_count += riing->channel_leds[channel_idx];
    }
    colors.resize(led_count);

    /*-------------------------------------------------*\
    | Set zones and leds                                |
    \*-------------------------------------------------*/
    unsigned int led_idx = 0;
    for (unsigned int channel_idx = 0; channel_idx < 5; channel_idx++)
    {
        if(riing->channel_leds[channel_idx] > 0)
        {
            zone* new_zone = new zone;

            char ch_idx_string[2];
            sprintf(ch_idx_string, "%d", channel_idx + 1);

            new_zone->name = "Riing Channel ";
            new_zone->name.append(ch_idx_string);
            new_zone->type = ZONE_TYPE_LINEAR;

            std::vector<int> *new_zone_map = new std::vector<int>();

            for (unsigned int led_ch_idx = 0; led_ch_idx < riing->channel_leds[channel_idx]; led_ch_idx++)
            {
                char led_idx_string[3];
                sprintf(led_idx_string, "%d", led_ch_idx + 1);

                led new_led;
                new_led.name = "Riing Channel ";
                new_led.name.append(ch_idx_string);
                new_led.name.append(", LED ");
                new_led.name.append(led_idx_string);

                leds.push_back(new_led);
                leds_channel.push_back(channel_idx + 1);

                new_zone_map->push_back(led_idx);
                led_idx++;
            }

            new_zone->map.push_back(*new_zone_map);
            zones.push_back(*new_zone);
            zones_channel.push_back(channel_idx + 1);
        }
    }
}

void RGBController_ThermaltakeRiing::UpdateLEDs()
{
    for(std::size_t zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        unsigned int channel = zones_channel[zone_idx];

        std::vector<RGBColor> channel_colors;

        for(std::size_t color = 0; color < colors.size(); color++)
        {
            if(leds_channel[color] == channel)
            {
                channel_colors.push_back(colors[color]);
            }
        }

        if(channel_colors.size() > 0)
        {
            riing->SetChannelLEDs(channel, channel_colors);
        }
    }
}

void RGBController_ThermaltakeRiing::UpdateZoneLEDs(int zone)
{
    unsigned int channel = zones_channel[zone];

    std::vector<RGBColor> channel_colors;

    for(std::size_t color = 0; color < colors.size(); color++)
    {
        if(leds_channel[color] == channel)
        {
            channel_colors.push_back(colors[color]);
        }
    }

    if(channel_colors.size() > 0)
    {
        riing->SetChannelLEDs(channel, channel_colors);
    }
}

void RGBController_ThermaltakeRiing::UpdateSingleLED(int led)
{
    unsigned int channel = leds_channel[led];

    std::vector<RGBColor> channel_colors;

    for(std::size_t color = 0; color < colors.size(); color++)
    {
        if(leds_channel[color] == channel)
        {
            channel_colors.push_back(colors[color]);
        }
    }

    if(channel_colors.size() > 0)
    {
        riing->SetChannelLEDs(channel, channel_colors);
    }
}

void RGBController_ThermaltakeRiing::SetCustomMode()
{
}

void RGBController_ThermaltakeRiing::UpdateMode()
{
}