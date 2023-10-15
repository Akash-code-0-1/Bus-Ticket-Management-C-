#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int counter = 0;
string buses[100][100];

class BusInfo
{
public:
    string busNumber;
    string busName;
    string startTime;
    int capacity;

    BusInfo *next;

    BusInfo(string number, string name, string time, int cap)
        : busNumber(number), busName(name), startTime(time), capacity(cap), next(nullptr) {}
};

class BookTicket
{
public:
    string passengerName;
    string passengerPhoneNumber;
    string passengerEmail;
    string passengerStartLocation;
    string passengerDestination;
    float ticketCost;
    string seatNumber;
    string busStrtTime;

    BookTicket(string name, string phone, string email, string startLoc, string destination, float cost, string seat, string startTime)
        : passengerName(name), passengerPhoneNumber(phone), passengerEmail(email), passengerStartLocation(startLoc),
          passengerDestination(destination), ticketCost(cost), seatNumber(seat), busStrtTime(startTime) {}
};

void addBus(BusInfo *&head, string busNumber, string busName, string startTime, int capacity)
{
    BusInfo *newBus = new BusInfo(busNumber, busName, startTime, capacity);
    if (!head)
    {
        head = newBus;
    }
    else
    {
        BusInfo *current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newBus;
    }
    cout << "\n\n         Bus added successfully." << endl;

    char seatLabel = 'S';

    for (int j = 0; j < capacity; j++)
    {
        buses[counter][j] = seatLabel + to_string(j + 1);
    }

    counter++;
}
/* without use of color

void showAvailableSeat(int capacity, int busIndex)
{
    cout << "Seat Availability:\n\n";
    for (int j = 0, i = 1; j < capacity; j++, i++)
    {
        if (i == 5)
        {
            cout << endl;
            i = 1;
        }
        if (i == 3)
        {
            cout << "      ";
        }
        cout << setw(4) << buses[busIndex][j] << " ";
    }
    cout << endl;
}
*/

void showAvailableSeat(int capacity, int busIndex)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "Seat Availability:\n\n";
    for (int j = 0, i = 1; j < capacity; j++, i++)
    {
        if (i == 5)
        {
            cout << endl;
            i = 1;
        }
        if (i == 3)
        {
            cout << "      ";
        }

        // Check if the seat value is " X " and set text color to red
        if (buses[busIndex][j] == " X ")
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        }
        else
        {
            // Reset text color to default (white) for other seats
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }

        // Print the seat value with proper formatting
        cout << setw(4) << buses[busIndex][j] << " ";
    }

    // Reset text color to default after all seats are printed
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    cout << endl;
}

void updateBusSeat(string seatNumber, int capacity, int busIndex)
{

    for (int j = 0; j < capacity; j++)
    {
        if (buses[busIndex][j] == seatNumber)
        {
            buses[busIndex][j] = " X ";
            break;
        }
    }
}

void showBusDetails(BusInfo *head)
{
    if (!head)
    {
        cout << "No buses available." << endl;
        return;
    }

    cout << "Bus Details:\n\n";
    BusInfo *current = head;
    cout << "||Bus Number||      ||Bus Name||        ||Bus Capacity||      ||Bus Start Time||\n\n";
    while (current)
    {
        cout << "   " << current->busNumber << "                  " << current->busName << "                  " << current->capacity << "                   " << current->startTime << endl;
        current = current->next;
    }
}

int convertStartTimeToInt(const string &startTime)
{
    int hours = stoi(startTime.substr(0, 2));
    int minutes = stoi(startTime.substr(3, 2));
    return hours * 100 + minutes;
}

void searchBusesByStartTime(BusInfo *head, const string &searchTime)
{
    int searchTimeInt = convertStartTimeToInt(searchTime);
    BusInfo *current = head;
    bool found = false;
    cout << "        Your Search Bus Inforamtion: \n\n";

    cout << "||Bus Number||      ||Bus Name||        ||Available Seat||      ||Bus Start Time||\n\n";

    while (current)
    {
        int startTimeInt = convertStartTimeToInt(current->startTime);
        if (startTimeInt == searchTimeInt)
        {
            cout << "   " << current->busNumber << "                  " << current->busName << "                  " << current->capacity << "                   " << current->startTime << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "No buses found with the specified starting time." << endl;
    }
}

void bookTicket(vector<BookTicket> &bookings, BusInfo *busList)
{
    string busNumber;
    cout << "Enter Bus Number for Booking: ";
    cin >> busNumber;

    BusInfo *currentBus = busList;
    int busIndex = 0;

    while (currentBus)
    {
        if (currentBus->busNumber == busNumber)
        {
            showAvailableSeat(currentBus->capacity, busIndex);

            if (currentBus->capacity > 0)
            {
                string passengerName, passengerPhoneNumber, passengerEmail, passengerStartLocation, passengerDestination, seatNumber;
                float ticketCost;

                cout << "         Enter Details of Passenger:\n";

                cout << "\nEnter Passenger Name: ";
                cin >> passengerName;
                cout << "Enter Passenger Phone Number: ";
                cin >> passengerPhoneNumber;
                cout << "Enter Passenger Email: ";
                cin >> passengerEmail;
                cout << "Enter Passenger Starting Location: ";
                cin >> passengerStartLocation;
                cout << "Enter Passenger Destination: ";
                cin >> passengerDestination;
                cout << "Enter Ticket Cost: ";
                cin >> ticketCost;
                cout << "Enter Seat Number: ";
                cin >> seatNumber;

                updateBusSeat(seatNumber, currentBus->capacity, busIndex);

                // Create a booking
                BookTicket booking(passengerName, passengerPhoneNumber, passengerEmail, passengerStartLocation, passengerDestination, ticketCost, seatNumber, currentBus->startTime);

                // Add the booking to the vector
                bookings.push_back(booking);

                // Reduce available seats
                currentBus->capacity--;

                cout << "\n\nTicket booked successfully for " << passengerName << ". Seat Number: " << seatNumber << endl;
            }
            else
            {
                cout << "\n\nSorry, no available seats for this bus." << endl;
            }
            return;
        }
        currentBus = currentBus->next;
        busIndex++;
    }

    cout << "\nBus with number " << busNumber << " not found." << endl;
}

void searchAndShowBookedBusDetails(const vector<BookTicket> &bookings, const string &busStrtTime)
{
    cout << "Booked Bus Details for Bus At  " << busStrtTime << ":\n\n";
    cout << "||Passenger Name||      ||Phone Number||              ||Email||            ||Seat Number||        ||Start Time||       ||      From    ||     ||    Destination  ||\n\n";

    bool found = false;
    for (const BookTicket &booking : bookings)
    {
        if (booking.busStrtTime == busStrtTime)
        {
            cout << "    " << booking.passengerName << "                  " << booking.passengerPhoneNumber << "                "
                 << booking.passengerEmail << "                 " << booking.seatNumber << "                  " << booking.busStrtTime << "                " << booking.passengerStartLocation << "                   " << booking.passengerDestination << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No bookings found for Bus Number " << busStrtTime << "." << endl;
    }
}

void updateBusInfo(BusInfo *busList, const string &busNumber)
{
    BusInfo *currentBus = busList;
    while (currentBus)
    {
        if (currentBus->busNumber == busNumber)
        {
            string updatedBusName, updatedStartTime, updatedBusNumber;
            int updatedCapacity;

            cout << "     Enter Updated Information:\n\n";

            cout << "Enter updated Bus Name: ";
            cin >> updatedBusName;
            cout << "Enter updated Capacity: ";
            cin >> updatedCapacity;
            cout << "Enter updated Start Time: ";
            cin >> updatedStartTime;

            // Updating bus information
            currentBus->busName = updatedBusName;
            currentBus->capacity = updatedCapacity;
            currentBus->startTime = updatedStartTime;

            cout << "\n\nBus information updated successfully." << endl;
            return;
        }
        currentBus = currentBus->next;
    }

    cout << "\n\nBus with number " << busNumber << " not found." << endl;
}

void updateTicketInfo(vector<BookTicket> &bookings, const string &CheckbusStrtTime, const string &CheckpassengerPhoneNumber)
{

    for (BookTicket &booking : bookings)
    {
        if (booking.passengerPhoneNumber == CheckpassengerPhoneNumber && booking.busStrtTime == CheckbusStrtTime)
        {
            string updatedPhoneNumber, updatedEmail, updatedPassengerName, updatedStartLocation, updatedDestination, updatedSeatNumber;
            int updatedTicketCost;
            cout << "        Enter Updated Information:\n\n";

            cout << "Enter Passenger Name: ";
            cin >> updatedPassengerName;
            cout << "Enter updated Phone Number: ";
            cin >> updatedPhoneNumber;
            cout << "Enter updated Email: ";
            cin >> updatedEmail;
            cout << "Enter Updated Passenger Starting Location: ";
            cin >> updatedStartLocation;
            cout << "Enter Updated Passenger Destination: ";
            cin >> updatedDestination;
            cout << "Enter Updated Ticket Cost: ";
            cin >> updatedTicketCost;
            cout << "Enter Updated Seat Number: ";
            cin >> updatedSeatNumber;

            // Updating ticket information
            booking.passengerName = updatedPassengerName;
            booking.passengerPhoneNumber = updatedPhoneNumber;
            booking.passengerEmail = updatedEmail;
            booking.passengerStartLocation = updatedStartLocation;
            booking.passengerDestination = updatedDestination;
            booking.ticketCost = updatedTicketCost;
            booking.seatNumber = updatedSeatNumber;

            cout << "Ticket information updated successfully." << endl;
            return;
        }
    }

    cout << "No booking found for passenger: " << CheckpassengerPhoneNumber << endl;
}

void shutdownBus(BusInfo *&busList, const string &busNumber)
{
    BusInfo *currentBus = busList;
    BusInfo *prevBus = nullptr;

    while (currentBus)
    {
        if (currentBus->busNumber == busNumber)
        {
            if (prevBus)
            {
                prevBus->next = currentBus->next;
                delete currentBus;
            }
            else
            {
                busList = currentBus->next;
                delete currentBus;
            }

            cout << "\n\nBus " << busNumber << " is Removed!" << endl;
            return;
        }
        prevBus = currentBus;
        currentBus = currentBus->next;
    }

    cout << "\n\nBus " << busNumber << " is not found." << endl;
}

void cancelBookedTicket(vector<BookTicket> &bookings, BusInfo *busList, const string &busStrtTime, const string &passengerName, const string &seatNumber)
{
    auto it = bookings.begin();
    while (it != bookings.end())
    {
        if (it->busStrtTime == busStrtTime && it->passengerName == passengerName && it->seatNumber == seatNumber)
        {
            // Find the corresponding bus based on busStrtTime
            BusInfo *currentBus = busList;
            while (currentBus)
            {
                if (currentBus->startTime == busStrtTime)
                {
                    // Increase the capacity of the corresponding bus
                    currentBus->capacity++;

                    // Erase the booking from the vector and update the iterator
                    it = bookings.erase(it);

                    cout << "\n\nTicket for passenger " << passengerName << " with seat " << seatNumber << " on bus " << busStrtTime << " has been canceled." << endl;
                    return;
                }
                currentBus = currentBus->next;
            }
        }
        else
        {
            ++it; // Move to the next booking if not a match
        }
    }

    cout << "\n\nNo matching booking found for passenger: " << passengerName << " and seat: " << seatNumber << " on bus " << busStrtTime << endl;
}

int main()
{
    BusInfo *busList = nullptr;
    vector<BookTicket> bookings;
    int choice;
    string busStrtTime;
    string busToUpdate;
    string passengerPhoneNumberToUpdate;
    string busToShutdown;
    string passengerName;
    string seatNumber;

    while (true)
    {
        cout << "\n----------------------------   Menu  ---------------------------------\n";
        cout << "|                1. Add Bus                                          |\n";
        cout << "|                2. Show Bus Details                                 |\n";
        cout << "|                3. Search Bus                                       |\n";
        cout << "|                4. Book Ticket                                      |\n";
        cout << "|                5. Search & Show Booked Bus Information             |\n";
        cout << "|                6. Update Bus Information                           |\n";
        cout << "|                7. Update Ticket Information                        |\n";
        cout << "|                8. Shutdown Bus                                     |\n";
        cout << "|                9. Cancel Booked Ticket                             |\n";
        cout << "|                10. Exit                                            |\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "                 Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            cout << "              Add Bus\n\n";
            cout << "Please Add Your Bus Information to Add New Bus\n";
            string busNumber, busName, startTime;
            int capacity;
            cout << "Enter Bus Number: ";
            cin >> busNumber;
            cout << "Enter Bus Name: ";
            cin >> busName;
            cout << "Enter Bus Starting Time (HH:MM): ";
            cin >> startTime;
            cout << "Enter Bus Capacity: ";
            cin >> capacity;
            addBus(busList, busNumber, busName, startTime, capacity);
            break;
        }
        case 2:
            system("cls");
            cout << "              Show Bus Details\n\n";
            showBusDetails(busList);
            break;
        case 3:
        {
            system("cls");
            cout << "           Search Bus By Time   \n\n";
            string searchTime;
            cout << "Enter Starting Time to Search (HH:MM): ";
            cin >> searchTime;
            searchBusesByStartTime(busList, searchTime);
            break;
        }
        case 4:
            system("cls");
            cout << "           Book Ticket\n\n";
            bookTicket(bookings, busList);
            break;
        case 5:
            system("cls");
            cout << "       Booked Bus Details    \n\n";
            cout << "Enter Bus start time: ";
            cin >> busStrtTime;
            searchAndShowBookedBusDetails(bookings, busStrtTime);
            break;
        case 6:
            system("cls");
            cout << "Enter Bus Number to update: ";
            cin >> busToUpdate;
            updateBusInfo(busList, busToUpdate);
            break;
        case 7:
            system("cls");
            cout << "         Update Ticket Information:\n\n";
            cout << "Enter Bus Start Time to update: ";
            cin >> busStrtTime;
            cout << "Enter Passenger Phone Number to update: ";
            cin >> passengerPhoneNumberToUpdate;
            updateTicketInfo(bookings, busStrtTime, passengerPhoneNumberToUpdate);
            break;
        case 8:
            system("cls");
            cout << "         Delete Bus           \n\n";
            cout << "Enter Bus Number to shut down: ";
            cin >> busToShutdown;
            shutdownBus(busList, busToShutdown);
            break;
        case 9:
            system("cls");
            cout << "        Cancel Booked Ticket     \n\n";
            cout << "Enter Bus Start Time: ";
            cin >> busStrtTime;
            cout << "Enter Passenger Name to cancel ticket: ";
            cin >> passengerName;
            cout << "Enter Seat Number to cancel ticket: ";
            cin >> seatNumber;
            cancelBookedTicket(bookings, busList, busStrtTime, passengerName, seatNumber);
            break;
        case 10:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "\n\nInvalid choice. Please try again." << endl;
        }
    }
}
