/*
#include "defragmenter.h"
#include "DefragRunner.h"
#include "QuadraticProbing.h"
#include "mynew.h"


Defragmenter::Defragmenter(DiskDrive *diskDrive)
{
    int fileNum = diskDrive->getNumFiles(); // get num files
    int capacity = diskDrive->getCapacity() - 1;
    int const arraySize = 12000;
    int arrayCount = 0;
    int emptySpace = -1;// needs new one
    int emptyRam = -1; // needs new one
    int index = 2; // b/c positions 0 and 1 are reserved
    DiskBlock* fragment = NULL; // to store the fragments
    DiskBlock* temp = NULL;  // to move things around after deletion
    DiskBlock** storeInRAM;//Array in RAM
    storeInRAM = new DiskBlock*[arraySize];
    QuadraticHashTable<int>* hashLoc; //Hash Table to store new Loc on Disk
    hashLoc = new QuadraticHashTable<int>(-1, 200000);
    //hacatshLoc->printSize();
    
    
    int blah = capacity;
    while (diskDrive->FAT[blah]) blah--;
    emptySpace = blah; // first empty from back
    
    
    for (int i = 0; i < fileNum; i++)
    {
        int blockID = diskDrive->directory[i].getFirstBlockID();
        // once done try comenting that out and see what happens
        if (blockID == diskDrive->directory[i].getFirstBlockID()) // so the directory knows where the new file starts
        {
            diskDrive->directory[i].setFirstBlockID(index);
        }
        
        while (blockID != 1)
        {
            if (emptySpace == -1)
            {
                int i = capacity;
                while (diskDrive->FAT[i]) i--;
                emptySpace = i; // first empty from back
            }
            
            //if (index == 10)
            //{
              //  cout << " Help " << endl;
            //}
            //*****************************************************
            //                  READ
            //*****************************************************
            
            if (index <= blockID) // it hasn't been moved so read it from disk
            {
                fragment = diskDrive->readDiskBlock(blockID);
                diskDrive->FAT[blockID] = false; // maintins FAT table
            }
            else // fragment has been moved, read it from hash
            {
                int newLoc = hashLoc->find(blockID);
                
                if (newLoc <= 0) // stored in RAM array
                {
                    int dummy = -1 * (newLoc);
                    fragment = storeInRAM[dummy];
                    storeInRAM[dummy] = NULL; // make empty
                    emptyRam = newLoc;
                }
                else // stored on disk
                {
                    hashLoc->remove(blockID);
                    while (hashLoc->find(newLoc) != (-1))
                    {
                        newLoc = hashLoc->find(newLoc);
                        hashLoc->remove(newLoc);
                    }
                    fragment = diskDrive->readDiskBlock(newLoc);
                    diskDrive->FAT[newLoc] = false;
                }
            }
            
            
            //*****************************************************
            //                  WRITE
            //*****************************************************
            
            //cout << " I got here" << index << endl;
            
            if (blockID == index) //if the fragment is on proper spot by chance go to the next one
            {
                blockID = fragment->getNext();
            }
            else // if the fragment is not on the proper spot write on the index
            {
                
                if (diskDrive->FAT[index]) // if occupied
                {
                    temp = diskDrive->readDiskBlock(index);
                    int oldLoc = index;
                    int newLoc;
                    if (arrayCount < arraySize || (emptyRam =!-1))// if RAM array has space
                    {
                        
                        if (arrayCount < arraySize)
                        {
                            newLoc = -arrayCount;
                            storeInRAM[arrayCount] = temp;
                            arrayCount++;
                        }
                        else if (emptyRam = !- 1)// fix empty spaces in ram to minimize disk accesess
                        {
                            newLoc = -emptyRam; // negative to differ
                            storeInRAM[emptyRam] = temp;
                            delete temp;
                            emptyRam = -1;// used needs new empty space
                        }
                    }
                    else // if Ram array full get space from disk stack
                    {
                        newLoc = emptySpace;
                        diskDrive->writeDiskBlock(temp, newLoc);
                        delete temp;
                        diskDrive->FAT[newLoc] = true;
                        emptySpace = -1; // used needs new empty space
                    }
                    
                    diskDrive->writeDiskBlock(fragment, index);
                    hashLoc->insert(oldLoc, newLoc); // stores the location
                }
                else // empty
                {
                    diskDrive->writeDiskBlock(fragment, index);
                }
                blockID = fragment->getNext();
            }
            index++; // go to next spot
            delete fragment;
        }
    }
} // Defragmenter()
*/

#include "defragmenter.h"
#include "DefragRunner.h"
#include "QuadraticProbing.h"
#include "mynew.h"


Defragmenter::Defragmenter(DiskDrive *diskDrive)
{
	int fileNum = diskDrive->getNumFiles(); // get num files
	int capacity = diskDrive->getCapacity() - 1;
	int const arraySize = 12000;
	int arrayCount = 0;
	int emptySpace = -1;// needs new one
	int emptyRam = -1; // needs new one
	int index = 2; // b/c positions 0 and 1 are reserved
	DiskBlock* fragment = NULL; // to store the fragments
	DiskBlock* temp = NULL;  // to move things around after deletion
	DiskBlock** storeInRAM;//Array in RAM
	storeInRAM = new DiskBlock*[arraySize];
	QuadraticHashTable<int>* hashLoc; //Hash Table to store new Loc on Disk
	hashLoc = new QuadraticHashTable<int>(-1, 200000);
	//hacatshLoc->printSize();


	int blah = capacity;
	while (diskDrive->FAT[blah]) blah--;
	emptySpace = blah; // first empty from back


	for (int i = 0; i < fileNum; i++)
	{
		int blockID = diskDrive->directory[i].getFirstBlockID();
		// once done try comenting that out and see what happens
		if (blockID == diskDrive->directory[i].getFirstBlockID()) // so the directory knows where the new file starts
		{
			diskDrive->directory[i].setFirstBlockID(index);
		}

		while (blockID != 1)
		{
			//if (index == 10)
			//{
			//  cout << " Help " << endl;
			//}
			//*****************************************************
			//                  READ
			//*****************************************************

			if (index <= blockID) // it hasn't been moved so read it from disk
			{
				fragment = diskDrive->readDiskBlock(blockID);
				diskDrive->FAT[blockID] = false; // maintins FAT table
				//new lines in code **********
				if (blockID > emptySpace)
					emptySpace = blockID;
				//*******************
			}
			else // fragment has been moved, read it from hash
			{
				int newLoc = hashLoc->find(blockID);

				if (newLoc <= 0) // stored in RAM array
				{
					int dummy = -1 * (newLoc);
					fragment = storeInRAM[dummy];
					storeInRAM[dummy] = NULL; // make empty
					emptyRam = newLoc;
				}
				else // stored on disk
				{
					hashLoc->remove(blockID);
					while (hashLoc->find(newLoc) != (-1))
					{
						newLoc = hashLoc->find(newLoc);
						hashLoc->remove(newLoc);
					}
					fragment = diskDrive->readDiskBlock(newLoc);
					diskDrive->FAT[newLoc] = false;
					//new lines in code **********
					if (newLoc > emptySpace)
						emptySpace = newLoc;
					//*******************
				}
			}


			//*****************************************************
			//                  WRITE
			//*****************************************************

			//cout << " I got here" << index << endl;

			if (blockID == index) //if the fragment is on proper spot by chance go to the next one
			{
				blockID = fragment->getNext();
			}
			else // if the fragment is not on the proper spot write on the index
			{

				if (diskDrive->FAT[index]) // if occupied
				{
					temp = diskDrive->readDiskBlock(index);
					int oldLoc = index;
					int newLoc;
					if (arrayCount < arraySize || (emptyRam = !- 1))// if RAM array has space
					{

						if (arrayCount < arraySize)
						{
							newLoc = -arrayCount;
							storeInRAM[arrayCount] = temp;
							arrayCount++;
						}
						else if (emptyRam = !- 1)// fix empty spaces in ram to minimize disk accesess
						{
							newLoc = -emptyRam; // negative to differ
							storeInRAM[emptyRam] = temp;
							delete temp;
							emptyRam = -1;// used needs new empty space
						}
					}
					else // if Ram array full get space from disk stack
					{
						newLoc = emptySpace;
						diskDrive->writeDiskBlock(temp, newLoc);
						delete temp;
						diskDrive->FAT[newLoc] = true;
						//int i = capacity;
						//new lines in code **********
						while (diskDrive->FAT[emptySpace]) emptySpace--;
						//emptySpace = i; // first empty from back
						//*******************

					}

					diskDrive->writeDiskBlock(fragment, index);
					hashLoc->insert(oldLoc, newLoc); // stores the location
				}
				else // empty
				{
					diskDrive->writeDiskBlock(fragment, index);
				}
				blockID = fragment->getNext();
			}
			index++; // go to next spot
			delete fragment;
		}
	}
} // Defragmenter()
