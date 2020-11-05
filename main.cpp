#include "SerialCOM.hpp"
int main(int argc, char *argv[])
{
  SerialCOM com("/dev/ttyACM0");
  com.Open();
  com.SetOption();
  com.StartRead();
  while(com.isOpened()){
    sleep(2);
  }
  return 0;
}