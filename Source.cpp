#include <iostream>
#include <string>
#include "CLIManager.h"

int main() {
	std::shared_ptr<CLIManager> c_manager = std::make_shared<CLIManager>();
	c_manager->run();
}