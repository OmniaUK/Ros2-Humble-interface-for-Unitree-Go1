
# uint8[2] head # Not in use
# uint8 level_flag #levelFlag # Not in use
# uint8 frame_reserve #frameReserve # Not in use

uint32[2] sn #SN
uint32[2] version
uint16 bandwidth #bandWidth
# IMU imu # Not in use
# MotorState[20] motor_state #motorState # Not in use
#BmsState bms # Excluded due to dedicated BMS topic
int16[4] foot_force #footForce
# int16[4] foot_force_est #footForceEst # Not in use
uint8 mode
# float32 progress # Not in use
uint8 gait_type #gaitType		   
float32 foot_raise_height #footRaiseHeight		  
float32[3] position 
float32 body_height #bodyHeight			  
float32[3] velocity 
float32 yaw_speed #yawSpeed				   
# float32[4] range_obstacle #rangeObstacle # Not in use
# Cartesian[4] foot_position_to_body #footPosition2Body # Not in use
# Cartesian[4] foot_speed_to_body #footSpeed2Body	# Not in use
# uint8[40] wireless_remote #wirelessRemote # Not in use
# uint32 reserve # Not in use

# uint32 crc # Not in use