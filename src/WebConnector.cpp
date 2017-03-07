#include "webconnector.h"

const char* ssid = "STATEMACHINE";
WiFiServer server(80);

void WebConnector::init() {
  WiFi.mode(WIFI_AP);
  IPAddress Ip(192, 168, 1, 1);
  IPAddress NMask(255, 255, 255, 0);
  WiFi.softAPConfig(Ip, Ip, NMask);
  WiFi.softAP(ssid);
  server.begin();
  activeCommand = 12;
}

void WebConnector::handleConnection() {
  WiFiClient client = server.available();
  while (client.connected()) {
    if (client.available()) {
      while(client.available()) {
        input = client.readStringUntil('\n');
        if (input.startsWith("GET")) {
          // this is our get request, check if we have a parameter
          int commandPosition = input.indexOf("?command=");
          if (commandPosition > -1) {
            // a command, how exciting.
            activeCommand = input.substring(commandPosition+9, commandPosition+11);
            newValue = true;
            Serial.println("The active command is: " + activeCommand);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!DOCTYPE HTML><html></html>");
            client.stop();

          } else {
            // give back the ajax page with commands
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!doctype html><html><head>    <meta charset=\"utf-8\">    <title>Mini Kame</title>    <style>        div {            width: 100%;            height: 400px;        }        div div {            width: 33%;            height: 33%;            outline: 1px solid;            float: left;            font-size: 24px;            color: white;            text-align: center;            line-height: 500%;        }        .cB {            background-color: green;        }        .cBStop {            background-color: gray;        }        .cBDir {            background-color: orange;        }    </style>    <script type=\"text/javascript\">        function fireCommand(value) {            document.getElementById(value).style.background =\"black\";            var xhttp = new XMLHttpRequest();            xhttp.onreadystatechange = function() {                if (xhttp.readyState == 4) {                    document.getElementById(value).style.background = '';                }};            xhttp.open(\"GET\", \"cmd.html?command=\"+value, true);            xhttp.send();        }    </script></head><body><div>    <div class=\"cB\" id=\"01\" onclick=\"fireCommand('01')\" >Mad</div>    <div class=\"cBStop\" id=\"02\" onclick=\"fireCommand('02')\">Calm</div>    <div class=\"cBDir\" id=\"03\" onclick=\"fireCommand('03')\">Nice</div></div></body></html>");

            client.stop();
          }
        }
      }
    }
  }
}

String WebConnector::getActiveCommand() {
  newValue = false;
  return activeCommand;
}

bool WebConnector::hasNewValue() {
    return newValue;
}
