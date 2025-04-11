#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <random>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cmath> 

using namespace std;

//-----------------Structures-------------------------------

struct
{
    string memberID;
    string membername;
    string hpNum;
    double purseValue;
    int memberpoint;
} currentData, newData;

struct OrderedItem {
    string name;
    string category; // For pizza, pasta, or sides
    string size;     // Only for pizza
    string setOrAlaCarte; // Add this member to store "Set" or "Ala Carte"
    int quantity;
    double price;
};

//--------------Function Prototypes Declaration-------------

//Function Declarations/Prototypes
//By E-Ian
//Member Login
bool memberLogin();
//Main Menu and Inner Menu
void startupInterface();
void mainMenu();
//Member Registration Module
void memberRegistration(string a);
string cardIDGenerator();
bool memberCardValidation(string card_num);
bool mobileNumberValidation(string hpNum);
//Member Details Module
void memberDetails();
//Read file information
vector<string> readFileInfo(string memberid2);
//Update Member Detail File Content
void modifyFileInfo();
//Compare information of currentdata and newdata structures
bool compareStructData();
//Check for empty string during input
bool checkEmptyString(string input);
//Thank you logo
void thankyoulogo();

//By Ke Shen
//Food Order Module
bool compareOrderedItemsByName(const OrderedItem& a, const OrderedItem& b);
void addToOrder(string itemName1, string category1, string size1, string setOrAlaCarte1);
void option1();
void menu();
void pizzaMenu();
void pastaMenu();
void sidesMenu();
void beveragesMenu();
void modifyOrderedItemQuantity();
void displayOrderedItems();
void payment();
double getItemPrice(string itemName, string category, string size, string setOrAlaCarte);
// Register Logo
void registerlogo();

//By Jia Qi
// Welcome Logo
void welcomelogo();
//Member Top Up Module
int memberTopUp();
//Takeaway food packaging Module
int FoodPackagingModule();

//By Wai Chung
//Food Order Module
bool isSingleDigit(const string& input);
//Payment Module
bool paymentSection(double total);
bool walletBalance(double total);
bool memberPointPayment(double total);

//-----------------------------------------------------------


//-----------------Variable Declarations--------------------

//Global Variable Declaration
string membername, hpNum, memberID, option, mainchoice, subchoice, userInputID;
int idDigits, memberpoint, mPoint;
double purseValue = 0, newPurseValue = 0;
bool _choice;

//Food Order Service Module - Global Declarations
string pizzaName, pastaName, choice;

//Food Order Service Module - Control variable for looping 
bool isValidChoice = false, isValidMenuChoice = false, isValidChoice1 = false, isValidSize = false, isValidSetorAla = false, isValidContinue1 = false, isValidChoice2 = false, isValidContinue2 = false, isValidChoice3 = false, isValidContinue3 = false, isValidChoice4 = false, isValidContinue4 = false, isValidItemNumber = false, isValidQuantity = false, isValidQuantity2 = false, isValidChoice5 = false, isValidClear = false, loop = false;

//-----------------------------------------------------------


//-----------------Other Functions---------------------------

//Welcome Logo
void welcomelogo()
{
    cout << "\t\t\t         ____   ____  _____  _____   ____      __ __  __ __  ____  " << endl;
    cout << "\t\t\t        |    \\ l    j|     T|     T /    T    |  T  T|  T  T|    \\ " << endl;
    cout << "\t\t\t        |  o  ) |  T l__/  |l__/  |Y  o  |    |  l  ||  |  ||  o  )" << endl;
    cout << "\t\t\t        |   _/  |  | |   __j|   __j|     |    |  _  ||  |  ||     T" << endl;
    cout << "\t\t\t        |  |    |  | |  /  ||  /  ||  _  |    |  |  ||  :  ||  O  |" << endl;
    cout << "\t\t\t        |  |    j  l |     ||     ||  |  |    |  |  |l     ||     |" << endl;
    cout << "\t\t\t        l__j   |____jl_____jl_____jl__j__j    l__j__j \\__,_jl_____j" << endl;
}

//Thank you logo
void thankyoulogo()
{
    cout << "\t\t\t  ______  __ __   ____  ____   __  _      __ __   ___   __ __      __ " << endl;
    cout << "\t\t\t |      T|  T  T /    T|    \\ |  l/ ]    |  T  T /   \\ |  T  T    |  T" << endl;
    cout << "\t\t\t |      ||  l  |Y  o  ||  _  Y|  ' /     |  |  |Y     Y|  |  |    |  |" << endl;
    cout << "\t\t\t l_j  l_j|  _  ||     ||  |  ||    \\     |  ~  ||  O  ||  |  |    |__j" << endl;
    cout << "\t\t\t   |  |  |  |  ||  _  ||  |  ||     Y    l___, ||     ||  :  |     __ " << endl;
    cout << "\t\t\t   |  |  |  |  ||  |  ||  |  ||  .  |    |     !l     !l     |    |  T" << endl;
    cout << "\t\t\t   l__j  l__j__jl__j__jl__j__jl__j\\_j    l____/  \\___/  \\__,_j    l__j" << endl;
}

void registerlogo()
{
    cout << "\t\t\t\t ____     ___   ____  ____  _____ ______    ___  ____  " << endl;
    cout << "\t\t\t\t|    \\   /  _] /    |l    j/ ___/|      |  /  _]|    \\ " << endl;
    cout << "\t\t\t\t|  D  ) /  [_ Y   __j |  T(   \\_ |      | /  [_ |  D  )" << endl;
    cout << "\t\t\t\t|    / |    _]|  T  | |  | \\__  |l_j  l_j|    _]|    / " << endl;
    cout << "\t\t\t\t|    \\ |   [_ |  l_ | |  | /  \\ |  |  |  |   [_ |    \\ " << endl;
    cout << "\t\t\t\t|  .  ||     T|     | j  l \\    |  |  |  |     T|  .  Y" << endl;
    cout << "\t\t\t\tl__j\\_jl_____jl___,_j|____j \\___j  l__j  l_____jl__j\\_j" << endl;
}

//Compare structure data
bool compareStructData()
{
    return currentData.memberID == newData.memberID &&
        currentData.membername == newData.membername &&
        currentData.hpNum == newData.hpNum &&
        currentData.purseValue == newData.purseValue &&
        currentData.memberpoint == newData.memberpoint;
}

//File Data Modify Function
void modifyFileInfo()
{
    string line, word;

    fstream fin, temp, fout;

    fin.open("memberinfo.dat", ios::in);
    temp.open("temp.dat", ios::out | ios::app);

    vector<string> row;

    while (getline(fin, line))
    {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ',')) {

            row.push_back(word);

        }

        if (row[0] != newData.memberID)
            temp << line << endl;
    }

    fin.close();
    temp.close();
    remove("memberinfo.dat");
    rename("temp.dat", "memberinfo.dat");

    fout.open("memberinfo.dat", ios::out | ios::app);
    fout << newData.memberID << "," << newData.membername << "," << newData.hpNum << "," << newData.purseValue << "," << newData.memberpoint << "\n";
    fout.close();
}

//Check empty string
bool checkEmptyString(string input)
{
    bool userInput;
    const char* input_c = input.c_str();

    if (input.empty() || input_c[0] == ' ')
    {
        cout << "Invalid input. Please try again" << endl;
        userInput = true;
    }
    else
        userInput = false;

    return userInput;
}

//File Info Retrieve Function
vector<string> readFileInfo(string memberid2) {
    string line, word, memberid1;
    bool found;

    fstream fin;

    fin.open("memberinfo.dat", ios::in);

    vector<string> row;
    vector<string> memberDetails;

    found = false;

    while (getline(fin, line)) {

        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {

            row.push_back(word);

        }

        memberid1 = row[0];

        if (memberid1 == memberid2) {
            memberDetails = row;
            found = true;
            break;
        }
    }

    if (!found) {
        fin.seekg(0, ios::beg); // Reset file pointer to beginning
    }

    fin.close();

    return memberDetails;

}

//User interface on program launch
void startupInterface()
{
    cout << "\t\t\t\t      **********************************************" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      * Welcome to Pizza Hub (Kuala Lumpur Branch) *" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      **********************************************" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      * Please choose an option to proceed:        *" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      * No          Item                           *" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      * 1.          New Member Registration        *" << endl;
    cout << "\t\t\t\t      * 2.          Existing Member Log In         *" << endl;
    cout << "\t\t\t\t      * 3.          Exit Program                   *" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      **********************************************" << endl;
}

//Member Log in Function
bool memberLogin()
{
    string userMemberID;
    vector<string>memberDetails;

    cout << "\nEnter customer Membership ID: ";
    getline(cin, userMemberID);

    memberDetails = readFileInfo(userMemberID);

    if (!memberDetails.empty()) {
        currentData.memberID = newData.memberID = memberDetails[0];
        currentData.membername = newData.membername = memberDetails[1];
        currentData.hpNum = newData.hpNum = memberDetails[2];
        currentData.purseValue = newData.purseValue = stod(memberDetails[3]);
        currentData.memberpoint = newData.memberpoint = stoi(memberDetails[4]);
        return false;
    }
    else {
        cout << "Membership ID not found, please try again." << endl;
        return true;
    }
}

//Home Page
void mainMenu()
{
    system("cls");
    cout << "\t\t\t\t      **********************************************" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      * Pizza Hub (Kuala Lumpur Branch) Main Menu  *" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      **********************************************" << endl;
    cout << "\n";
    cout << "\t\t\t\t\t     Welcome to Pizza Hub, " << newData.membername << "!" << endl;
    cout << "\n";
    cout << "\t\t\t\t      **********************************************" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      *  Please choose an option to proceed:       *" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      *    No            Item                      *" << endl;
    cout << "\t\t\t\t      *    1.            Food Order Service        *" << endl;
    cout << "\t\t\t\t      *    2.            Member Card Top-Up        *" << endl;
    cout << "\t\t\t\t      *    3.            Membership Details        *" << endl;
    cout << "\t\t\t\t      *    4.            Takeaway Packaging        *" << endl;
    cout << "\t\t\t\t      *    5.            Log Out                   *" << endl;
    cout << "\t\t\t\t      *                                            *" << endl;
    cout << "\t\t\t\t      **********************************************" << endl;
}

//-----------------------------------------------------------


//-----------------Member Registration Module----------------

//User Input Function
void memberRegistration(string id)
{
    bool result = true;

    fstream fout;
    fout.open("memberinfo.dat", ios::out | ios::app);

    system("cls");
    cout << "\t\t\t   =================================================================" << "\n";
    registerlogo();
    cout << "\n\t\t\t   =================================================================" << "\n";
    cout << "\n\t\t\t\t ******************************************************\n\n"
        "\t\t\t\t  Welcome to Pizza Hub's Customer Registration Portal!\n\n"
        "\t\t\t\t ******************************************************\n\n";

    do
    {
        cout << "\nPlease enter the customer's name (Alphabets only) : ";
        getline(cin, membername);

        if (checkEmptyString(membername))
        {
            result = false;
        }
        else
        {
            for (int i = 0; i < membername.length(); i++)
            {
                if (isblank(membername[i]) || isalpha(membername[i]))
                {
                    result = true;
                }
                else
                {
                    result = false;
                    cout << "Name contains invalid characters, please try again." << endl;
                    break;
                }
            }
        }

    } while (result == false);

    do {

        do {
            cout << "\nPlease enter the mobile number (Digits only) : ";
            getline(cin, hpNum);
        } while (checkEmptyString(hpNum));

    } while (!mobileNumberValidation(hpNum));

    memberID = id;
    memberpoint = 0;
    system("cls");
    cout << "\n\t\t\t         ************************************************" << "\n\n";
    cout << "\t\t\t\t         Member registration is successful!" << "\n\n";
    cout << "\t\t\t         *************************************************" << endl;
    cout << "\n\t\t\t         Pizza Hub Customer Membership Details" << "\n\n";
    cout << "\t\t\t         Member ID             : " << memberID << endl;
    cout << "\t\t\t         Member Name           : " << membername << endl;
    cout << "\t\t\t         Mobile Number         : " << hpNum << endl;
    cout << "\t\t\t         Current Purse Value   : " << "RM " << fixed << showpoint << setprecision(2) << purseValue << endl;
    cout << "\t\t\t         Current Member Points : " << memberpoint << " points" << "\n\n";
    cout << "\t\t\t         *************************************************" << endl;

    fout << memberID << "," << membername << "," << hpNum << "," << purseValue << "," << memberpoint << "\n";

    fout.close();
}

//Mobile Number Validation
bool mobileNumberValidation(string hpNum)
{
    string line, word, _hpNum;
    fstream fin;

    fin.open("memberinfo.dat", ios::in);

    if (!fin) {
        cout << "File not found. A new file will be created." << endl;
        return false;
    }

    vector<string> row;

    while (getline(fin, line)) {

        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {

            row.push_back(word);

        }

        _hpNum = row[2];

        if (_hpNum == hpNum) {
            cout << "Mobile number existed, please try again." << endl;
            fin.close();
            return false;
        }
    }

    if (!(all_of(hpNum.begin(), hpNum.end(), ::isdigit)))
    {
        cout << "Please enter digits only." << endl;
        return false;
    }

    int a = hpNum.length();

    if (a < 10 || a > 11)
    {
        cout << "Please enter minimum 10 digits and maximum 11 digits for mobile number." << endl;
        return false;
    }

    if (hpNum[0] != '0')
    {
        cout << "Mobile number should start with \"0\". Please try again." << endl;
        return false;
    }

    fin.close();
    return true;
}

//Card ID Generator
string cardIDGenerator()
{
    string _memberID;
    do
    {
        srand(time(NULL));
        _memberID = to_string(1 + (rand() % 999999));
        for (int a = _memberID.length(); a < 6; a++) {
            _memberID = "0" + _memberID;
        }
        _memberID = "PZH" + _memberID;
    } while (!memberCardValidation(_memberID));
    return _memberID;
}

//Membership ID Validation
bool memberCardValidation(string card_num)
{
    string line, word, memberid1;
    fstream fin;

    fin.open("memberinfo.dat", ios::in);

    if (!fin) {
        cout << "Error Opening the file. New file will be created." << endl;
        return false;
    }

    vector<string> row;

    while (getline(fin, line)) {

        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {

            row.push_back(word);

        }

        memberid1 = row[0];

        if (card_num == memberid1) {
            fin.close();
            return false;
        }

    }

    fin.close();
    return true;
}

//-----------------------------------------------------------


//-----------------Member Details Module---------------------

//Member Details Function
void memberDetails()
{
    system("cls");
    cout << "\n\t\t\t\t    Here are the member details!" << endl;
    cout << "\n";
    cout << "\t\t\t\t    *****************************************" << endl;
    cout << "\n";
    cout << "\t\t\t\t    Pizza Hub Customer Membership Details" << endl;
    cout << "\n\t\t\t\t    Member ID             : " << newData.memberID << endl;
    cout << "\t\t\t\t    Member Name           : " << newData.membername << endl;
    cout << "\t\t\t\t    Mobile Number         : " << newData.hpNum << endl;
    cout << "\t\t\t\t    Current Purse Value   : " << "RM " << fixed << showpoint << setprecision(2) << newData.purseValue << endl;
    cout << "\t\t\t\t    Current Member Points : " << newData.memberpoint << " points" << endl;
    cout << "\n";
    cout << "\t\t\t\t    *****************************************" << endl;
}

//-----------------------------------------------------------


//-----------------Member Top Up Module----------------------

//Member Top Up Function
int memberTopUp()
{
    string user_selection, new_option;
    double current_balance, final_balance, payable_amount, errorMsg = 0.0;
    double service_charge, option_A, option_B, option_C, option_D;
    bool continue_loop = false, _continue = false, continueTopUp = false, contTopUp = false;

    option_A = 5.00;
    option_B = 10.00;
    option_C = 30.00;
    option_D = 50.00;
    service_charge = 0.50;
    current_balance = 0.00;
    payable_amount = 0.00;
    final_balance = 0.00;

    system("cls");
    cout << "\t\t\t\t*************************************************************" << endl;
    cout << "\n\t\t\t\t\t       Welcome to Pizza Hub Top Up Portal!" << endl << endl;
    cout << "\t\t\t\t*************************************************************\n" << endl;
    cout << "\t\t\t\t*************************************************************" << endl;
    cout << "\n\t\t\t\tPizza Hub Customer Purse Value & Membership Points Details" << endl << endl;
    cout << "\t\t\t\tMember ID             : " << newData.memberID << endl;
    cout << "\t\t\t\tCurrent Purse Value   : " << "RM " << fixed << showpoint << setprecision(2) << newData.purseValue << endl;
    cout << "\t\t\t\tCurrent Member Points : " << newData.memberpoint << " points" << "\n\n";
    cout << "\t\t\t\t*************************************************************" << endl;
    do {
        cout << "\n\t\t\t\t     **************************************************\n\n"
            "\t\t\t\t         Top Up Option\n\n"
            "\t\t\t\t         Please Select One Option Only (A/B/C/D/E ):\n"
            "\t\t\t\t         A \t\t Top Up RM 5.00 \n"
            "\t\t\t\t         B \t\t Top Up RM 10.00\n"
            "\t\t\t\t         C \t\t Top Up RM 30.00\n"
            "\t\t\t\t         D \t\t Top Up RM 50.00\n"
            "\t\t\t\t         E \t\t Cancel Top-Up\n\n"
            "\t\t\t\t     **************************************************\n" << endl;
        do
        {
            cout << "Enter Top Up Option(only one): ";
            getline(cin, user_selection);

            cout << "\n";
            if (user_selection == "A" || user_selection == "a")
            {
                current_balance = current_balance + option_A;
                final_balance = current_balance;
                payable_amount = payable_amount + option_A + service_charge;
                _continue = true;
                cout << "Your Current Selected Amount= RM " << final_balance << endl;
                cout << "Your Payable Amount= RM " << payable_amount << endl;

            }
            else if (user_selection == "B" || user_selection == "b")
            {
                current_balance = current_balance + option_B;
                final_balance = current_balance;
                payable_amount = payable_amount + option_B + service_charge;
                _continue = true;
                cout << "Your Current Selected Amount= RM " << final_balance << endl;
                cout << "Your Payable Amount= RM " << payable_amount << endl;
            }
            else if (user_selection == "C" || user_selection == "c")
            {
                current_balance = current_balance + option_C;
                final_balance = current_balance;
                payable_amount = payable_amount + option_C + service_charge;
                _continue = true;
                cout << "Your Current Selected Amount= RM " << final_balance << endl;
                cout << "Your Payable Amount= RM " << payable_amount << endl;
            }
            else if (user_selection == "D" || user_selection == "d")
            {
                current_balance = current_balance + option_D;
                final_balance = current_balance;
                payable_amount = payable_amount + option_D + service_charge;
                _continue = true;
                cout << "Your Current Selected Amount= RM " << final_balance << endl;
                cout << "Your Payable Amount= RM " << payable_amount << endl;
            }
            else if (user_selection == "E" || user_selection == "e")
            {
                return 0;
            }
            else
            {
                cout << "Invalid input\n";
                _continue = false;
                continue_loop = true;
            }

            if (_continue)
            {
                continueTopUp = true;

                while (continueTopUp == true)
                {
                    cout << "\nWish to top up for more? (Y = Continue, N = Confirm Top Up): ";
                    getline(cin, new_option);

                    cout << "\n";
                    if (new_option == "Y" || new_option == "y")
                    {
                        system("cls");
                        contTopUp = true;
                        continue_loop = false;
                        continueTopUp = false;
                    }
                    else if (new_option == "N" || new_option == "n")
                    {
                        system("cls");
                        cout << "\n\t\t\t\t     **************************************************";
                        cout << "\n";
                        cout << "\n\t\t\t\t     Hereby attached the Top-Up receipt: " << endl;
                        cout << "\n";
                        cout << "\n\t\t\t\t     The final top up value: RM " << final_balance << endl;
                        cout << "\n\t\t\t\t     The payable amount: RM " << payable_amount << endl;
                        cout << "\n";
                        cout << "\t\t\t\t     **************************************************\n";
                        cout << "\n";
                        newData.purseValue += final_balance;
                        continue_loop = false;
                        continueTopUp = false;
                        contTopUp = false;
                    }
                    else
                    {
                        cout << "Invalid Input\n";
                    }
                }
            }
        } while (continue_loop == true);

    } while (contTopUp == true);

}

//-----------------------------------------------------------


//-----------------TakeAway Packaging Module-----------------

int FoodPackagingModule()
{
    int small = 0, large = 0, charge_small = 0, charge_large = 0, amount;
    double total_charge = 0.0;
    string boxType, boxNum, rptoption, paymentPrompt;
    bool invalidInput = false, rpttakeaway = false, paymentV = false;

    system("cls");
    cout << "\t\t\t\t    *****************************************" << endl;
    cout << "\n";
    cout << "\t\t\t\t\t  PIZZA HUB FOOD PACKAGING PAGE" << endl;
    cout << "\n";
    do {
        cout << "\t\t\t\t    *****************************************\n" << endl;
        cout << "\t\t\t\t    Type of boxes required: " << endl;
        cout << "\n";
        cout << "\t\t\t\t    1.\t Small Box" << endl;
        cout << "\t\t\t\t    2.\t Large Box" << endl;
        cout << "\t\t\t\t    3.\t Back to Main Menu\n" << endl;
        cout << "\t\t\t\t    ******************************************\n" << endl;
        do {
            cout << "Please enter type of box: ";
            getline(cin, boxType);

            if (boxType == "1")
            {
                do
                {
                    try {
                        cout << "Enter number of small boxes: ";
                        getline(cin, boxNum);

                        amount = stoi(boxNum);
                        small += amount;
                        charge_small = 2 * small;
                        invalidInput = false;
                    }
                    catch (const exception&) {
                        cout << "Invalid input. Please enter again.\n" << endl;
                        invalidInput = true;
                    }

                } while (invalidInput == true);

            }
            else if (boxType == "2") {
                do
                {
                    try {
                        cout << "Enter number of large boxes: ";
                        getline(cin, boxNum);

                        amount = stoi(boxNum);
                        large += amount;
                        charge_large = 2 * large;
                        invalidInput = false;
                    }
                    catch (const exception&) {
                        cout << "Invalid input. Please enter again.\n" << endl;
                        invalidInput = true;
                    }

                } while (invalidInput == true);
            }
            else if (boxType == "3") {
                return 0;
            }
            else {
                cout << "Invalid input. Please enter again.\n" << endl;
                invalidInput = true;
            }

        } while (invalidInput == true);

        total_charge = charge_small + charge_large;
        system("cls");
        cout << endl;
        cout << "\t\t\t\t    **************************************************\n" << endl;
        cout << "\t\t\t\t    Current amount of boxes: \n" << endl;
        cout << "\t\t\t\t    Small boxes: " << small << endl;
        cout << "\t\t\t\t    Large boxes: " << large << endl;
        cout << "\t\t\t\t    Amount charged: RM" << fixed << setprecision(2) << total_charge << endl;
        cout << "\n\t\t\t\t    **************************************************\n" << endl;

        do {
            cout << "Wish to add more boxes? (Y/N): ";
            getline(cin, rptoption);

            if (rptoption == "Y" || rptoption == "y")
            {
                system("cls");
                cout << "\n";
                invalidInput = false;
                rpttakeaway = true;
            }
            else if (rptoption == "N" || rptoption == "n") {

                invalidInput = false;
                rpttakeaway = false;
            }
            else {
                cout << "Invalid input. Please enter again.\n";
                cout << "\n";
                invalidInput = true;
            }

        } while (invalidInput == true);

    } while (rpttakeaway == true);
    system("cls");
    cout << endl;
    cout << "\t\t\t\t    **************************************************\n" << endl;
    cout << "\t\t\t\t    TOTAL PACKAGING\n" << endl;
    cout << "\t\t\t\t    Total number of small boxes: " << small << endl;
    cout << "\t\t\t\t    Total number of large boxes: " << large << endl;
    cout << "\t\t\t\t    Total amount payable: RM" << fixed << setprecision(2) << total_charge << endl;
    cout << "\n\t\t\t\t    ***************************************************" << endl;
    cout << "\n";

    do {
        cout << "Proceed to payment page? (Y = Yes / N = Cancel Order): ";
        getline(cin, paymentPrompt);

        if (paymentPrompt == "Y" || paymentPrompt == "y")
        {
            paymentV = paymentSection(total_charge);
            if (paymentV == true) {
                cout << "Membership Points earned: " << mPoint << " points" << endl;
                cout << "Your updated wallet balance is: RM" << newData.purseValue << endl;
                cout << "Your updated membership point balance is: " << newData.memberpoint << " points" << endl;
                cout << "\n";
                mPoint = 0;
                invalidInput = false;
            }
            else
            {
                cout << "Order Cancelled." << endl;
                invalidInput = false;
            }
        }
        else if (paymentPrompt == "N" || paymentPrompt == "n")
        {
            invalidInput = false;
        }
        else {
            cout << "Invalid input. Please enter again.\n";
            cout << "\n";
            invalidInput = true;
        }

    } while (invalidInput == true);
}

//-----------------------------------------------------------


//-----------------------------------Food Order Service Module----------------------------------------------

vector<OrderedItem> orderedItems;

// function to sort OrderedItem objects by name
bool compareOrderedItemsByName(const OrderedItem& a, const OrderedItem& b) {
    return a.name < b.name;
}

//Check single digit
bool isSingleDigit(const string& input) {
    return input.length() == 1 && std::isdigit(input[0]);
}

// Function to add an item to the orderedItems vector
void addToOrder(string itemName1, string category1, string size1 = "", string setOrAlaCarte1 = "") {
    // Check if the item is already in the orderedItems vector
    bool found = false;
    for (auto& item : orderedItems) {
        if (item.name == itemName1 && item.category == category1 && item.size == size1 && item.setOrAlaCarte == setOrAlaCarte1) {
            item.quantity++;
            found = true;
            break;
        }
    }
    if (!found) {
        orderedItems.push_back({ itemName1, category1, size1, setOrAlaCarte1, 1 });
    }
}

// Function to calculate item price based on name, category, size, and set/ala carte
double getItemPrice(string itemName, string category, string size, string setOrAlaCarte) {
    // Implement your pricing logic here
    double price = 0.0;  // Initialize with a default price

    if (category == "Pizza") {
        // Example pricing logic for Regular and Large sizes
        if (size == "Regular") {
            if (itemName == "Hawaiian Chicken" || itemName == "Chicken Pepperoni" || itemName == "Aloha Chicken" || itemName == "Island Tuna" || itemName == "Veggie Lover" || itemName == "Deluxe Cheese") {
                price = 35.90;
            }
            else {
                price = 39.30;
            }
        }
        else if (size == "Large") {
            if (itemName == "Hawaiian Chicken" || itemName == "Chicken Pepperoni" || itemName == "Aloha Chicken" || itemName == "Island Tuna" || itemName == "Veggie Lover" || itemName == "Deluxe Cheese") {
                price = 47.90;
            }
            else {
                price = 52.30;
            }
        }
    }
    else if (category == "Pasta") {
        if (itemName == "Classic Tomato Spaghetti" || itemName == "Chicken Pepperoni Spaghetti" || itemName == "Aloha Olio Spaghetti") {
            price = 15.50;
        }
        else {
            price = 17.50;
        }
    }
    else if (category == "Sides") {
        if (itemName == "Huts Poppers Hash Bites" || itemName == "Huts Poppers Sausage" || itemName == "Huts Poppers Chicken Bites") {
            price = 7.90;
        }
        else if (itemName == "Huts Breadstix Mozzarella") {
            price = 7.90;
        }
        else if (itemName == "Chessy Flatbread") {
            price = 6.90;
        }
        else if (itemName == "Mama Mia Meatballs") {
            price = 12.90;
        }
        else if (itemName == "Krispy Onion Rings") {
            price = 8.90;
        }
        else if (itemName == "Krispy Wedges") {
            price = 7.90;
        }
        else if (itemName == "Krispy Fries") {
            price = 6.90;
        }
        else if (itemName == "Mushroom Soup") {
            price = 4.90;
        }
    }
    else {
        if (itemName == "Coke" || itemName == "Sprite" || itemName == "Fanta Strawberry" || itemName == "Fuze Lemon Tea") {
            price = 5.50;
        }
        else if (itemName == "Peach Tea") {
            price = 4.90;
        }
        else if (itemName == "Minute Maid Plus Orange") {
            price = 9.70;
        }
        else if (itemName == "Mineral Water") {
            price = 3.00;
        }
    }
    // Apply pricing adjustments for set or ala carte
    if (setOrAlaCarte == "Set") {
        price += 5.00;
    }

    return price;
}

bool isTakeaway = false; // Initialize the flag as false

//Food Menu
void option1()
{
    system("cls");
    cout << "\t    ===================================================================================================" << "\n";
    cout << "\t     _______  _______  _______  ______     _______  _______  ______    __   __  ___   _______  _______ " << "\n";
    cout << "\t    |       ||       ||       ||      |   |       ||       ||    _ |  |  | |  ||   | |       ||       |" << "\n";
    cout << "\t    |    ___||   _   ||   _   ||  _    |  |  _____||    ___||   | ||  |  |_|  ||   | |       ||    ___|" << "\n";
    cout << "\t    |   |___ |  | |  ||  | |  || | |   |  | |_____ |   |___ |   |_||_ |       ||   | |       ||   |___ " << "\n";
    cout << "\t    |    ___||  |_|  ||  |_|  || |_|   |  |_____  ||    ___||    __  ||       ||   | |      _||    ___|" << "\n";
    cout << "\t    |   |    |       ||       ||       |   _____| ||   |___ |   |  | | |     | |   | |     |_ |   |___ " << "\n";
    cout << "\t    |___|    |_______||_______||______|   |_______||_______||___|  |_|  |___|  |___| |_______||_______|" << "\n";
    cout << "\t                                                                                                       " << "\n";
    cout << "\t    ===================================================================================================" << "\n\n";
    cout << "\t\t\t\t\t\t  Welcome to Food Service" << "\n\n";
    // Ask customer dine-in or takeaway
    cout << "\t\t\t\t\t\t    Dine-in or Takeaway" << "\n\n";

    string choice;
    // Validation of choice
    // Loop until the input is successfully read
    while (!isValidChoice) {
        cout << "Please enter your choice (D for dine-in, T for takeaway): ";
        getline(cin, choice);

        // Make sure there are no other characters in the input buffer
        if (choice == "D" || choice == "d") {
            system("cls");
            cout << "\nYou have chosen dine-in. Enjoy your meal at PizzaHub!" << "\n\n";
            // Set the flag for dine-in
            isTakeaway = false;
            menu();
            isValidChoice = true; // Break out of the loop if it is true
        }
        else if (choice == "T" || choice == "t") {
            system("cls");
            cout << "\nYou have chosen takeaway. Your order will be packed for pickup." << "\n\n";
            // Set the flag for takeaway
            isTakeaway = true;
            menu();
            isValidChoice = true; // Break out of the loop if it is true    
        }
        else {
            cout << "Invalid choice. Please select D for dine-in or T for takeaway." << "\n\n";
            isValidChoice = false; // Continue loop if it is false
        }
    }
    isValidChoice = false;
}

//Food Menu
void menu()
{
    do {
        //Show Food Menu
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                               Welcome to the Food Menu                               ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||    1. Pizza Menu                                                                     ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||    2. Pasta Menu                                                                     ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||    3. Sides Menu                                                                     ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||    4. Beverages Menu                                                                 ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||    C. Currently Order                                                                ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||    P. Checkout                                                                       ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||    X. Back to Main-Menu (Ordered items will be clear)                                ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";

        string menuChoice;
        // Validation of menuChoice
        // Loop until the input is successfully read
        while (!isValidMenuChoice) {
            cout << "Please enter your choice : ";
            getline(cin, menuChoice);
            // Make sure there are no other characters in the input buffer
            if (menuChoice == "1") {
                pizzaMenu(); // Call the pizzaMenu() function for pizza menu
                isValidMenuChoice = true; // Break out of the loop if it is true    
                loop = true;
            }
            else if (menuChoice == "2") {
                pastaMenu(); // Call the pastaMenu() function for pasta menu
                isValidMenuChoice = true; // Break out of the loop if it is true 
                loop = true;
            }
            else if (menuChoice == "3") {
                sidesMenu(); // Call the sidesMenu() function for sides menu
                isValidMenuChoice = true; // Break out of the loop if it is true 
                loop = true;
            }
            else if (menuChoice == "4") {
                beveragesMenu(); // Call the beveragesMenu() function for beverages menu
                isValidMenuChoice = true; // Break out of the loop if it is true 
                loop = true;
            }
            else if (menuChoice == "C" || menuChoice == "c") {
                system("cls");
                displayOrderedItems(); // Display the currently ordered items
                isValidMenuChoice = true; // Break out of the loop if it is true 
                loop = true;
            }
            else if (menuChoice == "P" || menuChoice == "p") {
                payment(); // Call the proceedToPayment() function for payment
                isValidMenuChoice = true; // Break out of the loop if it is true 
                loop = false;
            }
            else if (menuChoice == "X" || menuChoice == "x") {
                if (orderedItems.empty()) {
                    isValidMenuChoice = true; // Break out of the loop if it is true 
                    loop = false;
                }
                else {
                    orderedItems.clear();
                    cout << "\n";
                    cout << "OrderedItems Cleared!" << "\n";
                    isValidMenuChoice = true; // Break out of the loop if it is true 
                    loop = false;
                }
            }
            else {
                cout << "Invalid choice. Please select 1 - 4 only." << "\n\n";
                isValidMenuChoice = false; // Continue loop if it is false
            }
        }
        isValidMenuChoice = false;
    } while (loop == true);
}

//Pizza Menu
void pizzaMenu() {
    system("cls");
    do {
        // show PizzaMenu
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                              Welcome to the Pizza Menu                               ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    1.  Aloha Chicken " << " R - RM 35.90 L - RM 47.90    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    2.  Blazing Seafood " << " R - RM 39.30 L - RM 52.30    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    3.  Chicken Pepperoni " << " R - RM 35.90 L - RM 47.90    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    4.  Creamy Crispy Chicken " << " R - RM 39.30 L - RM 52.30    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    5.  Deluxe Cheese " << " R - RM 35.90 L - RM 47.90    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    6.  Hawaiian Chicken " << " R - RM 35.90 L - RM 47.90    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    7.  Hawaiian Supreme " << " R - RM 39.30 L - RM 52.30    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    8.  Island Tuna " << " R - RM 35.90 L - RM 47.90    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    9.  Triple Chicken " << " R - RM 39.30 L - RM 52.30    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||   10.  Veggie Lover " << " R - RM 35.90 L - RM 47.90    ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||              (Upgrade to Set: +RM 5.00 - Mushroom Soup + Mineral Water)              ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||    X. Back to Food Menu                                                              ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";


        string cc1[10] = { "Aloha Chicken", "Blazing Seafood", "Chicken Pepperoni", "Creamy Crispy Chicken", "Deluxe Cheese", "Hawaiian Chicken", "Hawaiian Supreme", "Island Tuna", "Triple Chicken", "Veggie Lover" };
        string choice1Str;
        const char* choice1 = choice1Str.c_str();
        bool continuing1 = true;
        int cho1;
        // Validation of choice1
        // Loop until the input is successfully read

        while (!isValidChoice1) {
            continuing1 = true;
            cout << "Please enter your choice : ";
            getline(cin, choice1Str);

            if (choice1Str == "X" || choice1Str == "x") {
                continuing1 = false;
                loop = false;
                system("cls");
                isValidChoice1 = true; // Break out of the loop if it is true 
            }
            else if (choice1Str == "10") {
                cout << "You have chosen " << cc1[10 - 1] << "." << "\n\n";
                pizzaName = cc1[10 - 1];
                isValidChoice1 = true; // Break out of the loop if it is true 
            }
            else {
                if (isSingleDigit(choice1Str)) {
                    cho1 = choice1[0] - '0'; // Convert char to int
                    if (cho1 >= 1 && cho1 <= 10) {
                        cout << "You have chosen " << cc1[cho1 - 1] << "." << "\n\n";
                        pizzaName = cc1[cho1 - 1];
                        isValidChoice1 = true; // Break out of the loop if it is true 
                    }
                    else {
                        cout << "Invalid choice. Please select 1 - 10 only or X for Back to Food Menu." << "\n\n";
                        isValidChoice1 = false; // Continue loop if it is false
                    }
                }
                else {
                    cout << "Invalid choice. Please select 1 - 10 only or X for Back to Food Menu." << "\n\n";
                    isValidChoice1 = false; // Continue loop if it is false
                }
            }
        }
        isValidChoice1 = false; // Let it as false for user can loop again

        if (continuing1 == true) {
            string size;
            cout << "Pizza Size : Regular or Large (R or L):" << "\n";
            // Validation of size
            // Loop until the input is successfully read
            while (!isValidSize) {
                cout << "Please enter your choice (R for Regular, L for Large): ";
                getline(cin, size);
                // Make sure there are no other characters in the input buffer
                if (size == "R" || size == "r") {
                    cout << "You have chosen Regular Size." << "\n\n";
                    size = "Regular";  // Change "R" to "Regular"
                    isValidSize = true; // Break out of the loop if it is true 
                }
                else if (size == "L" || size == "l") {
                    cout << "You have chosen Large Size." << "\n\n";
                    size = "Large";  // Change "L" to "Large"
                    isValidSize = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select R for Regular Size or L for Large Size." << "\n\n";
                    isValidSize = false; // Continue loop if it is false
                }
            }

            isValidSize = false; // Let it as false for user can loop again

            string setOrAlaCarte;
            cout << "Set or Ala Carte? (S for Set, A for Ala Carte):" << "\n";
            // Validation of setOrAlaCarte
            // Loop until the input is successfully read
            while (!isValidSetorAla) {
                cout << "Please enter your choice (S for Set, A for Ala Carte): ";
                getline(cin, setOrAlaCarte);
                // Make sure there are no other characters in the input buffer
                if (setOrAlaCarte == "S" || setOrAlaCarte == "s") {
                    cout << "You have chosen Set Meal." << "\n\n";
                    addToOrder(pizzaName, "Pizza", size, "Set");
                    isValidSetorAla = true; // Break out of the loop if it is true 
                }
                else if (setOrAlaCarte == "A" || setOrAlaCarte == "a") {
                    cout << "You have chosen Ala Carte." << "\n\n";
                    addToOrder(pizzaName, "Pizza", size, "Ala Carte");
                    isValidSetorAla = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select S for Set Meal or A for Ala Carte." << "\n\n";
                    isValidSetorAla = false; // Continue loop if it is false 
                }
            }
            isValidSetorAla = false; // Let it as false for user can loop again

            string continue1;
            cout << "Do you want to continue order?" << "\n";
            // Validation of continue2
            // Loop until the input is successfully read
            while (!isValidContinue1) {
                cout << "Please enter your choice (Y for Continue, N for Confirm): ";
                getline(cin, continue1);
                // Make sure there are no other characters in the input buffer
                if (continue1 == "Y" || continue1 == "y") {
                    system("cls");
                    loop = true;
                    isValidContinue1 = true; // Break out of the loop if it is true 
                }
                else if (continue1 == "N" || continue1 == "n") {
                    system("cls");
                    loop = false;
                    isValidContinue1 = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select Y for Continue Order or N for Confirm Order." << "\n\n";
                    isValidContinue1 = false; // Continue loop if it is false 
                }
            }
            isValidContinue1 = false; // Let it as false for user can loop again
        }
    } while (loop == true);
}

//Pasta Menu
void pastaMenu() {
    system("cls");
    do {
        // show PastaMenu
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                              Welcome to the Pasta Menu                               ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(75) << setfill('.') << left << "\t\t||    1.  Aloha Olio Spaghetti " << " RM 15.50      ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(75) << setfill('.') << left << "\t\t||    2.  Asam Pedas Spaghetti " << " RM 17.50      ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(75) << setfill('.') << left << "\t\t||    3.  Chicken Bolognaise Spaghetti " << " RM 17.50      ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(75) << setfill('.') << left << "\t\t||    4.  Chicken Pepperoni Spaghetti " << " RM 15.50      ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(75) << setfill('.') << left << "\t\t||    5.  Classic Tomato Spaghetti " << " RM 15.50      ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(75) << setfill('.') << left << "\t\t||    6.  Creamy Carbonara Spaghetti " << " RM 17.50      ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(75) << setfill('.') << left << "\t\t||    7.  Salami Olio Spaghetti " << " RM 17.50      ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||              (Upgrade to Set: +RM 5.00 - Mushroom Soup + Mineral Water)              ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||    X. Back to Food Menu                                                              ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";

        string cc2[7] = { "Aloha Olio Spaghetti", "Asam Pedas Spaghetti", "Chicken Bolognaise Spaghetti", "Chicken Pepperoni Spaghetti", "Classic Tomato Spaghetti", "Creamy Carbonara Spaghetti", "Salami Olio Spaghetti" };
        string choice2Str;
        const char* choice2 = choice2Str.c_str();
        bool continuing2 = true;
        int cho2;
        // Validation of choice2
        // Loop until the input is successfully read

        while (!isValidChoice2) {
            cout << "Please enter your choice : ";
            getline(cin, choice2Str);

            if (choice2Str == "X" || choice2Str == "x") {
                system("cls");
                loop = false;
                continuing2 = false;
                isValidChoice2 = true; // Break out of the loop if it is true 
            }
            else {
                if (isSingleDigit(choice2Str)) {
                    cho2 = choice2[0] - '0'; // Convert char to int
                    if (cho2 >= 1 && cho2 <= 7) {
                        cout << "You have chosen " << cc2[cho2 - 1] << "." << "\n\n";
                        pastaName = cc2[cho2 - 1];
                        isValidChoice2 = true; // Break out of the loop if it is true 
                    }
                    else {
                        cout << "Invalid choice. Please select 1 - 7 only or X for Back to Food Menu." << "\n\n";
                        isValidChoice2 = false; // Continue loop if it is false
                    }
                }
                else {
                    cout << "Invalid choice. Please select 1 - 7 only or X for Back to Food Menu." << "\n\n";
                    isValidChoice2 = false; // Continue loop if it is false
                }
            }
        }
        isValidChoice2 = false; // Let it as false for user can loop again

        if (continuing2 == true) {
            string setOrAlaCarte;
            cout << "Set or Ala Carte? (S for Set, A for Ala Carte):" << "\n";
            // Validation of setOrAlaCarte
            // Loop until the input is successfully read
            while (!isValidSetorAla) {
                cout << "Please enter your choice (S for Set, A for Ala Carte): ";
                getline(cin, setOrAlaCarte);
                // Make sure there are no other characters in the input buffer
                if (setOrAlaCarte == "S" || setOrAlaCarte == "s") {
                    cout << "You have chosen Set Meal." << "\n\n";
                    addToOrder(pastaName, "Pasta", "", "Set");
                    isValidSetorAla = true; // Break out of the loop if it is true 
                }
                else if (setOrAlaCarte == "A" || setOrAlaCarte == "a") {
                    cout << "You have chosen Ala Carte." << "\n\n";
                    addToOrder(pastaName, "Pasta", "", "Ala Carte");
                    isValidSetorAla = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select S for Set Meal or A for Ala Carte." << "\n\n";
                    isValidSetorAla = false; // Continue loop if it is false
                }
            }

            isValidSetorAla = false; // Let it as false for user can loop again

            string continue2;
            cout << "Do you want to continue order?" << "\n";
            // Validation of continue2
            // Loop until the input is successfully read
            while (!isValidContinue2) {
                cout << "Please enter your choice (Y for Continue, N for Confirm): ";
                getline(cin, continue2);
                // Make sure there are no other characters in the input buffer
                if (continue2 == "Y" || continue2 == "y") {
                    system("cls");
                    loop = true;
                    isValidContinue2 = true; // Break out of the loop if it is true 
                }
                else if (continue2 == "N" || continue2 == "n") {
                    system("cls");
                    loop = false;
                    isValidContinue2 = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select Y for Continue Order or N for Confirm Order." << "\n\n";
                    isValidContinue2 = false; // Continue loop if it is false
                }
            }
            isValidContinue2 = false; // Let it as false for user can loop again
        }
    } while (loop == true);
}

//Sides Menu
void sidesMenu() {
    system("cls");
    do {
        // show Sides Menu
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                              Welcome to the Sides Menu                               ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    1.  Chessy Flatbread " << " RM 6.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    2.  Huts Breadstix Mozzarella " << " RM 7.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    3.  Huts Poppers Chicken Bites " << " RM 7.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    4.  Huts Poppers Hash Bites " << " RM 7.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    5.  Huts Poppers Sausage " << " RM 7.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    6.  Krispy Fries " << " RM 6.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    7.  Krispy Onion Rings " << " RM 8.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    8.  Krispy Wedges " << " RM 7.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    9.  Mama Mia Meatballs " << " RM 12.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||   10.  Mushroom Soup " << " RM 4.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||    X. Back to Food Menu                                                              ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";

        string cc3[10] = { "Chessy Flatbread", "Huts Breadstix Mozzarella", "Huts Poppers Chicken Bites", "Huts Poppers Hash Bites", "Huts Poppers Sausage", "Krispy Fries", "Krispy Onion Rings", "Krispy Wedges", "Mama Mia Meatballs", "Mushroom Soup" };
        string choice3Str;
        const char* choice3 = choice3Str.c_str();
        bool continuing3 = true;
        int cho3;
        // Validation of choice3
        // Loop until the input is successfully read

        while (!isValidChoice3) {
            cout << "Please enter your choice : ";
            getline(cin, choice3Str);

            if (choice3Str == "X" || choice3Str == "x") {
                system("cls");
                loop = false;
                continuing3 = false;
                isValidChoice3 = true; // Break out of the loop if it is true 
            }
            else if (choice3Str == "10") {
                cout << "You have chosen " << cc3[10 - 1] << "." << "\n\n";
                addToOrder(cc3[10 - 1], "Sides");
                isValidChoice3 = true; // Break out of the loop if it is true 
            }
            else {
                if (isSingleDigit(choice3Str)) {
                    cho3 = choice3[0] - '0'; // Convert char to int
                    if (cho3 >= 1 && cho3 <= 10) {
                        cout << "You have chosen " << cc3[cho3 - 1] << "." << "\n\n";
                        addToOrder(cc3[cho3 - 1], "Sides");
                        isValidChoice3 = true; // Break out of the loop if it is true 
                    }
                    else {
                        cout << "Invalid choice. Please select 1 - 10 only or X for Back to Food Menu." << "\n\n";
                        isValidChoice3 = false; // Continue loop if it is false
                    }
                }
                else {
                    cout << "Invalid choice. Please select 1 - 10 only or X for Back to Food Menu." << "\n\n";
                    isValidChoice3 = false; // Continue loop if it is false
                }
            }
        }
        isValidChoice3 = false; // Let it as false for user can loop again
        if (continuing3 == true) {
            string continue3;
            cout << "Do you want to continue order?" << "\n";
            // Validation of continue1
            // Loop until the input is successfully read
            while (!isValidContinue3) {
                cout << "Please enter your choice (Y for Continue, N for Confirm): ";
                getline(cin, continue3);
                // Make sure there are no other characters in the input buffer
                if (continue3 == "Y" || continue3 == "y") {
                    system("cls");
                    loop = true;
                    isValidContinue3 = true; // Break out of the loop if it is true 
                }
                else if (continue3 == "N" || continue3 == "n") {
                    system("cls");
                    loop = false;
                    isValidContinue3 = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select Y for Continue Order or N for Confirm Order." << "\n\n";
                    isValidContinue3 = false; // Continue loop if it is false
                }
            }
            isValidContinue3 = false; // Let it as false for user can loop again
        }
    } while (loop == true);
}

//Beverages Menu
void beveragesMenu() {
    system("cls");
    do {
        // show Beverage Menu
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                            Welcome to the Beverages Menu                             ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    1.  Coke " << " RM 5.50\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    2.  Fanta Strawberry " << " RM 5.50\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    3.  Fuze Lemon Tea " << " RM 5.50\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    4.  Minute Maid Plus Orange " << " RM 9.70\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    5.  Peach Tea " << " RM 4.90\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    6.  Sprite " << " RM 5.50\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << setw(60) << setfill('.') << left << "\t\t||    7.  Mineral Water " << " RM 3.00\t\t\t||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||    X. Back to Food Menu                                                              ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";

        string cc4[7] = { "Coke", "Fanta Strawberry", "Fuze Lemon Tea", "Minute Maid Plus Orange", "Peach Tea", "Sprite", "Mineral Water" };
        string choice4Str;
        const char* choice4 = choice4Str.c_str();
        bool continuing4 = true;
        int cho4;
        // Validation of choice4
        // Loop until the input is successfully read

        while (!isValidChoice4) {
            cout << "Please enter your choice : ";
            getline(cin, choice4Str);

            if (choice4Str == "X" || choice4Str == "x") {
                system("cls");
                loop = false;
                continuing4 = false;
                isValidChoice4 = true; // Break out of the loop if it is true 
            }
            else {
                if (isSingleDigit(choice4Str)) {
                    cho4 = choice4[0] - '0'; // Convert char to int
                    if (cho4 >= 1 && cho4 <= 7) {
                        cout << "You have chosen " << cc4[cho4 - 1] << "." << "\n\n";
                        addToOrder(cc4[cho4 - 1], "Beverages");
                        isValidChoice4 = true; // Break out of the loop if it is true 
                    }
                    else {
                        cout << "Invalid choice. Please select 1 - 7 only or X for Back to Food Menu." << "\n\n";
                        isValidChoice4 = false; // Continue loop if it is false
                    }
                }
                else {
                    cout << "Invalid choice. Please select 1 - 7 only or X for Back to Food Menu." << "\n\n";
                    isValidChoice4 = false; // Continue loop if it is false
                }
            }
        }
        isValidChoice4 = false; // Let it as false for user can loop again
        if (continuing4 == true) {
            string continue4;
            cout << "Do you want to continue order?" << "\n";
            // Validation of continue1
            // Loop until the input is successfully read
            while (!isValidContinue4) {
                cout << "Please enter your choice (Y for Continue, N for Confirm): ";
                getline(cin, continue4);
                // Make sure there are no other characters in the input buffer
                if (continue4 == "Y" || continue4 == "y") {
                    system("cls");
                    loop = true;
                    isValidContinue4 = true; // Break out of the loop if it is true 
                }
                else if (continue4 == "N" || continue4 == "n") {
                    system("cls");
                    loop = false;
                    isValidContinue4 = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select Y for Continue Order or N for Confirm Order." << "\n\n";
                    isValidContinue4 = false; // Continue loop if it is false
                }
            }
            isValidContinue4 = false; // Let it as false for user can loop again
        }
    } while (loop == true);
}

// Function to add or remove quantity for an ordered item
void modifyOrderedItemQuantity() {

    if (orderedItems.empty()) {
        system("cls");
        cout << "No items currently ordered. Cant Modify!" << "\n\n";
        isValidItemNumber = true;
        isValidQuantity = true;
        isValidQuantity2 = true;
    }

    int itemNumber;
    while (!isValidItemNumber) {
        cout << "Enter the item number you want to modify (1 - " << orderedItems.size() << " or X for cancel): ";
        string itemNumberStr;
        getline(cin, itemNumberStr);

        // Check if the user wants to cancel quantity modification
        if (itemNumberStr == "x" || itemNumberStr == "X") {
            system("cls");
            cout << "\nQuantity modification cancelled." << "\n\n";
            // You may want to set isValidItemNumber to true here to exit the loop
            isValidItemNumber = true;
            isValidQuantity = true;
            isValidQuantity2 = true;
        }
        else {
            try {
                itemNumber = stoi(itemNumberStr);

                if (itemNumber >= 1 && itemNumber <= orderedItems.size()) {
                    isValidItemNumber = true; // Break out of the loop if it is true
                }
                else {
                    cout << "Invalid item number. Please enter a valid item number or X to cancel. " << "\n\n";
                    isValidItemNumber = false;
                }
            }
            catch (const std::invalid_argument& e) {
                // Handle the case where stoi throws an exception (e.g., if the input is not a valid integer)
                cout << "Invalid input. Please enter a valid item number or X to cancel. " << "\n\n";
                isValidItemNumber = false;
            }
        }
    }

    isValidItemNumber = false; // Let it as false for user can loop again

    int quantityChange;
    while (!isValidQuantity) {
        cout << "Enter the quantity change (+X to add, -X to remove): ";
        string quantityChangeStr;
        getline(cin, quantityChangeStr);
        try {
            quantityChange = stoi(quantityChangeStr);
            if (quantityChange >= -orderedItems[itemNumber - 1].quantity) {
                isValidQuantity2 = false;
                isValidQuantity = true; // Break out of the loop if it is true 
            }
            else {
                cout << "Invalid quantity change. Please enter a valid quantity change." << "\n\n";
                isValidQuantity = false; // Continue loop if it is false
            }
        }
        catch (const exception&) {
            cout << "Invalid input. Please enter a valid quantity change." << "\n";
            isValidQuantity = false; // Continue loop if it is false
        }
    }
    isValidQuantity = false; // Let it as false for user can loop again

    while (!isValidQuantity2) {
        // Update the item quantity 
        int newQuantity = orderedItems[itemNumber - 1].quantity + quantityChange;
        orderedItems[itemNumber - 1].quantity = newQuantity;

        // If quantity becomes zero or less, remove the item from the list
        if (newQuantity <= 0) {
            orderedItems.erase(orderedItems.begin() + itemNumber - 1);
            system("cls");
            cout << "\nItem removed from the order." << "\n\n";
            isValidQuantity2 = true;
        }
        else {
            system("cls");
            cout << "\nQuantity updated." << "\n\n";
            isValidQuantity2 = true;
        }
    }
    isValidQuantity2 = false; // Let it as false for user can loop again
}

// Function to display currently ordered items
void displayOrderedItems() {

    // Sort the orderedItems by name (A-Z)
    sort(orderedItems.begin(), orderedItems.end(), compareOrderedItemsByName);

    while (!isValidChoice5) {
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                                Currently Ordered Items                               ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n";
        if (orderedItems.empty()) {
            cout << "\t\t||                                                                                      ||" << "\n";
            cout << "\t\t||    No items currently ordered.                                                       ||" << "\n";
            cout << "\t\t||                                                                                      ||" << "\n";
        }
        else {
            cout << "\t\t      Currently Ordered Items:                                                          " << "\n\n";
            int itemNumber = 1;
            for (const auto& item : orderedItems) {
                cout << "\t\t      " << itemNumber << ". " << item.name;
                if (item.category == "Pizza") {
                    cout << " (" << item.size << ")"; // Display size of pizza
                }
                if (item.category == "Pizza" || item.category == "Pasta") {
                    cout << " - " << item.setOrAlaCarte; // Display set or ala carte information for pizza and pasta items
                }
                cout << " - " << item.quantity << " item" << (item.quantity > 1 ? "s" : "") << "\n\n"; // Plural form if needed
                itemNumber++;
            }
        }
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||    Q. Add or Remove Quantity                                                         ||" << "\n";
        cout << "\t\t||                                                                                      ||" << "\n";
        cout << "\t\t||    X. Back to Food Menu                                                              ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";

        string choice5;
        // Validation of continue5
        // Loop until the input is successfully read
        cout << "Please enter your choice (Q for Change Quantity / X for back to Food Menu): ";
        getline(cin, choice5);
        // Make sure there are no other characters in the input buffer
        if (choice5 == "Q" || choice5 == "q") {
            modifyOrderedItemQuantity(); // Call the menu() function for food menu
            isValidChoice5 = false;
        }
        else if (choice5 == "X" || choice5 == "x") {
            system("cls");
            isValidChoice5 = true; // Break out of the loop if it is true 
        }
        else {
            system("cls");
            cout << "Invalid choice. Please select Q for change quantity or X for back to Food Menu." << "\n\n";
            isValidChoice5 = false; // Continue loop if it is false
        }
    }
    isValidChoice5 = false; // Let it as false for user can loop again
}

//Payment 
void payment() {
    // Calculate the total price of the order
    double totalPrice = 0.0, totalPriceWithCharges = 0.0, roundedtotalPrice = 0.0;
    bool paymentV = false;
    bool isValidOrder = true;

    // Sort the orderedItems by name (A-Z)
    sort(orderedItems.begin(), orderedItems.end(), compareOrderedItemsByName);

    for (const auto& item : orderedItems) {
        double itemPrice = getItemPrice(item.name, item.category, item.size, item.setOrAlaCarte);
        totalPrice += itemPrice * item.quantity;
    }

    // Display the invoice
    system("cls");
    if (isTakeaway) {
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                          Invoice for Your Order (Take Away)                          ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";
    }
    else {
        cout << "\t\t==========================================================================================" << "\n";
        cout << "\t\t||                           Invoice for Your Order (Dine In)                           ||" << "\n";
        cout << "\t\t==========================================================================================" << "\n\n";
    }

    if (orderedItems.empty()) {
        isValidOrder = false;
        system("cls");
        cout << "\nNo items ordered. Returning to Food Menu......" << "\n\n";
        menu();
    }
    else {
        int itemNumber = 1;
        for (const auto& item : orderedItems) {
            double itemPrice = getItemPrice(item.name, item.category, item.size, item.setOrAlaCarte);
            cout << "\t\t" << itemNumber << ". " << item.name;
            if (item.category == "Pizza") {
                cout << " (" << item.size << ")";
                cout << " - " << item.setOrAlaCarte;
            }
            else if (item.category == "Pasta") {
                cout << " - " << item.setOrAlaCarte;
            }
            cout << " - " << item.quantity << " item" << (item.quantity > 1 ? "s" : ""); // Plural form if needed
            cout << " - RM " << itemPrice << " each";
            cout << " - Total: RM " << fixed << setprecision(2) << itemPrice * item.quantity << "\n\n";
            itemNumber++;
        }

        // Calculate packaging box charges only for takeaway
        if (isTakeaway) {
            // Count the number of items for each type of packaging box
            int largePackagingBoxCount = 0;
            int smallPackagingBoxCount = 0;
            for (const auto& item : orderedItems) {
                if (item.setOrAlaCarte == "Set") { // Only Set using large packaging box
                    largePackagingBoxCount += item.quantity;
                }
                else if (item.category != "Beverages" || item.category == "Sides" || item.setOrAlaCarte == "Ala Carte") { // Only Ala Carte using small packaging box
                    smallPackagingBoxCount += item.quantity;
                }
            }
            // Calculate the charges for each type of packaging box
            double largePackagingBoxCharge = largePackagingBoxCount * 2.0; // RM 2.00 per large packaging box
            double smallPackagingBoxCharge = smallPackagingBoxCount * 2.0; // RM 2.00 per small packaging box
            double totalPackagingBoxCharge = 0.0;

            // Display packaging box information and charges
            if (largePackagingBoxCount > 0) {
                cout << "\t\tLarge Packaging Box - " << largePackagingBoxCount << " item" << (largePackagingBoxCount > 1 ? "s" : "") << " - RM 2.00 each - Total: RM " << fixed << setprecision(2) << largePackagingBoxCharge << "\n\n";
            }
            if (smallPackagingBoxCount > 0) {
                cout << "\t\tSmall Packaging Box - " << smallPackagingBoxCount << " item" << (smallPackagingBoxCount > 1 ? "s" : "") << " - RM 2.00 each - Total: RM " << fixed << setprecision(2) << smallPackagingBoxCharge << "\n\n";
            }

            cout << "\t\t==========================================================================================" << "\n";
            for (const auto& item : orderedItems) {
                double itemPrice = getItemPrice(item.name, item.category, item.size, item.setOrAlaCarte);
                totalPackagingBoxCharge = largePackagingBoxCharge + smallPackagingBoxCharge;
            }
            totalPriceWithCharges += totalPrice + totalPackagingBoxCharge;
            roundedtotalPrice += round(totalPriceWithCharges * 10) / 10;
            cout << "\t\tTotal Price : RM" << totalPrice << "\n\n";
            cout << "\t\tTotal Packaging Box Price : RM" << totalPackagingBoxCharge << "\n\n";
            cout << "\t\tTotal Payment Amount (including packaging box charges): RM " << fixed << setprecision(2) << roundedtotalPrice << "\n";
            cout << "\t\t==========================================================================================" << "\n";
        }
        else {
            cout << "\t\t==========================================================================================" << "\n";
            double serviceCharge = 0.0;
            for (const auto& item : orderedItems) {
                double itemPrice = getItemPrice(item.name, item.category, item.size, item.setOrAlaCarte);
                serviceCharge = totalPrice * 0.10;
            }
            totalPriceWithCharges += totalPrice + serviceCharge;
            roundedtotalPrice += round(totalPriceWithCharges * 10) / 10;
            cout << "\t\tTotal Price : RM" << totalPrice << "\n\n";
            cout << "\t\tService Charge (10%) : RM" << serviceCharge << "\n\n";
            cout << "\t\tTotal Payment Amount (including Service charges): RM " << fixed << setprecision(2) << roundedtotalPrice << "\n";
            cout << "\t\t==========================================================================================" << "\n";
        }
    }
    // Ask for confirmation
    while (isValidOrder == true) {
        cout << "\nDo you confirm the order? (Y/N): ";
        string confirmation;
        getline(cin, confirmation);
        system("cls");

        if (confirmation == "Y" || confirmation == "y") {
            cout << "\nThank you for your order! Now proceed to the payment." << "\n\n";
            cout << "*****************************************************************\n\n" << endl;
            /*cout << "==========================================================================================" << "\n\n";*/
            paymentV = paymentSection(roundedtotalPrice);
            if (paymentV == true)
            {
                isValidOrder = false;

                // Sort the orderedItems by name (A-Z)
                sort(orderedItems.begin(), orderedItems.end(), compareOrderedItemsByName);

                cout << "\t\t==========================================================================================" << "\n";
                cout << "\t\t||                                    Payment Receipt                                   ||" << "\n";
                cout << "\t\t==========================================================================================" << "\n\n";
                if (orderedItems.empty()) {
                    cout << "\t\t\t\tNo items ordered." << "\n\n";
                    cout << "==========================================================================================" << "\n\n";
                    menu();
                    system("cls");
                }
                else {
                    int itemNumber = 1;
                    for (const auto& item : orderedItems) {
                        double itemPrice = getItemPrice(item.name, item.category, item.size, item.setOrAlaCarte);
                        cout << "\t\t" << itemNumber << ". " << item.name;
                        if (item.category == "Pizza") {
                            cout << " (" << item.size << ")";
                            cout << " - " << item.setOrAlaCarte;
                        }
                        else if (item.category == "Pasta") {
                            cout << " - " << item.setOrAlaCarte;
                        }
                        cout << " - " << item.quantity << " item" << (item.quantity > 1 ? "s" : ""); // Plural form if needed
                        cout << " - RM " << itemPrice << " each";
                        cout << " - Total: RM " << fixed << setprecision(2) << itemPrice * item.quantity << "\n\n";
                        itemNumber++;
                    }

                    // Calculate packaging box charges only for takeaway
                    if (isTakeaway) {
                        // Count the number of items for each type of packaging box
                        int largePackagingBoxCount = 0;
                        int smallPackagingBoxCount = 0;
                        for (const auto& item : orderedItems) {
                            if (item.setOrAlaCarte == "Set") { // Only Set using large packaging box
                                largePackagingBoxCount += item.quantity;
                            }
                            else if (item.category != "Beverages" || item.category == "Sides" || item.setOrAlaCarte == "Ala Carte") { // Only Ala Carte using small packaging box
                                smallPackagingBoxCount += item.quantity;
                            }
                        }
                        // Calculate the charges for each type of packaging box
                        double largePackagingBoxCharge = largePackagingBoxCount * 2.0; // RM 2.00 per large packaging box
                        double smallPackagingBoxCharge = smallPackagingBoxCount * 2.0; // RM 2.00 per small packaging box
                        double totalPackagingBoxCharge = 0.0;

                        // Display packaging box information and charges
                        if (largePackagingBoxCount > 0) {
                            cout << "\t\tLarge Packaging Box - " << largePackagingBoxCount << " item" << (largePackagingBoxCount > 1 ? "s" : "") << " - RM 2.00 each - Total: RM " << fixed << setprecision(2) << largePackagingBoxCharge << "\n\n";
                        }
                        if (smallPackagingBoxCount > 0) {
                            cout << "\t\tSmall Packaging Box - " << smallPackagingBoxCount << " item" << (smallPackagingBoxCount > 1 ? "s" : "") << " - RM 2.00 each - Total: RM " << fixed << setprecision(2) << smallPackagingBoxCharge << "\n\n";
                        }

                        cout << "\t\t==========================================================================================" << "\n";
                        for (const auto& item : orderedItems) {
                            double itemPrice = getItemPrice(item.name, item.category, item.size, item.setOrAlaCarte);
                            totalPackagingBoxCharge = largePackagingBoxCharge + smallPackagingBoxCharge;
                        }

                        cout << "\t\tTotal Price : RM" << totalPrice << "\n\n";
                        cout << "\t\tTotal Packaging Box Price : RM" << totalPackagingBoxCharge << "\n\n";
                        cout << "\t\tTotal Payment Amount (including packaging box charges): RM " << fixed << setprecision(2) << roundedtotalPrice << "\n";
                        cout << "\t\t==========================================================================================" << "\n";
                        cout << "\t\tMembership Points earned: " << mPoint << " points" << endl;
                        cout << "\t\tYour updated wallet balance is: RM" << newData.purseValue << endl;
                        cout << "\t\tYour updated membership point balance is: " << newData.memberpoint << " points" << endl;
                        cout << "\t\t==========================================================================================" << "\n\n";
                    }
                    else {
                        cout << "\t\t==========================================================================================" << "\n";
                        double serviceCharge = 0.0;
                        for (const auto& item : orderedItems) {
                            double itemPrice = getItemPrice(item.name, item.category, item.size, item.setOrAlaCarte);
                            serviceCharge = totalPrice * 0.10;
                        }

                        cout << "\t\tTotal Price : RM" << totalPrice << "\n\n";
                        cout << "\t\tService Charge (10%) : RM" << serviceCharge << "\n\n";
                        cout << "\t\tTotal Payment Amount (including Service charges): RM " << fixed << setprecision(2) << roundedtotalPrice << "\n";
                        cout << "\t\t==========================================================================================" << "\n";
                        cout << "\t\tMembership Points earned: " << mPoint << " points" << endl;
                        cout << "\t\tYour updated wallet balance is: RM" << newData.purseValue << endl;
                        cout << "\t\tYour updated membership point balance is: " << newData.memberpoint << " points" << endl;
                        cout << "\t\t==========================================================================================" << "\n\n";
                    }
                }
                orderedItems.clear();
            }
            else {
                cout << "Order Cancelled." << endl;
                orderedItems.clear();
                isValidOrder = false;
            }
        }
        else if (confirmation == "N" || confirmation == "n") {
            isValidOrder = false;
            cout << "\nOrder not confirmed. Returning to the food menu." << "\n";
            string clear;
            cout << "\nDo you want to clear items?" << "\n";
            // Validation of clear
            // Loop until the input is successfully read
            while (!isValidClear) {
                cout << "Please enter your choice (Y for Clear, N for No Clear): ";
                getline(cin, clear);
                // Make sure there are no other characters in the input buffer
                if (clear == "Y" || clear == "y") {
                    // Clear the ordered items for a new order
                    orderedItems.clear();
                    system("cls");
                    cout << "\nThe Order Items is Cleared." << "\n\n";
                    menu();
                    isValidClear = true; // Break out of the loop if it is true 
                }
                else if (clear == "N" || clear == "n") {
                    system("cls");
                    cout << "\nThe Order Items is Remained." << "\n\n";
                    menu();
                    isValidClear = true; // Break out of the loop if it is true 
                }
                else {
                    cout << "Invalid choice. Please select Y for Clear Order or N for No Clear Order." << "\n\n";
                    isValidClear = false; // Continue loop if it is false
                }
            }
            isValidClear = false;  // Let it as false for user can loop again
        }
        else {
            isValidOrder = false;
            system("cls");
            cout << "\nInvalid choice. Returning to the food menu." << "\n\n";
            menu();
        }
    }
    isValidOrder = true;
}

//----------------------------------------------------------------------------------------------------------


//-----------------------Payment Module-----------------------------------

bool paymentSection(double total) {

    string paymentInput;
    bool pointValid, invInput = false, contPayment = false, paymentValid = false;

    system("cls");
    do {
        cout << "\t\t\t  *************************************************************" << endl;
        cout << "\n\t\t\t    Pizza Hub Customer Purse Value & Membership Points Details" << endl << endl;
        cout << "\t\t\t\t       Member ID             : " << newData.memberID << endl;
        cout << "\t\t\t\t       Current Purse Value   : " << "RM " << fixed << showpoint << setprecision(2) << newData.purseValue << endl;
        cout << "\t\t\t\t       Current Member Points : " << newData.memberpoint << " points" << "\n\n";
        cout << "\t\t\t  *************************************************************\n" << endl;
        cout << "\t\t\t\t================================================" << endl;
        cout << "\t\t\t\t|        Welcome to the Payment Menu           |" << endl;
        cout << "\t\t\t\t================================================" << "\n";
        cout << "\t\t\t\t|                                              |" << endl;
        cout << "\t\t\t\t|  1. Pay with Wallet Balance                  |" << endl;
        cout << "\t\t\t\t|  2. Pay with Memberhip Point                 |" << endl;
        cout << "\t\t\t\t|  3. Top Up Wallet                            |" << endl;
        cout << "\t\t\t\t|  4. Cancel Order                             |" << endl;
        cout << "\t\t\t\t|                                              |" << endl;
        cout << "\t\t\t\t================================================" << "\n\n";

        do {
            cout << "Choose payment method (Select from 1 - 4): ";
            getline(cin, paymentInput);

            if (paymentInput == "1")
            {
                pointValid = walletBalance(total);
                if (pointValid == false)
                {
                    contPayment = true;
                    invInput = false;
                    cout << "\n";
                }
                else
                {
                    contPayment = false;
                    invInput = false;
                    paymentValid = true;
                }
            }
            else if (paymentInput == "2")
            {
                pointValid = memberPointPayment(total);
                if (pointValid == false)
                {
                    contPayment = true;
                    invInput = false;
                    cout << "\n";
                }
                else
                {
                    contPayment = false;
                    invInput = false;
                    paymentValid = true;
                }
            }
            else if (paymentInput == "3")
            {
                memberTopUp();
                system("cls");
                cout << "Proceeding to Payment Menu....." << endl;
                cout << "\n";
                contPayment = true;
                invInput = false;
            }
            else if (paymentInput == "4")
            {
                system("cls");
                cout << "Returning to Main Menu....." << endl;
                cout << "\n";
                contPayment = false;
                invInput = false;
                paymentValid = false;
            }
            else
            {
                cout << "Invalid input. Please enter again." << endl;
                cout << "\n";
                invInput = true;
            }

        } while (invInput == true);

    } while (contPayment == true);

    return paymentValid;
}

bool walletBalance(double total) {

    //int mPoint;

    if (newData.purseValue >= total)
    {
        newData.purseValue -= total;
        mPoint = int(total);
        newData.memberpoint += mPoint;
        system("cls");
        cout << "Payment Successful!" << endl;
        cout << "\n";
        return true;
    }
    else {
        system("cls");
        cout << "Insufficient balance. Please select another payment method or proceed to top up." << endl;
        return false;
    }
}

bool memberPointPayment(double total) {

    if (newData.memberpoint >= (total * 100))
    {
        newData.memberpoint -= (total * 100);
        system("cls");
        cout << "Payment is successful!" << endl;
        cout << "\n";
        return true;
    }
    else
    {
        system("cls");
        cout << "Insufficient member points. Please select another payment method." << endl;
        return false;
    }
}

//-------------------------------------------------------------------------


//Main Function
int main()
{
    string trash;
    bool repeatOption, mainmenu2input = false, rptmainmenu2 = false, mainmenu2input2 = false, repeatlogin = false, rptmainmenuinput = false, rptmainmenu = false;

    do {
        system("cls");
        cout << "\t\t\t      ===============================================================" << "\n";
        welcomelogo();
        cout << "\n\t\t\t      ===============================================================" << "\n";
        cout << "\n\n";
        startupInterface();
        do {

            cout << "\nPlease enter your option (Select from 1 to 3 only): ";
            getline(cin, mainchoice);

            if (mainchoice == "1")
            {
                memberID = cardIDGenerator();
                memberRegistration(memberID);
                cout << endl;
                cout << "Please enter to proceed......";
                getline(cin, trash);
                cout << "\n";
                rptmainmenuinput = false;
                rptmainmenu = true;
            }
            else if (mainchoice == "2")
            {
                do {
                    repeatOption = memberLogin();

                    if (!repeatOption)
                    {
                        repeatlogin = false;
                        do {
                            mainMenu();
                            do {
                                cout << "\nPlease enter your option (Select from 1 to 5 only): ";
                                getline(cin, subchoice);

                                if (subchoice == "1")
                                {
                                    option1();
                                    cout << "\n";
                                    cout << "Please enter to return to main menu......";
                                    getline(cin, trash);
                                    if (!compareStructData())
                                    {
                                        modifyFileInfo();
                                    }
                                    mainmenu2input = false;
                                    rptmainmenu2 = true;
                                }
                                else if (subchoice == "2")
                                {
                                    memberTopUp();
                                    cout << "Please enter to return to main menu......";
                                    getline(cin, trash);
                                    if (!compareStructData())
                                    {
                                        modifyFileInfo();
                                    }
                                    mainmenu2input = false;
                                    rptmainmenu2 = true;
                                }
                                else if (subchoice == "3")
                                {
                                    memberDetails();
                                    cout << "\nPlease enter to return to main menu......";
                                    getline(cin, trash);
                                    mainmenu2input = false;
                                    rptmainmenu2 = true;
                                }
                                else if (subchoice == "4")
                                {
                                    FoodPackagingModule();
                                    cout << "\n";
                                    cout << "Please enter to return to main menu......";
                                    getline(cin, trash);
                                    if (!compareStructData())
                                    {
                                        modifyFileInfo();
                                    }
                                    mainmenu2input = false;
                                    rptmainmenu2 = true;
                                }
                                else if (subchoice == "5")
                                {
                                    if (!compareStructData())
                                    {
                                        modifyFileInfo();
                                    }
                                    mainmenu2input = false;
                                    rptmainmenu2 = false;
                                }
                                else {
                                    cout << "Invalid input, please try again." << endl;
                                    mainmenu2input = true;
                                }

                            } while (mainmenu2input == true);

                        } while (rptmainmenu2 == true);
                    }
                    else
                    {
                        do {
                            cout << "\nDo you want to try again? (Y/N): ";
                            getline(cin, option);

                            if (option == "Y" || option == "y")
                            {
                                mainmenu2input2 = false;
                                repeatlogin = true;
                            }

                            else if (option == "N" || option == "n")
                            {
                                cout << "\n";
                                mainmenu2input2 = false;
                                repeatlogin = false;
                            }
                            else {
                                cout << "Invalid input, please try again." << endl;
                                mainmenu2input2 = true;
                            }

                        } while (mainmenu2input2 == true);

                    }

                } while (repeatlogin == true);

                rptmainmenuinput = false;
                rptmainmenu = true;
            }
            else if (mainchoice == "3")
            {
                system("cls");
                cout << endl;
                cout << "\t\t\t=======================================================================" << "\n";
                thankyoulogo();
                cout << "\n\t\t\t=======================================================================" << "\n";
                cout << "\n\n";
                cout << "\t\t\t\t  **************************************************" << endl;
                cout << "\n";
                cout << "\t\t\t\t  Thank you for using our program. Have a nice day!" << endl;
                cout << "\n";
                cout << "\t\t\t\t  **************************************************\n\n\n\n";
                rptmainmenuinput = false;
                rptmainmenu = false;
            }
            else {
                cout << "Invalid input, please try again." << endl;
                rptmainmenuinput = true;
            }

        } while (rptmainmenuinput == true);

    } while (rptmainmenu == true);

    return 0;

}
