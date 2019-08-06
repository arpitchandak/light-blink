// This example uses an Arduino Uno together with

// an Ethernet Shield to connect to shiftr.io.

//

// You can check on your device after a successful

// connection here: https://shiftr.io/try.

//

// by Joël Gähwiler

// https://github.com/256dpi/arduino-mqtt

 

#include <Ethernet.h>

#include <MQTT.h>

 

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

byte ip[] = {10, 2, 6, 95};
//ip(169, 254, 39, 67);// <- change to match your network

 

EthernetClient net;

MQTTClient client;

 

unsigned long lastMillis = 0;

 

void connect() {

  Serial.print("connecting...");

  while (!client.connect("arduino", "dht_1011", "dht_1234")) {

    Serial.print(".");

    delay(1000);

  }

 

  Serial.println("\nconnected!");

 

  client.subscribe("/arduino");

  // client.unsubscribe("/hello");

}

 

void messageReceived(String &topic, String &payload) {

  Serial.println("incoming: " + topic + " - " + payload);

}

 

void setup() {

  Serial.begin(115200);

  Ethernet.begin(mac, ip);

 

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.

  // You need to set the IP address directly.

  client.begin("broker.shiftr.io", net);

  client.onMessage(messageReceived);

 

  connect();

}

 

void loop() {

  client.loop();

 

  if (!client.connected()) {

    connect();

  }

 

  // publish a message roughly every second.

  if (millis() - lastMillis > 1000) {

    lastMillis = millis();

    client.publish("/hello", "world");

  }

}
