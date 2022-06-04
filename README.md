# cur v2
A simple plugin for CMD cursor handling.

**Usage**

``cur.exe <command> <args..>``

**The following commands are available:**

``cur get`` - Returns X Y coordinates to STDOUT, **the coordinates returned is the point after the prompt, not on the prompt**

`` cur set <x> <y>`` - Sets the screen to the coordinates given. If a non-numeric argument is given, the argument is defaulted to 0. **be careful**

`` cur blink <on/off>`` - Enable or disable the cursor blinking.

``cur size 0-100`` - Set the cursor size. It will turn blinking back on when the size is adjusted.

``cur show <on/off>`` - Show or hide the cursor.


