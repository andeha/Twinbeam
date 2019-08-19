To start the pdb debugger and to inspect the state of your microcontroller, write:

```
My-MacbookPro-8:pdb> ./pdb

pdb, revision 6a5c45ca (^-c to quit.)

pdb: Starting /Applications/microchip/mplabx/v5.20/mplab_platform/bin/mdb.sh

>init
pdb: starts initializing device PIC32MZ2064DAB288


>Aug 07, 2019 2:17:58 PM org.openide.util.NbPreferences getPreferencesProvider
WARNING: NetBeans implementation of Preferences not found
Aug 07, 2019 2:17:59 PM com.microchip.mplab.mdbcore.RealICETool.RIMessages OutputMessage
INFO: 



*****************************************************

Connecting to Starter Kit on Board...

Currently loaded firmware on Starter Kit on Board
Firmware Suite Version.....01.56.00
Firmware type..............PIC32MZ

Target voltage detected
Unable to connect to the target device.
Failed to get Device ID

>glcdmode

GLCDMODE: GRAPHICS LCD CONTROLLER MODE REGISTER =  0x00000082

     GLCD_MODE_LCDEN 0␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|LCD Controller Module Enable
  GLCD_MODE_CURSOREN ␣0␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Programmable Cursor Enable
  GLCD_MODE_VSYNCPOL ␣␣␣0|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Vertical Sync Polarity
  GLCD_MODE_HSYNCPOL ␣␣␣␣|0␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Horizontal Sync Polarity
     GLCD_MODE_DEPOL ␣␣␣␣|␣0␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|DE Polarity
    GLCD_MODE_DITHER ␣␣␣␣|␣␣␣0|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Dithering Enable
  GLCD_MODE_VSYNCCYC ␣␣␣␣|␣␣␣␣|0␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Vertical Sync for Single Cycle Per Line Enable
   GLCD_MODE_PCLKPOL ␣␣␣␣|␣␣␣␣|␣0␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Pixel Clock Out Polarity
  GLCD_MODE_PGRAMPEN ␣␣␣␣|␣␣␣␣|␣␣␣0|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Palette Gamma Ramp Enable
GLCD_MODE_FORCEBLANK ␣␣␣␣|␣␣␣␣|␣␣␣␣|0␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Force Output to Blank
 GLCD_MODE_YUVOUTPUT ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣0␣|␣␣␣␣|␣␣␣␣|YUV Output Enable
 GLCD_MODE_FORMATCLK ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣0|␣␣␣␣|␣␣␣␣|Formatting Clock Divide Enable
  GLCD_MODE_RGBSEQ_3 ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|111␣|␣␣␣␣|RGB Sequential Modes


>
```

Note that a well-written `pdb` also may be started with `-s` and appears to be a source of knowledge in a varienty of matters.
