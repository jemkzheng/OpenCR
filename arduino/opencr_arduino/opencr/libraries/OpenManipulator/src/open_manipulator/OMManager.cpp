/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Hye-Jong KIM*/


#include "../../include/open_manipulator/OMManager.h"

//////////////////////////////////////Manipulator////////////////////////////////////////////

    Manipulator::Manipulator(String name, int8_t dof):
    {
      name_ = name;
      dof_ = dof;
      base_position_ = Eigen::Vector3f::Zero();
      base_orientation_ = Eigen::Matrix3f::Identity(3,3);
    }

    Manipulator::Manipulator(int8_t dof):
    name("UnknownManipulator")
    {
      dof_ = dof;
      base_position_ = Eigen::Vector3f::Zero();
      base_orientation_ = Eigen::Matrix3f::Identity(3,3);
    }

    Manipulator::~Manipulator(){}

    // void Manipulator::init(int8_t number_of_joint, int8_t number_of_link, int8_t number_of_tool)
    // {
    //   number_of_joint_ = number_of_joint;
    //   number_of_link_ = number_of_link;
    //   number_of_tool_ = number_of_tool;
    //   joint.resize(number_of_joint_);
    //   link.resize(number_of_link_);
    //   tool.resize(number_of_tool_);
    // }

    void Manipulator::setDOF(int8_t dof)
    {
      dof_=dof;
    }

    void Manipulator::setBasePosition(Eigen::Vector3f base_position)
    {
      base_position_ = base_position;
    }

    void Manipulator::setBaseOrientation(Eigen::Matrix3f base_orientation)
    {
      base_orientation_ = base_orientation;
    }

    void Manipulator::setBasePose(Pose base_pose)
    {
      base_position_ = base_pose.position;
      base_orientation_ = base_pose.orientation;
    }

    Eigen::Vector3f Manipulator::getBasePosition()
    {
      return base_position_;
    }

    Eigen::Matrix3f Manipulator::getBaseOrientation()
    {
      return base_orientation_;
    }

    Pose Manipulator::getBasePose()
    {
      Pose temp;
      temp.position = base_position_;
      temp.orientation = base_orientation_;
      return temp
    }

//////////////////////////////////////Joint////////////////////////////////////////////

    Joint::Joint(): 
      dxl_id_(-1),
      angle_(0.0),
      velocity_(0.0),
      acceleration_(0.0)
    {
      position_ = Eigen::Vector3f::Zero();
      orientation_ = Eigen::Matrix3f::Identity(3,3);
    }

    Joint::~Joint(){}

    void Joint::init(int8_t dxl_id, Eigen::Vector3f axis)
    {
      dxl_id_ = dxl_id;
      axis_ = axis;
    }

    int8_t Joint::getId()
    {
      return dxl_id_;
    }

    Eigen::Vector3f getAxis()
    {
      return axis_;
    }

    void Joint::setAngle(float angle)
    {
      angle_ = angle;
    }
    
    float Joint::getAngle()
    {
      return angle_;
    }

    void Joint::setVelocity(float velocity)
    {
      velocity_ = velocity;
    }

    float Joint::getVelocity()
    {
      return velocity_;
    }
    
    void Joint::setAcceleration(float acceleration)
    {
      acceleration_ = acceleration;
    }

    float Joint::getAcceleration()
    {
      return acceleration_;
    }

    void Joint::setPosition(Eigen::Vector3f position)
    {
      position_ = position;
    }

    Eigen::Vector3f Joint::getPosition()
    {
      return position_;
    }

    void Joint::setOrientation(Eigen::Matrix3f orientation)
    {
      orientation_ = orientation;
    }

    Eigen::Matrix3f Joint::getOrientation()
    {
      return orientation_;n
    }

    void Joint::setPose(Pose joint_pose)
    {
      position_ = joint_pose.position;
      orientation_ = joint_pose.orientation;
    }

    Pose Joint::getPose()
    {
      Pose joint_pose;
      joint_pose.position = position_;
      joint_pose.orientation = orientation_;
      return joint_pose;
    }
 
//////////////////////////////////////Link////////////////////////////////////////////

    Link::Link(): 
    counter_(0),
    number_of_joint_in_link_(0),
    mass_(0.0),
    inertia_moment_(0.0)
    {
      center_position_ = Eigen::Vector3f::Zero();
    }

    Link::~Link(){}

    void Link::init(float mass, Eigen::Vector3f center_position)
    {
      mass_ = mass;
      center_position_ = center_position;
    }

    void Link::init(float mass, float inertia_moment, Eigen::Vector3f center_position)
    {
      inertia_moment_ = inertia_moment;
      mass_ = mass;
      center_position_ = center_position;
    }

    void Link::setJointInLink(int8_t number, Eigen::Vector3f relative_position, Eigen::Matrix3f relative_orientation)
    {
      jointinlink_(counter_).number = number;
      jointinlink_(counter_).relative_position = relative_position; 
      jointinlink_(counter_).relative_orientation = relative_orientation;
      if(counter_ >= number_of_joint_in_link_){counter_++;}
    }

    void Link::setJointInLink(int8_t joint_in_link_number, int8_t number, Eigen::Vector3f relative_position, Eigen::Matrix3f relative_orientation)
    {
      jointinlink_(joint_in_link_number).number = number;
      jointinlink_(joint_in_link_number).relative_position = relative_position; 
      jointinlink_(joint_in_link_number).relative_orientation = relative_orientation;
    }

    JointInLink Link::getJointInformation(int8_t joint_in_link_number)
    {
      JointInLink temp;
      temp.number = jointinlink_(joint_in_link_number).number;
      temp.relative_position = jointinlink_(joint_in_link_number).relative_position;
      temp.relative_orientation = jointinlink_(joint_in_link_number).relative_orientation;
      return temp;
    }

    int8_t Link::getTheNumberOfJoint()
    {
      return number_of_joint_in_link_;
    }

    float Link::getMass()
    {
      return mass_;
    }

    void Link::setMass(float mass)
    {
      mass_ = mass;
    }

    float Link::getInertiaMoment()
    {
      return inertia_moment_;
    }

    void Link::setInertiaMoment(float inertia_moment)
    {
      inertia_moment_ = inertia_moment;
    }

    int8_t Link::findJoint(int8_t joint_number)
    {
      int8_t i;
      for(i=0; i < number_of_joint_in_link_; i++)
      {
        if(jointinlink_.at(i).number == joint_number)
        {
          return i;
        }
      }
    }

    Eigen::Vector3f Link::getCenterPosition()
    {
      return center_position_;
    }

    Eigen::Vector3f Link::getCenterPosition(int8_t from)
    {
      Eigen::Vector3f temp;
      temp = center_position_ - jointinlink_.at(FineJoint(from)).relative_position;

      return temp;
    }
    
    Eigen::Vector3f Link::getRelativeJointPosition(int8_t to, int8_t from)
    {
      Eigen::Vector3f temp;

      temp = jointinlink_.at(FindJoint(to)).relative_position - jointinlink_.at(FindJoint(from)).relative_position;
      return temp; 
    }

    Eigen::Vector3f Link::getRelativeJointOrientation(int8_t to, int8_t from)
    {
      Eigen::Vector3f temp;

      temp = jointinlink_.at(FindJoint(from)).relative_orientation.transpose() * jointinlink_.at(FindJoint(to)).relative_orientation;
      return temp; 
    }

//////////////////////////////////////Tool////////////////////////////////////////////

    Tool::Tool():
    tool_type_("null"),
    {
      position_from_final_joint_ = Eigen::Vector3f::Zero();
      orientation_from_final_joint_ = Eigen::Matrix3f::Identity(3,3);
      position_ = Eigen::Vector3f::Zero();
      orientation_ = Eigen::Matrix3f::Identity(3,3);
    }
    Tool::~Tool(){}
    void init(String tool_type, Eigen::Vector3f position_from_final_joint, Eigen::Matrix3f orientation_from_final_joint)
    {
      tool_type_ = tool_type;
      position_from_final_joint_ = position_from_final_joint;
      orientation_from_final_joint_ = orientation_from_final_joint;
    }

    Eigen::Vector3f Tool::getRelativePosition()
    {
      return position_from_final_joint_;
    }

    Eigen::Matrix3f Tool::getRlativeOrientation()
    {
      return orientation_from_final_joint_;
    }

    Pose Tool::getRelativePose()
    {
      Pose temp;
      temp.position = position_from_final_joint_;
      temp.orientation = orientation_from_final_joint;
      return temp;
    }

    void Tool::setPosition(Eigen::Vector3f position)
    {
      position_ = position;
    }

    void Tool::setOrientation(Eigen::Matrix3f orientation)
    {
      orientation_ = orientation;
    }

    Eigen::Vector3f Tool::getPosition()
    {
      return position_;
    }

    Eigen::Matrix3f Tool::getOrientation()
    {
      return orientation_;
    }

    Pose Tool::getPose()
    {
      Pose tool_pose;
      tool_pose.position = position_;
      tool_pose.orientation = orientation_;
      return tool_pose;
    }



