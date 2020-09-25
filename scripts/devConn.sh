#!/bin/bash
  roslaunch hsr_bringup co605_finger_go.launch &
  roslaunch gripper_bridge gripper_bridge_finger.launch &
  rosrun handrb_ui launch_vision.sh &
#  rosrun hsc3api_bridge hsc3api_bridge &
  rosrun perception_bridge perception_bridge &
  sleep 5
  roslaunch pickplace_bridge finger_pickplace_bridge.launch &
  rosrun openni2_tracker voice.sh &
  rosrun gripper_bridge five_finger_gripper.sh &
  rosrun dm_bridge dm_bridge &
  rosrun planner_bridge planner &
  rosrun motion_bridge motion_bridge_exe &
#  roslaunch force_bridge bring_up_realRobot.launch &
#  gnome-terminal -x bash -c "rosrun force_bridge shakeHandJudge" &
  rosrun daq_ros_driver daq_ros_driver &
  sleep 5
  gnome-terminal -x bash -c "rosrun hscfsm_bridge hscfsm_bridge" &
  sleep 2
  rosrun perception_bridge five_finger_scene.sh &
wait
exit 0
