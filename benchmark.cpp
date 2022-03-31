#include <iostream>
#include <chrono>

#include "tests.h"

#define CLOCKTIME_NOW std::chrono::high_resolution_clock::now()
#define DURATION(begin, end) std::chrono::duration_cast<std::chrono::milliseconds>((end) - (begin)).count()

void printhelpManual() 
{
	std::cout << "\n--------------------------------------------------------------------------------\n";
	std::cout << "     C++ RUNTIME BENCHMARK TEST     ::     Diagnostic Tool by bootsareme\n";
	std::cout << "--------------------------------------------------------------------------------\n\n";
	std::cout << "This diagnostic tool will calculate your computer's execution speed. "
					"It will perform a series of 5 tests in ascending difficulty and return"
					"the results of each test in milliseconds. This diagnostic tool will only"
					" calculate your computer's runtime speed as compilation speed will vary between software. "
					"At the end of the diagnostic, this program will give you a CPU & Memory Health Score. "
					"The score is meant for diagnostic purposes and SHOULD NOT SUBSITUTE FOR PROFESSIONAL ADVICE. "
					"This program MUST be executed via a CLI (see below for CLI options).\n\n";
	std::cout << "::\n:: Command Line Options :   benchmark.exe --start\n::\n"
					"                                 /help :: Opens this help manual.\n"
					"                             /parallel :: Enables use of multiple logical cores on the processor (if supported). \n";
}

int main(/*const int argc, char* argv[]*/)
{
    //if (argv[1] == std::string("/help")) 
    {
        printhelpManual();
    //    return 0;
    }

    const bool useAllCores = false;//argv[1] == std::string("/parallel");
    std::string modeStr = "Single Threaded";

    if (useAllCores)
        modeStr = "Multithreaded";

    printhelpManual();
    std::cout << "\n===========================\n";
    std::cout << "   DETECTED SYSTEM SPECS\n";
    std::cout << "===========================\n";
    system("systeminfo");
    std::cout << "\n\n==============================\n";
    std::cout << "   RUNNING DIAGNOSTIC TESTS\n==============================\n\n";

    ///////////////////////////     BEGIN DIAGNOSTICS       /////////////////////////////////////////////////////

    const auto startI = CLOCKTIME_NOW;

    

    const auto stopI = CLOCKTIME_NOW;
    std::cout << "TEST I -       Integer Operations (" + modeStr + ") :  " << DURATION(startI, stopI) << " ms\n";


    const auto startII = CLOCKTIME_NOW;
    // vector i/o
    const auto stopII = CLOCKTIME_NOW;
    std::cout << "TEST II - Array Searching & Sorting  (" + modeStr + ") :  " << DURATION(startII, stopII) << " ms\n";

    const auto startIII = CLOCKTIME_NOW;
    // parallel multithreading -- subject to change
    const auto stopIII = CLOCKTIME_NOW;
    std::cout << "TEST III - Console I/O String Stream  (" + modeStr + ") :  " << DURATION(startIII, stopIII) << " ms\n";

    const auto startIV = CLOCKTIME_NOW;
    Tests::prime(useAllCores);
    const auto stopIV = CLOCKTIME_NOW;
    std::cout << "TEST IV - Prime Number Generation (" + modeStr + ") :  " << DURATION(startIV, stopIV) << " ms\n";


    const auto startV = CLOCKTIME_NOW;
    Tests::matrix_operations(useAllCores);
    const auto stopV = CLOCKTIME_NOW;
    std::cout << "TEST V - Complex Matrix Transforms (" + modeStr + ") :  " << DURATION(startV, stopV) << " ms\n";

    //////////////////////////////////  END DIAGNOSTICS    /////////////////////////////////////////////////////////


    std::string decision;
    const auto total = DURATION(startI, stopI) + DURATION(startII, stopII)
		+ DURATION(startIII, stopIII) + DURATION(startIV, stopIV) + DURATION(startV, stopV);

    if (total <= 1000)
        decision = "Excellent";
    else if (total <= 5000)
        decision = "Good";
    else if (total <= 9999)
        decision = "Fair";
    else
        decision = "Poor";

    std::cout << "\n=======================\n";
    std::cout << "   BENCHMARK RESULTS\n";
    std::cout << "=======================\n\n";
    std::cout << " Total Diagnosis Time  :  " << total << " ms\n";
    std::cout << "  Average Test Length  :  " << total / 5 << " ms\n";
    std::cout << "CPU and Memory Health  :  " << decision;
    std::cout << "\n\n====================\n";
    std::cout << "   CPU & RAM INFO\n";
    std::cout << "====================\n\n";
    system("wmic cpu get name, currentclockspeed, currentvoltage");
    system("wmic memorychip get capacity, speed, memorytype, name");
}