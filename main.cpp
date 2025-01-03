#include <iostream>
#include <cstdlib>
// #include "headerr.h"
#include "codes.cpp"  // Consider changing to ".h" for header functions

using namespace std;


int main() {
    welcome();
    int i;

    while (true) {
        cout << "Enter 1 for petrol stations nearby\n"
             << "Enter 2 to find nearest bus stop\n"
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
                cout<<endl<<endl;
                break;
            case 2:
                welcome_weather();
                weather_info();
                cout<<endl<<endl;
                break;
            case 3:
                welcome_transport();
                search_transport();
                cout<<endl<<endl;
                break;
            case 4:
                dijikstra();
                cout<<endl<<endl;
                break;
            case 5:
                tollmanagement();
                cout<<endl<<endl;
                break;
            case 6:
                sorttt();
                cout<<endl<<endl;
                break;
            case 7:
                bstttt();
                cout<<endl<<endl;
                break;
            case 8:
                parking();
                cout<<endl<<endl;
                break;
            case 9:
                queue_main();
                cout<<endl<<endl;
                break;
            case 10:
                search_veh();
                cout<<endl<<endl;
                break;
            case 11:
                krusgal();
                cout<<endl<<endl;
                break;
            case 12:
                game();
                cout<<endl<<endl;
                break;
            default:
                cout << "Wrong input" << endl;
                exit(0);
        }
    }

    return 0;
}
