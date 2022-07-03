#ifndef __LIBVOLTMETER__
#define __LIBVOLTMETER__

#define ADCPIN A4 // GPIO 32

float get_voltage() {
    pinMode(A4,INPUT_PULLDOWN);
    float adcValue = analogRead(ADCPIN);
    return ((adcValue * 3.3) / 4095);
}

#endif // LIBVOLTMETER
