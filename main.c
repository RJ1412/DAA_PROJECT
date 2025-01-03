#include <iostream>
#include <cstdlib>
#include "headerr.h"
#include "codes.cpp"  // Consider changing to ".h" for header functions

using namespace std;

int main() {
    welcome();
    int i;

    while (true) {
        cout << "Enter 1 for petrol stations nearby\n"
             << "Enter 2 for weather report\n"
             << "Enter 3 for transport schedule\n"
             << "Enter 4 for Dijkstra's algorithm\n"
             << "Enter 5 for toll management\n"
             << "Enter 6 for getting all data related to roads\n"
             << "Enter 7 for getting roads based on road id\n"
             << "Enter 8 to check parking slots\n"
             << "Enter 9 for data related to all traffic laws violated\n"
             << "Enter 10 to search for a vehicle\n"
             << "ENTER 11 TO FIND MINIMUM TIME REQUIRED TO COVER ALL THE PLACES\n"
             << "Enter 12 bored in traffic????\n";
        cin >> i;

        switch (i) {
            case 1:
                welcome_petrol();
                petrol_nearby();
                sort_petroll();
                print_sorted_petrol();
                break;
            case 2:
                welcome_weather();
                weather_info();
                break;
            case 3:
                welcome_transport();
                search_transport();
                break;
            case 4:
                dijikstra();
                break;
            case 5:
                tollmanagement();
                break;
            case 6:
                sorttt();
                break;
            case 7:
                bstttt();
                break;
            case 8:
                parking();
                break;
            case 9:
                queue_main();
                break;
            case 10:
                search_veh();
                break;
            case 11:
                krusgal();
                break;
            case 12:
                game();
                break;
            default:
                cout << "Wrong input" << endl;
                exit(0);
        }
    }

    return 0;
}
