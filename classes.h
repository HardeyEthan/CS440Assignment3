#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
using namespace std;

class Record {
public:
    int id, manager_id;
    std::string bio, name;

    Record(vector<std::string> fields) {
        id = stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = stoi(fields[3]);
    }

    void print() {
        cout << "\tID: " << id << "\n";
        cout << "\tNAME: " << name << "\n";
        cout << "\tBIO: " << bio << "\n";
        cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};


class LinearHashIndex {

private:
    const int BLOCK_SIZE = 4096;

    vector<int> blockDirectory; // Map the least-significant-bits of h(id) to a bucket location in EmployeeIndex (e.g., the jth bucket)
                                // can scan to correct bucket using j*BLOCK_SIZE as offset (using seek function)
								// can initialize to a size of 256 (assume that we will never have more than 256 regular (i.e., non-overflow) buckets)
    int n;  // The number of indexes in blockDirectory currently being used
    int i;	// The number of least-significant-bits of h(id) to check. Will need to increase i once n > 2^i
    int j;  // Used to search the blockdir and find the right page for a given record id
    int numRecords;    // Records currently in index. Used to test whether to increase n
    int nextFreeBlock; // Next place to write a bucket. Should increment it by BLOCK_SIZE whenever a bucket is written to EmployeeIndex
    int nextFreeOverflow;
    string fName;      // Name of index file
    int hashResult;
    string pageBuffer;

    void replaceString(string toCopy, char** copyHere, int location){

        for(int i = 0; i < toCopy.length(); i++){
            
            (*copyHere)[i+location] = toCopy[i];
        }

    }



    // Insert new record into index
    void insertRecord(Record record) {

        //the size needed to store the new record and its corresponding slot dir slot
        int newRecordLength = 8 + 8 + record.bio.length() + record.name.length() + 4 + 12;

        // No records written to index yet
        if (numRecords == 0) {
            // Initialize index with first blocks (start with 4)
            blockDirectory.push_back(00);
            blockDirectory.push_back(01);
            blockDirectory.push_back(10);
            blockDirectory.push_back(11);

            nextFreeBlock = 4*BLOCK_SIZE;
            nextFreeOverflow = 4096*256;

        }

        // Add record to the index in the correct block, creating a overflow block if necessary
        numRecords++;

        //compute the hash function "id mod 216"
        int hashResult = record.id%216;
        int binResult = 0;
        int modResult = 0;
        int divResult = hashResult;

        //convert to binary and grab i least significant bits
        for(int k = 0; k < i; k++){
            //build an int that looks like binary
            modResult = divResult%2;
            divResult = divResult/2;

            binResult += pow(10,k) * modResult;

        }

        //check for bit flip
        if(binResult > blockDirectory.at(n-1)){
            //perform the bit flip
            int xorFella = pow(10, i-1);
            binResult ^= xorFella;
        }

        //based on the binary result, determine which block to go to, j represents the block number
        for(int k = 0; k < n; k++){
            if(blockDirectory.at(k) == binResult){
                j = blockDirectory.at(k);
            }
        }

        //open the file and seek to the desired block
        ifstream indexFile;
        indexFile.open(fName);
        indexFile.seekg(j * BLOCK_SIZE);

        //declare the c style buffer to read in the block
        char* pageDataBuffer = new char[BLOCK_SIZE + 1];
        indexFile.read(pageDataBuffer, BLOCK_SIZE);
        pageDataBuffer[BLOCK_SIZE] = '\0'

        //set the buffer to a normal string and delete the c string
        string stringBuffer = pageDataBuffer;
        delete[] pageDataBuffer;

        //set the buffer to a stringstream and delete the normal string
        stringstream myStrStrm;
        myStrStrm.str(stringBuffer);
        stringBuffer.clear();

        //for processing small bits of data;
        string inputBuffer;


        //determine how much space is currently available in the determined block, go to the slot dir and add up the offsets
        getline(myStrStrm, inputBuffer, '[');
        int sizeOfSlotDir = BLOCK_SIZE - tellg(myStrStrm);
        getline(myStrStrm, inputBuffer, '*');
        int lastOff = stoi(inputBuffer);
        getline(myStrStrm, inputBuffer, ',')
        getline(myStrStrm, inputBuffer, '*');
        int lastLen = stoi(inputBuffer);
        
        //if space, insert
        if((lastOff + lastLen + sizeOfSlotDir + newRecordLength) <= BLOCK_SIZE){
            //put the record in the given block, then push it back onto the file

            myStrStrm.clear();

            
        }
        //if no space, insert into overflow
        else{
            //create an overflow page and store it there

            //update the pointer in the current page, and write it to the file

            //create a buffer to write the new page

            //seek to the correct position in the file

            //write it and clear the buffer
        }


        // Take neccessary steps if capacity is reached:
		// increase n; increase i (if necessary); place records in the new bucket that may have been originally misplaced due to a bit flip

        //check whether the average number of records per page exceeds 70% capacity, if so, increase n
        //730 represents the max size of a record with its data plus slot dir
        if((numRecords * 730) > (.7 * n * 4096)){
            n++;
            nextFreeBlock += BLOCK_SIZE;
        }

        //check whether i needs to be increased to accomidate n
        if(pow(2,i) < n){
            i++;
        }

        //perform any necessary reorganization
        //go through the file

        //determine if a given record belongs

            //if doesn't belong, determine if it needs a bit flip

                //if needs a bit flip, flip the bit and find its place

                //if doesn't need a flip, find its place
        

    }

public:
    LinearHashIndex(string indexFileName) {
        n = 4; // Start with 4 buckets in index
        i = 2; // Need 2 bits to address 4 buckets
        numRecords = 0;
        nextFreeBlock = 0;
        fName = indexFileName;

        // Create your EmployeeIndex file and write out the initial 4 buckets
        // make sure to account for the created buckets by incrementing nextFreeBlock appropriately

        //open the index file
        ofstream outFile;
        outFile.open(indexFileName);

        //make a new page, and put the empty pointer at the end
        char* newPage = new char[4096];
        string filePointer = "{0000000000}";
        memset(newPage, ' ', 4096);
        replaceString(filePointer, &newPage, 4083);

        //declare buffer and fill with spaces
        for(int i = 0; i < 4; i++){
            outFile.write(newPage, 4096);
        }

        delete[] newPage;
        outFile.close();
      
    }

    // Read csv file and add records to the index
    void createFromFile(string csvFName) {
        
        //open the input file
        ifstream inputFile;
        inputFile.open(csvFName);

        //start reading from the file
        string curLine;
        string id;
        string manid;
        string name;
        string bio;

        
        //loop until all records have been sent to the insert function
        while(true){
            
            //process the id element
            if(getline(inputFile, curLine, ',')){
                id = curLine;
                
                //process the name element
                getline(inputFile, curLine, ',');
                name = curLine;
    
                //process the bio element
                getline(inputFile, curLine, ',');
                bio = curLine;
    
                //process the manager id element
                getline(inputFile, curLine);
                manid = curLine;
    
                //cout << id << " " << name << " " << bio << " " << manid << endl;
                
                vector<string> myVector{id, name, bio, manid};
                Record myRecord(myVector);
    
                //send the record to insertRecord
                //insertRecord(myRecord);
                
            }
            //if the getline is invalid, that means there is no new line, break out and close the input file
            else{
                break;
            }

        }

        //close the input file
        inputFile.close();
    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        
    }
};
