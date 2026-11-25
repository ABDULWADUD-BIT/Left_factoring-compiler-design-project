
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Find the common prefix of two strings
string findPrefix(string a, string b)
{
    string prefix = "";

    int i = 0;

    while (i < a.length() && i < b.length() && a[i] == b[i])
    {
        prefix += a[i];
        i++;
    }

    return prefix;
}

// Check whether a production is epsilon
bool isEpsilon(string s)
{
    return s == "epsilon" || s == "eps" || s == "#";
}

// Generate a new non-terminal name
string generateName(string base, int number)
{
    return base + "_factor" + to_string(number);
}

// Perform left factoring recursively
void leftFactoring(string nonTerminal, vector<string> productions)
{
    int factorCount = 1;

    cout << "\nOriginal Grammar:\n";
    cout << nonTerminal << " -> ";

    for (int i = 0; i < productions.size(); i++)
    {
        cout << productions[i];

        if (i != productions.size() - 1)
            cout << " | ";
    }

    cout << "\n\nApplying Left Factoring...\n";

    while (true)
    {
        int bestI = -1;
        int bestJ = -1;
        string bestPrefix = "";

        // Find the longest common prefix
        // among all pairs of productions
        for (int i = 0; i < productions.size(); i++)
        {
            for (int j = i + 1; j < productions.size(); j++)
            {
                string prefix = findPrefix(
                    productions[i], productions[j]
                );

                if (prefix.length() > bestPrefix.length())
                {
                    bestPrefix = prefix;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        // Stop if no common prefix exists
        if (bestPrefix == "")
            break;

        // Collect every production having this prefix
        vector<string> group;
        vector<string> remaining;

        for (int i = 0; i < productions.size(); i++)
        {
            if (productions[i].substr(0, bestPrefix.length()) == bestPrefix)
            {
                string suffix = productions[i].substr(bestPrefix.length());

                if (suffix == "")
                    suffix = "epsilon";

                group.push_back(suffix);
            }
            else
            {
                remaining.push_back(productions[i]);
            }
        }

        // Generate a new non-terminal
        string newNT = generateName(nonTerminal, factorCount);
        factorCount++;

        // Add the factored production
        remaining.push_back(bestPrefix + " " + newNT);

        // Display the transformation
        cout << "\nStep " << factorCount - 1 << ":\n";

        cout << nonTerminal << " -> ";

        for (int i = 0; i < remaining.size(); i++)
        {
            cout << remaining[i];

            if (i != remaining.size() - 1)
                cout << " | ";
        }

        cout << "\n";

        cout << newNT << " -> ";

        for (int i = 0; i < group.size(); i++)
        {
            cout << group[i];

            if (i != group.size() - 1)
                cout << " | ";
        }

        cout << "\n";

        // Replace old productions with new productions
        productions = remaining;

        // Recursively factor the new group
        leftFactoring(newNT, group);
    }

    // Display final grammar for this non-terminal
    cout << "\nFinal productions for " << nonTerminal << ":\n";

    cout << nonTerminal << " -> ";

    for (int i = 0; i < productions.size(); i++)
    {
        cout << productions[i];

        if (i != productions.size() - 1)
            cout << " | ";
    }

    cout << "\n";
}

int main()
{
    string nonTerminal;
    int n;

    cout << "====================================\n";
    cout << "       LEFT FACTORING TOOL\n";
    cout << "====================================\n";

    cout << "\nEnter non-terminal: ";
    cin >> nonTerminal;

    cout << "Enter number of productions: ";
    cin >> n;

    if (n < 1)
    {
        cout << "Invalid number of productions!\n";
        return 0;
    }

    vector<string> productions(n);

    cout << "\nEnter productions (without -> or |):\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Production " << i + 1 << ": ";
        cin >> productions[i];

        if (productions[i].empty())
        {
            cout << "Invalid production!\n";
            return 0;
        }
    }

    leftFactoring(nonTerminal, productions);

    cout << "\n====================================\n";
    cout << "       LEFT FACTORING COMPLETED\n";
    cout << "====================================\n";

    return 0;
}



