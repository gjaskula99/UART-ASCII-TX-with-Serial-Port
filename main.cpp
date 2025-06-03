#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	try
	{
		cout << "Creating output file...";
		fstream output;
		output.open("output.asm", ios::out);
		if(output.is_open() && output.good())
		{
			cout << " done\nGenerating assembler headers...";
			output << ".nolist\n.include \"m16def.inc\"\n.list\n.listmac\n.device ATmega16\n.cseg\n\n.org 0x0000\nJMP START\n";
			output << "\n.org 0x0030\nSTART:\nLDI r16, LOW(RAMEND)\nLDI r17, HIGH(RAMEND)\nOUT SPL, r16\nOUT SPH, r17\n\nCALL PB0_STRING\n\n";
			output << "JMP PC\n\n\n";
			output << ".org 0x0420\nDELAY_104:\nLDI r30, 255\nLoop_Count:\n\tDEC r30\n\tBRNE Loop_Count\n\tLDI r30, 19\n\tLoop_Count2:\n\t\tDEC r30\n\t\tBRNE Loop_Count2\nRET\n\n";
			output << "PB0_STRING:\n;Start signal\nLDI r16, 0b00000001\nOUT DDRB, r16\n;Actual data\n";
			cout << " done\n";
			
			string target = "";
			cout << "Enter input word: ";
			getline(cin, target);
			cout << "Writting assembler...\n";
                        for(int i = 0; i < target.length(); i++)
                        {
                                int character = static_cast<int>(target[i]);
                                output << ";Sign " << target[i] << " ASCII: " << character << "\n";
                                output << "CBI PORTB, 0\t;Start sign\nCALL DELAY_104\n";
                                cout << target[i] << " = " << character << "\t";

                                for(int bit = 0; bit < 8; ++bit)
                                {
                                        int result = (character >> bit) & 1;
                                        cout << result;
                                        if(result == 0)
                                        {
                                                output << "CBI PORTB, 0\n";
                                        }
                                        else
                                        {
                                                output << "SBI PORTB, 0\n";
                                        }
                                        output << "CALL DELAY_104\n";
                                }

                                cout << "\n";
                                output << "SBI PORTB, 0\t;Stop sign\nCALL DELAY_104\n";
                        }
			output << "RET\n";
			cout << "done\nClosing output...";
			output.close();
			cout << " done";
		}
		else throw("File opening failed");
	}
	catch(...)
	{
		cout << " FAILED";
		return -1;
	}
	return 0;
}
