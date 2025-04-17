#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include<vector>
#include<cctype>
#include<fstream>
#include<cstdlib>

using namespace std;


//Base
const string ClientFileName = "ATMinformation.txt";

struct Cleint
{
    string AccountName;
    string PinCode;
    string CleintName;
    string PhoneNumber;
    unsigned AccountBalance;
    bool MarkAccount = true;
};

Cleint  Registered;
string sRegistered;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Read From File
vector<string> SplitLine(string Line)
{
    vector<string> SaveWords;
    string Space = "#//#";
    short Postion;
    string Word;

    while ((Postion = Line.find(Space)) != std::string::npos)
    {
        Word = Line.substr(0, Postion);

        if (Word != "")
        {
            SaveWords.push_back(Word);
        }
        Line.erase(0, Postion + Space.length());
    }

    if (Line != "")
    {
        SaveWords.push_back(Line);
    }

    return SaveWords;
}

Cleint CovertLineIntoRecord(string Line)
{
    vector<string> TakeFromSplit = SplitLine(Line);

    Cleint CleintConvert;

    CleintConvert.AccountName = TakeFromSplit[0];
    CleintConvert.PinCode = TakeFromSplit[1];
    CleintConvert.CleintName = TakeFromSplit[2];
    CleintConvert.PhoneNumber = TakeFromSplit[3];
    CleintConvert.AccountBalance = stod(TakeFromSplit[4]);

    return CleintConvert;
}

vector<Cleint> ReadFromFile()
{
    fstream MyFile;

    vector<Cleint> SaveCleintInVector;

    MyFile.open(ClientFileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        Cleint CleintLine;

        while (getline(MyFile, Line))
        {
            CleintLine = CovertLineIntoRecord(Line);
            SaveCleintInVector.push_back(CleintLine);
        }
    }
    MyFile.close();

    return SaveCleintInVector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Paste In File
string ConvertEditedAccountIntoString(Cleint CleintForEdit)
{
    string Convert = "";
    string Space = "#//#";

    Convert = Convert + CleintForEdit.AccountName;
    Convert = Convert + Space;
    Convert = Convert + CleintForEdit.PinCode;
    Convert = Convert + Space;
    Convert = Convert + CleintForEdit.CleintName;
    Convert = Convert + Space;
    Convert = Convert + CleintForEdit.PhoneNumber;
    Convert = Convert + Space;
    Convert = Convert + to_string(CleintForEdit.AccountBalance);

    return Convert;
}

vector<Cleint> PasteInFileFalseOnly5(vector<Cleint> SaveCleintInVector)
{
    fstream MyFile;

    MyFile.open(ClientFileName, ios::out);

    string Line;

    if (MyFile.is_open())
    {
        for (Cleint N50 : SaveCleintInVector)
        {
            if (N50.MarkAccount == true)
            {
                Line = ConvertEditedAccountIntoString(N50);
                MyFile << Line << endl;
            }
        }
    }
    MyFile.close();

    return SaveCleintInVector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Total Balance
int TotalBalance(vector<Cleint> SaveCleintInVector)
{
    int Total;
    for (Cleint T10 : SaveCleintInVector)
    {
        if (T10.AccountName == sRegistered)
        {
            Total = T10.AccountBalance;
            return Total;
        }
    }

}

void TotalAccountBalance()
{
    vector<Cleint> SaveCleintInVector = ReadFromFile();
    int Total = TotalBalance(SaveCleintInVector);
    cout << "Total Account Balance = " << Total << endl;
    cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//QuickWithDraw
short NumberToQuickWithdraw()
{
    cout << "===========================================" << endl;
    cout << "===========================================" << endl;
    cout << "\t\tQuick WithDraw Menu" << endl;
    cout << "===========================================" << endl;
    cout << "===========================================" << endl;
    cout << "[1]200 \t";
    cout << "\t[2]500 " << endl;
    cout << "[3]1000 \t";
    cout << "[4]2000 " << endl;
    cout << "[5]3000 \t";
    cout << "[6]4000 " << endl;
    cout << "===========================================" << endl;
    cout << "===========================================" << endl;

    cout << endl;
    TotalAccountBalance();
    cout << endl;
    short AmountWillWithdraw;
    cout << "Enter Number Between to [1] To [6] ? ";
    cin >> AmountWillWithdraw;

    return AmountWillWithdraw;
}

void QuickWithdrawAmount(vector<Cleint>& SaveCleintInVector, short WithDrawChoice)
{
    for (Cleint& C4 : SaveCleintInVector)
    {
        if (sRegistered == C4.AccountName)
        {
            if ((WithDrawChoice == 1) && (!C4.AccountBalance < 200))
            {
                C4.AccountBalance -= 200;
            }
            else if ((WithDrawChoice == 2) && (!C4.AccountBalance < 500))
            {
                C4.AccountBalance -= 500;
            }
            else if ((WithDrawChoice == 3) && (!C4.AccountBalance < 1000))
            {
                C4.AccountBalance -= 1000;
            }
            else if ((WithDrawChoice == 4) && (!C4.AccountBalance < 2000))
            {
                C4.AccountBalance -= 2000;
            }
            else if ((WithDrawChoice == 5) && (!C4.AccountBalance < 3000))
            {
                C4.AccountBalance -= 3000;
            }
            else if ((WithDrawChoice == 6) && (!C4.AccountBalance < 4000))
            {
                C4.AccountBalance -= 4000;
            }

        }
    }
}

Cleint PushInVectorQuickWithdraw(Cleint& Information, vector<Cleint>& SaveCleintInVector)
{
    for (Cleint& C5 : SaveCleintInVector)
    {
        if (C5.AccountName == sRegistered)
        {
            Information = C5;
            C5.MarkAccount = false;
        }
    }
    return Information;
}

void QuickWithDraw()
{
    vector<Cleint> SaveCleintInVector = ReadFromFile();
    short WithDrawChoice = NumberToQuickWithdraw();
    Cleint Information;

    if (WithDrawChoice == 1 || WithDrawChoice == 2 || WithDrawChoice == 3 || WithDrawChoice == 4 || WithDrawChoice == 5 || WithDrawChoice == 6)
    {
        QuickWithdrawAmount(SaveCleintInVector, WithDrawChoice);
        Information = PushInVectorQuickWithdraw(Information, SaveCleintInVector);
        SaveCleintInVector.push_back(Information);
        PasteInFileFalseOnly5(SaveCleintInVector);
        cout << endl;
        cout << " Quick Withdrawal Done successful." << endl;
        cout << endl;
    }
    else
    {
        system("cls");
        cout << "Sorry,Wrong Number " << endl;
        cout << endl;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//NormalWithDraw
int AmountToWithdraw(vector<Cleint>& SaveCleintInVector, Cleint& Information)
{
    cout << endl;
    int AmountWillWithdraw;
    cout << "Enter Amount to Withdraw ? ";
    cin >> AmountWillWithdraw;

    return AmountWillWithdraw;
}

void WithdrawAmount(vector<Cleint>& SaveCleintInVector, int AmountWillWithdraw)
{
    for (Cleint& C4 : SaveCleintInVector)
    {
        if (sRegistered == C4.AccountName)
        {
            C4.AccountBalance -= AmountWillWithdraw;
        }
    }
}

Cleint PushInVectorWithdraw(Cleint& Information, vector<Cleint>& SaveCleintInVector)
{
    for (Cleint& C5 : SaveCleintInVector)
    {
        if (C5.AccountName == sRegistered)
        {
            Information = C5;
            C5.MarkAccount = false;
        }
    }
    return Information;
}

void Withdraw()
{
    vector<Cleint> SaveCleintInVector = ReadFromFile();
    Cleint Information;
    int AmountWillWithdraw = AmountToWithdraw(SaveCleintInVector, Information);

    if (AmountWillWithdraw < TotalBalance(SaveCleintInVector))
    {
        WithdrawAmount(SaveCleintInVector, AmountWillWithdraw);
        Information = PushInVectorWithdraw(Information, SaveCleintInVector);
        SaveCleintInVector.push_back(Information);
        PasteInFileFalseOnly5(SaveCleintInVector);
        cout << endl;
        cout << "Withdrawal Done successful." << endl;
        cout << endl;

    }
    else
    {
        system("cls");
        cout << "You Don't Have Enought Money to WithDraw " << endl;
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Deposit

int AmountToDeposit()
{
    int AmountDeposited;
    cout << "Enter Amount to Deposit ? ";
    cin >> AmountDeposited;

    return AmountDeposited;
}

void DepositAmount(vector<Cleint>& SaveCleintInVector, int AmountWillDeposit)
{
    for (Cleint& C4 : SaveCleintInVector)
    {
        if (sRegistered == C4.AccountName)
        {
            C4.AccountBalance = C4.AccountBalance + AmountWillDeposit;
        }
    }
}

Cleint PushInVectorDeposit(Cleint& Information, vector<Cleint>& SaveCleintInVector)
{
    for (Cleint& C5 : SaveCleintInVector)
    {
        if (C5.AccountName == sRegistered)
        {
            Information = C5;
            C5.MarkAccount = false;
        }
    }
    return Information;
}

void Deposit()
{
    vector<Cleint> SaveCleintInVector = ReadFromFile();
    Cleint Information;
    int AmountWillDeposit = AmountToDeposit();

    if (AmountWillDeposit > 0)
    {
        DepositAmount(SaveCleintInVector, AmountWillDeposit);
        Information = PushInVectorDeposit(Information, SaveCleintInVector);
        SaveCleintInVector.push_back(Information);
        PasteInFileFalseOnly5(SaveCleintInVector);
        cout << endl;
        cout << "Depsoit Done successful." << endl;
        cout << endl;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Login
string ReadAccountNameToLogin()
{
    cout << "_______________________________________________________" << endl;
    cout << "_______________________________________________________" << endl;
    cout << "\t\t\tLogin" << endl;
    cout << "_______________________________________________________" << endl;
    cout << "_______________________________________________________" << endl;
    string AccountName;
    cout << "Enter Account Name ? ";
    cin >> AccountName;

    return AccountName;
}

string ReadPinCodeToLogin()
{
    string AccountName;
    cout << "Enter PinCode ? ";
    cin >> AccountName;

    return AccountName;
}

bool CheckAccountThatLogedIn(vector <Cleint> SaveCleintInVector, string AccountNameToLogin, string PinCodeToLoginIn)
{
    for (Cleint P20 : SaveCleintInVector)
    {
        if (P20.AccountName == AccountNameToLogin && P20.PinCode == PinCodeToLoginIn)
        {
            return true;
        }
    }
    return false;

}

void PrintATMMenu()
{
    system("cls");
    cout << "_______________________________________________________" << endl;
    cout << "_______________________________________________________" << endl;
    cout << "\t\t\tMain Menu" << endl;
    cout << "_______________________________________________________" << endl;
    cout << "_______________________________________________________" << endl;
    cout << "[1]Qiuck WithDraw" << endl;
    cout << "[2]Normal WithDraw" << endl;
    cout << "[3]Deposit" << endl;
    cout << "[4]Check Balance" << endl;
    cout << "[5]Exit" << endl;
    cout << "_______________________________________________________" << endl;
    cout << "_______________________________________________________" << endl;
    cout << endl;
    cout << "Enter Number Between [1] To [5] ? ";
    short Number;
    cin >> Number;
    system("cls");

    switch (Number)
    {

    case 1:
        QuickWithDraw();
        system("pause");
        system("cls");
        PrintATMMenu();
        break;

    case 2:
        Withdraw();
        system("pause");
        system("cls");
        PrintATMMenu();
        break;

    case 3:
        Deposit();
        system("pause");
        system("cls");
        PrintATMMenu();
        break;

    case 4:
        TotalAccountBalance();
        system("pause");
        system("cls");
        PrintATMMenu();
        break;

    case 5:
        system("cls");
        cout << "==================================" << endl;
        cout << "\tPull Your Card :-)" << endl;
        cout << "==================================" << endl;
        break;
    }
}

void Login()
{
    vector <Cleint> SaveCleintInVector = ReadFromFile();
    string AccountNameToLogin = ReadAccountNameToLogin();
    string PinCodeToLoginIn = ReadPinCodeToLogin();
    sRegistered = AccountNameToLogin;
    bool CheckLog = CheckAccountThatLogedIn(SaveCleintInVector, AccountNameToLogin, PinCodeToLoginIn);
    if (CheckLog)
    {
        PrintATMMenu();
    }
    else
    {
        system("cls");
        Login();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    Login();
}