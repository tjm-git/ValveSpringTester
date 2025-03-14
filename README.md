# ValveSpringTester
Convert an arbor press to check valve spring height vs PSI using a load cell and rotary encoder.
This project uses a 1/2 ton arbor press to compress and measure the length/height and compression
PSI to compare to specifications.  Briefly, the arbor press has been modified with a large disk
attached to the vertical ram by removing it from the base and drilling and tapping a hole to mount
the disk.  The disk is approximately 3/16 thick and 2.5" diameter with a 1/4"  hole on center and 
counter sunk to make the disk flat at the bottom with no protrusions.  The ram is drilled and 
tapped for 1/4"-20 flat head hex drive bolt.  The load cell rests on the arbor base below the added 
disk.  The horizontal operating shaft was removed and drilled with an 8mm in the non-handle end, fitted
with an 8mm pin (press fit) leaving enough of a protrusion to fit into the rotary encoder bore and
tightened with the supplied grub screws.  The housing of the encoder is fastened to the frame of the
arbor press by way of a 4mm screw into a drilled and tapped hole in one of the arbor adjustment bolts
with a small spacer.  The vertical travel of the arbor ram is limited to a 3.1" free spring length.

The encoder and load cell wiring are routed to a 3D printed case housing an I2C 2004 LCD display, a small 
circuit board with a XIAO ESP32S3 and a generic HX711 load cell amplifier.  There is also a capacitive
touch switch cemented to the inside of the case specifically for a tare adjustment if needed after 
startup.

The load cell is an LCF-6, 58mm 200kg (440lbs) unit that works very well.  Throughout the range of 0-440lbs 
there is not more than 0.01 inch of actual compression of the cell.  For that amount no correction
is really necessary when reading spring length.  Most length and compression data specs is noted
with a 10% variation.  The load cell is required to be calibrated with a separate app to get a 
calibration number for accurate readings.  Since the load cell is not completely linear, this number
and some code to make adjustments need to be massaged to get very accurate readings.  This code is 
not in the current sketch.

The rotary encoder is a GHB-38, incremental, NPN output unit with 2048 PPR.  This needs to be calibrated
for a linear length readout either by accurately measuring the movement of the arbor ram and using a
small sketch to count the points or by moving the operating arm a known number of degrees and just doing
the math, 2048ppr/360.  Readout for length is to 0.01" as most, if not all, spring specs are to hundreths.

