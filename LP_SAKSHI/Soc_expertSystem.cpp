#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool askQuestion(const string &question)
{
    char response;
    cout << question << " (y/n): ";
    cin >> response;
    response = tolower(response);
    while (response != 'y' && response != 'n')
    {
        cout << "Invalid input. Enter 'y' or 'n': ";
        cin >> response;
        response = tolower(response);
    }
    return response == 'y';
}

void diagnoseWaterIssue()
{
    cout << "\n--- Detailed Water Supply Diagnosis ---\n";
    int score = 0;

    if (askQuestion("1. Was there a prior notice about water shutdown?"))
        score += 2;
    if (askQuestion("2. Did other buildings in the area face the same issue?"))
        score += 1;
    if (askQuestion("3. Was there a visible pipe leakage in the society?"))
        score += 3;
    if (askQuestion("4. Did the water pressure drop before the shutdown?"))
        score += 2;
    if (askQuestion("5. Was the overhead tank empty that day?"))
        score += 2;
    if (askQuestion("6. Did maintenance staff report a pump failure?"))
        score += 3;
    if (askQuestion("7. Has the municipal supply been irregular lately?"))
        score += 1;
    if (askQuestion("8. Was there construction work near the water lines?"))
        score += 2;
    if (askQuestion("9. Did the issue persist beyond 24 hours?"))
        score += 1;
    if (askQuestion("10. Were any complaints logged before the shutdown?"))
        score += 1;

    cout << "\n>> Most Probable Cause: ";
    if (score >= 8)
    {
        cout << "Major pipe burst or pump failure (Immediate repair needed).\n";
    }
    else if (score >= 5)
    {
        cout << "Scheduled maintenance or municipal supply issue.\n";
    }
    else if (score >= 3)
    {
        cout << "Temporary disruption due to construction or low pressure.\n";
    }
    else
    {
        cout << "Unknown cause (Contact maintenance for inspection).\n";
    }
}

void diagnosePowerIssue()
{
    cout << "\n--- Detailed Common Passage Light Diagnosis ---\n";
    int score = 0;

    if (askQuestion("1. Was there a complete blackout in the society?"))
        score += 3;
    if (askQuestion("2. Did the lights flicker before going off?"))
        score += 2;
    if (askQuestion("3. Are other common area lights working?"))
        score += 1;
    if (askQuestion("4. Was there a recent electrical inspection?"))
        score += 1;
    if (askQuestion("5. Did anyone report sparks or burning smells?"))
        score += 3;
    if (askQuestion("6. Is the circuit breaker tripped?"))
        score += 2;
    if (askQuestion("7. Were the lights working fine before sudden failure?"))
        score += 1;
    if (askQuestion("8. Has there been frequent power fluctuations?"))
        score += 2;
    if (askQuestion("9. Did maintenance recently change wiring?"))
        score += 1;
    if (askQuestion("10. Are backup lights (if any) also not working?"))
        score += 2;

    cout << "\n>> Most Probable Cause: ";
    if (score >= 8)
    {
        cout << "Major electrical fault (Call an electrician immediately).\n";
    }
    else if (score >= 5)
    {
        cout << "Wiring issue or circuit overload.\n";
    }
    else if (score >= 3)
    {
        cout << "Bulb/fixture failure or minor tripping.\n";
    }
    else
    {
        cout << "Unknown cause (Inspect wiring and connections).\n";
    }
}

int main()
{
    cout << "\n--- Advanced Society Maintenance Expert System ---\n";
    cout << "Select an issue to diagnose:\n";
    cout << "1. No water supply on Monday\n";
    cout << "2. No lights in common passage\n";

    int choice;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    if (choice == 1)
    {
        diagnoseWaterIssue();
    }
    else if (choice == 2)
    {
        diagnosePowerIssue();
    }
    else
    {
        cout << "Invalid choice. Exiting.\n";
    }

    cout << "\nThank you for using the Society Maintenance Expert System!\n";
    return 0;
}