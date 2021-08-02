### Send Message to a Slack Channel 

##### Shopping List
 * ESP8266 NodeMCU
 * Slack account

### Incoming Webhooks integration

Follow these steps to create a Slack app.:

* Sign in to [Slack](https://slack.com/signin) and verify the channel exists where you want to post your slacks.
* Create channel if it does not exists. 
* Create an [app](https://api.slack.com/apps).
* Enter an app name and choose the workspace to associate with the app. Click "Create App".
* Click "Incoming Webhooks" under the section "Add features and functionality".
* In the next window, turn on the switch to activate "Incoming Webhooks".
* Extra options will now appear. Click on "Add New Webhook to Workspace" at the bottom.
* Select a channel and then click “Allow”. You will be redirected back to "Incoming Webhooks".
* Scroll down and you can see Webhook URL which look something like this: https://hooks.slack.com/services/TXXXXXXXXXX/BXXXXXXXXXX/XXXXXXXXXXXXXXXXXXXXXXXX
* Above the Webhook URL there is a curl command where you can test your slack webhook. (it should work inside git bash)
* Copy the Webhook URL. It will be used to send a message to a channel that selected in the setup. In this case, general channel has been selected.
* Get fingerprint of a SSL certificate. In order to send a GET request using the HTTPS protocol from ESP8266 NodeMCU to slack server, we need to get the fingerprint of the SSL certificate. 
* Open a browser and enter the URL address of your Slack website. Click on the lock symbol in the address bar and choose "Certificate". In the new window select the "Details" tab and find "Thumbprint" field in the list. Copy the thumbprint. It will be used inside  the code.

![thumbprint in dutch](images/certificate.png)

Note: The fingerprint should be updated when the certificate expires.

### The code

Replace the values with the constants to store Wi-Fi network SSID and password, a Webhook URL, and fingerprint of a SSL certificate.

### Serial monitor

In the serial monitor you can enter a message which can be send to the slack channel.