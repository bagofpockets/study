// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include "File_handler.h"

int main()
{
	File_handler a("3MBA_N.STP");

	a.print_data("SPHERICAL_SURFACE");
	a.print_data("B_SPLINE_SURFACE");
	a.print_data("CONICAL_SURFACE");
	a.print_data("TOROIDAL_SURFACE");
	a.print_data("CYLINDRICAL_SURFACE");

	std::cout << "runtime = " << clock() / 1000.0 << std::endl;
	return 0;
}