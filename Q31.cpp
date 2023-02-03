// A transaction is possibly invalid if :

//     the amount exceeds $1000, or;
//     if it occurs within(and including) 60 minutes of another transaction with the same name in a different city.
// You are given an array of strings transaction where transactions[i] consists of comma - separated values representing the name, time(in minutes), amount, and city of the transaction.
// Return a list of transactions that are possibly invalid.You may return the answer in any order

class Solution
    {
    public:
        vector<string> invalidTransactions(vector<string> &transactions)
        {

            int flag = 0;
            vector<string> name;
            vector<int> time;
            vector<int> amount;
            vector<string> city;
            vector<string> res;

            for (auto str : transactions)
            {
                stringstream ss(str);
                string st;

                while (getline(ss, st, ','))
                {
                    if (flag == 0)
                    {
                        name.emplace_back(st);
                        flag = 1;
                    }
                    else if (flag == 1)
                    {
                        time.emplace_back(stoi(st));
                        flag = 2;
                    }
                    else if (flag == 2)
                    {
                        amount.emplace_back(stoi(st));
                        flag = 3;
                    }
                    else if (flag == 3)
                    {
                        city.emplace_back(st);
                        flag = 0;
                    }
                }
            }

            int j = 0;
            for (auto it : amount)
            {
                if (it > 1000)
                {
                    res.emplace_back(transactions[j]);
                }
                j++;
            }

            for (int i = 0; i < transactions.size(); i++)
            {
                for (int j = 0; j < transactions.size(); j++)
                {
                    if (name[i] == name[j] && city[i] != city[j])
                    {
                        if (abs(time[i] - time[j]) <= 60)
                        {
                            if (amount[i] <= 1000)
                            {
                                res.emplace_back(transactions[i]);
                                break;
                            }
                        }
                    }
                }
            }

            return res;
        }
    };
