#include <iostream>

#include "Testing\Sandbox.cpp"
#include "Testing\UnitTests.cpp"

int main(int argc, char *argv[])
{
	using namespace gnl;

	UnitTests *tests = new UnitTests();
	tests->runAllTests();

	//Sandbox *app = new Sandbox();
	//app->run();
}