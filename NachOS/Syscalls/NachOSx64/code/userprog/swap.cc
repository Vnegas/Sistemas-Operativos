#include "swap.h"
#include <iostream>

Swap::Swap(int sizeSwap) {
  this->oldPage = 0;
  this->size = sizeSwap;
  this->swapMap = new BitMap(sizeSwap);
  this->swapFile = nullptr;
  this->space = nullptr;
  this->machine = nullptr;
}

Swap::~Swap() {
  delete swapMap;
  this->size = 0;
  this->oldPage = 0;
  this->swapFile = nullptr;
  this->space = nullptr;
  this->machine = nullptr;
}

int Swap::findPageToSwap() {
  // Use this->oldPage to keep track of the page to replace
  for (int i = oldPage; i < this->size; i++) {
    // Validate is valid (in main memory) and dirty (has been modified)
    if (this->space->getPageTable()[i].valid) {
      this->oldPage = i;
      return this->space->getPageTable()[i].virtualPage;
    }
  }

  for (int i = 0; i < oldPage; i++) {
    // Validate is valid (in main memory) and dirty (has been modified)
    if (this->space->getPageTable()[i].valid) {
      this->oldPage = i;
      return this->space->getPageTable()[i].virtualPage;
    }
  }

  return -1;
}

int Swap::findFreePageInSwap() {
  return swapMap->Find();
}

void Swap::movePageToSwap(int vpn, int ppn) {
  int freePageInSwap = this->findFreePageInSwap();
  if (-1 == freePageInSwap) {
    std::cout << "No free page in swap\n";
    ASSERT(false);
  }
  //  Validate the page to move is valid (in main memory) and dirty (has been modified)
  // Write the page to the swap
  this->swapFile->WriteAt(&(machine->mainMemory[ppn * PageSize]), PageSize, freePageInSwap * PageSize);
  // Update the page table
  this->space->getPageTable()[vpn].valid = false;
  this->space->getPageTable()[vpn].physicalPage = freePageInSwap;
  this->space->getPageTable()[vpn].dirty = true;
  // Update the swap map
  this->swapMap->Mark(freePageInSwap);
}

void Swap::movePageToMainMemory(int vpn, int frame) {
  // Page is in the swap and is dirty

  // Read the page from the swap
  this->swapFile->ReadAt(&(machine->mainMemory[frame * PageSize]), 
    PageSize, 
    this->space->getPageTable()[vpn].physicalPage * PageSize);
  
  // Say in the swap File this position is free
  this->swapMap->Clear(this->space->getPageTable()[vpn].physicalPage);
  // Update the page table
  this->space->getPageTable()[vpn].valid = true;
  this->space->getPageTable()[vpn].physicalPage = frame;
  this->space->getPageTable()[vpn].virtualPage = vpn;
  this->space->getPageTable()[vpn].dirty = true; // The page is dirty because it has been modified
}
