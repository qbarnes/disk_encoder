/*
 * Take hex input and display the number as encoded with FM and MFM.
 */

#include <iostream>
#include <string>
#include <bitset>
#include <cinttypes>

using namespace std;

struct mod_encoding {
	uint64_t	n;
	string		s;
public:
	mod_encoding() : n(0), s() {}
	uint64_t& num() { return n; }
	string& str() { return s; }
};


mod_encoding
fm_encode(uint32_t x)
{
	mod_encoding	ret;

	for (int i = sizeof(x)*8; i >= 0; --i) {
		if (x & ((uint32_t)1 << i)) {
			ret.num() |= (uint64_t)3 << (i*2);
			ret.str() += "11";
		} else {
			ret.num() |= (uint64_t)1 << (i*2);
			ret.str() += "10";
		}
	}

	return ret;
}


mod_encoding
mfm_encode(uint32_t x)
{
	mod_encoding	ret;
	int		prec = -1;

	for (int i = sizeof(x)*8; i >= 0; --i) {
		bool	b = x & ((uint32_t)1 << i);

		ret.n <<= 2;

		if (b) {
			ret.num() |= 1;
			ret.str() += "01";
		} else {
			switch (prec) {
			case 0:
				ret.num() |= 2;
				ret.str() += "10";
				break;
			case 1:
				ret.num() |= 0;
				ret.str() += "00";
				break;
			default:
				ret.num() |= 0;
				ret.str() += "?";
				break;
			}
		}

		prec = b;
	}

	return ret;
}


int
main(int argc, char **argv)
{
	do {
		uint32_t	inum;

		cout << "Input hex number: " << flush;
		cin >> hex >> inum;
		if (cin.rdstate() != istream::goodbit)
			break;

		auto enc = fm_encode(inum);
		cout << "FM Encode:  ";
		cout << hex << enc.num() << dec << endl;
		cout << "            ";
		cout << enc.str() << endl;

		enc = mfm_encode(inum);
		cout << "MFM Encode: ";
		cout << hex << enc.num() << dec << endl;
		cout << "            ";
		cout << enc.str() << endl;

	} while (1);

	cout << endl;

	return 0;
}
