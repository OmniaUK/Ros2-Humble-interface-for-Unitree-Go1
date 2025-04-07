uint8[2] head
uint8 level_flag #levelFlag
uint8 frame_reserve #frameReserve

#uint32[2] sn #SN  -- Dont want to change the SN
#uint32[2] version -- Dont want to change the version
uint16 bandwidth #bandWidth
uint8 mode 

uint8 gait_type #gaitType		   
uint8 speed_level #speedLevel			   
float32 foot_raise_height #footRaiseHeight		   
float32 body_height #bodyHeight	   
float32[2] position 
float32[3] euler	   
float32[2] velocity 
float32 yaw_speed# yawSpeed				   
BmsCmd bms
LED[4] led
uint8[40] wireless_remote #wirelessRemote
uint32 reserve

uint32 crc