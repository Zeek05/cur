# cur
A simple plugin for CMD cursor handling.

**Usage**

``cur.exe <command> <args..>``

**The following commands are available:**

``cur get`` - Returns X Y coordinates to STDOUT, **the coordinates returned is the point after the prompt, not on the prompt**

`` cur set <x> <y>`` - Sets the screen to the coordinates given. If a non-numeric argument is given, the argument is defaulted to 0. **be careful**

`` cur blink <on/off> <opt. 0-100>`` - Enable or disable the cursor blinking. You can also supply an optional argument to change the size of the cursor (100 being full character cell, 0 being smallest), even if the cursor is already on.

