#!/bin/bash
  roslaunch hsr_bringup co605_finger_go.launch &
  rosrun openni2_tracker voice.sh &
#  roslaunch gripper_bridge gripper_bridge_finger.launch &
#  rosrun handrb_ui launch_vision.sh &
#  rosrun hsc3api_bridge hsc3api_bridge &
  sleep 5
#  rosrun gripper_bridge five_finger_gripper.sh &
  rosrun dm_bridge dm_bridge &
  rosrun planner_bridge planner &
  rosrun motion_bridge motion_bridge_exe &
  roslaunch force_bridge bring_up_realRobot.launch &
wait
exit 0
