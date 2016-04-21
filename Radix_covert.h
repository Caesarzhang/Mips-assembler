#include <sstream>
#include <string>
using namespace std;



string unsignExt(const string s, unsigned int len) {
	string temp;
	if (len < s.length())
		return s.substr(s.length() - len, 16);
	temp.append(len - s.length(), '0');
	return temp + s;
}

string signExt(const string s, unsigned int len) {
	string temp;
	if (len < s.length())
		return s.substr(s.length() - len, 16);
	temp.append(len - s.length(), s[0]);
	return temp + s;
}

void getclean(string &s) {
	for (unsigned int i = 0; i < s.length(); ++i)
		if (s[i] != '0' && s[i] != '1') {
			s.erase(i, 1);
			--i;
		}
}

string bin2hex(string s) {
	string ans, item, hex;
	for (unsigned int i = 0; i < s.length(); ++i)
		if (s[i] != '0' && s[i] != '1') {
			s.erase(i, 1);
			--i;
		}
	int k;
	for (k = 0; (s.length() + k) % 4 != 0; ++k);
    s = unsignExt(s, (unsigned int)s.length() + k);
	for (unsigned int i = 0; i < s.length(); i += 4) {
		item = s.substr(i, 4);
		if (item == "0000")
			ans.append(1, '0');
		else if (item == "0001")
			ans.append(1, '1');
		else if (item == "0010")
			ans.append(1, '2');
		else if (item == "0011")
			ans.append(1, '3');
		else if (item == "0100")
			ans.append(1, '4');
		else if (item == "0101")
			ans.append(1, '5');
		else if (item == "0110")
			ans.append(1, '6');
		else if (item == "0111")
			ans.append(1, '7');
		else if (item == "1000")
			ans.append(1, '8');
		else if (item == "1001")
			ans.append(1, '9');
		else if (item == "1010")
			ans.append(1, 'A');
		else if (item == "1011")
			ans.append(1, 'B');
		else if (item == "1100")
			ans.append(1, 'C');
		else if (item == "1101")
			ans.append(1, 'D');
		else if (item == "1110")
			ans.append(1, 'E');
		else if (item == "1111")
			ans.append(1, 'F');
	}
	return ans;
}

string hex2bin(string s) {
	string ans;
	for (unsigned i = 0; i < s.length(); ++i) {
		switch (s[i]) {
			case '0': ans.append("0000"); break;
			case '1': ans.append("0001"); break;
			case '2': ans.append("0010"); break;
			case '3': ans.append("0011"); break;
			case '4': ans.append("0100"); break;
			case '5': ans.append("0101"); break;
			case '6': ans.append("0110"); break;
			case '7': ans.append("0111"); break;
			case '8': ans.append("1000"); break;
			case '9': ans.append("1001"); break;
			case 'A': ans.append("1010"); break;
			case 'a': ans.append("1010"); break;
			case 'B': ans.append("1011"); break;
			case 'b': ans.append("1011"); break;
			case 'C': ans.append("1100"); break;
			case 'c': ans.append("1100"); break;
			case 'D': ans.append("1101"); break;
			case 'd': ans.append("1101"); break;
			case 'E': ans.append("1110"); break;
			case 'e': ans.append("1110"); break;
			case 'F': ans.append("1111"); break;
			case 'f': ans.append("1111"); break;
		}
	}
	return ans;
}

void Reverse(string &ans) {
	for (unsigned int i = 0; i < ans.length(); ++i)
		if (ans[i] == '0')
			ans[i] = '1';
		else
			ans[i] = '0';

    for (size_t i = ans.length() - 1; i >= 0; --i)
		if (ans[i] == '0') {
			ans[i] = '1';
			break;
		}
		else
			ans[i] = '0';
}

string int2bin(int val) {
	string ans;
	bool flag = false;
	if (val < 0) {
		val = -val;
		flag = true;
	}
	while (val != 0) {
		int remain = val % 2;
		string temp;
		temp.append(1, (char)(remain + '0'));
		val /= 2;
		ans.insert(0, temp);
	}
	if (flag == true) {
		Reverse(ans);
	}
	return flag == true ? ("1" + ans) : ("0" + ans);
}

unsigned int hex2int(string hex) {
	int ans = 0;
	bool flag = false;
	string bin = hex2bin(hex);
	if (bin[0] == '1') {
		Reverse(bin);
		flag = true;
	}
	hex = bin2hex(bin);
	for (unsigned int i = 0; i < hex.length(); ++i) {
		if (hex[i] >= 'A' && hex[i] <= 'F')
			ans = ans * 16 + hex[i] - 'A' + 10;
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			ans = ans * 16 + hex[i] - 'a' + 10;
		else
			ans = ans * 16 + hex[i] - '0';
	}
	return flag == false ? ans : -ans;
}

unsigned int addr2int(string raw) {
	for (unsigned int i = 0; i < raw.length(); ++i) {
		if (!isdigit(raw[i]) && !isalpha(raw[i]) && raw[i] != '-') {
			raw.erase(i, 1);
			--i;
		}
	}
	if (raw.find("0x") != string::npos) {
		string hex = raw.substr(raw.find("0x") + 2);
		return hex2int(hex);
	}
	else if (raw.find("0X") != string::npos) {
		string hex = raw.substr(raw.find("0X") + 2);
		return hex2int(hex);
	}
	else {
		int ans;
		stringstream ss;
		ss << raw;
		ss >> ans;
		return ans;
	}
}

string str2bin(string s) {
	unsigned int val = addr2int(s);
	return int2bin(val);
}
