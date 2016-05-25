/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: robot_wheel_top.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1    V1.0          creat this file
*
* Description:  
***********************************************************************************************************************/

#include "robot_wheel_top.h"
#include "hf_link.h"

const float degree_to_radian=0.017453;
const float radian_to_degree=57.2958;

RobotAbstract my_robot;
HFLink hf_link_pc_node(0x11,0x01,&my_robot);
HFLink *hf_link_node_pointer=&hf_link_pc_node;

RobotWheel hands_free_robot;

/***********************************************************************************************************************
* Function:     void RobotWheel::robotWheelTopInit(void)
*
* Scope:        public
*
* Description:  robot init
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void RobotWheel::robotWheelTopInit(void)          
{
    set_robot_wheel_radius(my_robot.robot_parameters.robot_wheel_radius);
    set_robot_body_radius(my_robot.robot_parameters.robot_body_radius);
    l_filter = my_robot.robot_parameters.speed_low_filter;

    my_robot.motor_parameters.p1=motor_top.motor1.get_p1();
    my_robot.motor_parameters.i1=motor_top.motor1.get_i1();
    my_robot.motor_parameters.d1=motor_top.motor1.get_d1();
    my_robot.motor_parameters.p2=motor_top.motor1.get_p2();
    my_robot.motor_parameters.i2=motor_top.motor1.get_i2();
    my_robot.motor_parameters.d2=motor_top.motor1.get_d2();
}

/***********************************************************************************************************************
* Function:     void RobotWheel::robotWheelTopCall(void)   
*
* Scope:        public
*
* Description:  robot control interface, you must call it in a frequency , generaly  can set
*               be a half of pid frequency
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void RobotWheel::robotWheelTopCall(void)
{
    robotDataUpdate();
    chassisControl();    // control your robotic chassis
    robotCoordCalc();    // for robot localization
    headControl();       // control your robotic head
    armControl();        // control your robotic arm
}

/***********************************************************************************************************************
* Function:     void RobotWheel::robotDataUpdate(void)
*
* Scope:        private
*
* Description:  update the robot RobotAbstract ,only need a low call frequency , <=20HZ is recommended
*
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void RobotWheel::robotDataUpdate(void)
{
    //chassis
    my_robot.measure_global_speed.x = 0;
    my_robot.measure_global_speed.y = 0;
    my_robot.measure_global_speed.z = 0;
    my_robot.measure_robot_speed.x =0;
    my_robot.measure_robot_speed.y =0;
    my_robot.measure_robot_speed.z =0;

    my_robot.measure_motor_speed.servo1 = motor_top.motor1.get_measure_angle_speed() * degree_to_radian;
    my_robot.measure_motor_speed.servo2 = motor_top.motor2.get_measure_angle_speed() * degree_to_radian;
    my_robot.measure_motor_speed.servo3 = motor_top.motor3.get_measure_angle_speed() * degree_to_radian;

    getRobotSpeed((float* )&my_robot.measure_motor_speed , (float* )&my_robot.measure_robot_speed);
    getGlobalSpeed((float* )&my_robot.measure_motor_speed , (float* )&my_robot.measure_global_speed , my_robot.measure_global_coordinate.z);

    my_robot.measure_motor_mileage.servo1 = motor_top.motor1.get_past_total_angle() * degree_to_radian;
    my_robot.measure_motor_mileage.servo2 = motor_top.motor2.get_past_total_angle() * degree_to_radian;
    my_robot.measure_motor_mileage.servo3 = motor_top.motor3.get_past_total_angle() * degree_to_radian;
    //coordinate data will be update by robotCoordCalc function , because this Typed data need a High Frequency
    //MSGCoord   measure_global_coordinate ;
    //MSGCoord   measure_robot_coordinate;

    //update by arm function , because it's not required components
    //measure_arm1_state
    //measure_arm2_state

    //update by head function , because it's not required components
    //measure_head1_state
    //measure_head2_state
    my_robot.robot_system_info.battery_voltage=system_data.Battery_Voltage;
    my_robot.robot_system_info.cpu_temperature=system_data.CPU_Temperature;
    my_robot.robot_system_info.cpu_usage=system_data.CPU_Usage;
    my_robot.robot_system_info.system_time=system_data.System_Time;

#ifdef DRIVER_IMU
    my_robot.measure_imu_euler_angle.pitch = imu_arithmetic_model.Fus_Angle.pitch * degree_to_radian;
    my_robot.measure_imu_euler_angle.roll = imu_arithmetic_model.Fus_Angle.roll * degree_to_radian;
    my_robot.measure_imu_euler_angle.yaw = imu_arithmetic_model.Fus_Angle.yaw * degree_to_radian;
#endif


    /****************************************************************************/


    if(hf_link_node_pointer->receive_package_renew[CLEAR_COORDINATE_DATA]==1)
    {
        hf_link_node_pointer->receive_package_renew[CLEAR_COORDINATE_DATA]=0;
        my_robot.measure_global_coordinate.x=0;
        my_robot.measure_global_coordinate.y=0;
        my_robot.measure_global_coordinate.z=0;
        my_robot.measure_robot_coordinate.x=0;
        my_robot.measure_robot_coordinate.y=0;
        my_robot.measure_robot_coordinate.z=0;
        motor_top.motor1.clear_past_total_angle();
        motor_top.motor2.clear_past_total_angle();
        motor_top.motor3.clear_past_total_angle();
    }
    if(hf_link_node_pointer->receive_package_renew[SET_ROBOY_PARAMETERS]==1)
    {
        hf_link_node_pointer->receive_package_renew[SET_ROBOY_PARAMETERS]=0;
        set_robot_wheel_radius(my_robot.robot_parameters.robot_wheel_radius);
        set_robot_body_radius(my_robot.robot_parameters.robot_body_radius);
        l_filter = my_robot.robot_parameters.speed_low_filter;
    }
    if(hf_link_node_pointer->receive_package_renew[SAVE_ROBOY_PARAMETERS]==1)
    {
        hf_link_node_pointer->receive_package_renew[SAVE_ROBOY_PARAMETERS]=0;
    }
    if(hf_link_node_pointer->receive_package_renew[SET_MOTOR_PARAMETERS]==1)
    {
        hf_link_node_pointer->receive_package_renew[SET_MOTOR_PARAMETERS]=0;

        motor_top.motor1.set_pid_parameters(my_robot.motor_parameters.p1 , my_robot.motor_parameters.i1,
                                            my_robot.motor_parameters.d1 , my_robot.motor_parameters.p2,
                                            my_robot.motor_parameters.i2 , my_robot.motor_parameters.d2
                                            );
        motor_top.motor2.set_pid_parameters(my_robot.motor_parameters.p1 , my_robot.motor_parameters.i1,
                                            my_robot.motor_parameters.d1 , my_robot.motor_parameters.p2,
                                            my_robot.motor_parameters.i2 , my_robot.motor_parameters.d2
                                            );
#if ROBOT_WHEEL_MODEL > 2
        motor_top.motor3.set_pid_parameters(my_robot.motor_parameters.p1 , my_robot.motor_parameters.i1,
                                            my_robot.motor_parameters.d1 , my_robot.motor_parameters.p2,
                                            my_robot.motor_parameters.i2 , my_robot.motor_parameters.d2
                                            );
#endif

#if ROBOT_WHEEL_MODEL > 3
        motor_top.motor3.set_pid_parameters(my_robot.motor_parameters.p1 , my_robot.motor_parameters.i1,
                                            my_robot.motor_parameters.d1 , my_robot.motor_parameters.p2,
                                            my_robot.motor_parameters.i2 , my_robot.motor_parameters.d2
                                            );
#endif

    }
    if(hf_link_node_pointer->receive_package_renew[SAVE_MOTOR_PARAMETERS]==1)
    {
        hf_link_node_pointer->receive_package_renew[SAVE_MOTOR_PARAMETERS]=0;
    }

}

/***********************************************************************************************************************
* Function:     void RobotWheel::chassisControl(void)           
*
* Scope:        private
*
* Description:  control your robotic chassis
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void RobotWheel::chassisControl(void)    
{ 	 

    if( hf_link_node_pointer->receive_package_renew[SET_GLOBAL_SPEED]==1 ){
        hf_link_node_pointer->receive_package_renew[SET_GLOBAL_SPEED]=0;
        control_command_quality += 30;        //control_command_quality add 30
        globalSpeedSet( (float* )&my_robot.expect_global_speed , (float* )&my_robot.expect_motor_speed ,
                        my_robot.measure_global_coordinate.z);
    }
    else if( hf_link_node_pointer->receive_package_renew[SET_ROBOT_SPEED]==1 ){
        hf_link_node_pointer->receive_package_renew[SET_ROBOT_SPEED ]=0;
        control_command_quality += 30;
        robotSpeedSet((float* )&my_robot.expect_robot_speed , (float* )&my_robot.expect_motor_speed);
    }
    else if( hf_link_node_pointer->receive_package_renew[SET_MOTOR_SPEED]==1 ){
        hf_link_node_pointer->receive_package_renew[SET_MOTOR_SPEED] = 0;
        control_command_quality += 30;
    }

    control_command_quality=control_command_quality-(100.00f/call_frequency); //control_command_quality reduce 1 every call
    if(control_command_quality >= 100){
        control_command_quality=100;
    }
    else if(control_command_quality <= 5){
        control_command_quality = 5;
    }
    if(control_command_quality <=30 ){  //if control_command_quality is too low
        robot_control_en = 0;  //motor control disable
    }
    else if(control_command_quality >=70 ){  //if control_command_quality is too low
        robot_control_en = 1;  //motor control disable
    }

    if(robot_control_en == 0)
    {
        motor_top.expect_angle_speed_m1=0;     //set motor Expect Speed 0
        motor_top.expect_angle_speed_m2=0;
#if ROBOT_WHEEL_MODEL > 2
        motor_top.expect_angle_speed_m3=0;
#endif
#if ROBOT_WHEEL_MODEL > 3
        motor_top.expect_angle_speed_m4=0;
#endif
    }
    else if(robot_control_en == 1)
    {
        motor_top.enable_m1=1 ;                //set motor enable
        motor_top.enable_m2=1 ;
#if ROBOT_WHEEL_MODEL > 2
        motor_top.enable_m3=1 ;
#endif
#if ROBOT_WHEEL_MODEL > 3
        motor_top.enable_m4=1 ;
#endif

        motor_top.expect_angle_speed_m1 = (1-l_filter) *motor_top.expect_angle_speed_m1 +
                l_filter* my_robot.expect_motor_speed.servo1*radian_to_degree ;                  //Speed Low-pass filter
        motor_top.expect_angle_speed_m2 = (1-l_filter) *motor_top.expect_angle_speed_m2 +
                l_filter* my_robot.expect_motor_speed.servo2*radian_to_degree ;

#if ROBOT_WHEEL_MODEL > 2
        motor_top.expect_angle_speed_m3 = (1-l_filter) *motor_top.expect_angle_speed_m3 +
                l_filter* my_robot.expect_motor_speed.servo3*radian_to_degree ;
#endif
#if ROBOT_WHEEL_MODEL > 3
        motor_top.expect_angle_speed_m4 = (1-l_filter) *motor_top.expect_angle_speed_m4 +
                l_filter* my_robot.expect_motor_speed.servo4*radian_to_degree ;
#endif
    }

}

/***********************************************************************************************************************
* Function:     void RobotWheel::headControl(void)         
*
* Scope:        private
*
* Description:  control your robotic head
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void RobotWheel::headControl(void)
{
#ifdef  DRIVER_SERVO
    my_robot.measure_head1_state.pitch = hf_head.measure_head_pitch;
    my_robot.measure_head1_state.yaw = hf_head.measure_head_yaw;
    my_robot.measure_head2_state.pitch = 0;
    my_robot.measure_head2_state.yaw =0;

    if( hf_link_node_pointer->receive_package_renew[SET_HEAD_1]==1 ){
        hf_link_node_pointer->receive_package_renew[SET_HEAD_1]=0;
        hf_head.set_head_state_renew=1;
        hf_head.expect_head_pitch = my_robot.expect_head1_state.pitch;
        hf_head.expect_head_yaw = my_robot.expect_head1_state.yaw;
    }
#endif
}

/***********************************************************************************************************************
* Function:     void RobotWheel::armControl(void)       
*
* Scope:        private
*
* Description:  control your robotic arm
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void RobotWheel::armControl(void)
{


}

/***********************************************************************************************************************
* Function:     void RobotWheel::robotCoordCalc(void)
*
* Scope:        private
*
* Description:  calculating coordinates, this is a  common methods  for robot localization
*               
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void RobotWheel::robotCoordCalc(void)
{

    d_motor_len_filter_.m1 = motor_top.motor1.get_d_past_angel() * degree_to_radian * get_robot_wheel_radius();

    d_motor_len_filter_.m2 = motor_top.motor2.get_d_past_angel() * degree_to_radian * get_robot_wheel_radius();

#if ROBOT_WHEEL_MODEL > 2
    d_motor_len_filter_.m3 = motor_top.motor3.get_d_past_angel() * degree_to_radian * get_robot_wheel_radius();
#endif

#if ROBOT_WHEEL_MODEL > 3
    d_motor_len_filter_.m4 = motor_top.motor4.past_angle * degree_to_radian * WHEEL_R;
#endif

#if COORD_CALC_IMU_EN == 1 
    //measure_global_coordinate.Z=imu_arithmetic_model.Fus_Angle.yaw ;   //use the IMU data to calculating coordinates
    //measure_robot_coordinate.Z=imu_arithmetic_model.Fus_Angle.yaw ;
#endif

    //need time stm32F1 330us  stm32F4+NOFPU 64~80us   stm32F4+FPU 8~16us
    getGlobalCoordinate( (float* )&d_motor_len_filter_ , (float* )&my_robot.measure_global_coordinate);
    //need time stm32F1 20us  stm32F4+FPU 0~2us
    getRobotCoordinate( (float* )&d_motor_len_filter_ , (float* )&my_robot.measure_robot_coordinate);

}

