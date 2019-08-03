int getReading() {
    return analogRead(A0);
}

float getVoltage() {
    return getReading() * (3.3 / 1023);
}

float getPercentage() {
    return getReading() * (100.0 / 1023);
}

String getVoltageString() {
    return String(getVoltage()) + "V";
}

String getPercentageString() {
    return String(getPercentage()) + "%";
}
