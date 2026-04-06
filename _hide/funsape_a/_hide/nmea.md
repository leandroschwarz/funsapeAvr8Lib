$GPGGA,x,x,x,x,x,0,00,99.99,x,x,x,x,x,*48

|  ID   | Field       | Value     |
| :---: | :---------- | :-------- |
|   0   | xxGGA       | $GPGGA  , |
|   1   | time        | x         |
|   2   | lat         | x         |
|   3   | NS          | x         |
|   4   | long        | x         |
|   5   | EW          | x         |
|   6   | quality     | 0       , |
|   7   | numSV       | 00      , |
|   8   | HDOP        | 99.99   , |
|   9   | alt         | x         |
|  10   | uAlt        | x         |
|  11   | sep         | x         |
|  12   | uSep        | x         |
|  13   | diffAge     | x         |
|  14   | diffStation | ?         |
|  15   | cs          | *48       |
|  16   | CR LF       |

$GPGLL,,,,,,V,N*64

|   ID   | Field   | Value  |
| :----: | :------ | :----- |
|   0    | xxGLL   | $GPGLL |
|   1    | lat     | x      |
|   2    | NS      | x      |
|   3    | long    | x      |
|   4    | EW      | x      |
|   5    | time    | x      |
|   6    | status  | V      |
| 7 (op) | posMode | N      |
|   8    | cs      | *64    |
|   9    | CR LF   |

$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30

|  ID   |  Field  | Value  |
| :---: | :-----: | :----: |
|   0   |  xxGSA  | $GPGSA |
|   1   | opMode  |   A    |
|   2   | navMode |   1    |
|   3   |   sv    |   x    |
|   4   |   sv    |   x    |
|   5   |   sv    |   x    |
|   6   |   sv    |   x    |
|   7   |   sv    |   x    |
|   8   |   sv    |   x    |
|   9   |   sv    |   x    |
|  10   |   sv    |   x    |
|  11   |   sv    |   x    |
|  12   |   sv    |   x    |
|  13   |   sv    |   x    |
|  14   |   sv    |   x    |
|  15   |  PDOP   | 99.99  |
|  16   |  HDOP   | 99.99  |
|  17   |  VDOP   | 99.99  |
|  18   |   cs    |  *30   |
|  19   |  CR LF  |

$GPGSV,1,1,00*79

|       ID       | Field  | Value  |
| :------------: | :----- | :----- |
|       0        | xxGSV  | $GPGSV |
|       1        | numMsg | 1      |
|       2        | msgNum | 1      |
|       3        | numSV  | 00     |
| 4 (8, 12, 16)  | sv     |        |
| 5 (9, 13, 17)  | elv    |        |
| 6 (10, 14, 18) | az     |        |
| 7 (11, 15, 19) | cno    |        |
|       20       | cs     | *79    |
|       21       | CR LF  |

$GPRMC,x,V,x,x,x,x,x,x,x,x,x,N*53

|  ID   | Field   | Value  |
| :---: | :------ | :----- |
|   0   | xxRMC   | $GPRMC |
|   1   | time    | x      |
|   2   | status  | V      |
|   3   | lat     | x      |
|   4   | NS      | x      |
|   5   | long    | x      |
|   6   | EW      | x      |
|   7   | spd     | x      |
|   8   | cog     | x      |
|   9   | date    | x      |
|  10   | mv      | x      |
|  11   | mvEW    | x      |
|  12   | posMode | N      |
|  13   | cs      | *53    |
|  14   | CR LF   |

$GPTXT,01,01,02,ANTSTATUS=DONTKNOW*33

|  ID   |  Field  |       Value        |
| :---: | :-----: | :----------------: |
|   0   |  xxTXT  |       $GPTXT       |
|   1   | numMsg  |         01         |
|   2   | msgNum  |         01         |
|   3   | msgType |         02         |
|   4   |  text   | ANTSTATUS=DONTKNOW |
|   5   |   cs    |        *33         |
|   6   |  CR LF  |

$GPTXT,01,01,02,ANTSTATUS=INIT*25

|  ID   |  Field  |     Value      |
| :---: | :-----: | :------------: |
|   0   |  xxTXT  |     $GPTXT     |
|   1   | numMsg  |       01       |
|   2   | msgNum  |       01       |
|   3   | msgType |       02       |
|   4   |  text   | ANTSTATUS=INIT |
|   5   |   cs    |      *25       |
|   6   |  CR LF  |

$GPTXT,01,01,02,ANTSTATUS=OK*3B

|  ID   |  Field  |    Value     |
| :---: | :-----: | :----------: |
|   0   |  xxTXT  |    $GPTXT    |
|   1   | numMsg  |      01      |
|   2   | msgNum  |      01      |
|   3   | msgType |      02      |
|   4   |  text   | ANTSTATUS=OK |
|   5   |   cs    |     *3B      |
|   6   |  CR LF  |

$GPTXT,01,01,02,ANTSUPERV=AC SD PDoS SR*20

|  ID   |  Field  |          Value          |
| :---: | :-----: | :---------------------: |
|   0   |  xxTXT  |         $GPTXT          |
|   1   | numMsg  |           01            |
|   2   | msgNum  |           01            |
|   3   | msgType |           02            |
|   4   |  text   | ANTSUPERV=AC SD PDoS SR |
|   5   |   cs    |           *20           |
|   6   |  CR LF  |

$GPTXT,01,01,02,HW  UBX-G60xx  00040007 FF7FFFFFp*53

|  ID   |  Field  |               Value               |
| :---: | :-----: | :-------------------------------: |
|   0   |  xxTXT  |              $GPTXT               |
|   1   | numMsg  |                01                 |
|   2   | msgNum  |                01                 |
|   3   | msgType |                02                 |
|   4   |  text   | HW  UBX-G60xx  00040007 FF7FFFFFp |
|   5   |   cs    |                *53                |
|   6   |  CR LF  |

$GPTXT,01,01,02,ROM CORE 7.03 (45969) Mar 17 2011 16:18:34*59

|  ID   |  Field  |                   Value                    |
| :---: | :-----: | :----------------------------------------: |
|   0   |  xxTXT  |                   $GPTXT                   |
|   1   | numMsg  |                     01                     |
|   2   | msgNum  |                     01                     |
|   3   | msgType |                     02                     |
|   4   |  text   | ROM CORE 7.03 (45969) Mar 17 2011 16:18:34 |
|   5   |   cs    |                    *59                     |
|   6   |  CR LF  |

$GPTXT,01,01,02,u-blox ag - www.u-blox.com*50

|  ID   |  Field  |           Value            |
| :---: | :-----: | :------------------------: |
|   0   |  xxTXT  |           $GPTXT           |
|   1   | numMsg  |             01             |
|   2   | msgNum  |             01             |
|   3   | msgType |             02             |
|   4   |  text   | u-blox ag - www.u-blox.com |
|   5   |   cs    |            *50             |
|   6   |  CR LF  |

$GPVTG,x,x,x,x,x,x,x,x,N*30

|  ID   |  Field  | Value  |
| :---: | :-----: | :----: |
|   0   |  xxVTG  | $GPVTG |
|   1   |  cogt   |   x    |
|   2   |    T    |   x    |
|   3   |  cogm   |   x    |
|   4   |    M    |   x    |
|   5   |  knots  |   x    |
|   6   |    N    |   x    |
|   7   |   kph   |   x    |
|   8   |    K    |   x    |
|   9   | posMode |   N    |
|  10   |   cs    |  *30   |
|  11   |  CR LF  |
