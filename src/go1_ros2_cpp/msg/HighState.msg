
uint8[2] head
uint8 level_flag #levelFlag
uint8 frame_reserve #frameReserve

uint32[2] sn #SN
uint32[2] version
uint16 bandwidth #bandWidth
IMU imu
MotorState[20] motor_state #motorState
BmsState bms
int16[4] foot_force #footForce
int16[4] foot_force_est #footForceEst
uint8 mode
float32 progress
uint8 gait_type #gaitType		   
float32 foot_raise_height #footRaiseHeight		  
float32[3] position 
float32 body_height #bodyHeight			  
float32[3] velocity 
float32 yaw_speed #yawSpeed				   
float32[4] range_obstacle #rangeObstacle
Cartesian[4] foot_position_to_body #footPosition2Body 
Cartesian[4] foot_speed_to_body #footSpeed2Body	
uint8[40] wireless_remote #wirelessRemote
uint32 reserve

uint32 crc