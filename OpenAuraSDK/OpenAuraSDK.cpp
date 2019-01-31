// OpenAuraSDK.cpp : Defines the exported functions for the DLL application.
//

#include "i2c_smbus.h"
#include "i2c_smbus_piix4.h"
#include "i2c_smbus_i801.h"
#include "AuraController.h"
#include "OpenAuraSDK.h"
#include <vector>

std::vector<AuraController *> controllers;

void CreateAuraDevice(AuraBusDriverType driver, unsigned int base, aura_dev_id dev)
{
    i2c_smbus_interface * bus;
    AuraController * aura;

    switch (driver)
    {
    case I2C_DRIVER_SMBUS_PIIX4:
        bus = new i2c_smbus_piix4();
        ((i2c_smbus_piix4 *)bus)->piix4_smba = base;
        break;

    case I2C_DRIVER_SMBUS_I801:
        bus = new i2c_smbus_i801();
        ((i2c_smbus_i801 *)bus)->i801_smba = base;
        break;

    default:
        return;
    }

    aura = new AuraController();
    aura->bus = bus;
    aura->dev = dev;

    controllers.push_back(aura);
}

//code adapted from i2c-tools i2cdetect.c
#define MODE_AUTO   0
#define MODE_QUICK  1
#define MODE_READ   2
#define MODE_FUNC   3

void DetectI2C(i2c_smbus_interface * bus, int mode)
{
    int i, j;
    int res;
    int slave_addr;

    freopen("i2cdetect.txt", "w", stdout);

    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");

    for (i = 0; i < 128; i += 16)
    {
        printf("%02x: ", i);

        for (j = 0; j < 16; j++)
        {
            /* Set slave address */
            slave_addr = i + j;

            /* Probe this address */
            switch (mode)
            {
            case MODE_QUICK:
                res = bus->i2c_smbus_write_quick(slave_addr, I2C_SMBUS_WRITE);
                break;
            case MODE_READ:
                res = bus->i2c_smbus_read_byte(slave_addr);
                break;
            default:
                if ((i + j >= 0x30 && i + j <= 0x37)
                 || (i + j >= 0x50 && i + j <= 0x5F))
                    res = bus->i2c_smbus_read_byte(slave_addr);
                else
                    res = bus->i2c_smbus_write_quick(slave_addr, I2C_SMBUS_WRITE);
                break;
            }

            if (res < 0)
            {
                printf("-- ");
            }
            else
            {
                printf("%02x ", i + j);
            }
        }
        printf("\r\n");
    }
}

void DumpAuraDevices()
{
    freopen("file.txt", "w", stdout);
    for (unsigned int i = 0; i < controllers.size(); i++)
    {
        unsigned char dcolor0 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x00 );
        unsigned char dcolor1 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x01 );
        unsigned char dcolor2 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x02 );
        unsigned char dcolor3 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x03 );
        unsigned char dcolor4 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x04 );
        unsigned char dcolor5 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x05 );
        unsigned char dcolor6 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x06 );
        unsigned char dcolor7 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x07 );
        unsigned char dcolor8 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x08 );
        unsigned char dcolor9 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x09 );
        unsigned char dcolorA = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0A );
        unsigned char dcolorB = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0B );
        unsigned char dcolorC = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0C );
        unsigned char dcolorD = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0D );
        unsigned char dcolorE = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0E );

        unsigned char ecolor0 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x00 );
        unsigned char ecolor1 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x01 );
        unsigned char ecolor2 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x02 );
        unsigned char ecolor3 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x03 );
        unsigned char ecolor4 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x04 );
        unsigned char ecolor5 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x05 );
        unsigned char ecolor6 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x06 );
        unsigned char ecolor7 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x07 );
        unsigned char ecolor8 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x08 );
        unsigned char ecolor9 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x09 );
        unsigned char ecolorA = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0A );
        unsigned char ecolorB = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0B );
        unsigned char ecolorC = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0C );
        unsigned char ecolorD = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0D );
        unsigned char ecolorE = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0E );

        unsigned char direct  = controllers[i]->AuraRegisterRead( AURA_REG_DIRECT               );
        unsigned char mode    = controllers[i]->AuraRegisterRead( AURA_REG_MODE                 );

        printf("Controller %d\r\n", i);
        printf("Direct Mode:    %d \r\n", direct  );
        printf("Mode Value:     %d \r\n", mode    );
        printf("Direct Color 0: %d \r\n", dcolor0);
        printf("Direct Color 1: %d \r\n", dcolor1);
        printf("Direct Color 2: %d \r\n", dcolor2);
        printf("Direct Color 3: %d \r\n", dcolor3);
        printf("Direct Color 4: %d \r\n", dcolor4);
        printf("Direct Color 5: %d \r\n", dcolor5);
        printf("Direct Color 6: %d \r\n", dcolor6);
        printf("Direct Color 7: %d \r\n", dcolor7);
        printf("Direct Color 8: %d \r\n", dcolor8);
        printf("Direct Color 9: %d \r\n", dcolor9);
        printf("Direct Color A: %d \r\n", dcolorA);
        printf("Direct Color B: %d \r\n", dcolorB);
        printf("Direct Color C: %d \r\n", dcolorC);
        printf("Direct Color D: %d \r\n", dcolorD);
        printf("Direct Color E: %d \r\n", dcolorE);
        printf("Effect Color 0: %d \r\n", ecolor0);
        printf("Effect Color 1: %d \r\n", ecolor1);
        printf("Effect Color 2: %d \r\n", ecolor2);
        printf("Effect Color 3: %d \r\n", ecolor3);
        printf("Effect Color 4: %d \r\n", ecolor4);
        printf("Effect Color 5: %d \r\n", ecolor5);
        printf("Effect Color 6: %d \r\n", ecolor6);
        printf("Effect Color 7: %d \r\n", ecolor7);
        printf("Effect Color 8: %d \r\n", ecolor8);
        printf("Effect Color 9: %d \r\n", ecolor9);
        printf("Effect Color A: %d \r\n", ecolorA);
        printf("Effect Color B: %d \r\n", ecolorB);
        printf("Effect Color C: %d \r\n", ecolorC);
        printf("Effect Color D: %d \r\n", ecolorD);
        printf("Effect Color E: %d \r\n", ecolorE);
    }
}

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x77);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x71);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x73);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x74);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B20, 0x4E);
    CreateAuraDevice(I2C_DRIVER_SMBUS_I801, 0xF000, 0x02);
    //DumpAuraDevices();
	short status[128];
	for (int i = 0; i < 128; i++)
	{
		status[i] = Inp32(0xF000 + i);
	}
    DetectI2C(controllers[0]->bus, MODE_AUTO);

    //for (unsigned int i = 0; i < controllers.size(); i++)
    //{
    //    controllers[i]->AuraRegisterWrite(AURA_REG_COLORS_EFFECT, 255);
    //    controllers[i]->AuraRegisterWrite(AURA_REG_DIRECT, 0);
    //    controllers[i]->AuraRegisterWrite(AURA_REG_MODE, AURA_MODE_RAINBOW);
    //    controllers[i]->AuraRegisterWrite(AURA_REG_APPLY, AURA_APPLY_VAL);
    //}

    return TRUE;
}