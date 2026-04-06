# NMEA

# GGA - Global positioning system fix data

```
$xxGGA,time,lat,NS,long,EW,quality,numSV,HDOP,alt,M,sep,M,diffAge,diffStation*cs<CR><LF>
```

| Field |    Name     | Unit  |   Format    |   Example   | Description                                                                            |
| :---: | :---------: | :---: | :---------: | :---------: | :------------------------------------------------------------------------------------- |
|   0   |    xxGGA    |   -   |   string    |   $GPGGA    | GGA Message ID (xx = current Talker ID)                                                |
|   1   |    time     |   -   |  hhmmss.ss  |  092725.00  | UTC time, see note on UTC representation                                               |
|   2   |     lat     |   -   | ddmm.mmmmm  | 4717.11399  | Latitude (degrees & minutes), see format description                                   |
|   3   |     NS      |   -   |  character  |      N      | North/South indicator                                                                  |
|   4   |    long     |   -   | dddmm.mmmmm | 00833.91590 | Longitude (degrees & minutes), see format description                                  |
|   5   |     EW      |   -   |  character  |      E      | East/West indicator                                                                    |
|   6   |   quality   |   -   |    digit    |      1      | Quality indicator for position fix, see table below and position fix flags description |
|   7   |    numSV    |   -   |   numeric   |     08      | Number of satellites used (range: 0-12)                                                |
|   8   |    HDOP     |   -   |   numeric   |    1.01     | Horizontal Dilution of Precision                                                       |
|   9   |     alt     |   m   |   numeric   |    499.6    | Altitude above mean sea level                                                          |
|  10   |    uAlt     |   -   |  character  |      M      | Altitude units: meters (fixed field)                                                   |
|  11   |     sep     |   m   |   numeric   |    48.0     | Geoid separation: difference between geoid and mean sea level                          |
|  12   |    uSep     |   -   |  character  |      M      | Separation units: meters (fixed field)                                                 |
|  13   |   diffAge   |   s   |   numeric   |      -      | Age of differential corrections (blank when DGPS is not used)                          |
|  14   | diffStation |   -   |   numeric   |      -      | ID of station providing differential corrections (blank when DGPS is not used)         |
|  15   |     cs      |   -   | hexadecimal |     *5B     | Checksum                                                                               |
|  16   |    CR LF    |   -   |  character  |      -      | Carriage return and line feed                                                          |

| Quality Indicator | Description, see also position fix flags description |
| :---------------: | :--------------------------------------------------- |
|         0         | No Fix / Invalid                                     |
|         1         | Standard GPS (2D/3D)                                 |
|         2         | Differential GPS                                     |
|         6         | Estimated (DR) Fix                                   |

# GLL - Global Latitude and Longitude, with time of position fix and status

```
$xxGLL,lat,NS,long,EW,time,status,posMode*cs<CR><LF>
```

| Field  |  Name   | Unit  |   Format    |   Example   | Description                                                                              |
| :----: | :-----: | :---: | :---------: | :---------: | :--------------------------------------------------------------------------------------- |
|   0    |  xxGLL  |   -   |   string    |   $GPGLL    | GLL Message ID (xx = current Talker ID)                                                  |
|   1    |   lat   |   -   | ddmm.mmmmm  | 4717.11364  | Latitude (degrees & minutes), see format description                                     |
|   2    |   NS    |   -   |  character  |      N      | North/South indicator                                                                    |
|   3    |  long   |   -   | dddmm.mmmmm | 00833.91565 | Longitude (degrees & minutes), see format description                                    |
|   4    |   EW    |   -   |  character  |      E      | East/West indicator                                                                      |
|   5    |  time   |   -   |  hhmmss.ss  |  092321.00  | UTC time, see note on UTC representation                                                 |
|   6    | status  |   -   |  character  |      A      | V = Data invalid or receiver warning, A = Data valid. See position fix flags description |
| 7 (op) | posMode |   -   |  character  |      A      | Positioning mode, see position fix flags description                                     |
|   8    |   cs    |   -   | hexadecimal |     *60     | Checksum                                                                                 |
|   9    |  CR LF  |   -   |  character  |      -      | Carriage return and line feed                                                            |

# GSA - GNSS DOP and Active Satellites

```
$xxGSA,opMode,navMode{,sv},PDOP,HDOP,VDOP*cs<CR><LF>
```

| Field  |  Name   | Unit  |   Format    | Example | Description                                                                                                      |
| :----: | :-----: | :---: | :---------: | :-----: | :--------------------------------------------------------------------------------------------------------------- |
|   0    |  xxGSA  |   -   |   string    | $GPGSA  | GSA Message ID (xx = current Talker ID)                                                                          |
|   1    | opMode  |   -   |  character  |    A    | Operation mode (M - Manually set to operate in 2D or 3D mode, A - Automatically switching between 2D or 3D mode) |
|   2    | navMode |   -   |    digit    |    3    | Navigation mode (1 - Fix not available, 2 - 2D Fix, 3 - 3D Fix)                                                  |
| 3 - 14 |   sv    |   -   |   numeric   |   29    | Satellite number                                                                                                 |
|   15   |  PDOP   |   -   |   numeric   |  1.94   | Position dilution of precision                                                                                   |
|   16   |  HDOP   |   -   |   numeric   |  1.18   | Horizontal dilution of precision                                                                                 |
|   17   |  VDOP   |   -   |   numeric   |  1.54   | Vertical dilution of precision                                                                                   |
|   18   |   cs    |   -   | hexadecimal |   *0D   | Checksum                                                                                                         |
|   19   |  CR LF  |   -   |  character  |    -    | Carriage return and line feed                                                                                    |

# GSV - GNSS Satellites in View

```
$xxGSV,numMsg,msgNum,numSV,{,sv,elv,az,cno}*cs<CR><LF>
```

|     Field      |  Name  | Unit  |   Format    | Example | Description                                                     |
| :------------: | :----: | :---: | :---------: | :-----: | :-------------------------------------------------------------- |
|       0        | xxGSV  |   -   |   string    | $GPGSV  | GSV Message ID (xx = current Talker ID)                         |
|       1        | numMsg |   -   |    digit    |    3    | Number of messages, total number of GSV messages being output   |
|       2        | msgNum |   -   |    digit    |    1    | Navigation mode (1 - Fix not available, 2 - 2D Fix, 3 - 3D Fix) |
|       3        | numSV  |   -   |   numeric   |   29    | Satellite number                                                |
| 4 (8, 12, 16)  |   sv   |   -   |   numeric   |   23    | Satellite ID                                                    |
| 5 (9, 13, 17)  |  elv   |  deg  |   numeric   |   38    | Elevation (range 0-90)                                          |
| 6 (10, 14, 18) |   az   |  deg  |   numeric   |   230   | Azimuth, (range 0-359)                                          |
| 7 (11, 15, 19) |  cno   | dBHz  |   numeric   |   44    | Signal strength (C/N0, range 0-99), blank when not tracking     |
|       20       |   cs   |   -   | hexadecimal |   *0D   | Checksum                                                        |
|       21       | CR LF  |   -   |  character  |    -    | Carriage return and line feed                                   |

# RMC - Recommended Minimum data

```
$xxRMC,time,status,lat,NS,long,EW,spd,cog,date,mv,mvEW,posMode*cs<CR><LF>
```

| Field |  Name   |  Unit   |   Format    |   Example   | Description                                                                              |
| :---: | :-----: | :-----: | :---------: | :---------: | :--------------------------------------------------------------------------------------- |
|   0   |  xxRMC  |    -    |   string    |   $GPRMC    | RMC Message ID (xx = current Talker ID)                                                  |
|   1   |  time   |    -    |  hhmmss.ss  |  083559.00  | UTC time, see note on UTC representation                                                 |
|   2   | status  |    -    |  character  |      A      | V = Data invalid or receiver warning, A = Data valid. See position fix flags description |
|   3   |   lat   |    -    | ddmm.mmmmm  | 4717.11437  | Latitude (degrees & minutes), see format description                                     |
|   4   |   NS    |    -    |  character  |      N      | North/South indicator                                                                    |
|   5   |  long   |    -    | dddmm.mmmmm | 00833.91522 | Longitude (degrees & minutes), see format description                                    |
|   6   |   EW    |    -    |  character  |      E      | East/West indicator                                                                      |
|   7   |   spd   |  knots  |   numeric   |    0.004    | Speed over ground                                                                        |
|   8   |   cog   | degress |   numeric   |    77.52    | Course over ground                                                                       |
|   9   |  date   |    -    |   ddmmyy    |   091202    | Date in day, month, year format, see note on UTC representation                          |
|  10   |   mv    | degrees |   numeric   |      -      | Magnetic variation value (blank - not supported)                                         |
|  11   |  mvEW   |    -    |  character  |      -      | Magnetic variation E/W indicator (blank - not supported)                                 |
|  12   | posMode |    -    |  character  |      -      | Positioning mode, see position fix flags description                                     |
|  13   |   cs    |    -    | hexadecimal |     *57     | Checksum                                                                                 |
|  14   |  CR LF  |    -    |  character  |      -      | Carriage return and line feed                                                            |

# TXT - Text Transmission

```
$xxTXT,numMsg,msgNum,msgType,text*cs<CR><LF>
```

| Field |  Name   | Unit  |   Format    |    Example     | Description                                                                                                                        |
| :---: | :-----: | :---: | :---------: | :------------: | :--------------------------------------------------------------------------------------------------------------------------------- |
|   0   |  xxTXT  |   -   |   string    |     $GPTXT     | TXT Message ID (xx = current Talker ID)                                                                                            |
|   1   | numMsg  |   -   |   numeric   |       01       | Total number of messages in this transmission, 01 ... 99                                                                           |
|   2   | msgNum  |   -   |   numeric   |       01       | Message number in this transmission, range 01 ... xx                                                                               |
|   3   | msgType |   -   |   numeric   |       02       | Text identifier, u-blox GPS receivers specify the type of the message with this number. (00 Error, 01 Warning, 02 Notice, 07 User) |
|   4   |  text   |   -   |   string    | www.u-blox.com | Any ASCII text                                                                                                                     |
|   5   |   cs    |   -   | hexadecimal |      *67       | Checksum                                                                                                                           |
|   6   |  CR LF  |   -   |  character  |       -        | Carriage return and line feed                                                                                                      |

# VTG - Course over ground and Ground speed

```
$xxVTG,cogt,T,cogm,M,knots,N,kph,K,posMode*cs<CR><LF>
```

| Field |  Name   |  Unit   |   Format    | Example | Description                                        |
| :---: | :-----: | :-----: | :---------: | :-----: | :------------------------------------------------- |
|   0   |  xxVTG  |    -    |   string    | $GPVTG  | VTG Message ID (xx = current Talker ID)            |
|   1   |  cogt   | degrees |   numeric   |  77.52  | Course over ground (true)                          |
|   2   |    T    |    -    |  character  |    T    | Fixed field: true                                  |
|   3   |  cogm   | degrees |   numeric   |    -    | Course over ground (magnetic), not output          |
|   4   |    M    |    -    |  character  |    M    | Fixed field: magnetic                              |
|   5   |  knots  |  knots  |   numeric   |  0.004  | Speed over ground                                  |
|   6   |    N    |    -    |  character  |    N    | Fixed field: knots                                 |
|   7   |   kph   |  km/h   |   numeric   |  0.008  | Speed over ground                                  |
|   8   |    K    |    -    |  character  |    K    | Fixed field: kilometers per hour                   |
|   9   | posMode |    -    |  character  |    A    | Mode Indicator, see position fix flags description |
|  10   |   cs    |    -    | hexadecimal |   *06   | Checksum                                           |
|  11   |  CR LF  |    -    |  character  |    -    | Carriage return and line feed                      |
