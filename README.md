# ValveSpringTester

    This project is to convert an arbor press to check valve spring height vs PSI using 
a load cell and rotary encoder. This project uses a 1/2 ton arbor press to compress 
a valve spring to it's working or test length and give a readout of compression force 
in Pounds Per Square Inch (PSI) to compare to specifications.  Briefly, the arbor 
press has a few modifications.  The arbor press base has only one mod, that being 
one of the ram adjustment screws drilled and tapped for a small bolt to fix the rotary 
encoder body fixed.  The ram was removed and the bottom end drilled and tapped to 
mount a 2 1/2" aluminum disk approximately 0.225" thick with a countersunk 1/4"-20 
flat head hex drive bolt.  This disk will accomodate most spring diameters and the 
countersunk fastener will allow the disk to mate flat to the load cell surface for 
zeroing.
    The horizontal operating shaft was removed, placed in the lathe, drilled with 
an 8mm drill in the non-handle end, fitted with an 8mm pin (press fit) leaving 
enough of a protrusion to fit into the rotary encoder bore and tightened with 
the supplied grub screws.  To keep the rotary encoder housing fixed to the arbor 
press, the drilled and tapped adjustment bolt we mentioned earlier was used with 
a 4mm hex drive screw/bolt and a small spacer.
    The load cell just rests on the arbor base under the ram and disk.  It could 
use a way to keep it centered, something like a fixed plate or a recess cut into 
the arbor itself.  With the load cell in place on the base, this particular 1/2 
ton press is limited to springs of not more than 3.1" of free spring length.
    The electronics of the unit consists of a XIAO ESP32S3 SOC collecting and 
processing the inputs, an I2C LCD display, a generic HX711 load cell amplifier 
taking the load cell output and feeding the result to the ESP32S3, and the rotary 
encoder feeding the spring height length data also to the ESP32S3.  The encoder 
and load cell wiring are attached to a small generic circuit board housing the 
ESP32S3 and the HX711 boards.  This board and the I2C 2004 LCD are mounted in a 
custom 3D printed case designed with Freecad. There is also a capacitive touch 
switch cemented to the inside of the case specifically for a tare adjustment if 
needed after startup. The capacitive touch switch appears to operate with about 
a 1cm proximity and works fine through the 3mm thick case.  The leads from the 
sensors can be soldered directly to their connection point although I used 
miniature 4 adn 5 pin male/female connectors.
    The load cell is an LCF-6, 58mm 200kg (440lbs) unit that works very well. 
Throughout the range of 0-440lbs there is not more than 0.01 inch of actual 
compression of the cell and for that amount no correction is really necessary 
when reading spring length. Most length and compression data specs are noted 
with a 10% variation and spring lengths noted to 0.01". The load cell is required 
to be calibrated with a separate app to get a calibration number for accurate 
readings.  This needs yet to be inserted into the code.  Since the load cell i
s not 100% completely linear, this calibration number and some code to 'massage' 
any variations are needed to increase accuracy.  This code is not in the current 
sketch. As mentioned, a HX711 generic load cell amplifier that supplies a 24 bit 
DAC is generally used with load cells of this type.
    The rotary encoder is a GHB-38, incremental, NPN output unit with 2048 PPR. 
This needs to be calibrated for linear length movement of the arbor ram.  Since 
the gearing of the ram and horizontal shaft can vary from arbor to arbor the rotary 
encoder needs to be calbrated.  We can do this accurately measuring the movement 
of the arbor ram and counting the number of pulses per inch for that distance using 
a simple sketch, or by rotating the shaft a known number of degrees and computing 
at 2048 pulses per 360 degrees of movement.   In either case, some simple 
calculations will give us the needed display numbers.  Readout for length is to 0.01" 
as most, if not all, spring specs are to hundreths.  Since there is roughly 700 
pulses per inch, accuracy to the 0.01" is an easy goal.


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

The encoder and load cell wiring are mounted to a 3D printed case that houses an I2C 2004 LCD display, a 
small circuit board with a XIAO ESP32S3 and a generic HX711 load cell amplifier.  There is also a capacitive
touch switch cemented to the inside of the case specifically for a tare adjustment if needed after 
startup.  The capacitive touch switch appears to operate with about a 1cm proximity and works through
the 3mm thick case.

The load cell is an LCF-6, 58mm 200kg (440lbs) unit that works very well.  Throughout the range of 0-440lbs 
there is not more than 0.01 inch of actual compression of the cell.  For that amount no correction
is really necessary when reading spring length.  Most length and compression data specs is noted
with a 10% variation.  The load cell is required to be calibrated with a separate app to get a 
calibration number for accurate readings.  Since the load cell is not completely linear, this number
and some code to make adjustments need to be massaged to get very accurate readings.  This code is 
not in the current sketch.  As mentioned, a HX711 generic load cell amplifier that supplies a 24 bit
DAC is generally used with load cells of this type.

The rotary encoder is a GHB-38, incremental, NPN output unit with 2048 PPR.  This needs to be calibrated
for a linear length readout either by accurately measuring the movement of the arbor ram and using a
small sketch to count the points or by moving the operating arm a known number of degrees and just doing
the math, 2048ppr/360.  Readout for length is to 0.01" as most, if not all, spring specs are to hundreths.

