Design NEA back up document
========================
# Design  

## General Overview
This project will be developed in C and ASM mainly with other necessary build files (I.E maker files) since non of these are object-orientated so there is no need for me to unnecessary implement structures. The system will need to talk directly to hardware and i will use ASM to accomplish this. this system will be able to power on and accept keyboard presses. 


## IPSO chart (Input, Process, Storage, Output)  

| Input | Process | Storage | Output |
|-------|---------|---------|--------|
| Power on / BIOS | Bootloader loads kernel into memory | Kernel stored in RAM | CLI “Booting Minimal OS” |
| User keystrokes | Kernel interprets key codes via interrupt handlers | Temporary memory buffer | Displayed characters on screen |
| Diagnostic command (e.g., `TCPU`) | Program executes arithmetic logic unit checks | Registers used temporarily | CPU check passed |
| Diagnostic command (e.g., `TKeyboard`) | Program maps each keystroke against expected input | No permanent storage | Missing/working keys list |
| Exit / Shutdown command | Kernel halts CPU | Clears buffer | System Shutdown |

## Modular design 
this is a breakdown diagram of the essential functions of each of my main systems:
![Modual design](images/modules_diagram.png)




Modular design comments
When designing system split into smaller components

Form/Navigation Design

Code Base

Data Dictonary

Validation Reqired

Algorithums

OOP

trace tables testing stratigys



Design

IPSO Chart (Input, Process, Storage, Output)
Input	Process	Storage	Output
Power on / BIOS handoff	Bootloader loads kernel into memory	Kernel stored in RAM	CLI message: “Booting Minimal OS…”
User keystrokes	Kernel interprets key codes via interrupt handlers	Temporary memory buffer	Displayed characters on screen
Diagnostic command (e.g., test_cpu)	Program executes arithmetic logic unit checks	Registers used temporarily	CLI output: “CPU check passed”
Diagnostic command (e.g., test_keyboard)	Program maps each keystroke against expected input	No permanent storage	CLI output: Missing/working keys list
Exit / Shutdown command	Kernel halts CPU	Clears buffer	CLI message: “System halted”























