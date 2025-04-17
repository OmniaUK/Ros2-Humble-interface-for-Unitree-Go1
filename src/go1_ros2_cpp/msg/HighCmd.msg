# uint8[2] head # Not in use
#uint8 level_flag #levelFlag # Not in use
# uint8 frame_reserve #frameReserve # Not in use

# uint32[2] sn #SN  -- Dont want to change the SN
# uint32[2] version -- Dont want to change the version
# uint16 bandwidth #bandWidth # Not in use
uint8 mode

uint8 gait_type #gaitType		   
# uint8 speed_level #speedLevel # Not in use	   
float32 foot_raise_height #footRaiseHeight		   
float32 body_height #bodyHeight	   
# float32[2] position # Not in use
float32[3] euler	   
float32[2] velocity 
float32 yaw_speed # yawSpeed				   
# BmsCmd bms # Not in use
# LED[4] led # Not in use
# uint8[40] wireless_remote #wirelessRemote # Not in use
# uint32 reserve # Not in use

# uint32 crc # Not in use