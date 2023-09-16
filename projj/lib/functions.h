#include "../include/header.h"
void toggleled() {
    if (millis() - buttonprevious >= 300UL) {
        state = !state;
        digitalWrite(ledPin, state);
        buttonprevious = millis();
    }
}

void handletoggle() {
    toggleled();
    server.send(200, "text/plain", "LED toggled");
}

void handleRoot() {
    String html = "<html><body>";
    html += "<h1>NodeMCU LED Control</h1>";
    html += "<button id=\"myButton\" onclick=\"toggle()\">" + String(state ? "Off" : "On") + "</button>";
    html += "<script>";
    html += "function toggle() {";
    html += "  var xhr = new XMLHttpRequest();";
    html += "  xhr.open('GET', '/tog', true);";
    html += "  xhr.send();";
    html += "  var button = document.getElementById('myButton');";
    html += "  if (button.innerHTML === 'On') {";
    html += "    button.innerHTML = 'Off';";
    html += "  } else {";
    html += "    button.innerHTML = 'On';";
    html += "  }";
    html += "}";
    html += "</script>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}
