#include <iostream>
#include "stdafx.h"
#include "proc.h"
#include "mem.h"
#include <string>
#include <stdlib.h>

//Declares and initialises variables for later use
int newHealth{ 1337 }, originalHealth{ 100 }, newAmmo{ 1337 }, originalAmmo{ 30 };
bool bHealth{ false }, bAmmo{ false }, bRecoil{ false }, ammoStatus{ false }, healthStatus{ false }, recoilStatus{ false };

int main() {


	//Get the proccess ID For Assault Cube
	DWORD procId{ GetProcId(L"ac_client.exe") };

	//set console title
	SetConsoleTitle(L"Alythesniper's Assault Cube Trainer");

	//Get the base address of Assault Cube
	uintptr_t moduleBaseAdd{ GetModuleBaseAddress(procId, L"ac_client.exe") };


	///Create a handle to the process using the windows API
	HANDLE procHandle{ 0 };
	procHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	//Get local player's base address
	uintptr_t playerBaseAdd{ moduleBaseAdd + 0x0011E20C };

	//Get health and ammo adress
	uintptr_t healthAddress{ FindDMAAddy(procHandle, playerBaseAdd, { 0xF8 }) }, ammoAddress{ FindDMAAddy(procHandle, playerBaseAdd, { 0x374, 0x14, 0x0 }) };

	

	//checks if assault cube is open
	DWORD isOpen{ 0 };

	void print();
	print();


	while (GetExitCodeProcess(procHandle, &isOpen) && isOpen == STILL_ACTIVE) {

		if (bHealth) {
			WriteProcessMemory(procHandle, (LPVOID)healthAddress, &newHealth, sizeof(newHealth), NULL);
		};
		if (GetAsyncKeyState(VK_F1) & 1) {
			WriteProcessMemory(procHandle, (LPVOID)healthAddress, &originalHealth, sizeof(newHealth), NULL);
			bHealth = !bHealth;
			healthStatus = !healthStatus;
			print();
		};

		if (bAmmo) {
			WriteProcessMemory(procHandle, (LPVOID)ammoAddress, &newAmmo, sizeof(newAmmo), NULL);
		};
	
		if (GetAsyncKeyState(VK_F2) & 1) {
			WriteProcessMemory(procHandle, (LPVOID)ammoAddress, &originalAmmo, sizeof(newAmmo), NULL);
			bAmmo = !bAmmo;
			ammoStatus = !ammoStatus;
			print();

		};

		if (bRecoil) {
			NopEx((BYTE*)(moduleBaseAdd + 0x63786), (unsigned int)10, procHandle);
		};

		if (GetAsyncKeyState(VK_F3) & 1) {
			PatchEx((BYTE*)(moduleBaseAdd + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", (unsigned int)10, procHandle);
			bRecoil = !bRecoil;
			recoilStatus = !recoilStatus;
			print();
		};
	};


	//Prints if assault cube is not open
	system("cls");
	std::cout << "\nAssault cube not open. Exiting now..." << std::endl;
	Sleep(2500);
	std::exit;
};

void print() {
	char health{ ' ' }, ammo{ ' ' }, recoil{ ' ' };
	system("cls");
	if (healthStatus) {
		health = '*' ;
	}
	else
	{
		health = ' ' ;
	};
	if (ammoStatus) {
		ammo = '*' ;
	}
	else
	{
		ammo = ' ' ;
	};
	if (recoilStatus) {
		recoil = '*';
	}
	else
	{
		recoil = ' ';
	};
	std::cout << "Health Hack Status" << "	-->		[" << health << "]\n"
			  << "Ammo Hack Status" << "	-->		[" << ammo << "]\n"
			  << "Recoil Hack Status" << "	-->		[" << recoil << "]\n";
}	