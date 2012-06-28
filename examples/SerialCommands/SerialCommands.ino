#include <SerialCommandProcessor.h>

class ExampleCommands;
SerialCommandProcessor<ExampleCommands> commandProcessor;

class ExampleCommands {
public:
  static void handleCommand(char *cmd, uint8_t len);
};

void setup() {
  Serial.begin(57600);
}

void loop() {
  commandProcessor.step(Serial);
}

void ExampleCommands::handleCommand(char *command, uint8_t len) {
  if (strcmp(command, "echo off") == 0) {
    commandProcessor.echo = false;
  }
  else if (strcmp(command, "echo on") == 0) {
    commandProcessor.echo = true;
  }
  else if (strcmp(command, "") == 0 || strcmp(command, "ping") == 0) {
    Serial.println("pong");
  }
  else {
    Serial.println("failed");
    return;
  }
  Serial.println("ok");
}
