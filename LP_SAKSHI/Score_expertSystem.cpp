#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

bool ask_question(const string &question)
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

// 10 Evaluation Criteria
bool is_punctual() { return ask_question("1. Is the employee punctual?"); }
bool meets_deadlines() { return ask_question("2. Does the employee meet deadlines?"); }
bool shows_initiative() { return ask_question("3. Does the employee show initiative?"); }
bool communicates_well() { return ask_question("4. Does the employee communicate well?"); }
bool works_in_team() { return ask_question("5. Does the employee work well in a team?"); }
bool handles_pressure() { return ask_question("6. Can the employee handle pressure?"); }
bool is_adaptable() { return ask_question("7. Is the employee adaptable to change?"); }
bool has_problem_solving_skills() { return ask_question("8. Does the employee have good problem-solving skills?"); }
bool is_detail_oriented() { return ask_question("9. Is the employee detail-oriented?"); }
bool accepts_feedback() { return ask_question("10. Does the employee take feedback positively?"); }

int main()
{
    cout << "\n--- Employee Performance Evaluation ---\n"
         << endl;

    int score = 0;

    if (is_punctual())
        score++;
    if (meets_deadlines())
        score++;
    if (shows_initiative())
        score++;
    if (communicates_well())
        score++;
    if (works_in_team())
        score++;
    if (handles_pressure())
        score++;
    if (is_adaptable())
        score++;
    if (has_problem_solving_skills())
        score++;
    if (is_detail_oriented())
        score++;
    if (accepts_feedback())
        score++;

    cout << "\n--- Performance Summary ---\n";
    cout << "Total Score: " << score << "/10\n";

    // Scorecard logic
    if (score == 10)
        cout << "Outstanding: Perfect performance in all areas.\n";
    else if (score >= 8)
        cout << "Excellent: Very strong performance with minor scope for growth.\n";
    else if (score >= 6)
        cout << "Good: Consistently meets expectations, can improve further.\n";
    else if (score >= 4)
        cout << "Fair: Some strengths, but multiple areas need improvement.\n";
    else if (score >= 2)
        cout << "Poor: Significant improvement needed across most areas.\n";
    else
        cout << "Critical: Immediate performance intervention required.\n";

    return 0;
}
