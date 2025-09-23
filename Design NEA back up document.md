Design NEA back up document
========================

Design:

IPSO Chart.
Input, Process, Storage, Output.

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























