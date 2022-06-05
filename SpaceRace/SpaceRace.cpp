// SpaceRace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>
#include <ctime>
using namespace std;

mutex m;
string userText;

void intro()
{
	// Give a brief introduction to the program
	cout << "Welcome to the launch control room.\n";
	// Pause to give the user time to read
	Sleep(3000);
	cout << "This is a very important operation as multiple rockets are expected to take off today.\n";
	Sleep(5000);
	cout << "Enter 'start' to begin the launches.\n";
	while (userText != "start")
	{
		cin >> userText;
	}
}

void timer(int seconds)
{
	for (int s = -1; s <= seconds; s++)
	{
		
		// print the current amount of seconds left in the timer
		cout << seconds << endl;
		seconds -= 1;
		// pause for 1 second
		Sleep(1000);
	}
}

void rocketLaunch(int i, int location)
{
	// Only allow one thread at a time to execute the function
	m.lock();
	if (location == 0)
	{
		cout << "The main base is preparing remotely launch rocket #" << this_thread::get_id() << " on pad " << i << endl;
	}
	else if (location == 1)
	{
		cout << "The local base is preparing launch rocket #" << this_thread::get_id() << " on pad " << i << endl;
	}
	// countdown from 3 seconds
	timer(3);
	cout << "Launched!\n";
	// Unlock so the next thread can access the function
	m.unlock();
}

int main()
{
	intro();
	cout << "Preparing to launch all available rockets.\n";
	// Launch a rocket from the main thread
	rocketLaunch(1, 0);
	Sleep(3000);
	
	cout << "Error! Main base has lost remote access to the launch controls.\n";
	cout << "Preparing to swap control to the local base.\n";
	cout << "Enter 'swap' to begin controlling the launch from the local base.\n";
	while (userText != "swap")
	{
		cin >> userText;
	}
	// Begin launching rockets from the child threads
	thread rocket1(rocketLaunch, 2, 1);
	thread rocket2(rocketLaunch, 3, 1);
	thread rocket3(rocketLaunch, 4, 1);
	thread rocket4(rocketLaunch, 5, 1);
	thread rocket5(rocketLaunch, 6, 1);
	thread rocket6(rocketLaunch, 7, 1);
	thread rocket7(rocketLaunch, 8, 1);
	thread rocket8(rocketLaunch, 9, 1);
	thread rocket9(rocketLaunch, 10, 1);

	// Wait for each thread to finish before continuing
	rocket9.join();
	rocket8.join();
	rocket7.join();
	rocket6.join();
	rocket5.join();
	rocket4.join();
	rocket3.join();
	rocket2.join();
	rocket1.join();


	cout << "All rockets are airborne!\n";
}