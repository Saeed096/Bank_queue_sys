#include <iostream>
#include "LinkedList.h"
#include "Client.h"
#include "Teller.h"
#include "Bank.h"
#include <queue>
#include <windows.h>


using namespace std;

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}


int main()
{
    SetColor(8);
    cout << "\n\t\t\t\t\t\t\t\tBQM System\n\n\n\n\n";
    SetColor(15);
    int clientsNum;
    SetColor(8);
    cout << "enter clients num \n";
    SetColor(15);
    cin >> clientsNum;
    cout << "-----------------" << endl << endl;
    LinkedList<Client> clientsList;


    for (int i = 0; i < clientsNum; i++)
    {
        Client client;
        SetColor(8);
        cout << "enter client no. " << i + 1 << " name" << endl;
        SetColor(15);
        cin >> client.name;

        char c;
        SetColor(8);
        cout << "Is client no. " << i + 1 << " a VIP client? \t y-n" << endl;
        SetColor(15);
        cin >> c;


        if (c == 'y' || c == 'Y')
        {
            client.isVip = true;
        }
        SetColor(8);
        cout << "enter arrival time for client no. " << i + 1 << endl;
        SetColor(15);
        cin >> client.arrival_time;

        SetColor(8);
        cout << "enter service time for client no. " << i + 1 << endl;
        SetColor(15);
        cin >> client.service_duration;

        cout << "-----------------\n" << endl;

        clientsList.Add(client);

    }

    Bank b(clientsNum);
    b.arrangeQueue(clientsList);
    b.assignClientsToTellers();
    b.showStatistics();
}
