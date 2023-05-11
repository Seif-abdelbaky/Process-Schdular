#include "UI.h"

UI::UI(int x)
{
	timestep = x;
}

void UI::generate_silent()
{
	cout << "Silent Mode..........., Simulation Starts ..." << endl;
}

void UI::generate(int x)
{
	cout << "Current Timestep:" << x << endl;

}

void UI::next(int mode)
{
	if (mode == 1)
	{
		cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!\n";
		cin.clear(); //this will clear any values remain in cin from prior run
		cin.ignore(1000000000, '\n');
		//cin.get();
		//system("PAUSE"); 
	}
	else
	{
		Sleep(1000);
	}
	system("CLS"); //this will clear the screen of any text from prior run



	// this ends your main function.
	return;
}

void UI::printProcessors(Processor** arr, int count)
{
	cout << "-------------- RDY processes --------------" << endl;

	for (int i = 0;i < count; i++)
	{
		if (!arr[i]->isHeated())
		{
			cout << "processor " << i + 1 << " ";
			arr[i]->printRDY();
			//cout << "USing Brute Force: " << arr[i]->TimeLeftReady() << endl;
		}
	}
}

void UI::printRunning(Processor** arr, int count)
{
	cout << "-------------- RUN processes --------------" << endl;
	int z = 0;
	for (int i = 0;i < count; i++)
	{
		if (arr[i]->isBusy())
			z++;
	}
	cout << z << " RUN:";
	int printed = 0;
	for (int i = 0; i < count; i++)
	{
		if (arr[i]->isBusy() && arr[i]->getRun())
		{

			cout << arr[i]->getRun();
			cout << "(P" << i + 1 << ")";
			if (printed + 1 != z)
			{
				cout << ", ";
			}
			printed++;
		}
	}
	cout << endl;
}
