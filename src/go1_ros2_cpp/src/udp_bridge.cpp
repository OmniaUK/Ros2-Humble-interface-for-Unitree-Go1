/* This is an example file to test the UDP control
*/

// SDK includes
#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include "FaceLightClient.h"

// General includes
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace UNITREE_LEGGED_SDK;

class Custom
{
public:
  Custom(uint8_t level) : safe(LeggedType::Go1),
                          udp(level, 8090, "192.168.12.1", 8082)
  {
    udp.InitCmdData(cmd);
  }
  void UDPRecv();
  void UDPSend();
  void RobotControl();

  Safety safe;
  UDP udp;
  HighCmd cmd = {};
  HighState state = {};
  int motiontime = 0;
  float dt = 0.002; // 0.001~0.01
};

void Custom::UDPRecv()
{
  udp.Recv();
  udp.GetRecv(state);
}

void Custom::UDPSend()
{
  udp.Send();
}

FaceLightClient ledControl;

void set_head_led(uint8_t r, uint8_t g, uint8_t b) {
  const uint8_t color[3] = {r, g, b};
  ledControl.setAllLed(color);
  ledControl.sendCmd();
}

void Custom::RobotControl()
{
  motiontime += 2;
  //   printf("%d   %f\n", motiontime, state.imu.quaternion[2]);
  cmd.mode = 0; // 0:idle, default stand      1:forced stand     2:walk continuously
  cmd.gaitType = 0;
  cmd.speedLevel = 0;
  cmd.footRaiseHeight = 0;
  cmd.bodyHeight = 0;
  cmd.euler[0] = 0;
  cmd.euler[1] = 0;
  cmd.euler[2] = 0;
  cmd.velocity[0] = 0.0f;
  cmd.velocity[1] = 0.0f;
  cmd.yawSpeed = 0.0f;
  cmd.reserve = 0;
// Moving the head about on the spot
  // if (motiontime > 0 && motiontime < 1000)
  // {
  //   cmd.mode = 1;
  //   cmd.euler[0] = -0.3;
  // }
  // if (motiontime > 1000 && motiontime < 2000)
  // {
  //   cmd.mode = 1;
  //   cmd.euler[0] = 0.3;
  // }
  // if (motiontime > 2000 && motiontime < 3000)
  // {
  //   cmd.mode = 1;
  //   cmd.euler[1] = -0.2;
  // }
  // if (motiontime > 3000 && motiontime < 4000)
  // {
  //   cmd.mode = 1;
  //   cmd.euler[1] = 0.2;
  // }
  // if (motiontime > 4000 && motiontime < 5000)
  // {
  //   cmd.mode = 1;
  //   cmd.euler[2] = -0.2;
  // }
  // if (motiontime > 5000 && motiontime < 6000)
  // {
  //   cmd.mode = 1;
  //   cmd.euler[2] = 0.2;
  // }
  // if (motiontime > 6000 && motiontime < 7000)
  // {
  //   cmd.mode = 1;
  //   cmd.bodyHeight = -0.2;
  // }
  // if (motiontime > 7000 && motiontime < 8000)
  // {
  //   cmd.mode = 1;
  //   cmd.bodyHeight = 0.1;
  // }
  // if (motiontime > 8000 && motiontime < 9000)
  // {
  //   cmd.mode = 1;
  //   cmd.bodyHeight = 0.0;
  // }
  
  // sit down
  // if (motiontime > 9000 && motiontime < 11000)
  // {
  //   cmd.mode = 5;
  // }
  // if (motiontime > 11000 && motiontime < 13000)
  // {
  //   cmd.mode = 7;
  // }
  // if (motiontime > 13000 && motiontime < 15000)
  // {
  //   cmd.mode = 6;
  // }

  // stand back up
  // if (motiontime > 15000 && motiontime < 16000)
  // {
  //   cmd.mode = 0;
  // }


  // Spin on the spot
  // if (motiontime > 16000 && motiontime < 20000)
  // {
  //   cmd.mode = 2;
  //   cmd.gaitType = 2;
  //   cmd.velocity[0] = 0.4f;
  //   cmd.yawSpeed = 2;
  //   cmd.footRaiseHeight = 0.1;
  // }
  
  // move forward a small bit
  // if (motiontime > 20000 && motiontime < 22000)
  // {
  //   cmd.mode = 0;
  //   cmd.velocity[0] = 0;
  // }
  // if (motiontime > 22000 && motiontime < 26000)
  // {
  //   cmd.mode = 2;
  //   cmd.gaitType = 1;
  //   cmd.velocity[0] = 0.2f;
  //   cmd.bodyHeight = 0.1;
  // }

  // straightHand mode usage
  // if (motiontime > 26000 && motiontime < 27000)
  // {
  //    cmd.mode = 1;
  // // }
  // // if (motiontime > 27000 && motiontime < 35000)
  // // {
  //   cmd.mode = 11;
  // }

  //  Jump left
  // // jumpYaw mode usage
  // if (motiontime > 35000 && motiontime < 36000)
  // {
  //   cmd.mode = 1;
  // }
  // if (motiontime > 36000 && motiontime < 37000)
  // {
  //  cmd.mode = 7;
  // }

  //udp.SetSend(cmd);
}

int main(void)
{
  std::cout << "Communication level is set to HIGH-level." << std::endl
            << "WARNING: Make sure the robot is standing on the ground." << std::endl
            << "Press Enter to continue..." << std::endl;
  std::cin.ignore();

  Custom custom(HIGHLEVEL);
  //LoopFunc loop_control("control_loop", custom.dt, boost::bind(&Custom::RobotControl, &custom));
  // LoopFunc loop_udpSend("udp_send", custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
  // LoopFunc loop_udpRecv("udp_recv", custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

  // loop_udpSend.start();
  // loop_udpRecv.start();
  //loop_control.start();

  std::string sysState = " ";

  while (1)
  {
    set_head_led(255,0,0);  // Setting led using LED SDK
    //custom.UDPRecv(); // Update state from legged SDK
    sysState = std::to_string(custom.state.bms.SOC); // 
    std::cout << "Battery: %" + sysState << std::endl;
    sysState = std::to_string(custom.state.imu.temperature); // 
    std::cout << "Temp(C): " + sysState << std::endl;
    sysState = std::to_string(custom.state.velocity[0]); // 
    std::cout << "Forward Speed: " + sysState + "m/s" << std::endl;
    //custom.cmd.velocity[0] = 0.01;
    custom.cmd.mode = 2;
    custom.cmd.gaitType = 1;
    custom.cmd.velocity[0] = 0.1f;
    custom.udp.SetSend(custom.cmd);

    sleep(1);
    set_head_led(0,0,0);
    sleep(1);
    // if (sysState)
    // {
    //   /* code */
    // }
    
  };

  return 0;
}