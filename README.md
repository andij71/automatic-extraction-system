# automatic-extraction-system

## Allgemeine Informationen

version: v1.0
mcu: Arduino Nano


## Hardware

<<<<<<< HEAD
### analog inputs
CURRENT1   A0
CURRENT2   A1
CURRENT3   A2

### digital inputs
TEACH1      D4    active low
TEACH2      D3    active low
TEACH3      D2    active low
SWITCH1     D5    active low
SWITCH2     D6    active low
SWITCH3     D7    active low
SJ1         D11   active low  
SJ2         D12   active low
SJ3         D13   active low

### digital outputs
RELAIS1     D8
RELAIS2     D9
RELAIS3     D10
=======
// analog inputs
#define aiCURRENT1   0
#define aiCURRENT2   1
#define aiCURRENT3   2


// digital inputs
#define iTEACH1      4   // active low
#define iTEACH2      3   // active low
#define iTEACH3      2   // active low
#define iSWITCH1     5   // active low
#define iSWITCH2     6   // active low
#define iSWITCH3     7   // active low
#define iSJ1         11  // active low  
#define iSJ2         12  // active low
#define iSJ3         13  // active low

// digital outputs
#define oRELAIS1     8
#define oRELAIS2     9
#define oRELAIS3     10



todo:
- Platine 
>>>>>>> efa4fa175ad74897e69909d8972f1c101950fe78
