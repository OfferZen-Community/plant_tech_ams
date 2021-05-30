# Installation

Make sure that you have screen or a similar 
Follow the [guide](https://docs.micropython.org/en/v1.15/esp8266/tutorial/intro.html) to get the basic firmware installation done.

You will need a way to view the serial terminal so it's best to make sure you have screen installed or something similar.

This [guide](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html) will help with that part.
arduino-cli --help

For uploading and working with the board I use [mpfshell](https://github.com/wendlers/mpfshell) which you can install as follows:
pip install mpfshell

```

# Configuration

## Grant appropriate permissions

If you are using linux, you will have to grant permission to your user to access the serial. 
You can simply add your user to the `uucp` or `dialout` group in order to do so.

```
sudo usermod -aG uucp my_username
sudo usermod -aG dialout my_username
```

Remember to log out and back in for the changes in the user groups to take effect.

# Create a program with the example code

Next, let's try to upload the blink sample code. You will see that the code is all contained in a boot.py script. This is because the micropython firmware will automatically try to run the code in a boot.py file once it is uploaded to the board.

Replace the `cu.usbserial-310` with the appropriate usb device on your system.
mpfshell --open cu.usbserial-310 -nc put boot.py;
```

*note:* If you have not followed the steps for user permissions in the beginning of this guide, here is where you will find out. If you are getting permission denied, reffer back to the first session of the guide for information.

4. You are done! The LED should have started blinking. You can go back to the [main guide](PREP.md) and follow that from step 4 onwards!

# Bonus

On linux, if you want to check what the arduino is outputing to the serial (the test program outputs ON and OFF, as the LED changes state), you can do so by connecting to the serial port using screen, in this example `/dev/cu.usbserial-310`. This would look something like:

```
screen /dev/cu.usbserial-310 115200
```
It's important to note that you need to connect to the serial at the right baud rate. By default it is 115200 kbps.