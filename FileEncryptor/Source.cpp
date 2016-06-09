/*
File Xor encryptor/decryptor based on key file.
Written by SaEeD
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <iomanip>

using namespace std;
void usage()
{
	cout << "Option -d for Decrypt or Option -e for Encrypt" << endl;
	cout << "Encryptor [-d | -e] <Filename> <Keyfile>" << endl;

}

int crypt(const string &filename, const string &keyfile );

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		usage();
		return 1;
	}
	
	if ( strcmp(argv[1], "-e") == 0)
	{
		cout << "[+]Encrypting File: " << argv[2] << endl;
		crypt(argv[2], argv[3]);
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		cout << "[+]Decrypting File: " << argv[2] << endl;
		crypt(argv[2], argv[3]);
	}
	else {
		usage();
		return 1;
	}	

	return 0;
}

int crypt(const string &filename, const string &keyfile)
{
	

	cout << "[*]Using Key File: " << keyfile << endl;
	
	ifstream m_input, key;
	ofstream m_output;
	m_input.open(filename, ios::in | ios::binary);
	key.open(keyfile, ios::in | ios::binary);
	m_output.open(filename + "-New", ios::out | ios::binary);


	//read the file
	char ch;
	char ch2;
	key.seekg(0, ios_base::end);
	unsigned int size = key.tellg();
	key.seekg(0);
	int counter = 0;
	
	cout << "[+]Key File size is: " << size << " bytes" << "\n----[Key Hex Contents]----" << endl;

	while (counter !=size)
	{
		key.read((&ch), 1);
		cout << "0x" << hex << setfill('0') << setw(2) << ((int)ch & 0xffU) << " ";
		counter++;
	}
	counter = 0;
	cout << "\n---------------------------------------" << endl;
	key.seekg(0);

	int byte1, byte2;

	while (!m_input.eof())
	{
		if (counter == size)
		{
			counter = 0;
			key.seekg(0);
		}

		m_input.read((&ch), 1);
		key.read((&ch2), 1);
		
		byte1 = (int)ch;
		byte2 = (int)ch2;
		unsigned char x = byte1 ^ byte2;
		m_output << x;
		counter++;
	}

	m_input.close();
	key.close();
	m_output.close();

	cout << "[!]DONE :)" << endl;

	return 0;
}