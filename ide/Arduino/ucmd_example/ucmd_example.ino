#include "ucmd_example.h"

uc_app *app;

char *receive_data(char *buf, size_t buf_size) {
  char r = 0;
  size_t i = 0;
  while (!Serial.available());
  
  while (i < buf_size - 1) {
     if (Serial.available()) {
       r = Serial.read();
       buf[i] = r;
       i++;
       buf[i] = '\0';
       if (r == '\n') {
         break;
       }
     }
  }

  return buf;
}

void send_data(const char *response) {
  Serial.println(response); 
}

void setup() {                    
  Serial.begin(9600);
  while (!Serial);
  app = uc_math_app_get_instance();
  uc_app_set_send_data(app, send_data);
  uc_app_set_receive_data(app, receive_data);
}

void loop() {
  uc_app_run(app);
  delay(1000);
}
