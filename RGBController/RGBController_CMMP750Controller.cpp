/*-------------------------------------------------------------------*\
|  RGBController_CMMP750Controller.cpp                                |
|                                                                     |
|  Driver for Coolermaster MP750 mousepad                             |
|                                                                     |
|  Chris M (Dr_No)          18th Apr 2020                             |
|                                                                     |
\*-------------------------------------------------------------------*/

#include "RGBController_CMMP750Controller.h"

RGBController_CMMP750Controller::RGBController_CMMP750Controller(CMMP750Controller* cmmp_ptr)
{
    cmmp750     = cmmp_ptr;

    name        = cmmp750->GetDeviceName();
    type        = DEVICE_TYPE_MOUSEMAT;
    description = "Cooler Master Mousepad 750";
    version     = "1.0";
    serial      = "";
    location    = cmmp750->GetLocation();

    mode Static;
    Static.name       = "Static";
    Static.value      = MP750_MODE_STATIC;
    Static.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Static.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    mode Blink;
    Blink.name       = "Blink";
    Blink.value      = MP750_MODE_BLINK;
    Blink.flags      = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR;
    Blink.speed_min  = MP750_SPEED_SLOWEST;
    Blink.speed_max  = MP750_SPEED_FASTEST;
    Blink.color_mode = MODE_COLORS_PER_LED;
    Blink.speed      = MP750_SPEED_NORMAL;
    modes.push_back(Blink);

    mode Breathing;
    Breathing.name       = "Breathing";
    Breathing.value      = MP750_MODE_BREATHING;
    Breathing.flags      = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR;
    Breathing.speed_min  = MP750_SPEED_SLOWEST;
    Breathing.speed_max  = MP750_SPEED_FASTEST;
    Breathing.color_mode = MODE_COLORS_PER_LED;
    Breathing.speed      = MP750_SPEED_NORMAL;
    modes.push_back(Breathing);

    mode ColorCycle;
    ColorCycle.name       = "Color Cycle";
    ColorCycle.value      = MP750_MODE_COLOR_CYCLE;
    ColorCycle.flags      = MODE_FLAG_HAS_SPEED;
    ColorCycle.speed_min  = MP750_SPEED_SLOWEST;
    ColorCycle.speed_max  = MP750_SPEED_FASTEST;
    ColorCycle.color_mode = MODE_COLORS_NONE;
    ColorCycle.speed      = MP750_SPEED_NORMAL;
    modes.push_back(ColorCycle);

    mode BreathCycle;
    BreathCycle.name       = "Breath Cycle";
    BreathCycle.value      = MP750_MODE_BREATH_CYCLE;
    BreathCycle.flags      = MODE_FLAG_HAS_SPEED;
    BreathCycle.speed_min  = MP750_SPEED_SLOWEST;
    BreathCycle.speed_max  = MP750_SPEED_FASTEST;
    BreathCycle.color_mode = MODE_COLORS_NONE;
    BreathCycle.speed      = MP750_SPEED_NORMAL;
    modes.push_back(BreathCycle);

    SetupZones();
}

RGBController_CMMP750Controller::~RGBController_CMMP750Controller()
{

}

void RGBController_CMMP750Controller::SetupZones()
{
    zone MP_zone;
    MP_zone.name          = "Mousepad";
    MP_zone.type          = ZONE_TYPE_SINGLE;
    MP_zone.leds_min      = 1;
    MP_zone.leds_max      = 1;
    MP_zone.leds_count    = 1;
    zones.push_back(MP_zone);

    led MP_led;
    MP_led.name = "Mousepad LED";
    leds.push_back(MP_led);

    SetupColors();
}

void RGBController_CMMP750Controller::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_CMMP750Controller::UpdateLEDs()
{
    unsigned char red = RGBGetRValue(colors[0]);
    unsigned char grn = RGBGetGValue(colors[0]);
    unsigned char blu = RGBGetBValue(colors[0]);
    cmmp750->SetColor(red, grn, blu);
}

void RGBController_CMMP750Controller::UpdateZoneLEDs(int zone)
{
    RGBColor      color = colors[zone];
    unsigned char red   = RGBGetRValue(color);
    unsigned char grn   = RGBGetGValue(color);
    unsigned char blu   = RGBGetBValue(color);
    cmmp750->SetColor(red, grn, blu);
}

void RGBController_CMMP750Controller::UpdateSingleLED(int led)
{
    UpdateZoneLEDs(led);
}

void RGBController_CMMP750Controller::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_CMMP750Controller::UpdateMode()
{
    switch(modes[active_mode].value)
    {
        case MP750_MODE_STATIC:
            cmmp750->SetMode(MP750_MODE_STATIC, modes[active_mode].speed);
            break;
        case MP750_MODE_BLINK:
            cmmp750->SetMode(MP750_MODE_BLINK, modes[active_mode].speed);
            break;
        case MP750_MODE_BREATHING:
            cmmp750->SetMode(MP750_MODE_BREATHING, modes[active_mode].speed);
            break;
        case MP750_MODE_COLOR_CYCLE:
            cmmp750->SetMode(MP750_MODE_COLOR_CYCLE, modes[active_mode].speed);
            break;
        case MP750_MODE_BREATH_CYCLE:
            cmmp750->SetMode(MP750_MODE_BREATH_CYCLE, modes[active_mode].speed);
            break;
        default:
            cmmp750->SetMode(MP750_MODE_BREATHING, modes[active_mode].speed);
            break;
    }
}
