
#include "./server/setup/start_server.h"
#include "./hid/devices.h"

int main(){
    
    create_keyboard();
    create_mouse();
    
    start_server();

}
