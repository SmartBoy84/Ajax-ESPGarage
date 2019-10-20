#include <ESP8266WiFi.h>

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"; //To show the device that we have connected

String html = R"=====(
<!DOCTYPE html>
<html>

<head>
    <meta name='viewport' content='width=device-width, initial-scale=1.0' />
    <meta charset='utf-8'>
    <title>Led Control</title>
</head>

<style>
    body {
        background-color: skyblue;
    }

    #LED_button {
        background-color: tomato;
        color: white;
        padding: 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 60px;
        margin: 2px 2px;
        border-radius: 40px;
        border: 4px solid black;
    }
</style>

<script>
    function garage() {
        var ajaxRequest = null;
        if (window.XMLHttpRequest) {
            ajaxRequest = new XMLHttpRequest();
        } else {
            ajaxRequest = new ActiveXObject("Microsoft.XMLHTTP");
        }

        if (!ajaxRequest) {
            alert("AJAX is not supported.");
            return;
        }
        ajaxRequest.open("GET", "open", true);
        ajaxRequest.onreadstatechange = function() {
            if (ajaxRequest.readState == 4 && ajaxRequest.status == 200) {
                var ajaxRequest = ajaxRequest.responseText;
            }
        }
        ajaxRequest.send();
    }
</script>

<body>
    <input type="button" id="LED_button" onclick="garage()" value="Garage Button!" />
</body>

</html>
)=====";

char ssid[] = "Mahmood-WiFi";
char pass[] = "Hamdan.6171@@@@";

String request = "";
int led = 5;

WiFiServer server(80);

void setup() {
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    Serial.begin(115200);
        Serial.println();
Serial.println(ssid);
    WiFi.begin(ssid, pass);
        while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
        Serial.print(WiFi.localIP()); 
            server.begin();
    Serial.println("Server started");

}

void loop() {
  
    WiFiClient client = server.available();
    if (!client){
      return;
      }
      request = client.readStringUntil('\r');
      Serial.println(request);
      if (request.indexOf("open")>0) {
        digitalWrite(led, HIGH);
        delay(110);
        digitalWrite(led, LOW);
        delay(5);
       }
          else {
                client.flush();
                client.print(header);
                client.print(html);
                delay(5);
            }
}
