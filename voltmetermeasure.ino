
//NOTE THAT the measurements are repeated 10 times to reduce the effect of noise, but it's not required to take the average(i.e. divide by 10 because 
//you're now going to calibrate the value (sum of 10 readings) to the expected voltage value
//to calibrate, choose a known 0V and measure with the arduino, if it's 0 then it's fine
//then choose another known voltage, say, 3.3V (using the voltage source) and measure the reading
//now the REAL voltage will be (any reading)*Scale factor, where Scale factor = actualvoltage(3.3V)/reading measured when conneced to 3.3V
//so, run the bottom code, then after calibrating and finding the scale factor, UNCOMMENT the commented code and remove the replica:



//const float scalefactor = 0.5059; // my scalefactor: yours will be different!
const int repeats = 10; // number of times to repeat the measurement
long int sum = 0; // a running total of the measurements for that channel


void setup() {
Serial.begin(9600);
analogReference(DEFAULT); // NB use "EXTERNAL" only if using an external reference
}

// take measurements and print result
void loop() {
readvoltage();
Serial.print("sum of ten readings is : ");
Serial.print(sum);
Serial.println("; ");

//after calibration, uncomment the below and remove the above

//float voltage = sum * scalefactor; // convert to voltage in millivolts
//Serial.print("voltage in mV is : ");
//Serial.print(voltage,0);
delay (2000);
}

void readvoltage() {
sum = 0;
for (int j = 0; j < repeats; j++) {
 sum += analogRead(0); // *** this depends on your Vout pin, here it's 0 but you can connect to any analog pin (A0 to A14)
 delay(7); // choose a short delay that does not add to 20msec.
 }
}
