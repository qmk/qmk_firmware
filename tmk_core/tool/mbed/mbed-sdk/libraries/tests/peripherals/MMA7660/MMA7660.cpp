#include "MMA7660.h"

MMA7660::MMA7660(PinName sda, PinName scl, bool active) : _i2c(sda, scl)
{
    setActive(active);
    samplerate = 64;

}

//Since the MMA lacks a WHO_AM_I register, we can only check if there is a device that answers to the I2C address
bool MMA7660::testConnection( void )
{
    if (_i2c.write(MMA7660_ADDRESS, NULL, 0) == 0 )
        return true;
    else
        return false;
}

void MMA7660::setActive(bool state)
{
    char modereg = read(MMA7660_MODE_R);
    modereg &= ~(1<<0);

    //If it somehow was in testmode, disable that
    if (modereg && (1<<2)) {
        modereg &= ~(1<<2);
        write(MMA7660_MODE_R, modereg);
    }

    modereg += state;
    write(MMA7660_MODE_R, modereg);
}

void MMA7660::readData(int *data)
{
    if (!active) {
        setActive(true);
        active = true;
        wait(0.012 + 1/samplerate); //Wait until new sample is ready, my experience is that 1/samplerate isnt needed, but datasheet says so
    }

    char temp[3];
    bool alert;

    do {
        alert = false;
        read(MMA7660_XOUT_R, temp, 3);
        for (int i = 0; i<3; i++) {
            if (temp[i] > 63)
                alert = true;
            if (temp[i] > 31)
                temp[i] += 128+64;
            data[i] = (signed char)temp[i];
        }
    } while (alert);

    if (!active)
        setActive(false);
}


void MMA7660::readData(float *data)
{
    int intdata[3];
    readData(intdata);
    for (int i = 0; i<3; i++)
        data[i] = intdata[i]/MMA7660_SENSITIVITY;
}

float MMA7660::x( void )
{
    return getSingle(0);
}

float MMA7660::y( void )
{
    return getSingle(1);
}

float MMA7660::z( void )
{
    return getSingle(2);
}


void MMA7660::setSampleRate(int samplerate)
{
    setActive(false);                               //Not allowed to be active to change anything
    int rates[] = {120, 64, 32, 16, 8, 4, 2, 1};    //Alowed samplerates (and their number in array is also number required for MMA)
    int sampleLoc = 0, sampleError = 10000, temp;
    for (int i = 0; i<8; i++) {
        temp = abs( rates[i] - samplerate );
        if (temp<sampleError) {
            sampleLoc = i;
            sampleError=temp;
        }
    }

    //Update the samplerate reg
    temp = read(MMA7660_SR_R);
    temp &= ~0x07;                                  //Awake sample rate are lowest 3 bit
    temp |= sampleLoc;
    write(MMA7660_SR_R, temp);
    this->samplerate = rates[sampleLoc];
    setActive(active);                              //Restore previous active state
}


MMA7660::Orientation MMA7660::getSide( void )
{
    char tiltreg = read(MMA7660_TILT_R);

    //We care about 2 LSBs
    tiltreg &= 0x03;
    if (tiltreg == 0x01)
        return MMA7660::Front;
    if (tiltreg == 0x02)
        return MMA7660::Back;
    return MMA7660::Unknown;
}

MMA7660::Orientation MMA7660::getOrientation( void )
{
    char tiltreg = read(MMA7660_TILT_R);

    //We care about bit 2, 3 and 4 (counting from zero)
    tiltreg &= 0x07<<2;
    tiltreg >>= 2;
    if (tiltreg == 0x01)
        return MMA7660::Left;
    if (tiltreg == 0x02)
        return MMA7660::Right;
    if (tiltreg == 0x05)
        return MMA7660::Down;
    if (tiltreg == 0x06)
        return MMA7660::Up;
    return MMA7660::Unknown;
}



//////////////////////////////////////////////
///////////////PRIVATE////////////////////////
//////////////////////////////////////////////


void MMA7660::write(char address, char data)
{
    char temp[2];
    temp[0]=address;
    temp[1]=data;

    _i2c.write(MMA7660_ADDRESS, temp, 2);
}

char MMA7660::read(char address)
{
    char retval;
    _i2c.write(MMA7660_ADDRESS, &address, 1, true);
    _i2c.read(MMA7660_ADDRESS, &retval, 1);
    return retval;
}

void MMA7660::read(char address, char *data, int length)
{
    _i2c.write(MMA7660_ADDRESS, &address, 1, true);
    _i2c.read(MMA7660_ADDRESS, data, length);
}

float MMA7660::getSingle( int number )
{
    if (!active) {
        setActive(true);
        wait(0.012 + 1/samplerate); //Wait until new sample is ready
    }

    signed char temp;
    bool alert;

    do {
        alert = false;
        temp = read(MMA7660_XOUT_R + number);
        if (temp > 63)
            alert = true;
        if (temp > 31)
            temp += 128+64;
    } while (alert);

    if (!active)
        setActive(false);

    return temp / MMA7660_SENSITIVITY;
}
