//
// Created by mm on 23-3-17.
//
// Library common
#include <iostream>
#include <fstream>

// Library Eigen3
#include <Eigen/Core>
#include <Eigen/Dense>

#include <yaml-cpp/yaml.h>





Eigen::Vector3f roll_pitch_yaw_rad ;
Eigen::Vector3f roll_pitch_yaw_cali_rad ;


Eigen::Vector3f roll_pitch_yaw_deg ;
Eigen::Vector3f roll_pitch_yaw_cali_deg ;

Eigen::Vector3f roll_pitch_yaw_delta_deg ;

Eigen::Vector3f r_s2b;
Eigen::Vector3f r_s2b_cali ;

Eigen::Matrix3f rotation_matrix;
Eigen::Matrix3f rotation_matrix_cali;

Eigen::AngleAxisf rotation_vector ;
Eigen::AngleAxisf rotation_vector_cali ;

int main(int argc, char **argv) {

    //TODO read yaml vec
    YAML::Node config = YAML::LoadFile("../../file/radar_front.yaml");
    r_s2b  << config["r_s2b"][0].as<float>() , config["r_s2b"][1].as<float>() , config["r_s2b"][2].as<float>();
    std::cout <<"r_s2b = "<< r_s2b.transpose() <<std::endl;
    //FIXME write yaml
    //ING_ING sdd



//    std::cout <<"config = "<< config.size() <<std::endl;
//    std::ofstream fout("../../file/radar_front_cali.yaml");
//    fout << config <<std::endl;
//    fout.close();






    // read a r_vec
    r_s2b << 3.1415926, 0, 0;
    std::cout<< " r_s2b: " << r_s2b.transpose() <<std::endl;

    // r_vec -> rotation_vec
    Eigen::AngleAxisf rotation_vec (r_s2b.norm(), Eigen::Vector3f(r_s2b / r_s2b.norm()));
    rotation_matrix = rotation_vec.matrix();

    // rotation_vec -> rotation_matrix
    std::cout<< " rotation_matrix\n " << rotation_matrix<<std::endl;


    // rotation_matrix -> rpy(roll, pitch, ywa)
    //roll_pitch_yaw_rad << 1,2,3;

    roll_pitch_yaw_rad = rotation_matrix.eulerAngles(0,1,2);
    roll_pitch_yaw_deg = roll_pitch_yaw_rad*180/M_PI ;

    //calib_rpy

    roll_pitch_yaw_delta_deg << 0,0,0;
    roll_pitch_yaw_cali_deg = roll_pitch_yaw_deg + roll_pitch_yaw_delta_deg;

    roll_pitch_yaw_cali_rad = roll_pitch_yaw_cali_deg*M_PI/180;

    std::cout<<"Before Cali: " << roll_pitch_yaw_deg.transpose() <<std::endl;
    std::cout<<"Cali Offset: "<<roll_pitch_yaw_delta_deg.transpose() <<std::endl;
    std::cout<<"After Cali: " <<roll_pitch_yaw_cali_deg.transpose() <<std::endl;

    // calib_rpy -> rotation_vec
    Eigen::AngleAxisf roll_angle(roll_pitch_yaw_cali_rad(0), Eigen::Vector3f::UnitX());
    Eigen::AngleAxisf pitch_angle(roll_pitch_yaw_cali_rad(1), Eigen::Vector3f::UnitY());
    Eigen::AngleAxisf yaw_angle(roll_pitch_yaw_cali_rad(2), Eigen::Vector3f::UnitZ());
    rotation_vector_cali  = roll_angle * pitch_angle * yaw_angle;

    // rotation_vec-> rotation_matrix

    rotation_matrix_cali = rotation_vector_cali.matrix() ;
    std::cout<<"rotation_matrix_cali:\n " <<rotation_matrix_cali <<std::endl;

    // rotation_vec-> r_s2b_cali
    std:: cout << " r_s2b_cali is: " << rotation_vector_cali.angle() * rotation_vector_cali.axis().transpose() <<std:: endl;





  }