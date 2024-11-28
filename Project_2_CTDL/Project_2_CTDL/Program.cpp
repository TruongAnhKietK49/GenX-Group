#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h> 
#include <windows.h>

using namespace std;

string centerText(const string& text) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int padding = (consoleWidth - text.length()) / 2;
	if (padding > 0) {
		return string(padding, ' ') + text;
	}
	return text;
}
void setTextColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void printCentered(const string& text, int color) {
	setTextColor(color);
	cout << centerText(text);
	setTextColor(7);
}

class Employee {
	string userName;
	string passWord;
	string fullName;
	string address;
	string phone;
	string email;
	int count;
	vector<pair<string, string>> employee;
public:
	Employee(string _userName = "", string _passWord = "", string _fullName = "", string _address = "", string _phone = "", string _email = "", int _count = NULL)
		: userName(_userName), passWord(_passWord), fullName(_fullName), address(_address), phone(_phone), email(_email), count(_count) {
		loadEmployConfig();
		string file = _userName + ".txt";
		loadData(file);
	}

	string getUserName() const { return userName; }
	string getPassWord() const { return passWord; }
	string getFullName() const { return fullName; }
	string getAddress() const { return address; }
	string getPhone() const { return phone; }
	string getEmail() const { return email; }
	int getCount() const { return count; }

	void setUserName(const string& _userName) { userName = _userName; }
	void setPassWord(const string& _passWord) { passWord = _passWord; }
	void setFullName(const string& _fullName) { fullName = _fullName; }
	void setAddress(const string& _address) { address = _address; }
	void setPhone(const string& _phone) { phone = _phone; }
	void setEmail(const string& _email) { email = _email; }
	void setCount(const int& _count) { count = _count; }

	//load thông tin cá nhân của Employee
	void loadData(const string& fileName) {
		fstream fileInfo(fileName, ios::in);
		if (fileInfo.is_open()) {
			int lineCount = 0;
			string line;
			while (getline(fileInfo, line)) {
				switch (lineCount) {
				case 0:
					fullName = line;
					break;
				case 1:
					address = line;
					break;
				case 2:
					phone = line;
					break;
				case 3:
					email = line;
					break;
				case 4:
					count = stoi(line); // Chuyển đổi từ string sang int
					break;
				}
				lineCount++;
			}
			fileInfo.close();
		}
		string user = fileName.substr(0, fileName.size() - 4);
		fstream fileUser("./Employees.txt", ios::in);
		if (fileUser.is_open()) {
			string User, Pin;
			while (getline(fileUser, User) && getline(fileUser, Pin)) {
				if (user == User) {
					userName = User;
					passWord = Pin;
				}
			}
			fileUser.close();
		}
	}

	//Load tài khoản Employee khi chạy code
	void loadEmployConfig() {
		fstream fi("./Employees.txt", ios::in);
		if (fi.is_open()) {
			string user, password;
			while (getline(fi,user) && getline(fi, password)) {
				employee.push_back({ user, password });
			}
			fi.close();
		}
		else cout << "Can't open file Employees.txt to read!";
	}

	//Update mật khẩu sau khi chỉnh sửa
	void updatePassword(Employee& tmp, string user) {
		for (auto& it : employee) {
			if (it.first == user) {
				it.second = tmp.getPassWord(); // Cập nhật mật khẩu
				break;
			}
		}
		fstream fo("./Employees.txt", ios::out);
		if (fo.is_open()) {
			for (const auto& it : employee) {
				fo << it.first << endl << it.second << endl;
			}
			fo.close();
		}
		else {
			cout << "Can't open file Employees.txt to update password!" << endl;
		}
	}


	//Update lại thông tin sau khi chỉnh sửa
	void updateInfoEmployee(Employee& tmp, string userName) {
		string file = userName + ".txt";
		fstream fo(file, ios::out); // Mở tệp ở chế độ ghi với chế độ cắt bỏ
		if (fo.is_open()) {
			fo << tmp.getFullName() << endl;
			fo << tmp.getAddress() << endl;
			fo << tmp.getPhone() << endl;
			fo << tmp.getEmail() << endl;
			fo << tmp.getCount() << endl;
			fo.close();
		}
		else {
			cout << "Can't open file: " << file << " to update info employee!" << endl;
		}
	}


	//Check xem đăng nhập khớp tài khoản
	bool checkLogin(const string& username, const string& password) {
		for (const auto& account : employee) {
			if (account.first == username && account.second == password)
				return true;
		}
		return false;
	}
	bool checkUser(const string& username) {
		for (const auto& account : employee) {
			if (account.first == username)
				return true;
		}
		return false;
	}

	void addEmployee() {
		while (true) {
			printCentered("Enter Username: ", 14);
			getline(cin, userName);
			if (userName.empty()) {
				printCentered("Username can't be empty! Please re-enter!\n", 6);
				continue;
			}
			else if (checkUser(userName)) {
				printCentered("Username already exists! Please choose another username!\n", 6);
				continue;
			}
			else break;
		}
		
		passWord = "111111";
		
		while (true)
		{
			printCentered("Enter FullName: ", 14);
			getline(cin, fullName);
			if (fullName.empty()) {
				printCentered("FullName can't be empty! Please re-enter!\n", 6);
				continue;
			}
			else break;
		}
		
		while (true)
		{
			printCentered("Enter Address: ", 14);
			getline(cin, address);
			if (address.empty()) {
				printCentered("Address can't be empty! Please re-enter!\n", 6);
				continue;
			}
			else break;
		}
		
		while (true)
		{
			printCentered("Enter Phone: ", 14);
			getline(cin, phone);
			if (phone.empty()) {
				printCentered("Phone can't be empty! Please re-enter!\n", 6);
				continue;
			}
			else break;
		}

		while (true)
		{
			printCentered("Enter Email: ", 14);
			getline(cin, email);
			if (email.empty()) {
				printCentered("Email can't be empty! Please re-enter!\n", 6);
				continue;
			}
			else break;
		}
	}

	void menuEmployee() {
		printCentered("-----Menu-----\n", 14);
		printCentered("1. Show info of account!\n", 14);
		printCentered("2. Change password!\n", 14);
		printCentered("3. Exit!\n", 14);
	}

	void displayInfo() const {
		printCentered("-->Information<--\n", 13);
		printCentered("User: " + userName + "\n", 14);
		printCentered("Password: " + passWord + "\n", 14);
		printCentered("Name: " + fullName + "\n", 14);
		printCentered("Address: " + address + "\n", 14);
		printCentered("Phone: " + phone + "\n", 14);
		printCentered("Email: " + email + "\n\n", 14);
	}

	void Show() const {
		displayInfo();
	}
};
class Administer {
private:
	string userName;
	string passWord;
	vector<Employee> employees;
	vector<pair<string, string>> adminAccounts; //Lưu trữ user và pass
	
public: 
	Administer(string _userName = "", string _passWord = "") {
		userName = _userName;
		passWord = _passWord;
		loadAminConfig();
		loadEmployeesFromFile();
	}

	//Load tài khoản Admin trong file admin.txt
	void loadAminConfig() {
		fstream fi("./admin.txt", ios::in);
		if (fi.is_open()) {
			string username, password;
			while (fi >> username >> password) {
				adminAccounts.push_back({ username, password });
			}
			fi.close();
		}
	}

	//Load toàn bộ thông tin Employee để show or delete
	void loadEmployeesFromFile() {
		string userName, passWord, fullName, address, phone, email;
		int count;
		fstream fi("./Employees.txt", ios::in);
		if (fi.is_open()) {
			while (getline(fi, userName) && getline(fi, passWord)) {
				string file = userName + ".txt";
				fstream fe(file, ios::in);
				if (fe.is_open()) {
					getline(fe, fullName);
					getline(fe, address);
					getline(fe, phone);
					getline(fe, email);
					fe >> count;
					fe.close();

					employees.emplace_back(userName, passWord, fullName, address, phone, email, count);
				}
				else {
					printCentered("Cant open file name: " + file + " of the employee!\n", 6);
				}
			}
			fi.close();
		}
		else {
			printCentered("Cant open file Employees.txt to read!\n", 6);
		}
	}

	//Check admin đăng nhập
	bool checkLogin(const string& username, const string& password) {
		for (const auto& account : adminAccounts) {
			if (account.first == username && account.second == password) {
				return true;
			}
		}
		return false;
	}

	//Tạo tài khoản Employee
	void addEmployee(const Employee& employee) {
		employees.push_back(employee);
		saveEmployeesToFile(employees, employee.getUserName());
		system("cls");
		printCentered("Add successful Employee!\n", 10);
	}

	//Lưu trữ account của employee vừa tạo
	void saveEmployeesToFile(vector<Employee>& employees, const string& userName) {
		fstream fo("./Employees.txt", ios::out);
		if (fo.is_open()) {
			for (const Employee& emp : employees) {
				fo << emp.getUserName() << endl
					<< emp.getPassWord() << endl;
			}
			fo.close();
			string fileName = userName + ".txt";
			fstream fe(fileName, ios::out);
			if (fe.is_open()) {
				for (Employee& emp : employees) {
					if (userName == emp.getUserName()) {
						emp.setCount(0);
						fe << emp.getFullName() << endl
							<< emp.getAddress() << endl
							<< emp.getPhone() << endl
							<< emp.getEmail() << endl
							<< emp.getCount() << endl;
					}
				}
				fe.close();
			}
			else printCentered("Cant open file name: " + fileName + " of the employee to write!\n", 6);
		}
		else {
			printCentered("Can't open file Employees.txt to save Employees!\n", 6);
		}
	}

	//Xóa tài khoản Employee
	void deleteEmployee(const string& userName) {
		auto it = find_if(employees.begin(), employees.end(),
			[&userName](const Employee& emp) {
				return emp.getUserName() == userName;
			});

		if (it != employees.end()) {
			employees.erase(remove_if(employees.begin(), employees.end(),
				[&userName](const Employee& emp) {
					return emp.getUserName() == userName;
				}), employees.end());
			updateAfterDelete(employees, userName);
			system("cls");
			printCentered("Delete Successful Employee!\n", 10);
		}
		else {
			printCentered("Can't find userEmployee " + userName + " to delete!\n", 6);
		}
	}


	//Update lại danh sách Employees.txt sau khi xóa đi nhân viên
	void updateAfterDelete(vector<Employee>& emp, string userName) {
		fstream fo("./Employees.txt", ios::out);
		if (fo.is_open()) {
			for (const Employee& tmp : emp) {
				fo << tmp.getUserName() << endl;
				fo << tmp.getPassWord() << endl;
			}
			fo.close();
			string file = userName + ".txt";
			if (remove(file.c_str()) == 0) {
				printCentered("Delete " + file + " success!\n", 10);
			}
			else printCentered("Delete " + file + " fail!\n", 4);
		}
		else printCentered("Cant open file Employees.txt to update!\n", 6);
	}

	void findEmployee(string& userEmployee) {
		bool check = false;
		for (Employee it : employees) {
			if (it.getUserName() == userEmployee) {
				string file = userEmployee + ".txt";
				it.loadData(file);
				it.Show();
				check = true;
				break;
			}
		}
		if(!check) printCentered("Cant find userEmployee " + userEmployee + "\n", 6);
	}

	void displayMenu() {
		printCentered("1. Add employee\n", 14);
		printCentered("2. Delete employee\n", 14);
		printCentered("3. Find employee\n", 14);
		printCentered("4. Show employees list\n", 14);
		printCentered("5. Update info Employee\n", 14);
		printCentered("6. Exit\n", 14);
		printCentered("Enter your choice: ", 15);
	}

	void menuInfo() {
		printCentered("1. Update fullName\n", 14);
		printCentered("2. Update address\n", 14);
		printCentered("3. Update phone\n", 14);
		printCentered("4. Update email\n", 14);
		printCentered("5. Exit!\n", 14);
		printCentered("Enter your choice: ", 15);
	}

	//Hàm trả về giá trị Employee
	vector<Employee>& getEmployees()  {
		return employees;
	}
};

int menuStart() {
	system("cls");
	printCentered("-----Menu-----\n", 12);
	printCentered("1. Admin\n",14);
	printCentered("2. Employee\n",14);
	printCentered("3. Exit!\n", 14);
	printCentered("Enter choice: ", 15);
	int choice; cin >> choice;
	return choice;
}
string enterPassword() {
	string pin = "";
	char key;
	while (true) {
		key = _getch();
		if (key == '\r') {
			printCentered("\n", 10);
			break;
		}
		else if (key == '\b') {
			if (!pin.empty()) {
				cout << "\b \b";
				pin.pop_back();
			}
		}
		else {
			pin += key;
			cout << "*";
		}
	}
	return pin;
}
void inpUpdateEmployee(Employee& tmp, string userEmployee);
void logAdmin() {
	string user, pin = "";
	system("cls");
	printCentered("-----Login Admin-----\n", 12);
	printCentered("User: ", 9);
	getline(cin, user);
	printCentered("Pin: ", 9);

	pin = enterPassword();

	Administer admin(user, pin);

	if (admin.checkLogin(user, pin)) {
		printCentered("Login successfully! Wait a few seconds...\n", 10);
		Sleep(2000);
		bool check = true;
		while (check)
		{
			system("cls");
			admin.displayMenu();
			int choice; cin >> choice;
			cin.ignore();
			
			Employee tmp;
			string userEmployee;

			bool kTra = false;
			switch (choice)
			{
			case 1:
				system("cls");
				tmp.addEmployee();
				admin.addEmployee(tmp);
				printCentered("Press any key to continue....", 7);
				_getch();
				break;
			case 2:
				system("cls");
				printCentered("Enter user of Employee to detele: ", 15);
				getline(cin, userEmployee);
				admin.deleteEmployee(userEmployee);
				printCentered("Press any key to continue....", 7);
				_getch();
				break;
			case 3:
				system("cls");
				printCentered("Enter userName to find: ", 15);
				getline(cin, userEmployee);
				admin.findEmployee(userEmployee);
				printCentered("Press any key to continue....", 7);
				_getch();
				break;
			case 4:
				system("cls");
				printCentered("------List Employees------\n", 14);
				for (Employee emp : admin.getEmployees()) {
					string data = emp.getUserName();
					data = data + ".txt";
					emp.loadData(data);
					emp.Show();
					printCentered("---------------------\n", 7);
				}
				printCentered("Press any key to continue....", 7);
				_getch();
				break;
			case 5:
				system("cls");
				printCentered("Enter userEmployee to update: ", 14);
				getline(cin, userEmployee);
				for (Employee& emp : admin.getEmployees()) {

					if (emp.getUserName() == userEmployee) {
						inpUpdateEmployee(emp, userEmployee);
						kTra = true;
						break;
					}
				}
				if (kTra == false) {
					printCentered("Can't find userEmployee " + userEmployee + " to update!\n", 6);
					printCentered("Press any key to continue....", 7);
					_getch();
				}
				break;
			case 6:
				check = false;
				break;
			default:
				printCentered("Invalid value! Please re-enter value!\n", 4);
				break;
			}
		}
	}
	else {
		printCentered("Incorrect User or Pin! Please re-enter...\n", 4);
		printCentered("Press any key to continue....", 7);
		_getch();
	}
}

void inpUpdateEmployee(Employee& tmp, string userEmployee)
{
	system("cls");
	while (true)
	{
		Administer ad;
		ad.menuInfo();
		int choice; cin >> choice;
		cin.ignore();
		string newName, newAddress, newPhone, newEmail;
		switch (choice)
		{
		case 1:
			printCentered("Enter newName: ", 14);
			getline(cin, newName);
			tmp.setFullName(newName);
			tmp.updateInfoEmployee(tmp, userEmployee);
			system("cls");
			printCentered("Update successful!\n", 10);
			break;
		case 2:
			printCentered("Enter newAddres: ", 14);
			getline(cin, newAddress);
			tmp.setAddress(newAddress);
			tmp.updateInfoEmployee(tmp, userEmployee);
			system("cls");
			printCentered("Update successful!\n", 10);
			break;
		case 3:
			printCentered("Enter newPhone: ", 14);
			getline(cin, newPhone);
			tmp.setPhone(newPhone);
			tmp.updateInfoEmployee(tmp, userEmployee);
			system("cls");
			printCentered("Update successful!\n", 10);
			break;
		case 4:
			printCentered("Enter newEmail: ", 14);
			getline(cin, newEmail);
			tmp.setEmail(newEmail);
			tmp.updateInfoEmployee(tmp, userEmployee);
			system("cls");
			printCentered("Update successful!\n", 10);
			break;
		case 5:
			return;
			break;
		default:
			printCentered("Invalid value! Please re-enter value!\n", 4);
			break;
		}
		
	}
}
void logEmployee() {
	int cnt = 0;
	bool check = true;
	while (check) {
		system("cls");
		printCentered("-----Login Employee-----\n", 12);
		string user, pin;
		printCentered("User: ", 9);
		getline(cin, user);
		printCentered("Pin: ", 9);
		
		pin = enterPassword();

		Employee emp(user, pin);
		if (emp.checkLogin(user, pin)) {
			printCentered("Login successfully! Wait a few seconds...\n", 10);
			Sleep(2000);
			system("cls");
			int count = emp.getCount() + 1;
			emp.setCount(count);
			if (count == 1) {
				string oldPass, newPass, againNewPass;
				while (true) {
					system("cls");
					printCentered("First login, need to change password!\n", 9);
					printCentered("Enter password to verify: ", 9);
					oldPass = enterPassword();
					if (oldPass == pin) {
						printCentered("Enter newPass: ", 9);
						newPass = enterPassword();
						if (newPass == pin) {
							printCentered("You have entered your old password.Please re-enter after 2 seconds\n", 4);
							Sleep(2000);
							continue;
						}
						else {
							printCentered("Enter newPass again: ", 9);
							againNewPass = enterPassword();
							if (newPass == againNewPass) {
								emp.setPassWord(newPass);
								emp.updatePassword(emp, user);
								emp.updateInfoEmployee(emp, user);
								printCentered("Change password successfully! Wait a few seconds...\n", 10);
								Sleep(2000);
								return;
							}
							else {
								printCentered("Incorrect Password! Wait 2 seconds to re-enter\n", 4);
								Sleep(2000);
								continue;
							}
						}
					}
					else {
						printCentered("Incorrect Password! Wait 2 seconds to re-enter\n", 4);
						Sleep(2000);
						continue;
					}
				}
			}
			bool checked = true;
			while (checked == true) {
				system("cls");
				emp.menuEmployee();
				printCentered("Enter your choice: ", 15);
				int choice; cin >> choice;
				string fileName = user + ".txt";
				cin.ignore();
				if (choice == 1) {
					emp.loadData(fileName);
					system("cls");
					emp.Show();
					printCentered("Press any key to continue....", 7);
					_getch();
				}
				else if (choice == 2) {
					string oldPass, newPass, againNewPass;
					system("cls");
					printCentered("Enter password to verify: ", 14);
					oldPass = enterPassword();
					if (oldPass == pin) {
						printCentered("Enter newPass: ", 14);
						newPass = enterPassword();
						if (newPass == oldPass) {
							printCentered("You have entered your old password.Please re-enter after 2 seconds\n", 4);
							Sleep(2000);
							continue;
						}
						else {
							printCentered("Enter newPass again: ", 14);
							againNewPass = enterPassword();
							if (newPass == againNewPass) {
								emp.setPassWord(newPass);
								emp.updatePassword(emp, user);
								emp.updateInfoEmployee(emp, user);
								printCentered("Update password successful!\n", 10);
								Sleep(2000);
								break;
							}
							else {
								printCentered("Incorrect password! Please re-enter\n", 4);
								Sleep(2000);
								continue;
							}
						}
					}
					else {
						printCentered("Incorrect verify password! Wait 1.5 seconds to re-enter\n\n", 4);
						Sleep(1500);
					}
				}
				else if (choice == 3) {
					checked = false;
					check = false;
					break;
				}
			}
		}
		else {
			printCentered("Incorrect user or pin! Please re-enter...wait 2 seconds\n", 4);
			Sleep(2000);
			cnt++;
			if (cnt == 3) {
				check = false;
				printCentered("Enter wrong password 3 times, automatically exit\n", 4);
			}
		}
	}
}

int main() {
	bool check = true;
	while (check) {
		int choice = menuStart();
		if (choice == 1) {
			cin.ignore();
			logAdmin();
		}
		else if (choice == 2) {
			cin.ignore();
			logEmployee();
		}
		else {
			check = false;
			break;
		}
	}

	return 0;
}

