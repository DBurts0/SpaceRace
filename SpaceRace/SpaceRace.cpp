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

int ranNum;

int launchLocation(int num)
{
	num = rand() % 2;
	return num;
}

void intro()
{
	cout << "Welcome to the launch control room.\n";
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
		// pause for 1 second
		Sleep(1000);
		// print the current amount of seconds left in the timer
		cout << seconds << endl;
		seconds -= 1;
	}
	Sleep(1000);
}

void rocketLaunch(int i, int location)
{
	launchLocation(location);
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
	// clear the value of userText so the while loop will run the next time its called
	m.unlock();
}

int main()
{
	intro();
	srand(time(0));
	cout << "Preparing to launch all available rockets.\n";
	ranNum = 0;
	rocketLaunch(1, ranNum);
	Sleep(3000);
	cout << "Error! Main base has lost remote access to the launch controls.\n";
	cout << "Preparing to swap control to the local base.\n";
	cout << "Enter 'swap' to begin controlling the launch from the local base.\n";
	while (userText != "swap")
	{
		cin >> userText;
	}
	ranNum = 1;
	thread rocket1(rocketLaunch, 2, ranNum);
	thread rocket2(rocketLaunch, 3, ranNum);
	thread rocket3(rocketLaunch, 4, ranNum);
	thread rocket4(rocketLaunch, 5, ranNum);
	thread rocket5(rocketLaunch, 6, ranNum);
	thread rocket6(rocketLaunch, 7, ranNum);
	thread rocket7(rocketLaunch, 8, ranNum);
	thread rocket8(rocketLaunch, 9, ranNum);
	thread rocket9(rocketLaunch, 10, ranNum);


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