//
// Created by tony on 2022/10/11.
//

#include <csignal>
#include "state_machine.h"

std::shared_ptr<ackermann_planning::pnc::StateMachine> state_machine_ptr;

void sigintHandler(int sig) {
  if (state_machine_ptr) {
    state_machine_ptr->stop();
    state_machine_ptr.reset();
  }

  ROS_INFO("state machine shutting down!");
  ros::shutdown();
}

int main(int argc, char** argv) {
  ros::init(argc, argv, ackermann_planning::pnc::NODE_NAME);
  state_machine_ptr = std::make_shared<ackermann_planning::pnc::StateMachine>();
  signal(SIGINT, sigintHandler);
  state_machine_ptr->init();
  state_machine_ptr->run();
  return 0;
}
