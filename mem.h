#pragma once
#include <Windows.h>

void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);

