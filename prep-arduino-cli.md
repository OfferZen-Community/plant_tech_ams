# Installation

Install arduino-cli, this will vary depending on your OS.

## Archlinux

You can install it from the distro repositories

```
sudo pacman -S arduino-cli
```

you can verify that `arduino-cli` is properly installed by running

```
arduino-cli --help
```

# Configuration

With the cli utility installed, it's time to configure it.

1. Generate an empty configuration file. The file will be generated in `~/.arduino15/arduino-cli.yaml`.

```
arduino-cli config init
```

2. Add the url (https://arduino.esp8266.com/stable/package_esp8266com_index.json) for the ESP8266 to the configuration inside `additional_urls`. The file should look similar to:

```
board_manager:
  additional_urls: [https://arduino.esp8266.com/stable/package_esp8266com_index.json]
daemon:
  port: "50051"
directories:
  data: /home/my_username/.arduino15
  downloads: /home/my_username/.arduino15/staging
  user: /home/my_username/Arduino
library:
  enable_unsafe_install: false
logging:
  file: ""
  format: text
  level: info
metrics:
  addr: :9090
  enabled: true
sketch:
  always_export_binaries: false
```

3. Update the index

```
arduino-cli core update-index
```

4. Install the board libraries

```
arduino-cli core install esp8266:esp8266
```

## Grant appropriate permissions

If you are using linux, you will have to grant permission to your user to access the serial. 
You can simply add your user to the `uucp` group in order to do so.

```
sudo usermod -aG uucp my_username
```

Remember to log out and back in for the changes in the user groups to take effect.

# Create a sketch with the example code

Next, let's create an empty sketch and add the code from the example.

1. Create a new sketch

```
arduino-cli sketch new BlinkESP
```

2. The above command will create a directory with a skeleton file, `BlinkESP/BlinkESP.ino`. Replace the content of `BlinkESP.ino` with the contents from the [example](BlinkESP.ino). The file should look like this:

```

/*
  Blink an ESP8266 NodeMCU board
  Turns flashes an LED for one second delay.
  
  This program needs no circuit. It will use a built-in LED
  
  by Eng. Alaa Al Nassan
 */


# define LED D4 // Use built-in LED which connected to D4 pin or GPIO 2

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the LED as an output
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED, HIGH);  // Turn the LED off because the LED is active low
  Serial.println("OFF");
  delay(1000);            // Wait a second
  digitalWrite(LED, LOW);   // Turn the LED on because the LED is active low
  Serial.println("ON");
  delay(1000);              // Wait a second
}
```

# Compile and upload the code for the board

If you did everything correctly thus far, you should be able to compile the code for the board now!

1. Compile

```
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 BlinkESP
```

2. Plug in the board, if you haven't already done so. Next, run the following utility to determine where your board is

```
arduino-cli board list
```

On linux It should be something similar to `/dev/ttyUSB0`. On windows you should see the appropriate COM port.

3. Upload the compiled code to the port we discovered on the previous step.

```
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:nodemcuv2 BlinkESP
```

*note:* If you have not followed the steps for user permissions in the beginning of this guide, here is where you will find out. If you are getting permission denied, reffer back to the first session of the guide for information.

4. You are done! The LED should have started bliking. You can go back to the [main guide](PREP.md) and follow that from step 4 onwards!

# Bonus

On linux, if you want to check what the arduino is outputing to the serial (the test program outputs ON and OFF, as the LED changes state), you can do so by *simply* listing the content of the serial port which the board is being emulated on, in this example `/dev/ttyUSB0`. This would look something like:

```
tail -f /dev/ttyUSB0
```
