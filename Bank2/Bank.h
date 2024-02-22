#pragma once
#include "Teller.h"
#include <queue> 
#include "Client.h"
#include <cmath>
#include <windows.h>

using namespace std;



class Bank
{
private:
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

	LinkedList <Teller> tellersList;
	int tellersNum;
	queue<Client> clientsQueue;
	float totalWaitingTime = 0;
	float totalServiceTime = 0;
	int counter = 0;

	void vipSort(LinkedList<Client>* l)
	{
		Node <Client>* temp = l->head;
		if (temp == NULL)
			return;

		while (temp->Next != NULL)
		{
			if (temp->c.isVip == false && temp->Next->c.isVip == true)   
			{
				Node <Client>* premClient = temp->Next;
				while (premClient->Prev != NULL && premClient->Prev->c.isVip == false && premClient->c.arrival_time <= premClient->Prev->c.arrival_time + premClient->Prev->c.waiting_time)
				{
					l->Swap(premClient, premClient->Prev);
					premClient = premClient->Prev;
				}
			}
			temp = temp->Next;
		}

	}

	void calcMinWaitingTime(LinkedList<Client>* l)
	{
		Node <Client>* temp = l->head;

		Node <Teller>* tellerTemp = tellersList.head;
		while (temp != NULL)
		{
			tellerTemp = tellersList.head;       
			while (tellerTemp != NULL)
			{
				if (tellerTemp->c.lastCompletedService <= temp->c.arrival_time)
				{
					temp->c.waiting_time = 0;
					temp->c.leave_time = temp->c.arrival_time + temp->c.service_duration;
					tellerTemp->c.lastCompletedService = temp->c.leave_time;
					break;
				}
				tellerTemp = tellerTemp->Next;
			}

			if (tellerTemp == NULL)
			{
				tellerTemp = tellersList.head;
				Node <Teller>* temp2 = tellersList.head;

				while (temp2 != NULL)
				{
					if (tellerTemp->c.lastCompletedService <= temp2->c.lastCompletedService)
						temp2 = temp2->Next;

					else
					{
						tellerTemp = tellerTemp->Next;
						temp2 = tellersList.head;
						continue;
					}
				}
				temp->c.waiting_time = tellerTemp->c.lastCompletedService - temp->c.arrival_time;     // teller temp >> null ptr???????????
				temp->c.leave_time = temp->c.arrival_time + temp->c.service_duration + temp->c.waiting_time;
				tellerTemp->c.lastCompletedService = temp->c.leave_time;
			}

			temp = temp->Next;
		}
		tellerTemp = tellersList.head;
		while (tellerTemp != NULL)
		{
			tellerTemp->c.lastCompletedService = 0;
			tellerTemp = tellerTemp->Next;
		}
	}

	int clientsNum;
public:

	Bank(int clientsNum)
	{
		this->clientsNum = clientsNum;           
		float x = (float)clientsNum / 3;
		tellersNum = ceil(x);
		for (int i = 0; i < tellersNum; i++)
		{
			Teller t;
			t.id = i + 1;

			tellersList.Add(t);
		}
	}


	void arrangeQueue(LinkedList<Client> l)
	{
		l.bubbleSort();
		calcMinWaitingTime(&l);
		vipSort(&l);

		while (l.head != NULL)        
		{
			clientsQueue.push(l.head->c);
			l.Remove(l.head->c);
		}
	}

	void assignClientsToTellers()
	{
		SetColor(4);
		cout << endl << "we will allocate " << tellersNum << " tellers for those " << clientsNum << " clients" << endl;
		SetColor(15);
		cout << "-----------------\n\n";
		while (!clientsQueue.empty())
		{
			Node<Teller>* temp = tellersList.head;
			while (temp != NULL)
			{
				if (temp->c.lastCompletedService <= clientsQueue.front().arrival_time)
				{
					clientsQueue.front().waiting_time = 0;
					totalWaitingTime += clientsQueue.front().waiting_time;
					totalServiceTime += clientsQueue.front().service_duration;
					clientsQueue.front().servingTellerId = temp->c.id;
					clientsQueue.front().leave_time = clientsQueue.front().arrival_time + clientsQueue.front().service_duration;
					temp->c.lastCompletedService = clientsQueue.front().leave_time;
					counter++;
					SetColor(2);
					cout << "client number " << counter << " his name is " << clientsQueue.front().name << " ,arrived at " << clientsQueue.front().arrival_time << " , served by teller num " << temp->c.id << " , his waiting time was " << clientsQueue.front().waiting_time << " and he left at " << clientsQueue.front().leave_time;

					if (clientsQueue.front().isVip == true)
						cout << "\t \"VIP Client\"" << endl;
					else
						cout << endl;

					SetColor(15);
					clientsQueue.pop();
					break;
				}
				temp = temp->Next;
			}

			if (temp == NULL)
			{
				temp = tellersList.head;
				Node <Teller>* temp2 = tellersList.head;

				while (temp2 != NULL)
				{
					if (temp->c.lastCompletedService <= temp2->c.lastCompletedService)
						temp2 = temp2->Next;

					else
					{
						temp = temp->Next;
						temp2 = tellersList.head;
						continue;
					}
				}
				clientsQueue.front().waiting_time = temp->c.lastCompletedService - clientsQueue.front().arrival_time;
				totalWaitingTime += clientsQueue.front().waiting_time;
				totalServiceTime += clientsQueue.front().service_duration;
				clientsQueue.front().servingTellerId = temp->c.id;
				clientsQueue.front().leave_time = clientsQueue.front().arrival_time + clientsQueue.front().service_duration + clientsQueue.front().waiting_time;
				temp->c.lastCompletedService = clientsQueue.front().leave_time;
				counter++;
				SetColor(2);
				cout << "client number " << counter << " his name is " << clientsQueue.front().name << " ,arrived at " << clientsQueue.front().arrival_time << " , served by teller num " << temp->c.id << " , his waiting time was " << clientsQueue.front().waiting_time << " and he left at " << clientsQueue.front().leave_time;

				if (clientsQueue.front().isVip == true)
					cout << "\t \"VIP Client\"" << endl;
				else
					cout << endl;

				SetColor(15);
				clientsQueue.pop();
			}


		}

	}

	void showStatistics()
	{
		cout << "-----------------\n";
		SetColor(2);
		cout << "\nAverage waiting time = " << totalWaitingTime / counter << endl;
		cout << "Average service time = " << totalServiceTime / counter << endl;
		SetColor(15);
		cout << "-----------------\n";
	}
};

